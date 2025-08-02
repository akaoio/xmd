/**
 * @file test_loop_simple.c
 * @brief Simple test suite for loop system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/variable.h"
#include "../../include/store.h"
#include "../../include/loop.h"

/**
 * @brief Test for-in loop with arrays
 */
void test_for_in_array_loop(void) {
    printf("Testing for-in array loops...\n");
    
    LoopContext* ctx = loop_context_new();
    assert(ctx != NULL);
    
    store* s = store_create();
    assert(s != NULL);
    
    // Create an array of strings
    variable* items[3];
    items[0] = variable_create_string("apple");
    items[1] = variable_create_string("banana");
    items[2] = variable_create_string("cherry");
    
    variable* array = variable_new_array(items, 3);
    store_set(s, "fruits", array);
    
    char* result = NULL;
    int status = for_loop_process(ctx, "fruit", "fruits", "- item\n", s, &result);
    
    assert(status == LOOP_SUCCESS);
    assert(result != NULL);
    assert(strlen(result) > 0);
    
    free(result);
    
    for (int i = 0; i < 3; i++) {
        variable_unref(items[i]);
    }
    variable_unref(array);
    store_destroy(s);
    loop_context_free(ctx);
    
    printf("✓ For-in array loop tests passed\n");
}

/**
 * @brief Test while loops
 */
void test_while_loops(void) {
    printf("Testing while loops...\n");
    
    LoopContext* ctx = loop_context_new();
    store* s = store_create();
    
    // Set up a simple condition that will be false (to avoid infinite loop)
    variable* false_var = variable_create_boolean(0);
    store_set(s, "condition", false_var);
    
    char* result = NULL;
    int status = while_loop_process(ctx, "false", "Count\n", s, &result);
    
    assert(status == LOOP_SUCCESS);
    assert(result != NULL);
    // Should be empty since condition is false
    assert(strlen(result) == 0);
    
    free(result);
    variable_unref(false_var);
    store_destroy(s);
    loop_context_free(ctx);
    
    printf("✓ While loop tests passed\n");
}

/**
 * @brief Test loop control (break/continue)
 */
void test_loop_control(void) {
    printf("Testing loop control statements...\n");
    
    LoopContext* ctx = loop_context_new();
    
    // Test break
    int break_result = loop_break(ctx);
    assert(break_result == LOOP_BREAK);
    
    // Test continue
    int continue_result = loop_continue(ctx);
    assert(continue_result == LOOP_CONTINUE);
    
    loop_context_free(ctx);
    
    printf("✓ Loop control tests passed\n");
}

/**
 * @brief Test loop edge cases
 */
void test_loop_edge_cases(void) {
    printf("Testing loop edge cases...\n");
    
    LoopContext* ctx = loop_context_new();
    store* s = store_create();
    
    // Test empty array
    variable* empty_array = variable_new_array(NULL, 0);
    store_set(s, "empty", empty_array);
    
    char* result = NULL;
    int status = for_loop_process(ctx, "item", "empty", "Item\n", s, &result);
    
    assert(status == LOOP_SUCCESS);
    assert(result != NULL);
    assert(strlen(result) == 0); // Should be empty
    
    free(result);
    
    // Test undefined collection
    result = NULL;
    status = for_loop_process(ctx, "item", "undefined", "Item\n", s, &result);
    
    assert(status == LOOP_ERROR);
    
    variable_unref(empty_array);
    store_destroy(s);
    loop_context_free(ctx);
    
    printf("✓ Loop edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Loop System Tests (Simple) ===\n");
    
    test_for_in_array_loop();
    test_while_loops();
    test_loop_control();
    test_loop_edge_cases();
    
    printf("\n✅ All loop tests passed!\n");
    return 0;
}
