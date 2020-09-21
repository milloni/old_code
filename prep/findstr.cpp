#include <iostream>
#include <string>

int findStr(const std::string& haystack, const std::string& needle)
{
    int endIdx = haystack.size() - needle.size() + 1;
    for (int i = 0; i < endIdx; i++) {
        for (int j = 0; haystack[i + j] == needle[j]; j++) {
            if (j == static_cast<int>(needle.size()) - 1 && haystack[i + j] == needle[j]) {
                return i;
            }
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cerr << "Missing arguments" << std::endl;
        return 1;
    }
    std::string haystack(argv[1]);
    std::string needle(argv[2]);
    int idx = findStr(haystack, needle);
    if (idx == -1) {
        std::cout << "Match not found!" << std::endl;
    } else {
        std::cout << "Index: " << idx << std::endl;
        std::cout << haystack << std::endl;
        for (int i = 0; i < idx; i++) {
            std::cout << " ";
        }
        std::cout << needle << std::endl;
    }
}
