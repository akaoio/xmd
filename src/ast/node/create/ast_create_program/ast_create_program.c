/**
 * @file ast_create_program.c
 * @brief Implementation of ast_create_program function
 * 
 * This file contains ONLY the ast_create_program function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Create AST program node
 * @return New program node or NULL on error
 */
ast_node* ast_create_program(void) {
    ast_node* node;
    XMD_MALLOC_SAFE(node, ast_node, NULL, "ast_create_program: Failed to allocate memory");
    
    node->type = AST_PROGRAM;
    node->data.program.statements = NULL;
    node->data.program.statement_count = 0;
    node->location.line = 0;
    node->location.column = 0;
    node->location.filename = NULL;
    return node;
}
