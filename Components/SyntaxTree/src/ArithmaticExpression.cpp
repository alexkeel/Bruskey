#include "ArithmaticExpression.hpp"

ArithmaticExpression::ArithmaticExpression(Expression *lhs, Expression *op, Expression *rhs)
{
    if(op != nullptr)
    {
        expression = lhs->toCode() + op->toCode() + rhs->toCode();
    }    
}
