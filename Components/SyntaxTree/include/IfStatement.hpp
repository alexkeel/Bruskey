#include <Statement.hpp>
#include <string>
#include "Node.hpp"

class IfStatement : public Statement
{
public:
    IfStatement(Expression *condition);
    ~IfStatement();

private:
    virtual std::string toCode() const; 
    std::string condition;
};

