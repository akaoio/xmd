/**
 * @file dependency_check_circular_from.c
 * @brief Check circular dependencies starting from specific module
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/dependency.h"

// Forward declaration for recursive helper
static int visit_node_from_dfs(DependencyDetector* detector, DependencyNode* node, const char* start_module);

/**
 * @brief Check circular dependencies starting from specific module
 * @param detector Dependency detector
 * @param module_name Starting module name
 * @return ModuleResult indicating success or circular dependency found
 */
int dependency_check_circular_from(DependencyDetector* detector, const char* module_name) {
    if (!detector || !detector->graph || !module_name) {
        return MODULE_ERROR;
    }
    
    DependencyGraph* graph = detector->graph;
    
    // Find starting node
    DependencyNode* start_node = NULL;
    for (size_t i = 0; i < graph->node_count; i++) {
        if (strcmp(graph->nodes[i]->module->name, module_name) == 0) {
            start_node = graph->nodes[i];
            break;
        }
    }
    
    if (!start_node) {
        return MODULE_NOT_FOUND;
    }
    
    // Reset all visit states
    for (size_t i = 0; i < graph->node_count; i++) {
        graph->nodes[i]->visit_state = 0; // White (unvisited)
    }
    
    // Clear any previous cycle path
    if (detector->cycle_path) {
        for (size_t i = 0; i < detector->cycle_path_count; i++) {
            free(detector->cycle_path[i]);
        }
        free(detector->cycle_path);
        detector->cycle_path = NULL;
        detector->cycle_path_count = 0;
    }
    
    // Start DFS from the specified module
    return visit_node_from_dfs(detector, start_node, module_name);
}

/**
 * @brief DFS visit helper for cycle detection from specific start
 * @param detector Dependency detector
 * @param node Current node
 * @param start_module Starting module name (to detect cycle back to start)
 * @return ModuleResult indicating success or circular dependency found
 */
static int visit_node_from_dfs(DependencyDetector* detector, DependencyNode* node, const char* start_module) {
    node->visit_state = 1; // Gray (visiting)
    
    // Visit all children
    for (size_t i = 0; i < node->child_count; i++) {
        DependencyNode* child = node->children[i];
        
        // Check if we've circled back to the starting module
        if (strcmp(child->module->name, start_module) == 0) {
            return MODULE_CIRCULAR_DEPENDENCY;
        }
        
        if (child->visit_state == 1) { // Gray - back edge found (cycle)
            return MODULE_CIRCULAR_DEPENDENCY;
        }
        
        if (child->visit_state == 0) { // White - unvisited
            int result = visit_node_from_dfs(detector, child, start_module);
            if (result == MODULE_CIRCULAR_DEPENDENCY) {
                return MODULE_CIRCULAR_DEPENDENCY;
            }
        }
    }
    
    node->visit_state = 2; // Black (finished)
    return MODULE_SUCCESS;
}