/**
 * @file module.h
 * @brief Module system for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef MODULE_H
#define MODULE_H

#include <stddef.h>
#include "store.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Module structure
 */
typedef struct xmd_module {
    char* name;                 /**< Module name */
    char* path;                 /**< Module file path */
    char* content;              /**< Module content */
    store* exports;             /**< Exported variables */
    char** dependencies;        /**< Module dependencies */
    size_t dependency_count;    /**< Number of dependencies */
    bool loaded;                /**< Whether module is loaded */
    bool loading;               /**< Loading flag for cycle detection */
} Module;

/**
 * @brief Module registry
 */
typedef struct module_registry {
    Module** modules;           /**< Array of modules */
    size_t count;               /**< Number of modules */
    size_t capacity;            /**< Registry capacity */
    char** search_paths;        /**< Module search paths */
    size_t search_path_count;   /**< Number of search paths */
} ModuleRegistry;

/**
 * @brief Module result codes
 */
typedef enum {
    MODULE_SUCCESS = 0,             /**< Operation successful */
    MODULE_ERROR = -1,              /**< General error */
    MODULE_NOT_FOUND = -2,          /**< Module not found */
    MODULE_CIRCULAR_DEPENDENCY = -3, /**< Circular dependency detected */
    MODULE_ALREADY_LOADED = -4,     /**< Module already loaded */
    MODULE_INVALID_PATH = -5        /**< Invalid module path */
} ModuleResult;

/**
 * @brief Create a new module
 * @param name Module name
 * @param path Module file path
 * @return New module or NULL on error
 */
Module* module_new(const char* name, const char* path);

/**
 * @brief Free a module
 * @param module Module to free
 */
void module_free(Module* module);

/**
 * @brief Load module content from file
 * @param module Module to load
 * @return ModuleResult indicating success/failure
 */
int module_load_content(Module* module);

/**
 * @brief Add dependency to module
 * @param module Module to update
 * @param dependency_name Name of dependency
 * @return ModuleResult indicating success/failure
 */
int module_add_dependency(Module* module, const char* dependency_name);

/**
 * @brief Export a variable from module
 * @param module Module to export from
 * @param name Variable name
 * @param value Variable value
 * @return ModuleResult indicating success/failure
 */
int module_export(Module* module, const char* name, variable* value);

/**
 * @brief Get exported variable from module
 * @param module Module to get from
 * @param name Variable name
 * @return Variable or NULL if not found
 */
variable* module_get_export(Module* module, const char* name);

/**
 * @brief Create a new module registry
 * @return New module registry or NULL on error
 */
ModuleRegistry* module_registry_new(void);

/**
 * @brief Free a module registry
 * @param registry Registry to free
 */
void module_registry_free(ModuleRegistry* registry);

/**
 * @brief Add search path to registry
 * @param registry Module registry
 * @param path Search path to add
 * @return ModuleResult indicating success/failure
 */
int module_registry_add_search_path(ModuleRegistry* registry, const char* path);

/**
 * @brief Register a module in the registry
 * @param registry Module registry
 * @param module Module to register
 * @return ModuleResult indicating success/failure
 */
int module_registry_register(ModuleRegistry* registry, Module* module);

/**
 * @brief Find module by name
 * @param registry Module registry
 * @param name Module name
 * @return Module or NULL if not found
 */
Module* module_registry_find(ModuleRegistry* registry, const char* name);

/**
 * @brief Load module by name
 * @param registry Module registry
 * @param name Module name
 * @return ModuleResult indicating success/failure
 */
int module_registry_load(ModuleRegistry* registry, const char* name);

/**
 * @brief Resolve module path
 * @param registry Module registry
 * @param name Module name or relative path
 * @param resolved_path Buffer to store resolved path (caller must free)
 * @return ModuleResult indicating success/failure
 */
int module_resolve_path(ModuleRegistry* registry, const char* name, char** resolved_path);

#ifdef __cplusplus
}
#endif

#endif /* MODULE_H */