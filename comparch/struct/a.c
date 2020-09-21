#include <stdlib.h>
#include <stdio.h>

typedef struct _my_struct_t {
    int a;
    int b;
} my_struct_t;

int main(void) {
    my_struct_t my_struct = { .a = 1, .b = 2 };
    printf("%d %d\n", my_struct.a, my_struct.b);

    return 0;
}

