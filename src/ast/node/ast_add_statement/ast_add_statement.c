/**
 * @file ast_add_statement.c
 * @brief Implementation of ast_add_statement function
 * 
 * This file contains ONLY the ast_add_statement function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include "ast_node.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Add a statement to a program or block node
 * @param block Program or block node
 * @param statement Statement to add
 * @return 0 on success, -1 on error
 */
int ast_add_statement(ast_node* block, ast_node* statement) {
    // Add debug prints before validation
    fprintf(stderr, "[DEBUG] ast_add_statement called: block=%p, statement=%p\n", (void*)block, (void*)statement);
    
    XMD_VALIDATE_PTRS_RETVAL(-1, block, statement);
    
    fprintf(stderr, "[DEBUG] block->type=%d (AST_PROGRAM=%d, AST_BLOCK=%d)\n", 
            block->type, AST_PROGRAM, AST_BLOCK);
    
    XMD_VALIDATE_CONDITION_RETVAL(block->type == AST_PROGRAM || block->type == AST_BLOCK, -1,
                                  "Node type does not support statements");
    
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
    
    size_t old_count = *count_ptr;
    size_t new_count = old_count + 1;
    
    // Replace complex macro with safe direct realloc
    if (new_count > SIZE_MAX / sizeof(ast_node*)) {
        XMD_ERROR("AST array resize overflow: %zu elements", new_count);
        return -1;
    }
    
    ast_node** temp = (ast_node**)realloc(*statements_ptr, new_count * sizeof(ast_node*));
    if (!temp) {
        XMD_ERROR("Memory reallocation failed for %zu bytes", new_count * sizeof(ast_node*));
        return -1;
    }
    
    *statements_ptr = temp;
    (*statements_ptr)[old_count] = statement;
    *count_ptr = new_count;
    return 0;
}
