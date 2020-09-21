#ifndef INCLUDED_SCC
#define INCLUDED_SCC

#include <vector>
#include <list>

class Graph {
  private:
    int m_vertexCount;
    int m_edgeCount;
    std::vector<std::list<int> > m_adjacency;
    std::vector<std::list<int> > m_reverseAdjacency;

  public:
    Graph(int vertexCount);

    Graph createReversed() const;
    int vertexCount() const;
    int edgeCount() const;
    const std::list<int>& adjacent(int vertex) const;

    void addEdge(int source, int destination);
};

class SccCalculator {
  private:
    Graph m_graph;
    Graph m_reversedGraph;

  public:
    SccCalculator(const Graph& graph);
    void run(std::vector<int> *outGroups) const;

  private:
    void _computeSccs(std::vector<int> *outGroups) const;
    void _computeOrder(std::vector<int> *outOrder) const;
};

#endif // INCLUDED_SCC
