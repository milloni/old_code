#include <iostream>

std::string recontructAlphabet(const std::vector<std::string> &words)
{
    int mergedSize = 0;
    for (int = 0; i < static_cast<int>(words.size()); i++) {
        totalSize += words[i].size();
    }
    std::string merged;
    merged.reserve(mergedSize);

    std::vector<int> idxs(words.size(), 0);
    for (int i = 0; i < mergedSize; i++) {
        int strIdx = 0;
        int minIdx = 0;
        for (int j = 0; j < static_cast<int>(words.size()); j++) {
            
        }
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::string> words;
    words.reserve(n);
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        words.push_back(s);
    }

    return 0;
}
