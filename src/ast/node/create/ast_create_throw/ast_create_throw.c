/**
 * @file ast_create_throw.c
 *
 * @brief Implementation of ast_create_throw function
 * 
 * This file contains ONLY the ast_create_throw function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include "ast.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Create throw statement AST node
 * @param exception Exception expression to throw
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_throw(ast_node* exception, source_location loc) {
    XMD_VALIDATE_PTR_RETURN(exception, NULL);
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    XMD_NULL_CHECK(node);
    
    node->type = AST_THROW;
    node->location = loc;
    node->data.throw_stmt.exception = exception;
    
    return node;
}