/**
 * @file test_exec_variable_substitution.c
 * @brief Test suite for exec function variable substitution
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
 * @brief Test basic exec function with variable substitution
 */
void test_exec_basic_variable_substitution() {
    printf("Testing exec with basic variable substitution...\n");
    
    // Create test context
    store* variables = store_create();
    assert(variables != NULL);
    
    // Set a test variable
    variable* test_var = variable_create_string("hello world");
    store_set(variables, "greeting", test_var);
    
    // Create AST evaluator context  
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    ctx->currently_executing = true;
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    memset(evaluator, 0, sizeof(ast_evaluator));
    evaluator->ctx = ctx;
    
    // Parse and evaluate: exec "echo {{greeting}}"
    const char* input = "exec \"echo {{greeting}}\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    assert(ast->data.program.statement_count == 1);
    
    ast_node* stmt = ast->data.program.statements[0];
    assert(stmt->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt->data.function_call.name, "exec") == 0);
    
    // Evaluate the exec function
    ast_value* result = ast_evaluate(stmt, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "hello world") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    store_destroy(variables);
    free(evaluator);
    free(ctx);
    
    printf("✓ Basic variable substitution test passed\n");
}

/**
 * @brief Test exec function with complex command construction
 */
void test_exec_complex_command_construction() {
    printf("Testing exec with complex command construction...\n");
    
    // Create test context
    store* variables = store_create();
    assert(variables != NULL);
    
    // Set test variables
    variable* pattern_var = variable_create_string("debug|test");
    store_set(variables, "pattern", pattern_var);
    
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    ctx->currently_executing = true;
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    memset(evaluator, 0, sizeof(ast_evaluator));
    evaluator->ctx = ctx;
    
    // Parse and evaluate: exec "echo \"{{pattern}}\""
    const char* input = "exec \"echo \\\"{{pattern}}\\\"\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    ast_node* stmt = ast->data.program.statements[0];
    assert(stmt->type == AST_FUNCTION_CALL);
    
    // Evaluate the exec function
    ast_value* result = ast_evaluate(stmt, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    
    // Should have substituted the pattern and executed echo
    printf("Expected: '\"debug|test\"'\n");
    printf("Actual:   '%s'\n", result->value.string_value);
    // The echo command will output the quoted string
    assert(strstr(result->value.string_value, "debug|test") != NULL);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    store_destroy(variables);
    free(evaluator);
    free(ctx);
    
    printf("✓ Complex command construction test passed\n");
}

/**
 * @brief Test exec function with multiple variable substitutions
 */
void test_exec_multiple_variable_substitutions() {
    printf("Testing exec with multiple variable substitutions...\n");
    
    // Create test context
    store* variables = store_create();
    assert(variables != NULL);
    
    // Set test variables
    variable* cmd_var = variable_create_string("echo");
    variable* arg1_var = variable_create_string("hello");
    variable* arg2_var = variable_create_string("world");
    store_set(variables, "cmd", cmd_var);
    store_set(variables, "arg1", arg1_var);
    store_set(variables, "arg2", arg2_var);
    
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    ctx->currently_executing = true;
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    memset(evaluator, 0, sizeof(ast_evaluator));
    evaluator->ctx = ctx;
    
    // Parse and evaluate: exec "{{cmd}} {{arg1}} {{arg2}}"
    const char* input = "exec \"{{cmd}} {{arg1}} {{arg2}}\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    ast_node* stmt = ast->data.program.statements[0];
    
    // Evaluate the exec function
    ast_value* result = ast_evaluate(stmt, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "hello world") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    store_destroy(variables);
    free(evaluator);
    free(ctx);
    
    printf("✓ Multiple variable substitutions test passed\n");
}

/**
 * @brief Test exec function with find command pattern (level 5 style)
 */
void test_exec_find_command_pattern() {
    printf("Testing exec with find command pattern...\n");
    
    // Create test context
    store* variables = store_create();
    assert(variables != NULL);
    
    // Set pattern variable (simulating join result)
    variable* pattern_var = variable_create_string("debug|mock|test");
    store_set(variables, "keywords", pattern_var);
    
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    ctx->currently_executing = true;
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    memset(evaluator, 0, sizeof(ast_evaluator));
    evaluator->ctx = ctx;
    
    // Parse and evaluate find command with grep pattern
    const char* input = "exec \"find . -name \\\"*.c\\\" -exec grep -l \\\"{{keywords}}\\\" {} +\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    ast_node* stmt = ast->data.program.statements[0];
    
    // Evaluate the exec function
    ast_value* result = ast_evaluate(stmt, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    
    // Result should contain file paths (we can't predict exact files, but should not be empty)
    // The key test is that the command executed without truncation
    // Just verify we got a valid string result (may be empty if no files match)
    assert(result->value.string_value != NULL);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    store_destroy(variables);
    free(evaluator);
    free(ctx);
    
    printf("✓ Find command pattern test passed\n");
}

/**
 * @brief Test exec function with variable that doesn't exist
 */
void test_exec_undefined_variable() {
    printf("Testing exec with undefined variable...\n");
    
    // Create test context with empty variables
    store* variables = store_create();
    assert(variables != NULL);
    
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    ctx->currently_executing = true;
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    memset(evaluator, 0, sizeof(ast_evaluator));
    evaluator->ctx = ctx;
    
    // Parse and evaluate: exec "echo {{undefined}}"
    const char* input = "exec \"echo {{undefined}}\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    ast_node* stmt = ast->data.program.statements[0];
    
    // Evaluate the exec function
    ast_value* result = ast_evaluate(stmt, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    
    // Should execute "echo {{undefined}}" literally (variable not substituted)
    assert(strcmp(result->value.string_value, "{{undefined}}") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    store_destroy(variables);
    free(evaluator);
    free(ctx);
    
    printf("✓ Undefined variable test passed\n");
}

/**
 * @brief Test exec function with empty variable
 */
void test_exec_empty_variable() {
    printf("Testing exec with empty variable...\n");
    
    // Create test context
    store* variables = store_create();
    assert(variables != NULL);
    
    // Set empty variable
    variable* empty_var = variable_create_string("");
    store_set(variables, "empty", empty_var);
    
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    ctx->currently_executing = true;
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    memset(evaluator, 0, sizeof(ast_evaluator));
    evaluator->ctx = ctx;
    
    // Parse and evaluate: exec "echo start{{empty}}end"
    const char* input = "exec \"echo start{{empty}}end\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    ast_node* stmt = ast->data.program.statements[0];
    
    // Evaluate the exec function
    ast_value* result = ast_evaluate(stmt, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "startend") == 0);
    
    // Cleanup
    ast_value_free(result);
    ast_free(ast);
    token_list_free(tokens);
    store_destroy(variables);
    free(evaluator);
    free(ctx);
    
    printf("✓ Empty variable test passed\n");
}

/**
 * @brief Main test runner
 */
int main() {
    printf("=== Exec Variable Substitution Test Suite ===\n");
    
    test_exec_basic_variable_substitution();
    test_exec_complex_command_construction();
    test_exec_multiple_variable_substitutions();
    test_exec_find_command_pattern();
    test_exec_undefined_variable();
    test_exec_empty_variable();
    
    printf("\n✅ All exec variable substitution tests passed!\n");
    return 0;
}