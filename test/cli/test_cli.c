/**
 * @file test_cli.c
 * @brief Test suite for CLI interface
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "../../include/cli.h"

/**
 * @brief Test CLI argument parsing
 */
static void test_cli_argument_parsing(void) {
    printf("Testing CLI argument parsing...\n");
    
    // Test basic process command
    {
        char* argv[] = {"xmd", "process", "test.md"};
        int argc = 3;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args != NULL);
        assert(args->command == CLI_CMD_PROCESS);
        assert(args->input_file != NULL);
        assert(strcmp(args->input_file, "test.md") == 0);
        assert(args->output_file == NULL);
        assert(!args->verbose);
        assert(!args->debug);
        
        free(args->input_file);
        free(args);
    }
    
    // Test process command with output
    {
        char* argv[] = {"xmd", "process", "input.md", "-o", "output.md"};
        int argc = 5;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args != NULL);
        assert(args->command == CLI_CMD_PROCESS);
        assert(args->input_file != NULL);
        assert(strcmp(args->input_file, "input.md") == 0);
        assert(args->output_file != NULL);
        assert(strcmp(args->output_file, "output.md") == 0);
        
        free(args->input_file);
        free(args->output_file);
        free(args);
    }
    
    // Test watch command
    {
        char* argv[] = {"xmd", "watch", "/path/to/dir", "--verbose"};
        int argc = 4;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args != NULL);
        assert(args->command == CLI_CMD_WATCH);
        assert(args->watch_directory != NULL);
        assert(strcmp(args->watch_directory, "/path/to/dir") == 0);
        assert(args->verbose);
        
        free(args->watch_directory);
        free(args);
    }
    
    // Test validate command
    {
        char* argv[] = {"xmd", "validate", "test.md", "--debug"};
        int argc = 4;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args != NULL);
        assert(args->command == CLI_CMD_VALIDATE);
        assert(args->input_file != NULL);
        assert(strcmp(args->input_file, "test.md") == 0);
        assert(args->debug);
        
        free(args->input_file);
        free(args);
    }
    
    // Test config command
    {
        char* argv[] = {"xmd", "config"};
        int argc = 2;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args != NULL);
        assert(args->command == CLI_CMD_CONFIG);
        
        free(args);
    }
    
    // Test plugin command
    {
        char* argv[] = {"xmd", "plugin", "list"};
        int argc = 3;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args != NULL);
        assert(args->command == CLI_CMD_PLUGIN);
        assert(args->plugin_name != NULL);
        assert(strcmp(args->plugin_name, "list") == 0);
        
        free(args->plugin_name);
        free(args);
    }
    
    // Test help command
    {
        char* argv[] = {"xmd", "--help"};
        int argc = 2;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args != NULL);
        assert(args->help);
        
        free(args);
    }
    
    // Test version command
    {
        char* argv[] = {"xmd", "--version"};
        int argc = 2;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args != NULL);
        assert(args->version);
        
        free(args);
    }
    
    // Test invalid command
    {
        char* argv[] = {"xmd", "invalid"};
        int argc = 2;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args == NULL); // Should fail for invalid command
    }
    
    printf("✓ CLI argument parsing tests passed\n");
}

/**
 * @brief Test CLI execution flow
 */
static void test_cli_execution(void) {
    printf("Testing CLI execution flow...\n");
    
    // Create a temporary test file
    const char* test_content = "# Test\n\nThis is a test markdown file.\n";
    const char* test_file = "./xmd_test.md";
    
    FILE* f = fopen(test_file, "w");
    assert(f != NULL);
    fprintf(f, "%s", test_content);
    fclose(f);
    
    // Test process command execution
    {
        char* argv[] = {"xmd", "process", (char*)test_file};
        int argc = 3;
        
        cli_context* ctx = cli_init(argc, argv);
        assert(ctx != NULL);
        assert(ctx->args != NULL);
        assert(ctx->args->command == CLI_CMD_PROCESS);
        
        // Note: Actual execution would depend on XMD processor being available
        // For now, just test that CLI context is set up correctly
        
        cli_cleanup(ctx);
    }
    
    // Test validate command execution
    {
        char* argv[] = {"xmd", "validate", (char*)test_file};
        int argc = 3;
        
        cli_context* ctx = cli_init(argc, argv);
        assert(ctx != NULL);
        assert(ctx->args != NULL);
        assert(ctx->args->command == CLI_CMD_VALIDATE);
        
        cli_cleanup(ctx);
    }
    
    // Cleanup test file
    unlink(test_file);
    
    printf("✓ CLI execution tests passed\n");
}

/**
 * @brief Test configuration system
 */
static void test_configuration_system(void) {
    printf("Testing configuration system...\n");
    
    // Test configuration creation
    xmd_config* config = config_create();
    assert(config != NULL);
    assert(!config->loaded);
    assert(config->value_count == 0);
    
    // Test setting and getting values
    {
        config_value* str_val = malloc(sizeof(config_value));
        str_val->type = CONFIG_STRING;
        str_val->data.string_val = strdup("test_value");
        
        assert(config_set(config, "test_key", str_val) == 0);
        assert(config->value_count == 1);
        
        config_value* retrieved = config_get(config, "test_key");
        assert(retrieved != NULL);
        assert(retrieved->type == CONFIG_STRING);
        assert(strcmp(retrieved->data.string_val, "test_value") == 0);
        
        // Test non-existent key
        config_value* missing = config_get(config, "missing_key");
        assert(missing == NULL);
    }
    
    // Test integer values
    {
        config_value* int_val = malloc(sizeof(config_value));
        int_val->type = CONFIG_INTEGER;
        int_val->data.integer_val = 42;
        
        assert(config_set(config, "int_key", int_val) == 0);
        
        config_value* retrieved = config_get(config, "int_key");
        assert(retrieved != NULL);
        assert(retrieved->type == CONFIG_INTEGER);
        assert(retrieved->data.integer_val == 42);
    }
    
    // Test boolean values
    {
        config_value* bool_val = malloc(sizeof(config_value));
        bool_val->type = CONFIG_BOOLEAN;
        bool_val->data.boolean_val = true;
        
        assert(config_set(config, "bool_key", bool_val) == 0);
        
        config_value* retrieved = config_get(config, "bool_key");
        assert(retrieved != NULL);
        assert(retrieved->type == CONFIG_BOOLEAN);
        assert(retrieved->data.boolean_val == true);
    }
    
    // Test configuration validation
    assert(config_validate(config) == 0);
    
    config_destroy(config);
    
    printf("✓ Configuration system tests passed\n");
}

/**
 * @brief Test plugin system
 */
static void test_plugin_system(void) {
    printf("Testing plugin system...\n");
    
    // Test plugin manager creation
    plugin_manager* manager = plugin_manager_create();
    assert(manager != NULL);
    assert(manager->plugin_count == 0);
    assert(manager->plugins != NULL);
    
    // Test plugin listing (should be empty initially)
    {
        char** plugin_names = NULL;
        size_t count = 0;
        
        assert(plugin_list(manager, &plugin_names, &count) == 0);
        assert(count == 0);
        assert(plugin_names == NULL);
    }
    
    // Test loading non-existent plugin (should fail gracefully)
    {
        int result = plugin_load(manager, "/nonexistent/plugin.so");
        assert(result == -1); // Should fail
    }
    
    // Test unloading non-existent plugin (should fail gracefully)
    {
        int result = plugin_unload(manager, "nonexistent");
        assert(result == -1); // Should fail
    }
    
    plugin_manager_destroy(manager);
    
    printf("✓ Plugin system tests passed\n");
}

/**
 * @brief Test C API interface
 */
static void test_c_api(void) {
    printf("Testing C API interface...\n");
    
    // Test XMD initialization
    void* handle = xmd_init(NULL);
    assert(handle != NULL);
    
    // Test string processing
    {
        const char* test_input = "# Test\n\nThis is test content.";
        xmd_result* result = xmd_process_string(handle, test_input, strlen(test_input));
        
        assert(result != NULL);
        assert(result->error_code == 0);
        assert(result->output != NULL);
        assert(result->output_length > 0);
        assert(result->processing_time_ms >= 0);
        
        xmd_result_free(result);
    }
    
    // Test validation
    {
        const char* test_input = "# Valid Markdown\n\nThis is valid.";
        xmd_result* result = xmd_validate(handle, test_input, strlen(test_input));
        
        assert(result != NULL);
        assert(result->error_code == 0);
        
        xmd_result_free(result);
    }
    
    // Test configuration
    {
        assert(xmd_set_config(handle, "debug", "true") == 0);
        
        char* value = xmd_get_config(handle, "debug");
        assert(value != NULL);
        assert(strcmp(value, "true") == 0);
        
        free(value);
    }
    
    xmd_cleanup(handle);
    
    printf("✓ C API tests passed\n");
}

/**
 * @brief Test edge cases and error conditions
 */
static void test_edge_cases(void) {
    printf("Testing edge cases...\n");
    
    // Test NULL arguments
    assert(cli_parse_args(0, NULL) == NULL);
    assert(cli_init(0, NULL) == NULL);
    assert(config_create() != NULL); // Should work without arguments
    assert(plugin_manager_create() != NULL); // Should work without arguments
    
    // Test empty arguments
    {
        char* argv[] = {"xmd"};
        int argc = 1;
        
        cli_args* args = cli_parse_args(argc, argv);
        assert(args == NULL); // Should fail - no command specified
    }
    
    // Test configuration with NULL inputs
    {
        xmd_config* config = config_create();
        assert(config != NULL);
        
        assert(config_get(config, NULL) == NULL);
        assert(config_set(config, NULL, NULL) == -1);
        assert(config_load_file(config, NULL) == -1);
        
        config_destroy(config);
    }
    
    // Test plugin manager with NULL inputs
    {
        plugin_manager* manager = plugin_manager_create();
        assert(manager != NULL);
        
        assert(plugin_load(manager, NULL) == -1);
        assert(plugin_unload(manager, NULL) == -1);
        assert(plugin_process(manager, NULL, "input", NULL) == -1);
        
        plugin_manager_destroy(manager);
    }
    
    // Test C API with NULL inputs
    {
        void* handle = xmd_init(NULL);
        assert(handle != NULL); // Should work with NULL config
        xmd_cleanup(handle); // Clean up the handle
        
        assert(xmd_process_string(NULL, "input", 5) == NULL);
        assert(xmd_validate(NULL, "input", 5) == NULL);
        assert(xmd_set_config(NULL, "key", "value") == -1);
        assert(xmd_get_config(NULL, "key") == NULL);
    }
    
    printf("✓ Edge case tests passed\n");
}

/**
 * @brief Main test function
 */
int main(void) {
    printf("=== CLI System Tests ===\n");
    
    test_cli_argument_parsing();
    test_cli_execution();
    test_configuration_system();
    test_plugin_system();
    test_c_api();
    test_edge_cases();
    
    printf("\n✅ All CLI tests passed!\n");
    return 0;
}