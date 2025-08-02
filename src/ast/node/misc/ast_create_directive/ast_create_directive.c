/**
 * @file ast_create_directive.c
 * @brief Implementation of ast_create_directive function
 * 
 * This file contains ONLY the ast_create_directive function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "cli.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Create AST directive node
 * @param command Directive command (set, if, exec, etc.)
 * @param loc Source location
 * @return New directive node or NULL on error
 */
ast_node* ast_create_directive(const char* command, source_location loc) {
    if (!command) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_DIRECTIVE;
    node->data.directive.command = xmd_strdup(command);
    node->data.directive.arguments = NULL;
    node->data.directive.argument_count = 0;
    node->location = loc;
    
    if (!node->data.directive.command) {
        free(node);
        return NULL;
    }
    
    return node;
}
