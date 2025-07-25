/**
 * @file test_token.c
 * @brief Comprehensive tests for token system
 * @author XMD Team
 *
 * Tests all token functionality including creation, destruction,
 * memory management, and type handling.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "token.h"

/**
 * @brief Test token creation with different types
 */
void test_token_create_basic(void) {
    // Test TEXT token creation
    token* t1 = token_create(TOKEN_TEXT, "Hello World", 1, 5);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_TEXT);
    assert(strcmp(t1->value, "Hello World") == 0);
    assert(t1->line == 1);
    assert(t1->column == 5);
    assert(t1->next == NULL);
    token_destroy(t1);
    
    // Test HEADING token creation
    token* t2 = token_create(TOKEN_HEADING, "# Main Title", 2, 1);
    assert(t2 != NULL);
    assert(t2->type == TOKEN_HEADING);
    assert(strcmp(t2->value, "# Main Title") == 0);
    assert(t2->line == 2);
    assert(t2->column == 1);
    token_destroy(t2);
    
    // Test HTML_COMMENT token creation
    token* t3 = token_create(TOKEN_HTML_COMMENT, "<!-- comment -->", 3, 10);
    assert(t3 != NULL);
    assert(t3->type == TOKEN_HTML_COMMENT);
    assert(strcmp(t3->value, "<!-- comment -->") == 0);
    token_destroy(t3);
}

/**
 * @brief Test token creation with NULL values
 */
void test_token_create_null_handling(void) {
    // Test with NULL value
    token* t1 = token_create(TOKEN_TEXT, NULL, 1, 1);
    assert(t1 != NULL);
    assert(t1->value == NULL);
    assert(t1->type == TOKEN_TEXT);
    token_destroy(t1);
    
    // Test with empty string
    token* t2 = token_create(TOKEN_TEXT, "", 1, 1);
    assert(t2 != NULL);
    assert(t2->value != NULL);
    assert(strlen(t2->value) == 0);
    token_destroy(t2);
}

/**
 * @brief Test token creation with very long values
 */
void test_token_create_long_values(void) {
    // Create a long value (1000 characters)
    char* long_value = malloc(1001);
    for (int i = 0; i < 1000; i++) {
        long_value[i] = 'A' + (i % 26);
    }
    long_value[1000] = '\0';
    
    token* t = token_create(TOKEN_TEXT, long_value, 1, 1);
    assert(t != NULL);
    assert(strcmp(t->value, long_value) == 0);
    assert(strlen(t->value) == 1000);
    
    token_destroy(t);
    free(long_value);
}

/**
 * @brief Test token destruction and memory cleanup
 */
void test_token_destroy(void) {
    // Create token and verify destruction doesn't crash
    token* t = token_create(TOKEN_TEXT, "Test", 1, 1);
    assert(t != NULL);
    token_destroy(t);
    
    // Test destroying NULL token (should not crash)
    token_destroy(NULL);
}

/**
 * @brief Test token copying functionality
 */
void test_token_copy(void) {
    token* original = token_create(TOKEN_HEADING, "# Test Heading", 5, 10);
    assert(original != NULL);
    
    token* copy = token_copy(original);
    assert(copy != NULL);
    assert(copy != original); // Different memory addresses
    assert(copy->type == original->type);
    assert(strcmp(copy->value, original->value) == 0);
    assert(copy->line == original->line);
    assert(copy->column == original->column);
    assert(copy->next == NULL);
    
    token_destroy(original);
    token_destroy(copy);
}

/**
 * @brief Test token copying with NULL input
 */
void test_token_copy_null(void) {
    token* copy = token_copy(NULL);
    assert(copy == NULL);
}

/**
 * @brief Test token type conversion to string
 */
void test_token_type_to_string(void) {
    assert(strcmp(token_type_to_string(TOKEN_TEXT), "TEXT") == 0);
    assert(strcmp(token_type_to_string(TOKEN_HEADING), "HEADING") == 0);
    assert(strcmp(token_type_to_string(TOKEN_LIST_ITEM), "LIST_ITEM") == 0);
    assert(strcmp(token_type_to_string(TOKEN_CODE_BLOCK), "CODE_BLOCK") == 0);
    assert(strcmp(token_type_to_string(TOKEN_HTML_COMMENT), "HTML_COMMENT") == 0);
    assert(strcmp(token_type_to_string(TOKEN_XMD_DIRECTIVE), "XMD_DIRECTIVE") == 0);
    assert(strcmp(token_type_to_string(TOKEN_VARIABLE_REF), "VARIABLE_REF") == 0);
    assert(strcmp(token_type_to_string(TOKEN_EOF), "EOF") == 0);
    
    // Test invalid token type
    assert(strcmp(token_type_to_string((token_type)999), "UNKNOWN") == 0);
}

/**
 * @brief Test token equality comparison
 */
void test_token_equals(void) {
    token* t1 = token_create(TOKEN_TEXT, "Hello", 1, 5);
    token* t2 = token_create(TOKEN_TEXT, "Hello", 1, 5);
    token* t3 = token_create(TOKEN_TEXT, "World", 1, 5);
    token* t4 = token_create(TOKEN_HEADING, "Hello", 1, 5);
    token* t5 = token_create(TOKEN_TEXT, "Hello", 2, 5);
    
    // Same content should be equal
    assert(token_equals(t1, t2) == true);
    
    // Different values should not be equal
    assert(token_equals(t1, t3) == false);
    
    // Different types should not be equal
    assert(token_equals(t1, t4) == false);
    
    // Different positions should not be equal
    assert(token_equals(t1, t5) == false);
    
    // NULL comparisons
    assert(token_equals(NULL, NULL) == true);
    assert(token_equals(t1, NULL) == false);
    assert(token_equals(NULL, t1) == false);
    
    token_destroy(t1);
    token_destroy(t2);
    token_destroy(t3);
    token_destroy(t4);
    token_destroy(t5);
}

/**
 * @brief Test token list creation and management
 */
void test_token_list_operations(void) {
    token* head = NULL;
    
    // Test appending tokens
    token* t1 = token_create(TOKEN_TEXT, "First", 1, 1);
    token* t2 = token_create(TOKEN_TEXT, "Second", 1, 6);
    token* t3 = token_create(TOKEN_TEXT, "Third", 1, 13);
    
    head = token_list_append(head, t1);
    assert(head == t1);
    assert(t1->next == NULL);
    
    head = token_list_append(head, t2);
    assert(head == t1);
    assert(t1->next == t2);
    assert(t2->next == NULL);
    
    head = token_list_append(head, t3);
    assert(head == t1);
    assert(t1->next == t2);
    assert(t2->next == t3);
    assert(t3->next == NULL);
    
    // Test list length
    assert(token_list_length(head) == 3);
    
    // Test list cleanup
    token_list_destroy(head);
}

/**
 * @brief Test token list with empty list
 */
void test_token_list_empty(void) {
    assert(token_list_length(NULL) == 0);
    token_list_destroy(NULL); // Should not crash
}

/**
 * @brief Test token serialization to string
 */
void test_token_to_string(void) {
    token* t = token_create(TOKEN_HEADING, "# Test", 2, 5);
    char* str = token_to_string(t);
    
    assert(str != NULL);
    assert(strstr(str, "HEADING") != NULL);
    assert(strstr(str, "# Test") != NULL);
    assert(strstr(str, "2:5") != NULL);
    
    free(str);
    token_destroy(t);
}

/**
 * @brief Test token memory management under stress
 */
void test_token_memory_stress(void) {
    const int num_tokens = 1000;
    token** tokens = malloc(num_tokens * sizeof(token*));
    
    // Create many tokens
    for (int i = 0; i < num_tokens; i++) {
        char value[100];
        snprintf(value, sizeof(value), "Token %d", i);
        tokens[i] = token_create(TOKEN_TEXT, value, i + 1, 1);
        assert(tokens[i] != NULL);
    }
    
    // Verify all tokens
    for (int i = 0; i < num_tokens; i++) {
        char expected[100];
        snprintf(expected, sizeof(expected), "Token %d", i);
        assert(strcmp(tokens[i]->value, expected) == 0);
        assert(tokens[i]->line == i + 1);
    }
    
    // Cleanup all tokens
    for (int i = 0; i < num_tokens; i++) {
        token_destroy(tokens[i]);
    }
    
    free(tokens);
}

/**
 * @brief Test all token types
 */
void test_all_token_types(void) {
    token_type types[] = {
        TOKEN_TEXT,
        TOKEN_HEADING,
        TOKEN_LIST_ITEM,
        TOKEN_CODE_BLOCK,
        TOKEN_HTML_COMMENT,
        TOKEN_XMD_DIRECTIVE,
        TOKEN_VARIABLE_REF,
        TOKEN_EOF
    };
    
    const char* values[] = {
        "Plain text",
        "# Heading",
        "- List item",
        "```code```",
        "<!-- comment -->",
        "<!-- xmd:set var=\"value\" -->",
        "{{variable}}",
        ""
    };
    
    int num_types = sizeof(types) / sizeof(types[0]);
    
    for (int i = 0; i < num_types; i++) {
        token* t = token_create(types[i], values[i], 1, 1);
        assert(t != NULL);
        assert(t->type == types[i]);
        assert(strcmp(t->value, values[i]) == 0);
        token_destroy(t);
    }
}

/**
 * @brief Main test runner for token tests
 */
int main(void) {
    printf("Running token system tests...\n");
    
    test_token_create_basic();
    printf("✓ Token creation basic\n");
    
    test_token_create_null_handling();
    printf("✓ Token NULL handling\n");
    
    test_token_create_long_values();
    printf("✓ Token long values\n");
    
    test_token_destroy();
    printf("✓ Token destruction\n");
    
    test_token_copy();
    printf("✓ Token copying\n");
    
    test_token_copy_null();
    printf("✓ Token copy NULL\n");
    
    test_token_type_to_string();
    printf("✓ Token type to string\n");
    
    test_token_equals();
    printf("✓ Token equality\n");
    
    test_token_list_operations();
    printf("✓ Token list operations\n");
    
    test_token_list_empty();
    printf("✓ Token list empty\n");
    
    test_token_to_string();
    printf("✓ Token to string\n");
    
    test_token_memory_stress();
    printf("✓ Token memory stress\n");
    
    test_all_token_types();
    printf("✓ All token types\n");
    
    printf("All token tests passed!\n");
    return 0;
}