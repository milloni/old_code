#include <stdio.h>
#include <stdlib.h>

void int_to_string(char *buf, int val)
{
    int i = 0;
    int j = 0;
    int is_negative = 0;
    int tmp;

    if (val == 0) {
        buf[0] = '0';
        return;
    }
    if (val < 0) {
        val *= -1;
        is_negative = 1;
    }
    while (val > 0) {
        buf[i++] = '0' + (val % 10);
        val /= 10;
    }
    if (is_negative) {
        buf[i++] = '-';
    }
    for (j = 0; j < i / 2; j++) {
        tmp = buf[j];
        buf[j] = buf[i - j - 1];
        buf[i - j - 1] = tmp;
    }
    buf[i] = '\0';
}

int main(int argc, char **argv)
{
    char str[16] = { '\0' };
    int val;

    if (argc != 2) {
        return 1;
    }
    val = atoi(argv[1]);
    int_to_string(str, val);
    fputs(str, stdout);
    putchar('\n');
    return 0;
}
