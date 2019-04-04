#include "catch.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "ExpressionStatement.hpp"
#include "ArithmaticExpression.hpp"
#include "FunctionCall.hpp"
#include <vector>

TEST_CASE("Test an identifier")
{
    SECTION("Test an identifier")
    {
        Identifier *ident = new Identifier("test");

        REQUIRE(ident->toCode() == "test");
    }
}