/**
 * @file ast_create_literal.c
 * @brief Consolidated literal creation function
 * 
 * This file contains the unified ast_create_literal function.
 * Replaces separate string/number/boolean literal creators.
 * Genesis principle compliance - DRY elimination.
 */

#include <stdbool.h>
#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Create AST literal node for any type
 * @param type Literal type (string/number/boolean)
 * @param value Union containing the actual value
 * @param loc Source location
 * @return New literal node or NULL on error
 */
ast_node* ast_create_literal(literal_type type, literal_value value, source_location loc) {
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_LITERAL;
    node->data.literal.type = type;
    node->location = loc;
    
    switch (type) {
        case LITERAL_STRING:
            if (!value.string_value) {
                xmd_free(node);
                return NULL;
            }
            node->data.literal.value.string_value = xmd_strdup(value.string_value);
            if (!node->data.literal.value.string_value) {
                xmd_free(node);
                return NULL;
            }
            break;
        case LITERAL_NUMBER:
            node->data.literal.value.number_value = value.number_value;
            break;
        case LITERAL_BOOLEAN:
            node->data.literal.value.boolean_value = value.boolean_value;
            break;
        default:
            xmd_free(node);
            return NULL;
    }
    
    return node;
}

/**
 * @brief Convenience wrapper for string literals
 */
ast_node* ast_create_string_literal(const char* value, source_location loc) {
    literal_value val;
    val.string_value = value;
    return ast_create_literal(LITERAL_STRING, val, loc);
}

/**
 * @brief Convenience wrapper for number literals
 */
ast_node* ast_create_number_literal(double value, source_location loc) {
    literal_value val;
    val.number_value = value;
    return ast_create_literal(LITERAL_NUMBER, val, loc);
}

/**
 * @brief Convenience wrapper for boolean literals
 */
ast_node* ast_create_boolean_literal(bool value, source_location loc) {
    literal_value val;
    val.boolean_value = value;
    return ast_create_literal(LITERAL_BOOLEAN, val, loc);
}