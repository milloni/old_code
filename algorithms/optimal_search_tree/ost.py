def get_solutions_table(values, weights):
    size = len(values)
    assert size == len(weights)
    solutions = []
    for i in range(0, size):
        nested = [0] * size
        solutions.append(nested)

    for index, weight in enumerate(weights):
        solutions[index][index] = weight

    for index_range in range(1, size):
        for i in range(0, size - index_range):
            j = i + index_range
            solutions[i][j] = max_value_case(values, weights, solutions, i, j)
    return solutions


def max_value_case(values, weights, solutions, i, j):
    assert j > i
    search_times = []
    sw = sum(weights[i:j+1])
    
    # root_index = i
    search_times.append(sw + solutions[i + 1][j])

    for root_index in range(i + 1, j):
        a = sw + solutions[i][root_index - 1] + solutions[root_index + 1][j]
        search_times.append(a)

    # root_index = j
    search_times.append(sw + solutions[i][j - 1])

    return min(search_times)

