/**
 * @file executor_run_command.c
 * @brief Execute a command
 * @author XMD Team
 */

#include "../../../../include/executor_internal.h"

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