/**
 * @file ast_create_assignment.c
 * @brief Create AST assignment node
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST assignment node
 * @param variable Variable name (will be copied)
 * @param op Assignment operator
 * @param value Value expression (takes ownership)
 * @param loc Source location
 * @return New assignment node or NULL on error
 */
ast_node* ast_create_assignment(const char* variable, binary_operator op, ast_node* value, source_location loc) {
    if (!variable || !value) {
        return NULL;
    }
    
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_ASSIGNMENT;
    node->location = loc;
    
    node->data.assignment.variable = strdup(variable);
    if (!node->data.assignment.variable) {
        free(node);
        return NULL;
    }
    
    node->data.assignment.op = op;
    node->data.assignment.value = value;
    
    return node;
}