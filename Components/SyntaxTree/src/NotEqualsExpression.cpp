#include "NotEqualsExpression.hpp"

NotEqualsExpression::NotEqualsExpression(Expression *expression)
{
    this->expression = "!" + expression->toCode();
}

NotEqualsExpression::~NotEqualsExpression()
{

}

std::string NotEqualsExpression::toCode() const
{
    return this->expression;
}