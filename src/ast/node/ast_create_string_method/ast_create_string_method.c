/**
 * @file ast_create_string_method.c
 * @brief Implementation of ast_create_string_method function
 * 
 * This file contains ONLY the ast_create_string_method function.
 * One function per file - Genesis principle compliance.
 * Creates string method call AST nodes (str.upper, str.split)
 */

#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils.h"
#include "../../../utils/common/common_macros.h"
#include "../../../utils/common/validation_macros.h"

/**
 * @brief Create string method call AST node
 * @param string_expr String expression to call method on
 * @param method_name Method name (upper, lower, split, join, trim)
 * @param loc Source location
 * @return New string method AST node or NULL on error
 */
ast_node* ast_create_string_method(ast_node* string_expr, const char* method_name, source_location loc) {
    XMD_VALIDATE_PARAMS_2(NULL, string_expr, method_name);
    
    ast_node* node;
    XMD_MALLOC_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_STRING_METHOD;
    node->location = loc;
    node->data.string_method.string_expr = string_expr;
    node->data.string_method.argument_count = 0;
    node->data.string_method.arguments = NULL;
    
    XMD_STRDUP_VALIDATED(node->data.string_method.method_name, method_name, {
        XMD_FREE_SAFE(node);
        return NULL;
    });
    
    return node;
}