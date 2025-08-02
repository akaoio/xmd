/**
 * @file ast_create_string_literal.c
 * @brief Implementation of ast_create_string_literal function
 * 
 * This file contains ONLY the ast_create_string_literal function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"
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
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_LITERAL;
    node->data.literal.type = LITERAL_STRING;
    node->data.literal.value.string_value = xmd_strdup(value);
    node->location = loc;
    if (!node->data.literal.value.string_value) {
        free(node);
        return NULL;
    }
    return node;
}
