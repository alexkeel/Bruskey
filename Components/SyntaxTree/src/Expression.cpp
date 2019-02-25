#include "Expression.hpp"
#include <iostream>

Expression::Expression(Expression *expression)
{
    std::cout << "this is expression code: " + expression->toCode() << std::endl;
    this->expression = expression->toCode();
}

Expression::Expression()
{
    
}