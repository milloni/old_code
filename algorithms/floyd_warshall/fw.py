#!/usr/bin/env python3

import sys
import os

def solve_subproblems(vertex_count, edges, adjacency_list):
    # Set up
    edge_count = len(edges)
    cache_count = 2
    solutions = []
    for i in range(0, vertex_count):
        solutions.append([])
        for j in range(0, vertex_count):
            solutions[i].append([])
            for k in range(0, cache_count):
                solutions[i][j].append(float("inf"))
    print("Number of vertices:", vertex_count)

    # Base cases
    for i in range(0, vertex_count):
        for j in range(0, vertex_count):
            if i == j:
                solutions[i][j][0] = .0
    for v, w, l in edges:
        if l < solutions[v][w][0]:
            solutions[v][w][0] = l

    # Recursion
    #iteration_count = vertex_count + 1
    for k in range(0, vertex_count):
        print("Iteration: ", k)
        for i in range(0, vertex_count):
            for j in range(0, vertex_count):
                solutions[i][j][1] = min([
                    solutions[i][j][0],
                    solutions[i][k][0] + solutions[k][j][0]
                ])
                solutions[i][j][0] = solutions[i][j][1]
    return solutions


def find_shortest_paths(vertex_count, edges, adjacency_list):
    # Run computation
    shortest_paths = []
    solutions = solve_subproblems(vertex_count, edges, adjacency_list)
    for i in range(vertex_count):
        shortest_paths.append([])
        for j in range(vertex_count):
            shortest_paths[i].append(solutions[i][j][1])

    # Check for negative-sum cycles
    for i in range(0, vertex_count):
        if shortest_paths[i][i] < 0:
            return None
    return shortest_paths


def main():
    vertex_count, edge_count = map(int, input().strip().split())
    edges = []
    for i in range(0, edge_count):
        line_split = input().strip().split()
        v = int(line_split[0]) - 1
        w = int(line_split[1]) - 1
        l = float(line_split[2])
        edges.append((v, w, l))

    adjacency_list = {}
    for edge in edges:
        v = edge[0]
        adjacency_list[v] = edge

    shortest_paths = find_shortest_paths(vertex_count, edges, adjacency_list)
    if not shortest_paths:
        print("NULL")
    else:
        minimum_shortest_path = shortest_paths[0][0]
        for i in range(0, vertex_count):
            for j in range(0, vertex_count):
                if shortest_paths[i][j] < minimum_shortest_path:
                    minimum_shortest_path = shortest_paths[i][j]
        print(minimum_shortest_path)


if __name__ == '__main__':
    main()
