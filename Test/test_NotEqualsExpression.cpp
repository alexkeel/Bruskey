#include "catch.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "ExpressionStatement.hpp"
#include "ArithmaticExpression.hpp"
#include "FunctionCall.hpp"
#include "NotEqualsExpression.hpp"
#include <vector>

TEST_CASE("Test a not equals expression")
{
    SECTION("Test a not equals expression")
    {
        Identifier *plusOperator = new Identifier("+");
        Integer *lhsInt = new Integer("5");
        Integer *rhsInt = new Integer("7");
        ArithmaticExpression *arithmaticExpression = new ArithmaticExpression(lhsInt, plusOperator, rhsInt); 
        NotEqualsExpression *notEq = new NotEqualsExpression(arithmaticExpression);

        REQUIRE(notEq->toCode() == "!5+7");
    }
}