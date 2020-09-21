#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>

void count(char *character, int *howMany, const std::string& input)
{
    std::unordered_map<char, int> occurrences;
    for (int i = 0; i < 256; i++) {
        occurrences[static_cast<char>(i)] = 0;
    }

    for (char ch : input) {
        occurrences[ch]++;
    }

    std::unordered_map<char, int> firstOccurrence;
    for (int i = 0; i < static_cast<int>(input.size()); i++) {
        char ch = input[i];
        if (firstOccurrence.find(ch) == firstOccurrence.end()) {
            firstOccurrence[ch] = i;
        }
    }

    char resultChar;
    int resultHowMany = -1;
    int resultFirstIdx = -1;
    for (std::pair<const char, int>& x : occurrences) {
        char ch = x.first;
        int val = x.second;
        int firstIdx = firstOccurrence[ch];
        bool doSwap = resultHowMany < val ||
            (resultHowMany == val && firstIdx < resultFirstIdx);
        if (doSwap) {
            resultChar = ch;
            resultHowMany = val;
            resultFirstIdx = firstIdx;
        }
    }

    *character = resultChar;
    *howMany = resultHowMany;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Argument missing!" << std::endl;
        return 1;
    }
    std::string characters(argv[1]);

    char character;
    int howMany;
    count(&character, &howMany, characters);
    std::cout << character << " occurred " << howMany << " times." << std::endl;

    return 0;
}
