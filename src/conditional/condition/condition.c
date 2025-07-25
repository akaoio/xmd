/**
 * @file condition_simple.c
 * @brief Simplified condition evaluation implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/conditional.h"

/**
 * @brief Conditional context structure
 */
struct conditional_context {
    int depth;              /**< Nesting depth for nested conditionals */
    char* last_error;       /**< Last error message */
};

/**
 * @brief Create a new conditional context
 * @return New conditional context or NULL on error
 */
ConditionContext* condition_context_new(void) {
    ConditionContext* ctx = malloc(sizeof(ConditionContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->depth = 0;
    ctx->last_error = NULL;
    
    return ctx;
}

/**
 * @brief Free a conditional context
 * @param ctx Conditional context to free
 */
void condition_context_free(ConditionContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free(ctx->last_error);
    free(ctx);
}

/**
 * @brief Extract variable name from {{variable}} syntax
 * @param expr Expression to parse
 * @return Variable name or NULL if not found (caller must free)
 */
static char* extract_variable_name(const char* expr) {
    if (!expr) {
        return NULL;
    }
    
    // Find {{
    const char* start = strstr(expr, "{{");
    if (!start) {
        return NULL;
    }
    start += 2;
    
    // Find }}
    const char* end = strstr(start, "}}");
    if (!end) {
        return NULL;
    }
    
    // Extract variable name
    size_t len = end - start;
    char* var_name = malloc(len + 1);
    if (!var_name) {
        return NULL;
    }
    
    strncpy(var_name, start, len);
    var_name[len] = '\0';
    
    // Trim whitespace
    char* trimmed = var_name;
    while (isspace(*trimmed)) trimmed++;
    
    size_t trimmed_len = strlen(trimmed);
    while (trimmed_len > 0 && isspace(trimmed[trimmed_len - 1])) {
        trimmed[--trimmed_len] = '\0';
    }
    
    char* result = strdup(trimmed);
    free(var_name);
    return result;
}

/**
 * @brief Check if variable is truthy
 * @param var Variable to check
 * @return 1 if truthy, 0 if falsy
 */
static int variable_is_truthy(variable* var) {
    if (!var) {
        return 0;
    }
    
    switch (variable_get_type(var)) {
        case VAR_NULL:
            return 0;
        case VAR_BOOLEAN:
            return variable_get_boolean(var) ? 1 : 0;
        case VAR_NUMBER:
            return variable_get_number(var) != 0.0 ? 1 : 0;
        case VAR_STRING: {
            const char* str = variable_get_string(var);
            return (str && strlen(str) > 0) ? 1 : 0;
        }
        case VAR_ARRAY:
            return variable_array_length(var) > 0 ? 1 : 0;
        case VAR_OBJECT:
            return 1; // Objects are always truthy if they exist
        default:
            return 0;
    }
}

/**
 * @brief Evaluate a simple condition expression
 * @param ctx Conditional context
 * @param expression Expression to evaluate
 * @param st Variable store for lookups
 * @return ConditionResult indicating true/false/error
 */
int condition_evaluate(ConditionContext* ctx, const char* expression, store* st) {
    if (!ctx || !expression || !st) {
        return CONDITION_ERROR;
    }
    
    // Trim whitespace
    while (isspace(*expression)) expression++;
    size_t len = strlen(expression);
    while (len > 0 && isspace(expression[len - 1])) len--;
    
    char* expr = strndup(expression, len);
    if (!expr) {
        return CONDITION_ERROR;
    }
    
    // Handle NOT operator
    if (expr[0] == '!') {
        int result = condition_evaluate(ctx, expr + 1, st);
        free(expr);
        if (result == CONDITION_ERROR) {
            return CONDITION_ERROR;
        }
        return result == CONDITION_TRUE ? CONDITION_FALSE : CONDITION_TRUE;
    }
    
    // Handle logical operators
    char* and_pos = strstr(expr, " && ");
    char* or_pos = strstr(expr, " || ");
    
    if (and_pos) {
        *and_pos = '\0';
        int left_result = condition_evaluate(ctx, expr, st);
        if (left_result == CONDITION_ERROR) {
            free(expr);
            return CONDITION_ERROR;
        }
        
        if (left_result == CONDITION_FALSE) {
            free(expr);
            return CONDITION_FALSE; // Short-circuit AND
        }
        
        int right_result = condition_evaluate(ctx, and_pos + 4, st);
        free(expr);
        return right_result;
    }
    
    if (or_pos) {
        *or_pos = '\0';
        int left_result = condition_evaluate(ctx, expr, st);
        if (left_result == CONDITION_ERROR) {
            free(expr);
            return CONDITION_ERROR;
        }
        
        if (left_result == CONDITION_TRUE) {
            free(expr);
            return CONDITION_TRUE; // Short-circuit OR
        }
        
        int right_result = condition_evaluate(ctx, or_pos + 4, st);
        free(expr);
        return right_result;
    }
    
    // Simple variable evaluation - extract variable name and check truthiness
    char* var_name = extract_variable_name(expr);
    if (!var_name) {
        // Not a variable reference, treat as literal
        if (strcmp(expr, "true") == 0 || strcmp(expr, "1") == 0) {
            free(expr);
            return CONDITION_TRUE;
        } else if (strcmp(expr, "false") == 0 || strcmp(expr, "0") == 0 || strlen(expr) == 0) {
            free(expr);
            return CONDITION_FALSE;
        } else {
            free(expr);
            return CONDITION_TRUE; // Non-empty string is truthy
        }
    }
    
    // Look up variable in store
    variable* var = store_get(st, var_name);
    int result = variable_is_truthy(var) ? CONDITION_TRUE : CONDITION_FALSE;
    
    free(expr);
    free(var_name);
    
    return result;
}