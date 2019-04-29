#include "VariableDeclaration.hpp"
#include <iostream>
#include <cstring>
#include <string>

// Static member
std::map<std::string, bool> VariableDeclaration::definedVariables;

VariableDeclaration::VariableDeclaration(Identifier *type, Identifier *ident)
{
    this->statement = type->toCode() + " " + ident->toCode() + ";";
    // Add new variable to map if it doesnt exist, otherwise do nothing as it is a redefined variable
    if(definedVariables.find(ident->toCode()) == definedVariables.end())
    {
        // The variable does not exist, add to map
        definedVariables.insert(std::pair<std::string, bool>(ident->toCode(), true));
    }  
}

VariableDeclaration::VariableDeclaration(Identifier *type, Identifier *ident, Expression *assignment)
{
    this->statement = type->toCode() + " " + ident->toCode() + " = " + assignment->toCode() + ";";
    // Add new variable to map if it doesnt exist, otherwise do nothing as it is a redefined variable
    if(definedVariables.find(ident->toCode()) == definedVariables.end())
    {
        // The variable does not exist, add to map
        definedVariables.insert(std::pair<std::string, bool>(ident->toCode(), true));
        std::cout << definedVariables.count("x");
    }  
}

VariableDeclaration::VariableDeclaration(Identifier *ident, Expression *assignment)
{
    // If the variable is already defined, don't bother with dynamically allocating a type
    // Add new variable to map if it doesnt exist, otherwise do nothing as it is a redefined variable
    if(definedVariables.count(ident->toCode()) > 0)
    {
        // The variable already exists, no type definition needed
        this->statement = ident->toCode() + " = " + assignment->toCode() + ";";
    } 
    else
    {
        this->setUpRegex();

        std::string tmp = assignment->toCode();

        // The variable doesn't exist, define a type and add to map
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

        // The variable does not exist, add to map
        definedVariables.insert(std::pair<std::string, bool>(ident->toCode(), true));
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
    charRegex = "'[^'].*'";
}