#include <Expression.hpp>
#include <Identifier.hpp>
#include <string>
#include <vector>

class BuiltInFunction : public Expression
{
public:
    BuiltInFunction(Identifier *functionName, std::vector<Expression *> *argumentList);
    BuiltInFunction(Identifier *functionName);
    ~BuiltInFunction(){}

private:
    std::vector<Expression *> *argumentList;    
};