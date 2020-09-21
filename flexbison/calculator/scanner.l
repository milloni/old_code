%option noyywrap

%{

#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"

%}

DIGIT   [0-9]
NUMBER  {DIGIT}*

%%

{NUMBER}  { yylval = atoi(yytext); return NUMBER;   }
"+"       { return PLUS;                            }
"-"       { return MINUS;                           }
"*"       { return MULT;                            }
"/"       { return DIV;                             }
"\n"      { return NEWLINE;                         }
[ \t]   /* skip whitespace */
.         { printf("Unknown token: %s\n", yytext); 
            exit(1);                               }

%%

