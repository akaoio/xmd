/**
 * @file command_result_free.c
 * @brief Free a command result
 * @author XMD Team
 */

#include "../../../../include/executor_internal.h"

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