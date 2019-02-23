#include "TranslationUnit.hpp"
#include <iostream>

extern int yyparse();
extern int yylineno;
extern int yylex();

extern TranslationUnit *base;

extern "C"
{
    void yyerror(const char *);
}

int main(int argc, char **argv)
{
    yyparse();

    std::cout << base->toCode() << std::endl; 
}