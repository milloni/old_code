#include <iostream>

int main()
{
    char *str = "asdf";
    str[0] = 'x';
    std::cout << str << std::endl;
    return 0;
}
