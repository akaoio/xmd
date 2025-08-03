/**
 * @file reset_visit_states.c
 * @brief Reset visit states for all nodes
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency utilities subsystem
 */

#include "../../../../include/dependency.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Reset visit states for all nodes
 * @param graph Dependency graph
 */
void reset_visit_states(DependencyGraph* graph) {
    XMD_ENTRY_VALIDATE_VOID(graph);
    
    for (size_t i = 0; i < graph->node_count; i++) {
        if (graph->nodes[i]) {
            graph->nodes[i]->visit_state = 0; // White (unvisited)
        }
    }
}
