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
#include "ast.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Parse lambda function expression
 * @param pos Pointer to current position in input (will be advanced)
 * @return Lambda AST node or NULL if not a lambda expression
 */
ast_node* ast_parse_lambda(const char** pos) {
    XMD_VALIDATE_PTR_RETURN(pos, NULL);
    XMD_PARSE_VALIDATE_POS(pos, NULL);
    
    const char* start = *pos;
    const char* saved_pos = *pos;
    source_location loc = {1, *pos - start, NULL};
    
    // Parse parameters (simple case: single parameter or parenthesized list)
    char** parameters = NULL;
    size_t parameter_count = 0;
    
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Check for parenthesized parameter list
    if (**pos == '(') {
        (*pos)++; // Skip '('
        XMD_PARSE_SKIP_WHITESPACE(pos);
        
        // Parse parameter list
        while (**pos && **pos != ')') {
            const char* param_start;
            const char* param_end;
            
            XMD_PARSE_IDENTIFIER(pos, param_start, param_end, {
                *pos = saved_pos;
                return NULL;
            });
            
            // Grow parameter array
            parameter_count++;
            XMD_REALLOC_VALIDATED(parameters, char*, parameter_count * sizeof(char*), {
                *pos = saved_pos;
                return NULL;
            });
            
            // Copy parameter name
            size_t param_len = param_end - param_start;
            XMD_MALLOC_VALIDATED(parameters[parameter_count - 1], char, param_len + 1, {
                FOR_EACH_INDEX(i, parameter_count - 1) {
                    XMD_FREE_SAFE(parameters[i]);
                }
                XMD_FREE_SAFE(parameters);
                *pos = saved_pos;
                return NULL;
            });
            
            memcpy(parameters[parameter_count - 1], param_start, param_len);
            parameters[parameter_count - 1][param_len] = '\0';
            
            XMD_PARSE_SKIP_WHITESPACE(pos);
            
            // Check for comma
            if (**pos == ',') {
                (*pos)++;
                XMD_PARSE_SKIP_WHITESPACE(pos);
            }
        }
        
        if (**pos != ')') {
            FOR_EACH_INDEX(i, parameter_count) {
                XMD_FREE_SAFE(parameters[i]);
            }
            XMD_FREE_SAFE(parameters);
            *pos = saved_pos;
            return NULL;
        }
        (*pos)++; // Skip ')'
    } 
    // Single parameter without parentheses
    else if (isalpha(**pos) || **pos == '_') {
        const char* param_start;
        const char* param_end;
        
        XMD_PARSE_IDENTIFIER(pos, param_start, param_end, {
            *pos = saved_pos;
            return NULL;
        });
        
        parameter_count = 1;
        XMD_MALLOC_VALIDATED(parameters, char*, sizeof(char*), {
            *pos = saved_pos;
            return NULL;
        });
        
        size_t param_len = param_end - param_start;
        XMD_MALLOC_VALIDATED(parameters[0], char, param_len + 1, {
            XMD_FREE_SAFE(parameters);
            *pos = saved_pos;
            return NULL;
        });
        
        memcpy(parameters[0], param_start, param_len);
        parameters[0][param_len] = '\0';
    } else {
        // No parameters, not a lambda
        *pos = saved_pos;
        return NULL;
    }
    
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Look for '=>' operator
    if (strncmp(*pos, "=>", 2) != 0) {
        // Not a lambda, restore position and cleanup
        FOR_EACH_INDEX(i, parameter_count) {
            XMD_FREE_SAFE(parameters[i]);
        }
        XMD_FREE_SAFE(parameters);
        *pos = saved_pos;
        return NULL;
    }
    
    *pos += 2; // Skip '=>'
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse body expression
    ast_node* body = ast_parse_expression(pos);
    if (!body) {
        FOR_EACH_INDEX(i, parameter_count) {
            XMD_FREE_SAFE(parameters[i]);
        }
        XMD_FREE_SAFE(parameters);
        XMD_ERROR_RETURN(NULL, "Expected expression after '=>' in lambda");
    }
    
    // Create lambda node
    ast_node* lambda = ast_create_lambda(parameters, parameter_count, body, loc);
    
    // Cleanup parameter array (ast_create_lambda copies the strings)
    FOR_EACH_INDEX(i, parameter_count) {
        XMD_FREE_SAFE(parameters[i]);
    }
    XMD_FREE_SAFE(parameters);
    
    if (!lambda) {
        ast_free(body);
        return NULL;
    }
    
    return lambda;
}