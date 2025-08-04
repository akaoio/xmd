/**
 * @file ast_create_object_access.c
 * @brief Implementation of ast_create_object_access function
 * 
 * This file contains ONLY the ast_create_object_access function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST object access node (obj.property)
 * @param object Object expression 
 * @param property Property name to access
 * @param loc Source location
 * @return New object access node or NULL on error
 */
ast_node* ast_create_object_access(ast_node* object, const char* property, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, object, property);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_OBJECT_ACCESS, NULL);
    
    node->data.object_access.object_expr = object;
    XMD_STRDUP_VALIDATED(node->data.object_access.property_name, property,
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    node->location = loc;
    return node;
}