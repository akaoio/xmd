/**
 * @file flow_return_statement.c
 * @brief Handle return statements in flow control
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/flow.h"
#include "../../../include/variable.h"

/**
 * @brief Process a return statement
 * @param ctx Flow context
 * @param return_value Value to return (can be NULL)
 * @return FLOW_RETURN
 */
int flow_return_statement(FlowContext* ctx, variable* return_value) {
    if (!ctx) {
        return FLOW_ERROR;
    }
    
    // Clear any existing return value
    if (ctx->return_value) {
        variable_unref(ctx->return_value);
    }
    
    // Set new return value
    if (return_value) {
        ctx->return_value = return_value;
        variable_ref(return_value);
    } else {
        ctx->return_value = variable_create_null();
    }
    
    ctx->status = FLOW_RETURN;
    return FLOW_RETURN;
}