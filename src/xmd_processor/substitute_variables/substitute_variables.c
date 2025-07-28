/**
 * @file substitute_variables.c
 * @brief Substitute variables in text implementation (now uses AST)
 * @author XMD Team
 * @date 2025-07-28
 */

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/ast_evaluator.h"

/**
 * @brief Substitute {{variable}} patterns in text (now uses AST)
 * @param text Input text containing {{variable}} patterns
 * @param variables Variable store for variable lookups
 * @return New string with variables substituted (caller must free) or NULL on error
 */
char* substitute_variables(const char* text, store* variables) {
    return ast_substitute_variables(text, variables);
}
