#ifndef WHILESTATEMENT_H
#define WHILESTATEMENT_H

#include <Statement.hpp>
#include <string>
#include "Node.hpp"
#include "StatementList.hpp"

class WhileStatement : public Statement
{
public:
    WhileStatement(Expression *condition, StatementList *statements);
    WhileStatement(Expression *condition);
    ~WhileStatement();

private:
    virtual std::string toCode() const; 
    std::string condition;
};

#endif