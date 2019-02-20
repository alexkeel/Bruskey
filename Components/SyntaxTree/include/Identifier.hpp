#include "Node.hpp"
#include <string>

// Stores tokens identified as identifier as string
class Identifier : public Node
{
public:    
    Identifier(std::string value);
    
private:
    virtual std::string toCode(){return value;}
    std::string value;
}