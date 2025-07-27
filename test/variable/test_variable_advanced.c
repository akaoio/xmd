/**
 * @file test_variable_advanced.c
 * @brief Test advanced variable system features
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../include/variable.h"
#include "../../include/variable_internal.h"
#include "../../include/store.h"

void test_array_variable_operations(void) {
    printf("Testing advanced array variable operations...\n");
    
    // Test array creation and access
    variable* array = variable_create_array();
    assert(array != NULL);
    assert(array->type == VAR_ARRAY);
    assert(variable_array_size(array) == 0);
    
    // Test adding items
    variable* item1 = variable_create_string("first");
    variable* item2 = variable_create_string("second");
    variable* item3 = variable_create_string("third");
    
    variable_array_add(array, item1);
    variable_array_add(array, item2);
    variable_array_add(array, item3);
    
    assert(variable_array_size(array) == 3);
    
    // Test retrieval
    variable* retrieved1 = variable_array_get(array, 0);
    assert(retrieved1 != NULL);
    assert(strcmp(retrieved1->value.string_value, "first") == 0);
    
    variable* retrieved2 = variable_array_get(array, 1);
    assert(retrieved2 != NULL);
    assert(strcmp(retrieved2->value.string_value, "second") == 0);
    
    variable* retrieved3 = variable_array_get(array, 2);
    assert(retrieved3 != NULL);
    assert(strcmp(retrieved3->value.string_value, "third") == 0);
    
    // Test out-of-bounds access
    variable* out_of_bounds = variable_array_get(array, 5);
    assert(out_of_bounds == NULL);
    
    // Test empty array iteration
    variable* empty_array = variable_create_array();
    assert(variable_array_size(empty_array) == 0);
    
    variable_unref(array);
    variable_unref(empty_array);
    
    printf("✓ Array variable operations tests passed\n");
}

void test_variable_store_advanced(void) {
    printf("Testing advanced variable store operations...\n");
    
    store* var_store = store_create();
    assert(var_store != NULL);
    
    // Test storing arrays
    variable* test_array = variable_create_array();
    variable* elem1 = variable_create_string("element1");
    variable* elem2 = variable_create_string("element2");
    variable_array_add(test_array, elem1);
    variable_array_add(test_array, elem2);
    
    store_set(var_store, "my_array", test_array);
    
    // Test retrieving arrays
    variable* retrieved_array = store_get(var_store, "my_array");
    assert(retrieved_array != NULL);
    assert(retrieved_array->type == VAR_ARRAY);
    assert(variable_array_size(retrieved_array) == 2);
    
    variable* elem_check = variable_array_get(retrieved_array, 0);
    assert(strcmp(elem_check->value.string_value, "element1") == 0);
    
    // Test overwriting variables
    variable* new_string = variable_create_string("overwritten");
    store_set(var_store, "my_array", new_string);
    
    variable* overwritten = store_get(var_store, "my_array");
    assert(overwritten != NULL);
    assert(overwritten->type == VAR_STRING);
    assert(strcmp(overwritten->value.string_value, "overwritten") == 0);
    
    // Test non-existent variable
    variable* non_existent = store_get(var_store, "does_not_exist");
    assert(non_existent == NULL);
    
    variable_unref(test_array);
    variable_unref(new_string);
    store_destroy(var_store);
    
    printf("✓ Advanced variable store tests passed\n");
}

void test_variable_reference_counting(void) {
    printf("Testing variable reference counting...\n");
    
    // Create a string variable
    variable* str_var = variable_create_string("test_string");
    assert(str_var != NULL);
    assert(str_var->ref_count == 1);
    
    // Reference it
    variable_ref(str_var);
    assert(str_var->ref_count == 2);
    
    // Unreference once
    variable_unref(str_var);
    // Note: Can't check ref_count here as it might be freed
    
    // Create array and test ref counting
    variable* array_var = variable_create_array();
    variable* item = variable_create_string("array_item");
    
    variable_array_add(array_var, item);
    // Item should be referenced by array
    
    variable_unref(array_var);
    // Array and its items should be cleaned up
    
    printf("✓ Variable reference counting tests passed\n");
}

void test_variable_type_conversions(void) {
    printf("Testing variable type conversions...\n");
    
    // Test string to string conversion
    variable* str_var = variable_create_string("hello world");
    const char* str_result = variable_to_string(str_var);
    assert(str_result != NULL);
    assert(strcmp(str_result, "hello world") == 0);
    
    // Test number to string conversion
    variable* num_var = variable_create_number(42.5);
    const char* num_str = variable_to_string(num_var);
    assert(num_str != NULL);
    assert(strstr(num_str, "42") != NULL);
    
    // Test boolean to string conversion
    variable* bool_var = variable_create_boolean(true);
    const char* bool_str = variable_to_string(bool_var);
    assert(bool_str != NULL);
    assert(strcmp(bool_str, "true") == 0);
    
    variable* false_var = variable_create_boolean(false);
    const char* false_str = variable_to_string(false_var);
    assert(false_str != NULL);
    assert(strcmp(false_str, "false") == 0);
    
    // Test null to string conversion
    variable* null_var = variable_create_null();
    const char* null_str = variable_to_string(null_var);
    assert(null_str != NULL);
    assert(strlen(null_str) == 0); // Should be empty string
    
    variable_unref(str_var);
    variable_unref(num_var);
    variable_unref(bool_var);
    variable_unref(false_var);
    variable_unref(null_var);
    
    printf("✓ Variable type conversion tests passed\n");
}

void test_variable_array_edge_cases(void) {
    printf("Testing variable array edge cases...\n");
    
    // Test adding NULL to array
    variable* array = variable_create_array();
    variable_array_add(array, NULL);
    assert(variable_array_size(array) == 0); // Should not add NULL
    
    // Test array with mixed types
    variable* str_item = variable_create_string("string");
    variable* num_item = variable_create_number(123);
    variable* bool_item = variable_create_boolean(true);
    
    variable_array_add(array, str_item);
    variable_array_add(array, num_item);
    variable_array_add(array, bool_item);
    
    assert(variable_array_size(array) == 3);
    
    variable* get_str = variable_array_get(array, 0);
    assert(get_str->type == VAR_STRING);
    
    variable* get_num = variable_array_get(array, 1);
    assert(get_num->type == VAR_NUMBER);
    
    variable* get_bool = variable_array_get(array, 2);
    assert(get_bool->type == VAR_BOOLEAN);
    
    // Test array capacity growth
    for (int i = 0; i < 100; i++) {
        variable* item = variable_create_string("bulk_item");
        variable_array_add(array, item);
    }
    assert(variable_array_size(array) == 103); // 3 original + 100 new
    
    variable_unref(array);
    
    printf("✓ Variable array edge case tests passed\n");
}

void test_variable_memory_management(void) {
    printf("Testing variable memory management...\n");
    
    // Test creating and destroying many variables
    for (int i = 0; i < 1000; i++) {
        variable* var = variable_create_string("memory_test");
        variable_unref(var);
    }
    
    // Test array with many items
    variable* large_array = variable_create_array();
    for (int i = 0; i < 500; i++) {
        variable* item = variable_create_string("array_item");
        variable_array_add(large_array, item);
    }
    assert(variable_array_size(large_array) == 500);
    variable_unref(large_array);
    
    // Test nested arrays
    variable* outer_array = variable_create_array();
    for (int i = 0; i < 10; i++) {
        variable* inner_array = variable_create_array();
        for (int j = 0; j < 10; j++) {
            variable* item = variable_create_string("nested_item");
            variable_array_add(inner_array, item);
        }
        variable_array_add(outer_array, inner_array);
    }
    assert(variable_array_size(outer_array) == 10);
    variable_unref(outer_array);
    
    printf("✓ Variable memory management tests passed\n");
}

int main() {
    printf("=== Advanced Variable System Test Suite ===\n\n");
    
    test_array_variable_operations();
    test_variable_store_advanced();
    test_variable_reference_counting();
    test_variable_type_conversions();
    test_variable_array_edge_cases();
    test_variable_memory_management();
    
    printf("\n=== All Advanced Variable Tests Passed! ===\n");
    return 0;
}