/* gcc -Wall -Wextra -o chrlimit chrlimit.c
 * Test
 * Fix optstring */

#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)

#ifndef RLIM_INFINITY
#define RLIM_INFINITY ((rlim_t) -1)
#endif

enum chrlimit_lim_type {
    LIM_BOTH = 0,
    LIM_SOFT = 1,
    LIM_HARD = 2,
    LIM_NLIM = 3
};

enum chrlimit_action {
    ACTION_NONE = 0,
    ACTION_GET = 1,
    ACTION_SET = 2,
    ACTION_NACTIONS = 3
};

typedef struct _res_info_t {
    int   opt;
    int   res;
    char *sres;
    char *unit;
} res_info_t;

static bool runcmd = false;

static res_info_t resources[] = {
#ifdef RLIMIT_CPU
    { 't', RLIMIT_CPU, "RLIMIT_CPU", "seconds" },
#endif
#ifdef RLIMIT_FSIZE
    { 'f', RLIMIT_FSIZE, "RLIMIT_FSIZE", "bytes" },
#endif
#ifdef RLIMIT_DATA
    { 'd', RLIMIT_DATA, "RLIMIT_DATA", "bytes" },
#endif
#ifdef RLIMIT_STACK
    { 's', RLIMIT_STACK, "RLIMIT_STACK", "bytes" },
#endif
#ifdef RLIMIT_CORE
    { 'c', RLIMIT_CORE, "RLIMIT_CORE", "bytes" },
#endif
#ifdef RLIMIT_RSS
    { 'm', RLIMIT_RSS, "RLIMIT_RSS", "bytes" },
#endif
#ifdef RLIMIT_NOFILE
    { 'n', RLIMIT_NOFILE, "RLIMIT_NOFILE", NULL },
#endif
#ifdef RLIMIT_AS
    { 'v', RLIMIT_AS, "RLIMIT_AS", "bytes" },
#endif
#ifdef RLIMIT_NPROC
    { 'u', RLIMIT_NPROC, "RLIMIT_NPROC", NULL },
#endif
#ifdef RLIMIT_MEMLOCK
    { 'l', RLIMIT_MEMLOCK, "RLIMIT_MEMLOCK", "bytes" },
#endif
#ifdef RLIMIT_LOCKS
    { 'x', RLIMIT_LOCKS, "RLIMIT_LOCKS", NULL },
#endif
#ifdef RLIMIT_SIGPENDING
    { 'i', RLIMIT_SIGPENDING, "RLIMIT_SIGPENDING", NULL },
#endif
#ifdef RLIMIT_MSGQUEUE
    { 'q', RLIMIT_MSGQUEUE, "RLIMIT_MSGQUEUE", "bytes" },
#endif
#ifdef RLIMIT_NICE
    { 'e', RLIMIT_NICE, "RLIMIT_NICE", NULL },
#endif
#ifdef RLIMIT_RTPRIO
    { 'r', RLIMIT_RTPRIO, "RLIMIT_RTPRIO", NULL },
#endif
#ifdef RLIMIT_RTTIME
    { 'R', RLIMIT_RTTIME, "RLIMIT_RTTIME", "microseconds" }
#endif
};

#define NRES ((int)(sizeof(resources) / sizeof(resources[0])))

typedef struct _chrlimit_res_t {
    rlim_t  val;
    uint8_t act;
} chrlimit_res_t;

typedef struct _chrlimit_opt_t {
    int            idx;
    chrlimit_res_t soft;
    chrlimit_res_t hard;
} chrlimit_opt_t;

typedef struct _opts_t {
    char          *cmd;
    int            argc;
    char         **argv;
    bool           report_all;      /* -a */
    bool           help;            /* -h */
    int            numres;
    chrlimit_opt_t resources[NRES];
} opts_t;

static int findres(int opt) {
    for (int i = 0; i < NRES; i++) {
        if (resources[i].opt == opt) {
            return i;
        }
    }
    
    return -1;
}

static int stridx(const char *str, int ch) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) return i;
    }

    return -1;
}

#define STRRLIM(res) case res: return #res
static const char *strres(int res) {
    for (int i = 0; i < NRES; i++) {
        if (resources[i].res == res) return resources[i].sres;
    }

    return "unknown";
}

static void parse_optarg_token(chrlimit_opt_t *opt, const char *token) {
    char typs[5];
    int ret;
    rlim_t par;
    int saverrno;

    errno = 0;
    ret = sscanf(token, "%4s=%ld", typs, &par);
    saverrno = (int)errno;
    if (ret == 0) goto err;

    assert (ret > 0 && ret < 3);
    if (ret == 1) {
        if (saverrno != 0 && saverrno != EINVAL) goto err;
        else if (strcmp(typs, "soft") == 0) opt->soft.act = ACTION_GET;
        else if (strcmp(typs, "hard") == 0) opt->hard.act = ACTION_GET;
        else goto err;

        
    } else { /* ret == 2 */
        if (strcmp(typs, "soft") == 0) {
            opt->soft.act = ACTION_SET;
            opt->soft.val = par;
        }
        else if (strcmp(typs, "hard") == 0) {
            opt->hard.act = ACTION_SET;
            opt->hard.val = par;
        }
        else goto err;

        runcmd = true;
    }

    return;

err:
    fprintf(stderr, "Warning: invalid argument option\n");
    return;
}

static void parse_optarg(chrlimit_opt_t *opt, const char *optarg) {
    char *optargcp;
    char *first = NULL;
    char *second = NULL;
    int optidx;
    size_t optargsz;

    assert(optarg != NULL);
    
    optargsz = strlen(optarg);
    optargcp = malloc(optargsz + 1);
    if (optargcp == NULL) {
        perror("malloc");
        exit(1);
    }
    strncpy(optargcp, optarg, optargsz + 1);
    first = optargcp;

    optidx = stridx(optargcp, ',');
    if (optidx == -1 || optidx == (int)optargsz - 1) {
        second = NULL;
    } else {
        if (optidx == 0) first = NULL;
        else first[optidx] = '\0';
        second = &first[optidx + 1];
    }

    if (first == NULL && second == NULL) {
        fprintf(stderr, "Warning: missing option argument\n");
        return;
    }

    assert(first != NULL);
    parse_optarg_token(opt, first);
    if (second != NULL) {
        parse_optarg_token(opt, second);
    }

    /* fprintf(stderr, "SOFT: act=%d val=%lu HARD: act=%d val=%lu\n", 
            opt->soft.act, opt->soft.val, opt->hard.act, opt->hard.val); */
    free(optargcp);
    return;

}

static void parse_options(opts_t *result, int argc, char **argv) {
    const char *optstr = "a:c:d:e:f:hi:l:m:n:q:r:s:t:v:x:R:";
    int opt;
    int idx;

    memset(result, 0, sizeof(opts_t));
    while ((opt = getopt(argc, argv, optstr)) != -1) {
        if (opt == '?' || opt == ':') {
            continue;
        }

        if (opt == 'h') {
            result->help = true;
            continue;
        }

        if (opt == 'a') {
            result->report_all = true;
            continue;
        }

        idx = findres(opt);
        result->resources[result->numres].idx = idx;
        parse_optarg(&result->resources[result->numres++], optarg);

        assert(idx != -1);
        assert(idx < NRES);
    }

    if (runcmd) {
        if (optind >= argc && runcmd) {
            fprintf(stderr,
                "Warning: requested setting the limit and no command given\n");
            return;
        }

        result->cmd = argv[optind];
        result->argc = argc - optind;
        result->argv = &argv[optind];

        assert(result->cmd != NULL);
        assert(result->argc > 0);
        assert(result->argv != NULL);

    } else {
        result->cmd = NULL;
        result->argc = 0;
        result->argv = NULL;
    }
}

static int none_set(const opts_t *opts) {
    return !opts->report_all && opts->numres == 0;
}

static void printlim(int res, int restype, const struct rlimit *rlim) {
    const char *sres;
    char scur[24];
    char smax[24];

    if (rlim->rlim_cur == RLIM_INFINITY) {
        strcpy(scur, "unlimited");
    } else {
        snprintf(scur, 24 * sizeof(char), "%lu", rlim->rlim_cur);
    }
    
    if (rlim->rlim_max == RLIM_INFINITY) {
        strcpy(smax, "unlimited");
    } else {
        snprintf(smax, 24 * sizeof(char), "%lu", rlim->rlim_max);
    }

    sres = strres(res);
    if (restype == LIM_BOTH) {
        printf("%s: soft=%s,hard=%s\n", sres, scur, smax);
    } else if (restype == LIM_SOFT) {
        printf("%s: soft=%s\n", sres, scur);
    } else { /* restype == LIM_HARD */
        printf("%s: hard=%s\n", sres, smax);
    }
}

static void set_and_print(const chrlimit_opt_t *opt) {
    struct rlimit rlim;
    const char *sres;
    int res = resources[opt->idx].res;

    if (opt->soft.act == ACTION_NONE && opt->hard.act == ACTION_NONE) {
        return;
    }

    memset(&rlim, 0, sizeof(struct rlimit));
    sres = strres(res);
    if (getrlimit(res, &rlim) == -1) {
        fprintf(stderr, "Warning: unable to get the limit: %s\n", sres);
        return;
    }

    if (opt->soft.act == ACTION_SET) rlim.rlim_cur = opt->soft.val;
    if (opt->hard.act == ACTION_SET) rlim.rlim_max = opt->hard.val;
    if (opt->soft.act == ACTION_SET || opt->hard.act == ACTION_SET) {
        if (setrlimit(res, &rlim) == -1) {
            fprintf(stderr, "Warning: unable to set the limit %s\n", sres);
            return;
        }
    }

    assert(opt->soft.act != ACTION_NONE || opt->hard.act != ACTION_NONE);
    if (opt->soft.act == ACTION_GET && opt->hard.act == ACTION_GET) {
        printlim(res, LIM_BOTH, &rlim);
    } else if (opt->soft.act == ACTION_GET) {
        printlim(res, LIM_SOFT, &rlim);
    } else if (opt->hard.act == ACTION_GET) {
        printlim(res, LIM_HARD, &rlim);
    }
}

static void perform_actions(const opts_t *opts) {
    if (opts->report_all) {
        for (int i = 0; i < NRES; i++) {
            const char *sres;
            struct rlimit rlim;
            int res = resources[i].res;

            sres = strres(res);
            if (getrlimit(res, &rlim) == -1) {
                fprintf(stderr, "Unable to get the limit: %s\n", sres);
                return;
            }
            printlim(resources[i].res, LIM_BOTH, &rlim);
        }
        return;
    }

    for (int i = 0; i < NRES; i++) {
        set_and_print(&opts->resources[i]);
    }

    if (opts->cmd != NULL) {
        assert(opts->argc != 0);
        assert(opts->argv != NULL);

        if (execvp(opts->cmd, opts->argv) == -1) {
            perror("execvp");
            fprintf(stderr, "Error: unable to run the command: %s\n", opts->cmd);
            exit(1);
        }
    }
}

static void print_usage(int argc, char **argv) {
    UNUSED(argc);

    /* based on bash's ulimit man page */
    fprintf(stderr,
        "Usage:\n"
        "%s [-abcdefilmnpqrstuvxT [soft[=limit][,hard[=limit]]]] [command]\n"
        "Options:\n"
        "  -a     All current limits are reported\n"
        "  -b     The maximum socket buffer size\n"
        "  -c     The maximum size of core files created\n"
        "  -d     The maximum size of a process's data segment\n"
        "  -e     The maximum scheduling priority (\"nice\")\n"
        "  -f     The maximum size of files written by the shell and its children\n"
        "  -i     The maximum number of pending signals\n"
        "  -l     The maximum size that may be locked into memory\n"
        "  -m     The maximum resident set size (many systems do not honor this limit)\n"
        "  -n     The maximum number of open file descriptors (most systems do not allow this value to be set)\n"
        "  -p     The pipe size in 512-byte blocks (this may not be set)\n"
        "  -q     The maximum number of bytes in POSIX message queues\n"
        "  -r     The maximum real-time scheduling priority\n"
        "  -s     The maximum stack size\n"
        "  -t     The maximum amount of cpu time in seconds\n"
        "  -u     The maximum number of processes available to a single user\n"
        "  -v     The maximum amount of virtual memory available to the shell and, on some systems, to its children\n"
        "  -x     The maximum number of file locks\n"
        "  -T     The maximum number of threads\n",
        argv[0]
    );
}

static void print_usage_short(int argc, char **argv) {
    UNUSED(argc);

    fprintf(stderr,
        "Usage:\n"
        "%s [-abcdefilmnpqrstuvxT [soft[=limit][,hard[=limit]]]] [command]\n",
        argv[0]
    );
}

int main(int argc, char **argv) {
    opts_t opts;

    parse_options(&opts, argc, argv);
    if (opts.help) {
        print_usage(argc, argv);
        return 1;
    }
    if (none_set(&opts)) {
        print_usage_short(argc, argv);
        return 1;
    }

    perform_actions(&opts);
    return 0;
}

