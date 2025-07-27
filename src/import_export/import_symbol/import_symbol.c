/**
 * @file import_symbol.c
 * @brief Import specific symbol from module
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/import_export.h"

/**
 * @brief Import specific symbol from module
 * @param processor Import/export processor
 * @param module_name Module name or path
 * @param symbol_name Symbol to import
 * @param alias Alias for symbol (NULL for no alias)
 * @return ModuleResult indicating success/failure
 */
int import_symbol(ImportExportProcessor* processor, 
                 const char* module_name,
                 const char* symbol_name, 
                 const char* alias) {
    if (!processor || !module_name || !symbol_name) {
        return MODULE_ERROR;
    }
    
    // Find the module in the registry
    Module* module = module_registry_find(processor->registry, module_name);
    if (!module) {
        return MODULE_NOT_FOUND;
    }
    
    // Get the exported symbol from the module
    variable* exported_var = module_get_export(module, symbol_name);
    if (!exported_var) {
        return MODULE_ERROR;
    }
    
    // Use alias if provided, otherwise use original symbol name
    const char* import_name = alias ? alias : symbol_name;
    
    // Add the symbol to current scope
    variable_ref(exported_var);
    bool success = store_set(processor->current_scope, import_name, exported_var);
    
    return success ? MODULE_SUCCESS : MODULE_ERROR;
}