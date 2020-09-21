#include <vector>
#include <string>
#include <iostream>

#include "scc.h"

int vertexIndex(int clauseIndex, int clauseCount)
{
    if (clauseIndex > 0) {
        return clauseIndex - 1;
    } else {
        return clauseCount - clauseIndex - 1;
    }
}

int negationIndex(int vertex, int clauseCount)
{
    if (vertex >= clauseCount) {
        return vertex - clauseCount;
    } else {
        return vertex + clauseCount;
    }
}

bool hasSolution(const std::vector<int>& groups)
{
    const int vertexCount = static_cast<int>(groups.size());
    const int clauseCount = vertexCount / 2;
    for (int i = 0; i < clauseCount; i++) {
        if (groups[i] == groups[clauseCount + i]) {
            return false;
        }
    }
    return true;
}

int main()
{
    int clauseCount;
    std::cin >> clauseCount;
    int vertexCount = 2 * clauseCount;
    Graph graph(vertexCount);
    for (int i = 0; i < clauseCount; i++) {
        int first;
        std::cin >> first;
        int second;
        std::cin >> second;

        int firstIndex = vertexIndex(first, clauseCount);
        int secondIndex = vertexIndex(second, clauseCount);
        graph.addEdge(negationIndex(firstIndex, clauseCount), secondIndex);
        graph.addEdge(negationIndex(secondIndex, clauseCount), firstIndex);
    }

    SccCalculator scc(graph);
    std::vector<int> groups;
    scc.run(&groups);

    if (hasSolution(groups)) {
        std::cout << "There EXISTS a solution!" << std::endl;
    } else {
        std::cout << "There is no solution!" << std::endl;
    }
}
