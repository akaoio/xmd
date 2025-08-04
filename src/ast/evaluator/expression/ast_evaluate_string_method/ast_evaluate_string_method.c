/**
 * @file ast_evaluate_string_method.c
 *
 * @brief Implementation of ast_evaluate_string_method function
 * 
 * This file contains ONLY the ast_evaluate_string_method function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "ast_evaluator.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Evaluate string method calls (.upper, .lower, .split, .join, etc.)
 * @param node String method AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_string_method(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_STRING_METHOD, NULL, "ast_evaluate_string_method: Invalid node type");
    
    // Evaluate the string expression
    ast_value* string_val = ast_evaluate(node->data.string_method.string_expr, evaluator);
    if (!string_val || string_val->type != AST_VAL_STRING) {
        XMD_FREE_SAFE(string_val);
        XMD_ERROR_RETURN(NULL, "String method called on non-string value%s", "");
    }
    
    const char* str = string_val->value.string_value;
    const char* method = node->data.string_method.method_name;
    ast_value* result = NULL;
    
    if (STR_EQUALS(method, "upper")) {
        // Convert to uppercase
        size_t len = strlen(str);
        char* upper_str = xmd_malloc(len + 1);
        if (upper_str) {
            for (size_t i = 0; i <= len; i++) {
                upper_str[i] = toupper(str[i]);
            }
            result = ast_value_create_string(upper_str);
            XMD_FREE_SAFE(upper_str);
        }
        
    } else if (STR_EQUALS(method, "lower")) {
        // Convert to lowercase
        size_t len = strlen(str);
        char* lower_str = xmd_malloc(len + 1);
        if (lower_str) {
            for (size_t i = 0; i <= len; i++) {
                lower_str[i] = tolower(str[i]);
            }
            result = ast_value_create_string(lower_str);
            XMD_FREE_SAFE(lower_str);
        }
        
    } else if (STR_EQUALS(method, "split")) {
        // Split string by delimiter
        const char* delimiter = " "; // Default delimiter
        if (node->data.string_method.argument_count > 0) {
            ast_value* delim_val = ast_evaluate(node->data.string_method.arguments[0], evaluator);
            if (delim_val && delim_val->type == AST_VAL_STRING) {
                delimiter = delim_val->value.string_value;
            }
        }
        
        // Create array result
        result = ast_value_create_array();
        if (result) {
            char* str_copy = xmd_strdup(str);
            if (str_copy) {
                char* token = strtok(str_copy, delimiter);
                while (token) {
                    ast_value* token_val = ast_value_create_string(token);
                    if (token_val) {
                        ast_value_array_add(result, token_val);
                    }
                    token = strtok(NULL, delimiter);
                }
                XMD_FREE_SAFE(str_copy);
            }
        }
        
    } else if (STR_EQUALS(method, "trim")) {
        // Trim whitespace from both ends
        const char* start = str;
        while (isspace(*start)) start++;
        
        const char* end = str + strlen(str) - 1;
        while (end > start && isspace(*end)) end--;
        
        size_t len = end - start + 1;
        char* trimmed = xmd_malloc(len + 1);
        if (trimmed) {
            strncpy(trimmed, start, len);
            trimmed[len] = '\0';
            result = ast_value_create_string(trimmed);
            XMD_FREE_SAFE(trimmed);
        }
        
    } else if (STR_EQUALS(method, "length")) {
        // Get string length
        result = ast_value_create_number((double)strlen(str));
        
    } else {
        XMD_FREE_SAFE(string_val);
        XMD_ERROR_RETURN(NULL, "Unknown string method: %s", method);
    }
    
    XMD_FREE_SAFE(string_val);
    return result;
}