#include "WhileStatement.hpp"
#include "Common.hpp"
#include <iostream>

WhileStatement::WhileStatement(Expression *condition, StatementList *statements)
{
    this->condition = condition->toCode();

    if(statements != nullptr)
    {
        this->statementList = statements->getStatements();      
    }
}

WhileStatement::WhileStatement(Expression *condition)
{
    this->condition = condition->toCode();
}
 
WhileStatement::~WhileStatement()
{

}


std::string WhileStatement::toCode() const
{
    std::string retVal;
    retVal = "    while(" + this->condition + ")\n    {";
    for(int i = 0; i < this->statementList.size(); i++)
    {
        std::string tempStr = this->statementList.at(i)->toCode();
        tempStr = Common::indentString(tempStr);
        retVal += tempStr;
    }
    retVal += "\n    }";
    return retVal;  
}