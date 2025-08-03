/**
 * @file ast_parse_function.c
 *
 * @brief Implementation of ast_parse_function function
 * 
 * This file contains ONLY the ast_parse_function function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "error.h"
#include "module.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse function definition: function name param1 param2
 * @param pos Pointer to current position
 * @return Function definition AST node or NULL
 */
ast_node* ast_parse_function(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    const char* start = *pos;
    
    // Skip "function "
    start += 9;
    while (*start && isspace(*start)) {
        start++;
    }
    
    // Get function name
    const char* name_start = start;
    while (*start && !isspace(*start) && *start != '\n') {
        start++;
    }
    
    size_t name_len = start - name_start;
    if (name_len == 0) {
        // Skip to end of line on error
        while (**pos && **pos != '\n') {
            (*pos)++;
        }
        return NULL;
    }
    
    char* func_name;
    XMD_MALLOC_SAFE(func_name, char[name_len + 1], NULL, "ast_parse_function: Failed to allocate function name");
    if (!func_name) {
        return NULL;
    }
    strncpy(func_name, name_start, name_len);
    func_name[name_len] = '\0';
    
    // Create function definition node
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* func_def = ast_create_function_def(func_name, false, loc);
    free(func_name);
    
    if (!func_def) {
        return NULL;
    }
    
    // Parse space-separated parameters
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    while (*start && *start != '\n') {
        // Get parameter name
        const char* param_start = start;
        while (*start && !isspace(*start) && *start != '\n') {
            start++;
        }
        
        if (start > param_start) {
            size_t param_len = start - param_start;
            char* param_name;
            XMD_MALLOC_DYNAMIC(param_name, param_len + 1, NULL);
            strncpy(param_name, param_start, param_len);
            param_name[param_len] = '\0';
            ast_add_parameter(func_def, param_name);
            free(param_name);
        }
        
        // Skip whitespace
        while (*start && isspace(*start) && *start != '\n') {
            start++;
        }
    }
    
    
    // Function definition created without body (body parsing handled by caller)
    
    *pos = start;
    return func_def;
}
