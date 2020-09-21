#!/usr/bin/python3

def union(clusters, cluster_sizes, p, q):
    if p == q:
        return
    rp = root(clusters, p)
    rq = root(clusters, q)
    if cluster_sizes[rp] > cluster_sizes[rq]:
        _union(clusters, cluster_sizes, rp, rq)
    else:
        _union(clusters, cluster_sizes, rq, rp)


def _union(clusters, cluster_sizes, rp, rq):
    clusters[rq] = rp
    cluster_sizes[rp] += cluster_sizes[rq]


def root(clusters, p):
    q = clusters[p]
    while q != clusters[q]:
        q = clusters[q]
    return q


def flip_bit(s, index):
    if s[index] == ord("1"):
        s[index] = ord("0")
    else:
        assert s[index] == ord("0")
        s[index] = ord("1")


def get_codes_with_distance_one(code):
    new_code = bytearray(code, "utf-8")
    for index, char in enumerate(code):
        if index != 0:
            flip_bit(new_code, index - 1)
        flip_bit(new_code, index)
        yield str(new_code, "utf-8")


def get_codes_with_distance_two(code):
    for s in get_codes_with_distance_one(code):
        new_code = bytearray(s, "utf-8")
        for index, char in enumerate(code):
            if index != 0:
                flip_bit(new_code, index - 1)
            flip_bit(new_code, index)
            str_new_code = str(new_code, "utf-8")
            if code != str_new_code:
                yield str_new_code


def get_num_clusters(codes):
    vertices_by_code = {}
    cluster_sizes = [1] * len(codes)
    clusters = []
    for index, code in enumerate(codes):
        vertices_by_code[code] = index
        clusters.append(index)

    for index, code in enumerate(codes):
        for comp_code in get_codes_with_distance_one(code):
            if comp_code in vertices_by_code:
                comp_index = vertices_by_code[comp_code]
                union(clusters, cluster_sizes, index, comp_index)

    for index, code in enumerate(codes):
        for comp_code in get_codes_with_distance_two(code):
            if comp_code in vertices_by_code:
                comp_index = vertices_by_code[comp_code]
                union(clusters, cluster_sizes, index, comp_index)

    #print(clusters)
    #verify_solution(codes, clusters)
    roots = [root(clusters, x) for x in clusters]
    return count_unique_elements(roots)


def count_unique_elements(codes):
    count = 0
    codes_sorted = sorted(codes)
    for index in range(0, len(codes_sorted) - 1):
        if codes_sorted[index] != codes_sorted[index + 1]:
            count += 1
    return count + 1


def distance(a, b):
    assert len(a) == len(b)
    lengh = len(a)
    count = 0
    for x, y in zip(a, b):
        if x != y:
            count += 1
    return count


def verify_solution(codes, clusters):
    for xi, x in enumerate(codes):
        for yi, y in enumerate(codes):
            dist = distance(x, y)
            if dist > 2 and clusters[xi] == clusters[yi]:
                print("should not be together:", xi, yi)
            if dist <= 2 and clusters[xi] != clusters[yi]:
                print("should be togerther:", xi, yi)


def main():
    cluster_count, bit_count = map(int, input().strip().split())
    codes = []
    for i in range(0, cluster_count):
        codes.append("".join(input().strip().split()))
        assert len(codes[i]) == bit_count
    numClusters = get_num_clusters(codes)
    print(numClusters)

if __name__ == '__main__':
    main()
