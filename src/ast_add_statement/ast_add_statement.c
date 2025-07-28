/**
 * @file ast_add_statement.c
 * @brief Add statement to AST block or program node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include "../../include/ast_node.h"

/**
 * @brief Add statement to AST block or program node
 * @param block Block or program node
 * @param statement Statement to add (takes ownership)
 * @return 0 on success, -1 on error
 */
int ast_add_statement(ast_node* block, ast_node* statement) {
    if (!block || !statement) {
        return -1;
    }
    
    if (block->type == AST_BLOCK) {
        size_t new_count = block->data.block.statement_count + 1;
        ast_node** new_statements = realloc(block->data.block.statements, 
                                           new_count * sizeof(ast_node*));
        if (!new_statements) {
            return -1;
        }
        
        new_statements[block->data.block.statement_count] = statement;
        block->data.block.statements = new_statements;
        block->data.block.statement_count = new_count;
        return 0;
    }
    
    if (block->type == AST_PROGRAM) {
        size_t new_count = block->data.program.statement_count + 1;
        ast_node** new_statements = realloc(block->data.program.statements, 
                                           new_count * sizeof(ast_node*));
        if (!new_statements) {
            return -1;
        }
        
        new_statements[block->data.program.statement_count] = statement;
        block->data.program.statements = new_statements;
        block->data.program.statement_count = new_count;
        return 0;
    }
    
    return -1;
}