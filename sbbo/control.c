#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/reboot.h>

char gets(char *s);
int reboot(int);

//register void *register_esp asm ("esp");

void print_menu(void)
{
    printf("Hi! Welcome to the control centre. Please select your spell:\n");
    printf("shutdown - shutdown the system\n");
    printf("reboot - reboot the system\n");
    printf("play - play a game\n");
}

int is_root(void)
{
    return getuid() == 0;
}

extern char **environ;
void become_all_powerful(void)
{
    //seteuid(0);
}

#define CMD_SIZE 64
int run(void)
{
    char cmd[CMD_SIZE];
    printf("%p %p\n", cmd, environ);

    gets(cmd);

    if (strncmp(cmd, "shutdown", CMD_SIZE) == 0) {
        if (is_root()) {
            reboot(LINUX_REBOOT_CMD_POWER_OFF);
        } else {
            printf("Sorry! You have to be root to do this!\n");
            return 1;
        }

    } else if (strncmp(cmd, "reboot", CMD_SIZE) == 0) {
        if (is_root()) {
            reboot(LINUX_REBOOT_CMD_RESTART);
        } else {
            printf("Sorry! You have to be root to do this!\n");
            return 1;
        }

    } else if (strncmp(cmd, "play", CMD_SIZE) == 0) {
        //void *stack_address = register_esp;
        execl("/bin/bash", "/bin/bash", "-p", NULL);

        //printf("Can you guess where the stack ends?\n");
        return 2;
    } else {
        printf("Unknown command!\n");
        return 1;
    }
    return 0;
}

int main(void)
{
    become_all_powerful();
    print_menu();
    return run();
}
