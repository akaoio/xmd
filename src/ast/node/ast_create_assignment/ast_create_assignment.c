/**
 * @file ast_create_assignment.c
 * @brief Implementation of ast_create_assignment function
 * 
 * This file contains ONLY the ast_create_assignment function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST assignment node
 * @param variable Variable name
 * @param op Assignment operator
 * @param value Value expression
 * @param loc Source location
 * @return New assignment node or NULL on error
 */
ast_node* ast_create_assignment(const char* variable, binary_operator op, ast_node* value, source_location loc) {
    XMD_VALIDATE_PTRS_RETVAL(NULL, variable, value);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_ASSIGNMENT, NULL);
    
    node->location = loc;
    
    XMD_STRDUP_VALIDATED(node->data.assignment.variable, variable,
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    node->data.assignment.op = op;
    node->data.assignment.value = value;
    
    return node;
}
