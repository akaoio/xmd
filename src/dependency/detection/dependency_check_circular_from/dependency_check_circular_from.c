/**
 * @file dependency_check_circular_from.c
 * @brief DFS-based circular dependency check from specific node
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency detection subsystem
 */

#include "../../../../include/dependency.h"
#include "../../../../utils/common/common_macros.h"

// Forward declaration
DependencyNode* dependency_graph_find_node(DependencyGraph* graph, const char* module_name);
/**
 * @brief DFS-based circular dependency check from specific node
 * @param detector Dependency detector
 * @param module_name Starting module name
 * @return 1 if cycle found, 0 if no cycle, -1 on error
 */
int dependency_check_circular_from(DependencyDetector* detector, const char* module_name) {
    XMD_VALIDATE_PTRS(-1, detector, module_name);
    
    DependencyNode* node = dependency_graph_find_node(detector->graph, module_name);
    if (!node) {
        return -1;
    }
    
    if (node->visit_state == 1) {
        // Gray node - we've found a back edge (cycle)
        return 1;
    }
    
    if (node->visit_state == 2) {
        // Black node - already processed
        return 0;
    }
    
    // Mark as gray (currently being processed)
    node->visit_state = 1;
    
    // Check all children
    for (size_t i = 0; i < node->child_count; i++) {
        if (node->children[i] && node->children[i]->module) {
            int result = dependency_check_circular_from(detector, node->children[i]->module->name);
            if (result != 0) {
                return result; // Cycle found or error
            }
        }
    }
    
    // Mark as black (completely processed)
    node->visit_state = 2;
    return 0;
}
