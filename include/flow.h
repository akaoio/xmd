/**
 * @file flow.h
 * @brief Flow control system for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef FLOW_H
#define FLOW_H

#include "variable.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Flow control context
 */
typedef struct flow_context FlowContext;

/**
 * @brief Flow control result types
 */
typedef enum {
    FLOW_CONTINUE = 0,     /**< Continue normal execution */
    FLOW_BREAK = 1,        /**< Break from loop */
    FLOW_RETURN = 2,       /**< Return from function/block */
    FLOW_ERROR = -1        /**< Error in flow control */
} FlowResult;

/**
 * @brief Create a new flow context
 * @return New flow context or NULL on error
 */
FlowContext* flow_context_new(void);

/**
 * @brief Free a flow context
 * @param ctx Flow context to free
 */
void flow_context_free(FlowContext* ctx);

/**
 * @brief Execute break statement
 * @param ctx Flow context
 * @return FLOW_BREAK
 */
int flow_break_statement(FlowContext* ctx);

/**
 * @brief Execute continue statement
 * @param ctx Flow context
 * @return FLOW_CONTINUE
 */
int flow_continue_statement(FlowContext* ctx);

/**
 * @brief Execute return statement
 * @param ctx Flow context
 * @param return_value Value to return (can be NULL)
 * @return FLOW_RETURN
 */
int flow_return_statement(FlowContext* ctx, variable* return_value);

/**
 * @brief Check current flow status
 * @param ctx Flow context
 * @return Current FlowResult status
 */
int flow_check_status(FlowContext* ctx);

/**
 * @brief Get return value from flow context
 * @param ctx Flow context
 * @return Return value or NULL if none set
 */
variable* flow_get_return_value(FlowContext* ctx);

#ifdef __cplusplus
}
#endif

#endif /* FLOW_H */