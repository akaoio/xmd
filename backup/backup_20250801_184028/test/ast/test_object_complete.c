/**
 * @file test_object_complete.c
 * @brief Complete test for object literals and property access
 * @author XMD Team
 * @date 2025-07-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/ast_evaluator.h"
#include "../../include/ast_parser.h"
#include "../../include/ast_node.h"
#include "../../include/lexer_enhanced.h"
#include "../../include/store.h"
#include "../../include/variable.h"
#include "../../include/xmd.h"

/**
 * @brief Test basic object literal creation and evaluation
 */
void test_object_literal_basic(void) {
    printf("Testing basic object literal...\n");
    
    // Parse "{name: \"John\", age: 30}"
    const char* input = "{name: \"John\", age: 30}";
    token* tokens = lexer_enhanced_tokenize(input, "test");
    assert(tokens != NULL);
    
    parser_state state = {0};
    state.tokens = tokens;
    state.current_token = tokens;
    state.filename = "test";
    
    ast_node* node = ast_parse_primary(&state);
    assert(node != NULL);
    assert(node->type == AST_OBJECT_LITERAL);
    assert(node->data.object_literal.property_count == 2);
    
    // Create evaluator
    store* variables = store_create();
    printf("✓ Store created\n");
    processor_context dummy_ctx = {0};
    ast_evaluator* evaluator = ast_evaluator_create(variables, &dummy_ctx);
    printf("✓ Evaluator created: %p\n", (void*)evaluator);
    
    // Evaluate object literal
    printf("About to evaluate node type: %d\n", node->type);
    ast_value* result = ast_evaluate(node, evaluator);
    printf("Evaluation result: %p\n", (void*)result);
    assert(result != NULL);
    assert(result->type == AST_VAL_OBJECT);
    assert(result->value.object_value.pair_count == 2);
    
    // Check properties
    bool found_name = false, found_age = false;
    for (size_t i = 0; i < result->value.object_value.pair_count; i++) {
        ast_object_pair* pair = &result->value.object_value.pairs[i];
        if (strcmp(pair->key, "name") == 0) {
            assert(pair->value->type == AST_VAL_STRING);
            assert(strcmp(pair->value->value.string_value, "John") == 0);
            found_name = true;
        } else if (strcmp(pair->key, "age") == 0) {
            assert(pair->value->type == AST_VAL_NUMBER);
            assert(pair->value->value.number_value == 30.0);
            found_age = true;
        }
    }
    assert(found_name && found_age);
    
    ast_value_free(result);
    ast_evaluator_free(evaluator);
    store_destroy(variables);
    ast_free(node);
    token_list_free(tokens);
    
    printf("✓ Basic object literal test passed\n");
}

/**
 * @brief Test property access evaluation
 */
void test_property_access_basic(void) {
    printf("Testing basic property access...\n");
    
    // Create object variable in store
    store* variables = store_create();
    variable* obj = variable_create_object();
    variable* name_var = variable_create_string("Alice");
    variable* age_var = variable_create_string("25");
    
    variable_object_set(obj, "name", name_var);
    variable_object_set(obj, "age", age_var);
    store_set(variables, "person", obj);
    
    variable_unref(name_var);
    variable_unref(age_var);
    variable_unref(obj);
    
    // Parse "person.name"
    const char* input = "person.name";
    token* tokens = lexer_enhanced_tokenize(input, "test");
    assert(tokens != NULL);
    
    parser_state state = {0};
    state.tokens = tokens;
    state.current_token = tokens;
    state.filename = "test";
    
    ast_node* node = ast_parse_primary(&state);
    assert(node != NULL);
    assert(node->type == AST_PROPERTY_ACCESS);
    
    // Create evaluator
    processor_context dummy_ctx = {0};
    ast_evaluator* evaluator = ast_evaluator_create(variables, &dummy_ctx);
    
    // Evaluate property access
    ast_value* result = ast_evaluate(node, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_STRING);
    assert(strcmp(result->value.string_value, "Alice") == 0);
    
    ast_value_free(result);
    ast_evaluator_free(evaluator);
    store_destroy(variables);
    ast_free(node);
    token_list_free(tokens);
    
    printf("✓ Basic property access test passed\n");
}

/**
 * @brief Test object conversion between AST and variable systems
 */
void test_object_conversion(void) {
    printf("Testing object conversion...\n");
    
    // Create a variable object
    variable* obj = variable_create_object();
    variable* prop1 = variable_create_string("value1");
    variable* prop2 = variable_create_string("value2");
    
    variable_object_set(obj, "key1", prop1);
    variable_object_set(obj, "key2", prop2);
    
    // Convert to AST value
    ast_value* ast_val = ast_variable_to_value(obj);
    assert(ast_val != NULL);
    assert(ast_val->type == AST_VAL_OBJECT);
    assert(ast_val->value.object_value.pair_count == 2);
    
    // Convert back to variable
    variable* converted_obj = ast_value_to_variable(ast_val);
    assert(converted_obj != NULL);
    assert(variable_get_type(converted_obj) == VAR_OBJECT);
    assert(variable_object_size(converted_obj) == 2);
    
    // Check properties
    variable* check1 = variable_object_get(converted_obj, "key1");
    variable* check2 = variable_object_get(converted_obj, "key2");
    assert(check1 != NULL);
    assert(check2 != NULL);
    assert(strcmp(variable_to_string(check1), "value1") == 0);
    assert(strcmp(variable_to_string(check2), "value2") == 0);
    
    variable_unref(prop1);
    variable_unref(prop2);
    variable_unref(obj);
    variable_unref(converted_obj);
    ast_value_free(ast_val);
    
    printf("✓ Object conversion test passed\n");
}

/**
 * @brief Test nested object structure
 */
void test_nested_objects(void) {
    printf("Testing nested objects...\n");
    
    // Parse "{user: {name: \"Bob\", details: {age: 35}}}"
    const char* input = "{user: {name: \"Bob\", details: {age: 35}}}";
    token* tokens = lexer_enhanced_tokenize(input, "test");
    assert(tokens != NULL);
    
    parser_state state = {0};
    state.tokens = tokens;
    state.current_token = tokens;
    state.filename = "test";
    
    ast_node* node = ast_parse_primary(&state);
    assert(node != NULL);
    assert(node->type == AST_OBJECT_LITERAL);
    
    // Create evaluator
    store* variables = store_create();
    processor_context dummy_ctx = {0};
    ast_evaluator* evaluator = ast_evaluator_create(variables, &dummy_ctx);
    
    // Evaluate nested object
    ast_value* result = ast_evaluate(node, evaluator);
    assert(result != NULL);
    assert(result->type == AST_VAL_OBJECT);
    assert(result->value.object_value.pair_count == 1);
    
    // Check nested structure
    ast_object_pair* user_pair = &result->value.object_value.pairs[0];
    assert(strcmp(user_pair->key, "user") == 0);
    assert(user_pair->value->type == AST_VAL_OBJECT);
    assert(user_pair->value->value.object_value.pair_count == 2);
    
    ast_value_free(result);
    ast_evaluator_free(evaluator);
    store_destroy(variables);
    ast_free(node);
    token_list_free(tokens);
    
    printf("✓ Nested objects test passed\n");
}

int main() {
    printf("Running complete object system tests...\n\n");
    
    test_object_literal_basic();
    test_property_access_basic();
    test_object_conversion();
    test_nested_objects();
    
    printf("\n✅ All object system tests passed!\n");
    return 0;
}