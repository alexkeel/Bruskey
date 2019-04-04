#include "catch.hpp"
#include "BuiltInFunction.hpp"
#include "Identifier.hpp"
#include "Integer.hpp"
#include "Expression.hpp"
#include <vector>

TEST_CASE("Testing Built In Function")
{
    SECTION("Testing built in functions without parameters")
    {
        Identifier *ident = new Identifier("ObstacleDetected");
        BuiltInFunction *func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "initio_IrLeft() !=0 || initio_IrRight() !=0");

        ident = new Identifier("Stop");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "initio_DriveForward(0)");

        ident = new Identifier("BlobVisible");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "blobDetected(blob)");

        ident = new Identifier("SpinLeft");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "initio_SpinLeft(speed)");

        ident = new Identifier("SpinRight");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "initio_SpinRight(speed)");

        ident = new Identifier("DriveForward");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "initio_DriveForward(speed)");

        ident = new Identifier("DriveBackward");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "initio_DriveReverse(speed)");

        ident = new Identifier("GetBlobHAlignment");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "getBlobHAlignment()");

        ident = new Identifier("GetDistance");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "initio_UsGetDistance()");

        ident = new Identifier("LeftLineDetected");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "initio_IrLineLeft()");

        ident = new Identifier("RightLineDetected");
        func = new BuiltInFunction(ident);
        REQUIRE(func->toCode() == "initio_IrLineRight()");                        
    }

    SECTION("Testing built in functions wit parameters")
    {
        std::vector<Expression *> *argumentList = new std::vector<Expression *>();   
        Integer *integer = new Integer("50");      
        argumentList->push_back(integer);   

        Identifier *ident = new Identifier("Pause");
        BuiltInFunction *func = new BuiltInFunction(ident, argumentList);
        REQUIRE(func->toCode() == "delay(50)");  

        ident = new Identifier("SpinRight");
        func = new BuiltInFunction(ident, argumentList);
        REQUIRE(func->toCode() == "initio_SpinRight(50)");     

        ident = new Identifier("SpinLeft");
        func = new BuiltInFunction(ident, argumentList);
        REQUIRE(func->toCode() == "initio_SpinLeft(50)");  

        ident = new Identifier("DriveForward");
        func = new BuiltInFunction(ident, argumentList);
        REQUIRE(func->toCode() == "initio_DriveForward(50)");  

        ident = new Identifier("DriveBackward");
        func = new BuiltInFunction(ident, argumentList);
        REQUIRE(func->toCode() == "initio_DriveReverse(50)");                             
    }    
}
