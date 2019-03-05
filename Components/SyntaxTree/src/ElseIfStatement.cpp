#include "ElseIfStatement.hpp"
#include <iostream>

ElseIfStatement::ElseIfStatement(Expression *condition, StatementList *statements)
{
    this->condition = condition->toCode();
    if(statements != nullptr)
    {
        this->statementList = statements->getStatements();    
    }
}

ElseIfStatement::ElseIfStatement(Expression *condition)
{
    this->condition = condition->toCode();
}
 
ElseIfStatement::~ElseIfStatement()
{

}


std::string ElseIfStatement::toCode() const
{
    std::string retVal;
    retVal = "else if(" + this->condition + ")\n{";
    for(int i = 0; i < this->statementList.size(); i++)
    {
        std::string tempStr = this->statementList.at(i)->toCode();
        retVal += tempStr;
    }
    retVal += "\n}";

    return retVal;  
}