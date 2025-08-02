/**
 * @file dependency_graph_new.c
 * @brief Create a new dependency graph
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency graph subsystem
 */

#include "../../../../include/dependency.h"
#include "../../../../include/utils.h"
/**
 * @brief Create a new dependency graph
 * @return New dependency graph or NULL on error
 */
DependencyGraph* dependency_graph_new(void) {
    DependencyGraph* graph = xmd_malloc(sizeof(DependencyGraph));
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
