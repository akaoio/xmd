/**
 * @file test_user_functions_basic.c
 * @brief Basic tests for user-defined functions
 * @author XMD Team
 * @date 2025-07-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/ast_parser.h"
#include "../../include/ast_node.h"
#include "../../include/lexer_enhanced.h"

/**
 * @brief Test function definition AST node creation
 */
void test_function_def_creation() {
    printf("Testing function definition AST node creation...\n");
    
    source_location loc = {1, 1, "test.xmd"};
    
    // Create function definition
    ast_node* func_def = ast_create_function_def("add", loc);
    assert(func_def != NULL);
    assert(func_def->type == AST_FUNCTION_DEF);
    assert(strcmp(func_def->data.function_def.name, "add") == 0);
    assert(func_def->data.function_def.parameter_count == 0);
    assert(func_def->data.function_def.parameters == NULL);
    assert(func_def->data.function_def.body == NULL);
    
    printf("✓ Function definition creation passed\n");
    ast_free(func_def);
}

/**
 * @brief Test adding parameters to function definition
 */
void test_add_parameters() {
    printf("Testing parameter addition...\n");
    
    source_location loc = {1, 1, "test.xmd"};
    
    // Create function and add parameters
    ast_node* func_def = ast_create_function_def("add", loc);
    assert(func_def != NULL);
    
    // Add first parameter
    int result = ast_add_parameter(func_def, "a");
    assert(result == 0);
    assert(func_def->data.function_def.parameter_count == 1);
    assert(strcmp(func_def->data.function_def.parameters[0], "a") == 0);
    
    // Add second parameter
    result = ast_add_parameter(func_def, "b");
    assert(result == 0);
    assert(func_def->data.function_def.parameter_count == 2);
    assert(strcmp(func_def->data.function_def.parameters[1], "b") == 0);
    
    printf("✓ Parameter addition passed\n");
    ast_free(func_def);
}

/**
 * @brief Test return statement creation
 */
void test_return_statement() {
    printf("Testing return statement creation...\n");
    
    source_location loc = {1, 1, "test.xmd"};
    
    // Create return with value
    ast_node* value = ast_create_number_literal(42.0, loc);
    ast_node* return_stmt = ast_create_return(value, loc);
    assert(return_stmt != NULL);
    assert(return_stmt->type == AST_RETURN);
    assert(return_stmt->data.return_stmt.value == value);
    
    // Create empty return
    ast_node* empty_return = ast_create_return(NULL, loc);
    assert(empty_return != NULL);
    assert(empty_return->type == AST_RETURN);
    assert(empty_return->data.return_stmt.value == NULL);
    
    printf("✓ Return statement creation passed\n");
    
    ast_free(return_stmt);
    ast_free(empty_return);
}

/**
 * @brief Test complete function definition with body
 */
void test_complete_function() {
    printf("Testing complete function definition...\n");
    
    source_location loc = {1, 1, "test.xmd"};
    
    // Create function
    ast_node* func_def = ast_create_function_def("multiply", loc);
    assert(func_def != NULL);
    
    // Add parameters
    ast_add_parameter(func_def, "x");
    ast_add_parameter(func_def, "y");
    
    // Create body (block with return statement)
    ast_node* body = ast_create_block(loc);
    assert(body != NULL);
    
    // Create return statement: return x * y
    ast_node* x_ref = ast_create_variable_ref("x", loc);
    ast_node* y_ref = ast_create_variable_ref("y", loc);
    ast_node* multiply = ast_create_binary_op(BINOP_MUL, x_ref, y_ref, loc);
    ast_node* return_stmt = ast_create_return(multiply, loc);
    
    // Add return to body
    ast_add_statement(body, return_stmt);
    
    // Set body in function
    func_def->data.function_def.body = body;
    
    // Verify structure
    assert(func_def->data.function_def.parameter_count == 2);
    assert(strcmp(func_def->data.function_def.parameters[0], "x") == 0);
    assert(strcmp(func_def->data.function_def.parameters[1], "y") == 0);
    assert(func_def->data.function_def.body == body);
    assert(body->data.block.statement_count == 1);
    assert(body->data.block.statements[0]->type == AST_RETURN);
    
    printf("✓ Complete function definition passed\n");
    ast_free(func_def);
}

int main() {
    printf("=== User-Defined Functions Basic Tests ===\n");
    
    test_function_def_creation();
    test_add_parameters();
    test_return_statement();
    test_complete_function();
    
    printf("=== All basic function tests passed! ===\n");
    return 0;
}