/**
 * @file ast_create_class_def.c
 *
 *
 * @brief Implementation of ast_create_class_def function
 * 
 * This file contains ONLY the ast_create_class_def function.
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
 * @brief Create AST class definition node
 * @param name Class name
 * @param parent_class Parent class name (or NULL if no inheritance)
 * @param loc Source location
 * @return New class def node or NULL on error
 */
ast_node* ast_create_class_def(const char* name, const char* parent_class, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, name);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_CLASS_DEF, NULL);
    
    XMD_STRDUP_VALIDATED(node->data.class_def.name, name,
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    if (parent_class) {
        XMD_STRDUP_VALIDATED(node->data.class_def.parent_class, parent_class,
                             ({ XMD_FREE_SAFE(node->data.class_def.name); 
                                XMD_FREE_NULL(node); NULL; }));
    } else {
        node->data.class_def.parent_class = NULL;
    }
    
    node->data.class_def.constructor = NULL;
    node->data.class_def.methods = NULL;
    node->data.class_def.method_count = 0;
    node->location = loc;
    
    return node;
}
