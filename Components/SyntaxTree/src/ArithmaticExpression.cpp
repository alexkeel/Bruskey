#include "ArithmaticExpression.hpp"

ArithmaticExpression::ArithmaticExpression(Expression *lhs, std::string op, Expression *rhs)
{
    expression = lhs->toCode() + op + rhs->toCode();
}
