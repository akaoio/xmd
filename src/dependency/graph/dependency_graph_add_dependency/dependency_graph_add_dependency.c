/**
 * @file dependency_graph_add_dependency.c
 * @brief Add dependency relationship to graph
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Add dependency relationship to graph
 * @param graph Dependency graph
 * @param module_name Module name
 * @param dependency_name Dependency name
 * @return ModuleResult indicating success/failure
 */
int dependency_graph_add_dependency(DependencyGraph* graph, 
                                   const char* module_name,
                                   const char* dependency_name) {
    if (!graph || !module_name || !dependency_name) {
        return MODULE_ERROR;
    }
    
    // Find dependency and dependent nodes
    // module_name depends on dependency_name
    // So dependency_name must come before module_name in the sort order
    // This means dependency_name -> module_name (dependency points to dependent)
    DependencyNode* dependency_node = dependency_graph_find_node(graph, dependency_name);
    if (!dependency_node) {
        return MODULE_NOT_FOUND;
    }
    
    DependencyNode* dependent_node = dependency_graph_find_node(graph, module_name);
    if (!dependent_node) {
        return MODULE_NOT_FOUND;
    }
    
    return dependency_node_add_child(dependency_node, dependent_node);
}