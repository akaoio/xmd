/**
 * @file test_flow_simple.c
 * @brief Simple test suite for flow control system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/variable.h"
#include "../../include/flow.h"

/**
 * @brief Test basic flow context management
 */
void test_flow_context_lifecycle(void) {
    printf("Testing flow context lifecycle...\n");
    
    FlowContext* ctx = flow_context_new();
    assert(ctx != NULL);
    
    // Initially should be in continue state
    assert(flow_check_status(ctx) == FLOW_CONTINUE);
    
    flow_context_free(ctx);
    
    printf("✓ Flow context lifecycle tests passed\n");
}

/**
 * @brief Test break statement
 */
void test_break_statement(void) {
    printf("Testing break statements...\n");
    
    FlowContext* ctx = flow_context_new();
    
    // Execute break
    int result = flow_break_statement(ctx);
    assert(result == FLOW_BREAK);
    
    // Check that context is now in break state
    assert(flow_check_status(ctx) == FLOW_BREAK);
    
    flow_context_free(ctx);
    
    printf("✓ Break statement tests passed\n");
}

/**
 * @brief Test continue statement
 */
void test_continue_statement(void) {
    printf("Testing continue statements...\n");
    
    FlowContext* ctx = flow_context_new();
    
    // Execute continue
    int result = flow_continue_statement(ctx);
    assert(result == FLOW_CONTINUE);
    
    // Check that context remains in continue state
    assert(flow_check_status(ctx) == FLOW_CONTINUE);
    
    flow_context_free(ctx);
    
    printf("✓ Continue statement tests passed\n");
}

/**
 * @brief Test return statement
 */
void test_return_statement(void) {
    printf("Testing return statements...\n");
    
    FlowContext* ctx = flow_context_new();
    
    // Test return with value
    variable* return_val = variable_create_string("success");
    int result = flow_return_statement(ctx, return_val);
    assert(result == FLOW_RETURN);
    
    // Check that context is now in return state
    assert(flow_check_status(ctx) == FLOW_RETURN);
    
    // Check return value
    variable* retrieved_val = flow_get_return_value(ctx);
    assert(retrieved_val != NULL);
    assert(variable_get_type(retrieved_val) == VAR_STRING);
    assert(strcmp(variable_get_string(retrieved_val), "success") == 0);
    
    variable_unref(return_val);
    flow_context_free(ctx);
    
    printf("✓ Return statement tests passed\n");
}

/**
 * @brief Test return statement with null value
 */
void test_return_statement_null(void) {
    printf("Testing return statements with null...\n");
    
    FlowContext* ctx = flow_context_new();
    
    // Test return with null
    int result = flow_return_statement(ctx, NULL);
    assert(result == FLOW_RETURN);
    
    // Check return value
    variable* retrieved_val = flow_get_return_value(ctx);
    assert(retrieved_val != NULL);
    assert(variable_get_type(retrieved_val) == VAR_NULL);
    
    flow_context_free(ctx);
    
    printf("✓ Return statement null tests passed\n");
}

/**
 * @brief Test flow control state transitions
 */
void test_flow_state_transitions(void) {
    printf("Testing flow state transitions...\n");
    
    FlowContext* ctx = flow_context_new();
    
    // Start in continue state
    assert(flow_check_status(ctx) == FLOW_CONTINUE);
    
    // Transition to break
    flow_break_statement(ctx);
    assert(flow_check_status(ctx) == FLOW_BREAK);
    
    flow_context_free(ctx);
    
    // Test return state precedence
    ctx = flow_context_new();
    variable* return_val = variable_create_boolean(1);
    flow_return_statement(ctx, return_val);
    assert(flow_check_status(ctx) == FLOW_RETURN);
    
    // Return should take precedence over break
    flow_break_statement(ctx);
    assert(flow_check_status(ctx) == FLOW_RETURN);
    
    variable_unref(return_val);
    flow_context_free(ctx);
    
    printf("✓ Flow state transition tests passed\n");
}

/**
 * @brief Test edge cases and error handling
 */
void test_flow_edge_cases(void) {
    printf("Testing flow edge cases...\n");
    
    // Test NULL context handling (should not crash)
    int result = flow_break_statement(NULL);
    assert(result == FLOW_ERROR);
    
    result = flow_continue_statement(NULL);
    assert(result == FLOW_ERROR);
    
    result = flow_return_statement(NULL, NULL);
    assert(result == FLOW_ERROR);
    
    assert(flow_check_status(NULL) == FLOW_ERROR);
    assert(flow_get_return_value(NULL) == NULL);
    
    printf("✓ Flow edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Flow Control System Tests (Simple) ===\n");
    
    test_flow_context_lifecycle();
    test_break_statement();
    test_continue_statement();
    test_return_statement();
    test_return_statement_null();
    test_flow_state_transitions();
    test_flow_edge_cases();
    
    printf("\n✅ All flow control tests passed!\n");
    return 0;
}
