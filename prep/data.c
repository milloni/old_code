#include <stdio.h>

int main(void)
{
    char *str = "asdf";
    str[0] = 'x';
    printf("%s\n", str);
    return 0;
}
