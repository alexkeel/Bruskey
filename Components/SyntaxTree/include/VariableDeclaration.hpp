#ifndef VARIABLEDECLARATION_H
#define VARIABLEDECLARATION_H

#include "Node.hpp"
#include "Statement.hpp"
#include "Identifier.hpp"
#include <string>
#include <vector>

class VariableDeclaration : public Statement
{
public:
    VariableDeclaration(Identifier *type, Identifier *ident);

    VariableDeclaration(Identifier *type, Identifier *ident, Expression *assignment);

   ~VariableDeclaration();

    virtual std::string toCode() const;

private:
    std::string statement;
};

#endif