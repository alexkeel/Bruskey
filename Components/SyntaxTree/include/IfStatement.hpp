#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

#include <Statement.hpp>
#include <string>
#include "Node.hpp"
#include "StatementList.hpp"
#include "ElseIfStatement.hpp"
#include "ElseStatement.hpp"

class IfStatement : public Statement
{
public:
    IfStatement(Expression *condition, StatementList *statements);
    IfStatement(Expression *condition);
    ~IfStatement();

    void addElseIfClause(ElseIfStatement *clause);
    void addElseClause(ElseStatement *clause);

    virtual std::string toCode() const; 

private:
    std::string condition;
    std::vector<ElseIfStatement *> elseIfClauses;
    ElseStatement *elseStatement;
};

#endif