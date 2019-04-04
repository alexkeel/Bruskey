cmake_minimum_required(VERSION 2.8.9)

set(SOURCE_FILES test_ArithmaticExpression.cpp
                 test_BuiltInFunction.cpp
                 test_IfStatement.cpp
                 test_Expression.cpp
                 test_ExpressionStatement.cpp
                 test_FunctionCall.cpp
                 test_Integer.cpp
                 test_Identifier.cpp
                 test_NotEqualsExpression.cpp
                 test_ParenthesesExpression.cpp
                 test_WhileStatement.cpp
                 test_TranslationUnit.cpp
)

add_executable(Tests ${SOURCE_FILES})

target_link_libraries(Tests SyntaxTree)
target_link_libraries(Tests Catch)



