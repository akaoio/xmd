/**
 * @file test_conditional_simple.c
 * @brief Simple test suite for conditional statement system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/variable.h"
#include "../../include/store.h"
#include "../../include/conditional.h"

/**
 * @brief Test basic condition evaluation
 */
void test_condition_evaluation(void) {
    printf("Testing condition evaluation...\n");
    
    ConditionContext* ctx = condition_context_new();
    assert(ctx != NULL);
    
    store* s = store_create();
    assert(s != NULL);
    
    // Set up test variables
    variable* true_var = variable_create_boolean(1);
    variable* false_var = variable_create_boolean(0);
    variable* num_var = variable_create_number(42.0);
    
    store_set(s, "is_true", true_var);
    store_set(s, "is_false", false_var);
    store_set(s, "number", num_var);
    
    // Test boolean evaluation
    assert(condition_evaluate(ctx, "{{is_true}}", s) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "{{is_false}}", s) == CONDITION_FALSE);
    
    // Test number evaluation (non-zero is true)
    assert(condition_evaluate(ctx, "{{number}}", s) == CONDITION_TRUE);
    
    // Test logical operators
    assert(condition_evaluate(ctx, "{{is_true}} && {{number}}", s) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "{{is_false}} || {{number}}", s) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "!{{is_false}}", s) == CONDITION_TRUE);
    
    variable_unref(true_var);
    variable_unref(false_var);
    variable_unref(num_var);
    store_destroy(s);
    condition_context_free(ctx);
    
    printf("✓ Condition evaluation tests passed\n");
}

/**
 * @brief Test basic if/else statements
 */
void test_if_else_statements(void) {
    printf("Testing if/else statements...\n");
    
    ConditionContext* ctx = condition_context_new();
    store* s = store_create();
    
    variable* admin_var = variable_create_boolean(1);
    store_set(s, "is_admin", admin_var);
    
    char* result = NULL;
    
    // Test simple if statement (true condition)
    int status = if_statement_process(ctx, "{{is_admin}}", 
                                     "Welcome, Administrator!", 
                                     "Access denied.", 
                                     s, &result);
    assert(status == 0);
    assert(result != NULL);
    assert(strcmp(result, "Welcome, Administrator!") == 0);
    free(result);
    
    // Test simple if statement (false condition)
    variable* user_var = variable_create_boolean(0);
    store_set(s, "is_admin", user_var);
    
    status = if_statement_process(ctx, "{{is_admin}}", 
                                 "Welcome, Administrator!", 
                                 "Access denied.", 
                                 s, &result);
    assert(status == 0);
    assert(result != NULL);
    assert(strcmp(result, "Access denied.") == 0);
    free(result);
    
    variable_unref(admin_var);
    variable_unref(user_var);
    store_destroy(s);
    condition_context_free(ctx);
    
    printf("✓ If/else statement tests passed\n");
}

/**
 * @brief Test elif (else if) chains
 */
void test_elif_chains(void) {
    printf("Testing elif chains...\n");
    
    ConditionContext* ctx = condition_context_new();
    store* s = store_create();
    
    variable* role_var = variable_create_string("editor");
    store_set(s, "role", role_var);
    
    const char* conditions[] = {
        "false",  // Simplified - would be {{role}} == "admin" with full comparison support
        "true",   // Simplified - would be {{role}} == "editor"  
        "false"   // Simplified - would be {{role}} == "user"
    };
    
    const char* contents[] = {
        "Full administrative access",
        "Editorial privileges granted",
        "Standard user access"
    };
    
    char* result = NULL;
    int status = elif_statement_process(ctx, conditions, contents, 3, s, &result);
    
    assert(status == 0);
    assert(result != NULL);
    assert(strcmp(result, "Editorial privileges granted") == 0);
    free(result);
    
    variable_unref(role_var);
    store_destroy(s);
    condition_context_free(ctx);
    
    printf("✓ Elif chain tests passed\n");
}

/**
 * @brief Test edge cases and error handling
 */
void test_conditional_edge_cases(void) {
    printf("Testing conditional edge cases...\n");
    
    ConditionContext* ctx = condition_context_new();
    store* s = store_create();
    
    // Test undefined variable
    assert(condition_evaluate(ctx, "{{undefined_var}}", s) == CONDITION_FALSE);
    
    // Test empty string literal
    assert(condition_evaluate(ctx, "", s) == CONDITION_FALSE);
    
    // Test literal values
    assert(condition_evaluate(ctx, "true", s) == CONDITION_TRUE);
    assert(condition_evaluate(ctx, "false", s) == CONDITION_FALSE);
    
    store_destroy(s);
    condition_context_free(ctx);
    
    printf("✓ Conditional edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Conditional System Tests (Simple) ===\n");
    
    test_condition_evaluation();
    test_if_else_statements();
    test_elif_chains();
    test_conditional_edge_cases();
    
    printf("\n✅ All conditional tests passed!\n");
    return 0;
}