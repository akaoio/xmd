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
#include <string.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "module.h"
#include "store.h"
#include "variable.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Evaluate function definition node (store function for later calls)
 * @param node Function definition AST node
 * @param evaluator Evaluator context
 * @return Empty string value
 */
ast_value* ast_evaluate_function_def(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_FUNCTION_DEF, NULL, "ast_evaluate_function_def: Invalid node type");
    
    
    // Store the function AST node pointer in evaluator's functions store
    // We'll use a custom variable type that can hold a pointer
    variable* func_var;
    func_var = xmd_malloc(sizeof(variable));
    if (!func_var) {
        fprintf(stderr, "[ERROR] ast_evaluate_function_def: Failed to allocate function variable at %s:%d\n", __FILE__, __LINE__);
        return NULL;
    }
    
    // Use VAR_NULL type for function storage - the pointer won't be freed
    func_var->type = VAR_NULL; // NULL type doesn't free any value
    func_var->value.object_value = (variable_object*)node; // Store AST node pointer safely 
    func_var->ref_count = 1;
    
    // Store in evaluator's functions store
    if (!evaluator->functions) {
        fprintf(stderr, "ERROR: Functions store not initialized in evaluator\n");
        free(func_var);
        return NULL;
    }
    
    // Extract just the function name without parameters for storage key
    const char* full_name = node->data.function_def.name;
    char func_name_only[256];
    const char* paren = strchr(full_name, '(');
    if (paren) {
        size_t name_len = paren - full_name;
        if (name_len < sizeof(func_name_only)) {
            strncpy(func_name_only, full_name, name_len);
            func_name_only[name_len] = '\0';
        } else {
            strncpy(func_name_only, full_name, sizeof(func_name_only) - 1);
            func_name_only[sizeof(func_name_only) - 1] = '\0';
        }
    } else {
        strncpy(func_name_only, full_name, sizeof(func_name_only) - 1);
        func_name_only[sizeof(func_name_only) - 1] = '\0';
    }
    
    // fprintf(stderr, "DEBUG: Storing function '%s' with %zu parameters in store (ptr: %p)\n", func_name_only, node->data.function_def.parameter_count, (void*)evaluator->functions);
    store_set(evaluator->functions, func_name_only, func_var);
    variable_unref(func_var);
    // Function definitions return empty string (no output)
    return ast_value_create_string("");
}
