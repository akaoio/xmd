/**
 * @file process_cmd_function.c
 * @brief Process cmd function implementation
 * @author XMD Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Process cmd function call (e.g., cmd("ls -la"))
 * @param function_call Complete function call string (e.g., "cmd(\"tree /path\")")
 * @param ctx Processor context
 * @param output Buffer to store output
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_cmd_function(const char* function_call, processor_context* ctx, char* output, size_t output_size) {
    // Check if we should execute this block
    if (!should_execute_block(ctx)) {
        output[0] = '\0';
        return 0;
    }
    
    // Parse cmd("command") or cmd('command')
    const char* start = strchr(function_call, '(');
    const char* end = strrchr(function_call, ')');
    
    if (!start || !end || start >= end) {
        snprintf(output, output_size, "[Error: Invalid cmd() syntax]");
        return -1;
    }
    
    // Extract command string (inside quotes)
    const char* cmd_start = start + 1;
    while (*cmd_start && (*cmd_start == ' ' || *cmd_start == '\t')) cmd_start++;
    
    if (*cmd_start != '"' && *cmd_start != '\'') {
        snprintf(output, output_size, "[Error: cmd() requires quoted string argument]");
        return -1;
    }
    
    char quote_char = *cmd_start;
    cmd_start++; // Skip opening quote
    
    // Find closing quote
    const char* cmd_end = cmd_start;
    while (cmd_end < end && *cmd_end != quote_char) {
        cmd_end++;
    }
    
    if (cmd_end >= end || *cmd_end != quote_char) {
        snprintf(output, output_size, "[Error: cmd() missing closing quote]");
        return -1;
    }
    
    // Extract command
    size_t cmd_len = cmd_end - cmd_start;
    char* command = malloc(cmd_len + 1);
    strncpy(command, cmd_start, cmd_len);
    command[cmd_len] = '\0';
    
    // Execute command using dynamic function
    char* command_output = execute_command_dynamic(command, NULL);
    if (command_output) {
        snprintf(output, output_size, "%s", command_output);
        free(command_output);
    } else {
        snprintf(output, output_size, "[Error: Failed to execute command: %s]", command);
        free(command);
        return -1;
    }
    
    free(command);
    return 0;
}