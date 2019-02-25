#ifndef INTEGER_H
#define INTEGER_H

#include "Expression.hpp"
#include <string>

// Stores values identified as integers as a string value
class Integer : public Expression
{
public:
    Integer(const std::string &value);
    ~Integer();

    virtual std::string toCode() const {return this->expression;}

private:

};

#endif