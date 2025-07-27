/**
 * @file executor.h
 * @brief Command execution system for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <sys/types.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Command execution result
 */
typedef struct {
    int exit_code;              /**< Process exit code */
    char* stdout_data;          /**< Captured stdout */
    char* stderr_data;          /**< Captured stderr */
    size_t stdout_size;         /**< Size of stdout data */
    size_t stderr_size;         /**< Size of stderr data */
    long execution_time_ms;     /**< Execution time in milliseconds */
} CommandResult;

/**
 * @brief Execution result codes
 */
typedef enum {
    EXECUTOR_SUCCESS = 0,           /**< Command executed successfully */
    EXECUTOR_ERROR = -1,            /**< General execution error */
    EXECUTOR_TIMEOUT = -2,          /**< Command timed out */
    EXECUTOR_PERMISSION_DENIED = -3 /**< Permission denied */
} ExecutorResult;

/**
 * @brief Command execution context structure
 */
struct executor_context {
    char* last_error;           /**< Last error message */
    int timeout_ms;             /**< Default timeout in milliseconds */
    int default_timeout_ms;     /**< Default timeout for new commands */
    int enable_capture;         /**< Whether to capture output */
    size_t max_output_size;     /**< Maximum output size to capture */
};

/**
 * @brief Command execution context typedef
 */
typedef struct executor_context ExecutorContext;

/**
 * @brief Create a new executor context
 * @return New executor context or NULL on error
 */
ExecutorContext* executor_context_new(void);

/**
 * @brief Free an executor context
 * @param ctx Executor context to free
 */
void executor_context_free(ExecutorContext* ctx);

/**
 * @brief Execute a command
 * @param ctx Executor context
 * @param command Command to execute
 * @param result Command result (caller must free)
 * @return ExecutorResult indicating success/failure
 */
int executor_run_command(ExecutorContext* ctx, const char* command, CommandResult** result);

/**
 * @brief Execute a command with timeout
 * @param ctx Executor context
 * @param command Command to execute
 * @param timeout_ms Timeout in milliseconds
 * @param result Command result (caller must free)
 * @return ExecutorResult indicating success/failure
 */
int executor_run_with_timeout(ExecutorContext* ctx, const char* command, 
                             int timeout_ms, CommandResult** result);

/**
 * @brief Free a command result
 * @param result Command result to free
 */
void command_result_free(CommandResult* result);

#ifdef __cplusplus
}
#endif

#endif /* EXECUTOR_H */
