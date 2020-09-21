#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <cassert>
#include <stack>
#include <algorithm>

class Knapsack {
  public:
    Knapsack(
        const std::vector<int> values,
        const std::vector<int> weights,
        int knapsackSize);

    void run();
    int totalValue() const;

  private:
    std::vector<int> m_values;
    std::vector<int> m_weights;
    int m_knapsackSize;
    std::map<std::pair<int, int>, int> m_solutions;
    int m_totalValue;

    void findSolution(int itemIndex, int size);
};

Knapsack::Knapsack(
    const std::vector<int> values,
    const std::vector<int> weights,
    int knapsackSize)
    : m_values(values)
    , m_weights(weights)
    , m_knapsackSize(knapsackSize)
    , m_totalValue(-1)
{
    assert(values.size() > 0);
    assert(values.size() == weights.size());
    assert(knapsackSize > 0);
}

void Knapsack::run()
{
    assert(m_solutions.empty());
    findSolution(m_values.size() - 1, m_knapsackSize);
    auto key = std::make_pair(m_values.size() - 1, m_knapsackSize);
    m_totalValue = m_solutions.at(key);
}

int Knapsack::totalValue() const
{
    return m_totalValue;
}

void Knapsack::findSolution(int itemIndex, int size)
{
    assert(itemIndex >= 0);
    assert(itemIndex < static_cast<int>(m_values.size()));
    assert(size >= 0);
    int value = m_values[itemIndex];
    int weight = m_weights[itemIndex];
    auto subproblem = std::make_pair(itemIndex, size);

    if (itemIndex == 0) {
        //m_solutions[subproblem] = 0;
        m_solutions[subproblem] = weight <= size ? value : 0;
        return;
    }

    if (m_solutions.find(subproblem) == m_solutions.end()) {
        findSolution(itemIndex - 1, size);
        int firstSol = m_solutions.at(std::make_pair(itemIndex - 1, size));
        int secondSol = -1;
        if (weight <= size) {
            findSolution(itemIndex - 1, size - weight);
            secondSol = m_solutions.at(std::make_pair(itemIndex - 1, size - weight)) + value;
        }
        m_solutions[subproblem] = std::max(firstSol, secondSol);
        assert(m_solutions[subproblem] >= 0);
        assert(size != 0 || m_solutions[subproblem] == 0);
        return;
    }
}

int main()
{
    int knapsackSize;
    std::cin >> knapsackSize;
    int itemCount;
    std::cin >> itemCount;
    std::vector<int> values(itemCount);
    std::vector<int> weights(itemCount);
    for (int i = 0; i < itemCount; i++) {
        std::cin >> values[i];
        std::cin >> weights[i];
    }

    Knapsack knapsack(values, weights, knapsackSize);
    knapsack.run();
    std::cout << knapsack.totalValue() << std::endl;
    return 0;
}
