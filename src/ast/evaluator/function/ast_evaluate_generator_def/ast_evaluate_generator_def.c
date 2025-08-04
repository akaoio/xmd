/**
 * @file ast_evaluate_generator_def.c
 * @brief Implementation of ast_evaluate_generator_def function
 * 
 * This file contains ONLY the ast_evaluate_generator_def function.
 * One function per file - Genesis principle compliance.
 * Evaluates generator function definitions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Generator state structure for managing generator execution
 */
typedef struct {
    ast_node* generator_def;     /**< Generator function definition */
    ast_node* current_node;      /**< Current execution point */
    store* local_variables;      /**< Generator local variables */
    bool is_finished;            /**< Whether generator is exhausted */
    ast_value* last_yielded;     /**< Last yielded value */
} generator_state;

/**
 * @brief Evaluate generator function definition
 * @param node Generator function AST node
 * @param evaluator AST evaluator context
 * @return Generator function object or NULL on error
 */
ast_value* ast_evaluate_generator_def(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_AST_VALIDATE_TYPE(node, AST_GENERATOR_DEF, NULL, "ast_evaluate_generator_def");
    
    // Store the generator function in the functions store
    if (evaluator->functions) {
        // For now, store as a string representation
        char* gen_str;
        size_t str_size = 256;
        XMD_MALLOC_VALIDATED(gen_str, char, str_size, NULL);
        
        snprintf(gen_str, str_size, "generator:%s(%zu params)", 
                node->data.generator_def.name ? node->data.generator_def.name : "anonymous",
                node->data.generator_def.parameter_count);
        
        // Create a variable with the string value
        variable* gen_var = variable_create_string(gen_str);
        if (gen_var) {
            store_set(evaluator->functions, node->data.generator_def.name, gen_var);
        }
        
        XMD_FREE_SAFE(gen_str);
    }
    
    // Create a generator state object (simplified for now)
    char* generator_info;
    size_t info_size = 512;
    XMD_MALLOC_VALIDATED(generator_info, char, info_size, NULL);
    
    snprintf(generator_info, info_size, "Generator function '%s' with %zu parameters defined",
            node->data.generator_def.name ? node->data.generator_def.name : "anonymous",
            node->data.generator_def.parameter_count);
    
    // List parameters
    if (node->data.generator_def.parameter_count > 0) {
        strcat(generator_info, " (params: ");
        FOR_EACH_INDEX(i, node->data.generator_def.parameter_count) {
            if (i > 0) strcat(generator_info, ", ");
            if (node->data.generator_def.parameters[i]) {
                strcat(generator_info, node->data.generator_def.parameters[i]);
            }
        }
        strcat(generator_info, ")");
    }
    
    ast_value* result = ast_value_create_string(generator_info);
    XMD_FREE_SAFE(generator_info);
    
    return result;
}