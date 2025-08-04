#!/bin/bash
# Fix lambda parser macro issues
cat > /home/x/Projects/xmd/src/ast/parser/function/ast_parse_lambda/ast_parse_lambda.c << 'EOF'
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
    
    // Simple lambda: identifier => expression
    // Parse single parameter
    if (!isalpha(**pos) && **pos != '_') {
        *pos = saved_pos;
        return NULL;
    }
    
    const char* param_start = *pos;
    while (isalnum(**pos) || **pos == '_') (*pos)++;
    size_t param_len = *pos - param_start;
    
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
        *pos = saved_pos;
        return NULL;
    }
    
    // Create parameter array
    char** parameters = xmd_malloc(sizeof(char*));
    if (!parameters) {
        ast_free(body);
        *pos = saved_pos;
        return NULL;
    }
    
    parameters[0] = xmd_malloc(param_len + 1);
    if (!parameters[0]) {
        xmd_free(parameters);
        ast_free(body);
        *pos = saved_pos;
        return NULL;
    }
    
    memcpy(parameters[0], param_start, param_len);
    parameters[0][param_len] = '\0';
    
    // Create lambda node
    ast_node* lambda = ast_create_lambda(parameters, 1, body, loc);
    if (!lambda) {
        xmd_free(parameters[0]);
        xmd_free(parameters);
        ast_free(body);
        *pos = saved_pos;
        return NULL;
    }
    
    return lambda;
}
EOF

echo "Fixed lambda parser"