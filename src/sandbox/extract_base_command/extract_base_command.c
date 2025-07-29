/**
 * @file extract_base_command.c
 * @brief Extract base command from command string
 * @author XMD Team
 */

#include "../../../include/sandbox.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Extract base command from command string
 * @param command Full command string
 * @return Base command or NULL on error (caller must free)
 */
char* extract_base_command(const char* command) {
    if (!command) return NULL;
    
    // Skip leading whitespace
    while (*command && (*command == ' ' || *command == '\t')) {
        command++;
    }
    
    if (!*command) return NULL;
    
    // Find end of base command (first space, tab, or null)
    const char* end = command;
    while (*end && *end != ' ' && *end != '\t') {
        end++;
    }
    
    // Extract base command
    size_t len = end - command;
    char* result = malloc(len + 1);
    if (!result) return NULL;
    
    strncpy(result, command, len);
    result[len] = '\0';
    
    return result;
}