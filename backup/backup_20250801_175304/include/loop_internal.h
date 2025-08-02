/**
 * @file loop_internal.h
 * @brief Internal loop implementation structures
 * @author XMD Development Team
 */

#ifndef LOOP_INTERNAL_H
#define LOOP_INTERNAL_H

#include "loop.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Internal loop state structure
 */
typedef struct {
    int break_requested;      /**< Break flag */
    int continue_requested;   /**< Continue flag */
    size_t max_iterations;    /**< Maximum allowed iterations */
    char* last_error;         /**< Last error message */
} LoopState;

/**
 * @brief Loop condition evaluation function type
 */
typedef int (*LoopConditionFunc)(void* context);

/**
 * @brief Loop body execution function type
 */
typedef int (*LoopBodyFunc)(void* context, size_t iteration);

#ifdef __cplusplus
}
#endif

#endif /* LOOP_INTERNAL_H */
