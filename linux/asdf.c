#include <stdlib.h>
#include <stdio.h>

int main(void) {
    const char *str = "AAAAAAAA";
    printf("%20s\n", str);
    printf("%-20s\n", str);
    return 0;
}

