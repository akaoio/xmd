/**
 * @file dependency_graph_topological_sort.c
 * @brief Perform topological sort on dependency graph
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency graph subsystem
 */

#include <stdlib.h>
#include <stdbool.h>
#include "../../../../include/dependency.h"
#include "../../../../include/dependency_graph_internal.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Perform topological sort on dependency graph
 * @param graph Dependency graph
 * @return 0 on success, -1 on error or cycle detected
 */
int dependency_graph_topological_sort(DependencyGraph* graph) {
    if (!graph) {
        return -1;
    }
    
    if (graph->node_count == 0) {
        return 0;
    }
    
    // Allocate arrays
    int* in_degrees = xmd_malloc(graph->node_count * sizeof(int));
    bool* visited = xmd_malloc(graph->node_count * sizeof(bool));
    Module** result = xmd_malloc(graph->node_count * sizeof(Module*));
    
    if (!in_degrees || !visited || !result) {
        XMD_FREE_SAFE(in_degrees);
        XMD_FREE_SAFE(visited);
        XMD_FREE_SAFE(result);
        return -1;
    }
    
    // Initialize arrays
    for (size_t i = 0; i < graph->node_count; i++) {
        visited[i] = false;
        in_degrees[i] = 0;
    }
    
    // Calculate in-degrees
    for (size_t i = 0; i < graph->node_count; i++) {
        DependencyNode* node = graph->nodes[i];
        for (size_t j = 0; j < node->child_count; j++) {
            for (size_t k = 0; k < graph->node_count; k++) {
                if (graph->nodes[k] == node->children[j]) {
                    in_degrees[k]++;
                    break;
                }
            }
        }
    }
    
    // Kahn's algorithm
    size_t result_count = 0;
    bool progress = true;
    
    while (progress && result_count < graph->node_count) {
        progress = false;
        
        // Find a node with in-degree 0
        for (size_t i = 0; i < graph->node_count; i++) {
            if (!visited[i] && in_degrees[i] == 0) {
                visited[i] = true;
                result[result_count++] = graph->nodes[i]->module;
                progress = true;
                
                // Decrease in-degree of all children
                DependencyNode* node = graph->nodes[i];
                for (size_t j = 0; j < node->child_count; j++) {
                    for (size_t k = 0; k < graph->node_count; k++) {
                        if (graph->nodes[k] == node->children[j]) {
                            in_degrees[k]--;
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    
    XMD_FREE_SAFE(in_degrees);
    XMD_FREE_SAFE(visited);
    
    if (result_count != graph->node_count) {
        // Cycle detected
        XMD_FREE_SAFE(result);
        return -1;
    }
    
    // Store sorted order in graph
    if (graph->load_order) {
        for (size_t i = 0; i < graph->load_order_count; i++) {
            XMD_FREE_SAFE(graph->load_order[i]);
        }
        XMD_FREE_SAFE(graph->load_order);
    }
    
    graph->load_order = xmd_malloc(result_count * sizeof(char*));
    for (size_t i = 0; i < result_count; i++) {
        graph->load_order[i] = xmd_strdup(result[i]->name);
    }
    graph->load_order_count = result_count;
    
    XMD_FREE_SAFE(result);
    return 0;
}
