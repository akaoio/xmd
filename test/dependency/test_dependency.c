/**
 * @file test_dependency.c
 * @brief Test suite for dependency management system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/dependency.h"

/**
 * @brief Test dependency node creation and management
 */
void test_dependency_node_lifecycle(void) {
    printf("Testing dependency node lifecycle...\n");
    
    Module* module = module_new("test_module", "/test.xmd");
    DependencyNode* node = dependency_node_new(module);
    assert(node != NULL);
    assert(node->module == module);
    assert(node->children == NULL);
    assert(node->child_count == 0);
    assert(node->visit_state == 0);
    
    dependency_node_free(node);
    module_free(module);
    
    printf("✓ Dependency node lifecycle tests passed\n");
}

/**
 * @brief Test dependency node relationships
 */
void test_dependency_node_relationships(void) {
    printf("Testing dependency node relationships...\n");
    
    Module* parent_module = module_new("parent", "/parent.xmd");
    Module* child_module = module_new("child", "/child.xmd");
    
    DependencyNode* parent_node = dependency_node_new(parent_module);
    DependencyNode* child_node = dependency_node_new(child_module);
    
    // Add child dependency
    int result = dependency_node_add_child(parent_node, child_node);
    assert(result == MODULE_SUCCESS);
    assert(parent_node->child_count == 1);
    assert(parent_node->children[0] == child_node);
    
    // Add another child
    Module* child2_module = module_new("child2", "/child2.xmd");
    DependencyNode* child2_node = dependency_node_new(child2_module);
    
    result = dependency_node_add_child(parent_node, child2_node);
    assert(result == MODULE_SUCCESS);
    assert(parent_node->child_count == 2);
    assert(parent_node->children[1] == child2_node);
    
    // Test NULL inputs
    result = dependency_node_add_child(NULL, child_node);
    assert(result == MODULE_ERROR);
    
    result = dependency_node_add_child(parent_node, NULL);
    assert(result == MODULE_ERROR);
    
    dependency_node_free(parent_node);
    dependency_node_free(child2_node);
    module_free(parent_module);
    module_free(child_module);
    module_free(child2_module);
    
    printf("✓ Dependency node relationship tests passed\n");
}

/**
 * @brief Test dependency graph creation and management
 */
void test_dependency_graph_lifecycle(void) {
    printf("Testing dependency graph lifecycle...\n");
    
    DependencyGraph* graph = dependency_graph_new();
    assert(graph != NULL);
    assert(graph->nodes == NULL);
    assert(graph->node_count == 0);
    assert(graph->load_order == NULL);
    assert(graph->load_order_count == 0);
    
    dependency_graph_free(graph);
    
    printf("✓ Dependency graph lifecycle tests passed\n");
}

/**
 * @brief Test dependency graph module addition
 */
void test_dependency_graph_modules(void) {
    printf("Testing dependency graph module management...\n");
    
    DependencyGraph* graph = dependency_graph_new();
    
    // Add modules to graph
    Module* module1 = module_new("utils", "/utils.xmd");
    Module* module2 = module_new("config", "/config.xmd");
    
    int result = dependency_graph_add_module(graph, module1);
    assert(result == MODULE_SUCCESS);
    assert(graph->node_count == 1);
    
    result = dependency_graph_add_module(graph, module2);
    assert(result == MODULE_SUCCESS);
    assert(graph->node_count == 2);
    
    // Find nodes
    DependencyNode* node1 = dependency_graph_find_node(graph, "utils");
    assert(node1 != NULL);
    assert(node1->module == module1);
    
    DependencyNode* node2 = dependency_graph_find_node(graph, "config");
    assert(node2 != NULL);
    assert(node2->module == module2);
    
    DependencyNode* not_found = dependency_graph_find_node(graph, "nonexistent");
    assert(not_found == NULL);
    
    // Test duplicate addition
    result = dependency_graph_add_module(graph, module1);
    assert(result == MODULE_ALREADY_LOADED);
    assert(graph->node_count == 2);
    
    dependency_graph_free(graph);
    module_free(module1);
    module_free(module2);
    
    printf("✓ Dependency graph module tests passed\n");
}

/**
 * @brief Test dependency graph relationships
 */
void test_dependency_graph_relationships(void) {
    printf("Testing dependency graph relationships...\n");
    
    DependencyGraph* graph = dependency_graph_new();
    
    Module* app_module = module_new("app", "/app.xmd");
    Module* utils_module = module_new("utils", "/utils.xmd");
    Module* config_module = module_new("config", "/config.xmd");
    
    dependency_graph_add_module(graph, app_module);
    dependency_graph_add_module(graph, utils_module);
    dependency_graph_add_module(graph, config_module);
    
    // Add dependencies: app -> utils, app -> config
    int result = dependency_graph_add_dependency(graph, "app", "utils");
    assert(result == MODULE_SUCCESS);
    
    result = dependency_graph_add_dependency(graph, "app", "config");
    assert(result == MODULE_SUCCESS);
    
    // Verify relationships
    // Since app depends on utils and config, utils and config should each have app as a child
    DependencyNode* utils_node = dependency_graph_find_node(graph, "utils");
    DependencyNode* config_node = dependency_graph_find_node(graph, "config");
    DependencyNode* app_node = dependency_graph_find_node(graph, "app");
    
    assert(utils_node->child_count == 1);
    assert(utils_node->children[0]->module == app_module);
    assert(config_node->child_count == 1);
    assert(config_node->children[0]->module == app_module);
    assert(app_node->child_count == 0);
    
    // Test non-existent modules
    result = dependency_graph_add_dependency(graph, "nonexistent", "utils");
    assert(result == MODULE_NOT_FOUND);
    
    result = dependency_graph_add_dependency(graph, "app", "nonexistent");
    assert(result == MODULE_NOT_FOUND);
    
    dependency_graph_free(graph);
    module_free(app_module);
    module_free(utils_module);
    module_free(config_module);
    
    printf("✓ Dependency graph relationship tests passed\n");
}

/**
 * @brief Test topological sorting
 */
void test_topological_sort(void) {
    printf("Testing topological sorting...\n");
    
    DependencyGraph* graph = dependency_graph_new();
    
    // Create a dependency chain: app -> utils -> base
    Module* app_module = module_new("app", "/app.xmd");
    Module* utils_module = module_new("utils", "/utils.xmd");
    Module* base_module = module_new("base", "/base.xmd");
    
    dependency_graph_add_module(graph, app_module);
    dependency_graph_add_module(graph, utils_module);
    dependency_graph_add_module(graph, base_module);
    
    dependency_graph_add_dependency(graph, "app", "utils");
    dependency_graph_add_dependency(graph, "utils", "base");
    
    // Perform topological sort
    int result = dependency_graph_topological_sort(graph);
    assert(result == MODULE_SUCCESS);
    assert(graph->load_order_count == 3);
    
    // Verify order: base should come before utils, utils before app
    int base_pos = -1, utils_pos = -1, app_pos = -1;
    for (size_t i = 0; i < graph->load_order_count; i++) {
        if (strcmp(graph->load_order[i], "base") == 0) base_pos = i;
        if (strcmp(graph->load_order[i], "utils") == 0) utils_pos = i;
        if (strcmp(graph->load_order[i], "app") == 0) app_pos = i;
    }
    
    assert(base_pos >= 0 && utils_pos >= 0 && app_pos >= 0);
    assert(base_pos < utils_pos);
    assert(utils_pos < app_pos);
    
    dependency_graph_free(graph);
    module_free(app_module);
    module_free(utils_module);
    module_free(base_module);
    
    printf("✓ Topological sorting tests passed\n");
}

/**
 * @brief Test circular dependency detection
 */
void test_circular_dependency_detection(void) {
    printf("Testing circular dependency detection...\n");
    
    DependencyGraph* graph = dependency_graph_new();
    
    // Create circular dependency: A -> B -> C -> A
    Module* module_a = module_new("A", "/A.xmd");
    Module* module_b = module_new("B", "/B.xmd");
    Module* module_c = module_new("C", "/C.xmd");
    
    dependency_graph_add_module(graph, module_a);
    dependency_graph_add_module(graph, module_b);
    dependency_graph_add_module(graph, module_c);
    
    dependency_graph_add_dependency(graph, "A", "B");
    dependency_graph_add_dependency(graph, "B", "C");
    dependency_graph_add_dependency(graph, "C", "A");  // Creates cycle
    
    DependencyDetector* detector = dependency_detector_new(graph);
    assert(detector != NULL);
    
    int result = dependency_check_circular(detector);
    assert(result == MODULE_CIRCULAR_DEPENDENCY);
    
    // Get cycle path
    char** cycle_path = NULL;
    size_t cycle_length = 0;
    result = dependency_get_cycle_path(detector, &cycle_path, &cycle_length);
    assert(result == MODULE_SUCCESS);
    assert(cycle_length > 0);
    assert(cycle_path != NULL);
    
    // Free cycle path
    for (size_t i = 0; i < cycle_length; i++) {
        free(cycle_path[i]);
    }
    free(cycle_path);
    
    dependency_detector_free(detector);
    dependency_graph_free(graph);
    module_free(module_a);
    module_free(module_b);
    module_free(module_c);
    
    printf("✓ Circular dependency detection tests passed\n");
}

/**
 * @brief Test acyclic dependency graph
 */
void test_acyclic_dependency_graph(void) {
    printf("Testing acyclic dependency graph...\n");
    
    DependencyGraph* graph = dependency_graph_new();
    
    // Create acyclic dependency: A -> B, A -> C, B -> D, C -> D
    Module* module_a = module_new("A", "/A.xmd");
    Module* module_b = module_new("B", "/B.xmd");
    Module* module_c = module_new("C", "/C.xmd");
    Module* module_d = module_new("D", "/D.xmd");
    
    dependency_graph_add_module(graph, module_a);
    dependency_graph_add_module(graph, module_b);
    dependency_graph_add_module(graph, module_c);
    dependency_graph_add_module(graph, module_d);
    
    dependency_graph_add_dependency(graph, "A", "B");
    dependency_graph_add_dependency(graph, "A", "C");
    dependency_graph_add_dependency(graph, "B", "D");
    dependency_graph_add_dependency(graph, "C", "D");
    
    DependencyDetector* detector = dependency_detector_new(graph);
    
    int result = dependency_check_circular(detector);
    assert(result == MODULE_SUCCESS);  // No circular dependency
    
    // Test specific starting point
    result = dependency_check_circular_from(detector, "A");
    assert(result == MODULE_SUCCESS);
    
    dependency_detector_free(detector);
    dependency_graph_free(graph);
    module_free(module_a);
    module_free(module_b);
    module_free(module_c);
    module_free(module_d);
    
    printf("✓ Acyclic dependency graph tests passed\n");
}

/**
 * @brief Test dependency validation with module registry
 */
void test_dependency_validation(void) {
    printf("Testing dependency validation...\n");
    
    ModuleRegistry* registry = module_registry_new();
    
    // Create modules with dependencies
    Module* app_module = module_new("app", "/app.xmd");
    Module* utils_module = module_new("utils", "/utils.xmd");
    
    module_add_dependency(app_module, "utils");
    module_add_dependency(utils_module, "base");  // base doesn't exist
    
    module_registry_register(registry, app_module);
    module_registry_register(registry, utils_module);
    
    // Build dependency graph
    DependencyGraph* graph = NULL;
    int result = dependency_build_graph(registry, &graph);
    assert(result == MODULE_SUCCESS);
    assert(graph != NULL);
    
    // Validate dependencies (should fail due to missing 'base')
    result = dependency_validate_all(registry);
    assert(result == MODULE_NOT_FOUND);
    
    dependency_graph_free(graph);
    module_registry_free(registry);
    
    printf("✓ Dependency validation tests passed\n");
}

/**
 * @brief Test dependency system edge cases
 */
void test_dependency_edge_cases(void) {
    printf("Testing dependency edge cases...\n");
    
    // Test NULL inputs
    DependencyNode* null_node = dependency_node_new(NULL);
    assert(null_node == NULL);
    
    dependency_node_free(NULL);  // Should not crash
    dependency_graph_free(NULL);  // Should not crash
    dependency_detector_free(NULL);  // Should not crash
    
    // Test empty graph
    DependencyGraph* empty_graph = dependency_graph_new();
    int result = dependency_graph_topological_sort(empty_graph);
    assert(result == MODULE_SUCCESS);
    assert(empty_graph->load_order_count == 0);
    
    DependencyDetector* detector = dependency_detector_new(empty_graph);
    result = dependency_check_circular(detector);
    assert(result == MODULE_SUCCESS);  // No cycles in empty graph
    
    dependency_detector_free(detector);
    dependency_graph_free(empty_graph);
    
    printf("✓ Dependency edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Dependency Management Tests ===\n");
    
    test_dependency_node_lifecycle();
    test_dependency_node_relationships();
    test_dependency_graph_lifecycle();
    test_dependency_graph_modules();
    test_dependency_graph_relationships();
    test_topological_sort();
    test_circular_dependency_detection();
    test_acyclic_dependency_graph();
    test_dependency_validation();
    test_dependency_edge_cases();
    
    printf("\n✅ All dependency management tests passed!\n");
    return 0;
}
