/**
 * @file calculate_in_degrees.c
 * @brief Calculate in-degrees for all nodes
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency utilities subsystem
 */

#include "../../../../include/dependency.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Calculate in-degrees for all nodes
 * @param graph Dependency graph
 * @param in_degrees Output array for in-degrees
 * @return 0 on success, -1 on error
 */
int calculate_in_degrees(DependencyGraph* graph, int* in_degrees) {
    XMD_VALIDATE_PTRS(-1, graph, in_degrees);
    
    // Initialize all in-degrees to 0
    for (size_t i = 0; i < graph->node_count; i++) {
        in_degrees[i] = 0;
    }
    
    // Count incoming edges
    for (size_t i = 0; i < graph->node_count; i++) {
        DependencyNode* node = graph->nodes[i];
        if (!node) continue;
        
        for (size_t j = 0; j < node->child_count; j++) {
            // Find index of child node
            for (size_t k = 0; k < graph->node_count; k++) {
                if (graph->nodes[k] == node->children[j]) {
                    in_degrees[k]++;
                    break;
                }
            }
        }
    }
    
    return 0;
}
