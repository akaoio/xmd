/**
 * @file flow_internal.h
 * @brief Internal definitions for flow control system
 * @author XMD Development Team
 * @date 2025-07-31
 */

#ifndef FLOW_INTERNAL_H
#define FLOW_INTERNAL_H

#include "flow.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Flow operation results (internal)
 */
typedef enum {
    FLOW_SUCCESS = 0    /**< Operation successful */
} FlowInternalResult;

/**
 * @brief Extended flow context for internal use
 */
struct flow_context_internal {
    bool break_requested;       /**< Break requested flag */
    bool continue_requested;    /**< Continue requested flag */
    bool return_requested;      /**< Return requested flag */
    variable* return_value;     /**< Return value */
    bool in_loop;              /**< Currently in loop */
    bool in_function;          /**< Currently in function */
    int loop_depth;            /**< Current loop nesting depth */
    int function_depth;        /**< Current function depth */
};

#ifdef __cplusplus
}
#endif

#endif /* FLOW_INTERNAL_H */
