#!/usr/bin/python3

import heapq
import queue

class Node:
    def __init__(self, symbol):
        self.symbol = symbol
        self.left = None
        self.right = None


    def __lt__(self, other):
        return True


class Tree:
    def __init__(self, root):
        self.root = root


def codetree(priorities, symbols):
    pq = []
    for p, s in zip(priorities, symbols):
        node = Node(s)
        heapq.heappush(pq, (p, node))
    while len(pq) > 1:
        pa, na = heapq.heappop(pq)
        pb, nb = heapq.heappop(pq)
        p = pa + pb
        n = Node(None)
        n.left = na;
        n.right = nb;
        heapq.heappush(pq, (p, n))
    r = heapq.heappop(pq)
    return Tree(r[1])


def codedict(tree):
    result = {}
    q = queue.LifoQueue()
    q.put((tree.root, ""))
    while not q.empty():
        n, prefix = q.get()
        if n.symbol is None:
            if n.left:
                q.put((n.left, prefix + "0"))
            if n.right:
                q.put((n.right, prefix + "1"))
            continue
        assert not n.left and not n.right
        result[n.symbol] = prefix
    return result


def code(priorities, symbols):
    tree = codetree(priorities, symbols)
    return codedict(tree)
        
