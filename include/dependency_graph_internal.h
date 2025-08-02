/**
 * @file dependency_graph_internal.h
 * @brief Internal header for dependency graph functions
 * @author XMD Team
 */

#ifndef DEPENDENCY_GRAPH_INTERNAL_H
#define DEPENDENCY_GRAPH_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dependency.h"

// Internal function declarations
int calculate_in_degrees(DependencyGraph* graph, int* in_degrees);

// Public function declarations
DependencyNode* dependency_node_new(Module* module);
void dependency_node_free(DependencyNode* node);
int dependency_node_add_child(DependencyNode* node, DependencyNode* dependency_node);
DependencyGraph* dependency_graph_new(void);
void dependency_graph_free(DependencyGraph* graph);
int dependency_graph_add_module(DependencyGraph* graph, Module* module);
DependencyNode* dependency_graph_find_node(DependencyGraph* graph, const char* module_name);
int dependency_graph_add_dependency(DependencyGraph* graph, 
                                   const char* module_name,
                                   const char* dependency_name);
int dependency_graph_topological_sort(DependencyGraph* graph);
int dependency_build_graph(ModuleRegistry* registry, DependencyGraph** graph);

#endif /* DEPENDENCY_GRAPH_INTERNAL_H */
