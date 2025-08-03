/**
 * @file ast_create_return.c
 * @brief Implementation of ast_create_return function
 * 
 * This file contains ONLY the ast_create_return function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"

/**
 * @brief Create AST return statement node
 * @param value Return value expression (can be NULL)
 * @param loc Source location
 * @return New return node or NULL on error
 */
ast_node* ast_create_return(ast_node* value, source_location loc) {
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_RETURN;
    node->data.return_stmt.value = value;
    node->location = loc;
    return node;
}
