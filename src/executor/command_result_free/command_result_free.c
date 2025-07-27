/**
 * @file command_result_free.c
 * @brief Command result cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/executor.h"

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