#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "Expression.hpp"
#include <string>

// Stores tokens identified as identifier as string
class Identifier : public Expression
{
public:    
    Identifier(const std::string &value);
    ~Identifier();
    
private:
    virtual std::string toCode() const {return this->expression;}
};

#endif