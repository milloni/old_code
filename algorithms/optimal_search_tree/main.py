import ost
import os
import sys

def print_table(table):
    for horizontal in table:
        for i, x in enumerate(horizontal):
            if i != 0:
                print(" ", end="")
            print(x, end="")
        print()


def main():
    input_count = int(input())
    values = []
    weights = []
    for i in range(0, input_count):
        input_tokens = input().strip().split()
        value = int(input_tokens[0])
        values.append(value)
        weight = float(input_tokens[1])
        weights.append(weight)
    solutions = ost.get_solutions_table(values, weights)
    print_table(solutions)
    print(solutions[0][input_count - 1])


if __name__ == '__main__':
    main()
