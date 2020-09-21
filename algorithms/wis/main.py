#!/usr/bin/python3

import wis

def main():
    weights = []
    weights_length = int(input())
    for _ in range(0, weights_length):
        weights.append(int(input()))
    wis_scores = wis.wis_scores(weights)
    wis_set = wis.wis_set(wis_scores, weights)
    indices = map(lambda x: x - 1, [1, 2, 3, 4, 17, 117, 517, 997])
    def f(x):
        if x:
            return "1"
        return "0"
    out_string = "".join(f(wis_set[i]) for i in indices)
    print(out_string)

if __name__ == '__main__':
    main()
