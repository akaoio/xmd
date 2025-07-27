/**
 * @file flow_context_new.c
 * @brief Create new flow context
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/flow.h"

/**
 * @brief Create a new flow context
 * @return New flow context or NULL on error
 */
FlowContext* flow_context_new(void) {
    FlowContext* ctx = malloc(sizeof(FlowContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->status = FLOW_CONTINUE;
    ctx->return_value = NULL;
    ctx->in_loop = 0;
    ctx->loop_depth = 0;
    
    return ctx;
}