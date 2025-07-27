/**
 * @file conditional.h
 * @brief Conditional statement system for XMD control flow
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include <stdbool.h>
#include "variable.h"
#include "store.h"

/* Use the standard store type */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Conditional context for managing if/else/elif logic
 */
struct conditional_context {
    bool last_result;      /**< Result of last condition evaluation */
    char* last_error;      /**< Last error message */
};

/**
 * @brief Conditional context typedef  
 */
typedef struct conditional_context ConditionContext;

/**
 * @brief Result of condition evaluation
 */
typedef enum {
    CONDITION_TRUE = 1,    /**< Condition evaluated to true */
    CONDITION_FALSE = 0,   /**< Condition evaluated to false */
    CONDITION_ERROR = -1   /**< Error during evaluation */
} ConditionResult;

/**
 * @brief Conditional operator types
 */
typedef enum {
    CONDITION_OP_EQUAL,         /**< == operator */
    CONDITION_OP_NOT_EQUAL,     /**< != operator */
    CONDITION_OP_LESS,          /**< < operator */
    CONDITION_OP_LESS_EQUAL,    /**< <= operator */
    CONDITION_OP_GREATER,       /**< > operator */
    CONDITION_OP_GREATER_EQUAL, /**< >= operator */
    CONDITION_OP_LOGICAL_AND,   /**< && operator */
    CONDITION_OP_LOGICAL_OR,    /**< || operator */
    CONDITION_OP_LOGICAL_NOT,   /**< ! operator */
    CONDITION_OP_UNKNOWN        /**< Unknown operator */
} ConditionOperator;

/**
 * @brief Create a new conditional context
 * @return New conditional context or NULL on error
 */
ConditionContext* condition_context_new(void);

/**
 * @brief Free a conditional context
 * @param ctx Conditional context to free
 */
void condition_context_free(ConditionContext* ctx);

/**
 * @brief Evaluate a condition expression
 * @param ctx Conditional context
 * @param expression Expression to evaluate (e.g., "{{var}} > 5")
 * @param store Variable store for lookups
 * @return ConditionResult indicating true/false/error
 */
int condition_evaluate(ConditionContext* ctx, const char* expression, store* st);

/**
 * @brief Process an if/else statement
 * @param ctx Conditional context
 * @param condition Condition to evaluate
 * @param true_content Content to return if condition is true
 * @param false_content Content to return if condition is false (can be NULL)
 * @param store Variable store for lookups
 * @param result Output result string (caller must free)
 * @return 0 on success, non-zero on error
 */
int if_statement_process(ConditionContext* ctx, const char* condition, 
                        const char* true_content, const char* false_content, 
                        store* st, char** result);

/**
 * @brief Process an elif (else if) chain
 * @param ctx Conditional context
 * @param conditions Array of conditions to evaluate
 * @param contents Array of content strings corresponding to conditions
 * @param count Number of conditions/contents
 * @param store Variable store for lookups
 * @param result Output result string (caller must free)
 * @return 0 on success, non-zero on error
 */
int elif_statement_process(ConditionContext* ctx, const char* conditions[], 
                          const char* contents[], int count, 
                          store* st, char** result);

/**
 * @brief Parse logical AND operator
 * @param expr Expression to parse
 * @param operator Output operator type
 * @return Position after operator or NULL if not found
 */
const char* condition_logical_and(const char* expr, int* operator);

/**
 * @brief Parse logical OR operator
 * @param expr Expression to parse
 * @param operator Output operator type
 * @return Position after operator or NULL if not found
 */
const char* condition_logical_or(const char* expr, int* operator);

/**
 * @brief Parse logical NOT operator
 * @param expr Expression to parse
 * @param operator Output operator type
 * @return Position after operator or NULL if not found
 */
const char* condition_logical_not(const char* expr, int* operator);

#ifdef __cplusplus
}
#endif

#endif /* CONDITIONAL_H */
