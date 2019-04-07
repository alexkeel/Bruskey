#include "VariableDeclaration.hpp"
#include <iostream>

VariableDeclaration::VariableDeclaration(Identifier *type, Identifier *ident)
{
    this->statement = type->toCode() + " " + ident->toCode() + ";";
}

VariableDeclaration::VariableDeclaration(Identifier *type, Identifier *ident, Expression *assignment)
{
    this->statement = type->toCode() + " " + ident->toCode() + " = " + assignment->toCode() + ";";
}

VariableDeclaration::~VariableDeclaration()
{

}

std::string VariableDeclaration::toCode() const
{
    return this->statement;
}