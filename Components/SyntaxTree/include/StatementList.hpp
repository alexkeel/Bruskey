#ifndef STATEMENTLIST_H
#define STATEMENTLIST_H

#include "Statement.hpp"
#include <vector>

// Class to wrap a vector of statements
class StatementList
{
public:    
    StatementList(){};

    void addStatement(Statement *statement);
    std::vector<Statement *> getStatements();

private:
    std::vector<Statement *> statements;
};

#endif