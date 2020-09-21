GAP = "-"

def get_subproblems_table(a, b, penalties):
    subproblems = []
    for i in range(0, len(a) + 1):
        subproblems.append([])
    for i in range(0, len(a) + 1):
        for j in range(0, len(b) + 1):
            subproblems[i].append(0)

    for i in range(0, len(a)):
        subproblems[i + 1][0] = penalties(a[i], GAP)
    for i in range(0, len(b)):
        subproblems[0][i + 1] = penalties(b[i], GAP)

    for i in range(0, len(a)):
        for j in range(0, len(b)):
            case_a = subproblems[i - 1 + 1][j - 1 + 1] + penalties(a[i], b[j])
            case_b = subproblems[i + 1][j - 1 + 1] + penalties(GAP, b[j])
            case_c = subproblems[i - 1 + 1][j + 1] + penalties(a[i], GAP)
            min_case = min(case_a, case_b, case_c)
            subproblems[i + 1][j + 1] = min_case
    return subproblems


def get_alignment_from_table(subproblems):
    pass


def get_optimal_alignment(a, b, penalties):
    subproblems = get_subproblems_table(a, b, penalties)
    alignment = get_alignment_from_table(subproblems)
    return alignment


def get_alignment_score(a, b, penalties):
    subproblems = get_subproblems_table(a, b, penalties)
    return subproblems[len(a)][len(b)]
