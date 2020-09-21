#include <stdio.h>
#include <stdlib.h>

void func(void *addr)
{
    printf("%p\n", addr);
}

int main(void)
{
    void *addr = &func;

    func(addr);
    return 0;
}
