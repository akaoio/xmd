/**
 * @file module_free.c
 * @brief Module destruction function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Free a module
 * @param module Module to free
 */
void module_free(Module* module) {
    if (!module) {
        return;
    }
    
    free(module->name);
    free(module->path);
    free(module->content);
    
    if (module->exports) {
        store_destroy(module->exports);
    }
    
    if (module->dependencies) {
        for (size_t i = 0; i < module->dependency_count; i++) {
            free(module->dependencies[i]);
        }
        free(module->dependencies);
    }
    
    free(module);
}