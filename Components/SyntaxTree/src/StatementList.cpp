#include "StatementList.hpp"

void StatementList::addStatement(Statement *statement)
{
    if(statement != nullptr)
    {
        this->statements.push_back(statement);        
    }    
}

std::vector<Statement *> StatementList::getStatements()
{
    return this->statements;
}