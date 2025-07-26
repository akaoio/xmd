/**
 * @file module_registry_free.c
 * @brief Module registry destruction function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Free a module registry
 * @param registry Registry to free
 */
void module_registry_free(ModuleRegistry* registry) {
    if (!registry) {
        return;
    }
    
    // Free all modules
    for (size_t i = 0; i < registry->count; i++) {
        module_free(registry->modules[i]);
    }
    free(registry->modules);
    
    // Free search paths
    for (size_t i = 0; i < registry->search_path_count; i++) {
        free(registry->search_paths[i]);
    }
    free(registry->search_paths);
    
    free(registry);
}