#define _GNU_SOURCE  // For system functions - must be before includes

/**
 * @file executor_run_with_timeout.c
 * @brief Execute a command with timeout
 * @author XMD Team
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include "../../../../include/executor_internal.h"

/**
 * @brief Execute a command with timeout
 * @param ctx Executor context
 * @param command Command to execute
 * @param timeout_ms Timeout in milliseconds
 * @param result Command result (caller must free)
 * @return ExecutorResult indicating success/failure
 */
int executor_run_with_timeout(ExecutorContext* ctx, const char* command, 
                             int timeout_ms, CommandResult** result) {
    if (!ctx || !command || !result) {
        return EXECUTOR_ERROR;
    }
    
    *result = NULL;
    
    // Validate command
    if (strlen(command) == 0) {
        set_executor_error(ctx, "Empty command");
        return EXECUTOR_ERROR;
    }
    
    // Parse command arguments
    char** args;
    int argc = parse_command_args(command, &args);
    if (argc <= 0) {
        set_executor_error(ctx, "Failed to parse command");
        return EXECUTOR_ERROR;
    }
    
    // Create pipes for stdout and stderr
    int stdout_pipe[2], stderr_pipe[2];
    if (pipe(stdout_pipe) == -1 || pipe(stderr_pipe) == -1) {
        set_executor_error(ctx, "Failed to create pipes");
        free_command_args(args, argc);
        return EXECUTOR_ERROR;
    }
    
    // Record start time
    long start_time = get_time_ms();
    
    // Fork child process
    pid_t pid = fork();
    if (pid == -1) {
        set_executor_error(ctx, "Failed to fork process");
        close(stdout_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[0]);
        close(stderr_pipe[1]);
        free_command_args(args, argc);
        return EXECUTOR_ERROR;
    }
    
    if (pid == 0) {
        // Child process
        close(stdout_pipe[0]);
        close(stderr_pipe[0]);
        
        // Redirect stdout and stderr
        dup2(stdout_pipe[1], STDOUT_FILENO);
        dup2(stderr_pipe[1], STDERR_FILENO);
        
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);
        
        // Execute command
        execvp(args[0], args);
        
        // If we get here, exec failed
        perror("execvp failed");
        exit(127);
    }
    
    // Parent process
    close(stdout_pipe[1]);
    close(stderr_pipe[1]);
    
    // Allocate result structure
    CommandResult* cmd_result = malloc(sizeof(CommandResult));
    if (!cmd_result) {
        close(stdout_pipe[0]);
        close(stderr_pipe[0]);
        kill(pid, SIGTERM);
        waitpid(pid, NULL, 0);
        free_command_args(args, argc);
        return EXECUTOR_ERROR;
    }
    
    // Initialize result
    cmd_result->stdout_data = malloc(ctx->max_output_size);
    cmd_result->stderr_data = malloc(ctx->max_output_size);
    if (!cmd_result->stdout_data || !cmd_result->stderr_data) {
        command_result_free(cmd_result);
        close(stdout_pipe[0]);
        close(stderr_pipe[0]);
        kill(pid, SIGTERM);
        waitpid(pid, NULL, 0);
        free_command_args(args, argc);
        return EXECUTOR_ERROR;
    }
    
    // Read stdout and stderr with timeout
    cmd_result->stdout_size = read_with_timeout(stdout_pipe[0], cmd_result->stdout_data, 
                                               ctx->max_output_size, timeout_ms);
    cmd_result->stderr_size = read_with_timeout(stderr_pipe[0], cmd_result->stderr_data, 
                                               ctx->max_output_size, timeout_ms);
    
    close(stdout_pipe[0]);
    close(stderr_pipe[0]);
    
    // Wait for child process with timeout
    int status;
    long elapsed_time;
    pid_t wait_result = 0;
    
    do {
        wait_result = waitpid(pid, &status, WNOHANG);
        elapsed_time = get_time_ms() - start_time;
        
        if (wait_result == 0 && elapsed_time >= timeout_ms) {
            // Timeout reached, kill the process
            kill(pid, SIGTERM);
            usleep(100000); // Wait 100ms for graceful termination
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
            
            command_result_free(cmd_result);
            free_command_args(args, argc);
            set_executor_error(ctx, "Command timed out");
            return EXECUTOR_TIMEOUT;
        }
        
        if (wait_result == 0) {
            usleep(10000); // Sleep 10ms before checking again
        }
    } while (wait_result == 0);
    
    elapsed_time = get_time_ms() - start_time;
    
    if (wait_result == -1) {
        command_result_free(cmd_result);
        free_command_args(args, argc);
        set_executor_error(ctx, "Failed to wait for child process");
        return EXECUTOR_ERROR;
    }
    
    // Set exit code and execution time
    cmd_result->exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    cmd_result->execution_time_ms = elapsed_time;
    
    free_command_args(args, argc);
    *result = cmd_result;
    return EXECUTOR_SUCCESS;
}