%option noyywrap
%{
#include "stdio.h"    
#include "stdlib.h"
#include "Node.hpp"
#include "TranslationUnit.hpp"
#include "Statement.hpp"
#include "Integer.hpp"
#include "Identifier.hpp"
#include <string>
#include "parser.tab.hpp"

int lineCount = 1;
int spaceCount = 1;
int sourceLineCount = 1;
int charLength = 1;
%}

BuiltInType Robot

BuiltInFunction ObstacleDetected|Stop|BlobVisible|SpinLeft|SpinRight|DriveForward|DriveBackward

Keyword auto|double|int|struct|break|else|long|switch|case|enum|register|typedef|char|extern|return|union|const|float|short|unsigned|continue|for|signed|void|default|goto|sizeof|volatile|do|if|static|while

Identifier [_a-zA-Z][_a-zA-Z0-9]*

Operator [.][.][.]|[<>][<>][=]|[-][-]|[+][+]|[|][|]|[#][#]|[&][&]|[+\-*\/<>=!%^|&][=]|[<][<]|[->][>]|[<>&=+\/\-*(){}\[\]\.,%~!?:|^;]

FractionalConstant (([0-9]*\.[0-9]+)|([0-9]+\.))
ExponentPart ([eE][+-]?[0-9]+)

FloatingSuffix ([flFL])
IntegerSuffix ([uU][lL]|[lL][uU]|[uUlL])

DecimalConstant ([1-9][0-9]*)
OctalConstant ([0][0-7]*)
HexConstant ([0][xX][0-9A-Fa-f]+)

CharConstant ('(([\\]['])|([^']))+')

StringLiteral ["](([\\]["])|([^"]))*["]

NewLine (\r\n?|\n)

WhiteSpace [ ]

Tab \t

All .

%%

[+]                 {return ADD;}
[-]                 {return MINUS;}
[\*]                {return MUL;}
[\/]                {return DIV;}
[%]                 {return MOD;}
[,]                 {return COMMA;}
[(]                 {return LEFTPAREN;}
[)]                 {return RIGHTPAREN;}
[:]                 {return COLON;}
[<]                 {return LESSTHAN;}
[>]                 {return GREATERTHAN;}
[.]                 {return DOT;}
[==]                {return EQUALITYOP;}
true                {return TRUE;}
false               {return FALSE;}

if                  {return IF;}
equals              {return EQUALS;}
else                {return ELSE;}
function            {return FUNCTIONSTATEMENT;}
while               {return WHILE;}
not                 {return NOT;}
and                 {return AND;}
or                  {return OR;}

{BuiltInType}       {return BUILTINTYPE;}
{BuiltInFunction}   {return BUILTINFUNCTION;}

{Identifier}        {return IDENTIFIER;}

({HexConstant}|{OctalConstant}|{DecimalConstant}){IntegerSuffix}?   {return INTCONST;}

{WhiteSpace}        {;}
{Tab}               {;}
{All}               {;}


%%