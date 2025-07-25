/**
 * @file test_store.c
 * @brief Variable store comprehensive tests
 * @author XMD Team
 *
 * Tests for variable store operations including set, get,
 * remove, and memory management.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "store.h"
#include "variable.h"

/**
 * @brief Test store creation and destruction
 */
void test_store_lifecycle() {
    printf("Testing store lifecycle...\n");
    
    // Test creation
    store* s = store_create();
    assert(s != NULL);
    assert(store_size(s) == 0);
    
    // Test destruction
    store_destroy(s);
    
    // Test NULL destruction
    store_destroy(NULL); // Should not crash
    
    printf("✓ Store lifecycle tests passed\n");
}

/**
 * @brief Test basic store operations
 */
void test_basic_operations() {
    printf("Testing basic store operations...\n");
    
    store* s = store_create();
    assert(s != NULL);
    
    // Test setting variables
    variable* str_var = variable_create_string("hello");
    variable* num_var = variable_create_number(42.0);
    variable* bool_var = variable_create_boolean(true);
    
    bool result1 = store_set(s, "greeting", str_var);
    bool result2 = store_set(s, "answer", num_var);
    bool result3 = store_set(s, "flag", bool_var);
    
    assert(result1 == true);
    assert(result2 == true);
    assert(result3 == true);
    assert(store_size(s) == 3);
    
    // Test getting variables
    variable* retrieved_str = store_get(s, "greeting");
    variable* retrieved_num = store_get(s, "answer");
    variable* retrieved_bool = store_get(s, "flag");
    variable* not_found = store_get(s, "nonexistent");
    
    assert(retrieved_str != NULL);
    assert(variable_equals(retrieved_str, str_var) == true);
    assert(retrieved_num != NULL);
    assert(variable_equals(retrieved_num, num_var) == true);
    assert(retrieved_bool != NULL);
    assert(variable_equals(retrieved_bool, bool_var) == true);
    assert(not_found == NULL);
    
    // Test has functionality
    assert(store_has(s, "greeting") == true);
    assert(store_has(s, "answer") == true);
    assert(store_has(s, "flag") == true);
    assert(store_has(s, "nonexistent") == false);
    
    // Variables should have incremented reference counts
    assert(str_var->ref_count == 2); // Original + store
    assert(num_var->ref_count == 2);
    assert(bool_var->ref_count == 2);
    
    // Clean up original references
    variable_unref(str_var);
    variable_unref(num_var);
    variable_unref(bool_var);
    
    // Store should still have the variables
    assert(store_has(s, "greeting") == true);
    assert(store_has(s, "answer") == true);
    assert(store_has(s, "flag") == true);
    
    store_destroy(s);
    
    printf("✓ Basic store operations tests passed\n");
}

/**
 * @brief Test variable removal
 */
void test_variable_removal() {
    printf("Testing variable removal...\n");
    
    store* s = store_create();
    
    // Add some variables
    variable* var1 = variable_create_string("test1");
    variable* var2 = variable_create_string("test2");
    variable* var3 = variable_create_string("test3");
    
    store_set(s, "var1", var1);
    store_set(s, "var2", var2);
    store_set(s, "var3", var3);
    
    assert(store_size(s) == 3);
    
    // Test successful removal
    bool removed = store_remove(s, "var2");
    assert(removed == true);
    assert(store_size(s) == 2);
    assert(store_has(s, "var1") == true);
    assert(store_has(s, "var2") == false);
    assert(store_has(s, "var3") == true);
    
    // Test removal of non-existent variable
    bool not_removed = store_remove(s, "nonexistent");
    assert(not_removed == false);
    assert(store_size(s) == 2);
    
    // Clean up
    variable_unref(var1);
    variable_unref(var2);
    variable_unref(var3);
    
    store_destroy(s);
    
    printf("✓ Variable removal tests passed\n");
}

/**
 * @brief Test store clearing
 */
void test_store_clearing() {
    printf("Testing store clearing...\n");
    
    store* s = store_create();
    
    // Add multiple variables
    for (int i = 0; i < 10; i++) {
        char name[20];
        snprintf(name, sizeof(name), "var%d", i);
        
        variable* var = variable_create_number(i);
        store_set(s, name, var);
        variable_unref(var);
    }
    
    assert(store_size(s) == 10);
    
    // Clear the store
    store_clear(s);
    assert(store_size(s) == 0);
    
    // Verify all variables are gone
    for (int i = 0; i < 10; i++) {
        char name[20];
        snprintf(name, sizeof(name), "var%d", i);
        assert(store_has(s, name) == false);
    }
    
    store_destroy(s);
    
    printf("✓ Store clearing tests passed\n");
}

/**
 * @brief Test getting variable keys
 */
void test_store_keys() {
    printf("Testing store keys...\n");
    
    store* s = store_create();
    
    // Test empty store
    size_t count = 0;
    char** keys = store_keys(s, &count);
    assert(count == 0);
    assert(keys == NULL);
    
    // Add some variables
    variable* var1 = variable_create_string("value1");
    variable* var2 = variable_create_string("value2");
    variable* var3 = variable_create_string("value3");
    
    store_set(s, "alpha", var1);
    store_set(s, "beta", var2);
    store_set(s, "gamma", var3);
    
    // Get keys
    keys = store_keys(s, &count);
    assert(count == 3);
    assert(keys != NULL);
    
    // Verify all keys are present (order may vary)
    bool found_alpha = false, found_beta = false, found_gamma = false;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(keys[i], "alpha") == 0) found_alpha = true;
        if (strcmp(keys[i], "beta") == 0) found_beta = true;
        if (strcmp(keys[i], "gamma") == 0) found_gamma = true;
    }
    
    assert(found_alpha == true);
    assert(found_beta == true);
    assert(found_gamma == true);
    
    // Free keys array
    for (size_t i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
    
    // Clean up
    variable_unref(var1);
    variable_unref(var2);
    variable_unref(var3);
    
    store_destroy(s);
    
    printf("✓ Store keys tests passed\n");
}

/**
 * @brief Test variable overwriting
 */
void test_variable_overwriting() {
    printf("Testing variable overwriting...\n");
    
    store* s = store_create();
    
    // Set initial variable
    variable* var1 = variable_create_string("original");
    store_set(s, "test", var1);
    assert(store_size(s) == 1);
    assert(var1->ref_count == 2); // Original + store
    
    // Overwrite with new variable
    variable* var2 = variable_create_string("updated");
    store_set(s, "test", var2);
    assert(store_size(s) == 1); // Still only one variable
    
    // Verify new variable is stored
    variable* retrieved = store_get(s, "test");
    assert(variable_equals(retrieved, var2) == true);
    assert(variable_equals(retrieved, var1) == false);
    
    // Clean up
    variable_unref(var1);
    variable_unref(var2);
    
    store_destroy(s);
    
    printf("✓ Variable overwriting tests passed\n");
}

/**
 * @brief Test edge cases and error handling
 */
void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    store* s = store_create();
    
    // Test NULL operations
    assert(store_set(NULL, "test", NULL) == false);
    assert(store_set(s, NULL, NULL) == false);
    assert(store_get(NULL, "test") == NULL);
    assert(store_get(s, NULL) == NULL);
    assert(store_has(NULL, "test") == false);
    assert(store_has(s, NULL) == false);
    assert(store_remove(NULL, "test") == false);
    assert(store_remove(s, NULL) == false);
    
    // Test empty string key
    variable* var = variable_create_string("test");
    assert(store_set(s, "", var) == true);
    assert(store_has(s, "") == true);
    assert(store_get(s, "") != NULL);
    variable_unref(var);
    
    // Test very long key name
    char long_key[1000];
    for (int i = 0; i < 999; i++) {
        long_key[i] = 'a';
    }
    long_key[999] = '\0';
    
    variable* long_var = variable_create_string("long_key_test");
    assert(store_set(s, long_key, long_var) == true);
    assert(store_has(s, long_key) == true);
    variable_unref(long_var);
    
    // Test store with many variables (stress test)
    for (int i = 0; i < 1000; i++) {
        char key[20];
        snprintf(key, sizeof(key), "stress_%d", i);
        
        variable* stress_var = variable_create_number(i);
        store_set(s, key, stress_var);
        variable_unref(stress_var);
    }
    
    assert(store_size(s) == 1002); // 1000 + empty string + long key
    
    store_destroy(s);
    
    printf("✓ Edge case tests passed\n");
}

/**
 * @brief Main test function
 */
int main() {
    printf("=== Variable Store Tests ===\n");
    
    test_store_lifecycle();
    test_basic_operations();
    test_variable_removal();
    test_store_clearing();
    test_store_keys();
    test_variable_overwriting();
    test_edge_cases();
    
    printf("\n✅ All store tests passed!\n");
    return 0;
}