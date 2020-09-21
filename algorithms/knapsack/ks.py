
def get_table(size, values, weights):
    assert len(values) == len(weights)
    table = []
    for i in range(0, len(values)):
        table.append([])
    for i in range(0, len(values)):
        for j in range(0, size + 1):
            table[i].append(0)

    for n in range(0, len(values)):
        for s in range(0, size + 1):
            case1 = table[n - 1][s]
            case2 = -1
            if weights[n] <= s:
                case2 = values[n] + table[n - 1][s - weights[n]]
            table[n][s] = max(case1, case2)
    return table


def get_optimal_solution(size, values, weights):
    assert len(values) == len(weights)
    table = get_table(size, values, weights)
    items_that_fit = get_items_that_fit(size, values, weights, table)
    score = get_score(table)
    return (score, None)


def get_items_that_fit(size, values, weights, table):
    result = []
    s = size
    for n in range(len(values) - 1, -1, -1):
        assert s >= 0
        case1 = table[n - 1][s]
        case2 = -1
        if weights[n] <= s:
            case2 = values[n] + table[n - 1][s - weights[n]]
        val = max(case1, case2)
        if val == case2:
            result.append(n)
            s -= weights[n]
    return result


def get_score(table):
    return table[-1][-1]
