/**
 * @file ast_create_variable_ref.c
 * @brief Implementation of ast_create_variable_ref function
 * 
 * This file contains ONLY the ast_create_variable_ref function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"
#include "variable_internal.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST variable reference node
 * @param name Variable name
 * @param loc Source location
 * @return New variable ref node or NULL on error
 */
ast_node* ast_create_variable_ref(const char* name, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, name);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_VARIABLE_REF, NULL);
    
    XMD_STRDUP_VALIDATED(node->data.variable_ref.name, name,
                         ({ XMD_FREE_NULL(node); NULL; }));
    node->location = loc;
    
    return node;
}
