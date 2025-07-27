#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file error_throw.c
 * @brief Error throwing function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/error.h"

/**
 * @brief Throw an error
 * @param ctx Error context
 * @param type Error type
 * @param message Error message
 * @param file Source file
 * @param line Line number
 * @return Non-zero on error
 */
int error_throw(ErrorContext* ctx, ErrorType type, const char* message, 
                const char* file, int line) {
    if (!ctx) {
        return -1;
    }
    
    // Clean up any existing error
    free_xmd_error(ctx->current_error);
    
    // Create new error
    XMDError* error = malloc(sizeof(XMDError));
    if (!error) {
        return -1;
    }
    
    error->type = type;
    error->message = message ? strdup(message) : strdup("Unknown error");
    error->file = file ? strdup(file) : strdup("unknown");
    error->line = line;
    
    ctx->current_error = error;
    ctx->error_caught = 0;
    
    return 1; // Error thrown
}