/**
 * @file module_registry_find.c
 * @brief Module registry finder function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Find module by name
 * @param registry Module registry
 * @param name Module name
 * @return Module or NULL if not found
 */
Module* module_registry_find(ModuleRegistry* registry, const char* name) {
    if (!registry || !name) {
        return NULL;
    }
    
    for (size_t i = 0; i < registry->count; i++) {
        if (strcmp(registry->modules[i]->name, name) == 0) {
            return registry->modules[i];
        }
    }
    
    return NULL;
}