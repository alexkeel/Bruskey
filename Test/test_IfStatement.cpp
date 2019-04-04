#include "catch.hpp"
#include "IfStatement.hpp"
#include "ElseIfStatement.hpp"
#include "ElseStatement.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "Expression.hpp"
#include "ArithmaticExpression.hpp"
#include "StatementList.hpp"
#include "ExpressionStatement.hpp"
#include <vector>

TEST_CASE("Test If Statement")
{
    SECTION("If Statement without a body")
    {
        Integer *lhs = new Integer("5");
        Identifier *op = new Identifier(">");
        Integer *rhs = new Integer("4");

        ArithmaticExpression *condition = new ArithmaticExpression(lhs, op, rhs);
        IfStatement *ifStatement = new IfStatement(condition);
        REQUIRE(ifStatement->toCode() == "if(5>4)\n{\n}");
    }

    SECTION("If Statement with a body")
    {
        Integer *lhs = new Integer("5");
        Identifier *op = new Identifier(">");
        Integer *rhs = new Integer("4");
    
        ArithmaticExpression *condition = new ArithmaticExpression(lhs, op, rhs);
        ExpressionStatement *body = new ExpressionStatement(condition);
        StatementList *list = new StatementList();
        list->addStatement(body);

        IfStatement *ifStatement = new IfStatement(condition, list);
        REQUIRE(ifStatement->toCode() == "if(5>4)\n{5>4;\n}");
    }

    SECTION("If Statement with else if clauses")
    {
        Integer *lhs = new Integer("5");
        Identifier *op = new Identifier(">");
        Integer *rhs = new Integer("4");
    
        ArithmaticExpression *condition = new ArithmaticExpression(lhs, op, rhs);
        ExpressionStatement *body = new ExpressionStatement(condition);
        StatementList *list = new StatementList();
        list->addStatement(body);

        ElseIfStatement *elseIf = new ElseIfStatement(condition);

        IfStatement *ifStatement = new IfStatement(condition, list);
        ifStatement->addElseIfClause(elseIf);
        REQUIRE(ifStatement->toCode() == "if(5>4)\n{5>4;\n}else if(5>4)\n{\n}");

        ifStatement->addElseIfClause(elseIf);
        REQUIRE(ifStatement->toCode() == "if(5>4)\n{5>4;\n}else if(5>4)\n{\n}else if(5>4)\n{\n}");

        ifStatement->addElseIfClause(elseIf);
        REQUIRE(ifStatement->toCode() == "if(5>4)\n{5>4;\n}else if(5>4)\n{\n}else if(5>4)\n{\n}else if(5>4)\n{\n}");        

        ElseIfStatement *elseIfWithBody = new ElseIfStatement(condition, list);
        ifStatement = new IfStatement(condition, list);
        ifStatement->addElseIfClause(elseIfWithBody);
        REQUIRE(ifStatement->toCode() == "if(5>4)\n{5>4;\n}else if(5>4)\n{5>4;\n}");        
    }

    SECTION("If statements with else clause")
    {
        Integer *lhs = new Integer("5");
        Identifier *op = new Identifier(">");
        Integer *rhs = new Integer("4");
    
        ArithmaticExpression *condition = new ArithmaticExpression(lhs, op, rhs);
        ExpressionStatement *body = new ExpressionStatement(condition);
        StatementList *list = new StatementList();
        list->addStatement(body);

        ElseStatement *elseStmt = new ElseStatement(list);

        IfStatement *ifStatement = new IfStatement(condition, list);
        ifStatement->addElseClause(elseStmt);
        REQUIRE(ifStatement->toCode() == "if(5>4)\n{5>4;\n}else\n{5>4;\n}");        
    }
}