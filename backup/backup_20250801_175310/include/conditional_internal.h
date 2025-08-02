/**
 * @file conditional_internal.h
 * @brief Internal definitions for conditional system
 * @author XMD Development Team
 * @date 2025-07-31
 */

#ifndef CONDITIONAL_INTERNAL_H
#define CONDITIONAL_INTERNAL_H

#include "conditional.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Maximum nested conditions allowed
 */
#define MAX_NESTED_CONDITIONS 16

/**
 * @brief Result of if statement processing
 */
typedef enum {
    IF_TRUE = 1,      /**< Condition is true */
    IF_FALSE = 0,     /**< Condition is false */
    IF_ERROR = -1,    /**< Error during evaluation */
    IF_SKIP = -2      /**< Skip this block */
} IfResult;

/**
 * @brief Extended conditional context for internal use
 */
struct conditional_context_internal {
    bool last_result;                           /**< Result of last condition */
    char* last_error;                           /**< Last error message */
    int current_level;                          /**< Current nesting level */
    bool in_if_block;                          /**< Currently in if block */
    bool condition_met;                        /**< Any condition met */
    bool if_stack[MAX_NESTED_CONDITIONS];      /**< Stack of if results */
};

#ifdef __cplusplus
}
#endif

#endif /* CONDITIONAL_INTERNAL_H */
