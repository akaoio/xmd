/**
 * @file ast_parse_object_access.c
 * @brief Implementation of ast_parse_object_access function
 * 
 * This file contains ONLY the ast_parse_object_access function.
 * One function per file - Genesis principle compliance.
 * Detects obj.property syntax and creates appropriate AST nodes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Parse identifier or object property access (obj.property)
 * @param identifier_str The identifier string to parse
 * @param loc Source location for AST nodes
 * @return AST node (identifier or object access)
 */
ast_node* ast_parse_object_access(const char* identifier_str, source_location loc) {
    if (!identifier_str) return NULL;
    
    
    // Look for dot to detect object property access
    const char* dot_pos = strchr(identifier_str, '.');
    if (!dot_pos) {
        // No dot, just a regular identifier
        return ast_create_identifier(identifier_str, loc);
    }
    
    // Extract object name (before '.')
    size_t object_name_len = dot_pos - identifier_str;
    char* object_name = xmd_malloc(object_name_len + 1);
    if (!object_name) {
        return NULL;
    }
    strncpy(object_name, identifier_str, object_name_len);
    object_name[object_name_len] = '\0';
    
    // Extract property name (after '.')
    const char* property_start = dot_pos + 1;
    size_t property_len = strlen(property_start);
    if (property_len == 0) {
        XMD_FREE_SAFE(object_name);
        return ast_create_identifier(identifier_str, loc);
    }
    
    char* property_name = xmd_malloc(property_len + 1);
    if (!property_name) {
        XMD_FREE_SAFE(object_name);
        return NULL;
    }
    strcpy(property_name, property_start);
    
    
    // Create object expression (identifier)
    ast_node* object_expr = ast_create_identifier(object_name, loc);
    if (!object_expr) {
        XMD_FREE_SAFE(object_name);
        XMD_FREE_SAFE(property_name);
        return NULL;
    }
    
    // Create object access node
    ast_node* result = ast_create_object_access(object_expr, property_name, loc);
    if (result) {
    } else {
        ast_free(object_expr);
    }
    
    XMD_FREE_SAFE(object_name);
    // Note: property_name is now owned by the AST node, don't free here
    
    return result;
}
