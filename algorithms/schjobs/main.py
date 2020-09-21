#!/usr/bin/python3

import suboptimal
import optimal

def get_score(sch):
    result = 0
    for i, job in enumerate(sch):
        w, l = job
        ct = 0
        for ww, ll in sch[:i + 1]:
            ct += ll
        ct *= w
        result += ct
    return result


def main():
    num_jobs = int(input())
    jobs = []
    for i in range(0, num_jobs):
        input_line = input().split()
        weight = int(input_line[0])
        length = int(input_line[1])
        jobs.append((weight, length))
    scheduled_jobs_suboptimal = suboptimal.schedule(jobs)
    scheduled_jobs_optimal = optimal.schedule(jobs)
    score_suboptimal = get_score(scheduled_jobs_suboptimal)
    score_optimal = get_score(scheduled_jobs_optimal)
    print("suboptimal:", score_suboptimal)
    print("optimal:", score_optimal)
    #print("suboptimal:", scheduled_jobs_suboptimal)


if __name__ == '__main__':
    main()

