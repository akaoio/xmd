/**
 * @file ast_create_try_catch.c
 *
 * @brief Implementation of ast_create_try_catch function
 * 
 * This file contains ONLY the ast_create_try_catch function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Create try-catch AST node
 * @param try_block Try block AST node
 * @param catch_var Catch variable name
 * @param catch_block Catch block AST node
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_try_catch(ast_node* try_block, const char* catch_var, ast_node* catch_block, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, try_block, catch_var, catch_block);
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    XMD_NULL_CHECK(node);
    
    node->type = AST_TRY_CATCH;
    node->location = loc;
    
    node->data.try_catch.try_block = try_block;
    node->data.try_catch.catch_variable = xmd_strdup(catch_var);
    node->data.try_catch.catch_block = catch_block;
    
    if (!node->data.try_catch.catch_variable) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    return node;
}