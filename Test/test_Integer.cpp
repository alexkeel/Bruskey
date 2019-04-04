#include "catch.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "ExpressionStatement.hpp"
#include "ArithmaticExpression.hpp"
#include "FunctionCall.hpp"
#include <vector>

TEST_CASE("Test an integer")
{
    SECTION("Test an integer")
    {
        Integer *ident = new Integer("test");

        REQUIRE(ident->toCode() == "test");
    }
}