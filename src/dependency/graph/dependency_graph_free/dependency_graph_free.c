/**
 * @file dependency_graph_free.c
 * @brief Free a dependency graph
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency graph subsystem
 */

#include <stdlib.h>
#include "../../../../include/dependency.h"
#include "../../../utils/common/common_macros.h"

// Forward declaration
void dependency_node_free(DependencyNode* node);
/**
 * @brief Free a dependency graph
 * @param graph Graph to free
 */
void dependency_graph_free(DependencyGraph* graph) {
    XMD_ENTRY_VALIDATE_VOID(graph);
    
    // Free all nodes
    if (graph->nodes) {
        for (size_t i = 0; i < graph->node_count; i++) {
            dependency_node_free(graph->nodes[i]);
        }
        XMD_FREE_SAFE(graph->nodes);
    }
    
    // Free load order
    if (graph->load_order) {
        for (size_t i = 0; i < graph->load_order_count; i++) {
            XMD_FREE_SAFE(graph->load_order[i]);
        }
        XMD_FREE_SAFE(graph->load_order);
    }
    
    XMD_FREE_SAFE(graph);
}
