/**
 * @file ast_create_number_literal.c
 * @brief Implementation of ast_create_number_literal function
 * 
 * This file contains ONLY the ast_create_number_literal function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "variable.h"
/**
 * @brief Create AST number literal node
 * @param value Number value
 * @param loc Source location
 * @return New number node or NULL on error
 */
ast_node* ast_create_number_literal(double value, source_location loc) {
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_LITERAL;
    node->data.literal.type = LITERAL_NUMBER;
    node->data.literal.value.number_value = value;
    node->location = loc;
    return node;
}
