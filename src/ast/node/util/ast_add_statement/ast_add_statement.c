/**
 * @file ast_add_statement.c
 * @brief Implementation of ast_add_statement function
 * 
 * This file contains ONLY the ast_add_statement function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "variable.h"
/**
 * @brief Add a statement to a program or block node
 * @param block Program or block node
 * @param statement Statement to add
 * @return 0 on success, -1 on error
 */
int ast_add_statement(ast_node* block, ast_node* statement) {
    if (!block || !statement) {
        return -1;
    }
    
    if (block->type != AST_PROGRAM && block->type != AST_BLOCK) {
        return -1;
    }
    
    // Determine which union member to use
    ast_node*** statements_ptr;
    size_t* count_ptr;
    if (block->type == AST_PROGRAM) {
        statements_ptr = &block->data.program.statements;
        count_ptr = &block->data.program.statement_count;
    } else {
        statements_ptr = &block->data.block.statements;
        count_ptr = &block->data.block.statement_count;
    }
    
    // Reallocate array
    ast_node** new_statements = xmd_realloc(*statements_ptr, 
                                           (*count_ptr + 1) * sizeof(ast_node*));
    if (!new_statements) {
        return -1;
    }
    
    *statements_ptr = new_statements;
    (*statements_ptr)[*count_ptr] = statement;
    (*count_ptr)++;
    return 0;
}
