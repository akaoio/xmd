/**
 * @file import_all_symbols.c
 * @brief Import all symbols function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/import_export.h"

/**
 * @brief Import all symbols from module
 * @param processor Import/export processor
 * @param module_name Module name or path
 * @return ModuleResult indicating success/failure
 */
int import_all_symbols(ImportExportProcessor* processor, const char* module_name) {
    if (!processor || !module_name) {
        return MODULE_ERROR;
    }
    
    // Find module in registry
    Module* module = module_registry_find(processor->registry, module_name);
    if (!module) {
        return MODULE_NOT_FOUND;
    }
    
    // Get all export keys
    size_t key_count = 0;
    char** keys = store_keys(module->exports, &key_count);
    if (!keys && key_count > 0) {
        return MODULE_ERROR;
    }
    
    // Import each exported symbol
    for (size_t i = 0; i < key_count; i++) {
        variable* exported_var = store_get(module->exports, keys[i]);
        if (exported_var) {
            variable_ref(exported_var);
            store_set(processor->current_scope, keys[i], exported_var);
        }
    }
    
    // Free keys array
    for (size_t i = 0; i < key_count; i++) {
        free(keys[i]);
    }
    free(keys);
    
    return MODULE_SUCCESS;
}