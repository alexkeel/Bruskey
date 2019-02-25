%{
#include "stdio.h"    
#include "stdlib.h"
#include "Node.hpp"
#include "TranslationUnit.hpp"
#include "Statement.hpp"
#include "Integer.hpp"
#include "Identifier.hpp"
#include "FunctionCall.hpp"
#include "Expression.hpp"
#include "ArithmaticExpression.hpp"
#include "NotEqualsExpression.hpp"
#include "IfStatement.hpp"
#include "WhileStatement.hpp"
#include "StatementList.hpp"
#include <string>
#include <vector>

int yylex(void);
extern char *yytext;
TranslationUnit *base;
void yyerror(char const *);
%}

%union
{
    Node *node;
    TranslationUnit *tUnit;
    Statement *stmt;
    Expression *expr;
    Integer *integer;
    Identifier *ident;
    ArithmaticExpression *arithmaticExpression;
    IfStatement *ifStmt;
    WhileStatement *whileStmt;
    const std::string *string;
    std::vector<Expression *> *exprList;
    StatementList *stmtList;
}

%token EQUALITYOP AND DOT OR SUB ADD MINUS MUL DIV MOD INTCONST COMMA LEFTPAREN RIGHTPAREN END COLON LESSTHAN GREATERTHAN TRUE FALSE IF ELSE FUNCTIONSTATEMENT WHILE NOT BUILTINTYPE BUILTINFUNCTION IDENTIFIER EQUALS

// Terminals
%type <string> IDENTIFIER INTCONST ADD SUB DIV MUL MOD EQUALITYOP EQUALS 

// Non terminals
%type <stmt>      statement 
%type <integer>   constant 
%type <ident>     identifier multDivRemOp addSubOp eqalityOp equalsOp
%type <expr>      primaryExpression postfixExpression expression addSubExpression multDivRemExpression notEqualsExpression equalityExpression assignmentExpression
%type <exprList>  argumentExpressionList postfixExpression2 
%type <ifStmt>    ifStatement;
%type <whileStmt> whileStatement;
%type <stmtList>  statementList;

%start input

%%

input:
    statementList                                                           {base = new TranslationUnit($1);}
;

statementList:
    statement                                                               {$$ = new StatementList(); $$->addStatement($1);}
|   statementList statement                                                 {$$->addStatement($2);}    
;

// Statements

statement:
    ifStatement                                                             {$$ = $1;}
|   whileStatement                                                          {$$ = $1;}
;

ifStatement:
    IF expression COLON END                                                 {$$ = new IfStatement($2);}
|   IF expression COLON statementList END                                   {$$ = new IfStatement($2, $4);}
;

whileStatement:
    WHILE expression COLON END                                              {$$ = new WhileStatement($2);}
|   WHILE expression COLON statementList END                                {$$ = new WhileStatement($2, $4);}
;

// Expressions
expression:
    assignmentExpression                                                    {$$ = $1;}
;

assignmentExpression:
    equalityExpression                                                      {$$ = $1;}
|   equalityExpression equalsOp assignmentExpression                        {$$ = new ArithmaticExpression($1, $2, $3);}   
;

equalsOp:
    EQUALS                                                                  {$$ = new Identifier(yytext);}
    ;

equalityExpression:
    notEqualsExpression                                                     {$$ = $1;}
|   equalityExpression eqalityOp equalityExpression                         {$$ = new ArithmaticExpression($1, $2, $3);}    
;

eqalityOp:
    EQUALITYOP                                                              {$$ = new Identifier(yytext);}
;

notEqualsExpression:
    addSubExpression                                                        {$$ = $1;}
|   NOT multDivRemExpression                                                {$$ = new NotEqualsExpression($2);}    
;

addSubExpression:
    multDivRemExpression                                                    {$$ = $1;}
|   multDivRemExpression addSubOp addSubExpression                          {$$ = new ArithmaticExpression($1, $2, $3);}
;

addSubOp:
    ADD                                                                     {$$ = new Identifier(yytext);}
|   SUB                                                                     {$$ = new Identifier(yytext);}
;

multDivRemExpression:
    postfixExpression                                                       {$$ = $1;}
|   primaryExpression multDivRemOp multDivRemExpression                     {$$ = new ArithmaticExpression($1, $2, $3);}
;

multDivRemOp:
    MUL                                                                     {$$ = new Identifier(yytext);}
|   DIV                                                                     {$$ = new Identifier(yytext);}
|   MOD                                                                     {$$ = new Identifier(yytext);}
;    

postfixExpression:
    primaryExpression                                                       {$$ = $1;}
|   postfixExpression LEFTPAREN postfixExpression2                          {$$ = new FunctionCall($1, $3);}                            
|   postfixExpression LEFTPAREN expression RIGHTPAREN                       {$$ = new FunctionCall($1, $3);}    
;

postfixExpression2:
    RIGHTPAREN                                                              {$$ = new std::vector<Expression *>();}
|   argumentExpressionList RIGHTPAREN                                       {$$ = $1;}
;

argumentExpressionList:
    expression                                                              {$$ = new std::vector<Expression *>();}
|   argumentExpressionList COMMA expression                                 {$$->push_back($3);}
;

primaryExpression:
    identifier                                                              {$$ = $1;}
|   constant                                                                {$$ = $1;}
|   LEFTPAREN primaryExpression RIGHTPAREN                                  {$$ = $2;}
;

constant:
    INTCONST                                                                {$$ = new Integer(yytext);}
|   TRUE                                                                    {$$ = new Integer(yytext);}
|   FALSE                                                                   {$$ = new Integer(yytext);}
;

identifier:
    IDENTIFIER                                                              {$$ = new Identifier(yytext);}
;
%%

void yyerror(char const *x)
{
    printf("%s\n", x);
    exit(1);
}