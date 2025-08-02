/**
 * @file dependency_check_circular.c
 * @brief Check for circular dependencies in graph
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency detection subsystem
 */

#include "../../../../include/dependency.h"

// Forward declaration
void reset_visit_states(DependencyGraph* graph);
int dependency_check_circular_from(DependencyDetector* detector, const char* module_name);
/**
 * @brief Check for circular dependencies in graph
 * @param detector Dependency detector
 * @return 1 if circular dependencies found, 0 otherwise, -1 on error
 */
int dependency_check_circular(DependencyDetector* detector) {
    if (!detector || !detector->graph) {
        return -1;
    }
    
    reset_visit_states(detector->graph);
    
    // Check from each unvisited node
    for (size_t i = 0; i < detector->graph->node_count; i++) {
        if (detector->graph->nodes[i] && detector->graph->nodes[i]->visit_state == 0) {
            int result = dependency_check_circular_from(detector, detector->graph->nodes[i]->module->name);
            if (result != 0) {
                return result;
            }
        }
    }
    
    return 0; // No cycles found
}
