/**
 * @file ast_create_string_literal.c
 * @brief Implementation of ast_create_string_literal function
 * 
 * This file contains ONLY the ast_create_string_literal function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST string literal node
 * @param value String value
 * @param loc Source location
 * @return New string literal node or NULL on error
 */
ast_node* ast_create_string_literal(const char* value, source_location loc) {
    XMD_VALIDATE_PTRS_RETVAL(NULL, value);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_LITERAL, NULL);
    
    node->data.literal.type = LITERAL_STRING;
    node->data.literal.value.string_value = xmd_strdup(value);
    if (!node->data.literal.value.string_value) {
        xmd_free(node);
        return NULL;
    }
    
    node->location = loc;
    return node;
}
