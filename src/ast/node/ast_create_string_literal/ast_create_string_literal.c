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
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST string literal node
 * @param value String value (without quotes)
 * @param loc Source location
 * @return New string node or NULL on error
 */
ast_node* ast_create_string_literal(const char* value, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, value);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_LITERAL, NULL);
    
    node->data.literal.type = LITERAL_STRING;
    XMD_STRDUP_VALIDATED(node->data.literal.value.string_value, value, 
                         ({ XMD_FREE_NULL(node); NULL; }));
    node->location = loc;
    
    return node;
}
