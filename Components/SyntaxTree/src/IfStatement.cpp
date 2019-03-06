#include "IfStatement.hpp"
#include <iostream>

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

void IfStatement::addElseIfClause(ElseIfStatement *clause)
{
    this->elseIfClauses.push_back(clause);
}

void IfStatement::addElseClause(ElseStatement *clause)
{
    this->elseStatement = clause;
}

std::string IfStatement::toCode() const
{
    std::string retVal;
    retVal = "if(" + this->condition + ")\n{";
    for(int i = 0; i < this->statementList.size(); i++)
    {
        std::string tempStr = this->statementList.at(i)->toCode();
        retVal += tempStr;
    }
    retVal += "\n}";
    if(this->elseIfClauses.size() > 0)
    {
        for(int i = 0; i < this->elseIfClauses.size(); i++)
        {
            retVal += this->elseIfClauses.at(i)->toCode();
        }
    }
    if(this->elseStatement != nullptr)
    {
        retVal += this->elseStatement->toCode();
    }
    return retVal;  
}