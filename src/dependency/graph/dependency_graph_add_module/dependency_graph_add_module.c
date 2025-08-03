/**
 * @file dependency_graph_add_module.c
 * @brief Add module to dependency graph
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency graph subsystem
 */

#include "../../../../include/dependency.h"
#include "../../../../include/utils.h"
#include "../../../../src/utils/common/common_macros.h"
/**
 * @brief Add module to dependency graph
 * @param graph Dependency graph
 * @param module Module to add
 * @return 0 on success, -1 on error
 */
int dependency_graph_add_module(DependencyGraph* graph, Module* module) {
    XMD_VALIDATE_PTRS(-1, graph, module);
    
    // Check if module already exists
    if (dependency_graph_find_node(graph, module->name)) {
        return 0; // Already exists
    }
    
    // Expand capacity if needed
    if (graph->node_count >= graph->node_capacity) {
        size_t new_capacity = graph->node_capacity == 0 ? 8 : graph->node_capacity * 2;
        DependencyNode** new_nodes = xmd_realloc(graph->nodes, 
                                                  new_capacity * sizeof(DependencyNode*));
        if (!new_nodes) {
            XMD_ERROR_RETURN(-1, "Failed to reallocate graph nodes array");
        }
        graph->nodes = new_nodes;
        graph->node_capacity = new_capacity;
    }
    
    // Create and add node
    DependencyNode* node = dependency_node_new(module);
    if (!node) {
        XMD_ERROR_RETURN(-1, "Failed to create dependency node for module %s", module->name ? module->name : "unknown");
    }
    
    graph->nodes[graph->node_count++] = node;
    return 0;
}
