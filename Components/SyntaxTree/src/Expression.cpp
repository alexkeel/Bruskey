#include "Expression.hpp"
#include <iostream>

Expression::Expression(Expression *expression)
{
    this->expression = expression->toCode();
}

Expression::Expression()
{
    
}