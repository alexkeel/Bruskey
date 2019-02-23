#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "Node.hpp"
#include <string>

// Stores tokens identified as identifier as string
class Identifier : public Node
{
public:    
    Identifier(std::string *value);
    ~Identifier();
    
private:
    virtual std::string toCode() const {return *value;}
    std::string *value;
};

#endif