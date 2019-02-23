#ifndef INTEGER_H
#define INTEGER_H

#include "Node.hpp"
#include "string"

// Stores values identified as integers as a string value
class Integer : public Node
{
public:
    Integer(std::string* value);
    ~Integer();

    virtual std::string toCode() const {return value;}

private:
    std::string value;
};

#endif