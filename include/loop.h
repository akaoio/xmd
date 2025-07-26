/**
 * @file loop.h
 * @brief Loop system for XMD control flow
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef LOOP_H
#define LOOP_H

#include "variable.h"
#include "store.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Loop context for managing for/while loops
 */
typedef struct loop_context LoopContext;

/**
 * @brief Result of loop operations
 */
typedef enum {
    LOOP_SUCCESS = 0,      /**< Loop completed successfully */
    LOOP_BREAK = 1,        /**< Loop was broken */
    LOOP_CONTINUE = 2,     /**< Loop continue requested */
    LOOP_ERROR = -1        /**< Error during loop processing */
} LoopResult;

/**
 * @brief Create a new loop context
 * @return New loop context or NULL on error
 */
LoopContext* loop_context_new(void);

/**
 * @brief Free a loop context
 * @param ctx Loop context to free
 */
void loop_context_free(LoopContext* ctx);

/**
 * @brief Process a for-in loop
 * @param ctx Loop context
 * @param item_name Name of loop variable
 * @param collection_name Name of collection variable
 * @param template Template content for each iteration
 * @param st Variable store
 * @param result Output result string (caller must free)
 * @return LoopResult indicating success/break/error
 */
int for_loop_process(LoopContext* ctx, const char* item_name, 
                    const char* collection_name, const char* template, 
                    store* st, char** result);

/**
 * @brief Process a while loop
 * @param ctx Loop context
 * @param condition Condition to evaluate each iteration
 * @param template Template content for each iteration
 * @param st Variable store
 * @param result Output result string (caller must free)
 * @return LoopResult indicating success/break/error
 */
int while_loop_process(LoopContext* ctx, const char* condition, 
                      const char* template, store* st, char** result);

/**
 * @brief Request loop break
 * @param ctx Loop context
 * @return LOOP_BREAK
 */
int loop_break(LoopContext* ctx);

/**
 * @brief Request loop continue
 * @param ctx Loop context
 * @return LOOP_CONTINUE
 */
int loop_continue(LoopContext* ctx);

#ifdef __cplusplus
}
#endif

#endif /* LOOP_H */
