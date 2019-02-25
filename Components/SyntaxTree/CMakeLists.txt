cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES src/Expression.cpp
                 src/ArithmaticExpression.cpp 
                 src/Identifier.cpp src/Integer.cpp 
                 src/TranslationUnit.cpp 
                 src/FunctionCall.cpp 
                 src/NotEqualsExpression.cpp
                 src/IfStatement.cpp
                 src/WhileStatement.cpp
                 src/StatementList.cpp
 )

add_library(SyntaxTree ${SOURCE_FILES})

target_include_directories(SyntaxTree PUBLIC include)