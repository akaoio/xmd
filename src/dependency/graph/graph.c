/**
 * @file graph.c
 * @brief Dependency graph implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/dependency.h"

/**
 * @brief Create a new dependency node
 * @param module Module for this node
 * @return New dependency node or NULL on error
 */
DependencyNode* dependency_node_new(Module* module) {
    if (!module) {
        return NULL;
    }
    
    DependencyNode* node = malloc(sizeof(DependencyNode));
    if (!node) {
        return NULL;
    }
    
    node->module = module;
    node->children = NULL;
    node->child_count = 0;
    node->child_capacity = 0;
    node->visit_state = 0; // White (unvisited)
    
    return node;
}

/**
 * @brief Free a dependency node
 * @param node Node to free
 */
void dependency_node_free(DependencyNode* node) {
    if (!node) {
        return;
    }
    
    // Note: We don't free the module itself as it's owned by the registry
    free(node->children);
    free(node);
}

/**
 * @brief Add dependency to node
 * @param node Parent node
 * @param dependency_node Child dependency node
 * @return ModuleResult indicating success/failure
 */
int dependency_node_add_child(DependencyNode* node, DependencyNode* dependency_node) {
    if (!node || !dependency_node) {
        return MODULE_ERROR;
    }
    
    // Check if we need to expand capacity
    if (node->child_count >= node->child_capacity) {
        size_t new_capacity = node->child_capacity == 0 ? 4 : node->child_capacity * 2;
        DependencyNode** new_children = realloc(node->children, 
                                               new_capacity * sizeof(DependencyNode*));
        if (!new_children) {
            return MODULE_ERROR;
        }
        
        node->children = new_children;
        node->child_capacity = new_capacity;
    }
    
    node->children[node->child_count] = dependency_node;
    node->child_count++;
    
    return MODULE_SUCCESS;
}

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

/**
 * @brief Calculate in-degree for each node
 * @param graph Dependency graph
 * @param in_degree Output array for in-degrees
 * @return ModuleResult indicating success/failure
 */
static int calculate_in_degrees(DependencyGraph* graph, size_t* in_degree) {
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

/**
 * @brief Build dependency graph from module registry
 * @param registry Module registry
 * @param graph Output dependency graph (caller must free)
 * @return ModuleResult indicating success/failure
 */
int dependency_build_graph(ModuleRegistry* registry, DependencyGraph** graph) {
    if (!registry || !graph) {
        return MODULE_ERROR;
    }
    
    *graph = dependency_graph_new();
    if (!*graph) {
        return MODULE_ERROR;
    }
    
    // Add all modules to graph
    for (size_t i = 0; i < registry->count; i++) {
        int result = dependency_graph_add_module(*graph, registry->modules[i]);
        if (result != MODULE_SUCCESS) {
            dependency_graph_free(*graph);
            *graph = NULL;
            return result;
        }
    }
    
    // Add dependency relationships (only for dependencies that exist in registry)
    for (size_t i = 0; i < registry->count; i++) {
        Module* module = registry->modules[i];
        for (size_t j = 0; j < module->dependency_count; j++) {
            // Only add dependency if the dependency module exists in registry
            Module* dep_module = module_registry_find(registry, module->dependencies[j]);
            if (dep_module) {
                int result = dependency_graph_add_dependency(*graph, 
                                                           module->name,
                                                           module->dependencies[j]);
                if (result != MODULE_SUCCESS) {
                    dependency_graph_free(*graph);
                    *graph = NULL;
                    return result;
                }
            }
            // Note: Missing dependencies will be caught by dependency_validate_all
        }
    }
    
    return MODULE_SUCCESS;
}
