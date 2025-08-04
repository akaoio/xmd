/**
 * @file ast_parse_generator_function.c
 * @brief Implementation of ast_parse_generator_function function
 * 
 * This file contains ONLY the ast_parse_generator_function function.
 * One function per file - Genesis principle compliance.
 * Parses generator function definitions with function* syntax
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Parse generator function definition (function* name ...)
 * @param pos Pointer to current parsing position (will be advanced)
 * @return AST node for generator function or NULL on error
 */
ast_node* ast_parse_generator_function(const char** pos) {
    XMD_VALIDATE_PTR_RETURN(pos, NULL);
    XMD_VALIDATE_PTR_RETURN(*pos, NULL);
    
    const char* start = *pos;
    
    // Skip whitespace
    while (isspace(**pos)) (*pos)++;
    
    // Expect "function*"
    if (strncmp(*pos, "function*", 9) != 0) {
        return NULL;
    }
    *pos += 9;
    
    // Must have whitespace after "function*"
    if (!isspace(**pos)) {
        return NULL;
    }
    
    // Skip whitespace
    while (isspace(**pos)) (*pos)++;
    
    // Parse function name
    const char* name_start = *pos;
    while (isalnum(**pos) || **pos == '_') (*pos)++;
    
    if (*pos == name_start) {
        return NULL; // No function name
    }
    
    // Extract function name
    size_t name_len = *pos - name_start;
    char* function_name;
    XMD_MALLOC_VALIDATED(function_name, char, name_len + 1, NULL);
    strncpy(function_name, name_start, name_len);
    function_name[name_len] = '\0';
    
    // Create generator function AST node
    source_location loc = {1, 1, "unknown"};
    ast_node* generator_node;
    XMD_MALLOC_VALIDATED(generator_node, ast_node, 1, NULL);
    
    generator_node->type = AST_GENERATOR_DEF;
    generator_node->location = loc;
    generator_node->data.generator_def.name = function_name;
    generator_node->data.generator_def.parameters = NULL;
    generator_node->data.generator_def.parameter_count = 0;
    generator_node->data.generator_def.body = NULL;
    
    // Skip whitespace
    while (isspace(**pos)) (*pos)++;
    
    // Parse parameters (space-separated like regular functions)
    // For now, we'll parse a simple parameter list until newline
    const char* params_start = *pos;
    while (**pos && **pos != '\n' && **pos != '\r') {
        if (isalnum(**pos) || **pos == '_' || isspace(**pos)) {
            (*pos)++;
        } else {
            break;
        }
    }
    
    // Simple parameter parsing - split by spaces
    if (*pos > params_start) {
        const char* p = params_start;
        size_t param_count = 0;
        
        // Count parameters
        while (p < *pos) {
            while (p < *pos && isspace(*p)) p++;
            if (p < *pos) {
                param_count++;
                while (p < *pos && !isspace(*p)) p++;
            }
        }
        
        if (param_count > 0) {
            XMD_MALLOC_VALIDATED(generator_node->data.generator_def.parameters, char*, param_count, NULL);
            generator_node->data.generator_def.parameter_count = param_count;
            
            // Parse parameters
            p = params_start;
            size_t param_idx = 0;
            while (p < *pos && param_idx < param_count) {
                while (p < *pos && isspace(*p)) p++;
                if (p < *pos) {
                    const char* param_start = p;
                    while (p < *pos && !isspace(*p)) p++;
                    
                    size_t param_len = p - param_start;
                    XMD_MALLOC_VALIDATED(generator_node->data.generator_def.parameters[param_idx], char, param_len + 1, NULL);
                    strncpy(generator_node->data.generator_def.parameters[param_idx], param_start, param_len);
                    generator_node->data.generator_def.parameters[param_idx][param_len] = '\0';
                    param_idx++;
                }
            }
        }
    }
    
    // Skip to next line for body parsing
    while (**pos && **pos != '\n') (*pos)++;
    if (**pos == '\n') (*pos)++;
    
    // For now, create a simple block body (this would need proper indented block parsing)
    ast_node* body_block;
    XMD_MALLOC_VALIDATED(body_block, ast_node, 1, NULL);
    body_block->type = AST_BLOCK;
    body_block->location = loc;
    body_block->data.block.statements = NULL;
    body_block->data.block.statement_count = 0;
    
    generator_node->data.generator_def.body = body_block;
    
    return generator_node;
}