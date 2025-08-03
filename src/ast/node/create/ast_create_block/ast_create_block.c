/**
 * @file ast_create_block.c
 *
 *
 * @brief Implementation of ast_create_block function
 * 
 * This file contains ONLY the ast_create_block function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Create AST block node
 * @param loc Source location
 * @return New block node or NULL on error
 */
ast_node* ast_create_block(source_location loc) {
    ast_node* node;
    XMD_MALLOC_SAFE(node, ast_node, NULL, "ast_create_block: Failed to allocate memory");
    
    node->type = AST_BLOCK;
    node->data.block.statements = NULL;
    node->data.block.statement_count = 0;
    node->location = loc;
    return node;
}
