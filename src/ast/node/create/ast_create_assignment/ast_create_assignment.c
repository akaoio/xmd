/**
 * @file ast_create_assignment.c
 * @brief Implementation of ast_create_assignment function
 * 
 * This file contains ONLY the ast_create_assignment function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Create AST assignment node
 * @param variable Variable name
 * @param op Assignment operator
 * @param value Value expression
 * @param loc Source location
 * @return New assignment node or NULL on error
 */
ast_node* ast_create_assignment(const char* variable, binary_operator op, ast_node* value, source_location loc) {
    if (!variable || !value) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_ASSIGNMENT;
    node->data.assignment.variable = xmd_strdup(variable);
    node->data.assignment.op = op;
    node->data.assignment.value = value;
    node->location = loc;
    if (!node->data.assignment.variable) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    return node;
}
