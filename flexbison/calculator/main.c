#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s)
{
    printf("Error: %s\n", s);
}

int main(int argc, char **argv)
{
    const char *fname;
    FILE *fp;

    /*if (argc != 2) {
        return 1;
    }

    fname = argv[1];
    fp = fopen(fname, "r");
    if (fp == NULL) {
        return 1;
    }*/

    yylex();

    return 0;
}

