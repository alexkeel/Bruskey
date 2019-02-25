#ifndef FUNCTIONCALL_H
#define FUNCTIONCALL_H

#include <string>
#include <Expression.hpp>
#include <vector>

class FunctionCall : public Expression
{
public:

    FunctionCall(Expression *ident, Expression *argument);
    FunctionCall(Expression *ident, std::vector<Expression *> *arguments);
    FunctionCall(Expression *ident);

    ~FunctionCall(); 

private:
    virtual std::string toCode() const;
};

#endif