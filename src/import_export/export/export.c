/**
 * @file export.c
 * @brief Export symbol function
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/import_export.h"

/**
 * @brief Export symbol to current module
 * @param processor Import/export processor
 * @param symbol_name Symbol name
 * @param value Variable value
 * @return ModuleResult indicating success/failure
 */
int export_symbol(ImportExportProcessor* processor, 
                 const char* symbol_name, 
                 variable* value) {
    if (!processor || !symbol_name || !value) {
        return MODULE_ERROR;
    }
    
    // Note: In a real implementation, we would need to track the current module
    // being processed. For now, we'll just add it to the current scope.
    // This would typically be done through a module context or processor state.
    
    variable_ref(value);
    bool result = store_set(processor->current_scope, symbol_name, value);
    
    return result ? MODULE_SUCCESS : MODULE_ERROR;
}
