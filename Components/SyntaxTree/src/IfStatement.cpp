#include "IfStatement.hpp"
#include <iostream>

IfStatement::IfStatement(Expression *condition, StatementList *statements)
{
    this->condition = condition->toCode();
    if(statements != nullptr)
    {
        this->statementList = statements->getStatements();    
    }
    std::cout << "if";
}

IfStatement::IfStatement(Expression *condition)
{
    this->condition = condition->toCode();
    std::cout << "if";
}
 
IfStatement::~IfStatement()
{

}


std::string IfStatement::toCode() const
{
    std::string retVal;
    retVal = "    if(" + this->condition + ")\n    {\n";
    for(int i = 0; i < this->statementList.size(); i++)
    {
        retVal += statementList.at(i)->toCode();
    }
    retVal += "\n    }";
    return retVal;  
}