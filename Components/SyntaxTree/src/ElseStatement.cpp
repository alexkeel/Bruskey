#include "ElseStatement.hpp"
#include <iostream>

ElseStatement::ElseStatement(StatementList *statements)
{
    if(statements != nullptr)
    {
        this->statementList = statements->getStatements();    
    }
}
 
ElseStatement::~ElseStatement()
{

}


std::string ElseStatement::toCode() const
{
    std::string retVal;
    retVal = "else\n{";
    for(int i = 0; i < this->statementList.size(); i++)
    {
        std::string tempStr = this->statementList.at(i)->toCode();
        retVal += tempStr;
    }
    retVal += "\n}";
    return retVal;  
}