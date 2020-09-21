#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char intstr[16] = { '\0' };

    itoa(666, intstr, 10);
    fputs(intstr, stdout);
    return 0;
}
