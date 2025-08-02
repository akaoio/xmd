/**
 * @file dependency.h
 * @brief Dependency management system for XMD modules
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include <stddef.h>
#include <stdbool.h>
#include "module.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Dependency graph node
 */
typedef struct dependency_node {
    Module* module;                     /**< Module reference */
    struct dependency_node** children; /**< Dependencies */
    size_t child_count;                 /**< Number of dependencies */
    size_t child_capacity;              /**< Capacity for dependencies */
    int visit_state;                    /**< For cycle detection (0=white, 1=gray, 2=black) */
} DependencyNode;

/**
 * @brief Dependency graph
 */
typedef struct dependency_graph {
    DependencyNode** nodes;     /**< Array of nodes */
    size_t node_count;          /**< Number of nodes */
    size_t node_capacity;       /**< Capacity for nodes */
    char** load_order;          /**< Topologically sorted load order */
    size_t load_order_count;    /**< Number of modules in load order */
} DependencyGraph;

/**
 * @brief Dependency detector for circular dependencies
 */
typedef struct dependency_detector {
    DependencyGraph* graph;     /**< Dependency graph */
    char** cycle_path;          /**< Path of circular dependency */
    size_t cycle_path_count;    /**< Length of cycle path */
    char* last_error;           /**< Last error message */
} DependencyDetector;

/**
 * @brief Create a new dependency node
 * @param module Module for this node
 * @return New dependency node or NULL on error
 */
DependencyNode* dependency_node_new(Module* module);

/**
 * @brief Free a dependency node
 * @param node Node to free
 */
void dependency_node_free(DependencyNode* node);

/**
 * @brief Add dependency to node
 * @param node Parent node
 * @param dependency_node Child dependency node
 * @return ModuleResult indicating success/failure
 */
int dependency_node_add_child(DependencyNode* node, DependencyNode* dependency_node);

/**
 * @brief Create a new dependency graph
 * @return New dependency graph or NULL on error
 */
DependencyGraph* dependency_graph_new(void);

/**
 * @brief Free a dependency graph
 * @param graph Graph to free
 */
void dependency_graph_free(DependencyGraph* graph);

/**
 * @brief Add module to dependency graph
 * @param graph Dependency graph
 * @param module Module to add
 * @return ModuleResult indicating success/failure
 */
int dependency_graph_add_module(DependencyGraph* graph, Module* module);

/**
 * @brief Add dependency relationship to graph
 * @param graph Dependency graph
 * @param module_name Module name
 * @param dependency_name Dependency name
 * @return ModuleResult indicating success/failure
 */
int dependency_graph_add_dependency(DependencyGraph* graph, 
                                   const char* module_name,
                                   const char* dependency_name);

/**
 * @brief Find node by module name
 * @param graph Dependency graph
 * @param module_name Module name
 * @return Dependency node or NULL if not found
 */
DependencyNode* dependency_graph_find_node(DependencyGraph* graph, 
                                          const char* module_name);

/**
 * @brief Generate topological sort order
 * @param graph Dependency graph
 * @return ModuleResult indicating success/failure
 */
int dependency_graph_topological_sort(DependencyGraph* graph);

/**
 * @brief Create a new dependency detector
 * @param graph Dependency graph
 * @return New detector or NULL on error
 */
DependencyDetector* dependency_detector_new(DependencyGraph* graph);

/**
 * @brief Free a dependency detector
 * @param detector Detector to free
 */
void dependency_detector_free(DependencyDetector* detector);

/**
 * @brief Check for circular dependencies
 * @param detector Dependency detector
 * @return ModuleResult indicating success or circular dependency found
 */
int dependency_check_circular(DependencyDetector* detector);

/**
 * @brief Check circular dependencies starting from specific module
 * @param detector Dependency detector
 * @param module_name Starting module name
 * @return ModuleResult indicating success or circular dependency found
 */
int dependency_check_circular_from(DependencyDetector* detector, 
                                  const char* module_name);

/**
 * @brief Get circular dependency path
 * @param detector Dependency detector
 * @param path_buffer Buffer to store cycle path (caller must free)
 * @param path_length Output path length
 * @return ModuleResult indicating success/failure
 */
int dependency_get_cycle_path(DependencyDetector* detector, 
                             char*** path_buffer, 
                             size_t* path_length);

/**
 * @brief Build dependency graph from module registry
 * @param registry Module registry
 * @param graph Output dependency graph (caller must free)
 * @return ModuleResult indicating success/failure
 */
int dependency_build_graph(ModuleRegistry* registry, DependencyGraph** graph);

/**
 * @brief Validate all dependencies in registry
 * @param registry Module registry
 * @return ModuleResult indicating success or dependency issues
 */
int dependency_validate_all(ModuleRegistry* registry);

/**
 * @brief Reset visit states for all nodes in dependency graph
 * @param graph Dependency graph
 */
void reset_visit_states(DependencyGraph* graph);

/**
 * @brief Clear the cycle path tracking
 * @param detector Dependency detector
 */
void clear_cycle_path(DependencyDetector* detector);

/**
 * @brief Perform DFS cycle detection from a specific node
 * @param detector Dependency detector
 * @param node Starting node for DFS
 * @return MODULE_SUCCESS if no cycle, MODULE_CIRCULAR_DEPENDENCY if cycle found
 */
int dfs_cycle_detection(DependencyDetector* detector, DependencyNode* node);

#ifdef __cplusplus
}
#endif

#endif /* DEPENDENCY_H */
