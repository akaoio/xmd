/**
 * @file ast_create_destructure.c
 *
 * @brief Implementation of ast_create_destructure function
 * 
 * This file contains ONLY the ast_create_destructure function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Create destructuring assignment AST node
 * @param target_names Array of target variable names
 * @param target_count Number of target variables
 * @param source_expr Source expression to destructure from
 * @param is_object true for object destructuring, false for array
 * @param rest_name Rest parameter name (NULL if no rest)
 * @param loc Source location
 * @return AST node or NULL on failure
 */
ast_node* ast_create_destructure(char** target_names, size_t target_count, ast_node* source_expr, bool is_object, const char* rest_name, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, target_names, source_expr);
    
    ast_node* node = XMD_CALLOC(1, sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_DESTRUCTURE;
    node->location = loc;
    
    // Copy target names
    node->data.destructure.target_names = XMD_MALLOC(target_count * sizeof(char*));
    if (!node->data.destructure.target_names) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    for (size_t i = 0; i < target_count; i++) {
        if (target_names[i]) {
            node->data.destructure.target_names[i] = XMD_STRDUP(target_names[i]);
            if (!node->data.destructure.target_names[i]) {
                // Cleanup on failure
                for (size_t j = 0; j < i; j++) {
                    XMD_FREE_SAFE(node->data.destructure.target_names[j]);
                }
                XMD_FREE_SAFE(node->data.destructure.target_names);
                XMD_FREE_SAFE(node);
                return NULL;
            }
        } else {
            node->data.destructure.target_names[i] = NULL;
        }
    }
    
    node->data.destructure.target_count = target_count;
    node->data.destructure.source_expr = source_expr;
    node->data.destructure.is_object = is_object;
    
    // Copy rest name if provided
    if (rest_name) {
        node->data.destructure.rest_name = XMD_STRDUP(rest_name);
        if (!node->data.destructure.rest_name) {
            // Cleanup on failure
            for (size_t i = 0; i < target_count; i++) {
                XMD_FREE_SAFE(node->data.destructure.target_names[i]);
            }
            XMD_FREE_SAFE(node->data.destructure.target_names);
            XMD_FREE_SAFE(node);
            return NULL;
        }
    } else {
        node->data.destructure.rest_name = NULL;
    }
    
    return node;
}