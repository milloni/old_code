#include <stdlib.h>
#include <stdio.h>

void f(void) {
    static int a = 1;
    printf("%d\n", a);
    a = 0;
}

int main(void) {
    for (int i = 0; i < 5; i++) f();
    return 0;
}

