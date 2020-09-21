#!/usr/bin/python3

def wis_scores(weights):
    n = len(weights)
    scores = []
    if len(weights) > 0:
        scores.append(weights[0])
    if len(weights) > 1:
        if weights[1] > weights[0]:
            scores.append(weights[1])
        else:
            scores.append(weights[0])
    for i in range(2, n):
        scores.append(max(scores[i - 1], scores[i - 2] + weights[i]))
    return scores


def wis_set(scores, weights):
    n = len(scores)
    result_set = [False] * n
    i = n - 1
    while i > 1:
#        print("INDEX:", i, "SCORE:", scores[i], "WEIGHT:", weights[i])
        if scores[i] - weights[i] == scores[i - 2]:
            result_set[i] = True
            i -= 2
        else:
            assert scores[i] == scores[i - 1]
            result_set[i] = False
            i -= 1
    if result_set[2]:
        result_set[0] = True
    else:
        result_set[1] = True
    return result_set


def wis(weights):
    return wis_set(wis_scores(weights), weights)
