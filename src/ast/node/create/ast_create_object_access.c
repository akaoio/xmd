/**
 * @file ast_create_object_access.c
 * @brief Implementation of ast_create_object_access function
 * 
 * This file contains ONLY the ast_create_object_access function.
 * One function per file - Genesis principle compliance.
 * Handles creation of object property access AST nodes.
 */

#include <stdlib.h>
#include "../../../../include/ast.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Create AST object access node
 * @param object_expr Object expression
 * @param property_name Property name to access
 * @param loc Source location
 * @return New object access node or NULL on error
 */
ast_node* ast_create_object_access(ast_node* object_expr, const char* property_name, source_location loc) {
    if (!object_expr) return NULL;
    if (!property_name) return NULL;
    
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_OBJECT_ACCESS;
    node->data.object_access.object_expr = object_expr;
    
    // Duplicate the property name string
    node->data.object_access.property_name = xmd_strdup(property_name);
    if (!node->data.object_access.property_name) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    node->location = loc;
    return node;
}
