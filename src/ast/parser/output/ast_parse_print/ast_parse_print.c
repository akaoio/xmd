/**
 * @file ast_parse_print_simple.c
 * @brief Implementation of ast_parse_print_simple function
 * 
 * This file contains ONLY the ast_parse_print_simple function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "error.h"
#include "utils/common/common_macros.h"
/**
 * @brief Parse print statement: print "message" or print variable
 * @param pos Pointer to current position
 * @return Print function call AST node or NULL
 */
ast_node* ast_parse_print(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    const char* start = *pos;
    
    // Skip "print "
    start += 6;
    while (*start && isspace(*start) && *start != '\n') start++;
    // Parse the full expression to print (handles concatenation, math, etc.)
    ast_node* expr = ast_parse_expression(&start);
    if (!expr) {
        // Skip to end of line on error
        while (**pos && **pos != '\n') (*pos)++;
        return NULL;
    }
    // Create a function call node for print
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* print_call = ast_create_function_call("print", loc);
    if (print_call) {
        ast_add_argument(print_call, expr);
    } else {
        XMD_FREE_SAFE(expr);
    }
    *pos = start;
    return print_call;
}
