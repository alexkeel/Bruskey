#ifndef EXPRESSIONSTATEMENT_H
#define EXPRESSIONSTATEMENT_H

#include <Statement.hpp>
#include <string>

class ExpressionStatement : public Statement
{
public:
    ExpressionStatement(Expression *expression);
    ~ExpressionStatement();

    virtual std::string toCode() const;

private:
    std::string expression;    
};

#endif