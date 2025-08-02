/**
 * @file ast_create_method_def.c
 * @brief Implementation of ast_create_method_def function
 * 
 * This file contains ONLY the ast_create_method_def function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c (backup recovery)
 */

#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "utils.h"
/**
 * @brief Create AST method definition node
 * @param name Method name
 * @param is_private Whether method is private
 * @param loc Source location
 * @return New method def node or NULL on error
 */
ast_node* ast_create_method_def(const char* name, bool is_private, source_location loc) {
    if (!name) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_METHOD_DEF;
    node->data.method_def.name = xmd_strdup(name);
    node->data.method_def.parameters = NULL;
    node->data.method_def.parameter_count = 0;
    node->data.method_def.body = NULL;
    node->data.method_def.is_private = is_private;
    node->location = loc;
    if (!node->data.method_def.name) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    return node;
}
