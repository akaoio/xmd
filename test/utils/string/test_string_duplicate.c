/**
 * @file test_string_duplicate.c
 * @brief Unit tests for string_duplicate function
 * 
 * Tests the string duplication utility function with various inputs
 * including edge cases, null pointers, and empty strings.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../../src/utils/string/string_duplicate/string_duplicate.h"

/**
 * @brief Test string_duplicate with normal string
 */
static void test_string_duplicate_normal(void) {
    const char* input = "Hello, World!";
    char* result = string_duplicate(input);
    
    assert(result != NULL);
    assert(strcmp(result, input) == 0);
    assert(result != input); // Ensure it's a copy
    
    free(result);
    printf("✓ test_string_duplicate_normal\n");
}

/**
 * @brief Test string_duplicate with empty string
 */
static void test_string_duplicate_empty(void) {
    const char* input = "";
    char* result = string_duplicate(input);
    
    assert(result != NULL);
    assert(strcmp(result, "") == 0);
    assert(strlen(result) == 0);
    
    free(result);
    printf("✓ test_string_duplicate_empty\n");
}

/**
 * @brief Test string_duplicate with NULL input
 */
static void test_string_duplicate_null(void) {
    char* result = string_duplicate(NULL);
    
    assert(result == NULL);
    printf("✓ test_string_duplicate_null\n");
}

/**
 * @brief Test string_duplicate with long string
 */
static void test_string_duplicate_long(void) {
    char input[1000];
    memset(input, 'A', 999);
    input[999] = '\0';
    
    char* result = string_duplicate(input);
    
    assert(result != NULL);
    assert(strlen(result) == 999);
    assert(strcmp(result, input) == 0);
    
    free(result);
    printf("✓ test_string_duplicate_long\n");
}

/**
 * @brief Test string_duplicate with special characters
 */
static void test_string_duplicate_special(void) {
    const char* input = "Tab\tNewline\nQuote\"Backslash\\";
    char* result = string_duplicate(input);
    
    assert(result != NULL);
    assert(strcmp(result, input) == 0);
    
    free(result);
    printf("✓ test_string_duplicate_special\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("Running string_duplicate tests...\n");
    
    test_string_duplicate_normal();
    test_string_duplicate_empty();
    test_string_duplicate_null();
    test_string_duplicate_long();
    test_string_duplicate_special();
    
    printf("\nAll string_duplicate tests passed!\n");
    return 0;
}