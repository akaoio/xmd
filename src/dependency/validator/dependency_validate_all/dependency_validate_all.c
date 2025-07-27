/**
 * @file dependency_validate_all.c
 * @brief Validate all dependencies in a module registry
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/dependency.h"
#include "../../../../include/module.h"

/**
 * @brief Validate all dependencies in a module registry
 * @param registry Module registry to validate
 * @return ModuleResult indicating success or validation failure
 */
int dependency_validate_all(ModuleRegistry* registry) {
    if (!registry) {
        return MODULE_ERROR;
    }
    
    // Check that all dependencies exist in the registry
    for (size_t i = 0; i < registry->count; i++) {
        Module* module = registry->modules[i];
        
        for (size_t j = 0; j < module->dependency_count; j++) {
            const char* dep_name = module->dependencies[j];
            
            // Find the dependency in the registry
            Module* dep_module = module_registry_find(registry, dep_name);
            if (!dep_module) {
                // Dependency not found
                return MODULE_NOT_FOUND;
            }
        }
    }
    
    // Build dependency graph to check for circular dependencies
    DependencyGraph* graph = NULL;
    int result = dependency_build_graph(registry, &graph);
    if (result != MODULE_SUCCESS) {
        return result;
    }
    
    // Check for circular dependencies
    DependencyDetector* detector = dependency_detector_new(graph);
    if (!detector) {
        dependency_graph_free(graph);
        return MODULE_ERROR;
    }
    
    result = dependency_check_circular(detector);
    
    dependency_detector_free(detector);
    dependency_graph_free(graph);
    
    return result;
}