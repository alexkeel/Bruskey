#ifndef PARENTHESESEXPRESSION_H
#define PARENTHESESEXPRESSION_H

#include <Expression.hpp>

class ParenthesesExpression : public Expression
{
public:

    ParenthesesExpression(Expression *expression);
    ~ParenthesesExpression();

    virtual std::string toCode() const;

};

#endif