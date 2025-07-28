/**
 * @file test_escape_sequences.c
 * @brief Test suite for escape sequence parsing in lexer
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
 * @brief Test basic escape sequences in tokenization
 */
void test_basic_escape_sequences() {
    printf("Testing basic escape sequences in tokenization...\n");
    
    // Test that lexer correctly handles escaped quotes without truncating
    const char* input = "\"string with \\\"quotes\\\" inside\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    // Lexer should preserve escape sequences as-is
    assert(strcmp(tokens->value, "string with \\\"quotes\\\" inside") == 0);
    
    token_list_free(tokens);
    printf("✓ Basic escape sequences test passed\n");
}

/**
 * @brief Test backslash escaping in tokenization
 */
void test_backslash_escaping() {
    printf("Testing backslash escaping in tokenization...\n");
    
    // Test that lexer correctly handles escaped backslashes
    const char* input = "\"path\\\\to\\\\file\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    // Lexer should preserve escape sequences as-is
    assert(strcmp(tokens->value, "path\\\\to\\\\file") == 0);
    
    token_list_free(tokens);
    printf("✓ Backslash escaping test passed\n");
}

/**
 * @brief Test mixed escape sequences
 */
void test_mixed_escape_sequences() {
    printf("Testing mixed escape sequences...\n");
    
    // Test combination of escaped quotes and backslashes
    const char* input = "\"command \\\"grep -E \\\\\\\"pattern\\\\\\\"\\\" file\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    assert(strcmp(tokens->value, "command \"grep -E \\\"pattern\\\"\" file") == 0);
    
    token_list_free(tokens);
    printf("✓ Mixed escape sequences test passed\n");
}

/**
 * @brief Test single quotes with escape sequences
 */
void test_single_quote_escapes() {
    printf("Testing single quote escape sequences...\n");
    
    // Test escaped single quotes
    const char* input = "'string with \\'quotes\\' inside'";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    assert(strcmp(tokens->value, "string with 'quotes' inside") == 0);
    
    token_list_free(tokens);
    printf("✓ Single quote escape sequences test passed\n");
}

/**
 * @brief Test complex grep command with escape sequences
 */
void test_grep_command_escapes() {
    printf("Testing grep command escape sequences...\n");
    
    // This tests the exact pattern from level 5
    const char* input = "\"find src -type f -exec grep -liE \\\"debug|test\\\" {} +\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    assert(strcmp(tokens->value, "find src -type f -exec grep -liE \"debug|test\" {} +") == 0);
    
    token_list_free(tokens);
    printf("✓ Grep command escape sequences test passed\n");
}

/**
 * @brief Test newline and tab escape sequences
 */
void test_newline_tab_escapes() {
    printf("Testing newline and tab escape sequences...\n");
    
    // Test \\n and \\t escapes
    const char* input = "\"line1\\nline2\\tindented\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    assert(strcmp(tokens->value, "line1\nline2\tindented") == 0);
    
    token_list_free(tokens);
    printf("✓ Newline and tab escape sequences test passed\n");
}

/**
 * @brief Test edge cases with escape sequences
 */
void test_escape_edge_cases() {
    printf("Testing escape sequence edge cases...\n");
    
    // Test string ending with backslash (should not crash)
    const char* input1 = "\"string\\\\\"";
    token* tokens1 = lexer_enhanced_tokenize(input1, "test.xmd");
    
    assert(tokens1 != NULL);
    assert(tokens1->type == TOKEN_STRING);
    assert(strcmp(tokens1->value, "string\\") == 0);
    
    // Test empty string with escape
    const char* input2 = "\"\\\"\\\"\"";
    token* tokens2 = lexer_enhanced_tokenize(input2, "test.xmd");
    
    assert(tokens2 != NULL);
    assert(tokens2->type == TOKEN_STRING);
    assert(strcmp(tokens2->value, "\"\"") == 0);
    
    token_list_free(tokens1);
    token_list_free(tokens2);
    printf("✓ Escape sequence edge cases test passed\n");
}

/**
 * @brief Test multiple string literals with escapes
 */
void test_multiple_strings_with_escapes() {
    printf("Testing multiple string literals with escapes...\n");
    
    const char* input = "\"first\\\"quote\" \"second\\\\path\" \"third\\nlines\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    
    // First string
    assert(tokens->type == TOKEN_STRING);
    assert(strcmp(tokens->value, "first\"quote") == 0);
    
    // Second string
    token* current = tokens->next;
    assert(current != NULL);
    assert(current->type == TOKEN_STRING);
    assert(strcmp(current->value, "second\\path") == 0);
    
    // Third string
    current = current->next;
    assert(current != NULL);
    assert(current->type == TOKEN_STRING);
    assert(strcmp(current->value, "third\nlines") == 0);
    
    token_list_free(tokens);
    printf("✓ Multiple string literals with escapes test passed\n");
}

/**
 * @brief Main test runner
 */
int main() {
    printf("=== Escape Sequence Test Suite ===\n");
    
    test_basic_escape_sequences();
    test_backslash_escaping();
    test_mixed_escape_sequences();
    test_single_quote_escapes();
    test_grep_command_escapes();
    test_newline_tab_escapes();
    test_escape_edge_cases();
    test_multiple_strings_with_escapes();
    
    printf("\n✅ All escape sequence tests passed!\n");
    return 0;
}