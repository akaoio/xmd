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
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST directive node
 * @param command Directive command (set, if, exec, etc.)
 * @param loc Source location
 * @return New directive node or NULL on error
 */
ast_node* ast_create_directive(const char* command, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, command);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_DIRECTIVE, NULL);
    
    XMD_STRDUP_VALIDATED(node->data.directive.command, command,
                         ({ XMD_FREE_NULL(node); NULL; }));
    node->data.directive.arguments = NULL;
    node->data.directive.argument_count = 0;
    node->location = loc;
    
    return node;
}
