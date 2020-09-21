import seq
import sys

def print_table(table):
    for i in range(0, len(table)):
        nested_len = len(table[i])
        for j in range(0, nested_len):
            if j != 0:
                print(" ", end="")
            print(table[i][j], end="")
        print()


def penalty_function(a, b):
    if a == b:
        return 0
    else:
        return 1


def main():
    if len(sys.argv) != 3:
        print("Usage: {} <stringA> <stringB>")
        sys.exit(1)
    string_a = sys.argv[1].upper()
    string_b = sys.argv[2].upper()
#    print(string_a)
#    print(string_b)
    print_table(seq.get_subproblems_table(string_a, string_b, penalty_function))


if __name__ == '__main__':
    main()
