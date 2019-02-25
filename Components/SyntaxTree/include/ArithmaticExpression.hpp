#ifndef ARITHMATICEXPRESSION_H
#define ARITHMATICEXPRESSION_H

#include "Expression.hpp"
#include <iostream>
#include <string>

class ArithmaticExpression : public Expression
{
public:
    ArithmaticExpression(Expression *lhs, Expression *op, Expression *rhs);
};

#endif