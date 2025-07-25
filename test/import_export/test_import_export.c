/**
 * @file test_import_export.c
 * @brief Test suite for import/export system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/import_export.h"

/**
 * @brief Test import directive creation and parsing
 */
void test_import_directive_lifecycle(void) {
    printf("Testing import directive lifecycle...\n");
    
    // Test basic creation
    ImportDirective* import_dir = import_directive_new("utils", "helper_func", "help");
    assert(import_dir != NULL);
    assert(strcmp(import_dir->module_name, "utils") == 0);
    assert(strcmp(import_dir->symbol_name, "helper_func") == 0);
    assert(strcmp(import_dir->alias, "help") == 0);
    
    import_directive_free(import_dir);
    
    // Test with NULL alias
    import_dir = import_directive_new("config", "settings", NULL);
    assert(import_dir != NULL);
    assert(strcmp(import_dir->module_name, "config") == 0);
    assert(strcmp(import_dir->symbol_name, "settings") == 0);
    assert(import_dir->alias == NULL);
    
    import_directive_free(import_dir);
    
    // Test import all (NULL symbol)
    import_dir = import_directive_new("math", NULL, NULL);
    assert(import_dir != NULL);
    assert(strcmp(import_dir->module_name, "math") == 0);
    assert(import_dir->symbol_name == NULL);
    assert(import_dir->alias == NULL);
    
    import_directive_free(import_dir);
    
    printf("✓ Import directive lifecycle tests passed\n");
}

/**
 * @brief Test export directive creation
 */
void test_export_directive_lifecycle(void) {
    printf("Testing export directive lifecycle...\n");
    
    variable* str_var = variable_new_string("exported_value");
    ExportDirective* export_dir = export_directive_new("my_export", str_var);
    assert(export_dir != NULL);
    assert(strcmp(export_dir->symbol_name, "my_export") == 0);
    assert(export_dir->value == str_var);
    
    export_directive_free(export_dir);
    variable_unref(str_var);
    
    printf("✓ Export directive lifecycle tests passed\n");
}

/**
 * @brief Test import directive parsing
 */
void test_import_parsing(void) {
    printf("Testing import directive parsing...\n");
    
    ImportDirective* import_dir = NULL;
    
    // Test basic import parsing
    int result = import_parse_directive("import helper_func from utils", &import_dir);
    assert(result == MODULE_SUCCESS);
    assert(import_dir != NULL);
    assert(strcmp(import_dir->module_name, "utils") == 0);
    assert(strcmp(import_dir->symbol_name, "helper_func") == 0);
    assert(import_dir->alias == NULL);
    import_directive_free(import_dir);
    
    // Test import with alias
    result = import_parse_directive("import helper_func as help from utils", &import_dir);
    assert(result == MODULE_SUCCESS);
    assert(import_dir != NULL);
    assert(strcmp(import_dir->module_name, "utils") == 0);
    assert(strcmp(import_dir->symbol_name, "helper_func") == 0);
    assert(strcmp(import_dir->alias, "help") == 0);
    import_directive_free(import_dir);
    
    // Test import all
    result = import_parse_directive("import * from math", &import_dir);
    assert(result == MODULE_SUCCESS);
    assert(import_dir != NULL);
    assert(strcmp(import_dir->module_name, "math") == 0);
    assert(import_dir->symbol_name == NULL);
    assert(import_dir->alias == NULL);
    import_directive_free(import_dir);
    
    // Test path import
    result = import_parse_directive("import utils from \"./lib/utils.xmd\"", &import_dir);
    assert(result == MODULE_SUCCESS);
    assert(import_dir != NULL);
    assert(strcmp(import_dir->module_name, "./lib/utils.xmd") == 0);
    assert(strcmp(import_dir->symbol_name, "utils") == 0);
    import_directive_free(import_dir);
    
    // Test invalid syntax
    result = import_parse_directive("invalid syntax", &import_dir);
    assert(result == MODULE_ERROR);
    assert(import_dir == NULL);
    
    // Test NULL input
    result = import_parse_directive(NULL, &import_dir);
    assert(result == MODULE_ERROR);
    
    printf("✓ Import parsing tests passed\n");
}

/**
 * @brief Test export directive parsing
 */
void test_export_parsing(void) {
    printf("Testing export directive parsing...\n");
    
    // Create test scope with variables
    store* scope = store_create();
    variable* test_var = variable_new_string("test_value");
    store_set(scope, "my_var", test_var);
    
    ExportDirective* export_dir = NULL;
    
    // Test basic export parsing
    int result = export_parse_directive("export my_var", scope, &export_dir);
    assert(result == MODULE_SUCCESS);
    assert(export_dir != NULL);
    assert(strcmp(export_dir->symbol_name, "my_var") == 0);
    assert(export_dir->value != NULL);
    assert(export_dir->value->type == VAR_STRING);
    export_directive_free(export_dir);
    
    // Test export non-existent variable
    result = export_parse_directive("export nonexistent", scope, &export_dir);
    assert(result == MODULE_ERROR);
    assert(export_dir == NULL);
    
    // Test invalid syntax
    result = export_parse_directive("invalid export syntax", scope, &export_dir);
    assert(result == MODULE_ERROR);
    
    // Test NULL inputs
    result = export_parse_directive(NULL, scope, &export_dir);
    assert(result == MODULE_ERROR);
    
    result = export_parse_directive("export my_var", NULL, &export_dir);
    assert(result == MODULE_ERROR);
    
    variable_unref(test_var);
    store_destroy(scope);
    
    printf("✓ Export parsing tests passed\n");
}

/**
 * @brief Test import/export processor
 */
void test_import_export_processor(void) {
    printf("Testing import/export processor...\n");
    
    ModuleRegistry* registry = module_registry_new();
    store* scope = store_create();
    
    ImportExportProcessor* processor = import_export_processor_new(registry, scope);
    assert(processor != NULL);
    assert(processor->registry == registry);
    assert(processor->current_scope == scope);
    
    // Create and register a test module with exports
    Module* test_module = module_new("test_module", "/test.xmd");
    variable* exported_var = variable_new_number(123);
    module_export(test_module, "exported_value", exported_var);
    module_registry_register(registry, test_module);
    
    // Test symbol import
    int result = import_symbol(processor, "test_module", "exported_value", NULL);
    assert(result == MODULE_SUCCESS);
    
    // Verify the symbol was imported into current scope
    variable* imported = store_get(scope, "exported_value");
    assert(imported != NULL);
    assert(imported->type == VAR_NUMBER);
    assert(imported->value.number_value == 123);
    
    // Test import with alias
    result = import_symbol(processor, "test_module", "exported_value", "alias_name");
    assert(result == MODULE_SUCCESS);
    
    imported = store_get(scope, "alias_name");
    assert(imported != NULL);
    assert(imported->type == VAR_NUMBER);
    assert(imported->value.number_value == 123);
    
    // Test export from current scope
    variable* new_var = variable_new_string("new_export");
    store_set(scope, "local_var", new_var);
    
    result = export_symbol(processor, "local_var", new_var);
    assert(result == MODULE_SUCCESS);
    
    // Test import from non-existent module
    result = import_symbol(processor, "nonexistent", "var", NULL);
    assert(result == MODULE_NOT_FOUND);
    
    // Test import non-existent symbol
    result = import_symbol(processor, "test_module", "nonexistent", NULL);
    assert(result == MODULE_ERROR);
    
    variable_unref(exported_var);
    variable_unref(new_var);
    import_export_processor_free(processor);
    store_destroy(scope);
    module_registry_free(registry);
    
    printf("✓ Import/export processor tests passed\n");
}

/**
 * @brief Test import all functionality
 */
void test_import_all_symbols(void) {
    printf("Testing import all symbols...\n");
    
    ModuleRegistry* registry = module_registry_new();
    store* scope = store_create();
    
    ImportExportProcessor* processor = import_export_processor_new(registry, scope);
    
    // Create test module with multiple exports
    Module* test_module = module_new("multi_export", "/multi.xmd");
    
    variable* var1 = variable_new_string("value1");
    variable* var2 = variable_new_number(42);
    variable* var3 = variable_new_boolean(true);
    
    module_export(test_module, "export1", var1);
    module_export(test_module, "export2", var2);
    module_export(test_module, "export3", var3);
    
    module_registry_register(registry, test_module);
    
    // Import all symbols
    int result = import_all_symbols(processor, "multi_export");
    assert(result == MODULE_SUCCESS);
    
    // Verify all symbols were imported
    variable* imported1 = store_get(scope, "export1");
    assert(imported1 != NULL);
    assert(imported1->type == VAR_STRING);
    
    variable* imported2 = store_get(scope, "export2");
    assert(imported2 != NULL);
    assert(imported2->type == VAR_NUMBER);
    
    variable* imported3 = store_get(scope, "export3");
    assert(imported3 != NULL);
    assert(imported3->type == VAR_BOOLEAN);
    
    variable_unref(var1);
    variable_unref(var2);
    variable_unref(var3);
    import_export_processor_free(processor);
    store_destroy(scope);
    module_registry_free(registry);
    
    printf("✓ Import all symbols tests passed\n");
}

/**
 * @brief Test import/export edge cases
 */
void test_import_export_edge_cases(void) {
    printf("Testing import/export edge cases...\n");
    
    // Test NULL directive creation
    ImportDirective* null_import = import_directive_new(NULL, "symbol", NULL);
    assert(null_import == NULL);
    
    ExportDirective* null_export = export_directive_new(NULL, NULL);
    assert(null_export == NULL);
    
    // Test freeing NULL directives
    import_directive_free(NULL);  // Should not crash
    export_directive_free(NULL);  // Should not crash
    
    // Test processor with NULL inputs
    ImportExportProcessor* null_processor = import_export_processor_new(NULL, NULL);
    assert(null_processor == NULL);
    
    import_export_processor_free(NULL);  // Should not crash
    
    printf("✓ Import/export edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Import/Export System Tests ===\n");
    
    test_import_directive_lifecycle();
    test_export_directive_lifecycle();
    test_import_parsing();
    test_export_parsing();
    test_import_export_processor();
    test_import_all_symbols();
    test_import_export_edge_cases();
    
    printf("\n✅ All import/export tests passed!\n");
    return 0;
}