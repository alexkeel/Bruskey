#include "IfStatement.hpp"

IfStatement::IfStatement(Expression *condition)
{
    this->condition = condition->toCode();
}
 
IfStatement::~IfStatement()
{

}


std::string IfStatement::toCode() const
{
    return "    if(" + this->condition + ")\n    {\n    }";
}