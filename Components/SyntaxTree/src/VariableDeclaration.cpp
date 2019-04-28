#include "VariableDeclaration.hpp"
#include <iostream>
#include <cstring>
#include <string>

VariableDeclaration::VariableDeclaration(Identifier *type, Identifier *ident)
{
    this->statement = type->toCode() + " " + ident->toCode() + ";";
}

VariableDeclaration::VariableDeclaration(Identifier *type, Identifier *ident, Expression *assignment)
{
    this->statement = type->toCode() + " " + ident->toCode() + " = " + assignment->toCode() + ";";
}

VariableDeclaration::VariableDeclaration(Identifier *ident, Expression *assignment)
{
    this->setUpRegex();

    std::string tmp = assignment->toCode();

    // Execute regular expressions
    if(std::regex_search(tmp, intMatch, intRegex))
    {
        // Matched integer
        this->statement = "int " + ident->toCode() + " = " + assignment->toCode() + ";";
    }
    else if(std::regex_search(tmp, doubleMatch, doubleRegex))
    {
        // Matched double/float
        this->statement = "double " + ident->toCode() + " = " + assignment->toCode() + ";";
    }
    else if(std::regex_search(tmp, stringMatch, stringRegex))
    {
        // Matched string
        this->statement = "char* " + ident->toCode() + " = " + assignment->toCode() + ";";
    }
    else if(std::regex_search(tmp, charMatch, charRegex))
    {
        // Matched char
        this->statement = "char " + ident->toCode() + " = " + assignment->toCode() + ";";
    }
    else
    {
        this->statement = "UNKNOWN_TYPE";
    }
}

VariableDeclaration::~VariableDeclaration()
{

}

std::string VariableDeclaration::toCode() const
{
    return this->statement;
}

void VariableDeclaration::setUpRegex()
{
    intRegex = "^\\d+$";
    doubleRegex = "^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$";
    stringRegex = "\"[^\"]*\"";
    charRegex = "'[^']{1} *'";
}