/**
 * @file ast_parse_throw.c
 * @brief Implementation of ast_parse_throw function
 * 
 * This file contains ONLY the ast_parse_throw function.
 * One function per file - Genesis principle compliance.
 * Parses throw statements
 */

#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Parse throw statement
 * @param pos Pointer to current position in input (will be advanced)
 * @return Throw AST node or NULL on error
 */
ast_node* ast_parse_throw(const char** pos) {
    XMD_VALIDATE_PTR_RETURN(pos, NULL);
    XMD_PARSE_VALIDATE_POS(pos, NULL);
    
    const char* start = *pos;
    source_location loc = {1, *pos - start, NULL};
    
    // Expect 'throw' keyword
    XMD_PARSE_EXPECT_KEYWORD(pos, "throw", NULL);
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse exception expression
    ast_node* exception = ast_parse_expression(pos);
    if (!exception) {
        XMD_ERROR_RETURN(NULL, "Expected expression after 'throw'");
    }
    
    // Create throw node
    ast_node* throw_node = ast_create_throw(exception, loc);
    if (!throw_node) {
        ast_free(exception);
        return NULL;
    }
    
    return throw_node;
}