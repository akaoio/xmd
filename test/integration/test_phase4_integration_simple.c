/**
 * @file test_phase4_integration_simple.c
 * @brief Simple integration tests for Phase 4 command execution system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/variable.h"
#include "../../include/store.h"
#include "../../include/executor.h"
#include "../../include/sandbox.h"
#include "../../include/output.h"
#include "../../include/resource.h"

/**
 * @brief Test basic executor integration
 */
void test_executor_integration(void) {
    printf("Testing executor integration...\n");
    
    ExecutorContext* exec_ctx = executor_context_new();
    assert(exec_ctx != NULL);
    
    SandboxConfig* config = sandbox_config_new();
    assert(config != NULL);
    
    // Add echo to whitelist
    int add_result = sandbox_config_add_whitelist(config, "echo");
    assert(add_result == SANDBOX_SUCCESS);
    
    SandboxContext* sandbox_ctx = sandbox_context_new(config);
    assert(sandbox_ctx != NULL);
    
    CommandResult* result = NULL;
    
    // Test basic command execution with sandbox
    int check_result = sandbox_check_command_allowed(sandbox_ctx, "echo Hello XMD");
    assert(check_result == SANDBOX_SUCCESS);
    
    int status = executor_run_command(exec_ctx, "echo Hello XMD", &result);
    assert(status == EXECUTOR_SUCCESS);
    assert(result != NULL);
    assert(result->exit_code == 0);
    assert(strstr(result->stdout_data, "Hello XMD") != NULL);
    
    command_result_free(result);
    sandbox_context_free(sandbox_ctx);
    sandbox_config_free(config);
    executor_context_free(exec_ctx);
    
    printf("Executor integration test passed.\n");
}

/**
 * @brief Test output formatting integration
 */
void test_output_integration(void) {
    printf("Testing output formatting integration...\n");
    
    OutputFormatter* formatter = output_formatter_new();
    assert(formatter != NULL);
    
    const char* test_input = "Hello <world> & \"everyone\"!";
    char* formatted_output = NULL;
    
    // Test HTML escaping
    int result = output_format_text(formatter, test_input, OUTPUT_FORMAT_HTML, &formatted_output);
    assert(result == OUTPUT_SUCCESS);
    assert(formatted_output != NULL);
    assert(strstr(formatted_output, "&lt;world&gt;") != NULL);
    assert(strstr(formatted_output, "&amp;") != NULL);
    assert(strstr(formatted_output, "&quot;everyone&quot;") != NULL);
    
    free(formatted_output);
    output_formatter_free(formatter);
    
    printf("Output formatting integration test passed.\n");
}

/**
 * @brief Test resource monitoring integration
 */
void test_resource_integration(void) {
    printf("Testing resource monitoring integration...\n");
    
    ResourceMonitor* monitor = resource_monitor_new();
    assert(monitor != NULL);
    
    ResourceLimiter* limiter = resource_limiter_new();
    assert(limiter != NULL);
    
    // Start monitoring
    int start_result = resource_monitor_start(monitor);
    assert(start_result == RESOURCE_SUCCESS);
    
    // Get usage
    ResourceUsage usage;
    int usage_result = resource_monitor_get_usage(monitor, &usage);
    assert(usage_result == RESOURCE_SUCCESS);
    
    // Check limits (should be within default limits)
    int limit_result = resource_limiter_check_limits(limiter, &usage);
    assert(limit_result == RESOURCE_SUCCESS);
    
    // Stop monitoring
    int stop_result = resource_monitor_stop(monitor);
    assert(stop_result == RESOURCE_SUCCESS);
    
    resource_monitor_free(monitor);
    resource_limiter_free(limiter);
    
    printf("Resource monitoring integration test passed.\n");
}

/**
 * @brief Test complete Phase 4 pipeline
 */
void test_complete_phase4_pipeline(void) {
    printf("Testing complete Phase 4 pipeline...\n");
    
    // Set up all components
    ExecutorContext* exec_ctx = executor_context_new();
    assert(exec_ctx != NULL);
    
    SandboxConfig* sandbox_config = sandbox_config_new();
    assert(sandbox_config != NULL);
    
    sandbox_config_add_whitelist(sandbox_config, "echo");
    sandbox_config_add_whitelist(sandbox_config, "date");
    
    SandboxContext* sandbox_ctx = sandbox_context_new(sandbox_config);
    assert(sandbox_ctx != NULL);
    
    OutputFormatter* formatter = output_formatter_new();
    assert(formatter != NULL);
    
    ResourceMonitor* monitor = resource_monitor_new();
    assert(monitor != NULL);
    
    // Start monitoring
    resource_monitor_start(monitor);
    
    // Execute a command through the pipeline
    int check_result = sandbox_check_command_allowed(sandbox_ctx, "echo Test Pipeline");
    assert(check_result == SANDBOX_SUCCESS);
    
    CommandResult* result = NULL;
    int exec_result = executor_run_command(exec_ctx, "echo Test Pipeline", &result);
    assert(exec_result == EXECUTOR_SUCCESS);
    assert(result != NULL);
    
    // Format the output
    char* formatted_output = NULL;
    int format_result = output_format_text(formatter, result->stdout_data, 
                                          OUTPUT_FORMAT_CODE, &formatted_output);
    assert(format_result == OUTPUT_SUCCESS);
    assert(formatted_output != NULL);
    assert(strstr(formatted_output, "```") != NULL);
    assert(strstr(formatted_output, "Test Pipeline") != NULL);
    
    // Check resource usage
    ResourceUsage usage;
    resource_monitor_get_usage(monitor, &usage);
    
    // Clean up
    free(formatted_output);
    command_result_free(result);
    resource_monitor_stop(monitor);
    
    resource_monitor_free(monitor);
    output_formatter_free(formatter);
    sandbox_context_free(sandbox_ctx);
    sandbox_config_free(sandbox_config);
    executor_context_free(exec_ctx);
    
    printf("Complete Phase 4 pipeline test passed.\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Phase 4 Integration Tests ===\n");
    
    test_executor_integration();
    test_output_integration();
    test_resource_integration();
    test_complete_phase4_pipeline();
    
    printf("All Phase 4 integration tests passed!\n");
    return 0;
}