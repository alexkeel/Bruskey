%option noyywrap
%{
#include <iostream>
#include "grammar.tab.h"
%}

alpha       [a-zA-Z]
numeric     [0-9]+
name        {alpha}([0-9]*{alhpa}*)+
whitespace  [\r\t\v\f]      
linefeed    \n

%%

{name}              {return NAME;}
{numeric}           {return NUMBER;}
"int"               {return INTTYPE;}
"string"            {return STRINGTYPE;}
":"                 {return COLON;}
"while"             {return WHILE;}
"true"              {return TRUE;}
"false"             {return FALSE;}
"\""                {return QUOTE;}
"("                 {return LEFTPAREN;}
")"                 {return RIGHTPAREN;}
"Robot"             {return ROBOT;}
"if"                {return IF;}
"while"             {return WHILE;}
"then"              {return THEN;}
"end"               {return END;}
">"                 {return GREATERTHAN;}
"<"                 {return LESSTHAN;}
\/\/[A-z0-9]        {std::cout << "comment" << std::endl;}
.                   {std::cout << "all other shit" << std::endl;}

