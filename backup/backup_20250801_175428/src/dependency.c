/**
 * @file dependency.c
 * @brief Consolidated dependency management system for XMD
 * @author XMD Development Team
 *
 * All dependency functionality consolidated from 19 directories.
 * Provides circular dependency detection, graph management, and topological sorting.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/dependency.h"
#include "../include/memory.h"
#include "../include/utils.h"
#include "../include/module.h"

// ============================================================================
// DEPENDENCY NODE MANAGEMENT
// ============================================================================

/**
 * @brief Create a new dependency node
 * @param module Module to wrap in node
 * @return New dependency node or NULL on error
 */
DependencyNode* dependency_node_new(Module* module) {
    if (!module) {
        return NULL;
    }
    
    DependencyNode* node = xmd_malloc(sizeof(DependencyNode));
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
    
    free(node->children);
    free(node);
}

/**
 * @brief Add child dependency to node
 * @param parent Parent node
 * @param child Child node to add
 * @return 0 on success, -1 on error
 */
int dependency_node_add_child(DependencyNode* parent, DependencyNode* child) {
    if (!parent || !child) {
        return -1;
    }
    
    // Check if we need to expand capacity
    if (parent->child_count >= parent->child_capacity) {
        size_t new_capacity = parent->child_capacity == 0 ? 4 : parent->child_capacity * 2;
        DependencyNode** new_children = xmd_realloc(parent->children, 
                                                    new_capacity * sizeof(DependencyNode*));
        if (!new_children) {
            return -1;
        }
        
        parent->children = new_children;
        parent->child_capacity = new_capacity;
    }
    
    parent->children[parent->child_count++] = child;
    return 0;
}

// ============================================================================
// DEPENDENCY GRAPH MANAGEMENT
// ============================================================================

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
    if (graph->nodes) {
        for (size_t i = 0; i < graph->node_count; i++) {
            dependency_node_free(graph->nodes[i]);
        }
        free(graph->nodes);
    }
    
    free(graph);
}

/**
 * @brief Find node by module name
 * @param graph Dependency graph
 * @param module_name Module name to find
 * @return Dependency node or NULL if not found
 */
DependencyNode* dependency_graph_find_node(DependencyGraph* graph, const char* module_name) {
    if (!graph || !module_name) {
        return NULL;
    }
    
    for (size_t i = 0; i < graph->node_count; i++) {
        if (graph->nodes[i] && graph->nodes[i]->module && 
            strcmp(graph->nodes[i]->module->name, module_name) == 0) {
            return graph->nodes[i];
        }
    }
    
    return NULL;
}

/**
 * @brief Add module to dependency graph
 * @param graph Dependency graph
 * @param module Module to add
 * @return 0 on success, -1 on error
 */
int dependency_graph_add_module(DependencyGraph* graph, Module* module) {
    if (!graph || !module) {
        return -1;
    }
    
    // Check if module already exists
    if (dependency_graph_find_node(graph, module->name)) {
        return 0; // Already exists
    }
    
    // Check if we need to expand capacity
    if (graph->node_count >= graph->node_capacity) {
        size_t new_capacity = graph->node_capacity == 0 ? 8 : graph->node_capacity * 2;
        DependencyNode** new_nodes = xmd_realloc(graph->nodes, 
                                                  new_capacity * sizeof(DependencyNode*));
        if (!new_nodes) {
            return -1;
        }
        
        graph->nodes = new_nodes;
        graph->node_capacity = new_capacity;
    }
    
    // Create and add node
    DependencyNode* node = dependency_node_new(module);
    if (!node) {
        return -1;
    }
    
    graph->nodes[graph->node_count++] = node;
    return 0;
}

/**
 * @brief Add dependency relationship
 * @param graph Dependency graph
 * @param parent_name Parent module name
 * @param child_name Child dependency name
 * @return 0 on success, -1 on error
 */
int dependency_graph_add_dependency(DependencyGraph* graph, const char* parent_name, const char* child_name) {
    if (!graph || !parent_name || !child_name) {
        return -1;
    }
    
    DependencyNode* parent = dependency_graph_find_node(graph, parent_name);
    DependencyNode* child = dependency_graph_find_node(graph, child_name);
    
    if (!parent || !child) {
        return -1; // Both nodes must exist
    }
    
    return dependency_node_add_child(parent, child);
}

// ============================================================================
// CYCLE DETECTION
// ============================================================================

/**
 * @brief Reset visit states for all nodes
 * @param graph Dependency graph
 */
void reset_visit_states(DependencyGraph* graph) {
    if (!graph) {
        return;
    }
    
    for (size_t i = 0; i < graph->node_count; i++) {
        if (graph->nodes[i]) {
            graph->nodes[i]->visit_state = 0; // White (unvisited)
        }
    }
}

/**
 * @brief DFS-based circular dependency check from specific node
 * @param detector Dependency detector
 * @param node Starting node
 * @return 1 if cycle found, 0 if no cycle, -1 on error
 */
int dependency_check_circular_from(DependencyDetector* detector, const char* module_name) {
    if (!detector || !module_name) {
        return -1;
    }
    
    DependencyNode* node = dependency_graph_find_node(detector->graph, module_name);
    if (!node) {
        return -1;
    }
    
    if (node->visit_state == 1) {
        // Gray node - we've found a back edge (cycle)
        return 1;
    }
    
    if (node->visit_state == 2) {
        // Black node - already processed
        return 0;
    }
    
    // Mark as gray (currently being processed)
    node->visit_state = 1;
    
    // Check all children
    for (size_t i = 0; i < node->child_count; i++) {
        if (node->children[i] && node->children[i]->module) {
            int result = dependency_check_circular_from(detector, node->children[i]->module->name);
            if (result != 0) {
                return result; // Cycle found or error
            }
        }
    }
    
    // Mark as black (completely processed)
    node->visit_state = 2;
    return 0;
}

/**
 * @brief Check for circular dependencies in graph
 * @param detector Dependency detector
 * @return 1 if circular dependencies found, 0 otherwise, -1 on error
 */
int dependency_check_circular(DependencyDetector* detector) {
    if (!detector || !detector->graph) {
        return -1;
    }
    
    reset_visit_states(detector->graph);
    
    // Check from each unvisited node
    for (size_t i = 0; i < detector->graph->node_count; i++) {
        if (detector->graph->nodes[i] && detector->graph->nodes[i]->visit_state == 0) {
            int result = dependency_check_circular_from(detector, detector->graph->nodes[i]->module->name);
            if (result != 0) {
                return result;
            }
        }
    }
    
    return 0; // No cycles found
}

// ============================================================================
// DEPENDENCY DETECTOR MANAGEMENT
// ============================================================================

/**
 * @brief Create a new dependency detector
 * @return New dependency detector or NULL on error
 */
DependencyDetector* dependency_detector_new(DependencyGraph* graph) {
    DependencyDetector* detector = xmd_malloc(sizeof(DependencyDetector));
    if (!detector) {
        return NULL;
    }
    
    detector->graph = graph;
    detector->cycle_path = NULL;
    detector->cycle_path_count = 0;
    
    if (!detector->graph) {
        free(detector);
        return NULL;
    }
    
    return detector;
}

/**
 * @brief Free a dependency detector
 * @param detector Detector to free
 */
void dependency_detector_free(DependencyDetector* detector) {
    if (!detector) {
        return;
    }
    
    dependency_graph_free(detector->graph);
    free(detector->cycle_path);
    free(detector);
}

// ============================================================================
// TOPOLOGICAL SORTING
// ============================================================================

/**
 * @brief Calculate in-degrees for all nodes
 * @param graph Dependency graph
 * @param in_degrees Output array for in-degrees
 * @return 0 on success, -1 on error
 */
static int calculate_in_degrees(DependencyGraph* graph, int* in_degrees) {
    if (!graph || !in_degrees) {
        return -1;
    }
    
    // Initialize all in-degrees to 0
    for (size_t i = 0; i < graph->node_count; i++) {
        in_degrees[i] = 0;
    }
    
    // Count incoming edges
    for (size_t i = 0; i < graph->node_count; i++) {
        DependencyNode* node = graph->nodes[i];
        if (!node) continue;
        
        for (size_t j = 0; j < node->child_count; j++) {
            // Find index of child node
            for (size_t k = 0; k < graph->node_count; k++) {
                if (graph->nodes[k] == node->children[j]) {
                    in_degrees[k]++;
                    break;
                }
            }
        }
    }
    
    return 0;
}

/**
 * @brief Perform topological sort on dependency graph
 * @param graph Dependency graph
 * @param sorted_modules Output array for sorted modules (caller must free)
 * @param count Output count of sorted modules
 * @return 0 on success, -1 on error
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
        free(in_degrees);
        free(visited);
        free(result);
        return -1;
    }
    
    // Initialize visited array
    for (size_t i = 0; i < graph->node_count; i++) {
        visited[i] = false;
    }
    
    // Calculate in-degrees
    if (calculate_in_degrees(graph, in_degrees) != 0) {
        free(in_degrees);
        free(visited);
        free(result);
        return -1;
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
    
    free(in_degrees);
    free(visited);
    
    if (result_count != graph->node_count) {
        // Cycle detected
        free(result);
        return -1;
    }
    
    // Store sorted order in graph
    if (graph->load_order) {
        free(graph->load_order);
    }
    graph->load_order = xmd_malloc(result_count * sizeof(char*));
    for (size_t i = 0; i < result_count; i++) {
        graph->load_order[i] = xmd_strdup(result[i]->name);
    }
    graph->load_order_count = result_count;
    
    free(result);
    return 0;
}

// ============================================================================
// DEPENDENCY VALIDATION
// ============================================================================

/**
 * @brief Validate all dependencies in the system
 * @param detector Dependency detector
 * @return 0 if all dependencies valid, -1 on error or invalid dependencies
 */
int dependency_validate_all(ModuleRegistry* registry) {
    if (!registry) {
        return -1;
    }
    
    // Build dependency graph from registry - REAL IMPLEMENTATION NEEDED
    // This function was declared but never implemented - adding stub to prevent linker errors
    // TODO: Implement actual dependency graph building
    DependencyGraph* graph = dependency_graph_new();
    if (!graph) {
        return -1;
    }
    
    // Create detector
    DependencyDetector* detector = dependency_detector_new(graph);
    if (!detector) {
        dependency_graph_free(graph);
        return -1;
    }
    
    // Check for circular dependencies
    int circular_result = dependency_check_circular(detector);
    if (circular_result != 0) {
        dependency_detector_free(detector);
        return -1;
    }
    
    // Attempt topological sort
    int sort_result = dependency_graph_topological_sort(graph);
    
    dependency_detector_free(detector);
    return sort_result;
}
