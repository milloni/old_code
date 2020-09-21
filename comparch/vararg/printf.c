#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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

void millonis_printf(const char *fmt, ...)
{
    const char *fmt_curr = fmt;
    char ch;
    int val;
    int arg_idx = 0;
    register int esi asm ("esi");
    register int edx asm ("edx");
    register int ecx asm ("ecx");
    register long r8 asm ("r8");
    register long r9 asm ("r9");
    register long rbp asm ("rbp");
    int esi_saved;
    int edx_saved;
    int ecx_saved;
    int r8d_saved;
    int r9d_saved;
    void *stack_arg_ptr;
    char buf[16] = { '\0' };

    /* registers may be written to, so save the arguments */
    esi_saved = esi;
    edx_saved = edx;
    ecx_saved = ecx;
    r8d_saved = (int)r8;
    r9d_saved = (int)r9;
    stack_arg_ptr = (void *)rbp;
    stack_arg_ptr += sizeof(void *); /* skip saved ebp value */
    stack_arg_ptr += sizeof(void *); /* skip saved return address */

    ch = *fmt_curr;
    while (ch != '\0') {
        if (ch == '%') {
            fmt_curr++;
            ch = *fmt_curr;
            if (ch == '\0') {
                break;
            }
            if (ch == 'd') {
                switch (arg_idx) {
                  case 0:
                    val = esi_saved;
                    arg_idx++;
                    break;
                  case 1:
                    val = edx_saved;
                    arg_idx++;
                    break;
                  case 2:
                    val = ecx_saved;
                    arg_idx++;
                    break;
                  case 3:
                    val = r8d_saved;
                    arg_idx++;
                    break;
                  case 4:
                    val = r9d_saved;
                    arg_idx++;
                    break;
                  default:
                    val = *((int *)stack_arg_ptr);
                    /* int's get promoted to 64-bit values, so skip 8 bytes
                     * instead of 4 */
                    stack_arg_ptr += sizeof(long);
                    break;
                }
                int_to_string(buf, val);
                fputs(buf, stdout);
            }
            /* and so on for other modifiers... */
        } else {
            putchar(ch);
        }
        fmt_curr++;
        ch = *fmt_curr;
    }
}

void millonis_printf2(const char *fmt, ...)
{
    va_list ap;
    const char *fmt_curr = fmt;
    char ch;
    int val;
    char buf[16] = { '\0' };

    va_start(ap, fmt);
    ch = *fmt_curr;
    while (ch != '\0') {
        if (ch == '%') {
            fmt_curr++;
            ch = *fmt_curr;
            if (ch == '\0') {
                break;
            }
            if (ch == 'd') {
                val = va_arg(ap, int);
                int_to_string(buf, val);
                fputs(buf, stdout);
            }
            /* and so on for other modifiers... */
        } else {
            putchar(ch);
        }
        fmt_curr++;
        ch = *fmt_curr;
    }
    va_end(ap);
}

int main(void)
{
    /* asdf1x yz2qwerty 3 4 5 6 7 8 9 */
    millonis_printf("asdf%dx yz%dqwerty %d %d %d %d %d %d %d\n", 1, 2431,
        34153, 4, 5, 6, 7, 8, 9);
    millonis_printf("asdf%dx yz%dqwerty %d %d %d %d %d %d %d\n", 1, 2431,
        34153, 4, 5, 6, 7, 8, 9);

    return 0;
}
