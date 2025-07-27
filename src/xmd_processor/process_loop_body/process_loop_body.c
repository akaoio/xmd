/**
 * @file process_loop_body.c
 * @brief Loop body processing function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/loop.h"

/**
 * @brief Process loop body content
 * @param content Loop body content
 * @param ctx Processor context
 * @param loop_ctx Loop context
 * @return 0 on success, -1 on error
 */
int process_loop_body(const char* content, processor_context* ctx, LoopContext* loop_ctx) {
    if (!content || !ctx || !loop_ctx) {
        return -1;
    }
    
    // Check if break or continue was requested
    if (loop_ctx->break_requested) {
        return LOOP_BREAK;
    }
    if (loop_ctx->continue_requested) {
        return LOOP_CONTINUE;
    }
    
    // Process the loop body content - use basic text processing for now
    char* processed_content = substitute_variables(content, ctx->variables);
    
    if (!processed_content) {
        set_loop_error(loop_ctx, "Failed to process loop body");
        return LOOP_ERROR;
    }
    
    // For now, just set the processed content as output
    // In a full implementation, this would append to a result buffer
    free(processed_content);
    
    return LOOP_SUCCESS;
}