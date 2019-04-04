#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ArithmaticExpression.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"

TEST_CASE("Testing Arithmatic Expression")
{
    Identifier *plusOperator = new Identifier("+");
    Integer *lhsInt = new Integer("5");
    Integer *rhsInt = new Integer("7");

    SECTION("Generating basic arithmetic")
    {
        ArithmaticExpression arithmaticExpression(lhsInt, plusOperator, rhsInt); 

        REQUIRE(arithmaticExpression.toCode() == "5+7");
    }

    SECTION("Generating more complex arithmatic")
    {
        ArithmaticExpression arithmaticExpression(lhsInt, plusOperator, rhsInt); 
        ArithmaticExpression arithmaticExpression2(lhsInt, plusOperator, &arithmaticExpression); 

        REQUIRE(arithmaticExpression2.toCode() == "5+5+7");
    }

    SECTION("Using each operator (* / + - %)")
    {
        Identifier *newOperator = new Identifier("-");
        ArithmaticExpression arithmaticExpression1(lhsInt, newOperator, rhsInt); 

        REQUIRE(arithmaticExpression1.toCode() == "5-7");

        newOperator = new Identifier("/");
        ArithmaticExpression arithmaticExpression2(lhsInt, newOperator, rhsInt); 

        REQUIRE(arithmaticExpression2.toCode() == "5/7");

        newOperator = new Identifier("*");
        ArithmaticExpression arithmaticExpression3(lhsInt, newOperator, rhsInt); 

        REQUIRE(arithmaticExpression3.toCode() == "5*7");

        newOperator = new Identifier("%");
        ArithmaticExpression arithmaticExpression4(lhsInt, newOperator, rhsInt); 

        REQUIRE(arithmaticExpression4.toCode() == "5%7");
    }
}
