/**
 * @file test_executor.c
 * @brief Test suite for command execution system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../include/variable.h"
#include "../../include/store.h"
#include "../../include/executor.h"

// These functions are now implemented in the main library

/**
 * @brief Test basic command execution
 */
void test_basic_command_execution(void) {
    printf("Testing basic command execution...\n");
    
    ExecutorContext* ctx = executor_context_new();
    assert(ctx != NULL);
    
    CommandResult* result = NULL;
    
    // Test simple echo command
    int status = executor_run_command(ctx, "echo hello world", &result);
    assert(status == EXECUTOR_SUCCESS);
    assert(result != NULL);
    assert(result->exit_code == 0);
    assert(result->stdout_data != NULL);
    assert(strstr(result->stdout_data, "hello world") != NULL);
    
    command_result_free(result);
    executor_context_free(ctx);
    
    printf("✓ Basic command execution tests passed\n");
}

/**
 * @brief Test command execution with output capture
 */
void test_output_capture(void) {
    printf("Testing output capture...\n");
    
    ExecutorContext* ctx = executor_context_new();
    CommandResult* result = NULL;
    
    // Test stdout capture
    int status = executor_run_command(ctx, "echo stdout_test", &result);
    assert(status == EXECUTOR_SUCCESS);
    assert(result->stdout_data != NULL);
    assert(strstr(result->stdout_data, "stdout_test") != NULL);
    assert(result->stdout_size > 0);
    
    command_result_free(result);
    
    // Test stderr capture (use a command that naturally outputs to stderr)
    result = NULL;
    status = executor_run_command(ctx, "ls /nonexistent_directory_for_testing", &result);
    assert(status == EXECUTOR_SUCCESS);
    assert(result != NULL);
    assert(result->exit_code != 0); // ls should fail
    assert(result->stderr_data != NULL);
    assert(result->stderr_size > 0);
    
    command_result_free(result);
    executor_context_free(ctx);
    
    printf("✓ Output capture tests passed\n");
}

/**
 * @brief Test command execution with different exit codes
 */
void test_exit_codes(void) {
    printf("Testing exit codes...\n");
    
    ExecutorContext* ctx = executor_context_new();
    CommandResult* result = NULL;
    
    // Test successful command (exit code 0)
    int status = executor_run_command(ctx, "true", &result);
    assert(status == EXECUTOR_SUCCESS);
    assert(result->exit_code == 0);
    
    command_result_free(result);
    
    // Test failing command (exit code 1)
    result = NULL;
    status = executor_run_command(ctx, "false", &result);
    assert(status == EXECUTOR_SUCCESS); // Command ran successfully, but exit code is 1
    assert(result->exit_code == 1);
    
    command_result_free(result);
    
    // Test command with specific exit code (use false which exits with 1)
    result = NULL;
    status = executor_run_command(ctx, "false", &result);
    assert(status == EXECUTOR_SUCCESS);
    assert(result->exit_code == 1);
    
    command_result_free(result);
    executor_context_free(ctx);
    
    printf("✓ Exit code tests passed\n");
}

/**
 * @brief Test command execution with timeout
 */
void test_command_timeout(void) {
    printf("Testing command timeout...\n");
    
    ExecutorContext* ctx = executor_context_new();
    CommandResult* result = NULL;
    
    // Test command that completes within timeout
    int status = executor_run_with_timeout(ctx, "echo fast", 1000, &result);
    assert(status == EXECUTOR_SUCCESS);
    assert(result->exit_code == 0);
    
    command_result_free(result);
    
    // Test command that exceeds timeout
    result = NULL;
    status = executor_run_with_timeout(ctx, "sleep 2", 500, &result);
    assert(status == EXECUTOR_TIMEOUT);
    
    if (result) {
        command_result_free(result);
    }
    
    executor_context_free(ctx);
    
    printf("✓ Command timeout tests passed\n");
}

/**
 * @brief Test execution time measurement
 */
void test_execution_time(void) {
    printf("Testing execution time measurement...\n");
    
    ExecutorContext* ctx = executor_context_new();
    CommandResult* result = NULL;
    
    // Test that execution time is measured
    int status = executor_run_command(ctx, "sleep 0.1", &result);
    assert(status == EXECUTOR_SUCCESS);
    assert(result->execution_time_ms > 0);
    assert(result->execution_time_ms >= 100); // At least 100ms for sleep 0.1
    
    command_result_free(result);
    executor_context_free(ctx);
    
    printf("✓ Execution time tests passed\n");
}

/**
 * @brief Test invalid command handling
 */
void test_invalid_commands(void) {
    printf("Testing invalid command handling...\n");
    
    ExecutorContext* ctx = executor_context_new();
    CommandResult* result = NULL;
    
    // Test non-existent command
    int status = executor_run_command(ctx, "nonexistent_command_12345", &result);
    // Should complete but with non-zero exit code or error
    assert(status == EXECUTOR_SUCCESS || status == EXECUTOR_ERROR);
    
    if (result) {
        command_result_free(result);
    }
    
    // Test empty command
    result = NULL;
    status = executor_run_command(ctx, "", &result);
    assert(status == EXECUTOR_ERROR);
    
    if (result) {
        command_result_free(result);
    }
    
    // Test NULL command
    result = NULL;
    status = executor_run_command(ctx, NULL, &result);
    assert(status == EXECUTOR_ERROR);
    
    executor_context_free(ctx);
    
    printf("✓ Invalid command tests passed\n");
}

/**
 * @brief Test edge cases and error handling
 */
void test_executor_edge_cases(void) {
    printf("Testing executor edge cases...\n");
    
    // Test NULL context
    CommandResult* result = NULL;
    int status = executor_run_command(NULL, "echo test", &result);
    assert(status == EXECUTOR_ERROR);
    
    // Test context lifecycle
    ExecutorContext* ctx = executor_context_new();
    assert(ctx != NULL);
    executor_context_free(ctx);
    
    // Test double free (should not crash)
    executor_context_free(NULL);
    
    // Test result cleanup
    command_result_free(NULL); // Should not crash
    
    printf("✓ Executor edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Command Executor Tests ===\n");
    
    test_basic_command_execution();
    test_output_capture();
    test_exit_codes();
    test_command_timeout();
    test_execution_time();
    test_invalid_commands();
    test_executor_edge_cases();
    
    printf("\n✅ All executor tests passed!\n");
    return 0;
}
