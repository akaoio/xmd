/**
 * @file dependency_graph_topological_sort.c
 * @brief Generate topological sort order using Kahn's algorithm
 * @author XMD Team
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Generate topological sort order using Kahn's algorithm
 * @param graph Dependency graph
 * @return ModuleResult indicating success/failure
 */
int dependency_graph_topological_sort(DependencyGraph* graph) {
    if (!graph) {
        return MODULE_ERROR;
    }
    
    // Free existing load order
    for (size_t i = 0; i < graph->load_order_count; i++) {
        free(graph->load_order[i]);
    }
    free(graph->load_order);
    graph->load_order = NULL;
    graph->load_order_count = 0;
    
    if (graph->node_count == 0) {
        return MODULE_SUCCESS; // Empty graph
    }
    
    // Calculate in-degrees
    size_t* in_degree = malloc(graph->node_count * sizeof(size_t));
    if (!in_degree) {
        return MODULE_ERROR;
    }
    
    int result = calculate_in_degrees(graph, in_degree);
    if (result != MODULE_SUCCESS) {
        free(in_degree);
        return result;
    }
    
    // Create queue for nodes with in-degree 0
    size_t* queue = malloc(graph->node_count * sizeof(size_t));
    if (!queue) {
        free(in_degree);
        return MODULE_ERROR;
    }
    
    size_t queue_start = 0, queue_end = 0;
    
    // Add all nodes with in-degree 0 to queue
    for (size_t i = 0; i < graph->node_count; i++) {
        if (in_degree[i] == 0) {
            queue[queue_end++] = i;
        }
    }
    
    // Initialize result array
    graph->load_order = malloc(graph->node_count * sizeof(char*));
    if (!graph->load_order) {
        free(in_degree);
        free(queue);
        return MODULE_ERROR;
    }
    
    graph->load_order_count = 0;
    
    // Process queue
    while (queue_start < queue_end) {
        size_t node_idx = queue[queue_start++];
        DependencyNode* node = graph->nodes[node_idx];
        
        // Add to result
        graph->load_order[graph->load_order_count] = strdup(node->module->name);
        if (!graph->load_order[graph->load_order_count]) {
            // Cleanup on error
            for (size_t i = 0; i < graph->load_order_count; i++) {
                free(graph->load_order[i]);
            }
            free(graph->load_order);
            free(in_degree);
            free(queue);
            return MODULE_ERROR;
        }
        graph->load_order_count++;
        
        // Reduce in-degree of all children
        for (size_t i = 0; i < node->child_count; i++) {
            // Find child index
            for (size_t j = 0; j < graph->node_count; j++) {
                if (graph->nodes[j] == node->children[i]) {
                    in_degree[j]--;
                    if (in_degree[j] == 0) {
                        queue[queue_end++] = j;
                    }
                    break;
                }
            }
        }
    }
    
    free(in_degree);
    free(queue);
    
    // Check if all nodes were processed (no cycles)
    if (graph->load_order_count != graph->node_count) {
        for (size_t i = 0; i < graph->load_order_count; i++) {
            free(graph->load_order[i]);
        }
        free(graph->load_order);
        graph->load_order = NULL;
        graph->load_order_count = 0;
        return MODULE_CIRCULAR_DEPENDENCY;
    }
    
    return MODULE_SUCCESS;
}
