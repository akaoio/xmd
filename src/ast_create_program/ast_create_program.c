/**
 * @file ast_create_program.c
 * @brief Create AST program node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST program node
 * @return New program node or NULL on error
 */
ast_node* ast_create_program(void) {
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_PROGRAM;
    node->location.line = 0;
    node->location.column = 0;
    node->location.filename = NULL;
    
    node->data.program.statements = NULL;
    node->data.program.statement_count = 0;
    
    return node;
}