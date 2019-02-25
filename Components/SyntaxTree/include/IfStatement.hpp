#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

#include <Statement.hpp>
#include <string>
#include "Node.hpp"
#include "StatementList.hpp"

class IfStatement : public Statement
{
public:
    IfStatement(Expression *condition, StatementList *statements);
    IfStatement(Expression *condition);
    ~IfStatement();

private:
    virtual std::string toCode() const; 
    std::string condition;
};

#endif