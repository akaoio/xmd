/**
 * @file test_ast_create_number_literal.c  
 * @brief Test for ast_create_number_literal function
 * 
 * ENFORCING PRINCIPLE: Test-driven development
 * TEST FIRST, IMPLEMENT LATER
 */

#include "unity/unity.h"
#include "../src/ast/node/ast_create_number_literal/ast_create_number_literal.h"
#include "../include/ast.h"

/**
 * @brief Test ast_create_number_literal with valid input
 */
void test_ast_create_number_literal_valid(void) {
    source_location loc = {1, 1, "test.c"};
    double value = 42.5;
    
    ast_node* node = ast_create_number_literal(value, loc);
    
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(AST_NUMBER_LITERAL, node->type);
    TEST_ASSERT_EQUAL(42.5, node->data.number_literal.value);
    TEST_ASSERT_EQUAL(1, node->location.line);
    TEST_ASSERT_EQUAL(1, node->location.column);
    
    // Cleanup
    ast_free(node);
}

/**
 * @brief Test ast_create_number_literal with zero
 */
void test_ast_create_number_literal_zero(void) {
    source_location loc = {2, 5, "test.c"};
    double value = 0.0;
    
    ast_node* node = ast_create_number_literal(value, loc);
    
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(AST_NUMBER_LITERAL, node->type);
    TEST_ASSERT_EQUAL(0.0, node->data.number_literal.value);
    
    // Cleanup
    ast_free(node);
}

/**
 * @brief Test ast_create_number_literal with negative number
 */
void test_ast_create_number_literal_negative(void) {
    source_location loc = {3, 10, "test.c"};
    double value = -123.456;
    
    ast_node* node = ast_create_number_literal(value, loc);
    
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(AST_NUMBER_LITERAL, node->type);
    TEST_ASSERT_EQUAL(-123.456, node->data.number_literal.value);
    
    // Cleanup  
    ast_free(node);
}

/**
 * @brief Main test runner
 */
int main(void) {
    Unity_Begin("AST Create Number Literal Tests");
    
    RUN_TEST(test_ast_create_number_literal_valid);
    RUN_TEST(test_ast_create_number_literal_zero);
    RUN_TEST(test_ast_create_number_literal_negative);
    
    return Unity_End();
}