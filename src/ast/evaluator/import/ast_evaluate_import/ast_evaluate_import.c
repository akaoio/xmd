/**
 * @file ast_evaluate_import.c
 * @brief Implementation of ast_evaluate_import function
 * 
 * This file contains ONLY the ast_evaluate_import function.
 * One function per file - Genesis principle compliance.
 * Part of Phase 2 module system implementation.
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
 * @brief Evaluate import statement - load module and import its exports
 * @param node Import AST node
 * @param evaluator Evaluator context
 * @return Empty string value (imports don't produce output)
 */
ast_value* ast_evaluate_import(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_IMPORT, NULL, "ast_evaluate_import: Invalid node type");
    
    // Validate module path
    XMD_VALIDATE_STRING_RETVAL(node->data.import_stmt.module_path, NULL);
    
    // Initialize module registry if not present
    if (!evaluator->module_registry) {
        evaluator->module_registry = module_registry_new();
        if (!evaluator->module_registry) {
            XMD_ERROR_RETURN(NULL, "ast_evaluate_import: Failed to create module registry%s", "");
        }
        
        // Add current directory as default search path
        module_registry_add_search_path(evaluator->module_registry, ".");
        // Add sandbox directory for test modules
        module_registry_add_search_path(evaluator->module_registry, "sandbox");
    }
    
    const char* module_path = node->data.import_stmt.module_path;
    
    // Check if module is already loaded
    Module* existing_module = module_registry_find(evaluator->module_registry, module_path);
    if (existing_module && existing_module->loaded) {
        // Module already loaded, import its exports
        if (existing_module->exports) {
            size_t export_count = 0;
            char** export_keys = store_keys(existing_module->exports, &export_count);
            if (export_keys) {
                for (size_t i = 0; i < export_count; i++) {
                    variable* export_var = store_get(existing_module->exports, export_keys[i]);
                    if (export_var) {
                        // Copy exported variable to current evaluator's variables
                        variable_ref(export_var); // Add reference
                        store_set(evaluator->variables, export_keys[i], export_var);
                        variable_unref(export_var); // Release our reference
                    }
                    XMD_FREE_SAFE(export_keys[i]);
                }
                XMD_FREE_SAFE(export_keys);
            }
        }
        return ast_value_create_string("");
    }
    
    // Load new module
    int result = module_registry_load(evaluator->module_registry, module_path);
    if (result != MODULE_SUCCESS) {
        switch (result) {
            case MODULE_NOT_FOUND:
                XMD_ERROR_RETURN(NULL, "ast_evaluate_import: Module '%s' not found", module_path);
            case MODULE_CIRCULAR_DEPENDENCY:
                XMD_ERROR_RETURN(NULL, "ast_evaluate_import: Circular dependency detected for module '%s'", module_path);
            default:
                XMD_ERROR_RETURN(NULL, "ast_evaluate_import: Failed to load module '%s' (error %d)", module_path, result);
        }
    }
    
    // Get loaded module and import its exports
    Module* loaded_module = module_registry_find(evaluator->module_registry, module_path);
    if (loaded_module && loaded_module->exports) {
        size_t export_count = 0;
        char** export_keys = store_keys(loaded_module->exports, &export_count);
        if (export_keys) {
            for (size_t i = 0; i < export_count; i++) {
                variable* export_var = store_get(loaded_module->exports, export_keys[i]);
                if (export_var) {
                    // Copy exported variable to current evaluator's variables
                    variable_ref(export_var); // Add reference
                    store_set(evaluator->variables, export_keys[i], export_var);
                    variable_unref(export_var); // Release our reference
                }
                XMD_FREE_SAFE(export_keys[i]);
            }
            XMD_FREE_SAFE(export_keys);
        }
    }
    
    // Import statements return empty string (no output)
    return ast_value_create_string("");
}