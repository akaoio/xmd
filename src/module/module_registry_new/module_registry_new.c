/**
 * @file module_registry_new.c
 * @brief Module registry creation function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Create a new module registry
 * @return New module registry or NULL on error
 */
ModuleRegistry* module_registry_new(void) {
    ModuleRegistry* registry = malloc(sizeof(ModuleRegistry));
    if (!registry) {
        return NULL;
    }
    
    registry->modules = malloc(16 * sizeof(Module*));
    if (!registry->modules) {
        free(registry);
        return NULL;
    }
    
    registry->count = 0;
    registry->capacity = 16;
    registry->search_paths = NULL;
    registry->search_path_count = 0;
    
    return registry;
}