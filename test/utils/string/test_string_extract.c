/**
 * @file test_string_extract.c
 * @brief Unit tests for string_extract function
 * 
 * Tests the string extraction utility function with various inputs
 * including boundary conditions, invalid ranges, and edge cases.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../../src/utils/string/string_extract/string_extract.h"

/**
 * @brief Test string_extract with normal substring
 */
static void test_string_extract_normal(void) {
    const char* input = "Hello, World!";
    char* result = string_extract(input, 7, 5); // Extract "World"
    
    assert(result != NULL);
    assert(strcmp(result, "World") == 0);
    assert(strlen(result) == 5);
    
    free(result);
    printf("✓ test_string_extract_normal\n");
}

/**
 * @brief Test string_extract from beginning
 */
static void test_string_extract_beginning(void) {
    const char* input = "Hello, World!";
    char* result = string_extract(input, 0, 5); // Extract "Hello"
    
    assert(result != NULL);
    assert(strcmp(result, "Hello") == 0);
    
    free(result);
    printf("✓ test_string_extract_beginning\n");
}

/**
 * @brief Test string_extract to end
 */
static void test_string_extract_to_end(void) {
    const char* input = "Hello, World!";
    char* result = string_extract(input, 7, 6); // Extract "World!"
    
    assert(result != NULL);
    assert(strcmp(result, "World!") == 0);
    
    free(result);
    printf("✓ test_string_extract_to_end\n");
}

/**
 * @brief Test string_extract with zero length
 */
static void test_string_extract_zero_length(void) {
    const char* input = "Hello, World!";
    char* result = string_extract(input, 5, 0);
    
    assert(result != NULL);
    assert(strcmp(result, "") == 0);
    
    free(result);
    printf("✓ test_string_extract_zero_length\n");
}

/**
 * @brief Test string_extract with NULL input
 */
static void test_string_extract_null(void) {
    char* result = string_extract(NULL, 0, 5);
    
    assert(result == NULL);
    printf("✓ test_string_extract_null\n");
}

/**
 * @brief Test string_extract with out of bounds
 */
static void test_string_extract_out_of_bounds(void) {
    const char* input = "Hello";
    char* result = string_extract(input, 10, 5); // Start beyond string
    
    assert(result == NULL);
    printf("✓ test_string_extract_out_of_bounds\n");
}

/**
 * @brief Test string_extract with length exceeding bounds
 */
static void test_string_extract_length_exceeds(void) {
    const char* input = "Hello";
    char* result = string_extract(input, 3, 10); // Length goes beyond end
    
    // Should extract only available characters
    assert(result != NULL);
    assert(strcmp(result, "lo") == 0);
    
    free(result);
    printf("✓ test_string_extract_length_exceeds\n");
}

/**
 * @brief Test string_extract single character
 */
static void test_string_extract_single_char(void) {
    const char* input = "Hello";
    char* result = string_extract(input, 1, 1); // Extract "e"
    
    assert(result != NULL);
    assert(strcmp(result, "e") == 0);
    assert(strlen(result) == 1);
    
    free(result);
    printf("✓ test_string_extract_single_char\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("Running string_extract tests...\n");
    
    test_string_extract_normal();
    test_string_extract_beginning();
    test_string_extract_to_end();
    test_string_extract_zero_length();
    test_string_extract_null();
    test_string_extract_out_of_bounds();
    test_string_extract_length_exceeds();
    test_string_extract_single_char();
    
    printf("\nAll string_extract tests passed!\n");
    return 0;
}