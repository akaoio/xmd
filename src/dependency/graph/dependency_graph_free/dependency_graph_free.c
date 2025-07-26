/**
 * @file dependency_graph_free.c
 * @brief Free a dependency graph
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Free a dependency graph
 * @param graph Graph to free
 */
void dependency_graph_free(DependencyGraph* graph) {
    if (!graph) {
        return;
    }
    
    // Free all nodes
    for (size_t i = 0; i < graph->node_count; i++) {
        dependency_node_free(graph->nodes[i]);
    }
    free(graph->nodes);
    
    // Free load order
    for (size_t i = 0; i < graph->load_order_count; i++) {
        free(graph->load_order[i]);
    }
    free(graph->load_order);
    
    free(graph);
}