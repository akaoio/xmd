/**
 * @file reset_visit_states.c
 * @brief Reset dependency graph visit states function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/dependency.h"

/**
 * @brief Reset all node visit states  
 * @param graph Dependency graph
 */
void reset_visit_states(DependencyGraph* graph) {
    if (!graph) {
        return;
    }
    
    for (size_t i = 0; i < graph->node_count; i++) {
        graph->nodes[i]->visit_state = 0; // White (unvisited)
    }
}