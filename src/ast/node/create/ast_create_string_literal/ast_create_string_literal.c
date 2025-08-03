/**
 * @file ast_create_string_literal.c
 * @brief Implementation of ast_create_string_literal function
 * 
 * This file contains ONLY the ast_create_string_literal function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"

/**
 * @brief Create AST string literal node
 * @param value String value (without quotes)
 * @param loc Source location
 * @return New string node or NULL on error
 */
ast_node* ast_create_string_literal(const char* value, source_location loc) {
    if (!value) {
        return NULL;
    }
    
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    memset(node, 0, sizeof(ast_node));
    
    node->type = AST_LITERAL;
    node->data.literal.type = LITERAL_STRING;
    node->data.literal.value.string_value = xmd_strdup(value);
    node->location = loc;
    
    if (!node->data.literal.value.string_value) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    return node;
}
