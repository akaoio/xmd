/**
 * @file ast_create_boolean_literal.c
 * @brief Implementation of ast_create_boolean_literal function
 * 
 * This file contains ONLY the ast_create_boolean_literal function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST boolean literal node
 * @param value Boolean value
 * @param loc Source location
 * @return New boolean node or NULL on error
 */
ast_node* ast_create_boolean_literal(bool value, source_location loc) {
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_LITERAL, NULL);
    
    node->data.literal.type = LITERAL_BOOLEAN;
    node->data.literal.value.boolean_value = value;
    node->location = loc;
    
    return node;
}
