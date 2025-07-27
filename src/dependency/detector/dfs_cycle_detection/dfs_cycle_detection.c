/**
 * @file dfs_cycle_detection.c
 * @brief DFS-based cycle detection for dependency graph
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/dependency.h"

/**
 * @brief Perform DFS cycle detection from a specific node
 * @param detector Dependency detector
 * @param node Starting node for DFS
 * @return MODULE_SUCCESS if no cycle, MODULE_CIRCULAR_DEPENDENCY if cycle found
 */
int dfs_cycle_detection(DependencyDetector* detector, DependencyNode* node) {
    if (!detector || !node) {
        return MODULE_ERROR;
    }
    
    // Mark as gray (visiting)
    node->visit_state = 1;
    
    // Check all children
    for (size_t i = 0; i < node->child_count; i++) {
        DependencyNode* child = node->children[i];
        
        if (!child) {
            continue;
        }
        
        if (child->visit_state == 1) {
            // Found gray node - cycle detected
            return MODULE_CIRCULAR_DEPENDENCY;
        }
        
        if (child->visit_state == 0) {
            // White node - continue DFS
            int result = dfs_cycle_detection(detector, child);
            if (result != MODULE_SUCCESS) {
                return result;
            }
        }
    }
    
    // Mark as black (visited)
    node->visit_state = 2;
    
    return MODULE_SUCCESS;
}