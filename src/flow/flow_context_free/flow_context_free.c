/**
 * @file flow_context_free.c
 * @brief Free flow context
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/flow.h"

/**
 * @brief Free a flow context
 * @param ctx Flow context to free
 */
void flow_context_free(FlowContext* ctx) {
    if (!ctx) {
        return;
    }
    
    if (ctx->return_value) {
        variable_unref(ctx->return_value);
    }
    free(ctx);
}