/**
 * @file test_conditional.c
 * @brief Test suite for conditional statement system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/variable.h"
#include "../include/store.h"
#include "../include/template.h"

// Forward declarations for conditional functions
typedef struct conditional_context ConditionContext;
typedef enum {
    CONDITION_TRUE = 1,
    CONDITION_FALSE = 0,
    CONDITION_ERROR = -1
} ConditionResult;

// Function declarations that we'll implement
ConditionContext* condition_context_new(void);
void condition_context_free(ConditionContext* ctx);
int condition_evaluate(ConditionContext* ctx, const char* expression, VariableStore* store);
int if_statement_process(ConditionContext* ctx, const char* condition, const char* true_content, const char* false_content, VariableStore* store, char** result);
int elif_statement_process(ConditionContext* ctx, const char* conditions[], const char* contents[], int count, VariableStore* store, char** result);

/**
 * @brief Test basic condition evaluation
 */
void test_condition_evaluation(void) {
    printf("Testing condition evaluation...\n");
    
    ConditionContext* ctx = condition_context_new();
    assert(ctx != NULL);
    
    VariableStore* store = variable_store_new();
    assert(store != NULL);
    
    // Set up test variables
    Variable* true_var = variable_new_boolean(1);
    Variable* false_var = variable_new_boolean(0);
    Variable* num_var = variable_new_number(42.0);
    Variable* str_var = variable_new_string("hello");
    
    variable_store_set(store, "is_true", true_var);
    variable_store_set(store, "is_false", false_var);
    variable_store_set(store, "number", num_var);
    variable_store_set(store, "text", str_var);
    
    // Test boolean evaluation
    assert(condition_evaluate(ctx, "{{is_true}}", store) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "{{is_false}}", store) == CONDITION_FALSE);
    
    // Test number evaluation (non-zero is true)
    assert(condition_evaluate(ctx, "{{number}}", store) == CONDITION_TRUE);
    
    // Test string evaluation (non-empty is true)
    assert(condition_evaluate(ctx, "{{text}}", store) == CONDITION_TRUE);
    
    // Test comparison operators
    assert(condition_evaluate(ctx, "{{number}} > 40", store) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "{{number}} < 40", store) == CONDITION_FALSE);
    assert(condition_evaluate(ctx, "{{number}} == 42", store) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "{{text}} == \"hello\"", store) == CONDITION_TRUE);
    
    // Test logical operators
    assert(condition_evaluate(ctx, "{{is_true}} && {{number}} > 40", store) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "{{is_false}} || {{number}} > 40", store) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "!{{is_false}}", store) == CONDITION_TRUE);
    
    variable_unref(true_var);
    variable_unref(false_var);
    variable_unref(num_var);
    variable_unref(str_var);
    variable_store_free(store);
    condition_context_free(ctx);
    
    printf("✓ Condition evaluation tests passed\n");
}

/**
 * @brief Test basic if/else statements
 */
void test_if_else_statements(void) {
    printf("Testing if/else statements...\n");
    
    ConditionContext* ctx = condition_context_new();
    VariableStore* store = variable_store_new();
    
    Variable* admin_var = variable_new_boolean(1);
    variable_store_set(store, "is_admin", admin_var);
    
    char* result = NULL;
    
    // Test simple if statement (true condition)
    int status = if_statement_process(ctx, "{{is_admin}}", 
                                     "Welcome, Administrator!", 
                                     "Access denied.", 
                                     store, &result);
    assert(status == 0);
    assert(result != NULL);
    assert(strcmp(result, "Welcome, Administrator!") == 0);
    free(result);
    
    // Test simple if statement (false condition)
    Variable* user_var = variable_new_boolean(0);
    variable_store_set(store, "is_admin", user_var);
    
    status = if_statement_process(ctx, "{{is_admin}}", 
                                 "Welcome, Administrator!", 
                                 "Access denied.", 
                                 store, &result);
    assert(status == 0);
    assert(result != NULL);
    assert(strcmp(result, "Access denied.") == 0);
    free(result);
    
    variable_unref(admin_var);
    variable_unref(user_var);
    variable_store_free(store);
    condition_context_free(ctx);
    
    printf("✓ If/else statement tests passed\n");
}

/**
 * @brief Test elif (else if) chains
 */
void test_elif_chains(void) {
    printf("Testing elif chains...\n");
    
    ConditionContext* ctx = condition_context_new();
    VariableStore* store = variable_store_new();
    
    Variable* role_var = variable_new_string("editor");
    variable_store_set(store, "role", role_var);
    
    const char* conditions[] = {
        "{{role}} == \"admin\"",
        "{{role}} == \"editor\"", 
        "{{role}} == \"user\""
    };
    
    const char* contents[] = {
        "Full administrative access",
        "Editorial privileges granted",
        "Standard user access"
    };
    
    char* result = NULL;
    int status = elif_statement_process(ctx, conditions, contents, 3, store, &result);
    
    assert(status == 0);
    assert(result != NULL);
    assert(strcmp(result, "Editorial privileges granted") == 0);
    free(result);
    
    variable_unref(role_var);
    variable_store_free(store);
    condition_context_free(ctx);
    
    printf("✓ Elif chain tests passed\n");
}

/**
 * @brief Test nested conditionals
 */
void test_nested_conditionals(void) {
    printf("Testing nested conditionals...\n");
    
    ConditionContext* ctx = condition_context_new();
    VariableStore* store = variable_store_new();
    
    Variable* is_logged_in = variable_new_boolean(1);
    Variable* is_premium = variable_new_boolean(1);
    variable_store_set(store, "logged_in", is_logged_in);
    variable_store_set(store, "premium", is_premium);
    
    // Test nested condition logic
    assert(condition_evaluate(ctx, "{{logged_in}} && {{premium}}", store) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "{{logged_in}} && !{{premium}}", store) == CONDITION_FALSE);
    
    variable_unref(is_logged_in);
    variable_unref(is_premium);
    variable_store_free(store);
    condition_context_free(ctx);
    
    printf("✓ Nested conditional tests passed\n");
}

/**
 * @brief Test edge cases and error handling
 */
void test_conditional_edge_cases(void) {
    printf("Testing conditional edge cases...\n");
    
    ConditionContext* ctx = condition_context_new();
    VariableStore* store = variable_store_new();
    
    // Test undefined variable
    assert(condition_evaluate(ctx, "{{undefined_var}}", store) == CONDITION_FALSE);
    
    // Test empty string condition
    Variable* empty_str = variable_new_string("");
    variable_store_set(store, "empty", empty_str);
    assert(condition_evaluate(ctx, "{{empty}}", store) == CONDITION_FALSE);
    
    // Test null variable
    Variable* null_var = variable_new_null();
    variable_store_set(store, "null_val", null_var);
    assert(condition_evaluate(ctx, "{{null_val}}", store) == CONDITION_FALSE);
    
    // Test malformed expressions
    assert(condition_evaluate(ctx, "{{invalid", store) == CONDITION_ERROR);
    assert(condition_evaluate(ctx, "invalid}}", store) == CONDITION_ERROR);
    
    variable_unref(empty_str);
    variable_unref(null_var);
    variable_store_free(store);
    condition_context_free(ctx);
    
    printf("✓ Conditional edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Conditional System Tests ===\n");
    
    test_condition_evaluation();
    test_if_else_statements();
    test_elif_chains();
    test_nested_conditionals();
    test_conditional_edge_cases();
    
    printf("\n✅ All conditional tests passed!\n");
    return 0;
}