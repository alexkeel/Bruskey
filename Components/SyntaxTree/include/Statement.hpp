#ifndef STATEMENT_H
#define STATEMENT_H

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

protected:
    std::vector<Statement *> statementList;
};

#endif