#ifndef NOTEQUALSEXPRESSION_H
#define NOTEQUALSEXPRESSION_H

#include "Expression.hpp"
#include <string>

class NotEqualsExpression : public Expression 
{
public:

    NotEqualsExpression(Expression *expression);
    ~NotEqualsExpression();

    virtual std::string toCode() const;

};

#endif