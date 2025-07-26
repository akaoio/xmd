/**
 * @file test_phase5_integration.c
 * @brief Integration tests for Phase 5 module system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/module.h"
#include "../../include/import_export.h"
#include "../../include/dependency.h"
#include "../../include/variable.h"
#include "../../include/store.h"

/**
 * @brief Test basic module import/export integration
 */
void test_module_import_export_integration(void) {
    printf("Testing module import/export integration...\n");
    
    ModuleRegistry* registry = module_registry_new();
    store* scope = store_create();
    
    // Create utility module with exports
    Module* utils_module = module_new("utils", "/lib/utils.xmd");
    variable* helper_func = variable_new_string("def helper(): return 42");
    variable* constant_val = variable_new_number(100);
    
    module_export(utils_module, "helper", helper_func);
    module_export(utils_module, "CONSTANT", constant_val);
    module_registry_register(registry, utils_module);
    
    // Create main module that imports from utils
    ImportExportProcessor* processor = import_export_processor_new(registry, scope);
    
    // Import specific symbol
    int result = import_symbol(processor, "utils", "helper", "my_helper");
    assert(result == MODULE_SUCCESS);
    
    variable* imported = store_get(scope, "my_helper");
    assert(imported != NULL);
    assert(imported->type == VAR_STRING);
    assert(strcmp(imported->value.string_value, "def helper(): return 42") == 0);
    
    // Import all symbols
    result = import_all_symbols(processor, "utils");
    assert(result == MODULE_SUCCESS);
    
    imported = store_get(scope, "CONSTANT");
    assert(imported != NULL);
    assert(imported->type == VAR_NUMBER);
    assert(imported->value.number_value == 100);
    
    variable_unref(helper_func);
    variable_unref(constant_val);
    import_export_processor_free(processor);
    store_destroy(scope);
    module_registry_free(registry);
    
    printf("Module import/export integration test passed.\n");
}

/**
 * @brief Test dependency resolution integration
 */
void test_dependency_resolution_integration(void) {
    printf("Testing dependency resolution integration...\n");
    
    ModuleRegistry* registry = module_registry_new();
    
    // Create dependency chain: app -> utils -> base
    Module* base_module = module_new("base", "/lib/base.xmd");
    variable* base_var = variable_new_string("base_functionality");
    module_export(base_module, "base_func", base_var);
    
    Module* utils_module = module_new("utils", "/lib/utils.xmd");
    module_add_dependency(utils_module, "base");
    variable* utils_var = variable_new_string("utils_functionality");
    module_export(utils_module, "utils_func", utils_var);
    
    Module* app_module = module_new("app", "/app.xmd");
    module_add_dependency(app_module, "utils");
    
    module_registry_register(registry, base_module);
    module_registry_register(registry, utils_module);
    module_registry_register(registry, app_module);
    
    // Build dependency graph
    DependencyGraph* graph = NULL;
    int result = dependency_build_graph(registry, &graph);
    assert(result == MODULE_SUCCESS);
    
    // Verify no circular dependencies
    DependencyDetector* detector = dependency_detector_new(graph);
    result = dependency_check_circular(detector);
    assert(result == MODULE_SUCCESS);
    
    // Generate load order
    result = dependency_graph_topological_sort(graph);
    assert(result == MODULE_SUCCESS);
    assert(graph->load_order_count == 3);
    
    // Verify base loads before utils, utils before app
    int base_pos = -1, utils_pos = -1, app_pos = -1;
    for (size_t i = 0; i < graph->load_order_count; i++) {
        if (strcmp(graph->load_order[i], "base") == 0) base_pos = i;
        if (strcmp(graph->load_order[i], "utils") == 0) utils_pos = i;
        if (strcmp(graph->load_order[i], "app") == 0) app_pos = i;
    }
    
    assert(base_pos < utils_pos && utils_pos < app_pos);
    
    variable_unref(base_var);
    variable_unref(utils_var);
    dependency_detector_free(detector);
    dependency_graph_free(graph);
    module_registry_free(registry);
    
    printf("Dependency resolution integration test passed.\n");
}

/**
 * @brief Test circular dependency detection integration
 */
void test_circular_dependency_integration(void) {
    printf("Testing circular dependency detection integration...\n");
    
    ModuleRegistry* registry = module_registry_new();
    
    // Create circular dependency: A -> B -> C -> A
    Module* module_a = module_new("A", "/A.xmd");
    Module* module_b = module_new("B", "/B.xmd");
    Module* module_c = module_new("C", "/C.xmd");
    
    module_add_dependency(module_a, "B");
    module_add_dependency(module_b, "C");
    module_add_dependency(module_c, "A");  // Creates cycle
    
    module_registry_register(registry, module_a);
    module_registry_register(registry, module_b);
    module_registry_register(registry, module_c);
    
    // Build dependency graph
    DependencyGraph* graph = NULL;
    int result = dependency_build_graph(registry, &graph);
    assert(result == MODULE_SUCCESS);
    
    // Detect circular dependency
    DependencyDetector* detector = dependency_detector_new(graph);
    result = dependency_check_circular(detector);
    assert(result == MODULE_CIRCULAR_DEPENDENCY);
    
    // Get cycle path for analysis
    char** cycle_path = NULL;
    size_t cycle_length = 0;
    result = dependency_get_cycle_path(detector, &cycle_path, &cycle_length);
    assert(result == MODULE_SUCCESS);
    assert(cycle_length >= 3);  // At least A -> B -> C -> A
    
    // Clean up cycle path
    for (size_t i = 0; i < cycle_length; i++) {
        free(cycle_path[i]);
    }
    free(cycle_path);
    
    dependency_detector_free(detector);
    dependency_graph_free(graph);
    module_registry_free(registry);
    
    printf("Circular dependency detection integration test passed.\n");
}

/**
 * @brief Test module with variable system integration
 */
void test_module_variable_integration(void) {
    printf("Testing module variable system integration...\n");
    
    ModuleRegistry* registry = module_registry_new();
    store* global_scope = store_create();
    
    // Set up global variables
    variable* global_config = variable_new_string("production");
    store_set(global_scope, "ENV", global_config);
    
    // Create config module that uses global variables
    Module* config_module = module_new("config", "/config.xmd");
    
    // Export configuration based on global ENV variable
    variable* env_var = store_get(global_scope, "ENV");
    if (env_var && env_var->type == VAR_STRING) {
        if (strcmp(env_var->value.string_value, "production") == 0) {
            variable* prod_config = variable_new_string("prod_database_url");
            module_export(config_module, "DATABASE_URL", prod_config);
            variable_unref(prod_config);
        }
    }
    
    module_registry_register(registry, config_module);
    
    // Import configuration into application scope
    store* app_scope = store_create();
    ImportExportProcessor* processor = import_export_processor_new(registry, app_scope);
    
    int result = import_symbol(processor, "config", "DATABASE_URL", NULL);
    assert(result == MODULE_SUCCESS);
    
    variable* imported_config = store_get(app_scope, "DATABASE_URL");
    assert(imported_config != NULL);
    assert(imported_config->type == VAR_STRING);
    assert(strcmp(imported_config->value.string_value, "prod_database_url") == 0);
    
    variable_unref(global_config);
    import_export_processor_free(processor);
    store_destroy(app_scope);
    store_destroy(global_scope);
    module_registry_free(registry);
    
    printf("Module variable system integration test passed.\n");
}

/**
 * @brief Test complete module pipeline
 */
void test_complete_module_pipeline(void) {
    printf("Testing complete module pipeline...\n");
    
    ModuleRegistry* registry = module_registry_new();
    
    // Add search paths
    module_registry_add_search_path(registry, "/usr/local/xmd/lib");
    module_registry_add_search_path(registry, "./lib");
    
    // Create a complete module ecosystem
    // 1. Math utilities module
    Module* math_module = module_new("math", "/lib/math.xmd");
    variable* pi_value = variable_new_number(3.14159);
    variable* add_func = variable_new_string("def add(a, b): return a + b");
    module_export(math_module, "PI", pi_value);
    module_export(math_module, "add", add_func);
    
    // 2. String utilities module (depends on math for calculations)
    Module* string_module = module_new("string_utils", "/lib/string_utils.xmd");
    module_add_dependency(string_module, "math");
    variable* concat_func = variable_new_string("def concat(a, b): return a + b");
    module_export(string_module, "concat", concat_func);
    
    // 3. Application module (depends on both)
    Module* app_module = module_new("app", "/app.xmd");
    module_add_dependency(app_module, "math");
    module_add_dependency(app_module, "string_utils");
    
    // Register all modules
    module_registry_register(registry, math_module);
    module_registry_register(registry, string_module);
    module_registry_register(registry, app_module);
    
    // Validate dependencies
    int result = dependency_validate_all(registry);
    assert(result == MODULE_SUCCESS);
    
    // Build and verify dependency graph
    DependencyGraph* graph = NULL;
    result = dependency_build_graph(registry, &graph);
    assert(result == MODULE_SUCCESS);
    
    DependencyDetector* detector = dependency_detector_new(graph);
    result = dependency_check_circular(detector);
    assert(result == MODULE_SUCCESS);
    
    // Generate load order
    result = dependency_graph_topological_sort(graph);
    assert(result == MODULE_SUCCESS);
    
    // Create application scope and import everything needed
    store* app_scope = store_create();
    ImportExportProcessor* processor = import_export_processor_new(registry, app_scope);
    
    // Import math utilities
    result = import_symbol(processor, "math", "PI", NULL);
    assert(result == MODULE_SUCCESS);
    result = import_symbol(processor, "math", "add", "math_add");
    assert(result == MODULE_SUCCESS);
    
    // Import string utilities
    result = import_symbol(processor, "string_utils", "concat", NULL);
    assert(result == MODULE_SUCCESS);
    
    // Verify all imports
    variable* pi_import = store_get(app_scope, "PI");
    assert(pi_import != NULL && pi_import->type == VAR_NUMBER);
    
    variable* add_import = store_get(app_scope, "math_add");
    assert(add_import != NULL && add_import->type == VAR_STRING);
    
    variable* concat_import = store_get(app_scope, "concat");
    assert(concat_import != NULL && concat_import->type == VAR_STRING);
    
    variable_unref(pi_value);
    variable_unref(add_func);
    variable_unref(concat_func);
    import_export_processor_free(processor);
    dependency_detector_free(detector);
    dependency_graph_free(graph);
    store_destroy(app_scope);
    module_registry_free(registry);
    
    printf("Complete module pipeline test passed.\n");
}

/**
 * @brief Test module system error handling
 */
void test_module_error_handling(void) {
    printf("Testing module system error handling...\n");
    
    ModuleRegistry* registry = module_registry_new();
    store* scope = store_create();
    
    ImportExportProcessor* processor = import_export_processor_new(registry, scope);
    
    // Test import from non-existent module
    int result = import_symbol(processor, "nonexistent", "symbol", NULL);
    assert(result == MODULE_NOT_FOUND);
    
    // Test import non-existent symbol from existing module
    Module* test_module = module_new("test", "/test.xmd");
    module_registry_register(registry, test_module);
    
    result = import_symbol(processor, "test", "nonexistent_symbol", NULL);
    assert(result == MODULE_ERROR);
    
    // Test circular dependency handling
    Module* circular_a = module_new("circular_a", "/a.xmd");
    Module* circular_b = module_new("circular_b", "/b.xmd");
    
    module_add_dependency(circular_a, "circular_b");
    module_add_dependency(circular_b, "circular_a");
    
    module_registry_register(registry, circular_a);
    module_registry_register(registry, circular_b);
    
    DependencyGraph* graph = NULL;
    result = dependency_build_graph(registry, &graph);
    assert(result == MODULE_SUCCESS);
    
    DependencyDetector* detector = dependency_detector_new(graph);
    result = dependency_check_circular(detector);
    assert(result == MODULE_CIRCULAR_DEPENDENCY);
    
    dependency_detector_free(detector);
    dependency_graph_free(graph);
    import_export_processor_free(processor);
    store_destroy(scope);
    module_registry_free(registry);
    
    printf("Module system error handling test passed.\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Phase 5 Module System Integration Tests ===\n");
    
    test_module_import_export_integration();
    test_dependency_resolution_integration();
    test_circular_dependency_integration();
    test_module_variable_integration();
    test_complete_module_pipeline();
    test_module_error_handling();
    
    printf("\nAll Phase 5 integration tests passed!\n");
    return 0;
}
