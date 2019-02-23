#include "Node.hpp"
#include "Expression.hpp"

#include <string>
#include <vector>

class Statement : public Node
{
public:
    Statement() = default;
    virtual ~Statement() = default;

    virtual std::string toCode() const = 0;

private:
    std::vector<Statement *> statementList;
}