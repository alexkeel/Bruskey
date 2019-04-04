#include "catch.hpp"
#include "WhileStatement.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "Expression.hpp"
#include "ArithmaticExpression.hpp"
#include "StatementList.hpp"
#include "ExpressionStatement.hpp"
#include <vector>

TEST_CASE("Test While Statement")
{
    SECTION("While Statement without a body")
    {
        Integer *lhs = new Integer("5");
        Identifier *op = new Identifier(">");
        Integer *rhs = new Integer("4");

        ArithmaticExpression *condition = new ArithmaticExpression(lhs, op, rhs);
        WhileStatement *whileStatement = new WhileStatement(condition);
        REQUIRE(whileStatement->toCode() == "while(5>4)\n{\n}");
    }

    SECTION("While Statement with a body")
    {
        Integer *lhs = new Integer("5");
        Identifier *op = new Identifier(">");
        Integer *rhs = new Integer("4");
    
        ArithmaticExpression *condition = new ArithmaticExpression(lhs, op, rhs);
        ExpressionStatement *body = new ExpressionStatement(condition);
        StatementList *list = new StatementList();
        list->addStatement(body);

        WhileStatement *whileStatement = new WhileStatement(condition, list);
        REQUIRE(whileStatement->toCode() == "while(5>4)\n{5>4;\n}");
    }

}