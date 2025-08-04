/**
 * @file ast_create_generator_def.c
 * @brief Implementation of ast_create_generator_def function
 * 
 * This file contains ONLY the ast_create_generator_def function.
 * One function per file - Genesis principle compliance.
 */

#include "ast_node.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST generator function definition node
 * @param name Generator function name
 * @param parameters Array of parameter names
 * @param parameter_count Number of parameters
 * @param body Generator function body
 * @param loc Source location
 * @return New generator def node or NULL on error
 */
ast_node* ast_create_generator_def(const char* name, char** parameters, size_t parameter_count, ast_node* body, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, name);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_GENERATOR_DEF, NULL);
    
    node->location = loc;
    
    XMD_STRDUP_VALIDATED(node->data.generator_def.name, name, 
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    // Initialize parameters
    if (parameter_count > 0 && parameters) {
        node->data.generator_def.parameters = xmd_calloc(parameter_count, sizeof(char*));
        if (!node->data.generator_def.parameters) {
            XMD_FREE_NULL(node->data.generator_def.name);
            XMD_FREE_NULL(node);
            return NULL;
        }
        
        for (size_t i = 0; i < parameter_count; i++) {
            if (parameters[i]) {
                node->data.generator_def.parameters[i] = xmd_strdup(parameters[i]);
                if (!node->data.generator_def.parameters[i]) {
                    // Cleanup on failure
                    for (size_t j = 0; j < i; j++) {
                        XMD_FREE_NULL(node->data.generator_def.parameters[j]);
                    }
                    XMD_FREE_NULL(node->data.generator_def.parameters);
                    XMD_FREE_NULL(node->data.generator_def.name);
                    XMD_FREE_NULL(node);
                    return NULL;
                }
            }
        }
    } else {
        node->data.generator_def.parameters = NULL;
    }
    
    node->data.generator_def.parameter_count = parameter_count;
    node->data.generator_def.body = body;
    
    return node;
}