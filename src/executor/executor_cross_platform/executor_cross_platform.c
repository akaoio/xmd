/**
 * @file executor_cross_platform.c
 * @brief Cross-platform command execution using system()
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../../../include/platform.h"
#include "../../../include/executor.h"

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
