#ifndef TRANSLATIONUNIT_H
#define TRANSLATIONUNIT_H

#include "Node.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include "StatementList.hpp"

#include <string>
#include <vector>

class TranslationUnit : public Node
{
public:
    TranslationUnit(StatementList *statementList);
    ~TranslationUnit(){};

    virtual std::string toCode() const;

private:
    std::vector<Statement *> statementList;    
    std::string code;
};

#endif