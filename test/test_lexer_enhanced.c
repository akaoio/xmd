/**
 * @file test_lexer_enhanced.c  
 * @brief Test suite for enhanced lexer with expression tokens
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/token.h"
#include "../include/lexer_enhanced.h"

/**
 * @brief Test basic tokenization of identifiers and literals
 */
void test_basic_tokenization() {
    printf("Testing basic tokenization...\n");
    
    const char* input = "variable = \"hello world\" 42 true";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    // First token: identifier "variable"
    assert(tokens->type == TOKEN_IDENTIFIER);
    assert(strcmp(tokens->value, "variable") == 0);
    assert(tokens->line == 1);
    assert(tokens->column == 1);
    
    // Second token: operator "="
    token* current = tokens->next;
    assert(current != NULL);
    assert(current->type == TOKEN_OPERATOR);
    assert(strcmp(current->value, "=") == 0);
    
    // Third token: string literal
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_STRING);
    assert(strcmp(current->value, "hello world") == 0);
    
    // Fourth token: number literal
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_NUMBER);
    assert(strcmp(current->value, "42") == 0);
    
    // Fifth token: boolean literal
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_BOOLEAN);
    assert(strcmp(current->value, "true") == 0);
    
    // Sixth token: EOF
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_EOF);
    
    token_list_free(tokens);
    printf("✓ Basic tokenization tests passed\n");
}

/**
 * @brief Test operator tokenization
 */
void test_operator_tokenization() {
    printf("Testing operator tokenization...\n");
    
    const char* input = "+ - * / == != <= >= < > && || ! += =";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    const char* expected_ops[] = {"+", "-", "*", "/", "==", "!=", "<=", ">=", 
                                  "<", ">", "&&", "||", "!", "+=", "="};
    int op_count = sizeof(expected_ops) / sizeof(expected_ops[0]);
    
    token* current = tokens;
    for (int i = 0; i < op_count; i++) {
        assert(current != NULL);
        assert(current->type == TOKEN_OPERATOR);
        assert(strcmp(current->value, expected_ops[i]) == 0);
        current = current->next;
    }
    
    // Should end with EOF
    assert(current != NULL);
    assert(current->type == TOKEN_EOF);
    
    token_list_free(tokens);
    printf("✓ Operator tokenization tests passed\n");
}

/**
 * @brief Test string literal tokenization with various quote types
 */
void test_string_literals() {
    printf("Testing string literal tokenization...\n");
    
    const char* input = "\"double quotes\" 'single quotes' \"with spaces\" \"\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    // First string
    assert(tokens->type == TOKEN_STRING);
    assert(strcmp(tokens->value, "double quotes") == 0);
    
    // Second string
    token* current = tokens->next;
    assert(current != NULL);
    assert(current->type == TOKEN_STRING);
    assert(strcmp(current->value, "single quotes") == 0);
    
    // Third string
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_STRING);
    assert(strcmp(current->value, "with spaces") == 0);
    
    // Empty string
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_STRING);
    assert(strcmp(current->value, "") == 0);
    
    token_list_free(tokens);
    printf("✓ String literal tests passed\n");
}

/**
 * @brief Test number literal tokenization
 */
void test_number_literals() {
    printf("Testing number literal tokenization...\n");
    
    const char* input = "42 3.14 0 -5 10.0";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    const char* expected_numbers[] = {"42", "3.14", "0", "-5", "10.0"};
    int num_count = sizeof(expected_numbers) / sizeof(expected_numbers[0]);
    
    token* current = tokens;
    for (int i = 0; i < num_count; i++) {
        if (i == 3) {  // -5 is tokenized as operator "-" and number "5"
            assert(current->type == TOKEN_OPERATOR);
            assert(strcmp(current->value, "-") == 0);
            current = current->next;
            assert(current->type == TOKEN_NUMBER);
            assert(strcmp(current->value, "5") == 0);
        } else {
            assert(current != NULL);
            assert(current->type == TOKEN_NUMBER);
            assert(strcmp(current->value, expected_numbers[i]) == 0);
        }
        current = current->next;
    }
    
    token_list_free(tokens);
    printf("✓ Number literal tests passed\n");
}

/**
 * @brief Test boolean literal tokenization
 */
void test_boolean_literals() {
    printf("Testing boolean literal tokenization...\n");
    
    const char* input = "true false True False TRUE FALSE";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    // true
    assert(tokens->type == TOKEN_BOOLEAN);
    assert(strcmp(tokens->value, "true") == 0);
    
    // false
    token* current = tokens->next;
    assert(current != NULL);
    assert(current->type == TOKEN_BOOLEAN);
    assert(strcmp(current->value, "false") == 0);
    
    // The rest should be identifiers (case-sensitive)
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_IDENTIFIER);
    assert(strcmp(current->value, "True") == 0);
    
    token_list_free(tokens);
    printf("✓ Boolean literal tests passed\n");
}

/**
 * @brief Test array literal tokenization
 */
void test_array_literals() {
    printf("Testing array literal tokenization...\n");
    
    const char* input = "[1, 2, \"three\", true]";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    // [
    assert(tokens->type == TOKEN_LBRACKET);
    assert(strcmp(tokens->value, "[") == 0);
    
    // 1
    token* current = tokens->next;
    assert(current != NULL);
    assert(current->type == TOKEN_NUMBER);
    assert(strcmp(current->value, "1") == 0);
    
    // ,
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_COMMA);
    assert(strcmp(current->value, ",") == 0);
    
    // 2
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_NUMBER);
    assert(strcmp(current->value, "2") == 0);
    
    // Skip to ]
    while (current && current->type != TOKEN_RBRACKET) {
        current = current->next;
    }
    assert(current != NULL);
    assert(current->type == TOKEN_RBRACKET);
    assert(strcmp(current->value, "]") == 0);
    
    token_list_free(tokens);
    printf("✓ Array literal tests passed\n");
}

/**
 * @brief Test function call tokenization
 */
void test_function_calls() {
    printf("Testing function call tokenization...\n");
    
    const char* input = "import(\"file.txt\") print(var + 5)";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    // import
    assert(tokens->type == TOKEN_IDENTIFIER);
    assert(strcmp(tokens->value, "import") == 0);
    
    // (
    token* current = tokens->next;
    assert(current != NULL);
    assert(current->type == TOKEN_LPAREN);
    assert(strcmp(current->value, "(") == 0);
    
    // "file.txt"
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_STRING);
    assert(strcmp(current->value, "file.txt") == 0);
    
    // )
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_RPAREN);
    assert(strcmp(current->value, ")") == 0);
    
    token_list_free(tokens);
    printf("✓ Function call tests passed\n");
}

/**
 * @brief Test line and column tracking
 */
void test_location_tracking() {
    printf("Testing location tracking...\n");
    
    const char* input = "line1\nline2 var\n  line3";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    // line1 (line 1, column 1)
    assert(tokens->type == TOKEN_IDENTIFIER);
    assert(strcmp(tokens->value, "line1") == 0);
    assert(tokens->line == 1);
    assert(tokens->column == 1);
    
    // line2 (line 2, column 1)
    token* current = tokens->next;
    assert(current != NULL);
    assert(current->type == TOKEN_IDENTIFIER);
    assert(strcmp(current->value, "line2") == 0);
    assert(current->line == 2);
    assert(current->column == 1);
    
    // var (line 2, column 7)
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_IDENTIFIER);
    assert(strcmp(current->value, "var") == 0);
    assert(current->line == 2);
    assert(current->column == 7);
    
    // line3 (line 3, column 3 - after 2 spaces)
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_IDENTIFIER);
    assert(strcmp(current->value, "line3") == 0);
    assert(current->line == 3);
    assert(current->column == 3);
    
    token_list_free(tokens);
    printf("✓ Location tracking tests passed\n");
}

/**
 * @brief Test error conditions and malformed input
 */
void test_error_conditions() {
    printf("Testing error conditions...\n");
    
    // Test NULL input
    token* tokens = lexer_enhanced_tokenize(NULL, "test.xmd");
    assert(tokens == NULL);
    
    // Test empty input
    tokens = lexer_enhanced_tokenize("", "test.xmd");
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_EOF);
    token_list_free(tokens);
    
    // Test unterminated string
    tokens = lexer_enhanced_tokenize("\"unterminated", "test.xmd");
    assert(tokens != NULL);
    // Should still create a token but may be marked as error
    token_list_free(tokens);
    
    printf("✓ Error condition tests passed\n");
}

/**
 * @brief Test XMD directive tokenization
 */
void test_xmd_directives() {
    printf("Testing XMD directive tokenization...\n");
    
    const char* input = "<!-- xmd set var = \"value\" -->";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    // Should recognize as XMD directive
    assert(tokens->type == TOKEN_XMD_DIRECTIVE);
    assert(strstr(tokens->value, "set var = \"value\"") != NULL);
    
    token_list_free(tokens);
    printf("✓ XMD directive tests passed\n");
}

/**
 * @brief Main test runner
 */
int main() {
    printf("Running Enhanced Lexer Test Suite\n");
    printf("=================================\n");
    
    test_basic_tokenization();
    test_operator_tokenization();
    test_string_literals();
    test_number_literals();
    test_boolean_literals();
    test_array_literals();
    test_function_calls();
    test_location_tracking();
    test_error_conditions();
    
    printf("\n✅ All enhanced lexer tests passed!\n");
    return 0;
}