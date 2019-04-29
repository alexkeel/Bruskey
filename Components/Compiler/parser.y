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
#include "BuiltInFunction.hpp"
#include "ElseStatement.hpp"
#include "ElseIfStatement.hpp"
#include "ExpressionStatement.hpp"
#include "ParenthesesExpression.hpp"
#include "VariableDeclaration.hpp"
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
    std::vector<ElseIfStatement *> *elseIfStmtList;
    StatementList *stmtList;
    BuiltInFunction *builtInFunc;
    ElseStatement *elseStmt;
    ElseIfStatement *elseIfStmt;
    ExpressionStatement *expStmt;
    VariableDeclaration *varDclr;
}

%token GREATERTHANOREQUAL LESSTHANOREQUAL EQUALITYOP AND DOT OR SUB ADD MINUS MUL DIV MOD INTCONST COMMA LEFTPAREN RIGHTPAREN END COLON LESSTHAN GREATERTHAN TRUE FALSE IF ELSE FUNCTIONSTATEMENT WHILE NOT BUILTINTYPE BUILTINFUNCTION IDENTIFIER EQUALS TYPE STRING FLOAT CHAR

// Terminals
%type <string> IDENTIFIER INTCONST ADD SUB DIV MUL MOD EQUALITYOP EQUALS STRING FLOAT CHAR

// Non terminals
%type <stmt>            statement 
%type <integer>         constant 
%type <ident>           identifier multDivRemOp addSubOp eqalityOp equalsOp builtInType builtInFunction lessMoreThanOp andOrOp type stringLiteral charValue floatingPoint
%type <expr>            primaryExpression postfixExpression expression addSubExpression multDivRemExpression notEqualsExpression equalityExpression assignmentExpression lessMoreThanExpression parenthesesExpression andOrExpression assignment
%type <exprList>        argumentExpressionList postfixExpression2 
%type <elseIfStmtList>  elseIfStatementList
%type <ifStmt>          ifStatement
%type <elseStmt>        elseStatement
%type <elseIfStmt>      elseIfStatement
%type <whileStmt>       whileStatement
%type <stmtList>        statementList
%type <builtInFunc>     builtInFunctionCall
%type <expStmt>         expressionStatement
%type <varDclr>         variableDeclaration

%start input

%%

input:
    statementList                                                               {base = new TranslationUnit($1);}
;

statementList:
    statement                                                                   {$$ = new StatementList(); $$->addStatement($1);}
|   statementList statement                                                     {$$->addStatement($2);}    
;

// Statements

statement:
    ifStatement                                                                 {$$ = $1;}
|   whileStatement                                                              {$$ = $1;}
|   expressionStatement                                                         {$$ = $1;}
|   variableDeclaration                                                         {$$ = $1;}
;

variableDeclaration:
    type identifier assignment                                                  {$$ = new VariableDeclaration($1, $2, $3);}
|   type identifier                                                             {$$ = new VariableDeclaration($1, $2);}
|   identifier assignment                                                       {$$ = new VariableDeclaration($1, $2);}
;

type:
    TYPE                                                                        {$$ = new Identifier(yytext);}
;

expressionStatement:
    expression                                                                  {$$ = new ExpressionStatement($1);}
;

ifStatement:
    IF expression COLON END                                                     {$$ = new IfStatement($2);}
|   IF expression COLON statementList END                                       {$$ = new IfStatement($2, $4);}
|   IF expression COLON elseIfStatementList END                                 {$$ = new IfStatement($2); for(int i = 0; i < $4->size(); i++){$$->addElseIfClause($4->at(i));}}
|   IF expression COLON statementList elseIfStatementList END                   {$$ = new IfStatement($2, $4); for(int i = 0; i < $5->size(); i++){$$->addElseIfClause($5->at(i));}}
|   IF expression COLON statementList elseIfStatementList elseStatement END     {$$ = new IfStatement($2, $4); $$->addElseClause($6); for(int i = 0; i < $5->size(); i++){$$->addElseIfClause($5->at(i));}}
|   IF expression COLON statementList elseStatement END                         {$$ = new IfStatement($2, $4); $$->addElseClause($5);}
|   IF expression COLON elseIfStatementList elseStatement END                   {$$ = new IfStatement($2); $$->addElseClause($5); for(int i = 0; i < $4->size(); i++){$$->addElseIfClause($4->at(i));}}
|   IF expression COLON elseStatement END                                       {$$ = new IfStatement($2); $$->addElseClause($4);}
;

elseStatement:                                                              
    ELSE COLON                                                                  {$$ = new ElseStatement();}
|   ELSE COLON statementList                                                    {$$ = new ElseStatement($3);}  
;

elseIfStatement:                                                              
    ELSE IF expression COLON                                                    {$$ = new ElseIfStatement($3);}
|   ELSE IF expression COLON statementList                                      {$$ = new ElseIfStatement($3, $5);}  
;  

elseIfStatementList:
    elseIfStatement                                                             {$$ = new std::vector<ElseIfStatement *>(); $$->push_back($1);}
|   elseIfStatementList elseIfStatement                                         {$$->push_back($2);}
;

whileStatement:
    WHILE expression COLON END                                                  {$$ = new WhileStatement($2);}
|   WHILE expression COLON statementList END                                    {$$ = new WhileStatement($2, $4);}
;

// Expressions
expression: 
    assignmentExpression                                                        {$$ = $1;}
|   parenthesesExpression                                                       {$$ = $1;}
;

assignment:
    EQUALS constant                                                             {$$ = $2;}
|   EQUALS stringLiteral                                                        {$$ = $2;} 
|   EQUALS charValue                                                            {$$ = $2;} 
|   EQUALS floatingPoint                                                        {$$ = $2;} 
;

builtInFunctionCall:
    builtInType DOT builtInFunction LEFTPAREN RIGHTPAREN                        {$$ = new BuiltInFunction($3);} 
|   builtInType DOT builtInFunction LEFTPAREN argumentExpressionList RIGHTPAREN {$$ = new BuiltInFunction($3, $5);}
;

builtInType:
    BUILTINTYPE                                                                 {$$ = new Identifier(yytext);}
;

builtInFunction:
    BUILTINFUNCTION                                                             {$$ = new Identifier(yytext);}
;

parenthesesExpression:                                                
    LEFTPAREN expression RIGHTPAREN                                             {$$ = new ParenthesesExpression($2);}
;    

assignmentExpression:
    equalityExpression                                                          {$$ = $1;}
|   assignmentExpression equalsOp assignmentExpression                          {$$ = new ArithmaticExpression($1, $2, $3);}   
;

equalsOp:
    EQUALS                                                                      {$$ = new Identifier(yytext);}
;

equalityExpression:
    notEqualsExpression                                                         {$$ = $1;}
|   equalityExpression eqalityOp equalityExpression                             {$$ = new ArithmaticExpression($1, $2, $3);}    
;

eqalityOp:
    EQUALITYOP                                                                  {$$ = new Identifier("==");}
;

notEqualsExpression:
    lessMoreThanExpression                                                      {$$ = $1;}
|   NOT expression                                                              {$$ = new NotEqualsExpression($2);}   
;

lessMoreThanExpression:
    andOrExpression                                                             {$$ = $1;}
|   expression lessMoreThanOp expression                                        {$$ = new ArithmaticExpression($1, $2, $3);}
;

lessMoreThanOp:
    LESSTHAN                                                                    {$$ = new Identifier(yytext);}
|   GREATERTHAN                                                                 {$$ = new Identifier(yytext);}
|   GREATERTHANOREQUAL                                                          {$$ = new Identifier(yytext);}
|   LESSTHANOREQUAL                                                             {$$ = new Identifier(yytext);}
;

andOrExpression:
    addSubExpression                                                            {$$ = $1;}
|   expression andOrOp expression                                               {$$ = new ArithmaticExpression($1, $2, $3);}
;

andOrOp:
    AND                                                                         {$$ = new Identifier("&&");}
|   OR                                                                          {$$ = new Identifier("||");}    
;

addSubExpression:
    multDivRemExpression                                                        {$$ = $1;}
|   multDivRemExpression addSubOp addSubExpression                              {$$ = new ArithmaticExpression($1, $2, $3);}
;

addSubOp:
    ADD                                                                         {$$ = new Identifier(yytext);}
|   SUB                                                                         {$$ = new Identifier(yytext);}
;

multDivRemExpression:
    postfixExpression                                                           {$$ = $1;}
|   primaryExpression multDivRemOp multDivRemExpression                         {$$ = new ArithmaticExpression($1, $2, $3);}
;

multDivRemOp:
    MUL                                                                         {$$ = new Identifier(yytext);}
|   DIV                                                                         {$$ = new Identifier(yytext);}
|   MOD                                                                         {$$ = new Identifier(yytext);}
;    

postfixExpression:
    primaryExpression                                                           {$$ = $1;}
|   postfixExpression LEFTPAREN postfixExpression2                              {$$ = new FunctionCall($1, $3);}                            
|   postfixExpression LEFTPAREN expression RIGHTPAREN                           {$$ = new FunctionCall($1, $3);}    
;

postfixExpression2:
    RIGHTPAREN                                                                  {$$ = new std::vector<Expression *>();}
|   argumentExpressionList RIGHTPAREN                                           {$$ = $1;}
;

argumentExpressionList:
    expression                                                                  {$$ = new std::vector<Expression *>(); $$->push_back($1);}
|   argumentExpressionList COMMA expression                                     {$$->push_back($3);}
;

primaryExpression:
    builtInFunctionCall                                                         {$$ = $1;}
|   identifier                                                                  {$$ = $1;}
|   constant                                                                    {$$ = $1;}
|   charValue                                                                   {$$ = $1;}
|   floatingPoint                                                               {$$ = $1;}
|   stringLiteral                                                               {$$ = $1;}
|   LEFTPAREN primaryExpression RIGHTPAREN                                      {$$ = $2;}
;

charValue:
    CHAR                                                                        {$$ = new Identifier(yytext);}
;

floatingPoint:
    FLOAT                                                                       {$$ = new Identifier(yytext);}
;

stringLiteral:
    STRING                                                                      {$$ = new Identifier(yytext);}
;

constant:
    INTCONST                                                                    {$$ = new Integer(yytext);}
|   TRUE                                                                        {$$ = new Integer(yytext);}
|   FALSE                                                                       {$$ = new Integer(yytext);}
;

identifier:
    IDENTIFIER                                                                  {$$ = new Identifier(yytext);}
;
%%

void yyerror(char const *x)
{
    printf("%s\n", x);
    exit(1);
}