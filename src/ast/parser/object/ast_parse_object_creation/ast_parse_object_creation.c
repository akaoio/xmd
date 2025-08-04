/**
 * @file ast_parse_object_creation.c
 * @brief Implementation of ast_parse_object_creation function
 * 
 * This file contains ONLY the ast_parse_object_creation function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "store_internal.h"
#include "variable.h"
#include "utils/common/common_macros.h"
/**
 * @brief Parse object creation: set user name "Alice", age 30
 * @param pos Pointer to current position
 * @param obj_name Object variable name already parsed  
 * @return Assignment node with object creation
 */
ast_node* ast_parse_object_creation(const char** pos, const char* obj_name) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos, obj_name);
    const char* start = *pos;
    // Skip "set "
    start += 4;
    while (*start && isspace(*start)) start++;
    // Skip past obj_name to get to key-value pairs
    while (*start && !isspace(*start)) start++;
    while (*start && isspace(*start) && *start != '\n') start++;
    // We need to create an ast_node that evaluates to an object ast_value
    // Since there's no AST_OBJECT_LITERAL node type, we'll use a special marker approach
    // The proper solution would be to add AST_OBJECT_LITERAL type, but this is a quick fix
    
    source_location loc = {1, 1, "input"};
    
    // For now, let's use the old approach and create a string placeholder
    // that the assignment evaluator can recognize as an object creation marker
    char* object_data = NULL;
    size_t data_len = 0;
    
    // Serialize the object data into a special string format: "__OBJECT__:key1=value1,key2=value2"
    const char* object_prefix = "__OBJECT__:";
    size_t prefix_len = strlen(object_prefix);
    
    // Calculate total length needed
    data_len = prefix_len;
    const char* data_start = start;
    const char* data_end = start;
    while (*data_end && *data_end != '\n') {
        data_end++;
    }
    data_len += (data_end - data_start) + 1;
    
    XMD_MALLOC_SAFE(object_data, char[data_len], NULL, "Failed to allocate object data");
    strcpy(object_data, object_prefix);
    strncpy(object_data + prefix_len, data_start, data_end - data_start);
    object_data[data_len - 1] = '\0';
    
    // Create string literal with the object data
    ast_node* object_node = ast_create_string_literal(object_data, loc);
    XMD_FREE_SAFE(object_data);
    
    // Create assignment
    ast_node* assignment = ast_create_assignment(obj_name, BINOP_ASSIGN, object_node, loc);
    
    // Update position to end of object data
    start = data_end;
    *pos = start;
    return assignment;
}
