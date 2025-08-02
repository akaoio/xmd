/**
 * @file test_function_join.c
 * @brief Test join function implementation
 * @author XMD Team
 * @date 2025-07-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/ast_evaluator.h"
#include "../../include/ast_parser.h"
#include "../../include/lexer_enhanced.h"
#include "../../include/xmd_processor_internal.h"

/**
 * @brief Test join function with string array
 */
void test_join_string_array() {
    printf("Testing join function with string array...\n");
    
    // Create test context
    processor_context* ctx = processor_context_create();
    variable_store* store = variable_store_create();
    ast_evaluator* evaluator = ast_evaluator_create(store, ctx);
    
    // Test: join ["a", "b", "c"]
    const char* expr = "join [\"a\", \"b\", \"c\"]";
    token* tokens = lexer_enhanced_tokenize(expr, "test");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    assert(ast->type == AST_PROGRAM);
    assert(ast->data.program.statement_count == 1);
    
    ast_value* result = ast_evaluate(ast->data.program.statements[0], evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "a, b, c") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    ast_evaluator_free(evaluator);
    variable_store_free(store);
    processor_context_free(ctx);
    
    printf("✓ Join string array test passed\n");
}

/**
 * @brief Test join function with single element
 */
void test_join_single_element() {
    printf("Testing join function with single element...\n");
    
    // Create test context
    processor_context* ctx = processor_context_create();
    variable_store* store = variable_store_create();
    ast_evaluator* evaluator = ast_evaluator_create(store, ctx);
    
    // Test: join ["only"]
    const char* expr = "join [\"only\"]";
    token* tokens = lexer_enhanced_tokenize(expr, "test");
    ast_node* ast = ast_parse_program(tokens);
    
    ast_value* result = ast_evaluate(ast->data.program.statements[0], evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "only") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    ast_evaluator_free(evaluator);
    variable_store_free(store);
    processor_context_free(ctx);
    
    printf("✓ Join single element test passed\n");
}

/**
 * @brief Test join function with empty array
 */
void test_join_empty_array() {
    printf("Testing join function with empty array...\n");
    
    // Create test context
    processor_context* ctx = processor_context_create();
    variable_store* store = variable_store_create();
    ast_evaluator* evaluator = ast_evaluator_create(store, ctx);
    
    // Test: join []
    const char* expr = "join []";
    token* tokens = lexer_enhanced_tokenize(expr, "test");
    ast_node* ast = ast_parse_program(tokens);
    
    ast_value* result = ast_evaluate(ast->data.program.statements[0], evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    ast_evaluator_free(evaluator);
    variable_store_free(store);
    processor_context_free(ctx);
    
    printf("✓ Join empty array test passed\n");
}

/**
 * @brief Test join function with variable array
 */
void test_join_variable_array() {
    printf("Testing join function with variable array...\n");
    
    // Create test context
    processor_context* ctx = processor_context_create();
    variable_store* store = variable_store_create();
    ast_evaluator* evaluator = ast_evaluator_create(store, ctx);
    
    // Set up array variable
    variable* arr = variable_create_array();
    variable_array_add(arr, variable_create_string("x"));
    variable_array_add(arr, variable_create_string("y"));
    variable_array_add(arr, variable_create_string("z"));
    variable_store_set(store, "myarr", arr);
    
    // Test: join myarr
    const char* expr = "join myarr";
    token* tokens = lexer_enhanced_tokenize(expr, "test");
    ast_node* ast = ast_parse_program(tokens);
    
    ast_value* result = ast_evaluate(ast->data.program.statements[0], evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "x, y, z") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    ast_evaluator_free(evaluator);
    variable_store_free(store);
    processor_context_free(ctx);
    
    printf("✓ Join variable array test passed\n");
}

int main() {
    printf("=== Join Function Test Suite ===\n");
    
    test_join_string_array();
    test_join_single_element();
    test_join_empty_array();
    test_join_variable_array();
    
    printf("\n✅ All join function tests passed!\n");
    return 0;
}