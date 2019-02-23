cmake_minimum_required(VERSION 2.8)


add_library(SyntaxTree src/ArithmaticExpression.cpp src/Identifier.cpp src/Integer.cpp src/TranslationUnit.cpp)

target_include_directories(SyntaxTree PUBLIC include)