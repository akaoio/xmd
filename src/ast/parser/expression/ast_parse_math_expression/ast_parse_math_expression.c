/**
 * @file ast_parse_math_expression.c
 * @brief Implementation of ast_parse_math_expression function
 * 
 * This file contains ONLY the ast_parse_math_expression function.
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
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse mathematical expression: 2 + 3 * 4
 */
ast_node* ast_parse_math_expression(const char* expr) {
    XMD_VALIDATE_PTRS(NULL, expr);
    
    // Simple addition parser for Genesis compliance
    char* expr_copy = xmd_strdup(expr);
    if (!expr_copy) return NULL;
    // Find operators (simple left-to-right for now)
    char* op_pos = NULL;
    binary_operator op_type = BINOP_ADD;
    // Check for operators in order of precedence (for now, just left-to-right)
    if ((op_pos = strstr(expr_copy, " + "))) {
        op_type = BINOP_ADD;
    } else if ((op_pos = strstr(expr_copy, " - "))) {
        op_type = BINOP_SUB;
    } else if ((op_pos = strstr(expr_copy, " * "))) {
        op_type = BINOP_MUL;
    } else if ((op_pos = strstr(expr_copy, " / "))) {
        op_type = BINOP_DIV;
    }
    if (op_pos) {
        *op_pos = '\0';
        char* left_str = expr_copy;
        char* right_str = op_pos + 3;
        
        // Trim whitespace
        while (*left_str && isspace(*left_str)) left_str++;
        while (*right_str && isspace(*right_str)) right_str++;
        // Parse left operand
        ast_node* left = NULL;
        if (*left_str == '"') {
            // Parse string literal
            const char* temp_pos = left_str;
            left = ast_parse_string_literal(&temp_pos, &temp_pos);
        } else if (isdigit(*left_str) || *left_str == '-') {
            double val = atof(left_str);
            source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
            left = ast_create_number_literal(val, loc);
        } else {
            source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
            left = ast_parse_identifier_or_array(left_str, loc);
        }
        // Parse right operand (which might be another expression)
        ast_node* right = NULL;
        // Check if the right side contains more operators
        if (strstr(right_str, " + ") || strstr(right_str, " - ") || 
            strstr(right_str, " * ") || strstr(right_str, " / ")) {
            // Recursively parse the right side as another expression
            right = ast_parse_math_expression(right_str);
        } else if (*right_str == '"') {
            const char* temp_pos = right_str;
            right = ast_parse_string_literal(&temp_pos, &temp_pos);
        } else if (isdigit(*right_str) || *right_str == '-') {
            double val = atof(right_str);
            source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
            right = ast_create_number_literal(val, loc);
        } else {
            // Trim any trailing whitespace from identifier
            char* id_end = right_str + strlen(right_str) - 1;
            while (id_end > right_str && isspace(*id_end)) {
                *id_end = '\0';
                id_end--;
            }
            source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
            right = ast_parse_identifier_or_array(right_str, loc);
        }
        
        if (left && right) {
            source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
            ast_node* result = ast_create_binary_op(op_type, left, right, loc);
            XMD_FREE_SAFE(expr_copy);
            return result;
        } else {
            if (left) XMD_FREE_SAFE(left);
            if (right) XMD_FREE_SAFE(right);
        }
    }
    
    XMD_FREE_SAFE(expr_copy);
    return NULL;
}
