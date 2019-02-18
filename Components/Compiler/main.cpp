extern int yyparse();
extern int yylineno;
extern int yylex();

extern "C"
{
    void yyerror(const char *);
}

int main(int argc, char *argv)
{
    yyparse();
}