/**
 * @file dependency_check_circular.c
 * @brief Check for circular dependencies
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/dependency.h"

// Forward declaration for recursive helper
static int visit_node_dfs(DependencyDetector* detector, DependencyNode* node, size_t node_index);

/**
 * @brief Check for circular dependencies
 * @param detector Dependency detector
 * @return ModuleResult indicating success or circular dependency found
 */
int dependency_check_circular(DependencyDetector* detector) {
    if (!detector || !detector->graph) {
        return MODULE_ERROR;
    }
    
    DependencyGraph* graph = detector->graph;
    
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
    
    // Visit all nodes using DFS
    for (size_t i = 0; i < graph->node_count; i++) {
        if (graph->nodes[i]->visit_state == 0) { // White (unvisited)
            int result = visit_node_dfs(detector, graph->nodes[i], i);
            if (result == MODULE_CIRCULAR_DEPENDENCY) {
                return MODULE_CIRCULAR_DEPENDENCY;
            }
        }
    }
    
    return MODULE_SUCCESS;
}

/**
 * @brief DFS visit helper for cycle detection
 * @param detector Dependency detector
 * @param node Current node
 * @param node_index Index of current node
 * @return ModuleResult indicating success or circular dependency found
 */
static int visit_node_dfs(DependencyDetector* detector, DependencyNode* node, size_t node_index) {
    node->visit_state = 1; // Gray (visiting)
    
    // Visit all children
    for (size_t i = 0; i < node->child_count; i++) {
        DependencyNode* child = node->children[i];
        
        if (child->visit_state == 1) { // Gray - back edge found (cycle)
            return MODULE_CIRCULAR_DEPENDENCY;
        }
        
        if (child->visit_state == 0) { // White - unvisited
            // Find child index for recursive call
            size_t child_index = 0;
            for (size_t j = 0; j < detector->graph->node_count; j++) {
                if (detector->graph->nodes[j] == child) {
                    child_index = j;
                    break;
                }
            }
            
            int result = visit_node_dfs(detector, child, child_index);
            if (result == MODULE_CIRCULAR_DEPENDENCY) {
                return MODULE_CIRCULAR_DEPENDENCY;
            }
        }
    }
    
    node->visit_state = 2; // Black (finished)
    return MODULE_SUCCESS;
}