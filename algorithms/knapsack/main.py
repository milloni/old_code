import ks

def print_table(table):
    for i in range(0, len(table)):
        for j in range(0, len(table[i])):
            if j != 0:
                print(" ", end="")
            print(table[i][j], end="")
        print()


def main():
    input_line = input().split()
    size = int(input_line[0])
    item_count = int(input_line[1])
    values = []
    weights = []
    for i in range(0, item_count):
        input_line = input().split()
        values.append(int(input_line[0]))
        weights.append(int(input_line[1]))
#    print_table(ks.get_table(size, values, weights))
    print(ks.get_optimal_solution(size, values, weights)[0])


if __name__ == '__main__':
    main()
