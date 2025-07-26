/**
 * @file dependency_graph_new.c
 * @brief Create a new dependency graph
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Create a new dependency graph
 * @return New dependency graph or NULL on error
 */
DependencyGraph* dependency_graph_new(void) {
    DependencyGraph* graph = malloc(sizeof(DependencyGraph));
    if (!graph) {
        return NULL;
    }
    
    graph->nodes = NULL;
    graph->node_count = 0;
    graph->node_capacity = 0;
    graph->load_order = NULL;
    graph->load_order_count = 0;
    
    return graph;
}