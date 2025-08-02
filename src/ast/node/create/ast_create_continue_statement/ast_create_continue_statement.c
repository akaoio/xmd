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
/**
 * @brief Create continue statement node
 * @param loc Source location
 * @return Continue statement node or NULL
 */
ast_node* ast_create_continue_statement(source_location loc) {
    ast_node* node = xmd_calloc(1, sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_CONTINUE;
    node->location = loc;
    return node;
}
