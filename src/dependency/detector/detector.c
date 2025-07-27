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
