/**
 * @file ast_parse_ternary.c
 * @brief Implementation of ast_parse_ternary function
 * 
 * This file contains ONLY the ast_parse_ternary function.
 * One function per file - Genesis principle compliance.
 * Parses ternary operator expressions (condition ? true_expr : false_expr)
 */

#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Parse ternary operator expression
 * @param pos Pointer to current position in input (will be advanced)
 * @return Ternary AST node or NULL if not a ternary expression
 */
ast_node* ast_parse_ternary(const char** pos) {
    XMD_VALIDATE_PTR_RETURN(pos, NULL);
    XMD_PARSE_VALIDATE_POS(pos, NULL);
    
    const char* start = *pos;
    source_location loc = {1, *pos - start, NULL};
    
    // First, parse the condition (this could be any expression)
    ast_node* condition = ast_parse_comparison_expression(*pos);
    XMD_VALIDATE_PTR_RETURN(condition, NULL);
    
    // Advance past the condition
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Look for '?' operator
    if (**pos != '?') {
        // Not a ternary, return the condition as a regular expression
        return condition;
    }
    
    // Skip '?' and whitespace
    (*pos)++;
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse true expression
    ast_node* true_expr = ast_parse_expression(pos);
    if (!true_expr) {
        ast_free(condition);
        XMD_ERROR_RETURN(NULL, "Expected expression after '?' in ternary operator");
    }
    
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Look for ':' operator
    if (**pos != ':') {
        ast_free(condition);
        ast_free(true_expr);
        XMD_ERROR_RETURN(NULL, "Expected ':' in ternary operator");
    }
    
    // Skip ':' and whitespace
    (*pos)++;
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse false expression
    ast_node* false_expr = ast_parse_expression(pos);
    if (!false_expr) {
        ast_free(condition);
        ast_free(true_expr);
        XMD_ERROR_RETURN(NULL, "Expected expression after ':' in ternary operator");
    }
    
    // Create ternary node
    ast_node* ternary = ast_create_ternary(condition, true_expr, false_expr, loc);
    if (!ternary) {
        ast_free(condition);
        ast_free(true_expr);
        ast_free(false_expr);
        return NULL;
    }
    
    return ternary;
}