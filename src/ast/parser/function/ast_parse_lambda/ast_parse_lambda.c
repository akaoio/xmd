/**
 * @file ast_parse_lambda.c
 * @brief Implementation of ast_parse_lambda function
 * 
 * This file contains ONLY the ast_parse_lambda function.
 * One function per file - Genesis principle compliance.
 * Parses lambda function expressions (x => x * 2)
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "ast.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Parse lambda function expression
 * @param pos Pointer to current position in input (will be advanced)
 * @return Lambda AST node or NULL if not a lambda expression
 */
ast_node* ast_parse_lambda(const char** pos) {
    if (!pos || !*pos) return NULL;
    
    const char* saved_pos = *pos;
    source_location loc = {1, 1, "input"};
    
    // Skip whitespace
    while (**pos && isspace(**pos)) (*pos)++;
    
    char** parameters = NULL;
    int param_count = 0;
    
    // Check for parenthesized parameter list (a, b) => ...
    if (**pos == '(') {
        (*pos)++; // Skip '('
        
        // Parse comma-separated parameters
        parameters = xmd_malloc(sizeof(char*) * 10); // Max 10 params
        if (!parameters) {
            *pos = saved_pos;
            return NULL;
        }
        
        while (**pos && **pos != ')') {
            // Skip whitespace
            while (**pos && isspace(**pos)) (*pos)++;
            
            if (!isalpha(**pos) && **pos != '_') break;
            
            const char* param_start = *pos;
            while (isalnum(**pos) || **pos == '_') (*pos)++;
            size_t param_len = *pos - param_start;
            
            parameters[param_count] = xmd_malloc(param_len + 1);
            if (!parameters[param_count]) {
                for (int i = 0; i < param_count; i++) {
                    xmd_free(parameters[i]);
                }
                xmd_free(parameters);
                *pos = saved_pos;
                return NULL;
            }
            
            memcpy(parameters[param_count], param_start, param_len);
            parameters[param_count][param_len] = '\0';
            param_count++;
            
            // Skip whitespace
            while (**pos && isspace(**pos)) (*pos)++;
            
            // Check for comma
            if (**pos == ',') {
                (*pos)++;
                while (**pos && isspace(**pos)) (*pos)++;
            }
        }
        
        if (**pos != ')') {
            for (int i = 0; i < param_count; i++) {
                xmd_free(parameters[i]);
            }
            xmd_free(parameters);
            *pos = saved_pos;
            return NULL;
        }
        (*pos)++; // Skip ')'
        
    } else if (isalpha(**pos) || **pos == '_') {
        // Simple lambda: identifier => expression
        const char* param_start = *pos;
        while (isalnum(**pos) || **pos == '_') (*pos)++;
        size_t param_len = *pos - param_start;
        
        parameters = xmd_malloc(sizeof(char*));
        if (!parameters) {
            *pos = saved_pos;
            return NULL;
        }
        
        parameters[0] = xmd_malloc(param_len + 1);
        if (!parameters[0]) {
            xmd_free(parameters);
            *pos = saved_pos;
            return NULL;
        }
        
        memcpy(parameters[0], param_start, param_len);
        parameters[0][param_len] = '\0';
        param_count = 1;
    } else {
        *pos = saved_pos;
        return NULL;
    }
    
    // Skip whitespace
    while (**pos && isspace(**pos)) (*pos)++;
    
    // Check for =>
    if (strncmp(*pos, "=>", 2) != 0) {
        *pos = saved_pos;
        return NULL;
    }
    *pos += 2;
    
    // Skip whitespace
    while (**pos && isspace(**pos)) (*pos)++;
    
    // Parse body expression
    ast_node* body = ast_parse_expression(pos);
    if (!body) {
        for (int i = 0; i < param_count; i++) {
            xmd_free(parameters[i]);
        }
        xmd_free(parameters);
        *pos = saved_pos;
        return NULL;
    }
    
    // Create lambda node
    ast_node* lambda = ast_create_lambda(parameters, param_count, body, loc);
    if (!lambda) {
        for (int i = 0; i < param_count; i++) {
            xmd_free(parameters[i]);
        }
        xmd_free(parameters);
        ast_free(body);
        *pos = saved_pos;
        return NULL;
    }
    
    return lambda;
}
