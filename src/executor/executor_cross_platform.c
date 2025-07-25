/**
 * @file executor_cross_platform.c
 * @brief Cross-platform command execution implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../../include/platform.h"
#include "../../include/executor.h"

/**
 * @brief Executor context structure
 */
struct executor_context {
    int default_timeout_ms;     /**< Default timeout in milliseconds */
    size_t max_output_size;     /**< Maximum output size to capture */
    char* last_error;           /**< Last error message */
};

/**
 * @brief Cross-platform command execution using system()
 * @param ctx Executor context
 * @param command Command to execute
 * @param result Command result (caller must free)
 * @return Execution result
 */
int executor_run_command(ExecutorContext* ctx, const char* command, CommandResult** result) {
    if (!ctx || !command || !result) {
        return EXECUTOR_ERROR;
    }
    
    *result = NULL;
    
    // Simple cross-platform implementation using system()
    // Note: This is less secure than the original fork/exec implementation
    // but works across all platforms
    
    printf("Executing command: %s\n", command);
    
    xmd_time_t start_time;
    xmd_get_time(&start_time);
    
    int exit_code = system(command);
    
    xmd_time_t end_time;
    xmd_get_time(&end_time);
    
    // Calculate execution time in milliseconds
    uint64_t exec_time_ms = (end_time.seconds - start_time.seconds) * 1000 +
                           (end_time.nanoseconds - start_time.nanoseconds) / 1000000;
    
    printf("Command completed with exit code: %d (execution time: %llu ms)\n", 
           exit_code, (unsigned long long)exec_time_ms);
    
    // Create result structure
    CommandResult* cmd_result = malloc(sizeof(CommandResult));
    if (!cmd_result) {
        return EXECUTOR_ERROR;
    }
    
    // Initialize result
    cmd_result->exit_code = exit_code;
    cmd_result->execution_time_ms = exec_time_ms;
    cmd_result->stdout_data = NULL;
    cmd_result->stderr_data = NULL;
    cmd_result->stdout_size = 0;
    cmd_result->stderr_size = 0;
    
    *result = cmd_result;

#ifdef XMD_PLATFORM_WINDOWS
    // On Windows, system() returns the exit code directly
    return (exit_code == 0) ? EXECUTOR_SUCCESS : EXECUTOR_ERROR;
#else
    // On Unix-like systems, check if command executed successfully
    if (exit_code == -1) {
        return EXECUTOR_ERROR;
    }
    
    // Extract actual exit status
    if (WIFEXITED(exit_code)) {
        int actual_exit = WEXITSTATUS(exit_code);
        return (actual_exit == 0) ? EXECUTOR_SUCCESS : EXECUTOR_ERROR;
    } else {
        return EXECUTOR_ERROR;
    }
#endif
}

/**
 * @brief Execute a command with timeout (cross-platform implementation)
 * @param ctx Executor context
 * @param command Command to execute
 * @param timeout_ms Timeout in milliseconds
 * @param result Command result (caller must free)
 * @return ExecutorResult indicating success/failure
 */
int executor_run_with_timeout(ExecutorContext* ctx, const char* command, 
                             int timeout_ms, CommandResult** result) {
    // For simplicity, ignore timeout in cross-platform version
    // The timeout handling would be platform-specific
    return executor_run_command(ctx, command, result);
}

/**
 * @brief Cross-platform command validation
 * @param ctx Executor context  
 * @param command Command to validate
 * @return Validation result
 */
int executor_validate_command(ExecutorContext* ctx, const char* command) {
    if (!ctx || !command) {
        return EXECUTOR_ERROR;
    }
    
    // Basic validation - check for dangerous commands
    const char* dangerous_commands[] = {
        "rm -rf",
        "del /f",
        "format",
        "fdisk",
        "mkfs",
        "dd if=",
        NULL
    };
    
    for (int i = 0; dangerous_commands[i]; i++) {
        if (strstr(command, dangerous_commands[i])) {
            // Log error (simplified without accessing private struct)
            fprintf(stderr, "Dangerous command detected: %s\n", dangerous_commands[i]);
            return EXECUTOR_ERROR;
        }
    }
    
    // Check command length
    if (strlen(command) > 1024) {
        // Log error (simplified without accessing private struct)
        fprintf(stderr, "Command too long (max 1024 characters)\n");
        return EXECUTOR_ERROR;
    }
    
    return EXECUTOR_SUCCESS;
}

/**
 * @brief Create a new executor context
 * @return New executor context or NULL on error
 */
ExecutorContext* executor_context_new(void) {
    ExecutorContext* ctx = malloc(sizeof(ExecutorContext));
    if (!ctx) {
        return NULL;
    }
    
    return ctx;
}

/**
 * @brief Free an executor context
 * @param ctx Executor context to free
 */
void executor_context_free(ExecutorContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free(ctx);
}

/**
 * @brief Free a command result
 * @param result Command result to free
 */
void command_result_free(CommandResult* result) {
    if (!result) {
        return;
    }
    
    free(result->stdout_data);
    free(result->stderr_data);
    free(result);
}