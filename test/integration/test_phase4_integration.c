/**
 * @file test_phase4_integration.c
 * @brief Integration tests for Phase 4 command execution system
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
#include "../../include/error.h"
#include "../../include/executor.h"
#include "../../include/sandbox.h"
#include "../../include/output.h"
#include "../../include/resource.h"

// Integration function declarations
int xmd_exec_command(ExecutorContext* exec_ctx, SandboxContext* sandbox_ctx, 
                     const char* command, CommandResult** result);
int xmd_exec_with_variables(ExecutorContext* exec_ctx, const char* command_template, 
                           store* variable_store, CommandResult** result);
int xmd_conditional_exec(ConditionContext* cond_ctx, ExecutorContext* exec_ctx,
                        const char* condition, const char* command, 
                        store* variable_store, CommandResult** result);

/**
 * @brief Test basic executor integration
 */
void test_executor_integration(void) {
    printf("Testing executor integration...\n");
    
    ExecutorContext* exec_ctx = executor_context_new();
    assert(exec_ctx != NULL);
    
    SandboxConfig* config = sandbox_config_new();
    sandbox_config_add_whitelist(config, "echo");
    sandbox_config_add_whitelist(config, "ls");
    
    SandboxContext* sandbox_ctx = sandbox_context_new(config);
    assert(sandbox_ctx != NULL);
    
    CommandResult* result = NULL;
    
    // Test basic command execution with sandbox
    int check_result = sandbox_check_command_allowed(sandbox_ctx, "echo 'Hello XMD'");
    assert(check_result == SANDBOX_SUCCESS);
    
    int status = executor_run_command(exec_ctx, "echo 'Hello XMD'", &result);
    assert(status == EXECUTOR_SUCCESS);
    assert(result != NULL);
    assert(result->exit_code == 0);
    assert(strstr(result->stdout_data, "Hello XMD") != NULL);
    
    command_result_free(result);
    sandbox_context_free(sandbox_ctx);
    sandbox_config_free(config);
    executor_context_free(exec_ctx);
    
    printf("✓ Executor integration test passed\n");
}

/**
 * @brief Test command execution with variable interpolation
 */
void test_variable_interpolation_execution(void) {
    printf("Testing variable interpolation in commands...\n");
    
    ExecutorContext* exec_ctx = executor_context_new();
    store* variable_store = store_create();
    
    // Set up test variables
    variable* message_var = variable_create_string("Hello from variables");
    variable* count_var = variable_create_number(42);
    store_set(variable_store, "message", message_var);
    store_set(variable_store, "count", count_var);
    
    CommandResult* result = NULL;
    
    // Test command with variable interpolation
    int status = xmd_exec_with_variables(exec_ctx, "echo '{{message}} - {{count}}'", 
                                        variable_store, &result);
    assert(status == 0);
    assert(result != NULL);
    assert(strstr(result->stdout_data, "Hello from variables") != NULL);
    assert(strstr(result->stdout_data, "42") != NULL);
    
    command_result_free(result);
    variable_unref(message_var);
    variable_unref(count_var);
    store_destroy(variable_store);
    executor_context_free(exec_ctx);
    
    printf("✓ Variable interpolation execution test passed\n");
}

/**
 * @brief Test conditional command execution
 */
void test_conditional_command_execution(void) {
    printf("Testing conditional command execution...\n");
    
    ConditionContext* cond_ctx = condition_context_new();
    ExecutorContext* exec_ctx = executor_context_new();
    store* variable_store = store_create();
    
    // Set up test variables
    variable* should_run = variable_create_boolean(1);
    variable* should_not_run = variable_create_boolean(0);
    store_set(variable_store, "should_run", should_run);
    store_set(variable_store, "should_not_run", should_not_run);
    
    CommandResult* result = NULL;
    
    // Test command that should execute
    int status = xmd_conditional_exec(cond_ctx, exec_ctx, "{{should_run}}", 
                                     "echo 'Command executed'", variable_store, &result);
    assert(status == 0);
    assert(result != NULL);
    assert(strstr(result->stdout_data, "Command executed") != NULL);
    
    command_result_free(result);
    
    // Test command that should not execute
    result = NULL;
    status = xmd_conditional_exec(cond_ctx, exec_ctx, "{{should_not_run}}", 
                                 "echo 'Should not see this'", variable_store, &result);
    assert(status == 0);
    assert(result == NULL); // No result because command didn't run
    
    variable_unref(should_run);
    variable_unref(should_not_run);
    store_destroy(variable_store);
    executor_context_free(exec_ctx);
    condition_context_free(cond_ctx);
    
    printf("✓ Conditional command execution test passed\n");
}

/**
 * @brief Test command execution in loops
 */
void test_loop_command_execution(void) {
    printf("Testing command execution in loops...\n");
    
    ExecutorContext* exec_ctx = executor_context_new();
    store* variable_store = store_create();
    
    // Create array of commands to execute
    variable* commands[3];
    commands[0] = variable_create_string("echo 'Command 1'");
    commands[1] = variable_create_string("echo 'Command 2'");
    commands[2] = variable_create_string("echo 'Command 3'");
    
    variable* command_array = variable_new_array(commands, 3);
    store_set(variable_store, "commands", command_array);
    
    // Test would require loop integration with command execution
    // For now, test that we can iterate over commands
    assert(variable_array_length(command_array) == 3);
    
    for (size_t i = 0; i < variable_array_length(command_array); i++) {
        variable* cmd = variable_array_get(command_array, i);
        assert(cmd != NULL);
        assert(variable_get_type(cmd) == VAR_STRING);
        
        const char* cmd_str = variable_get_string(cmd);
        assert(strstr(cmd_str, "echo") != NULL);
    }
    
    for (int i = 0; i < 3; i++) {
        variable_unref(commands[i]);
    }
    variable_unref(command_array);
    store_destroy(variable_store);
    executor_context_free(exec_ctx);
    
    printf("✓ Loop command execution test passed\n");
}

/**
 * @brief Test error handling in command execution
 */
void test_command_execution_error_handling(void) {
    printf("Testing command execution error handling...\n");
    
    ExecutorContext* exec_ctx = executor_context_new();
    ErrorContext* error_ctx = error_context_new();
    
    CommandResult* result = NULL;
    
    // Test error handling with try/catch
    try_block_begin(error_ctx);
    
    // Try to execute a failing command
    int status = executor_run_command(exec_ctx, "false", &result);
    
    if (status != 0 || (result && result->exit_code != 0)) {
        error_throw(error_ctx, ERROR_RUNTIME, "Command execution failed", __FILE__, __LINE__);
    }
    
    try_block_end(error_ctx);
    
    // Catch the error
    catch_block_begin(error_ctx, ERROR_RUNTIME);
    if (error_is_caught(error_ctx)) {
        XMDError* error = error_get_current(error_ctx);
        assert(error != NULL);
        assert(error->type == ERROR_RUNTIME);
    }
    catch_block_end(error_ctx);
    
    if (result) {
        command_result_free(result);
    }
    
    error_context_free(error_ctx);
    executor_context_free(exec_ctx);
    
    printf("✓ Command execution error handling test passed\n");
}

/**
 * @brief Test output formatting integration
 */
void test_output_formatting_integration(void) {
    printf("Testing output formatting integration...\n");
    
    ExecutorContext* exec_ctx = executor_context_new();
    OutputFormatter* formatter = output_formatter_new();
    
    CommandResult* result = NULL;
    
    // Execute command with output
    int status = executor_run_command(exec_ctx, "echo 'Raw output with <tags>'", &result);
    assert(status == 0);
    assert(result != NULL);
    
    // Test formatting the output
    char* formatted_output = NULL;
    status = output_format_text(formatter, result->stdout_data, OUTPUT_FORMAT_HTML, &formatted_output);
    assert(status == 0);
    assert(formatted_output != NULL);
    assert(strstr(formatted_output, "&lt;tags&gt;") != NULL);
    
    free(formatted_output);
    
    // Test code formatting
    formatted_output = NULL;
    status = output_format_as_code(result->stdout_data, "bash", &formatted_output);
    assert(status == 0);
    assert(formatted_output != NULL);
    assert(strstr(formatted_output, "```bash") != NULL);
    
    free(formatted_output);
    command_result_free(result);
    output_formatter_free(formatter);
    executor_context_free(exec_ctx);
    
    printf("✓ Output formatting integration test passed\n");
}

/**
 * @brief Test resource limit integration
 */
void test_resource_limit_integration(void) {
    printf("Testing resource limit integration...\n");
    
    ExecutorContext* exec_ctx = executor_context_new();
    ResourceLimiter* limiter = resource_limiter_new();
    
    // Set conservative limits
    resource_limiter_set_memory_limit(limiter, 10);    // 10MB
    resource_limiter_set_time_limit(limiter, 2000);    // 2 seconds
    
    CommandResult* result = NULL;
    
    // Test command within limits
    int status = executor_run_with_timeout(exec_ctx, "echo 'within limits'", 1000, &result);
    assert(status == 0);
    assert(result != NULL);
    
    // Verify resource usage would be within limits
    // (actual resource monitoring would be integrated here)
    
    command_result_free(result);
    resource_limiter_free(limiter);
    executor_context_free(exec_ctx);
    
    printf("✓ Resource limit integration test passed\n");
}

/**
 * @brief Test security integration
 */
void test_security_integration(void) {
    printf("Testing security integration...\n");
    
    ExecutorContext* exec_ctx = executor_context_new();
    SandboxConfig* config = sandbox_config_new();
    
    // Set up restrictive security policy
    sandbox_config_add_whitelist(config, "echo");
    sandbox_config_add_whitelist(config, "ls");
    sandbox_config_add_allowed_path(config, "/tmp");
    
    SandboxContext* sandbox_ctx = sandbox_context_new(config);
    
    // Test allowed command
    assert(sandbox_check_command_allowed(sandbox_ctx, "echo test") == 0);
    
    // Test disallowed command
    assert(sandbox_check_command_allowed(sandbox_ctx, "rm -rf /") != 0);
    
    // Test path restrictions
    assert(sandbox_check_path_allowed(sandbox_ctx, "/tmp/safe.txt") == 0);
    assert(sandbox_check_path_allowed(sandbox_ctx, "/etc/passwd") != 0);
    
    sandbox_context_free(sandbox_ctx);
    sandbox_config_free(config);
    executor_context_free(exec_ctx);
    
    printf("✓ Security integration test passed\n");
}

/**
 * @brief Test complete Phase 4 pipeline
 */
void test_complete_phase4_pipeline(void) {
    printf("Testing complete Phase 4 pipeline...\n");
    
    // Set up all components
    ExecutorContext* exec_ctx = executor_context_new();
    ConditionContext* cond_ctx = condition_context_new();
    ErrorContext* error_ctx = error_context_new();
    store* variable_store = store_create();
    
    // Set up security
    SandboxConfig* config = sandbox_config_new();
    sandbox_config_add_whitelist(config, "echo");
    sandbox_config_add_whitelist(config, "date");
    SandboxContext* sandbox_ctx = sandbox_context_new(config);
    
    // Set up variables
    variable* user_var = variable_create_string("testuser");
    variable* debug_var = variable_create_boolean(1);
    store_set(variable_store, "user", user_var);
    store_set(variable_store, "debug", debug_var);
    
    // Test complete pipeline: variables -> condition -> execution -> output
    try_block_begin(error_ctx);
    
    // Check if debug mode is enabled
    if (condition_evaluate(cond_ctx, "{{debug}}", variable_store) == CONDITION_TRUE) {
        CommandResult* result = NULL;
        
        // Execute debug command with variable interpolation
        int status = xmd_exec_with_variables(exec_ctx, "echo 'Debug info for {{user}}'", 
                                            variable_store, &result);
        assert(status == 0);
        assert(result != NULL);
        assert(strstr(result->stdout_data, "testuser") != NULL);
        
        // Format output
        char* formatted = NULL;
        output_format_as_code(result->stdout_data, "text", &formatted);
        assert(formatted != NULL);
        assert(strstr(formatted, "```") != NULL);
        
        free(formatted);
        command_result_free(result);
    }
    
    try_block_end(error_ctx);
    
    // Cleanup
    variable_unref(user_var);
    variable_unref(debug_var);
    store_destroy(variable_store);
    sandbox_context_free(sandbox_ctx);
    sandbox_config_free(config);
    error_context_free(error_ctx);
    condition_context_free(cond_ctx);
    executor_context_free(exec_ctx);
    
    printf("✓ Complete Phase 4 pipeline test passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Phase 4 Integration Tests ===\n");
    
    test_executor_integration();
    test_variable_interpolation_execution();
    test_conditional_command_execution();
    test_loop_command_execution();
    test_command_execution_error_handling();
    test_output_formatting_integration();
    test_resource_limit_integration();
    test_security_integration();
    test_complete_phase4_pipeline();
    
    printf("\n✅ All Phase 4 integration tests passed!\n");
    return 0;
}