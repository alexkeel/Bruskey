#include "Expression.hpp"
#include <iostream>
#include <string>

class ArithmaticExpression : public Expression
{
public:
    ArithmaticExpression(Expression *lhs, std::string op, Expression *rhs);
}