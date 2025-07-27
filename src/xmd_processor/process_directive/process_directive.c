/**
 * @file process_directive.c
 * @brief Process single XMD directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Process a single XMD directive
 * @param directive The directive string to process
 * @param ctx Processor context
 * @param output Buffer to store output
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_directive(const char* directive, processor_context* ctx, char* output, size_t output_size) {
    // Rule 13: Error handling - validate inputs
    if (!directive || !ctx || !output || output_size == 0) {
        if (output && output_size > 0) {
            output[0] = '\0';
        }
        return -1;
    }
    
    char* dir_copy = strdup(directive);
    if (!dir_copy) {
        output[0] = '\0';
        return -1;
    }
    
    char* trimmed = trim_whitespace(dir_copy);
    
    // Skip "xmd:" prefix if present
    if (strncmp(trimmed, "xmd:", 4) == 0) {
        trimmed += 4;
        trimmed = trim_whitespace(trimmed);
    }
    
    int result = 0;
    
    // Extract command and args
    char* space = strchr(trimmed, ' ');
    char command[64];
    char* args = "";
    
    if (space) {
        size_t cmd_len = space - trimmed;
        if (cmd_len >= sizeof(command)) cmd_len = sizeof(command) - 1;
        strncpy(command, trimmed, cmd_len);
        command[cmd_len] = '\0';
        args = trim_whitespace(space + 1);
    } else {
        strncpy(command, trimmed, sizeof(command) - 1);
        command[sizeof(command) - 1] = '\0';
    }
    
    // Process based on command
    if (strcmp(command, "set") == 0) {
        result = process_set(args, ctx, output, output_size);
    } else if (strcmp(command, "if") == 0) {
        result = process_if(args, ctx, output, output_size);
    } else if (strcmp(command, "elif") == 0) {
        result = process_elif(args, ctx, output, output_size);
    } else if (strcmp(command, "else") == 0) {
        result = process_else(ctx, output, output_size);
    } else if (strcmp(command, "endif") == 0) {
        result = process_endif(ctx, output, output_size);
    } else if (strcmp(command, "exec") == 0) {
        result = process_exec(args, ctx, output, output_size);
    } else if (strcmp(command, "import") == 0) {
        result = process_import(args, ctx, output, output_size);
    } else if (strcmp(command, "for") == 0) {
        result = process_for(args, ctx, output, output_size);
    } else if (strcmp(command, "endfor") == 0) {
        output[0] = '\0';
        result = 0;
    } else if (strncmp(trimmed, "print(", 6) == 0) {
        // Handle print() function calls
        result = process_print_function(trimmed, ctx, output, output_size);
    } else if (strncmp(trimmed, "cmd(", 4) == 0) {
        // Handle cmd() function calls
        result = process_cmd_function(trimmed, ctx, output, output_size);
    } else {
        snprintf(output, output_size, "[Unknown command: %s]", command);
        result = -1;
    }
    
    free(dir_copy);
    return result;
}
