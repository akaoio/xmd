/**
 * @file executor.c
 * @brief Command execution implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include "../../../include/executor.h"

/**
 * @brief Executor context structure
 */
struct executor_context {
    int default_timeout_ms;     /**< Default timeout in milliseconds */
    size_t max_output_size;     /**< Maximum output size to capture */
    char* last_error;           /**< Last error message */
};

/**
 * @brief Create a new executor context
 * @return New executor context or NULL on error
 */
ExecutorContext* executor_context_new(void) {
    ExecutorContext* ctx = malloc(sizeof(ExecutorContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->default_timeout_ms = 30000; // 30 seconds default
    ctx->max_output_size = 1024 * 1024; // 1MB max output
    ctx->last_error = NULL;
    
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
    
    free(ctx->last_error);
    free(ctx);
}

/**
 * @brief Set error message in context
 * @param ctx Executor context
 * @param message Error message
 */
static void set_executor_error(ExecutorContext* ctx, const char* message) {
    if (!ctx || !message) {
        return;
    }
    
    free(ctx->last_error);
    ctx->last_error = strdup(message);
}

/**
 * @brief Get current time in milliseconds
 * @return Current time in milliseconds
 */
static long get_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

/**
 * @brief Read data from file descriptor with timeout
 * @param fd File descriptor to read from
 * @param buffer Buffer to store data
 * @param max_size Maximum size to read
 * @param timeout_ms Timeout in milliseconds
 * @return Number of bytes read, or -1 on error
 */
static ssize_t read_with_timeout(int fd, char* buffer, size_t max_size, int timeout_ms) {
    fd_set readfds;
    struct timeval timeout;
    size_t total_read = 0;
    
    while (total_read < max_size - 1) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        
        timeout.tv_sec = timeout_ms / 1000;
        timeout.tv_usec = (timeout_ms % 1000) * 1000;
        
        int ready = select(fd + 1, &readfds, NULL, NULL, &timeout);
        if (ready <= 0) {
            break; // Timeout or error
        }
        
        ssize_t bytes_read = read(fd, buffer + total_read, max_size - total_read - 1);
        if (bytes_read <= 0) {
            break; // EOF or error
        }
        
        total_read += bytes_read;
    }
    
    buffer[total_read] = '\0';
    return total_read;
}

/**
 * @brief Parse command into arguments
 * @param command Command string
 * @param args Array to store arguments (must be freed)
 * @return Number of arguments
 */
static int parse_command_args(const char* command, char*** args) {
    if (!command || !args) {
        return -1;
    }
    
    // Simple parsing - split on spaces (doesn't handle quotes properly)
    // This is a security limitation but keeps the implementation simple
    char* command_copy = strdup(command);
    if (!command_copy) {
        return -1;
    }
    
    int argc = 0;
    char* token = strtok(command_copy, " \t\n");
    char** argv = NULL;
    
    while (token) {
        argv = realloc(argv, (argc + 1) * sizeof(char*));
        if (!argv) {
            free(command_copy);
            return -1;
        }
        
        argv[argc] = strdup(token);
        argc++;
        token = strtok(NULL, " \t\n");
    }
    
    // NULL-terminate the array
    argv = realloc(argv, (argc + 1) * sizeof(char*));
    if (argv) {
        argv[argc] = NULL;
    }
    
    free(command_copy);
    *args = argv;
    return argc;
}

/**
 * @brief Free command arguments
 * @param args Arguments array
 * @param argc Number of arguments
 */
static void free_command_args(char** args, int argc) {
    if (!args) {
        return;
    }
    
    for (int i = 0; i < argc; i++) {
        free(args[i]);
    }
    free(args);
}

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

/**
 * @brief Execute a command
 * @param ctx Executor context
 * @param command Command to execute
 * @param result Command result (caller must free)
 * @return ExecutorResult indicating success/failure
 */
int executor_run_command(ExecutorContext* ctx, const char* command, CommandResult** result) {
    if (!ctx) {
        return EXECUTOR_ERROR;
    }
    
    return executor_run_with_timeout(ctx, command, ctx->default_timeout_ms, result);
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