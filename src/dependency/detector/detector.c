/**
 * @file detector.c  
 * @brief Dependency cycle detection implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/dependency.h"

/**
 * @brief Create a new dependency detector
 * @param graph Dependency graph to analyze
 * @return New dependency detector or NULL on error
 */
DependencyDetector* dependency_detector_new(DependencyGraph* graph) {
    if (!graph) {
        return NULL;
    }
    
    DependencyDetector* detector = malloc(sizeof(DependencyDetector));
    if (!detector) {
        return NULL;
    }
    
    detector->graph = graph;
    detector->cycle_path = NULL;
    detector->cycle_path_count = 0;
    detector->last_error = NULL;
    
    return detector;
}

/**
 * @brief Free a dependency detector
 * @param detector Detector to free
 */
void dependency_detector_free(DependencyDetector* detector) {
    if (!detector) {
        return;
    }
    
    // Free cycle path
    for (size_t i = 0; i < detector->cycle_path_count; i++) {
        free(detector->cycle_path[i]);
    }
    free(detector->cycle_path);
    
    free(detector->last_error);
    free(detector);
}

/**
 * @brief Clear the current cycle path
 * @param detector Dependency detector
 */
static void clear_cycle_path(DependencyDetector* detector) {
    if (!detector) {
        return;
    }
    
    for (size_t i = 0; i < detector->cycle_path_count; i++) {
        free(detector->cycle_path[i]);
    }
    free(detector->cycle_path);
    
    detector->cycle_path = NULL;
    detector->cycle_path_count = 0;
}

/**
 * @brief Add module to cycle path
 * @param detector Dependency detector
 * @param module_name Module name to add
 * @return ModuleResult indicating success/failure
 */
static int add_to_cycle_path(DependencyDetector* detector, const char* module_name) {
    if (!detector || !module_name) {
        return MODULE_ERROR;
    }
    
    char** new_path = realloc(detector->cycle_path, 
                             (detector->cycle_path_count + 1) * sizeof(char*));
    if (!new_path) {
        return MODULE_ERROR;
    }
    
    detector->cycle_path = new_path;
    detector->cycle_path[detector->cycle_path_count] = strdup(module_name);
    
    if (!detector->cycle_path[detector->cycle_path_count]) {
        return MODULE_ERROR;
    }
    
    detector->cycle_path_count++;
    return MODULE_SUCCESS;
}

/**
 * @brief Reset all node visit states  
 * @param graph Dependency graph
 */
static void reset_visit_states(DependencyGraph* graph) {
    if (!graph) {
        return;
    }
    
    for (size_t i = 0; i < graph->node_count; i++) {
        graph->nodes[i]->visit_state = 0; // White (unvisited)
    }
}

/**
 * @brief Simple DFS cycle detection using 3-coloring
 * @param detector Dependency detector
 * @param node Current node
 * @return ModuleResult indicating success or circular dependency found
 */
static int dfs_cycle_detection(DependencyDetector* detector, DependencyNode* node) {
    if (!detector || !node) {
        return MODULE_ERROR;
    }
    
    // If already fully processed (black), no cycles through this node
    if (node->visit_state == 2) {
        return MODULE_SUCCESS;
    }
    
    // If currently being processed (gray), we found a back edge = cycle!
    if (node->visit_state == 1) {
        clear_cycle_path(detector);
        add_to_cycle_path(detector, node->module->name);
        return MODULE_CIRCULAR_DEPENDENCY;
    }
    
    // Mark as gray (currently processing)
    node->visit_state = 1;
    
    // Visit all children
    for (size_t i = 0; i < node->child_count; i++) {
        DependencyNode* child = node->children[i];
        
        int result = dfs_cycle_detection(detector, child);
        if (result == MODULE_CIRCULAR_DEPENDENCY) {
            // Add current node to the cycle path
            add_to_cycle_path(detector, node->module->name);
            return result;
        }
        if (result != MODULE_SUCCESS) {
            return result;
        }
    }
    
    // Mark as black (fully processed)
    node->visit_state = 2;
    
    return MODULE_SUCCESS;
}

/**
 * @brief Check for circular dependencies
 * @param detector Dependency detector
 * @return ModuleResult indicating success or circular dependency found
 */
int dependency_check_circular(DependencyDetector* detector) {
    if (!detector || !detector->graph) {
        return MODULE_ERROR;
    }
    
    // Reset all visit states
    reset_visit_states(detector->graph);
    
    // Clear any previous cycle path
    clear_cycle_path(detector);
    
    // Check each unvisited node
    for (size_t i = 0; i < detector->graph->node_count; i++) {
        DependencyNode* node = detector->graph->nodes[i];
        
        if (node->visit_state == 0) { // White (unvisited)
            int result = dfs_cycle_detection(detector, node);
            
            if (result == MODULE_CIRCULAR_DEPENDENCY) {
                return result;
            }
            if (result != MODULE_SUCCESS) {
                return result;
            }
        }
    }
    
    return MODULE_SUCCESS;
}

/**
 * @brief Check for circular dependencies starting from a specific module
 * @param detector Dependency detector
 * @param module_name Starting module name
 * @return ModuleResult indicating success or circular dependency found
 */
int dependency_check_circular_from(DependencyDetector* detector, const char* module_name) {
    if (!detector || !detector->graph || !module_name) {
        return MODULE_ERROR;
    }
    
    // Find starting node
    DependencyNode* start_node = dependency_graph_find_node(detector->graph, module_name);
    if (!start_node) {
        return MODULE_NOT_FOUND;
    }
    
    // Reset all visit states
    reset_visit_states(detector->graph);
    
    // Clear any previous cycle path
    clear_cycle_path(detector);
    
    return dfs_cycle_detection(detector, start_node);
}

/**
 * @brief Get the cycle path if circular dependency was detected
 * @param detector Dependency detector
 * @param cycle_path Output cycle path (caller must free)
 * @param cycle_length Output cycle length
 * @return ModuleResult indicating success/failure
 */
int dependency_get_cycle_path(DependencyDetector* detector, 
                             char*** cycle_path, size_t* cycle_length) {
    if (!detector || !cycle_path || !cycle_length) {
        return MODULE_ERROR;
    }
    
    *cycle_path = NULL;
    *cycle_length = 0;
    
    if (detector->cycle_path_count == 0) {
        return MODULE_SUCCESS; // No cycle detected
    }
    
    // Allocate array for cycle path
    char** path = malloc(detector->cycle_path_count * sizeof(char*));
    if (!path) {
        return MODULE_ERROR;
    }
    
    // Copy cycle path
    for (size_t i = 0; i < detector->cycle_path_count; i++) {
        path[i] = strdup(detector->cycle_path[i]);
        if (!path[i]) {
            // Cleanup on error
            for (size_t j = 0; j < i; j++) {
                free(path[j]);
            }
            free(path);
            return MODULE_ERROR;
        }
    }
    
    *cycle_path = path;
    *cycle_length = detector->cycle_path_count;
    
    return MODULE_SUCCESS;
}

/**
 * @brief Validate all module dependencies
 * @param registry Module registry
 * @return ModuleResult indicating success or validation failure
 */
int dependency_validate_all(ModuleRegistry* registry) {
    if (!registry) {
        return MODULE_ERROR;
    }
    
    // Check that all dependencies exist
    for (size_t i = 0; i < registry->count; i++) {
        Module* module = registry->modules[i];
        
        for (size_t j = 0; j < module->dependency_count; j++) {
            const char* dep_name = module->dependencies[j];
            
            Module* dep_module = module_registry_find(registry, dep_name);
            if (!dep_module) {
                return MODULE_NOT_FOUND;
            }
        }
    }
    
    return MODULE_SUCCESS;
}