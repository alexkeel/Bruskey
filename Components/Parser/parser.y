%{
#include "stdio.h"    
#include "stdlib.h"

int yylex(void);
extern char *yytext;
void yyerror(char const *);
%}

%token INTCONST COMMA LEFTPAREN RIGHTPAREN COLON LESSTHAN GREATERTHAN TRUE FALSE IF ELSE FUNCTIONSTATEMENT WHILE NOT BUILTINTYPE BUILTINFUNCTION IDENTIFIER EQUALS
%start input

%%

input:


// Expressions



constant:
    INTCONST        {$$ = $1}
    ;

identifier :
    IDENTIFIER      {$$ = $1}
    ;
%%

void yyerror(char const *x)
{
    printf("=%s\n", x);
    exit(1);
}