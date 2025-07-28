/**
 * @file test_level5_integration.c
 * @brief Integration test for level 5 functionality
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/ast_evaluator.h"
#include "../include/ast_parser.h"
#include "../include/lexer_enhanced.h"
#include "../include/store.h"
#include "../include/variable.h"
#include "../include/xmd_processor_internal.h"

/**
 * @brief Test join function with custom separator
 */
void test_join_custom_separator_evaluation() {
    printf("Testing join function with custom separator evaluation...\n");
    
    // Create test context
    store* variables = store_create();
    assert(variables != NULL);
    
    // Create array variable
    variable* arr = variable_create_array();
    variable_array_add(arr, variable_create_string("debug"));
    variable_array_add(arr, variable_create_string("for now"));
    variable_array_add(arr, variable_create_string("in real"));
    variable_array_add(arr, variable_create_string("mock"));
    store_set(variables, "keywords", arr);
    
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    ctx->currently_executing = true;
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    memset(evaluator, 0, sizeof(ast_evaluator));
    evaluator->ctx = ctx;
    
    // Parse and evaluate: join keywords "|"
    const char* input = "join keywords \"|\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    ast_node* stmt = ast->data.program.statements[0];
    assert(stmt->type == AST_FUNCTION_CALL);
    
    // Evaluate the join function
    ast_value* result = ast_evaluate(stmt, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "debug|for now|in real|mock") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    store_destroy(variables);
    free(evaluator);
    free(ctx);
    
    printf("✓ Join custom separator evaluation test passed\n");
}

/**
 * @brief Test string concatenation with escape sequences
 */
void test_string_concatenation_with_escapes() {
    printf("Testing string concatenation with escape sequences...\n");
    
    // Create test context
    store* variables = store_create();
    assert(variables != NULL);
    
    // Set pattern variable
    variable* pattern_var = variable_create_string("debug|test");
    store_set(variables, "pattern", pattern_var);
    
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    ctx->currently_executing = true;
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    memset(evaluator, 0, sizeof(ast_evaluator));
    evaluator->ctx = ctx;
    
    // Parse and evaluate: "grep -E \"" + pattern + "\""
    const char* input = "\"grep -E \\\"\" + pattern + \"\\\"\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    ast_node* stmt = ast->data.program.statements[0];
    assert(stmt->type == AST_BINARY_OP);
    
    // Evaluate the concatenation
    ast_value* result = ast_evaluate(stmt, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "grep -E \"debug|test\"") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    store_destroy(variables);
    free(evaluator);
    free(ctx);
    
    printf("✓ String concatenation with escapes test passed\n");
}

/**
 * @brief Test level 5 core functionality sequence
 */
void test_level5_core_sequence() {
    printf("Testing level 5 core functionality sequence...\n");
    
    // Create test context
    store* variables = store_create();
    assert(variables != NULL);
    
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    ctx->currently_executing = true;
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    memset(evaluator, 0, sizeof(ast_evaluator));
    evaluator->ctx = ctx;
    
    // Step 1: Create array
    const char* input1 = "arr = [\"debug\", \"mock\", \"test\"]";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    assert(ast1 != NULL);
    
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_ASSIGNMENT);
    
    // Execute assignment
    int result1 = ast_evaluate_assignment(stmt1, evaluator);
    assert(result1 == 0);
    
    // Step 2: Join with custom separator
    const char* input2 = "join arr \"|\"";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    assert(ast2 != NULL);
    
    ast_node* stmt2 = ast2->data.program.statements[0];
    ast_value* result2 = ast_evaluate(stmt2, evaluator);
    assert(result2 != NULL);
    assert(strcmp(result2->value.string_value, "debug|mock|test") == 0);
    
    // Step 3: Store join result
    variable* keywords_var = ast_value_to_variable(result2);
    store_set(variables, "keywords", keywords_var);
    
    // Step 4: Build command with concatenation and escapes
    const char* input3 = "\"find . -name \\\"*.c\\\" -exec grep -l \\\"\" + keywords + \"\\\" {} +\"";
    token* tokens3 = lexer_enhanced_tokenize(input3, "test.xmd");
    ast_node* ast3 = ast_parse_program(tokens3);
    assert(ast3 != NULL);
    
    ast_node* stmt3 = ast3->data.program.statements[0];
    ast_value* result3 = ast_evaluate(stmt3, evaluator);
    assert(result3 != NULL);
    assert(strcmp(result3->value.string_value, "find . -name \"*.c\" -exec grep -l \"debug|mock|test\" {} +") == 0);
    
    // Cleanup
    ast_value_free(result2);
    ast_value_free(result3);
    ast_free(ast1);
    ast_free(ast2);
    ast_free(ast3);
    token_list_free(tokens1);
    token_list_free(tokens2);
    token_list_free(tokens3);
    store_destroy(variables);
    free(evaluator);
    free(ctx);
    
    printf("✓ Level 5 core sequence test passed\n");
}

/**
 * @brief Test escape sequence preservation in lexer
 */
void test_escape_sequence_preservation() {
    printf("Testing escape sequence preservation in lexer...\n");
    
    // Test the exact pattern that was failing before the fix
    const char* input = "\"find src -type f -exec grep -liE \\\"debug|test\\\" {} +\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    
    // Verify the full string is preserved, not truncated at escaped quotes
    const char* expected = "find src -type f -exec grep -liE \\\"debug|test\\\" {} +";
    assert(strcmp(tokens->value, expected) == 0);
    
    token_list_free(tokens);
    printf("✓ Escape sequence preservation test passed\n");
}

/**
 * @brief Main test runner
 */
int main() {
    printf("=== Level 5 Integration Test Suite ===\n");
    
    test_join_custom_separator_evaluation();
    test_string_concatenation_with_escapes();
    test_level5_core_sequence();
    test_escape_sequence_preservation();
    
    printf("\n✅ All level 5 integration tests passed!\n");
    return 0;
}