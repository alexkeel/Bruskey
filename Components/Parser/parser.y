%{
#include "stdio.h"    
#include "stdlib.h"

int yylex(void);
extern char *yytext;
void yyerror(char const *);
%}

%token BUILTINTYPE IDENTIFIER KEYWORD CONSTANT OPERATOR FRACTIONALCONTANT EXPONENTPART FLOATINGSUFFIX INTEGERSUFFIX DECIMALCONSTANT OCTALCONSTANT HEXCONSTANT CHARCONSTANT STRINGLITERAL INVALID
%start input

%%

input:
BUILTINTYPE {printf(":(");}

%%

void yyerror(char const *x)
{
    printf("Error %s\n", x);
    exit(1);
}