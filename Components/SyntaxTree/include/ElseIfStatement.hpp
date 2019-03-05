#ifndef ELSEIFSTATEMENT_H
#define ELSEIFSTATEMENT_H

#include <Statement.hpp>
#include <string>
#include "Node.hpp"
#include "StatementList.hpp"
#include "ElseStatement.hpp"

class ElseIfStatement : public Statement
{
public:
    ElseIfStatement(Expression *condition, StatementList *statements);
    ElseIfStatement(Expression *condition);
    ~ElseIfStatement();

    virtual std::string toCode() const; 

private:
    std::string condition;
};

#endif