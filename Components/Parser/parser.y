%{
#include "stdio.h"    
#include "stdlib.h"

int yylex(void);
extern char *yytext;
void yyerror(char const *);
%}

%token AND DOT OR SUB ADD MINUS MUL DIV MOD INTCONST COMMA LEFTPAREN RIGHTPAREN COLON LESSTHAN GREATERTHAN TRUE FALSE IF ELSE FUNCTIONSTATEMENT WHILE NOT BUILTINTYPE BUILTINFUNCTION IDENTIFIER EQUALS
%start input

%%

input:
    addSubExpression    {printf("works");};   
;

// Expressions
expression:
addSubExpression {}

addSubExpression:
    multDivRemExpression                        {}
|   addSubExpression addSubOp addSubExpression  {}
;

addSubOp:
    ADD {}
|   SUB {}
;

multDivRemExpression:
    unaryExpression                                         {}
|   multDivRemExpression multDivRemOp multDivRemExpression  {}
;

multDivRemOp:
    MUL {}
|   DIV {}
|   MOD {}
;    


unaryExpression:
    postfixExpression                   {}
|   unaryOperator postfixExpression     {}    
;

unaryOperator:
    AND     {}
|   OR      {}
|   NOT     {}
;

postfixExpression:
    primaryExpression                                   {}
|   postfixExpression LEFTPAREN postfixExpression2      {}
|   postfixExpression DOT expression                    {}
|   postfixExpression LEFTPAREN expression RIGHTPAREN   {}    
;

postfixExpression2:
    RIGHTPAREN                          {}
|   argumentExpressionList RIGHTPAREN   {}
    ;

argumentExpressionList:
    expression                                {}
|   expression COMMA argumentExpressionList   {}
    ;

primaryExpression:
    identifier                             {}
|   constant                               {}
|   LEFTPAREN primaryExpression RIGHTPAREN {}
    ;

constant:
    INTCONST        {$$ = $1;}
    ;

identifier :
    IDENTIFIER      {$$ = $1;}
    ;
%%

void yyerror(char const *x)
{
    printf("%s\n", x);
    exit(1);
}