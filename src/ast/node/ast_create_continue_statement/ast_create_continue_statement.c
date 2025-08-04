/**
 * @file ast_create_continue_statement.c
 *
 *
 * @brief Implementation of ast_create_continue_statement function
 * 
 * This file contains ONLY the ast_create_continue_statement function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "variable.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Create continue statement node
 * @param loc Source location
 * @return Continue statement node or NULL
 */
ast_node* ast_create_continue_statement(source_location loc) {
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_CONTINUE, NULL);
    
    node->location = loc;
    return node;
}
