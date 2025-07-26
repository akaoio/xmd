/**
 * @file dependency_build_graph.c
 * @brief Build dependency graph from module registry
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Build dependency graph from module registry
 * @param registry Module registry
 * @param graph Output dependency graph (caller must free)
 * @return ModuleResult indicating success/failure
 */
int dependency_build_graph(ModuleRegistry* registry, DependencyGraph** graph) {
    if (!registry || !graph) {
        return MODULE_ERROR;
    }
    
    *graph = dependency_graph_new();
    if (!*graph) {
        return MODULE_ERROR;
    }
    
    // Add all modules to graph
    for (size_t i = 0; i < registry->count; i++) {
        int result = dependency_graph_add_module(*graph, registry->modules[i]);
        if (result != MODULE_SUCCESS) {
            dependency_graph_free(*graph);
            *graph = NULL;
            return result;
        }
    }
    
    // Add dependency relationships (only for dependencies that exist in registry)
    for (size_t i = 0; i < registry->count; i++) {
        Module* module = registry->modules[i];
        for (size_t j = 0; j < module->dependency_count; j++) {
            // Only add dependency if the dependency module exists in registry
            Module* dep_module = module_registry_find(registry, module->dependencies[j]);
            if (dep_module) {
                int result = dependency_graph_add_dependency(*graph, 
                                                           module->name,
                                                           module->dependencies[j]);
                if (result != MODULE_SUCCESS) {
                    dependency_graph_free(*graph);
                    *graph = NULL;
                    return result;
                }
            }
            // Note: Missing dependencies will be caught by dependency_validate_all
        }
    }
    
    return MODULE_SUCCESS;
}