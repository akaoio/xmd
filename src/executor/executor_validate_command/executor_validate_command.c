/**
 * @file executor_validate_command.c
 * @brief Cross-platform command validation function
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/executor.h"

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
            // Log execution error
            fprintf(stderr, "Dangerous command detected: %s\n", dangerous_commands[i]);
            return EXECUTOR_ERROR;
        }
    }
    
    // Check command length
    if (strlen(command) > 1024) {
        // Log execution error
        fprintf(stderr, "Command too long (max 1024 characters)\n");
        return EXECUTOR_ERROR;
    }
    
    return EXECUTOR_SUCCESS;
}