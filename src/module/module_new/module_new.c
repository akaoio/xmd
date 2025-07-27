/**
 * @file module_new.c
 * @brief Module creation function
 * @author XMD Team
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/module_internal.h"

/**
 * @brief Create a new module
 * @param name Module name
 * @param path Module file path
 * @return New module or NULL on error
 */
Module* module_new(const char* name, const char* path) {
    if (!name || !path) {
        return NULL;
    }
    
    Module* module = malloc(sizeof(Module));
    if (!module) {
        return NULL;
    }
    
    module->name = strdup(name);
    module->path = strdup(path);
    module->content = NULL;
    module->exports = store_create();
    module->dependencies = NULL;
    module->dependency_count = 0;
    module->loaded = false;
    module->loading = false;
    
    if (!module->name || !module->path || !module->exports) {
        module_free(module);
        return NULL;
    }
    
    return module;
}
