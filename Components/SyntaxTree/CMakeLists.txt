cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES src/Expression.cpp
                 src/ArithmaticExpression.cpp 
                 src/Identifier.cpp src/Integer.cpp 
                 src/TranslationUnit.cpp 
                 src/FunctionCall.cpp 
                 src/NotEqualsExpression.cpp
                 src/IfStatement.cpp
                 src/ElseStatement.cpp
                 src/ElseIfStatement.cpp
                 src/WhileStatement.cpp
                 src/StatementList.cpp
                 src/BuiltInFunction.cpp
                 src/ExpressionStatement.cpp
                 src/ParenthesesExpression.cpp
                 src/Common.cpp
 )

add_library(SyntaxTree ${SOURCE_FILES})

target_include_directories(SyntaxTree PUBLIC include)