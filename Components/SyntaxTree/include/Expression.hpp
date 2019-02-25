#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include "Node.hpp"

class Expression : public Node
{

public:
    Expression();
    Expression(Expression *expression);

    virtual std::string toCode() const {return expression;}

protected:
    std::string expression;
};

#endif