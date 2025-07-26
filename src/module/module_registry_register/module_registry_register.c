/**
 * @file module_registry_register.c
 * @brief Module registry registration function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Register a module in the registry
 * @param registry Module registry
 * @param module Module to register
 * @return ModuleResult indicating success/failure
 */
int module_registry_register(ModuleRegistry* registry, Module* module) {
    if (!registry || !module) {
        return MODULE_ERROR;
    }
    
    // Check if module already exists
    for (size_t i = 0; i < registry->count; i++) {
        if (strcmp(registry->modules[i]->name, module->name) == 0) {
            return MODULE_ALREADY_LOADED;
        }
    }
    
    // Expand capacity if needed
    if (registry->count >= registry->capacity) {
        size_t new_capacity = registry->capacity * 2;
        Module** new_modules = realloc(registry->modules, 
                                      new_capacity * sizeof(Module*));
        if (!new_modules) {
            return MODULE_ERROR;
        }
        
        registry->modules = new_modules;
        registry->capacity = new_capacity;
    }
    
    registry->modules[registry->count] = module;
    registry->count++;
    
    return MODULE_SUCCESS;
}