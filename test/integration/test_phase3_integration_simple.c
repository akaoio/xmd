/**
 * @file test_phase3_integration_simple.c
 * @brief Simple integration tests for Phase 3 control flow system
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
#include "../../include/loop.h"
#include "../../include/flow.h"
#include "../../include/error.h"

/**
 * @brief Test integration of conditionals with variable system
 */
void test_conditional_variable_integration(void) {
    printf("Testing conditional variable integration...\n");
    
    store* s = store_create();
    ConditionContext* ctx = condition_context_new();
    
    // Set up test variables
    variable* is_admin = variable_create_boolean(1);
    variable* username = variable_create_string("admin");
    store_set(s, "is_admin", is_admin);
    store_set(s, "username", username);
    
    // Test conditional processing
    char* result = NULL;
    int status = if_statement_process(ctx, "{{is_admin}}", 
                                     "Welcome Administrator!", 
                                     "Access denied", 
                                     s, &result);
    
    assert(status == 0);
    assert(result != NULL);
    assert(strstr(result, "Administrator") != NULL);
    
    free(result);
    variable_unref(is_admin);
    variable_unref(username);
    store_destroy(s);
    condition_context_free(ctx);
    
    printf("✓ Conditional variable integration test passed\n");
}

/**
 * @brief Test integration of loops with variable system
 */
void test_loop_variable_integration(void) {
    printf("Testing loop variable integration...\n");
    
    store* s = store_create();
    LoopContext* ctx = loop_context_new();
    
    // Create array of items
    variable* items[2];
    items[0] = variable_create_string("first");
    items[1] = variable_create_string("second");
    
    variable* array = variable_new_array(items, 2);
    store_set(s, "items", array);
    
    char* result = NULL;
    int status = for_loop_process(ctx, "item", "items", "Item: content\n", s, &result);
    
    assert(status == LOOP_SUCCESS);
    assert(result != NULL);
    assert(strlen(result) > 0);
    
    free(result);
    
    for (int i = 0; i < 2; i++) {
        variable_unref(items[i]);
    }
    variable_unref(array);
    store_destroy(s);
    loop_context_free(ctx);
    
    printf("✓ Loop variable integration test passed\n");
}

/**
 * @brief Test flow control integration
 */
void test_flow_control_integration(void) {
    printf("Testing flow control integration...\n");
    
    FlowContext* ctx = flow_context_new();
    
    // Test normal flow
    assert(flow_check_status(ctx) == FLOW_CONTINUE);
    
    // Test break
    flow_break_statement(ctx);
    assert(flow_check_status(ctx) == FLOW_BREAK);
    
    flow_context_free(ctx);
    
    // Test return with value
    ctx = flow_context_new();
    variable* return_val = variable_create_number(42.0);
    flow_return_statement(ctx, return_val);
    
    assert(flow_check_status(ctx) == FLOW_RETURN);
    variable* retrieved = flow_get_return_value(ctx);
    assert(retrieved != NULL);
    assert(variable_get_type(retrieved) == VAR_NUMBER);
    
    variable_unref(return_val);
    flow_context_free(ctx);
    
    printf("✓ Flow control integration test passed\n");
}

/**
 * @brief Test error handling integration
 */
void test_error_handling_integration(void) {
    printf("Testing error handling integration...\n");
    
    ErrorContext* ctx = error_context_new();
    
    // Test basic error handling
    try_block_begin(ctx);
    error_throw(ctx, ERROR_RUNTIME, "Test error", __FILE__, __LINE__);
    try_block_end(ctx);
    
    catch_block_begin(ctx, ERROR_RUNTIME);
    assert(error_is_caught(ctx) == 1);
    
    XMDError* error = error_get_current(ctx);
    assert(error != NULL);
    assert(error->type == ERROR_RUNTIME);
    assert(strcmp(error->message, "Test error") == 0);
    
    catch_block_end(ctx);
    error_context_free(ctx);
    
    printf("✓ Error handling integration test passed\n");
}

/**
 * @brief Test combined control flow scenarios
 */
void test_combined_control_flow(void) {
    printf("Testing combined control flow scenarios...\n");
    
    store* s = store_create();
    ConditionContext* cond_ctx = condition_context_new();
    LoopContext* loop_ctx = loop_context_new();
    FlowContext* flow_ctx = flow_context_new();
    ErrorContext* error_ctx = error_context_new();
    
    // Set up test data
    variable* active = variable_create_boolean(1);
    variable* count = variable_create_number(3.0);
    store_set(s, "active", active);
    store_set(s, "count", count);
    
    // Test conditional with loop context
    if (condition_evaluate(cond_ctx, "{{active}}", s) == CONDITION_TRUE) {
        // Simulate some processing that might break
        flow_break_statement(flow_ctx);
        assert(flow_check_status(flow_ctx) == FLOW_BREAK);
    }
    
    // Test error handling with other contexts
    try_block_begin(error_ctx);
    // Simulate an error condition
    if (condition_evaluate(cond_ctx, "{{count}}", s) == CONDITION_TRUE) {
        error_throw(error_ctx, ERROR_VARIABLE, "Variable processing error", __FILE__, __LINE__);
    }
    try_block_end(error_ctx);
    
    catch_block_begin(error_ctx, ERROR_VARIABLE);
    assert(error_is_caught(error_ctx) == 1);
    catch_block_end(error_ctx);
    
    variable_unref(active);
    variable_unref(count);
    store_destroy(s);
    condition_context_free(cond_ctx);
    loop_context_free(loop_ctx);
    flow_context_free(flow_ctx);
    error_context_free(error_ctx);
    
    printf("✓ Combined control flow test passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Phase 3 Integration Tests (Simple) ===\n");
    
    test_conditional_variable_integration();
    test_loop_variable_integration();
    test_flow_control_integration();
    test_error_handling_integration();
    test_combined_control_flow();
    
    printf("\n✅ All Phase 3 integration tests passed!\n");
    return 0;
}