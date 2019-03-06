#include "ExpressionStatement.hpp"   
   
ExpressionStatement::ExpressionStatement(Expression *expression)
{
    this->expression = expression->toCode();
}

ExpressionStatement::~ExpressionStatement()
{

}

std::string ExpressionStatement::toCode() const
{
    return this->expression + ";";
}