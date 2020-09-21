%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

%}

%token PLUS   "+"
%token MINUS  "-"
%token MULT   "*"
%token DIV    "/"
%token NUMBER "number"
%token END    "end"
%token NEWLINE "newline"

%%

input:
  /* input */
| expression { printf("%d\n", $1); }
;

expression:
  NUMBER                      { $$ = $1; printf("$$ = %d\n", $1);     }
| expression PLUS expression  { $$ = $1 + $2;  printf("$$ = %d\n", $1); }
| expression MINUS expression { $$ = $1 - $2;  printf("$$ = %d\n", $1); }
| expression MULT expression  { $$ = $1 * $2;  printf("$$ = %d\n", $1); }
| expression DIV expression   { $$ = $1 / $2;  printf("$$ = %d\n", $1); }
;

%%

