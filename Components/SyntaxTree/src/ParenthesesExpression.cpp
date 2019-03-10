#include "ParenthesesExpression.hpp"

ParenthesesExpression::ParenthesesExpression(Expression *expression)
{
    this->expression = "(" + expression->toCode() + ")";
}

ParenthesesExpression::~ParenthesesExpression()
{

}

std::string ParenthesesExpression::toCode() const
{
    return this->expression;
}