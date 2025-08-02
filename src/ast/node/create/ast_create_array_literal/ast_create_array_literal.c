/**
 * @file ast_create_array_literal.c
 *
 *
 * @brief Implementation of ast_create_array_literal function
 * 
 * This file contains ONLY the ast_create_array_literal function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "variable.h"
/**
 * @brief Create AST array literal node
 * @param loc Source location
 * @return New array literal node or NULL on error
 */
ast_node* ast_create_array_literal(source_location loc) {
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_ARRAY_LITERAL;
    node->data.array_literal.elements = NULL;
    node->data.array_literal.element_count = 0;
    node->location = loc;
    return node;
}
