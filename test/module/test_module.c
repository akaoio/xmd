/**
 * @file test_module.c
 * @brief Test suite for module system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/module.h"

/**
 * @brief Test module creation and destruction
 */
void test_module_lifecycle(void) {
    printf("Testing module lifecycle...\n");
    
    Module* module = module_new("test_module", "/path/to/test.xmd");
    assert(module != NULL);
    assert(strcmp(module->name, "test_module") == 0);
    assert(strcmp(module->path, "/path/to/test.xmd") == 0);
    assert(module->exports != NULL);
    assert(module->dependencies == NULL);
    assert(module->dependency_count == 0);
    assert(module->loaded == false);
    assert(module->loading == false);
    
    module_free(module);
    
    printf("✓ Module lifecycle tests passed\n");
}

/**
 * @brief Test module dependency management
 */
void test_module_dependencies(void) {
    printf("Testing module dependencies...\n");
    
    Module* module = module_new("main_module", "/main.xmd");
    assert(module != NULL);
    
    // Add dependencies
    int result = module_add_dependency(module, "utils");
    assert(result == MODULE_SUCCESS);
    assert(module->dependency_count == 1);
    assert(strcmp(module->dependencies[0], "utils") == 0);
    
    result = module_add_dependency(module, "config");
    assert(result == MODULE_SUCCESS);
    assert(module->dependency_count == 2);
    assert(strcmp(module->dependencies[1], "config") == 0);
    
    // Test NULL inputs
    result = module_add_dependency(NULL, "test");
    assert(result == MODULE_ERROR);
    
    result = module_add_dependency(module, NULL);
    assert(result == MODULE_ERROR);
    
    module_free(module);
    
    printf("✓ Module dependency tests passed\n");
}

/**
 * @brief Test module export functionality
 */
void test_module_exports(void) {
    printf("Testing module exports...\n");
    
    Module* module = module_new("export_module", "/export.xmd");
    assert(module != NULL);
    
    // Export variables
    variable* str_var = variable_new_string("Hello World");
    int result = module_export(module, "greeting", str_var);
    assert(result == MODULE_SUCCESS);
    
    variable* num_var = variable_new_number(42);
    result = module_export(module, "answer", num_var);
    assert(result == MODULE_SUCCESS);
    
    // Test retrieval
    variable* retrieved = module_get_export(module, "greeting");
    assert(retrieved != NULL);
    assert(retrieved->type == VAR_STRING);
    assert(strcmp(retrieved->value.string_value, "Hello World") == 0);
    
    retrieved = module_get_export(module, "answer");
    assert(retrieved != NULL);
    assert(retrieved->type == VAR_NUMBER);
    assert(retrieved->value.number_value == 42);
    
    // Test non-existent export
    retrieved = module_get_export(module, "nonexistent");
    assert(retrieved == NULL);
    
    // Test NULL inputs
    result = module_export(NULL, "test", str_var);
    assert(result == MODULE_ERROR);
    
    result = module_export(module, NULL, str_var);
    assert(result == MODULE_ERROR);
    
    result = module_export(module, "test", NULL);
    assert(result == MODULE_ERROR);
    
    variable_unref(str_var);
    variable_unref(num_var);
    module_free(module);
    
    printf("✓ Module export tests passed\n");
}

/**
 * @brief Test module registry functionality
 */
void test_module_registry(void) {
    printf("Testing module registry...\n");
    
    ModuleRegistry* registry = module_registry_new();
    assert(registry != NULL);
    assert(registry->modules != NULL);
    assert(registry->count == 0);
    assert(registry->search_paths == NULL);
    assert(registry->search_path_count == 0);
    
    // Add search paths
    int result = module_registry_add_search_path(registry, "/usr/local/xmd/modules");
    assert(result == MODULE_SUCCESS);
    assert(registry->search_path_count == 1);
    assert(strcmp(registry->search_paths[0], "/usr/local/xmd/modules") == 0);
    
    result = module_registry_add_search_path(registry, "/home/user/xmd");
    assert(result == MODULE_SUCCESS);
    assert(registry->search_path_count == 2);
    
    // Register modules
    Module* module1 = module_new("utils", "/utils.xmd");
    result = module_registry_register(registry, module1);
    assert(result == MODULE_SUCCESS);
    assert(registry->count == 1);
    
    Module* module2 = module_new("config", "/config.xmd");
    result = module_registry_register(registry, module2);
    assert(result == MODULE_SUCCESS);
    assert(registry->count == 2);
    
    // Find modules
    Module* found = module_registry_find(registry, "utils");
    assert(found == module1);
    
    found = module_registry_find(registry, "config");
    assert(found == module2);
    
    found = module_registry_find(registry, "nonexistent");
    assert(found == NULL);
    
    // Test duplicate registration
    Module* duplicate = module_new("utils", "/different/utils.xmd");
    result = module_registry_register(registry, duplicate);
    assert(result == MODULE_ALREADY_LOADED);
    module_free(duplicate);
    
    // Test NULL inputs
    result = module_registry_register(NULL, module1);
    assert(result == MODULE_ERROR);
    
    result = module_registry_register(registry, NULL);
    assert(result == MODULE_ERROR);
    
    module_registry_free(registry);
    
    printf("✓ Module registry tests passed\n");
}

/**
 * @brief Test module path resolution
 */
void test_module_path_resolution(void) {
    printf("Testing module path resolution...\n");
    
    ModuleRegistry* registry = module_registry_new();
    assert(registry != NULL);
    
    // Add search paths
    module_registry_add_search_path(registry, "/usr/local/xmd/modules");
    module_registry_add_search_path(registry, "/home/user/xmd");
    
    char* resolved_path = NULL;
    
    // Test absolute path (use a file that actually exists, like this test file)
    int result = module_resolve_path(registry, __FILE__, &resolved_path);
    assert(result == MODULE_SUCCESS);
    assert(resolved_path != NULL);
    assert(strcmp(resolved_path, __FILE__) == 0);
    free(resolved_path);
    
    // Test module name resolution (would search in paths, expect NOT_FOUND)
    resolved_path = NULL;
    result = module_resolve_path(registry, "nonexistent_utils", &resolved_path);
    assert(result == MODULE_NOT_FOUND);
    assert(resolved_path == NULL);
    
    // Test NULL inputs
    result = module_resolve_path(NULL, "test", &resolved_path);
    assert(result == MODULE_ERROR);
    
    result = module_resolve_path(registry, NULL, &resolved_path);
    assert(result == MODULE_ERROR);
    
    result = module_resolve_path(registry, "test", NULL);
    assert(result == MODULE_ERROR);
    
    module_registry_free(registry);
    
    printf("✓ Module path resolution tests passed\n");
}

/**
 * @brief Test module edge cases and error handling
 */
void test_module_edge_cases(void) {
    printf("Testing module edge cases...\n");
    
    // Test NULL inputs for module functions
    Module* null_module = module_new(NULL, "/path");
    assert(null_module == NULL);
    
    null_module = module_new("name", NULL);
    assert(null_module == NULL);
    
    // Test empty strings
    Module* empty_module = module_new("", "");
    assert(empty_module != NULL);
    assert(strlen(empty_module->name) == 0);
    assert(strlen(empty_module->path) == 0);
    module_free(empty_module);
    
    // Test registry with NULL
    module_registry_free(NULL); // Should not crash
    
    ModuleRegistry* null_registry = module_registry_new();
    int result = module_registry_add_search_path(null_registry, NULL);
    assert(result == MODULE_ERROR);
    
    module_registry_free(null_registry);
    
    printf("✓ Module edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Module System Tests ===\n");
    
    test_module_lifecycle();
    test_module_dependencies();
    test_module_exports();
    test_module_registry();
    test_module_path_resolution();
    test_module_edge_cases();
    
    printf("\n✅ All module system tests passed!\n");
    return 0;
}
