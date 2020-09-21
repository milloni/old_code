#!/usr/bin/python3

def jobs_key(j):
    w, l = j
    return (w - l, w)


def schedule(jobs):
    schjobs = sorted(jobs, key=jobs_key, reverse=True)
    return schjobs

