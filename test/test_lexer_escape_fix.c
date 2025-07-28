/**
 * @file test_lexer_escape_fix.c
 * @brief Test suite for escape sequence parsing fix in lexer
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
 * @brief Test that lexer doesn't truncate at escaped quotes
 */
void test_escaped_quotes_no_truncation() {
    printf("Testing escaped quotes don't truncate tokens...\n");
    
    // This was the exact issue from level 5 - lexer truncated at \"
    const char* input = "\"find src -type f -exec grep -liE \\\"debug|test\\\" {} +\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    
    // The key test: token should contain the full string, not truncated at first \"
    const char* expected = "find src -type f -exec grep -liE \\\"debug|test\\\" {} +";
    assert(strcmp(tokens->value, expected) == 0);
    
    // Token should end properly
    assert(tokens->next != NULL);
    assert(tokens->next->type == TOKEN_EOF);
    
    token_list_free(tokens);
    printf("✓ Escaped quotes no truncation test passed\n");
}

/**
 * @brief Test that lexer properly handles escaped backslashes
 */
void test_escaped_backslashes_no_truncation() {
    printf("Testing escaped backslashes don't truncate tokens...\n");
    
    const char* input = "\"path\\\\to\\\\file\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    
    // Should preserve both backslashes in each escape sequence
    assert(strcmp(tokens->value, "path\\\\to\\\\file") == 0);
    
    token_list_free(tokens);
    printf("✓ Escaped backslashes no truncation test passed\n");
}

/**
 * @brief Test mixed escape sequences
 */
void test_mixed_escapes_no_truncation() {
    printf("Testing mixed escape sequences don't truncate...\n");
    
    const char* input = "\"test \\\"quoted\\\" and \\\\backslash\\\\\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    
    // Should preserve entire string with all escape sequences
    assert(strcmp(tokens->value, "test \\\"quoted\\\" and \\\\backslash\\\\") == 0);
    
    token_list_free(tokens);
    printf("✓ Mixed escape sequences no truncation test passed\n");
}

/**
 * @brief Test single quotes with escape sequences
 */
void test_single_quotes_escapes() {
    printf("Testing single quote escape sequences...\n");
    
    const char* input = "'can\\'t and won\\'t'";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    
    // Should preserve escape sequences in single quotes
    assert(strcmp(tokens->value, "can\\'t and won\\'t") == 0);
    
    token_list_free(tokens);
    printf("✓ Single quote escape sequences test passed\n");
}

/**
 * @brief Test string ending with escape sequence
 */
void test_string_ending_with_escape() {
    printf("Testing string ending with escape sequence...\n");
    
    const char* input = "\"ends with quote\\\"\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    
    // Should include the escaped quote at the end
    assert(strcmp(tokens->value, "ends with quote\\\"") == 0);
    
    token_list_free(tokens);
    printf("✓ String ending with escape test passed\n");
}

/**
 * @brief Test that actual quote after escape doesn't end string prematurely
 */
void test_quote_after_escape() {
    printf("Testing quote after escape doesn't end string...\n");
    
    const char* input = "\"before\\\"after\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    assert(tokens != NULL);
    assert(tokens->type == TOKEN_STRING);
    
    // The escaped quote should not terminate the string
    assert(strcmp(tokens->value, "before\\\"after") == 0);
    
    token_list_free(tokens);
    printf("✓ Quote after escape test passed\n");
}

/**
 * @brief Main test runner
 */
int main() {
    printf("=== Lexer Escape Sequence Fix Test Suite ===\n");
    
    test_escaped_quotes_no_truncation();
    test_escaped_backslashes_no_truncation();
    test_mixed_escapes_no_truncation();
    test_single_quotes_escapes();
    test_string_ending_with_escape();
    test_quote_after_escape();
    
    printf("\n✅ All lexer escape sequence fix tests passed!\n");
    return 0;
}