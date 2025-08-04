/**
 * @file ast_parse_expression_simple.c
 *
 * @brief Implementation of ast_parse_expression_simple function
 * 
 * This file contains ONLY the ast_parse_expression_simple function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast.h"
#include "ast_parser.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Parse expression (numbers, strings, variables, math)
 * @param pos Pointer to current position
 * @return Expression AST node or NULL
 */
ast_node* ast_parse_expression(const char** pos) {
    // Validate input parameters
    XMD_VALIDATE_PARAMS_2(NULL, pos, *pos);
    
    const char* start = *pos;
    
    // Skip whitespace
    XMD_PARSE_SKIP_WHITESPACE(&start);
    
    // Check for end of input
    XMD_PARSE_CHECK_END(&start, NULL);
    
    // Check if this might be an array (multiple comma-separated values)
    const char* scan = start;
    bool in_quotes = false;
    int paren_depth = 0;
    bool has_comma = false;
    
    while (*scan && *scan != '\n') {
        if (*scan == '"' && (scan == start || *(scan-1) != '\\')) {
            in_quotes = !in_quotes;
        } else if (!in_quotes) {
            if (*scan == '(') {
                paren_depth++;
            } else if (*scan == ')') {
                paren_depth--;
            } else if (*scan == ',' && paren_depth == 0) {
                has_comma = true;
                break;
            }
        }
        scan++;
    }
    
    // If we found a comma at top level, parse as array
    if (has_comma) {
        source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
        ast_node* array = ast_create_array_literal(loc);
        XMD_NULL_CHECK(array);
        
        // Parse comma-separated elements
        while (*start && *start != '\n') {
            // Parse one element
            const char* elem_start = start;
            in_quotes = false;
            paren_depth = 0;
            
            // Find end of this element
            while (*start && *start != '\n') {
                if (*start == '"' && (start == elem_start || *(start-1) != '\\')) {
                    in_quotes = !in_quotes;
                } else if (!in_quotes) {
                    if (*start == '(') {
                        paren_depth++;
                    } else if (*start == ')') {
                        paren_depth--;
                    } else if (*start == ',' && paren_depth == 0) {
                        break;
                    }
                }
                start++;
            }
            
            // Extract and parse the element
            size_t elem_len = start - elem_start;
            if (elem_len > 0) {
                char* elem_str;
                XMD_MALLOC_DYNAMIC(elem_str, elem_len + 1, NULL);
                strncpy(elem_str, elem_start, elem_len);
                elem_str[elem_len] = '\0';
                
                // Trim whitespace
                char* trim_start = elem_str;
                while (*trim_start && isspace(*trim_start)) {
                    trim_start++;
                }
                char* trim_end = elem_str + elem_len - 1;
                while (trim_end > trim_start && isspace(*trim_end)) {
                    *trim_end = '\0';
                    trim_end--;
                }
                
                // Parse the element
                const char* elem_pos = trim_start;
                ast_node* element = NULL;
                source_location elem_loc = {1, 1, "input"};
                
                // Parse string literal
                if (*elem_pos == '"') {
                    const char* str_start = elem_pos;
                    element = ast_parse_string_literal(&str_start, &elem_pos);
                } else if ((*elem_pos == '-' || isdigit(*elem_pos))) {
                    // Parse number
                    double val = atof(elem_pos);
                    element = ast_create_number_literal(val, elem_loc);
                } else if (strstr(elem_pos, " + ") || strstr(elem_pos, " - ") || 
                          strstr(elem_pos, " * ") || strstr(elem_pos, " / ")) {
                    // Parse expressions with operators
                    element = ast_parse_math_expression(elem_pos);
                } else {
                    // Parse identifiers/variables
                    element = ast_create_identifier(trim_start, elem_loc);
                }
                
                if (element) {
                    ast_add_element(array, element);
                }
                XMD_FREE_SAFE(elem_str);
            }
            
            // Skip comma if present
            if (*start == ',') {
                start++;
                while (*start && isspace(*start) && *start != '\n') {
                    start++;
                }
            }
        }
        
        *pos = start;
        return array;
    }
    
    // Not an array - parse as single expression
    const char* expr_start = start;
    in_quotes = false;
    paren_depth = 0;
    
    // Read until end of expression
    while (*start && *start != '\n') {
        if (*start == '"' && (start == expr_start || *(start-1) != '\\')) {
            in_quotes = !in_quotes;
        } else if (!in_quotes) {
            if (*start == '(') {
                paren_depth++;
            } else if (*start == ')') {
                if (paren_depth == 0) {
                    break; // End of expression
                }
                paren_depth--;
            } else if (*start == ',' && paren_depth == 0) {
                break; // End of expression
            }
        }
        start++;
    }
    
    size_t expr_len = start - expr_start;
    char* expr_str;
    XMD_MALLOC_DYNAMIC(expr_str, expr_len + 1, NULL);
    strncpy(expr_str, expr_start, expr_len);
    expr_str[expr_len] = '\0';
    
    // Trim trailing whitespace
    char* end = expr_str + expr_len - 1;
    while (end > expr_str && isspace(*end)) {
        *end = '\0';
        end--;
    }
    
    ast_node* result = NULL;
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    
    // Check for lambda function (x => expr or (x, y) => expr)
    if (strstr(expr_str, "=>")) {
        const char* lambda_pos = expr_str;
        result = ast_parse_lambda(&lambda_pos);
    } else if (strchr(expr_str, '?') && strchr(expr_str, ':')) {
        // Check for ternary operator (condition ? true_expr : false_expr)
        const char* ternary_pos = expr_str;
        result = ast_parse_ternary(&ternary_pos);
    } else if (strstr(expr_str, " + ") || strstr(expr_str, " - ") || 
        strstr(expr_str, " * ") || strstr(expr_str, " / ")) {
        // Check for mathematical expressions
        result = ast_parse_math_expression(expr_str);
    } else if (expr_str[0] == '"') {
        // Parse string literal
        const char* str_pos = expr_str;
        result = ast_parse_string_literal(&str_pos, &str_pos);
    } else if ((expr_str[0] == '-' || isdigit(expr_str[0])) && 
               strspn(expr_str + (expr_str[0] == '-' ? 1 : 0), "0123456789.") == 
               strlen(expr_str) - (expr_str[0] == '-' ? 1 : 0)) {
        // Parse number literal
        double val = atof(expr_str);
        result = ast_create_number_literal(val, loc);
    } else {
        // Check if it's a function call
        const char* temp_pos = expr_str;
        ast_node* func_call = ast_parse_potential_function_call(&temp_pos);
        if (func_call) {
            result = func_call;
        } else {
            // Check for object property access first (obj.property)
            if (strchr(expr_str, '.')) {
                result = ast_parse_object_access(expr_str, loc);
            } else {
                // Otherwise treat as variable reference or identifier (may include array access)
                result = ast_parse_identifier_or_array(expr_str, loc);
            }
        }
    }
    
    XMD_FREE_SAFE(expr_str);
    *pos = start;
    return result;
}
