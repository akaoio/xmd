/**
 * @file ast_create_throw.c
 * @brief Implementation of ast_create_throw function
 * 
 * This file contains ONLY the ast_create_throw function.
 * One function per file - Genesis principle compliance.
 * Creates throw statement AST nodes
 */

#include <stdlib.h>
#include "ast.h"
#include "utils.h"
#include "../../../utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create throw statement AST node
 * @param exception Expression to throw as exception
 * @param loc Source location
 * @return New throw AST node or NULL on error
 */
ast_node* ast_create_throw(ast_node* exception, source_location loc) {
    XMD_VALIDATE_PTR_RETURN(exception, NULL);
    
    ast_node* node;
    XMD_MALLOC_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_THROW;
    node->location = loc;
    node->data.throw_stmt.exception = exception;
    
    return node;
}