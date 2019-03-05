#ifndef ELSESTATEMENT_H
#define ELSESTATEMENT_H

#include "Statement.hpp"
#include "StatementList.hpp"
class ElseStatement : public Statement
{
public:
    ElseStatement(StatementList *statements);
    ElseStatement(){};
    ~ElseStatement();
    
    virtual std::string toCode() const; 

};

#endif