#include "catch.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "ExpressionStatement.hpp"
#include "ArithmaticExpression.hpp"
#include <vector>

TEST_CASE("Test expression statement")
{
    SECTION("Expression assigned to arithmatic expression")
    {
        Integer *lhs = new Integer("5");
        Identifier *op = new Identifier(">");
        Integer *rhs = new Integer("4");

        ArithmaticExpression *condition = new ArithmaticExpression(lhs, op, rhs);
        ExpressionStatement *expression = new ExpressionStatement(condition);
        REQUIRE(expression->toCode() == "5>4;");
    }
}