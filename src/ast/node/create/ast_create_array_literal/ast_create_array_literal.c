/**
 * @file ast_create_array_literal.c
 * @brief Implementation of ast_create_array_literal function
 * 
 * This file contains ONLY the ast_create_array_literal function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"

/**
 * @brief Create AST array literal node
 * @param loc Source location
 * @return New array literal node or NULL on error
 */
ast_node* ast_create_array_literal(source_location loc) {
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    memset(node, 0, sizeof(ast_node));
    
    node->type = AST_ARRAY_LITERAL;
    node->data.array_literal.elements = NULL;
    node->data.array_literal.element_count = 0;
    node->location = loc;
    
    return node;
}
