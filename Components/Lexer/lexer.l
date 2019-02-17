%option noyywrap
%{
#include <iostream>
#include "stdio.h"
#include "parser.tab.h"

int lineCount = 1;
int spaceCount = 1;
int sourceLineCount = 1;
int charLength = 1;
%}

BuiltInType Robot

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

{BuiltInType} {
    return BUILTINTYPE;
}

{Keyword} {
    return KEYWORD;
}

{Identifier} {
    return IDENTIFIER;
}

{Operator} {
    return OPERATOR;
}

{FractionalConstant}{ExponentPart}?{FloatingSuffix}? {
    return CONSTANT;
}

([0-9]+){ExponentPart}{FloatingSuffix}? {
    return CONSTANT;
}

{HexConstant}{IntegerSuffix}? {
    return CONSTANT;
}

{DecimalConstant}{IntegerSuffix}? {
    return CONSTANT;
}

{OctalConstant}{IntegerSuffix}? {
    return CONSTANT;
}

{CharConstant} {
    return CONSTANT;
}

{StringLiteral} {
    return STRINGLITERAL;
}

{NewLine} {
    spaceCount = 1;
    lineCount++;
    sourceLineCount++;
}

{WhiteSpace} {
    spaceCount++;
}

{Tab} {
    spaceCount += 8;
}

{All} {
    return INVALID;
}

%%