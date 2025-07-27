/**
 * @file flow_continue_statement.c
 * @brief Handle continue statements in flow control
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/flow.h"

/**
 * @brief Process a continue statement
 * @param ctx Flow context
 * @return FLOW_CONTINUE
 */
int flow_continue_statement(FlowContext* ctx) {
    if (!ctx) {
        return FLOW_ERROR;
    }
    
    ctx->status = FLOW_CONTINUE;
    return FLOW_CONTINUE;
}