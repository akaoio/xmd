/**
 * @file ast_create_lambda.c
 * @brief Implementation of ast_create_lambda function
 * 
 * This file contains ONLY the ast_create_lambda function.
 * One function per file - Genesis principle compliance.
 * Creates lambda function AST nodes (x => x * 2)
 */

#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils.h"
#include "../../../utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create lambda function AST node
 * @param parameters Array of parameter names
 * @param parameter_count Number of parameters
 * @param body Lambda body expression
 * @param loc Source location
 * @return New lambda AST node or NULL on error
 */
ast_node* ast_create_lambda(char** parameters, size_t parameter_count, ast_node* body, source_location loc) {
    XMD_VALIDATE_PTR_RETURN(body, NULL);
    
    ast_node* node;
    XMD_MALLOC_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_LAMBDA;
    node->location = loc;
    node->data.lambda.body = body;
    node->data.lambda.parameter_count = parameter_count;
    
    // Copy parameters if provided
    if (parameters && parameter_count > 0) {
        node->data.lambda.parameters = xmd_malloc(parameter_count * sizeof(char*));
        if (!node->data.lambda.parameters) {
            XMD_FREE_SAFE(node);
            return NULL;
        }
        
        FOR_EACH_INDEX(i, parameter_count) {
            if (parameters[i]) {
                node->data.lambda.parameters[i] = xmd_strdup(parameters[i]);
                if (!node->data.lambda.parameters[i]) {
                    // Cleanup previously allocated parameters
                    for (size_t j = 0; j < i; j++) {
                        XMD_FREE_SAFE(node->data.lambda.parameters[j]);
                    }
                    XMD_FREE_SAFE(node->data.lambda.parameters);
                    XMD_FREE_SAFE(node);
                    return NULL;
                }
            } else {
                node->data.lambda.parameters[i] = NULL;
            }
        }
    } else {
        node->data.lambda.parameters = NULL;
    }
    
    return node;
}