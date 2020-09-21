void _exit(int status);
int printf(const char *format, ...);
int execve(const char *filename, char *const argv[], char *const envp[]);
extern char **environ;

char argv0[] = { "/bin/sh" };
char argv1[] = { "-p" };
char *argv[] = { argv0, argv1, 0 };

void exit(int status)
{

    execve(argv0, argv, environ);

    // Exit if exevve failed
    printf("Exiting!\n");
    _exit(status);
}
