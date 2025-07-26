/**
 * @file module_export.c
 * @brief Module export function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Export a variable from module
 * @param module Module to export from
 * @param name Variable name
 * @param value Variable value
 * @return ModuleResult indicating success/failure
 */
int module_export(Module* module, const char* name, variable* value) {
    if (!module || !name || !value) {
        return MODULE_ERROR;
    }
    
    // Add reference to the variable
    variable_ref(value);
    
    // Store in exports
    bool result = store_set(module->exports, name, value);
    return result ? MODULE_SUCCESS : MODULE_ERROR;
}