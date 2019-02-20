#include <iostream>
#include <string>
#include "Node.hpp"

class Expression : public Node
{

public:
    virtual std::string toCode(){return expression;}

protected:
    std::string expression;
}