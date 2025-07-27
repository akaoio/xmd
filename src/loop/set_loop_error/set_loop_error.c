/**
 * @file set_loop_error.c
 * @brief Set error message in loop context
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/loop.h"

/**
 * @brief Set error message in loop context
 * @param ctx Loop context
 * @param message Error message
 */
void set_loop_error(LoopContext* ctx, const char* message) {
    if (!ctx || !message) {
        return;
    }
    
    // Free existing error message
    free(ctx->last_error);
    
    // Allocate and copy new error message
    ctx->last_error = malloc(strlen(message) + 1);
    if (ctx->last_error) {
        strcpy(ctx->last_error, message);
    }
}