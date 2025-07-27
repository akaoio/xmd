/**
 * @file flow_break_statement.c
 * @brief Handle break statements in flow control
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/flow.h"

/**
 * @brief Process a break statement
 * @param ctx Flow context
 * @return FLOW_BREAK
 */
int flow_break_statement(FlowContext* ctx) {
    if (!ctx) {
        return FLOW_ERROR;
    }
    
    // Don't override return status - return takes precedence
    if (ctx->status != FLOW_RETURN) {
        ctx->status = FLOW_BREAK;
    }
    return FLOW_BREAK;
}