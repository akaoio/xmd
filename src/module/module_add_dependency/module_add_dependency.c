/**
 * @file module_add_dependency.c
 * @brief Module dependency addition function
 * @author XMD Team
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/module_internal.h"

/**
 * @brief Add dependency to module
 * @param module Module to update
 * @param dependency_name Name of dependency
 * @return ModuleResult indicating success/failure
 */
int module_add_dependency(Module* module, const char* dependency_name) {
    if (!module || !dependency_name) {
        return MODULE_ERROR;
    }
    
    // Check if dependency already exists
    for (size_t i = 0; i < module->dependency_count; i++) {
        if (strcmp(module->dependencies[i], dependency_name) == 0) {
            return MODULE_SUCCESS; // Already exists
        }
    }
    
    // Reallocate dependencies array
    char** new_dependencies = realloc(module->dependencies, 
                                     (module->dependency_count + 1) * sizeof(char*));
    if (!new_dependencies) {
        return MODULE_ERROR;
    }
    
    module->dependencies = new_dependencies;
    module->dependencies[module->dependency_count] = strdup(dependency_name);
    
    if (!module->dependencies[module->dependency_count]) {
        return MODULE_ERROR;
    }
    
    module->dependency_count++;
    return MODULE_SUCCESS;
}
