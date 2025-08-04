/**
 * @file ast_parse_comparison_expression.c
 *
 * @brief Implementation of ast_parse_comparison_expression function
 * 
 * This file contains ONLY the ast_parse_comparison_expression function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "utils.h"
#include "../../../../../utils/common/common_macros.h"
/**
 * @brief Parse comparison expression: variable = value
 * @param expr Expression string to parse
 * @return Binary operation AST node or NULL
 */
static int recursion_depth = 0;
static int max_recursion = 100;

ast_node* ast_parse_comparison_expression(const char* expr) {
    if (!expr) {
        return NULL;
    }
    
    recursion_depth++;
    
    if (recursion_depth > max_recursion) {
        fprintf(stderr, "ERROR: Maximum recursion depth %d exceeded in ast_parse_comparison_expression\n", max_recursion);
        fprintf(stderr, "       Expression causing loop: '%s'\n", expr);
        recursion_depth--;
        return NULL;
    }
    
    char* expr_copy = xmd_strdup(expr);
    if (!expr_copy) {
        return NULL;
    }
    
    char* left_str = NULL;
    char* right_str = NULL;
    binary_operator op = BINOP_EQ;
    char* op_pos = NULL;
    int op_len = 0;
    
    // Look for comparison operators in order of precedence (longest first)
    
    // XMD uses ONLY single = for comparison, no == operator
    if ((op_pos = strstr(expr_copy, " <= "))) {
        op = BINOP_LE;
        op_len = 4;
    } else if ((op_pos = strstr(expr_copy, " >= "))) {
        op = BINOP_GE;
        op_len = 4;
    } else if ((op_pos = strstr(expr_copy, " != "))) {
        op = BINOP_NE;
        op_len = 4;
    } else if ((op_pos = strstr(expr_copy, " < "))) {
        op = BINOP_LT;
        op_len = 3;
    } else if ((op_pos = strstr(expr_copy, " > "))) {
        op = BINOP_GT;
        op_len = 3;
    } else if ((op_pos = strstr(expr_copy, " = "))) {
        op = BINOP_EQ;
        op_len = 3;
    } else {
        // No comparison operator found
        XMD_FREE_SAFE(expr_copy);
        recursion_depth--;
        return NULL;
    }
    
    // Split at operator
    *op_pos = '\0';
    left_str = expr_copy;
    right_str = op_pos + op_len;
    
    // Trim whitespace from both operands
    while (*left_str && isspace(*left_str)) left_str++;
    while (*right_str && isspace(*right_str)) right_str++;
    
    // Trim trailing whitespace
    char* end = left_str + strlen(left_str) - 1;
    while (end > left_str && isspace(*end)) *end-- = '\0';
    end = right_str + strlen(right_str) - 1;
    while (end > right_str && isspace(*end)) *end-- = '\0';
    
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    
    // Parse left operand
    ast_node* left = NULL;
    if (*left_str == '"') {
        // String literal - remove quotes
        size_t len = strlen(left_str);
        if (len >= 2 && left_str[len-1] == '"') {
            char* string_val;
            XMD_MALLOC_DYNAMIC(string_val, len - 1, NULL);
            strncpy(string_val, left_str + 1, len - 2);
            string_val[len - 2] = '\0';
            left = ast_create_string_literal(string_val, loc);
            XMD_FREE_SAFE(string_val);
        }
    } else if (isdigit(*left_str) || *left_str == '-') {
        double val = atof(left_str);
        left = ast_create_number_literal(val, loc);
    } else {
        left = ast_create_identifier(left_str, loc);
    }
    
    // Parse right operand
    ast_node* right = NULL;
    if (*right_str == '"') {
        size_t len = strlen(right_str);
        if (len >= 2 && right_str[len-1] == '"') {
            char* string_val;
            XMD_MALLOC_DYNAMIC(string_val, len - 1, NULL);
            strncpy(string_val, right_str + 1, len - 2);
            string_val[len - 2] = '\0';
            right = ast_create_string_literal(string_val, loc);
            XMD_FREE_SAFE(string_val);
        }
    } else if (isdigit(*right_str) || *right_str == '-') {
        double val = atof(right_str);
        right = ast_create_number_literal(val, loc);
    } else {
        right = ast_create_identifier(right_str, loc);
    }
    
    ast_node* result = NULL;
    if (left && right) {
        result = ast_create_binary_op(op, left, right, loc);
        
        // Debug logging switch - fully commented out
        // const char* op_name = "=";
        switch (op) {
            case BINOP_LT: /* op_name = "<"; */ break;
            case BINOP_LE: /* op_name = "<="; */ break;
            case BINOP_GT: /* op_name = ">"; */ break;
            case BINOP_GE: /* op_name = ">="; */ break;
            case BINOP_EQ: /* op_name = "="; */ break;
            case BINOP_NE: /* op_name = "!="; */ break;
            default: /* op_name = "?"; */ break;
        }
    } else {
        if (left) XMD_FREE_SAFE(left);
        if (right) XMD_FREE_SAFE(right);
    }
    
    XMD_FREE_SAFE(expr_copy);
    recursion_depth--;
    return result;
}
