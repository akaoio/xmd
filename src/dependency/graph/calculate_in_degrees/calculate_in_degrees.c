/**
 * @file calculate_in_degrees.c
 * @brief Calculate in-degree for each node
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Calculate in-degree for each node
 * @param graph Dependency graph
 * @param in_degree Output array for in-degrees
 * @return ModuleResult indicating success/failure
 */
int calculate_in_degrees(DependencyGraph* graph, size_t* in_degree) {
    if (!graph || !in_degree) {
        return MODULE_ERROR;
    }
    
    // Initialize all in-degrees to 0
    for (size_t i = 0; i < graph->node_count; i++) {
        in_degree[i] = 0;
    }
    
    // Count incoming edges for each node
    for (size_t i = 0; i < graph->node_count; i++) {
        DependencyNode* node = graph->nodes[i];
        for (size_t j = 0; j < node->child_count; j++) {
            // Find the index of the child node
            for (size_t k = 0; k < graph->node_count; k++) {
                if (graph->nodes[k] == node->children[j]) {
                    in_degree[k]++;
                    break;
                }
            }
        }
    }
    
    return MODULE_SUCCESS;
}