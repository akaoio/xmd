/**
 * @file ast_create_string_method.c
 *
 * @brief Implementation of ast_create_string_method function
 * 
 * This file contains ONLY the ast_create_string_method function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Create string method call AST node
 * @param string_expr String expression
 * @param method_name Method name (upper, lower, split, etc.)
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_string_method(ast_node* string_expr, const char* method_name, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, string_expr, method_name);
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    XMD_NULL_CHECK(node);
    
    node->type = AST_STRING_METHOD;
    node->location = loc;
    
    node->data.string_method.string_expr = string_expr;
    node->data.string_method.method_name = xmd_strdup(method_name);
    node->data.string_method.arguments = NULL;
    node->data.string_method.argument_count = 0;
    
    if (!node->data.string_method.method_name) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    return node;
}