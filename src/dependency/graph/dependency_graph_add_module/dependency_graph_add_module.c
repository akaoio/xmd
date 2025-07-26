/**
 * @file dependency_graph_add_module.c
 * @brief Add module to dependency graph
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Add module to dependency graph
 * @param graph Dependency graph
 * @param module Module to add
 * @return ModuleResult indicating success/failure
 */
int dependency_graph_add_module(DependencyGraph* graph, Module* module) {
    if (!graph || !module) {
        return MODULE_ERROR;
    }
    
    // Check if module already exists
    for (size_t i = 0; i < graph->node_count; i++) {
        if (strcmp(graph->nodes[i]->module->name, module->name) == 0) {
            return MODULE_ALREADY_LOADED;
        }
    }
    
    // Expand capacity if needed
    if (graph->node_count >= graph->node_capacity) {
        size_t new_capacity = graph->node_capacity == 0 ? 8 : graph->node_capacity * 2;
        DependencyNode** new_nodes = realloc(graph->nodes, 
                                            new_capacity * sizeof(DependencyNode*));
        if (!new_nodes) {
            return MODULE_ERROR;
        }
        
        graph->nodes = new_nodes;
        graph->node_capacity = new_capacity;
    }
    
    // Create node for module
    DependencyNode* node = dependency_node_new(module);
    if (!node) {
        return MODULE_ERROR;
    }
    
    graph->nodes[graph->node_count] = node;
    graph->node_count++;
    
    return MODULE_SUCCESS;
}