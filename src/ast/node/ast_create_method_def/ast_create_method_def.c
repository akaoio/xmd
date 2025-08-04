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
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Create AST method definition node
 * @param name Method name
 * @param is_private Whether method is private
 * @param loc Source location
 * @return New method def node or NULL on error
 */
ast_node* ast_create_method_def(const char* name, bool is_private, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, name);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_METHOD_DEF, NULL);
    
    XMD_STRDUP_VALIDATED(node->data.method_def.name, name,
                         ({ XMD_FREE_NULL(node); NULL; }));
    node->data.method_def.parameters = NULL;
    node->data.method_def.parameter_count = 0;
    node->data.method_def.body = NULL;
    node->data.method_def.is_private = is_private;
    node->location = loc;
    
    return node;
}
