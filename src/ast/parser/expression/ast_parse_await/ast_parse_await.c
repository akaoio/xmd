/**
 * @file ast_parse_await.c
 *
 * @brief Implementation of ast_parse_await function
 * 
 * This file contains ONLY the ast_parse_await function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ast_parse.h"
#include "../../../../../utils/common/validation_macros.h"

/**
 * @brief Parse await expression
 * @param parser Parser state
 * @return AST node or NULL on error
 */
ast_node* ast_parse_await(parser_state* parser) {
    XMD_VALIDATE_PARAMS_1(NULL, parser);
    
    if (!parser->current_token || parser->current_token->type != TOKEN_KEYWORD ||
        !STR_EQUALS(parser->current_token->value, "await")) {
        return NULL;
    }
    
    source_location loc = {
        .line = parser->current_token->line,
        .column = parser->current_token->column,
        .filename = parser->filename  
    };
    
    // Consume 'await' keyword
    parser->current_token = parser->current_token->next;
    
    // Parse expression to await
    ast_node* expression = ast_parse_expression(&parser);
    if (!expression) {
        XMD_ERROR_RETURN(NULL, "Expected expression after 'await'%s", "");
    }
    
    return ast_create_await(expression, loc);
}