/**
 * @file ast_create_try_catch.c
 * @brief Implementation of ast_create_try_catch function
 * 
 * This file contains ONLY the ast_create_try_catch function.
 * One function per file - Genesis principle compliance.
 * Creates try-catch error handling AST nodes
 */

#include <stdlib.h>
#include "ast.h"
#include "utils.h"
#include "../../../utils/common/common_macros.h"
#include "../../../utils/common/validation_macros.h"

/**
 * @brief Create try-catch AST node
 * @param try_block Block to execute that might throw
 * @param catch_var Variable name to capture exception in catch block
 * @param catch_block Block to execute if exception is thrown
 * @param loc Source location
 * @return New try-catch AST node or NULL on error
 */
ast_node* ast_create_try_catch(ast_node* try_block, const char* catch_var, ast_node* catch_block, source_location loc) {
    XMD_VALIDATE_PARAMS_2(NULL, try_block, catch_block);
    
    ast_node* node;
    XMD_MALLOC_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_TRY_CATCH;
    node->location = loc;
    node->data.try_catch.try_block = try_block;
    node->data.try_catch.catch_block = catch_block;
    
    // Duplicate catch variable name if provided
    if (catch_var) {
        XMD_STRDUP_VALIDATED(node->data.try_catch.catch_variable, catch_var, {
            XMD_FREE_SAFE(node);
            return NULL;
        });
    } else {
        node->data.try_catch.catch_variable = NULL;
    }
    
    return node;
}