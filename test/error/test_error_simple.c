/**
 * @file test_error_simple.c
 * @brief Simple test suite for error handling system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/error.h"

/**
 * @brief Test error context lifecycle
 */
void test_error_context_lifecycle(void) {
    printf("Testing error context lifecycle...\n");
    
    ErrorContext* ctx = error_context_new();
    assert(ctx != NULL);
    
    // Initially should have no error
    assert(error_get_current(ctx) == NULL);
    assert(error_is_caught(ctx) == 0);
    
    error_context_free(ctx);
    
    printf("✓ Error context lifecycle tests passed\n");
}

/**
 * @brief Test basic try/catch blocks
 */
void test_try_catch_basic(void) {
    printf("Testing basic try/catch blocks...\n");
    
    ErrorContext* ctx = error_context_new();
    
    // Begin try block
    int result = try_block_begin(ctx);
    assert(result == 0);
    
    // Throw an error
    error_throw(ctx, ERROR_RUNTIME, "Test runtime error", __FILE__, __LINE__);
    
    // End try block
    result = try_block_end(ctx);
    assert(result == 0);
    
    // Begin catch block for runtime errors
    result = catch_block_begin(ctx, ERROR_RUNTIME);
    assert(result == 0);
    
    // Check that error is caught
    assert(error_is_caught(ctx) == 1);
    XMDError* error = error_get_current(ctx);
    assert(error != NULL);
    assert(error->type == ERROR_RUNTIME);
    assert(strcmp(error->message, "Test runtime error") == 0);
    
    // End catch block
    result = catch_block_end(ctx);
    assert(result == 0);
    
    error_context_free(ctx);
    
    printf("✓ Basic try/catch tests passed\n");
}

/**
 * @brief Test multiple catch blocks
 */
void test_multiple_catch_blocks(void) {
    printf("Testing multiple catch blocks...\n");
    
    ErrorContext* ctx = error_context_new();
    
    // Test catching variable error
    try_block_begin(ctx);
    error_throw(ctx, ERROR_VARIABLE, "Variable not found", __FILE__, __LINE__);
    try_block_end(ctx);
    
    // First catch block (runtime errors) - should not match
    int result = catch_block_begin(ctx, ERROR_RUNTIME);
    assert(result == 0);
    assert(error_is_caught(ctx) == 0);
    catch_block_end(ctx);
    
    // Second catch block (variable errors) - should match
    result = catch_block_begin(ctx, ERROR_VARIABLE);
    assert(result == 0);
    assert(error_is_caught(ctx) == 1);
    XMDError* error = error_get_current(ctx);
    assert(error->type == ERROR_VARIABLE);
    catch_block_end(ctx);
    
    error_context_free(ctx);
    
    printf("✓ Multiple catch blocks tests passed\n");
}

/**
 * @brief Test error clearing
 */
void test_error_clearing(void) {
    printf("Testing error clearing...\n");
    
    ErrorContext* ctx = error_context_new();
    
    // Throw an error
    error_throw(ctx, ERROR_CUSTOM, "Custom error message", __FILE__, __LINE__);
    assert(error_get_current(ctx) != NULL);
    
    // Clear the error
    error_clear(ctx);
    assert(error_get_current(ctx) == NULL);
    assert(error_is_caught(ctx) == 0);
    
    error_context_free(ctx);
    
    printf("✓ Error clearing tests passed\n");
}

/**
 * @brief Test error message handling
 */
void test_error_messages(void) {
    printf("Testing error message handling...\n");
    
    ErrorContext* ctx = error_context_new();
    
    const char* test_message = "This is a detailed error message with context";
    const char* test_file = "test_file.c";
    int test_line = 123;
    
    error_throw(ctx, ERROR_RUNTIME, test_message, test_file, test_line);
    
    XMDError* error = error_get_current(ctx);
    assert(error != NULL);
    assert(error->type == ERROR_RUNTIME);
    assert(strcmp(error->message, test_message) == 0);
    assert(strcmp(error->file, test_file) == 0);
    assert(error->line == test_line);
    
    error_context_free(ctx);
    
    printf("✓ Error message tests passed\n");
}

/**
 * @brief Test edge cases and error conditions
 */
void test_error_edge_cases(void) {
    printf("Testing error edge cases...\n");
    
    // Test NULL context
    assert(error_throw(NULL, ERROR_RUNTIME, "test", __FILE__, __LINE__) != 0);
    assert(error_get_current(NULL) == NULL);
    assert(error_is_caught(NULL) == 0);
    
    ErrorContext* ctx = error_context_new();
    
    // Test NULL message
    error_throw(ctx, ERROR_RUNTIME, NULL, __FILE__, __LINE__);
    XMDError* error = error_get_current(ctx);
    assert(error != NULL);
    assert(error->message != NULL); // Should provide default message
    
    error_clear(ctx);
    
    // Test empty message
    error_throw(ctx, ERROR_RUNTIME, "", __FILE__, __LINE__);
    error = error_get_current(ctx);
    assert(error != NULL);
    assert(strlen(error->message) >= 0); // Should not be null
    
    error_context_free(ctx);
    
    printf("✓ Error edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Error Handling System Tests (Simple) ===\n");
    
    test_error_context_lifecycle();
    test_try_catch_basic();
    test_multiple_catch_blocks();
    test_error_clearing();
    test_error_messages();
    test_error_edge_cases();
    
    printf("\n✅ All error handling tests passed!\n");
    return 0;
}