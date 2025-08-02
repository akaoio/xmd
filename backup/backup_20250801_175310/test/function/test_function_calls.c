/**
 * @file test_function_calls.c
 * @brief Test suite for function call parsing
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
 * @brief Test join function parsing with array literal
 */
void test_join_function_parsing() {
    printf("Testing join function parsing...\n");
    
    // Test: join ["a", "b", "c"]
    const char* input = "join [\"a\", \"b\", \"c\"]";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    assert(tokens != NULL);
    
    ast_node* ast = ast_parse_program(tokens);
    assert(ast != NULL);
    assert(ast->type == AST_PROGRAM);
    assert(ast->data.program.statement_count == 1);
    
    // Check that it's parsed as a function call
    ast_node* stmt = ast->data.program.statements[0];
    assert(stmt->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt->data.function_call.name, "join") == 0);
    assert(stmt->data.function_call.argument_count == 1);
    
    // Check that the argument is an array literal
    ast_node* arg = stmt->data.function_call.arguments[0];
    assert(arg->type == AST_ARRAY_LITERAL);
    assert(arg->data.array_literal.element_count == 3);
    
    // Check array elements
    assert(arg->data.array_literal.elements[0]->type == AST_LITERAL);
    assert(arg->data.array_literal.elements[0]->data.literal.type == LITERAL_STRING);
    assert(strcmp(arg->data.array_literal.elements[0]->data.literal.value.string_value, "a") == 0);
    assert(arg->data.array_literal.elements[1]->type == AST_LITERAL);
    assert(arg->data.array_literal.elements[1]->data.literal.type == LITERAL_STRING);
    assert(strcmp(arg->data.array_literal.elements[1]->data.literal.value.string_value, "b") == 0);
    assert(arg->data.array_literal.elements[2]->type == AST_LITERAL);
    assert(arg->data.array_literal.elements[2]->data.literal.type == LITERAL_STRING);
    assert(strcmp(arg->data.array_literal.elements[2]->data.literal.value.string_value, "c") == 0);
    
    // Cleanup
    ast_free(ast);
    token_list_free(tokens);
    
    printf("✓ Join function parsing test passed\n");
}

/**
 * @brief Test join function parsing with parentheses
 */
void test_join_function_with_parentheses() {
    printf("Testing join function with parentheses...\n");
    
    // Test: join(["x", "y"])
    const char* input = "join([\"x\", \"y\"])";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    assert(tokens != NULL);
    
    ast_node* ast = ast_parse_program(tokens);
    assert(ast != NULL);
    assert(ast->type == AST_PROGRAM);
    assert(ast->data.program.statement_count == 1);
    
    // Check that it's parsed as a function call
    ast_node* stmt = ast->data.program.statements[0];
    assert(stmt->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt->data.function_call.name, "join") == 0);
    assert(stmt->data.function_call.argument_count == 1);
    
    // Check that the argument is an array literal
    ast_node* arg = stmt->data.function_call.arguments[0];
    assert(arg->type == AST_ARRAY_LITERAL);
    assert(arg->data.array_literal.element_count == 2);
    
    // Cleanup
    ast_free(ast);
    token_list_free(tokens);
    
    printf("✓ Join function with parentheses test passed\n");
}

/**
 * @brief Test join function parsing with empty array
 */
void test_join_empty_array_parsing() {
    printf("Testing join function with empty array...\n");
    
    // Test: join []
    const char* input = "join []";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    assert(tokens != NULL);
    
    ast_node* ast = ast_parse_program(tokens);
    assert(ast != NULL);
    assert(ast->type == AST_PROGRAM);
    assert(ast->data.program.statement_count == 1);
    
    // Check that it's parsed as a function call
    ast_node* stmt = ast->data.program.statements[0];
    assert(stmt->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt->data.function_call.name, "join") == 0);
    assert(stmt->data.function_call.argument_count == 1);
    
    // Check that the argument is an empty array literal
    ast_node* arg = stmt->data.function_call.arguments[0];
    assert(arg->type == AST_ARRAY_LITERAL);
    assert(arg->data.array_literal.element_count == 0);
    
    // Cleanup
    ast_free(ast);
    token_list_free(tokens);
    
    printf("✓ Join empty array parsing test passed\n");
}

/**
 * @brief Test join function parsing with variable reference
 */
void test_join_variable_parsing() {
    printf("Testing join function with variable...\n");
    
    // Test: join myarray
    const char* input = "join myarray";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    assert(tokens != NULL);
    
    ast_node* ast = ast_parse_program(tokens);
    assert(ast != NULL);
    assert(ast->type == AST_PROGRAM);
    assert(ast->data.program.statement_count == 1);
    
    // Check that it's parsed as a function call
    ast_node* stmt = ast->data.program.statements[0];
    assert(stmt->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt->data.function_call.name, "join") == 0);
    assert(stmt->data.function_call.argument_count == 1);
    
    // Check that the argument is a variable reference
    ast_node* arg = stmt->data.function_call.arguments[0];
    assert(arg->type == AST_VARIABLE_REF);
    assert(strcmp(arg->data.variable_ref.name, "myarray") == 0);
    
    // Cleanup
    ast_free(ast);
    token_list_free(tokens);
    
    printf("✓ Join variable parsing test passed\n");
}

/**
 * @brief Test join function parsing with custom separator
 */
void test_join_custom_separator_parsing() {
    printf("Testing join function with custom separator...\n");
    
    // Test: join arr "|" 
    const char* input = "join arr \"|\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    assert(tokens != NULL);
    
    ast_node* ast = ast_parse_program(tokens);
    assert(ast != NULL);
    assert(ast->type == AST_PROGRAM);
    assert(ast->data.program.statement_count == 1);
    
    // Check that it's parsed as a function call
    ast_node* stmt = ast->data.program.statements[0];
    assert(stmt->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt->data.function_call.name, "join") == 0);
    assert(stmt->data.function_call.argument_count == 2);
    
    // Check first argument is variable reference
    ast_node* arg1 = stmt->data.function_call.arguments[0];
    assert(arg1->type == AST_VARIABLE_REF);
    assert(strcmp(arg1->data.variable_ref.name, "arr") == 0);
    
    // Check second argument is string literal  
    ast_node* arg2 = stmt->data.function_call.arguments[1];
    assert(arg2->type == AST_LITERAL);
    assert(arg2->data.literal.type == LITERAL_STRING);
    assert(strcmp(arg2->data.literal.value.string_value, "|") == 0);
    
    // Cleanup
    ast_free(ast);
    token_list_free(tokens);
    
    printf("✓ Join custom separator parsing test passed\n");
}

/**
 * @brief Test other function parsing (import, exec)
 */
void test_other_function_parsing() {
    printf("Testing other function parsing...\n");
    
    // Test import function
    const char* input1 = "import \"file.md\"";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt1->data.function_call.name, "import") == 0);
    assert(stmt1->data.function_call.argument_count == 1);
    assert(stmt1->data.function_call.arguments[0]->type == AST_LITERAL);
    
    // Test exec function
    const char* input2 = "exec \"echo hello\"";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt2->data.function_call.name, "exec") == 0);
    assert(stmt2->data.function_call.argument_count == 1);
    assert(stmt2->data.function_call.arguments[0]->type == AST_LITERAL);
    
    // Cleanup
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Other function parsing test passed\n");
}

/**
 * @brief Test array indexing parsing
 */
void test_array_indexing_parsing() {
    printf("Testing array indexing parsing...\n");
    
    // Test: arr[0]
    const char* input1 = "arr[0]";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    assert(tokens1 != NULL);
    
    ast_node* ast1 = ast_parse_program(tokens1);
    assert(ast1 != NULL);
    assert(ast1->type == AST_PROGRAM);
    assert(ast1->data.program.statement_count == 1);
    
    // Check that it's parsed as array access
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_ARRAY_ACCESS);
    
    // Check array expression is variable reference
    ast_node* array_expr = stmt1->data.array_access.array_expr;
    assert(array_expr->type == AST_VARIABLE_REF);
    assert(strcmp(array_expr->data.variable_ref.name, "arr") == 0);
    
    // Check index expression is number literal
    ast_node* index_expr = stmt1->data.array_access.index_expr;
    assert(index_expr->type == AST_LITERAL);
    assert(index_expr->data.literal.type == LITERAL_NUMBER);
    assert(index_expr->data.literal.value.number_value == 0.0);
    
    // Test: items[i+1]
    const char* input2 = "items[i+1]";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_ARRAY_ACCESS);
    
    // Array should be "items"
    assert(stmt2->data.array_access.array_expr->type == AST_VARIABLE_REF);
    assert(strcmp(stmt2->data.array_access.array_expr->data.variable_ref.name, "items") == 0);
    
    // Index should be binary expression (i+1)
    assert(stmt2->data.array_access.index_expr->type == AST_BINARY_OP);
    assert(stmt2->data.array_access.index_expr->data.binary_op.op == BINOP_ADD);
    
    // Cleanup
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Array indexing parsing test passed\n");
}

/**
 * @brief Test array indexing in assignments
 */
void test_array_indexing_assignments() {
    printf("Testing array indexing in assignments...\n");
    
    // Test: element = arr[0]
    const char* input1 = "element = arr[0]";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_ASSIGNMENT);
    assert(strcmp(stmt1->data.assignment.variable, "element") == 0);
    assert(stmt1->data.assignment.op == BINOP_ASSIGN);
    
    // Value should be array access
    assert(stmt1->data.assignment.value->type == AST_ARRAY_ACCESS);
    
    // Test: result = first[0] + " - " + second[1]
    const char* input2 = "result = first[0] + \" - \" + second[1]";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_ASSIGNMENT);
    
    // Value should be binary expression with array accesses
    assert(stmt2->data.assignment.value->type == AST_BINARY_OP);
    assert(stmt2->data.assignment.value->data.binary_op.op == BINOP_ADD);
    
    // Cleanup
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Array indexing assignments test passed\n");
}

/**
 * @brief Test array indexing error cases
 */
void test_array_indexing_errors() {
    printf("Testing array indexing error cases...\n");
    
    // Test: arr[  (missing closing bracket)
    const char* input1 = "arr[0";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    // Should either be NULL or parser should have error
    assert(ast1 == NULL || parser_has_error());
    
    // Test: arr[] (empty index)
    const char* input2 = "arr[]";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    // Should either be NULL or parser should have error
    assert(ast2 == NULL || parser_has_error());
    
    // Cleanup
    if (ast1) ast_free(ast1);
    if (ast2) ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Array indexing error cases test passed\n");
}

/**
 * @brief Test comprehensive array literal parsing
 */
void test_comprehensive_array_literals() {
    printf("Testing comprehensive array literals...\n");
    
    // Test: Mixed type array ["string", 42, true]
    const char* input1 = "[\"string\", 42, true]";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_ARRAY_LITERAL);
    assert(stmt1->data.array_literal.element_count == 3);
    
    // Check string element
    assert(stmt1->data.array_literal.elements[0]->type == AST_LITERAL);
    assert(stmt1->data.array_literal.elements[0]->data.literal.type == LITERAL_STRING);
    assert(strcmp(stmt1->data.array_literal.elements[0]->data.literal.value.string_value, "string") == 0);
    
    // Check number element
    assert(stmt1->data.array_literal.elements[1]->type == AST_LITERAL);
    assert(stmt1->data.array_literal.elements[1]->data.literal.type == LITERAL_NUMBER);
    assert(stmt1->data.array_literal.elements[1]->data.literal.value.number_value == 42.0);
    
    // Check boolean element
    assert(stmt1->data.array_literal.elements[2]->type == AST_LITERAL);
    assert(stmt1->data.array_literal.elements[2]->data.literal.type == LITERAL_BOOLEAN);
    assert(stmt1->data.array_literal.elements[2]->data.literal.value.boolean_value == true);
    
    // Test: Single element array ["single"]
    const char* input2 = "[\"single\"]";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_ARRAY_LITERAL);
    assert(stmt2->data.array_literal.element_count == 1);
    
    // Test: Array with variables and expressions [var, x+1]
    const char* input3 = "[var, x+1]";
    token* tokens3 = lexer_enhanced_tokenize(input3, "test.xmd");
    ast_node* ast3 = ast_parse_program(tokens3);
    
    assert(ast3 != NULL);
    ast_node* stmt3 = ast3->data.program.statements[0];
    assert(stmt3->type == AST_ARRAY_LITERAL);
    assert(stmt3->data.array_literal.element_count == 2);
    
    // First element should be variable reference
    assert(stmt3->data.array_literal.elements[0]->type == AST_VARIABLE_REF);
    assert(strcmp(stmt3->data.array_literal.elements[0]->data.variable_ref.name, "var") == 0);
    
    // Second element should be binary expression
    assert(stmt3->data.array_literal.elements[1]->type == AST_BINARY_OP);
    assert(stmt3->data.array_literal.elements[1]->data.binary_op.op == BINOP_ADD);
    
    // Cleanup
    ast_free(ast1);
    ast_free(ast2);
    ast_free(ast3);
    token_list_free(tokens1);
    token_list_free(tokens2);
    token_list_free(tokens3);
    
    printf("✓ Comprehensive array literals test passed\n");
}

/**
 * @brief Test array indexing edge cases
 */
void test_array_indexing_edge_cases() {
    printf("Testing array indexing edge cases...\n");
    
    // Test: Simple array indexing with variable
    const char* input1 = "matrix[0]";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    ast_node* stmt1 = ast1->data.program.statements[0];
    // This should parse as array access
    assert(stmt1->type == AST_ARRAY_ACCESS);
    assert(stmt1->data.array_access.array_expr->type == AST_VARIABLE_REF);
    
    // Test: Complex index expressions arr[x*2+1]
    const char* input2 = "arr[x*2+1]";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_ARRAY_ACCESS);
    // Index should be complex binary expression
    assert(stmt2->data.array_access.index_expr->type == AST_BINARY_OP);
    
    // Skip complex array literal indexing for now
    
    // Cleanup
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Array indexing edge cases test passed\n");
}

/**
 * @brief Test function parsing edge cases
 */
void test_function_parsing_edge_cases() {
    printf("Testing function parsing edge cases...\n");
    
    // Test function with multiple arguments (if supported)
    const char* input1 = "join([\"a\"])";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt1->data.function_call.name, "join") == 0);
    
    // Test function with complex array
    const char* input2 = "join [\"first\", \"second with spaces\", \"third\"]";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt2->data.function_call.name, "join") == 0);
    assert(stmt2->data.function_call.argument_count == 1);
    
    ast_node* arg = stmt2->data.function_call.arguments[0];
    assert(arg->type == AST_ARRAY_LITERAL);
    assert(arg->data.array_literal.element_count == 3);
    assert(strcmp(arg->data.array_literal.elements[1]->data.literal.value.string_value, "second with spaces") == 0);
    
    // Cleanup
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Function parsing edge cases test passed\n");
}

/**
 * @brief Main test runner
 */
int main() {
    printf("=== Function Call Parsing Test Suite ===\n");
    
    test_join_function_parsing();
    test_join_function_with_parentheses();
    test_join_empty_array_parsing();
    test_join_variable_parsing();
    test_join_custom_separator_parsing();
    test_other_function_parsing();
    test_array_indexing_parsing();
    test_array_indexing_assignments();
    test_array_indexing_errors();
    test_function_parsing_edge_cases();
    test_comprehensive_array_literals();
    test_array_indexing_edge_cases();
    
    printf("\n✅ All function call parsing tests passed!\n");
    return 0;
}