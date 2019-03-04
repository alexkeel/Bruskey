#include "IfStatement.hpp"
#include <iostream>
#include "Common.hpp"

IfStatement::IfStatement(Expression *condition, StatementList *statements)
{
    this->condition = condition->toCode();
    if(statements != nullptr)
    {
        this->statementList = statements->getStatements();    
    }
}

IfStatement::IfStatement(Expression *condition)
{
    this->condition = condition->toCode();
}
 
IfStatement::~IfStatement()
{

}


std::string IfStatement::toCode() const
{
    std::string retVal;
    retVal = "    if(" + this->condition + ")\n    {";
    for(int i = 0; i < this->statementList.size(); i++)
    {
        std::string tempStr = this->statementList.at(i)->toCode();
        tempStr = Common::indentString(tempStr);
        retVal += tempStr;
    }
    retVal += "\n    }";
    return retVal;  
}