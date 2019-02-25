#include "WhileStatement.hpp"
#include <iostream>

WhileStatement::WhileStatement(Expression *condition, StatementList *statements)
{
    this->condition = condition->toCode();

    if(statements != nullptr)
    {
        this->statementList = statements->getStatements();      
    }
    std::cout << "while";
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
    retVal = "    while(" + this->condition + ")\n    {\n";
    for(int i = 0; i < this->statementList.size(); i++)
    {
        retVal += this->statementList.at(i)->toCode();
    }
    retVal += "\n    }";
    return retVal;  
}