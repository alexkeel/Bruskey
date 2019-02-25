#include "IfStatement.hpp"

IfStatement::IfStatement(Expression *condition, std::vector<Statement *> *statements)
{
    this->condition = condition->toCode();
    if(statements != nullptr)
    {
        this->statementList = *statements;    
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
    retVal = "    if(" + this->condition + ")\n    {\n";
    for(int i = 0; i < this->statementList.size(); i++)
    {
        retVal += statementList.at(i)->toCode();
    }
    retVal += "\n    }";

    return retVal;  
}