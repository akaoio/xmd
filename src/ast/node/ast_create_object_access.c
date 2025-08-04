/**
 * @file ast_create_object_access.c
 * @brief Implementation of ast_create_object_access function
 * 
 * This file contains ONLY the ast_create_object_access function.
 * One function per file - Genesis principle compliance.
 * Handles creation of object property access AST nodes.
 */

#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST object access node
 * @param object_expr Object expression
 * @param property_name Property name to access
 * @param loc Source location
 * @return New object access node or NULL on error
 */
ast_node* ast_create_object_access(ast_node* object_expr, const char* property_name, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, object_expr, property_name);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_OBJECT_ACCESS, NULL);
    node->data.object_access.object_expr = object_expr;
    
    // Duplicate the property name string
    XMD_STRDUP_VALIDATED(node->data.object_access.property_name, property_name, 
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    node->location = loc;
    return node;
}
