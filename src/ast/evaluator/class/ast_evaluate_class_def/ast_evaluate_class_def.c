/**
 * @file ast_evaluate_class_def.c
 * @brief Implementation of ast_evaluate_class_def function
 * 
 * This file contains ONLY the ast_evaluate_class_def function.
 * One function per file - Genesis principle compliance.
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
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate class definition node (store class for later instantiation)
 * @param node Class definition AST node
 * @param evaluator Evaluator context
 * @return Empty string value
 */
ast_value* ast_evaluate_class_def(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_CLASS_DEF, NULL, "ast_evaluate_class_def: Invalid node type");
    
    // Store the class AST node pointer in evaluator's classes store
    // Similar to function storage but for classes
    variable* class_var;
    XMD_MALLOC_CHECK(class_var, sizeof(variable));
    
    // Use VAR_NULL type for class storage - the pointer won't be freed
    class_var->type = VAR_NULL;
    class_var->value.object_value = (variable_object*)node; // Store AST node pointer safely
    class_var->ref_count = 1;
    
    // Store in evaluator's classes store (reuse functions store for now)
    if (!evaluator->functions) {
        XMD_FREE_SAFE(class_var);
        return NULL;
    }
    
    // Store class by name for instantiation
    const char* class_name = node->data.class_def.name;
    if (!class_name) {
        XMD_FREE_SAFE(class_var);
        return NULL;
    }
    
    fprintf(stderr, "DEBUG: Storing class '%s' in store (ptr: %p)\\n", class_name, (void*)evaluator->functions);
    store_set(evaluator->functions, class_name, class_var);
    variable_unref(class_var);
    
    // Class definitions return empty string (no output)
    return ast_value_create_string("");
}