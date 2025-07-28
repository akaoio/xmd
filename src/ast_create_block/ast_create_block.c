/**
 * @file ast_create_block.c
 * @brief Create AST block node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST block node
 * @param loc Source location
 * @return New block node or NULL on error
 */
ast_node* ast_create_block(source_location loc) {
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_BLOCK;
    node->location = loc;
    
    node->data.block.statements = NULL;
    node->data.block.statement_count = 0;
    
    return node;
}