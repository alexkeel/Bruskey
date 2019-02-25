#include <Statement.hpp>
#include <string>
#include <vector>
#include "Node.hpp"

class WhileStatement : public Statement
{
public:
    WhileStatement(Expression *condition, std::vector<Statement *> *statements);
    WhileStatement(Expression *condition);
    ~WhileStatement();

private:
    virtual std::string toCode() const; 
    std::string condition;
};

