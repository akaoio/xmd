/**
 * @file ast_parse_elif_simple.c
 * @brief Implementation of ast_parse_elif_simple function
 * 
 * This file contains ONLY the ast_parse_elif_simple function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse elif statement: elif condition
 * @param pos Pointer to current position
 * @return Conditional AST node or NULL
 */
ast_node* ast_parse_elif(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    // Skip "elif "
    start += 5;
    while (*start && isspace(*start)) start++;
    // Parse condition until end of line
    const char* condition_start = start;
    while (*start && *start != '\n') {
        start++;
    }
    size_t condition_len = start - condition_start;
    if (condition_len == 0) {
        return NULL;
    }
    
    // Create condition expression from string
    char* condition_str;
    XMD_MALLOC_SAFE(condition_str, char[condition_len + 1], NULL, "ast_parse_elif: Failed to allocate condition string");
    strncpy(condition_str, condition_start, condition_len);
    condition_str[condition_len] = '\0';
    // Trim trailing whitespace
    char* end = condition_str + condition_len - 1;
    while (end > condition_str && isspace(*end)) {
        *end = '\0';
        end--;
    }
    
    // Parse the condition as a comparison or simple expression
    ast_node* condition_node = NULL;
    if (strstr(condition_str, " < ") || strstr(condition_str, " > ") || 
        strstr(condition_str, " <= ") || strstr(condition_str, " >= ") ||
        strstr(condition_str, " = ") || strstr(condition_str, " != ")) {
        condition_node = ast_parse_comparison_expression(condition_str);
    } else {
        // Simple expression or variable
        const char* expr_pos = condition_str;
        condition_node = ast_parse_expression(&expr_pos);
    }
    
    XMD_FREE_SAFE(condition_str);
    if (!condition_node) {
        return NULL;
    }
    
    // Create conditional node for elif
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* elif_node = ast_create_conditional(condition_node, loc);
    *pos = start;
    return elif_node;
}
