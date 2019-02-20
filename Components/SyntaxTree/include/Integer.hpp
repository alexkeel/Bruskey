#include "Node.hpp"
#include "string"

// Stores values identified as integers as a string value
class Integer : public Node
{
public:
    Integer(std::string value);

    virtual std::string toCode(){return value;}

private:
    std::string value;
}