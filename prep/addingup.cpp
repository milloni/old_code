#include <vector>
#include <iostream>
#include <unordered_set>

bool doesAddUp(const std::vector<int>& values, int number)
{
    std::unordered_set<int> set;
    for (int x : values) {
        set.insert(x);
    }
    for (int x : values) {
        if (set.find(x - number) != set.end()) {
            std::cout << x << " " << x - number << std::endl;
            return true;
        }
    }
    return false;
}

int main()
{
    int x;
    int n;
    std::cin >> x;
    std::cin >> n;
    std::vector<int> values(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i];
    }
    std::cout << (doesAddUp(values, x) ? "Yes" : "No") << std::endl;
    return 0;
}
