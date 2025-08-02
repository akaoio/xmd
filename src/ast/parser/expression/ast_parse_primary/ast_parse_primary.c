/**
 * @file ast_parse_primary.c
 *
 * @brief Implementation of ast_parse_primary function
 * 
 * This file contains ONLY the ast_parse_primary function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "error.h"
#include "performance.h"
#include "token.h"
#include "variable.h"
/**
 * @brief Parse primary expression (number, string, identifier)
 * @param parser Parser state
 * @return AST node or NULL
 */
ast_node* ast_parse_primary(parser_state* parser) {
    if (!parser || !parser->current_token) {
        printf("[ERROR] ast_parse_primary: NULL parser or token\n");
        return NULL;
    }
    
    token* tok = parser->current_token;
    source_location loc = {tok->line, tok->column, parser->filename};
    parser_advance_token(parser);
    
    switch (tok->type) {
        case TOKEN_NUMBER: {
            double value = strtod(tok->value, NULL);
            return ast_create_number_literal(value, loc);
        }
        case TOKEN_STRING: {
            return ast_create_string_literal(tok->value, loc);
        }
        case TOKEN_BOOLEAN: {
            bool value = strcmp(tok->value, "true") == 0;
            return ast_create_boolean_literal(value, loc);
        }
        case TOKEN_IDENTIFIER: {
            return ast_create_identifier(tok->value, loc);
        }
        default:
            printf("[ERROR] ast_parse_primary: Unexpected token type %d\n", tok->type);
            return NULL;
    }
}
