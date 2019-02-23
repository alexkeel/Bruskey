#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

// The base class for each AST Node
class Node
{
public:
    Node() = default;
    virtual ~Node() = default;

    virtual std::string toCode() const = 0;

private:
    std::vector<Node *> children;
};

#endif