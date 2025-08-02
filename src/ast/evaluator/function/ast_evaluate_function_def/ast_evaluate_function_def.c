/**
 * @file ast_evaluate_function_def.c
 *
 *
 * @brief Implementation of ast_evaluate_function_def function
 * 
 * This file contains ONLY the ast_evaluate_function_def function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "module.h"
#include "store.h"
#include "variable.h"
#include "utils.h"
/**
 * @brief Evaluate function definition node (store function for later calls)
 * @param node Function definition AST node
 * @param evaluator Evaluator context
 * @return Empty string value
 */
ast_value* ast_evaluate_function_def(ast_node* node, ast_evaluator* evaluator) {
    if (!node || node->type != AST_FUNCTION_DEF || !evaluator) {
        return NULL;
    }
    
    printf("DEBUG: Evaluating function definition: %s\n", node->data.function_def.name);
    // Initialize global functions store if needed
    // ast_functions_init();  // Stub - function missing
    // Store the function AST node pointer directly in global functions store
    // We'll use a custom variable type that can hold a pointer
    variable* func_var = xmd_malloc(sizeof(variable));
    if (!func_var) {
        return ast_value_create_string("");
    }
    
    func_var->type = VAR_STRING; // Reuse string type temporarily
    func_var->value.string_value = (char*)node; // Store AST node pointer 
    func_var->ref_count = 1;
    store_set(global_functions, node->data.function_def.name, func_var);
    variable_unref(func_var);
    printf("DEBUG: Function '%s' stored for later calls\n", node->data.function_def.name);
    // Function definitions return empty string (no output)
    return ast_value_create_string("");
}
