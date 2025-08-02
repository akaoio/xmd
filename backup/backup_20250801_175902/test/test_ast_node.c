/**
 * @file test_ast_node.c
 * @brief Test suite for AST node system
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/ast_node.h"

/**
 * @brief Test AST node creation and basic properties
 */
void test_ast_node_creation() {
    printf("Testing AST node creation...\n");
    
    // Test program node creation
    ast_node* program = ast_create_program();
    assert(program != NULL);
    assert(program->type == AST_PROGRAM);
    assert(program->data.program.statements == NULL);
    assert(program->data.program.statement_count == 0);
    
    // Test string literal creation
    source_location loc = {1, 1, "test.xmd"};
    ast_node* str_lit = ast_create_string_literal("hello world", loc);
    assert(str_lit != NULL);
    assert(str_lit->type == AST_LITERAL);
    assert(str_lit->data.literal.type == LITERAL_STRING);
    assert(strcmp(str_lit->data.literal.value.string_value, "hello world") == 0);
    assert(str_lit->location.line == 1);
    assert(str_lit->location.column == 1);
    
    // Test number literal creation
    ast_node* num_lit = ast_create_number_literal(42.5, loc);
    assert(num_lit != NULL);
    assert(num_lit->type == AST_LITERAL);
    assert(num_lit->data.literal.type == LITERAL_NUMBER);
    assert(num_lit->data.literal.value.number_value == 42.5);
    
    // Test boolean literal creation
    ast_node* bool_lit = ast_create_boolean_literal(true, loc);
    assert(bool_lit != NULL);
    assert(bool_lit->type == AST_LITERAL);
    assert(bool_lit->data.literal.type == LITERAL_BOOLEAN);
    assert(bool_lit->data.literal.value.boolean_value == true);
    
    ast_free(program);
    ast_free(str_lit);
    ast_free(num_lit);
    ast_free(bool_lit);
    
    printf("✓ AST node creation tests passed\n");
}

/**
 * @brief Test variable reference and identifier nodes
 */
void test_variable_nodes() {
    printf("Testing variable and identifier nodes...\n");
    
    source_location loc = {2, 5, "test.xmd"};
    
    // Test variable reference
    ast_node* var_ref = ast_create_variable_ref("my_var", loc);
    assert(var_ref != NULL);
    assert(var_ref->type == AST_VARIABLE_REF);
    assert(strcmp(var_ref->data.variable_ref.name, "my_var") == 0);
    
    // Test identifier
    ast_node* ident = ast_create_identifier("identifier", loc);
    assert(ident != NULL);
    assert(ident->type == AST_IDENTIFIER);
    assert(strcmp(ident->data.identifier.name, "identifier") == 0);
    
    ast_free(var_ref);
    ast_free(ident);
    
    printf("✓ Variable node tests passed\n");
}

/**
 * @brief Test binary and unary operations
 */
void test_operation_nodes() {
    printf("Testing operation nodes...\n");
    
    source_location loc = {3, 10, "test.xmd"};
    
    // Create operands
    ast_node* left = ast_create_number_literal(10, loc);
    ast_node* right = ast_create_number_literal(5, loc);
    
    // Test binary operation
    ast_node* binop = ast_create_binary_op(BINOP_ADD, left, right, loc);
    assert(binop != NULL);
    assert(binop->type == AST_BINARY_OP);
    assert(binop->data.binary_op.op == BINOP_ADD);
    assert(binop->data.binary_op.left == left);
    assert(binop->data.binary_op.right == right);
    
    // Test unary operation
    ast_node* operand = ast_create_boolean_literal(true, loc);
    ast_node* unop = ast_create_unary_op(UNOP_NOT, operand, loc);
    assert(unop != NULL);
    assert(unop->type == AST_UNARY_OP);
    assert(unop->data.unary_op.op == UNOP_NOT);
    assert(unop->data.unary_op.operand == operand);
    
    ast_free(binop);  // Should free left and right too
    ast_free(unop);   // Should free operand too
    
    printf("✓ Operation node tests passed\n");
}

/**
 * @brief Test function call nodes
 */
void test_function_call_nodes() {
    printf("Testing function call nodes...\n");
    
    source_location loc = {4, 15, "test.xmd"};
    
    // Create function call
    ast_node* func_call = ast_create_function_call("import", loc);
    assert(func_call != NULL);
    assert(func_call->type == AST_FUNCTION_CALL);
    assert(strcmp(func_call->data.function_call.name, "import") == 0);
    assert(func_call->data.function_call.arguments == NULL);
    assert(func_call->data.function_call.argument_count == 0);
    
    // Add arguments
    ast_node* arg1 = ast_create_string_literal("file.txt", loc);
    ast_node* arg2 = ast_create_number_literal(100, loc);
    
    int result1 = ast_add_argument(func_call, arg1);
    int result2 = ast_add_argument(func_call, arg2);
    
    assert(result1 == 0);
    assert(result2 == 0);
    assert(func_call->data.function_call.argument_count == 2);
    assert(func_call->data.function_call.arguments[0] == arg1);
    assert(func_call->data.function_call.arguments[1] == arg2);
    
    ast_free(func_call);
    
    printf("✓ Function call node tests passed\n");
}

/**
 * @brief Test assignment nodes
 */
void test_assignment_nodes() {
    printf("Testing assignment nodes...\n");
    
    source_location loc = {5, 20, "test.xmd"};
    
    // Create assignment value
    ast_node* value = ast_create_string_literal("test value", loc);
    
    // Test regular assignment
    ast_node* assign = ast_create_assignment("var_name", BINOP_ASSIGN, value, loc);
    assert(assign != NULL);
    assert(assign->type == AST_ASSIGNMENT);
    assert(strcmp(assign->data.assignment.variable, "var_name") == 0);
    assert(assign->data.assignment.op == BINOP_ASSIGN);
    assert(assign->data.assignment.value == value);
    
    ast_free(assign);
    
    // Test += assignment
    ast_node* value2 = ast_create_string_literal("append", loc);
    ast_node* assign_add = ast_create_assignment("var2", BINOP_ASSIGN_ADD, value2, loc);
    assert(assign_add != NULL);
    assert(assign_add->data.assignment.op == BINOP_ASSIGN_ADD);
    
    ast_free(assign_add);
    
    printf("✓ Assignment node tests passed\n");
}

/**
 * @brief Test array literal nodes
 */
void test_array_nodes() {
    printf("Testing array literal nodes...\n");
    
    source_location loc = {6, 25, "test.xmd"};
    
    // Create array literal
    ast_node* array = ast_create_array_literal(loc);
    assert(array != NULL);
    assert(array->type == AST_ARRAY_LITERAL);
    assert(array->data.array_literal.elements == NULL);
    assert(array->data.array_literal.element_count == 0);
    
    // Add elements
    ast_node* elem1 = ast_create_string_literal("first", loc);
    ast_node* elem2 = ast_create_number_literal(42, loc);
    ast_node* elem3 = ast_create_boolean_literal(false, loc);
    
    assert(ast_add_element(array, elem1) == 0);
    assert(ast_add_element(array, elem2) == 0);
    assert(ast_add_element(array, elem3) == 0);
    
    assert(array->data.array_literal.element_count == 3);
    assert(array->data.array_literal.elements[0] == elem1);
    assert(array->data.array_literal.elements[1] == elem2);
    assert(array->data.array_literal.elements[2] == elem3);
    
    ast_free(array);
    
    printf("✓ Array node tests passed\n");
}

/**
 * @brief Test control flow nodes (conditional, loop)
 */
void test_control_flow_nodes() {
    printf("Testing control flow nodes...\n");
    
    source_location loc = {7, 30, "test.xmd"};
    
    // Test conditional
    ast_node* condition = ast_create_boolean_literal(true, loc);
    ast_node* conditional = ast_create_conditional(condition, loc);
    assert(conditional != NULL);
    assert(conditional->type == AST_CONDITIONAL);
    assert(conditional->data.conditional.condition == condition);
    assert(conditional->data.conditional.then_block == NULL);
    assert(conditional->data.conditional.else_block == NULL);
    
    // Test loop
    ast_node* iterable = ast_create_array_literal(loc);
    ast_node* loop = ast_create_loop("i", iterable, loc);
    assert(loop != NULL);
    assert(loop->type == AST_LOOP);
    assert(strcmp(loop->data.loop.variable, "i") == 0);
    assert(loop->data.loop.iterable == iterable);
    assert(loop->data.loop.body == NULL);
    
    ast_free(conditional);
    ast_free(loop);
    
    printf("✓ Control flow node tests passed\n");
}

/**
 * @brief Test block and program nodes with statements
 */
void test_block_nodes() {
    printf("Testing block and program nodes...\n");
    
    source_location loc = {8, 35, "test.xmd"};
    
    // Create block
    ast_node* block = ast_create_block(loc);
    assert(block != NULL);
    assert(block->type == AST_BLOCK);
    assert(block->data.block.statements == NULL);
    assert(block->data.block.statement_count == 0);
    
    // Add statements to block
    ast_node* stmt1 = ast_create_string_literal("statement 1", loc);
    ast_node* stmt2 = ast_create_number_literal(123, loc);
    
    assert(ast_add_statement(block, stmt1) == 0);
    assert(ast_add_statement(block, stmt2) == 0);
    
    assert(block->data.block.statement_count == 2);
    assert(block->data.block.statements[0] == stmt1);
    assert(block->data.block.statements[1] == stmt2);
    
    ast_free(block);
    
    printf("✓ Block node tests passed\n");
}

/**
 * @brief Test error conditions and edge cases
 */
void test_error_conditions() {
    printf("Testing error conditions...\n");
    
    source_location loc = {9, 40, "test.xmd"};
    
    // Test NULL parameter handling
    assert(ast_create_string_literal(NULL, loc) == NULL);
    assert(ast_create_variable_ref(NULL, loc) == NULL);
    assert(ast_create_identifier(NULL, loc) == NULL);
    
    // Test adding to NULL nodes
    ast_node* dummy = ast_create_string_literal("test", loc);
    assert(ast_add_argument(NULL, dummy) != 0);
    assert(ast_add_statement(NULL, dummy) != 0);
    assert(ast_add_element(NULL, dummy) != 0);
    
    ast_free(dummy);
    
    // Test freeing NULL node (should not crash)
    ast_free(NULL);
    
    printf("✓ Error condition tests passed\n");
}

/**
 * @brief Main test runner
 */
int main() {
    printf("Running AST Node Test Suite\n");
    printf("===========================\n");
    
    test_ast_node_creation();
    test_variable_nodes();
    test_operation_nodes();
    test_function_call_nodes();
    test_assignment_nodes();
    test_array_nodes();
    test_control_flow_nodes();
    test_block_nodes();
    test_error_conditions();
    
    printf("\n✅ All AST node tests passed!\n");
    return 0;
}