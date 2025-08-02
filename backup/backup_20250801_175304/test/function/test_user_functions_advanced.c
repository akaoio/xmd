/**
 * @file test_user_functions_advanced.c
 * @brief Advanced tests for user-defined functions with real scenarios
 * @author XMD Team
 * @date 2025-07-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/ast_parser.h"
#include "../../include/ast_node.h"
#include "../../include/ast_evaluator.h"
#include "../../include/store.h"
#include "../../include/variable.h"
#include "../../include/lexer_enhanced.h"

/**
 * @brief Test shell-style function call transformation
 */
void test_shell_function_transformation() {
    printf("Testing shell-style function call transformation...\n");
    
    // Test simple function call
    char* result = ast_transform_shell_function_call("add 5 3");
    assert(result != NULL);
    assert(strcmp(result, "add(5, 3)") == 0);
    free(result);
    
    // Test function with no arguments
    result = ast_transform_shell_function_call("getValue");
    assert(result != NULL);
    assert(strcmp(result, "getValue()") == 0);
    free(result);
    
    // Test function with quoted arguments
    result = ast_transform_shell_function_call("greet \"John Doe\" world");
    assert(result != NULL);
    assert(strcmp(result, "greet(\"John Doe\", world)") == 0);
    free(result);
    
    // Test non-function (should return NULL)
    result = ast_transform_shell_function_call("123 invalid");
    assert(result == NULL);
    
    printf("✓ Shell function transformation passed\n");
}

/**
 * @brief Test complete function definition and evaluation
 */
void test_function_definition_evaluation() {
    printf("Testing function definition and evaluation...\n");
    
    // Create evaluator and store
    store* variables = store_create();
    assert(variables != NULL);
    
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    
    ast_evaluator* evaluator = ast_evaluator_create(variables, ctx);
    assert(evaluator != NULL);
    
    source_location loc = {1, 1, "test.xmd"};
    
    // Create a simple function: function double x
    //                           return x * 2
    ast_node* func_def = ast_create_function_def("double", loc);
    assert(func_def != NULL);
    assert(ast_add_parameter(func_def, "x") == 0);
    
    // Create function body with return statement
    ast_node* body = ast_create_block(loc);
    assert(body != NULL);
    
    // Create return statement: return x * 2
    ast_node* x_ref = ast_create_variable_ref("x", loc);
    ast_node* two = ast_create_number_literal(2.0, loc);
    ast_node* multiply = ast_create_binary_op(BINOP_MUL, x_ref, two, loc);
    ast_node* return_stmt = ast_create_return(multiply, loc);
    
    assert(ast_add_statement(body, return_stmt) == 0);
    func_def->data.function_def.body = body;
    
    // Register function by evaluating its definition
    ast_value* reg_result = ast_evaluate(func_def, evaluator);
    assert(reg_result != NULL);
    assert(reg_result->type == AST_VAL_NULL);  // Registration returns null
    ast_value_free(reg_result);
    
    // Create function call: double(5)
    ast_node* call = ast_create_function_call("double", loc);
    assert(call != NULL);
    
    ast_node* arg = ast_create_number_literal(5.0, loc);
    assert(ast_add_argument(call, arg) == 0);
    
    // Evaluate function call
    ast_value* result = ast_evaluate(call, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_NUMBER);
    assert(result->value.number_value == 10.0);
    
    printf("✓ Function definition and evaluation passed\n");
    
    // Cleanup
    ast_value_free(result);
    ast_free(call);
    ast_free(func_def);
    ast_evaluator_free(evaluator);
    store_destroy(variables);
    free(ctx);
}

/**
 * @brief Test function with multiple parameters
 */
void test_multi_parameter_function() {
    printf("Testing multi-parameter function...\n");
    
    store* variables = store_create();
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    
    ast_evaluator* evaluator = ast_evaluator_create(variables, ctx);
    source_location loc = {1, 1, "test.xmd"};
    
    // Create function: function add a b
    //                  return a + b
    ast_node* func_def = ast_create_function_def("add", loc);
    assert(ast_add_parameter(func_def, "a") == 0);
    assert(ast_add_parameter(func_def, "b") == 0);
    
    ast_node* body = ast_create_block(loc);
    ast_node* a_ref = ast_create_variable_ref("a", loc);
    ast_node* b_ref = ast_create_variable_ref("b", loc);
    ast_node* add_expr = ast_create_binary_op(BINOP_ADD, a_ref, b_ref, loc);
    ast_node* return_stmt = ast_create_return(add_expr, loc);
    
    assert(ast_add_statement(body, return_stmt) == 0);
    func_def->data.function_def.body = body;
    
    // Register function
    ast_value* reg_result = ast_evaluate(func_def, evaluator);
    assert(reg_result != NULL);
    ast_value_free(reg_result);
    
    // Create function call: add(3, 7)
    ast_node* call = ast_create_function_call("add", loc);
    ast_node* arg1 = ast_create_number_literal(3.0, loc);
    ast_node* arg2 = ast_create_number_literal(7.0, loc);
    assert(ast_add_argument(call, arg1) == 0);
    assert(ast_add_argument(call, arg2) == 0);
    
    // Evaluate
    ast_value* result = ast_evaluate(call, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_NUMBER);
    assert(result->value.number_value == 10.0);
    
    printf("✓ Multi-parameter function passed\n");
    
    // Cleanup
    ast_value_free(result);
    ast_free(call);
    ast_free(func_def);
    ast_evaluator_free(evaluator);
    store_destroy(variables);
    free(ctx);
}

/**
 * @brief Test function scope isolation
 */
void test_function_scope() {
    printf("Testing function scope isolation...\n");
    
    store* variables = store_create();
    processor_context* ctx = malloc(sizeof(processor_context));
    memset(ctx, 0, sizeof(processor_context));
    ctx->variables = variables;
    
    // Set a global variable
    variable* global_var = variable_create_string("global_value");
    store_set(variables, "x", global_var);
    variable_unref(global_var);
    
    ast_evaluator* evaluator = ast_evaluator_create(variables, ctx);
    source_location loc = {1, 1, "test.xmd"};
    
    // Create function that uses parameter x: function getValue x
    //                                         return x
    ast_node* func_def = ast_create_function_def("getValue", loc);
    assert(ast_add_parameter(func_def, "x") == 0);
    
    ast_node* body = ast_create_block(loc);
    ast_node* x_ref = ast_create_variable_ref("x", loc);
    ast_node* return_stmt = ast_create_return(x_ref, loc);
    
    assert(ast_add_statement(body, return_stmt) == 0);
    func_def->data.function_def.body = body;
    
    // Register function
    ast_value* reg_result = ast_evaluate(func_def, evaluator);
    assert(reg_result != NULL);
    ast_value_free(reg_result);
    
    // Call function with different value
    ast_node* call = ast_create_function_call("getValue", loc);
    ast_node* arg = ast_create_string_literal("parameter_value", loc);
    assert(ast_add_argument(call, arg) == 0);
    
    // Should return parameter value, not global
    ast_value* result = ast_evaluate(call, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "parameter_value") == 0);
    
    // Verify global variable is unchanged
    variable* check_global = store_get(variables, "x");
    assert(check_global != NULL);
    assert(strcmp(check_global->value.string_value, "global_value") == 0);
    
    printf("✓ Function scope isolation passed\n");
    
    // Cleanup
    ast_value_free(result);
    ast_free(call);
    ast_free(func_def);
    ast_evaluator_free(evaluator);
    store_destroy(variables);
    free(ctx);
}

int main() {
    printf("=== Advanced User-Defined Functions Tests ===\n");
    
    test_shell_function_transformation();
    test_function_definition_evaluation();
    test_multi_parameter_function();
    test_function_scope();
    
    printf("=== All advanced function tests passed! ===\n");
    return 0;
}