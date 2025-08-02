/**
 * @file test_object_literals.c
 * @brief Test cases for AST object literal support
 * @author XMD Implementation Team
 * @date 2025-01-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/ast_evaluator.h"
#include "../../include/variable.h"

/**
 * @brief Test AST object value creation and cleanup
 */
static void test_ast_object_value_creation(void) {
    printf("Testing AST object value creation...\n");
    
    // Create an AST object value
    ast_value* obj_value = ast_value_create(AST_VAL_OBJECT);
    assert(obj_value != NULL);
    assert(obj_value->type == AST_VAL_OBJECT);
    
    // Initialize empty object
    obj_value->value.object_value.pairs = NULL;
    obj_value->value.object_value.pair_count = 0;
    
    // Test cleanup
    ast_value_free(obj_value);
    
    printf("✓ AST object value creation works\n");
}

/**
 * @brief Test AST object value with properties
 */
static void test_ast_object_value_with_properties(void) {
    printf("Testing AST object value with properties...\n");
    
    // Create object value
    ast_value* obj_value = ast_value_create(AST_VAL_OBJECT);
    assert(obj_value != NULL);
    
    // Add properties
    obj_value->value.object_value.pair_count = 2;
    obj_value->value.object_value.pairs = malloc(sizeof(ast_object_pair) * 2);
    assert(obj_value->value.object_value.pairs != NULL);
    
    // Add "name" property
    obj_value->value.object_value.pairs[0].key = strdup("name");
    obj_value->value.object_value.pairs[0].value = ast_value_create(AST_VAL_STRING);
    obj_value->value.object_value.pairs[0].value->value.string_value = strdup("Alice");
    
    // Add "age" property
    obj_value->value.object_value.pairs[1].key = strdup("age");
    obj_value->value.object_value.pairs[1].value = ast_value_create(AST_VAL_NUMBER);
    obj_value->value.object_value.pairs[1].value->value.number_value = 30.0;
    
    // Verify properties
    assert(strcmp(obj_value->value.object_value.pairs[0].key, "name") == 0);
    assert(strcmp(obj_value->value.object_value.pairs[0].value->value.string_value, "Alice") == 0);
    assert(obj_value->value.object_value.pairs[1].value->value.number_value == 30.0);
    
    // Test cleanup
    ast_value_free(obj_value);
    
    printf("✓ AST object value with properties works\n");
}

/**
 * @brief Test variable to AST object conversion
 */
static void test_variable_to_ast_object_conversion(void) {
    printf("Testing variable to AST object conversion...\n");
    
    // Create variable object
    variable* var_obj = variable_create_object();
    assert(var_obj != NULL);
    
    // Add properties to variable
    variable* name_var = variable_create_string("Bob");
    variable* age_var = variable_create_number(25);
    
    assert(variable_object_set(var_obj, "name", name_var) == 0);
    assert(variable_object_set(var_obj, "age", age_var) == 0);
    
    variable_unref(name_var);
    variable_unref(age_var);
    
    // Convert to AST value
    extern ast_value* ast_variable_to_value(variable* var);
    ast_value* ast_obj = ast_variable_to_value(var_obj);
    assert(ast_obj != NULL);
    assert(ast_obj->type == AST_VAL_OBJECT);
    assert(ast_obj->value.object_value.pair_count == 2);
    
    // Verify converted properties
    bool found_name = false, found_age = false;
    for (size_t i = 0; i < ast_obj->value.object_value.pair_count; i++) {
        if (strcmp(ast_obj->value.object_value.pairs[i].key, "name") == 0) {
            found_name = true;
            assert(ast_obj->value.object_value.pairs[i].value->type == AST_VAL_STRING);
            assert(strcmp(ast_obj->value.object_value.pairs[i].value->value.string_value, "Bob") == 0);
        }
        if (strcmp(ast_obj->value.object_value.pairs[i].key, "age") == 0) {
            found_age = true;
            assert(ast_obj->value.object_value.pairs[i].value->type == AST_VAL_NUMBER);
            assert(ast_obj->value.object_value.pairs[i].value->value.number_value == 25.0);
        }
    }
    assert(found_name && found_age);
    
    // Cleanup
    ast_value_free(ast_obj);
    variable_unref(var_obj);
    
    printf("✓ Variable to AST object conversion works\n");
}

/**
 * @brief Test AST to variable object conversion
 */
static void test_ast_to_variable_object_conversion(void) {
    printf("Testing AST to variable object conversion...\n");
    
    // Create AST object
    ast_value* ast_obj = ast_value_create(AST_VAL_OBJECT);
    ast_obj->value.object_value.pair_count = 1;
    ast_obj->value.object_value.pairs = malloc(sizeof(ast_object_pair));
    
    ast_obj->value.object_value.pairs[0].key = strdup("test");
    ast_obj->value.object_value.pairs[0].value = ast_value_create(AST_VAL_STRING);
    ast_obj->value.object_value.pairs[0].value->value.string_value = strdup("value");
    
    // Convert to variable
    extern variable* ast_value_to_variable(ast_value* value);
    variable* var_obj = ast_value_to_variable(ast_obj);
    assert(var_obj != NULL);
    assert(variable_get_type(var_obj) == VAR_OBJECT);
    assert(variable_object_size(var_obj) == 1);
    
    // Verify property
    variable* test_prop = variable_object_get(var_obj, "test");
    assert(test_prop != NULL);
    assert(variable_get_type(test_prop) == VAR_STRING);
    assert(strcmp(variable_to_string(test_prop), "value") == 0);
    
    // Cleanup
    ast_value_free(ast_obj);
    variable_unref(var_obj);
    
    printf("✓ AST to variable object conversion works\n");
}

/**
 * @brief Test object literal AST node creation
 */
static void test_object_literal_ast_node_creation(void) {
    printf("Testing object literal AST node creation...\n");
    
    // Create object literal node
    extern ast_node* ast_create_object_literal(void);
    ast_node* node = ast_create_object_literal();
    assert(node != NULL);
    assert(node->type == AST_OBJECT_LITERAL);
    assert(node->data.object_literal.pair_count == 0);
    assert(node->data.object_literal.pairs == NULL);
    
    // Add a property
    extern int ast_object_literal_add_property(ast_node* node, const char* key, ast_node* value);
    ast_node* value_node = ast_create_string_literal("test_value");
    assert(ast_object_literal_add_property(node, "test_key", value_node) == 0);
    
    assert(node->data.object_literal.pair_count == 1);
    assert(strcmp(node->data.object_literal.pairs[0].key, "test_key") == 0);
    assert(node->data.object_literal.pairs[0].value == value_node);
    
    // Cleanup
    ast_free(node);
    
    printf("✓ Object literal AST node creation works\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("Running object literal AST tests...\n\n");
    
    test_ast_object_value_creation();
    test_ast_object_value_with_properties();
    test_variable_to_ast_object_conversion();
    test_ast_to_variable_object_conversion();
    test_object_literal_ast_node_creation();
    
    printf("\n✅ All object literal AST tests passed!\n");
    return 0;
}