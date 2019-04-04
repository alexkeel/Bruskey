#include "catch.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "Expression.hpp"
#include "ArithmaticExpression.hpp"
#include <vector>

TEST_CASE("Test expression")
{
    SECTION("Expression assigned to arithmatic expression")
    {
        Integer *lhs = new Integer("5");
        Identifier *op = new Identifier(">");
        Integer *rhs = new Integer("4");

        ArithmaticExpression *condition = new ArithmaticExpression(lhs, op, rhs);
        Expression *expression = new Expression(condition);
        REQUIRE(expression->toCode() == "5>4");
    }
}