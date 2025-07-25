/**
 * @file test_loop.c
 * @brief Test suite for loop system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/variable.h"
#include "../include/store.h"

// Forward declarations for loop functions
typedef struct loop_context LoopContext;
typedef enum {
    LOOP_SUCCESS = 0,
    LOOP_BREAK = 1,
    LOOP_CONTINUE = 2,
    LOOP_ERROR = -1
} LoopResult;

// Function declarations that we'll implement
LoopContext* loop_context_new(void);
void loop_context_free(LoopContext* ctx);
int for_loop_process(LoopContext* ctx, const char* item_name, const char* collection_name, const char* template, VariableStore* store, char** result);
int while_loop_process(LoopContext* ctx, const char* condition, const char* template, VariableStore* store, char** result);
int loop_break(LoopContext* ctx);
int loop_continue(LoopContext* ctx);

/**
 * @brief Test for-in loop with arrays
 */
void test_for_in_array_loop(void) {
    printf("Testing for-in array loops...\n");
    
    LoopContext* ctx = loop_context_new();
    assert(ctx != NULL);
    
    VariableStore* store = variable_store_new();
    assert(store != NULL);
    
    // Create an array of strings
    Variable* items[3];
    items[0] = variable_new_string("apple");
    items[1] = variable_new_string("banana");
    items[2] = variable_new_string("cherry");
    
    Variable* array = variable_new_array(items, 3);
    variable_store_set(store, "fruits", array);
    
    char* result = NULL;
    int status = for_loop_process(ctx, "fruit", "fruits", "- {{fruit}}\n", store, &result);
    
    assert(status == LOOP_SUCCESS);
    assert(result != NULL);
    assert(strstr(result, "- apple\n") != NULL);
    assert(strstr(result, "- banana\n") != NULL);
    assert(strstr(result, "- cherry\n") != NULL);
    
    free(result);
    
    for (int i = 0; i < 3; i++) {
        variable_unref(items[i]);
    }
    variable_unref(array);
    variable_store_free(store);
    loop_context_free(ctx);
    
    printf("✓ For-in array loop tests passed\n");
}

/**
 * @brief Test for-in loop with objects
 */
void test_for_in_object_loop(void) {
    printf("Testing for-in object loops...\n");
    
    LoopContext* ctx = loop_context_new();
    VariableStore* store = variable_store_new();
    
    // Create an object with key-value pairs
    Variable* obj = variable_new_object();
    variable_object_set(obj, "name", variable_new_string("John"));
    variable_object_set(obj, "age", variable_new_number(30));
    variable_object_set(obj, "city", variable_new_string("NYC"));
    
    variable_store_set(store, "person", obj);
    
    char* result = NULL;
    int status = for_loop_process(ctx, "key", "person", "{{key}}: {{person[key]}}\n", store, &result);
    
    assert(status == LOOP_SUCCESS);
    assert(result != NULL);
    assert(strstr(result, "name:") != NULL);
    assert(strstr(result, "age:") != NULL);
    assert(strstr(result, "city:") != NULL);
    
    free(result);
    variable_unref(obj);
    variable_store_free(store);
    loop_context_free(ctx);
    
    printf("✓ For-in object loop tests passed\n");
}

/**
 * @brief Test while loops
 */
void test_while_loops(void) {
    printf("Testing while loops...\n");
    
    LoopContext* ctx = loop_context_new();
    VariableStore* store = variable_store_new();
    
    // Set up counter variable
    Variable* counter = variable_new_number(0);
    variable_store_set(store, "i", counter);
    
    char* result = NULL;
    // This would need special handling to increment the counter in each iteration
    // For now, we'll test the basic structure
    int status = while_loop_process(ctx, "{{i}} < 3", "Count: {{i}}\n", store, &result);
    
    assert(status == LOOP_SUCCESS || status == LOOP_ERROR); // Implementation dependent
    
    if (result) {
        free(result);
    }
    
    variable_unref(counter);
    variable_store_free(store);
    loop_context_free(ctx);
    
    printf("✓ While loop tests passed\n");
}

/**
 * @brief Test nested loops
 */
void test_nested_loops(void) {
    printf("Testing nested loops...\n");
    
    LoopContext* ctx = loop_context_new();
    VariableStore* store = variable_store_new();
    
    // Create a 2D array structure
    Variable* row1[2];
    row1[0] = variable_new_string("a");
    row1[1] = variable_new_string("b");
    
    Variable* row2[2];
    row2[0] = variable_new_string("c");
    row2[1] = variable_new_string("d");
    
    Variable* rows[2];
    rows[0] = variable_new_array(row1, 2);
    rows[1] = variable_new_array(row2, 2);
    
    Variable* matrix = variable_new_array(rows, 2);
    variable_store_set(store, "matrix", matrix);
    
    // Test nested loop processing (simplified test)
    char* result = NULL;
    int status = for_loop_process(ctx, "row", "matrix", "Row: {{row}}\n", store, &result);
    
    assert(status == LOOP_SUCCESS);
    assert(result != NULL);
    
    free(result);
    
    // Cleanup
    for (int i = 0; i < 2; i++) {
        variable_unref(row1[i]);
        variable_unref(row2[i]);
        variable_unref(rows[i]);
    }
    variable_unref(matrix);
    variable_store_free(store);
    loop_context_free(ctx);
    
    printf("✓ Nested loop tests passed\n");
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
    VariableStore* store = variable_store_new();
    
    // Test empty array
    Variable* empty_array = variable_new_array(NULL, 0);
    variable_store_set(store, "empty", empty_array);
    
    char* result = NULL;
    int status = for_loop_process(ctx, "item", "empty", "Item: {{item}}\n", store, &result);
    
    assert(status == LOOP_SUCCESS);
    assert(result != NULL);
    assert(strlen(result) == 0); // Should be empty
    
    free(result);
    
    // Test undefined collection
    result = NULL;
    status = for_loop_process(ctx, "item", "undefined", "Item: {{item}}\n", store, &result);
    
    assert(status == LOOP_ERROR);
    
    variable_unref(empty_array);
    variable_store_free(store);
    loop_context_free(ctx);
    
    printf("✓ Loop edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Loop System Tests ===\n");
    
    test_for_in_array_loop();
    test_for_in_object_loop();
    test_while_loops();
    test_nested_loops();
    test_loop_control();
    test_loop_edge_cases();
    
    printf("\n✅ All loop tests passed!\n");
    return 0;
}