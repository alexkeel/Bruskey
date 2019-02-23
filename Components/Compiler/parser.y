%{
#include "stdio.h"    
#include "stdlib.h"
#include "Node.hpp"
#include "TranslationUnit.hpp"
#include "Statement.hpp"
#include "Integer.hpp"
#include "Identifier.hpp"
#include <string>

int yylex(void);
extern char *yytext;
TranslationUnit *base;
std::vector<Statement *> statementList;
void yyerror(char const *);
%}

%union
{
    Node *node;
    TranslationUnit *tUnit;
    Statement *stmt;
    Expression *expression;
    Integer *integer;
    Identifier *ident;
    std::string *string;
}

%token EQUALITYOP AND DOT OR SUB ADD MINUS MUL DIV MOD INTCONST COMMA LEFTPAREN RIGHTPAREN COLON LESSTHAN GREATERTHAN TRUE FALSE IF ELSE FUNCTIONSTATEMENT WHILE NOT BUILTINTYPE BUILTINFUNCTION IDENTIFIER EQUALS

// Terminals
%type <string> IDENTIFIER INTCONST

// Non terminals
%type <stmt> statement
%type <integer> constant 
%type <ident>  identifier

%start input

%%

input:
    statementList {base = new TranslationUnit(statementList);}
;

statementList:
    statement               {statementList.push_back($1);}
|   statementList statement {statementList.push_back($2);}    
;

// Statements

statement:
    expression {}
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
    INTCONST        {$$ = new Integer($1);}
    ;

identifier:
    IDENTIFIER      {$$ = new Identifier($1);}
    ;
%%

void yyerror(char const *x)
{
    printf("%s\n", x);
    exit(1);
}