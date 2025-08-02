/**
 * @file test_ast_parser.c
 * @brief Test suite for AST parser system
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/ast_parser.h"
#include "../include/ast_node.h"
#include "../include/lexer_enhanced.h"

/**
 * @brief Test parsing simple literals
 */
void test_parse_literals() {
    printf("Testing literal parsing...\n");
    
    // Test string literal
    const char* input1 = "\"hello world\"";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    assert(ast1->type == AST_PROGRAM);
    assert(ast1->data.program.statement_count == 1);
    
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_LITERAL);
    assert(stmt1->data.literal.type == LITERAL_STRING);
    assert(strcmp(stmt1->data.literal.value.string_value, "hello world") == 0);
    
    // Test number literal
    const char* input2 = "42.5";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    assert(ast2->type == AST_PROGRAM);
    assert(ast2->data.program.statement_count == 1);
    
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_LITERAL);
    assert(stmt2->data.literal.type == LITERAL_NUMBER);
    assert(stmt2->data.literal.value.number_value == 42.5);
    
    // Test boolean literal
    const char* input3 = "true";
    token* tokens3 = lexer_enhanced_tokenize(input3, "test.xmd");
    ast_node* ast3 = ast_parse_program(tokens3);
    
    assert(ast3 != NULL);
    ast_node* stmt3 = ast3->data.program.statements[0];
    assert(stmt3->type == AST_LITERAL);
    assert(stmt3->data.literal.type == LITERAL_BOOLEAN);
    assert(stmt3->data.literal.value.boolean_value == true);
    
    ast_free(ast1);
    ast_free(ast2);
    ast_free(ast3);
    token_list_free(tokens1);
    token_list_free(tokens2);
    token_list_free(tokens3);
    
    printf("✓ Literal parsing tests passed\n");
}

/**
 * @brief Test parsing variable assignments
 */
void test_parse_assignments() {
    printf("Testing assignment parsing...\n");
    
    // Test simple assignment
    const char* input1 = "var = \"value\"";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    assert(ast1->type == AST_PROGRAM);
    assert(ast1->data.program.statement_count == 1);
    
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_ASSIGNMENT);
    assert(strcmp(stmt1->data.assignment.variable, "var") == 0);
    assert(stmt1->data.assignment.op == BINOP_ASSIGN);
    assert(stmt1->data.assignment.value->type == AST_LITERAL);
    
    // Test += assignment
    const char* input2 = "counter += 1";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_ASSIGNMENT);
    assert(strcmp(stmt2->data.assignment.variable, "counter") == 0);
    assert(stmt2->data.assignment.op == BINOP_ASSIGN_ADD);
    
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Assignment parsing tests passed\n");
}

/**
 * @brief Test parsing binary expressions
 */
void test_parse_binary_expressions() {
    printf("Testing binary expression parsing...\n");
    
    // Test simple addition
    const char* input1 = "1 + 2";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_BINARY_OP);
    assert(stmt1->data.binary_op.op == BINOP_ADD);
    assert(stmt1->data.binary_op.left->type == AST_LITERAL);
    assert(stmt1->data.binary_op.right->type == AST_LITERAL);
    
    // Test operator precedence (1 + 2 * 3 should be 1 + (2 * 3))
    const char* input2 = "1 + 2 * 3";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_BINARY_OP);
    assert(stmt2->data.binary_op.op == BINOP_ADD);
    
    // Left should be literal 1
    assert(stmt2->data.binary_op.left->type == AST_LITERAL);
    
    // Right should be multiplication (2 * 3)
    ast_node* right = stmt2->data.binary_op.right;
    assert(right->type == AST_BINARY_OP);
    assert(right->data.binary_op.op == BINOP_MUL);
    
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Binary expression parsing tests passed\n");
}

/**
 * @brief Test parsing function calls
 */
void test_parse_function_calls() {
    printf("Testing function call parsing...\n");
    
    // Test function call with no arguments
    const char* input1 = "print()";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt1->data.function_call.name, "print") == 0);
    assert(stmt1->data.function_call.argument_count == 0);
    
    // Test function call with arguments
    const char* input2 = "import(\"file.txt\", true)";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0]; 
    assert(stmt2->type == AST_FUNCTION_CALL);
    assert(strcmp(stmt2->data.function_call.name, "import") == 0);
    assert(stmt2->data.function_call.argument_count == 2);
    
    // First argument should be string literal
    ast_node* arg1 = stmt2->data.function_call.arguments[0];
    assert(arg1->type == AST_LITERAL);
    assert(arg1->data.literal.type == LITERAL_STRING);
    
    // Second argument should be boolean literal
    ast_node* arg2 = stmt2->data.function_call.arguments[1];
    assert(arg2->type == AST_LITERAL);
    assert(arg2->data.literal.type == LITERAL_BOOLEAN);
    
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Function call parsing tests passed\n");
}

/**
 * @brief Test parsing complex expressions
 */
void test_parse_complex_expressions() {
    printf("Testing complex expression parsing...\n");
    
    // Test parentheses
    const char* input1 = "(1 + 2) * 3";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_BINARY_OP);
    assert(stmt1->data.binary_op.op == BINOP_MUL);
    
    // Left should be addition (1 + 2)
    ast_node* left = stmt1->data.binary_op.left;
    assert(left->type == AST_BINARY_OP);
    assert(left->data.binary_op.op == BINOP_ADD);
    
    // Test comparison operators
    const char* input2 = "x == 5";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_BINARY_OP);
    assert(stmt2->data.binary_op.op == BINOP_EQ);
    
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Complex expression parsing tests passed\n");
}

/**
 * @brief Test parsing assignment with expressions
 */
void test_parse_assignment_expressions() {
    printf("Testing assignment with expressions...\n");
    
    // Test assignment with binary expression
    const char* input1 = "result = x + y * 2";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    assert(ast1 != NULL);
    ast_node* stmt1 = ast1->data.program.statements[0];
    assert(stmt1->type == AST_ASSIGNMENT);
    assert(strcmp(stmt1->data.assignment.variable, "result") == 0);
    assert(stmt1->data.assignment.op == BINOP_ASSIGN);
    
    // Value should be binary expression (x + y * 2)
    ast_node* value = stmt1->data.assignment.value;
    assert(value->type == AST_BINARY_OP);
    assert(value->data.binary_op.op == BINOP_ADD);
    
    // Test assignment with function call
    const char* input2 = "content = import(\"data.txt\")";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 != NULL);
    ast_node* stmt2 = ast2->data.program.statements[0];
    assert(stmt2->type == AST_ASSIGNMENT);
    assert(stmt2->data.assignment.value->type == AST_FUNCTION_CALL);
    
    ast_free(ast1);
    ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Assignment with expressions tests passed\n");
}

/**
 * @brief Test error handling in parser
 */
void test_parse_error_handling() {
    printf("Testing parser error handling...\n");
    
    // Test syntax error - missing closing parenthesis
    const char* input1 = "(1 + 2";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    ast_node* ast1 = ast_parse_program(tokens1);
    
    // Should return NULL or have error flag set
    assert(ast1 == NULL || parser_has_error());
    
    // Test syntax error - invalid assignment
    const char* input2 = "123 = value";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    ast_node* ast2 = ast_parse_program(tokens2);
    
    assert(ast2 == NULL || parser_has_error());
    
    if (ast1) ast_free(ast1);
    if (ast2) ast_free(ast2);
    token_list_free(tokens1);
    token_list_free(tokens2);
    
    printf("✓ Parser error handling tests passed\n");
}

/**
 * @brief Test parsing multiple statements
 */
void test_parse_multiple_statements() {
    printf("Testing multiple statement parsing...\n");
    
    const char* input = "x = 5\ny = x + 10\nresult = print(y)";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    ast_node* ast = ast_parse_program(tokens);
    
    assert(ast != NULL);
    assert(ast->type == AST_PROGRAM);
    assert(ast->data.program.statement_count == 3);
    
    // First statement: x = 5
    ast_node* stmt1 = ast->data.program.statements[0];
    assert(stmt1->type == AST_ASSIGNMENT);
    assert(strcmp(stmt1->data.assignment.variable, "x") == 0);
    
    // Second statement: y = x + 10
    ast_node* stmt2 = ast->data.program.statements[1];
    assert(stmt2->type == AST_ASSIGNMENT);
    assert(strcmp(stmt2->data.assignment.variable, "y") == 0);
    assert(stmt2->data.assignment.value->type == AST_BINARY_OP);
    
    // Third statement: result = print(y)
    ast_node* stmt3 = ast->data.program.statements[2];
    assert(stmt3->type == AST_ASSIGNMENT);
    assert(stmt3->data.assignment.value->type == AST_FUNCTION_CALL);
    
    ast_free(ast);
    token_list_free(tokens);
    
    printf("✓ Multiple statement parsing tests passed\n");
}

/**
 * @brief Main test runner
 */
int main() {
    printf("Running AST Parser Test Suite\n");
    printf("=============================\n");
    
    test_parse_literals();
    test_parse_assignments();
    test_parse_binary_expressions();
    test_parse_function_calls();
    test_parse_complex_expressions();
    test_parse_assignment_expressions();
    test_parse_error_handling();
    test_parse_multiple_statements();
    
    printf("\n✅ All AST parser tests passed!\n");
    return 0;
}