#!/usr/bin/env python3

# Master TODO:
#   * Support for large resources

import atexit
import concurrent.futures;
import getopt
import itertools
import json
import queue
import random
import requests
import sys
import threading
import time

from itertools     import product
from requests      import ConnectionError
from requests      import Timeout
from requests.auth import HTTPBasicAuth
from requests.auth import HTTPDigestAuth

TIMEOUT=6 # TODO: decide what to do with this

names_path = ""
extpath = ""
outpath = ""
recursive = False
verbosity = 1
numthreads = 1
target = ""
show_help = False
outfmt = ""
maxdepth = 3
randshuffle = False
authmethod = ""
user = ""
passwd = ""
max_download_size = 1024 # kbytes

names = []
extensions = []
urlqueue = queue.Queue()
outf = None
target_url = ""
gsession = None

usage_string="""Usage: {0} [options] <path> <url>
       {0} -h for a list of options""".format(sys.argv[0])

usage_string_long ="""Usage: {0} [options] <path> <url>
Options:
  -a    authentication method (basic, digest)
  -d    recursion depth; default 3
  -e    extensions file
  -f    output format (simple, json)
  -h    show this message and exit
  -o    write output to file
  -q    suppress output
  -r    be recursive
  -u    user or user:password
  -v    be verbose
  -w    number of threads
  -R    randomly shuffle the lists""".format(sys.argv[0])


def quiet():
    return verbosity < 1


def verbose():
    return verbosity > 1


# https://stackoverflow.com/questions/5574702/how-to-print-to-stderr-in-python
def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def perr(msg):
    eprint("Error: {0}".format(msg))


def pwrn(msg):
    eprint("Warning: {0}".format(msg))


def pinf(msg):
    eprint("Info: {0}".format(msg))


def print_usage():
    eprint(usage_string)


def print_usage_long():
    eprint(usage_string_long)


def cleanup():
    if outf:
        outf.close()


def parse_options():
    def err_usage(msg):
        if not quiet():
            perr(msg)
            print_usage()
        sys.exit(1)

    global authmethod
    global extpath
    global names_path
    global recursive
    global verbosity
    global numthreads
    global target
    global outpath
    global show_help
    global outfmt
    global maxdepth
    global randshuffle
    global user
    global passwd

    try:
        opts, args = getopt.getopt(sys.argv[1:], "a:d:e:f:ho:qru:vw:R")
    except getopt.GetoptError as err:
        err_usage(str(err))
    
    if len(args) > 0:
        names_path = args[0]
    if len(args) > 1:
        target = args[1]
    for opt, val in opts:
        if opt == "-a":
            val = val.lower().strip()
            if val not in ["basic", "digest"]:
                err_usage("Authentication method must be either basic or digest")
            authmethod = val
        elif opt == "-d":
            try:
                maxdepth = int(val)
            except ValueError as err:
                err_usage("Max depth must be an integer")
        elif opt == "-e":
            extpath = val
        elif opt == "-f":
            val = val.lower().strip()
            if val not in ["simple", "json"]:
                err_usage("Output format must be either simple or json")
            outfmt = val
        elif opt == "-h":
            show_help = True
        elif opt == "-o":
            outpath = val
        elif opt == "-q":
            if verbosity != 1:
                verbosity = 1
                err_usage("Can't specify -v and -q at the same time")
            verbosity = 0
        elif opt == "-r":
            recursive = True
        elif opt == "-u":
            left, sep, right = val.partition(":")
            if not left:
                err_usage("Invalid value for option {0}".format(opt))
            user = left
            if right:
                passwd = right
        elif opt == "-v":
            if verbosity != 1:
                verbosity = 1
                err_usage("Can't specify -v and -q at the same time")
            verbosity = 2
        elif opt == "-w":
            try:
                numthreads = int(val);
            except ValueError as err:
                err_usage("Number of threads must be an integer")
        elif opt == "-R":
            randshuffle = True
    if not outfmt:
        outfmt = "simple"
    if authmethod and not user:
        err_usage("Please specify user credentials to use with -a via -u option")


def auth_failed(resp):
    return resp.status_code == 401 or resp.status_code == 407


def url_alive(url):
    if verbose():
        pinf("Trying to connect to {0}".format(url))
    try:
        resp = gsession.get(url, timeout=TIMEOUT)
    except (ConnectionError, Timeout) as err:
        if not quiet():
            perr(str(err))
        return ""
    if auth_failed(resp):
        if not quiet():
            perr("Authentication failed")
            return ""
    if verbose():
        pinf("{0} is alive".format(url))
    return resp.url


def construct_url(target):
    url = target.lower().strip("/")
    schemas = ["http://", "https://"]
    for sch in schemas:
        if url.startswith(sch):
            return url_alive(url)
    for sch in schemas:
        assert not url.startswith(sch)
        full_url = sch + url
        result = url_alive(full_url)
        if result:
            return result
    return ""


def resp_file_exists(resp):
    # TODO: make this more sophisticated?
    return resp.ok


output_dict = {
    "url": "",
    "names": []
}
def write_output_init(url):
    output_dict["url"] = url


def write_output(name):
    assert outfmt in ["simple", "json"]

    if not quiet():
        print(name)
    if outf:
        if outfmt == "simple":
            print(name, file=outf)
        elif outfmt == "json":
            output_dict["names"].append(name)


def write_output_finalize():
    if outf and outfmt == "json":
        json.dump(output_dict, outf, indent=4)


def check_exists(url, name):
    # TODO: rewrite using context managers?

    if verbose():
        pinf("Trying {0}".format(url))
    try:
        resp = gsession.get(url, timeout=TIMEOUT, stream=True)
        # Do not download large resource but also prevent unnecessary
        # TCP connection teardowns
        for i, _ in enumerate(resp.iter_content(chunk_size=1024)):
            if i > max_download_size:
                break
    except (ConnectionError, Timeout) as err:
        # TODO: quit? try again? do nothing?
        if not quiet():
            pwrn("Unable to connect to {0}".format(url))
        return ""

    if resp_file_exists(resp):
        write_output(get_display_name(url))
        result = name
    else:
        result = ""

    resp.close()
    return result


def url_dir_elig(argurl):
    if argurl[-1] == "/":
        url = argurl[:-1]
    else:
        url = argurl

    left, sep, res = url.rpartition("/")
    if left.endswith("://") or not sep:
        return False
    if not res or res.find(".") != -1:
        return False

    left, sep, res = url.partition("://")
    if not left or not sep:
        return False
    depth = 0
    while res:
        left, sep, res = res.partition("/")
        depth += 1
    #print("argurl =", argurl, "depth =", depth)
    if depth > maxdepth:
        return False

    return True


def get_display_name(url):
    _, _, right = url.partition(target_url)
    right = right.strip("/")
    assert right
    return right


def url_add(a, b):
    while a.endswith("/"):
        a = a[:-1]
    return "{0}/{1}".format(a, b)


def bust_url(url):
    def format_name(arg):
        name, ext = arg
        if ext:
            return "{0}.{1}".format(name, ext)
        else:
            return name

    def worker_func(actual_name):
        requrl = url_add(url, actual_name)
        return check_exists(requrl, actual_name)

    result = []
    extensions2 = extensions + [""]
    with concurrent.futures.ThreadPoolExecutor(max_workers=numthreads) as executor:
        it = map(format_name, product(names, extensions2))
        for ret in executor.map(worker_func, it, chunksize=numthreads):
            if ret:
                result.append(ret)
                full = url_add(url, ret)
                if recursive and url_dir_elig(full):
                    urlqueue.put(full)
    return result
        

def bust_run():
    result = []
    write_output_init(target_url)

    urlqueue.put(target_url)
    while not urlqueue.empty():
        url = urlqueue.get()
        result += bust_url(url)

    write_output_finalize()
    return result


def read_list(li, f):
    for line in f:
        line = line.strip()
        if line and not line.startswith("#"):
            li.append(line)


def getpass(msg):
    try:
        import getpass
        if hasattr(getpass, "getpass"):
            use_getpass = True
        else:
            use_getpass = False
    except ImportError:
        use_getpass = False
    
    if use_getpass:
        passwd = getpass.getpass(prompt=msg)
    else:
        passwd = input(msg)
    return passwd


def main():
    global outf
    global target_url
    global gsession
    global passwd

    atexit.register(cleanup)
    parse_options()
    if show_help:
        print_usage_long()
        sys.exit(1)

    if not names_path:
        if not quiet():
            perr("Missing file list")
            print_usage()
        sys.exit(1)
    if not target:
        if not quiet():
            perr("Missing target url")
            print_usage()
        sys.exit(1)
    
    try:
        with open(names_path, "r") as f:
            read_list(names, f)
    except OSError as err:
        if not quiet():
            perr(str(err))
            perr("Unable to read from file: {0}".format(names_path))
        sys.exit(1)
    if not names:
        if not quiet():
            perr("List of files is empty")
        sys.exit(1)

    if extpath:
        try:
            with open(extpath, "r") as f:
                read_list(extensions, f)
        except OSError as err:
            if not quiet():
                perr(str(err))
                perr("Unable to read from file: {0}".format(extpath))
            sys.exit(1)

    if outpath:
        try:
            outf = open(outpath, "w")
        except OSError as err:
            if not quiet():
                perr(str(err))
                perr("Unable to open file {0} for writing".format(outpath))
            sys.exit(1)

    if randshuffle:
        random.shuffle(names)
        random.shuffle(extensions)

    assert authmethod in ["", "basic", "digest"]
    if authmethod and not passwd:
        if quiet():
            passwd = getpass("")
        else:
            passwd = getpass("Enter the password: ")
            
    gsession = requests.Session()
    if authmethod:
        assert user and passwd
        if authmethod == "basic":
            gsession.auth = HTTPBasicAuth(user, passwd)
        elif authmethod == "digest":
            gsession.auth = HTTPDigestAuth(user, passwd)

    target_url = construct_url(target)
    if not target_url:
        if not quiet():
            perr("Unable to connect to {0}".format(target))
        sys.exit(1)
    bust_run()


if __name__ == '__main__':
    main()
else:
    verbosity = 0

