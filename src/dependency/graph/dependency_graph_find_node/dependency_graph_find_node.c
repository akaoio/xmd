/**
 * @file dependency_graph_find_node.c
 * @brief Find node by module name
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Find node by module name
 * @param graph Dependency graph
 * @param module_name Module name
 * @return Dependency node or NULL if not found
 */
DependencyNode* dependency_graph_find_node(DependencyGraph* graph, 
                                          const char* module_name) {
    if (!graph || !module_name) {
        return NULL;
    }
    
    for (size_t i = 0; i < graph->node_count; i++) {
        if (strcmp(graph->nodes[i]->module->name, module_name) == 0) {
            return graph->nodes[i];
        }
    }
    
    return NULL;
}