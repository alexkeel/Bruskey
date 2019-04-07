#include "FunctionCall.hpp"

FunctionCall::FunctionCall(Expression *ident, Expression *argument)
{
    this->expression = ident->toCode() + "(" + argument->toCode() + ")";
}

FunctionCall::FunctionCall(Expression *ident, std::vector<Expression *> *arguments)
{
    this->expression = ident->toCode();
    this->expression += "(";
    for(int i = 0; i < arguments->size(); i++)
    {
        if(i == arguments->size() - 1)
        {
            this->expression += (arguments->at(i)->toCode()); 
        }
        else
        {
            this->expression += (arguments->at(i)->toCode() + ","); 
        }                
    }
    this->expression += ")";

}

FunctionCall::FunctionCall(Expression *ident)
{
    this->expression = ident->toCode() + "()";
}

FunctionCall::~FunctionCall()
{

}