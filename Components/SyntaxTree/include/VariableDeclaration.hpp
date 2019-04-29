#ifndef VARIABLEDECLARATION_H
#define VARIABLEDECLARATION_H

#include "Node.hpp"
#include "Statement.hpp"
#include "Identifier.hpp"
#include <string>
#include <regex>
#include <vector>
#include <map>

class VariableDeclaration : public Statement
{
public:

    VariableDeclaration(Identifier *type, Identifier *ident);

    VariableDeclaration(Identifier *ident, Expression *assignment);

    VariableDeclaration(Identifier *type, Identifier *ident, Expression *assignment);

   ~VariableDeclaration();

    void setUpRegex();

    virtual std::string toCode() const;

private:
    std::string statement;

    static std::map<std::string, bool> definedVariables;

    // Regular expressions
    std::regex intRegex;
    std::regex doubleRegex;
    std::regex stringRegex;
    std::regex charRegex;

    // Match vars
    std::smatch intMatch;
    std::smatch doubleMatch;
    std::smatch stringMatch;
    std::smatch charMatch;
};

#endif