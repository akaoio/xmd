/**
 * @file ast_parse_array_assignment.c
 * @brief Implementation of ast_parse_array_assignment function
 * 
 * This file contains ONLY the ast_parse_array_assignment function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "../../../../../utils/common/common_macros.h"
/**
 * @brief Parse array assignment: set scores 1, 2, 3
 * @param pos Pointer to current position
 * @param array_name Array variable name already parsed
 * @return Assignment node with array creation
 */
ast_node* ast_parse_array_assignment(const char** pos, const char* array_name) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos, array_name);
    const char* start = *pos;
    // Skip "set "
    start += 4;
    while (*start && isspace(*start)) start++;
    // Skip past array_name to get to values
    while (*start && !isspace(*start)) start++;
    while (*start && isspace(*start) && *start != '\n') start++;
    // Parse array values using existing expression parser (it handles comma-separated values)
    ast_node* array_expr = ast_parse_expression(&start);
    if (!array_expr) {
        return NULL;
    }
    source_location loc = {0, 0, ""};
    ast_node* assignment = ast_create_assignment(array_name, BINOP_ASSIGN, array_expr, loc);
    *pos = start;
    return assignment;
}
