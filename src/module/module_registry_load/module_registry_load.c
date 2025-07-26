/**
 * @file module_registry_load.c
 * @brief Module registry loader function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Load module by name
 * @param registry Module registry
 * @param name Module name
 * @return ModuleResult indicating success/failure
 */
int module_registry_load(ModuleRegistry* registry, const char* name) {
    if (!registry || !name) {
        return MODULE_ERROR;
    }
    
    Module* module = module_registry_find(registry, name);
    if (!module) {
        return MODULE_NOT_FOUND;
    }
    
    return module_load_content(module);
}