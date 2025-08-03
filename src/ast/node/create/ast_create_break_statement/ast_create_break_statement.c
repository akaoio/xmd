/**
 * @file ast_create_break_statement.c
 *
 *
 * @brief Implementation of ast_create_break_statement function
 * 
 * This file contains ONLY the ast_create_break_statement function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Create break statement node
 * @param loc Source location
 * @return Break statement node or NULL
 */
ast_node* ast_create_break_statement(source_location loc) {
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_BREAK;
    node->location = loc;
    return node;
}
