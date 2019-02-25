#include "WhileStatement.hpp"

WhileStatement::WhileStatement(Expression *condition, std::vector<Statement *> *statements)
{
    this->condition = condition->toCode();
    if(statements != nullptr)
    {
        this->statementList = *statements;    
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
    retVal = "    while(" + this->condition + ")\n    {\n";
    for(int i = 0; i < this->statementList.size(); i++)
    {
        retVal += statementList.at(i)->toCode();
    }
    retVal += "\n    }";

    return retVal;  
}