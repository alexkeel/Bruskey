#include <Expression.hpp>
#include <Identifier.hpp>
#include <string>
#include <vector>

class BuiltInFunction : public Expression
{
public:
    BuiltInFunction(Identifier *functionName, std::vector<Expression *> *argumentList);
    BuiltInFunction(Identifier *functionName);

    virtual std::string toCode() const;
private:
    std::vector<Expression *> *argumentList;    
};