#include "catch.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "ExpressionStatement.hpp"
#include "ArithmaticExpression.hpp"
#include "FunctionCall.hpp"
#include <vector>

TEST_CASE("Test a function call")
{
    SECTION("Test a function call with no argument")
    {
        Integer *arg1 = new Integer("5");
        Integer *arg2 = new Integer("4");
        Identifier *ident = new Identifier("test");

        FunctionCall *func = new FunctionCall(ident);
        REQUIRE(func->toCode() == "test()");
    }

    SECTION("Test a function call with a single argument")
    {
        Integer *arg1 = new Integer("5");
        Integer *arg2 = new Integer("4");
        Identifier *ident = new Identifier("test");

        FunctionCall *func = new FunctionCall(ident, arg1);
        REQUIRE(func->toCode() == "test(5)");
    }

    SECTION("Test a function call with multiple arguments")
    {
        Integer *arg1 = new Integer("5");
        Integer *arg2 = new Integer("4");
        Identifier *ident = new Identifier("test");
        std::vector<Expression *> *arguments = new std::vector<Expression *>();
        arguments->push_back(arg1);
        arguments->push_back(arg2);

        FunctionCall *func = new FunctionCall(ident, arguments);
        REQUIRE(func->toCode() == "test(5,4)");
    }
}