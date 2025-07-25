/**
 * @file module.c
 * @brief Module core implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "../../../include/module.h"

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

/**
 * @brief Load module content from file
 * @param module Module to load
 * @return ModuleResult indicating success/failure
 */
int module_load_content(Module* module) {
    if (!module) {
        return MODULE_ERROR;
    }
    
    if (module->loaded) {
        return MODULE_ALREADY_LOADED;
    }
    
    FILE* file = fopen(module->path, "r");
    if (!file) {
        return MODULE_NOT_FOUND;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(file);
        return MODULE_ERROR;
    }
    
    // Allocate buffer and read content
    module->content = malloc(file_size + 1);
    if (!module->content) {
        fclose(file);
        return MODULE_ERROR;
    }
    
    size_t bytes_read = fread(module->content, 1, file_size, file);
    module->content[bytes_read] = '\0';
    
    fclose(file);
    module->loaded = true;
    
    return MODULE_SUCCESS;
}

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

/**
 * @brief Get exported variable from module
 * @param module Module to get from
 * @param name Variable name
 * @return Variable or NULL if not found
 */
variable* module_get_export(Module* module, const char* name) {
    if (!module || !name) {
        return NULL;
    }
    
    return store_get(module->exports, name);
}

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

/**
 * @brief Add search path to registry
 * @param registry Module registry
 * @param path Search path to add
 * @return ModuleResult indicating success/failure
 */
int module_registry_add_search_path(ModuleRegistry* registry, const char* path) {
    if (!registry || !path) {
        return MODULE_ERROR;
    }
    
    // Reallocate search paths array
    char** new_paths = realloc(registry->search_paths, 
                              (registry->search_path_count + 1) * sizeof(char*));
    if (!new_paths) {
        return MODULE_ERROR;
    }
    
    registry->search_paths = new_paths;
    registry->search_paths[registry->search_path_count] = strdup(path);
    
    if (!registry->search_paths[registry->search_path_count]) {
        return MODULE_ERROR;
    }
    
    registry->search_path_count++;
    return MODULE_SUCCESS;
}

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

/**
 * @brief Check if file exists
 * @param path File path to check
 * @return true if file exists, false otherwise
 */
static bool file_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

/**
 * @brief Resolve module path
 * @param registry Module registry
 * @param name Module name or relative path
 * @param resolved_path Buffer to store resolved path (caller must free)
 * @return ModuleResult indicating success/failure
 */
int module_resolve_path(ModuleRegistry* registry, const char* name, char** resolved_path) {
    if (!registry || !name || !resolved_path) {
        return MODULE_ERROR;
    }
    
    *resolved_path = NULL;
    
    // If it's an absolute path, use it directly
    if (name[0] == '/') {
        if (file_exists(name)) {
            *resolved_path = strdup(name);
            return *resolved_path ? MODULE_SUCCESS : MODULE_ERROR;
        }
        return MODULE_NOT_FOUND;
    }
    
    // Try to find in search paths
    for (size_t i = 0; i < registry->search_path_count; i++) {
        size_t path_len = strlen(registry->search_paths[i]) + strlen(name) + 10;
        char* candidate = malloc(path_len);
        if (!candidate) {
            return MODULE_ERROR;
        }
        
        // Try with .xmd extension
        snprintf(candidate, path_len, "%s/%s.xmd", registry->search_paths[i], name);
        if (file_exists(candidate)) {
            *resolved_path = candidate;
            return MODULE_SUCCESS;
        }
        
        // Try without extension
        snprintf(candidate, path_len, "%s/%s", registry->search_paths[i], name);
        if (file_exists(candidate)) {
            *resolved_path = candidate;
            return MODULE_SUCCESS;
        }
        
        free(candidate);
    }
    
    // If not found in search paths and it's a relative name, assume it's a path
    if (file_exists(name)) {
        *resolved_path = strdup(name);
        return *resolved_path ? MODULE_SUCCESS : MODULE_ERROR;
    }
    
    return MODULE_NOT_FOUND;
}