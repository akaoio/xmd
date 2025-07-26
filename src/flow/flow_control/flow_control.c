/**
 * @file flow_control.c
 * @brief Flow control implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/flow.h"

/**
 * @brief Flow control context structure
 */
struct flow_context {
    FlowResult status;        /**< Current flow status */
    variable* return_value;   /**< Return value if any */
    int depth;                /**< Nesting depth */
};

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
    ctx->depth = 0;
    
    return ctx;
}

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

/**
 * @brief Execute break statement
 * @param ctx Flow context
 * @return FLOW_BREAK
 */
int flow_break_statement(FlowContext* ctx) {
    if (!ctx) {
        return FLOW_ERROR;
    }
    
    // Break only if not already in return state
    if (ctx->status != FLOW_RETURN) {
        ctx->status = FLOW_BREAK;
    }
    
    return FLOW_BREAK;
}

/**
 * @brief Execute continue statement
 * @param ctx Flow context
 * @return FLOW_CONTINUE
 */
int flow_continue_statement(FlowContext* ctx) {
    if (!ctx) {
        return FLOW_ERROR;
    }
    
    // Continue only if not in return or break state
    if (ctx->status == FLOW_CONTINUE) {
        // Status remains FLOW_CONTINUE
    }
    
    return FLOW_CONTINUE;
}

/**
 * @brief Execute return statement
 * @param ctx Flow context
 * @param return_value Value to return (can be NULL)
 * @return FLOW_RETURN
 */
int flow_return_statement(FlowContext* ctx, variable* return_value) {
    if (!ctx) {
        return FLOW_ERROR;
    }
    
    // Clean up any existing return value
    if (ctx->return_value) {
        variable_unref(ctx->return_value);
        ctx->return_value = NULL;
    }
    
    // Set new return value if provided
    if (return_value) {
        ctx->return_value = variable_ref(return_value);
    } else {
        ctx->return_value = variable_create_null();
    }
    
    ctx->status = FLOW_RETURN;
    return FLOW_RETURN;
}

/**
 * @brief Check current flow status
 * @param ctx Flow context
 * @return Current FlowResult status
 */
int flow_check_status(FlowContext* ctx) {
    if (!ctx) {
        return FLOW_ERROR;
    }
    
    return ctx->status;
}

/**
 * @brief Get return value from flow context
 * @param ctx Flow context
 * @return Return value or NULL if none set
 */
variable* flow_get_return_value(FlowContext* ctx) {
    if (!ctx) {
        return NULL;
    }
    
    return ctx->return_value;
}
