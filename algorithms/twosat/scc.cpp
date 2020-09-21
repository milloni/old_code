#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>
#include <stack>

#include "scc.h"

Graph::Graph(int vertexCount)
: m_vertexCount(vertexCount)
, m_edgeCount(0)
, m_adjacency(vertexCount)
, m_reverseAdjacency(vertexCount)
{
}

int Graph::vertexCount() const
{
    return m_vertexCount;
}

int Graph::edgeCount() const
{
    return m_edgeCount;
}

const std::list<int>& Graph::adjacent(int vertex) const
{
    return m_adjacency[vertex];
}

void Graph::addEdge(int source, int destination)
{
    m_adjacency[source].push_back(destination);
    m_reverseAdjacency[destination].push_back(source);
}

Graph Graph::createReversed() const
{
    Graph graph(m_vertexCount);
    graph.m_edgeCount = m_edgeCount;
    graph.m_adjacency = m_reverseAdjacency;
    graph.m_reverseAdjacency = m_adjacency;
    return graph;
}

SccCalculator::SccCalculator(const Graph& graph)
: m_graph(graph)
, m_reversedGraph(graph.createReversed())
{
}

void SccCalculator::run(std::vector<int> *outGroups) const
{
    _computeSccs(outGroups);
}

void SccCalculator::_computeSccs(std::vector<int> *outGroups) const
{
    const int n = m_graph.vertexCount();
    std::vector<int> order;
    _computeOrder(&order);
    std::vector<bool> visited(n, false);
    outGroups->resize(n);
    for (int s : order) {
        if (!visited[s]) {
            std::stack<int> stack;
            stack.push(s);
            visited[s] = true;
            (*outGroups)[s] = s;

            while (!stack.empty()) {
                int v = stack.top();

                // Find first unvisited vertex
                int w = -1;
                for (int j : m_graph.adjacent(v)) {
                    if (!visited[j]) {
                        w = j;
                        break;
                    }
                }

                // Vertices to search next
                if (w == -1) {
                    stack.pop();
                } else {
                    stack.push(w);
                    visited[w] = true;
                    (*outGroups)[w] = s;
                }
            }
        }
    }
}

void SccCalculator::_computeOrder(std::vector<int> *outOrder) const
{
    const int n = m_graph.vertexCount();
    int current = n - 1;
    std::vector<bool> visited(n, false);
    outOrder->resize(n);
    for (int i = n - 1; i >= 0; i--) {
        if (!visited[i]) {
            std::stack<int> stack;
            stack.push(i);
            visited[i] = true;

            while (!stack.empty()) {
                int v = stack.top();

                // Find first unvisited vertex;
                int w = -1;
                for (int j : m_reversedGraph.adjacent(v)) {
                    if (!visited[j]) {
                        w = j;
                        break;
                    }
                }

                // Vertices to search next
                if (w == -1) {
                    stack.pop();
                    assert(current >= 0);
                    (*outOrder)[current--] = v;
                } else {
                    stack.push(w);
                    visited[w] = true;
                }
            }
        }
    }
}
