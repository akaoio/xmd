/**
 * @file test_variable.c
 * @brief Variable system comprehensive tests
 * @author XMD Team
 *
 * Tests for variable creation, reference counting, type conversions,
 * and basic operations in the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "variable.h"

/**
 * @brief Test variable creation functions
 */
void test_variable_creation() {
    printf("Testing variable creation...\n");
    
    // Test null variable
    variable* null_var = variable_create_null();
    assert(null_var != NULL);
    assert(variable_get_type(null_var) == VAR_NULL);
    assert(null_var->ref_count == 1);
    variable_unref(null_var);
    
    // Test boolean variable
    variable* bool_var = variable_create_boolean(true);
    assert(bool_var != NULL);
    assert(variable_get_type(bool_var) == VAR_BOOLEAN);
    assert(bool_var->value.boolean_value == true);
    assert(bool_var->ref_count == 1);
    variable_unref(bool_var);
    
    // Test number variable
    variable* num_var = variable_create_number(42.5);
    assert(num_var != NULL);
    assert(variable_get_type(num_var) == VAR_NUMBER);
    assert(fabs(num_var->value.number_value - 42.5) < 0.001);
    assert(num_var->ref_count == 1);
    variable_unref(num_var);
    
    // Test string variable
    variable* str_var = variable_create_string("Hello World");
    assert(str_var != NULL);
    assert(variable_get_type(str_var) == VAR_STRING);
    assert(strcmp(str_var->value.string_value, "Hello World") == 0);
    assert(str_var->ref_count == 1);
    variable_unref(str_var);
    
    // Test array variable
    variable* arr_var = variable_create_array();
    assert(arr_var != NULL);
    assert(variable_get_type(arr_var) == VAR_ARRAY);
    assert(arr_var->ref_count == 1);
    variable_unref(arr_var);
    
    // Test object variable
    variable* obj_var = variable_create_object();
    assert(obj_var != NULL);
    assert(variable_get_type(obj_var) == VAR_OBJECT);
    assert(obj_var->ref_count == 1);
    variable_unref(obj_var);
    
    printf("✓ Variable creation tests passed\n");
}

/**
 * @brief Test reference counting
 */
void test_reference_counting() {
    printf("Testing reference counting...\n");
    
    // Create variable with ref count 1
    variable* var = variable_create_string("test");
    assert(var->ref_count == 1);
    
    // Increment reference
    variable* ref1 = variable_ref(var);
    assert(ref1 == var);
    assert(var->ref_count == 2);
    
    // Increment again
    variable* ref2 = variable_ref(var);
    assert(ref2 == var);
    assert(var->ref_count == 3);
    
    // Decrement references
    variable_unref(ref1);
    assert(var->ref_count == 2);
    
    variable_unref(ref2);
    assert(var->ref_count == 1);
    
    // Final unref should destroy
    variable_unref(var);
    
    // Test NULL handling
    variable* null_ref = variable_ref(NULL);
    assert(null_ref == NULL);
    variable_unref(NULL); // Should not crash
    
    printf("✓ Reference counting tests passed\n");
}

/**
 * @brief Test type conversions
 */
void test_type_conversions() {
    printf("Testing type conversions...\n");
    
    // Test boolean conversions
    variable* true_var = variable_create_boolean(true);
    variable* false_var = variable_create_boolean(false);
    variable* null_var = variable_create_null();
    variable* zero_var = variable_create_number(0.0);
    variable* nonzero_var = variable_create_number(42.0);
    variable* empty_str = variable_create_string("");
    variable* nonempty_str = variable_create_string("hello");
    
    assert(variable_to_boolean(true_var) == true);
    assert(variable_to_boolean(false_var) == false);
    assert(variable_to_boolean(null_var) == false);
    assert(variable_to_boolean(zero_var) == false);
    assert(variable_to_boolean(nonzero_var) == true);
    assert(variable_to_boolean(empty_str) == false);
    assert(variable_to_boolean(nonempty_str) == true);
    
    // Test array and object conversion (simplified)
    variable* arr_var = variable_create_array();
    variable* obj_var = variable_create_object();
    assert(variable_to_boolean(arr_var) == false); // NULL array value
    assert(variable_to_boolean(obj_var) == false); // NULL object value
    variable_unref(arr_var);
    variable_unref(obj_var);
    
    // Test number conversions
    assert(fabs(variable_to_number(true_var) - 1.0) < 0.001);
    assert(fabs(variable_to_number(false_var) - 0.0) < 0.001);
    assert(fabs(variable_to_number(null_var) - 0.0) < 0.001);
    assert(fabs(variable_to_number(nonzero_var) - 42.0) < 0.001);
    
    // Test string conversions
    char* true_str = variable_to_string(true_var);
    char* false_str = variable_to_string(false_var);
    char* null_str = variable_to_string(null_var);
    char* num_str = variable_to_string(nonzero_var);
    char* str_str = variable_to_string(nonempty_str);
    
    assert(strcmp(true_str, "true") == 0);
    assert(strcmp(false_str, "false") == 0);
    assert(strcmp(null_str, "null") == 0);
    assert(strcmp(num_str, "42") == 0);
    assert(strcmp(str_str, "hello") == 0);
    
    free(true_str);
    free(false_str);
    free(null_str);
    free(num_str);
    free(str_str);
    
    variable_unref(true_var);
    variable_unref(false_var);
    variable_unref(null_var);
    variable_unref(zero_var);
    variable_unref(nonzero_var);
    variable_unref(empty_str);
    variable_unref(nonempty_str);
    
    printf("✓ Type conversion tests passed\n");
}

/**
 * @brief Test variable equality
 */
void test_variable_equality() {
    printf("Testing variable equality...\n");
    
    // Test null equality
    variable* null1 = variable_create_null();
    variable* null2 = variable_create_null();
    assert(variable_equals(null1, null2) == true);
    assert(variable_equals(NULL, NULL) == true);
    assert(variable_equals(null1, NULL) == false);
    
    // Test boolean equality
    variable* true1 = variable_create_boolean(true);
    variable* true2 = variable_create_boolean(true);
    variable* false_var = variable_create_boolean(false);
    assert(variable_equals(true1, true2) == true);
    assert(variable_equals(true1, false_var) == false);
    
    // Test number equality
    variable* num1 = variable_create_number(42.5);
    variable* num2 = variable_create_number(42.5);
    variable* num3 = variable_create_number(41.5);
    assert(variable_equals(num1, num2) == true);
    assert(variable_equals(num1, num3) == false);
    
    // Test string equality
    variable* str1 = variable_create_string("hello");
    variable* str2 = variable_create_string("hello");
    variable* str3 = variable_create_string("world");
    assert(variable_equals(str1, str2) == true);
    assert(variable_equals(str1, str3) == false);
    
    // Test cross-type inequality
    assert(variable_equals(true1, num1) == false);
    assert(variable_equals(num1, str1) == false);
    assert(variable_equals(str1, null1) == false);
    
    variable_unref(null1);
    variable_unref(null2);
    variable_unref(true1);
    variable_unref(true2);
    variable_unref(false_var);
    variable_unref(num1);
    variable_unref(num2);
    variable_unref(num3);
    variable_unref(str1);
    variable_unref(str2);
    variable_unref(str3);
    
    printf("✓ Variable equality tests passed\n");
}

/**
 * @brief Test variable copying
 */
void test_variable_copying() {
    printf("Testing variable copying...\n");
    
    // Test null copy
    variable* null_var = variable_create_null();
    variable* null_copy = variable_copy(null_var);
    assert(null_copy != null_var); // Different instances
    assert(variable_equals(null_var, null_copy) == true);
    
    // Test boolean copy
    variable* bool_var = variable_create_boolean(true);
    variable* bool_copy = variable_copy(bool_var);
    assert(bool_copy != bool_var);
    assert(variable_equals(bool_var, bool_copy) == true);
    
    // Test number copy
    variable* num_var = variable_create_number(42.5);
    variable* num_copy = variable_copy(num_var);
    assert(num_copy != num_var);
    assert(variable_equals(num_var, num_copy) == true);
    
    // Test string copy
    variable* str_var = variable_create_string("hello");
    variable* str_copy = variable_copy(str_var);
    assert(str_copy != str_var);
    assert(str_copy->value.string_value != str_var->value.string_value); // Different string pointers
    assert(variable_equals(str_var, str_copy) == true);
    
    // Test NULL copy
    variable* null_result = variable_copy(NULL);
    assert(null_result == NULL);
    
    variable_unref(null_var);
    variable_unref(null_copy);
    variable_unref(bool_var);
    variable_unref(bool_copy);
    variable_unref(num_var);
    variable_unref(num_copy);
    variable_unref(str_var);
    variable_unref(str_copy);
    
    printf("✓ Variable copying tests passed\n");
}

/**
 * @brief Test edge cases and error handling
 */
void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    // Test NULL string creation
    variable* null_str = variable_create_string(NULL);
    assert(null_str != NULL);
    assert(variable_get_type(null_str) == VAR_STRING);
    assert(null_str->value.string_value != NULL);
    assert(strlen(null_str->value.string_value) == 0);
    
    // Test empty string
    variable* empty_str = variable_create_string("");
    assert(empty_str != NULL);
    assert(strlen(empty_str->value.string_value) == 0);
    
    // Test very long string
    char long_str[1000];
    for (int i = 0; i < 999; i++) {
        long_str[i] = 'a';
    }
    long_str[999] = '\0';
    
    variable* long_var = variable_create_string(long_str);
    assert(long_var != NULL);
    assert(strlen(long_var->value.string_value) == 999);
    assert(strcmp(long_var->value.string_value, long_str) == 0);
    
    // Test special numbers
    variable* nan_var = variable_create_number(NAN);
    variable* inf_var = variable_create_number(INFINITY);
    variable* neg_inf_var = variable_create_number(-INFINITY);
    
    assert(isnan(nan_var->value.number_value));
    assert(isinf(inf_var->value.number_value) && inf_var->value.number_value > 0);
    assert(isinf(neg_inf_var->value.number_value) && neg_inf_var->value.number_value < 0);
    
    variable_unref(null_str);
    variable_unref(empty_str);
    variable_unref(long_var);
    variable_unref(nan_var);
    variable_unref(inf_var);
    variable_unref(neg_inf_var);
    
    printf("✓ Edge case tests passed\n");
}

/**
 * @brief Main test function
 */
int main() {
    printf("=== Variable System Tests ===\n");
    
    test_variable_creation();
    test_reference_counting();
    test_type_conversions();
    test_variable_equality();
    test_variable_copying();
    test_edge_cases();
    
    printf("\n✅ All variable tests passed!\n");
    return 0;
}