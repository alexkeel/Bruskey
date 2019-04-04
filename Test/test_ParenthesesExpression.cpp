#include "catch.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "ExpressionStatement.hpp"
#include "ArithmaticExpression.hpp"
#include "FunctionCall.hpp"
#include "ParenthesesExpression.hpp"
#include <vector>

TEST_CASE("Test a parentheses expression")
{
    SECTION("Test a parentheses expression")
    {
        Identifier *plusOperator = new Identifier("+");
        Integer *lhsInt = new Integer("5");
        Integer *rhsInt = new Integer("7");
        ArithmaticExpression *arithmaticExpression = new ArithmaticExpression(lhsInt, plusOperator, rhsInt); 
        ParenthesesExpression *parExpr = new ParenthesesExpression(arithmaticExpression);

        REQUIRE(parExpr->toCode() == "(5+7)");
    }
}