cmake_minimum_required(VERSION 2.8)


add_library(SyntaxTree src/Expression.cpp src/ArithmaticExpression.cpp src/Identifier.cpp src/Integer.cpp src/TranslationUnit.cpp src/FunctionCall.cpp src/NotEqualsExpression.cpp src/IfStatement.cpp)

target_include_directories(SyntaxTree PUBLIC include)