#include <Statement.hpp>
#include <string>
#include <vector>
#include "Node.hpp"

class IfStatement : public Statement
{
public:
    IfStatement(Expression *condition, std::vector<Statement *> *statements);
    IfStatement(Expression *condition);
    ~IfStatement();

private:
    virtual std::string toCode() const; 
    std::string condition;
};

