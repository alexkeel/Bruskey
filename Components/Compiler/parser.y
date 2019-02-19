%{
#include "stdio.h"    
#include "stdlib.h"

int yylex(void);
extern char *yytext;
void yyerror(char const *);
%}

%token EQUALITYOP AND DOT OR SUB ADD MINUS MUL DIV MOD INTCONST COMMA LEFTPAREN RIGHTPAREN COLON LESSTHAN GREATERTHAN TRUE FALSE IF ELSE FUNCTIONSTATEMENT WHILE NOT BUILTINTYPE BUILTINFUNCTION IDENTIFIER EQUALS
%start input

%%

input:
    expression    {}
;

// Expressions
expression:
    assignmentExpression         {}
;

assignmentExpression:
    equalityExpression {}
|   equalityExpression EQUALS assignmentExpression {}   
;

equalityExpression:
    notEqualsExpression                               {}
|   notEqualsExpression EQUALITYOP equalityExpression {}    
;

notEqualsExpression:
    multDivRemExpression                        {}
|   NOT multDivRemExpression                    {}    
;

addSubExpression:
    multDivRemExpression                        {}
|   multDivRemExpression addSubOp addSubExpression  {}
;

addSubOp:
    ADD {}
|   SUB {}
;

multDivRemExpression:
    postfixExpression                                    {printf("umm");}
|   primaryExpression multDivRemOp multDivRemExpression  {printf("multdiv");}
;

multDivRemOp:
    MUL {}
|   DIV {}
|   MOD {}
;    

postfixExpression:
    primaryExpression                                   {printf("It should always get here");}
|   postfixExpression LEFTPAREN postfixExpression2      {printf("Argument");}
|   postfixExpression DOT expression                    {printf("Dot expression");}
|   postfixExpression LEFTPAREN expression RIGHTPAREN   {printf("EmptyParen");}    
;

postfixExpression2:
    RIGHTPAREN                          {}
|   argumentExpressionList RIGHTPAREN   {}
    ;

argumentExpressionList:
    expression                                {}
|   expression COMMA argumentExpressionList   { printf("expression list");}
    ;

primaryExpression:
    identifier                             { printf("Identifier");}
|   constant                               { printf("Constant");}
|   LEFTPAREN primaryExpression RIGHTPAREN { printf("Parens");}
    ;

constant:
    INTCONST        {$$ = $1;}
    ;

identifier:
    IDENTIFIER      {$$ = $1;}
    ;
%%

void yyerror(char const *x)
{
    printf("%s\n", x);
    exit(1);
}