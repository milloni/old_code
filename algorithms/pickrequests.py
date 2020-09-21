#!/usr/bin/python3

import random
import sys
import threading

def _conflict(a, b):
    x1, x2 = a
    y1, y2 = b
    if x1 < y2 and x2 > y1:
        return True
    return False


def conflict(a, b):
    if _conflict(a, b):
        return True
    if _conflict(b, a):
        return True
    return False

def random_requests(number):
    result = []
    for i in range(0, number):
        x = random.randint(0, 9)
        y = random.randint(x + 1, 10)
        while (x, y) in result:
            x = random.randint(0, 9)
            y = random.randint(x + 1, 10)
        result.append((x, y))
    return sorted(result)


def schedule_alg1(r):
    result = []
    rcopy = list(r)
    while rcopy:
        earliest_finish_idx = 0
        for i, val in enumerate(rcopy):
            x, y = val
            if y < rcopy[earliest_finish_idx][1]:
                earliest_finish_idx = i
        earliest_finish = rcopy[earliest_finish_idx]
        result.append(earliest_finish)
        rcopy.remove(earliest_finish)
        rcopycopy = list(rcopy)
        for i, val in enumerate(rcopycopy):
            #print("rcopy", i, rcopyrcopy, earliest_finish, val)
            if conflict(earliest_finish, val):
                #print("REMOVE", val)
                rcopy.remove(val)
    return sorted(result)


def schedule_alg2(r):
    result = []
    rcopy = list(r)
    while rcopy:
        num_conflicts = {}
        for val in rcopy:
            num_conflicts[val] = 0
        for i, val in enumerate(rcopy):
            for j, val2 in enumerate(rcopy):
                if i != j and conflict(val, val2):
                    num_conflicts[val] += 1
        min_conflicts_num = num_conflicts[rcopy[0]]
        min_conflicts_key = rcopy[0]
        for k, v in num_conflicts.items():
            if v < min_conflicts_num:
                #print("!!", k, v)
                min_conflicts_num = v
                min_conflicts_key = k
        #print("@@" + str(min_conflicts_key))
        #print(num_conflicts)
        rcopy.remove(min_conflicts_key)
        result.append(min_conflicts_key)
        #print(rcopy)
        rcopycopy = list(rcopy)
        for val in rcopycopy:
            #print("rcopy", rcopy, val)
            if conflict(min_conflicts_key, val):
                #print("REMOVE", val)
                rcopy.remove(val)
    return sorted(result)

gtfo_please = False
lock = threading.Lock()
def run(number, wtf):
    global gtfo_please
    while True:
        requests = random_requests(number)
        #print("REQUESTS: " + str(requests))
        alg1_result = schedule_alg1(requests)
        #print("RESULT: " + str(alg1_result))
        alg2_result = schedule_alg2(requests)
        #print("RESULT2: " + str(alg2_result))
        if len(alg1_result) != len(alg2_result):
            with lock:
                if gtfo_please:
                    break
                gtfo_please = True
            print("Requests: " + str(requests))
            print("ALG1:")
            print("    Result: " + str(alg1_result))
            print("ALG2:")
            print("    Result: " + str(alg2_result))
            break
            sys.exit(0)


def main():
    number = int(sys.argv[1])
    threads = [threading.Thread(target=run, args=(i, 1)) for i in range(1, number + 1)]
    for x in threads:
        x.start()
    for x in threads:
        x.join()
    #run(number)


if __name__ == '__main__':
    main()

