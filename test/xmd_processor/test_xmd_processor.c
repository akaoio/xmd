/**
 * @file test_xmd_processor.c
 * @brief Comprehensive test suite for XMD processor
 * @author XMD Team
 * @date 2025-07-26
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/store.h"
#include "../../include/variable.h"

// External functions from unified processor
char* process_xmd_content(const char* input, store* variables);
int process_xmd_directive(const char* directive, store* var_store, char* output, size_t output_size);

/**
 * @brief Test basic variable setting and substitution
 */
void test_basic_variable_substitution(void) {
    printf("Testing basic variable substitution...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* input = 
        "<!-- xmd:set name=\"World\" -->\n"
        "Hello {{name}}!\n";
    
    char* result = process_xmd_content(input, vars);
    assert(result != NULL);
    assert(strstr(result, "Hello World!") != NULL);
    assert(strstr(result, "xmd:set") == NULL); // Directive should be removed
    
    free(result);
    store_destroy(vars);
    printf("✅ Basic variable substitution test passed\n");
}

/**
 * @brief Test if/elif/else conditional logic
 */
void test_conditional_logic(void) {
    printf("Testing conditional logic...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    // Test 1: if condition true
    const char* input1 = 
        "<!-- xmd:set role=\"admin\" -->\n"
        "<!-- xmd:if role == \"admin\" -->\n"
        "Admin access granted\n"
        "<!-- xmd:elif role == \"user\" -->\n"
        "User access\n"
        "<!-- xmd:else -->\n"
        "Guest access\n"
        "<!-- xmd:endif -->\n";
    
    char* result1 = process_xmd_content(input1, vars);
    assert(result1 != NULL);
    assert(strstr(result1, "Admin access granted") != NULL);
    assert(strstr(result1, "User access") == NULL);
    assert(strstr(result1, "Guest access") == NULL);
    
    free(result1);
    
    // Test 2: elif condition true
    variable* role_var = variable_create_string("user");
    store_set(vars, "role", role_var);
    variable_unref(role_var);
    
    char* result2 = process_xmd_content(input1, vars);
    assert(result2 != NULL);
    assert(strstr(result2, "Admin access granted") == NULL);
    assert(strstr(result2, "User access") != NULL);
    assert(strstr(result2, "Guest access") == NULL);
    
    free(result2);
    
    // Test 3: else condition
    role_var = variable_create_string("unknown");
    store_set(vars, "role", role_var);
    variable_unref(role_var);
    
    char* result3 = process_xmd_content(input1, vars);
    assert(result3 != NULL);
    assert(strstr(result3, "Admin access granted") == NULL);
    assert(strstr(result3, "User access") == NULL);
    assert(strstr(result3, "Guest access") != NULL);
    
    free(result3);
    store_destroy(vars);
    printf("✅ Conditional logic test passed\n");
}

/**
 * @brief Test multiline directive support
 */
void test_multiline_directives(void) {
    printf("Testing multiline directives...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* input = 
        "<!-- xmd:\n"
        "set project=\"XMD\"\n"
        "set version=\"1.0\"\n"
        "set status=\"unified\"\n"
        "-->\n"
        "Project: {{project}} v{{version}}\n"
        "Status: {{status}}\n";
    
    char* result = process_xmd_content(input, vars);
    assert(result != NULL);
    assert(strstr(result, "Project: XMD v1.0") != NULL);
    assert(strstr(result, "Status: unified") != NULL);
    
    free(result);
    store_destroy(vars);
    printf("✅ Multiline directives test passed\n");
}

/**
 * @brief Test nested conditional statements
 */
void test_nested_conditionals(void) {
    printf("Testing nested conditionals...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* input = 
        "<!-- xmd:set dept=\"engineering\" -->\n"
        "<!-- xmd:set level=\"senior\" -->\n"
        "<!-- xmd:if dept == \"engineering\" -->\n"
        "Engineering Department\n"
        "  <!-- xmd:if level == \"senior\" -->\n"
        "  Senior Engineer\n"
        "  <!-- xmd:elif level == \"junior\" -->\n"
        "  Junior Engineer\n"
        "  <!-- xmd:endif -->\n"
        "<!-- xmd:elif dept == \"marketing\" -->\n"
        "Marketing Department\n"
        "<!-- xmd:else -->\n"
        "Unknown Department\n"
        "<!-- xmd:endif -->\n";
    
    char* result = process_xmd_content(input, vars);
    assert(result != NULL);
    assert(strstr(result, "Engineering Department") != NULL);
    assert(strstr(result, "Senior Engineer") != NULL);
    assert(strstr(result, "Junior Engineer") == NULL);
    assert(strstr(result, "Marketing Department") == NULL);
    
    free(result);
    store_destroy(vars);
    printf("✅ Nested conditionals test passed\n");
}

/**
 * @brief Test command execution directive
 */
void test_command_execution(void) {
    printf("Testing command execution...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* input = "<!-- xmd:exec echo \"Hello from command\" -->\n";
    
    char* result = process_xmd_content(input, vars);
    assert(result != NULL);
    assert(strstr(result, "Hello from command") != NULL);
    
    free(result);
    store_destroy(vars);
    printf("✅ Command execution test passed\n");
}

/**
 * @brief Test variable substitution edge cases
 */
void test_variable_edge_cases(void) {
    printf("Testing variable edge cases...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    // Test undefined variable
    const char* input1 = "Hello {{undefined_var}}!";
    char* result1 = process_xmd_content(input1, vars);
    assert(result1 != NULL);
    assert(strstr(result1, "Hello !") != NULL); // Should substitute with empty string
    
    free(result1);
    
    // Test variable with special characters
    variable* special_var = variable_create_string("test & <script>");
    store_set(vars, "special", special_var);
    variable_unref(special_var);
    
    const char* input2 = "Value: {{special}}";
    char* result2 = process_xmd_content(input2, vars);
    assert(result2 != NULL);
    assert(strstr(result2, "test & <script>") != NULL);
    
    free(result2);
    store_destroy(vars);
    printf("✅ Variable edge cases test passed\n");
}

/**
 * @brief Test malformed XMD directives
 */
void test_malformed_directives(void) {
    printf("Testing malformed directives...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    // Test unclosed comment
    const char* input1 = "<!-- xmd:set name=\"test\"\nHello {{name}}";
    char* result1 = process_xmd_content(input1, vars);
    assert(result1 != NULL);
    // Should handle gracefully, copying the malformed comment as-is
    
    free(result1);
    
    // Test malformed if without endif
    const char* input2 = 
        "<!-- xmd:if true -->\n"
        "This should appear\n"
        "No endif\n";
    char* result2 = process_xmd_content(input2, vars);
    assert(result2 != NULL);
    // Should handle gracefully
    
    free(result2);
    store_destroy(vars);
    printf("✅ Malformed directives test passed\n");
}

/**
 * @brief Test complete workflow integration
 */
void test_complete_workflow(void) {
    printf("Testing complete workflow...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* input = 
        "# XMD Processor Test\n\n"
        "<!-- xmd:\n"
        "set user=\"Alice\"\n"
        "set role=\"admin\"\n"
        "set project=\"XMD Parser\"\n"
        "-->\n"
        "Welcome {{user}}!\n\n"
        "<!-- xmd:if role == \"admin\" -->\n"
        "## Admin Dashboard\n"
        "Project: {{project}}\n"
        "<!-- xmd:exec echo \"System status: OK\" -->\n"
        "<!-- xmd:elif role == \"user\" -->\n"
        "## User Dashboard\n"
        "Limited access for {{user}}\n"
        "<!-- xmd:else -->\n"
        "## Guest Access\n"
        "Please log in\n"
        "<!-- xmd:endif -->\n\n"
        "Thank you for using {{project}}!\n";
    
    char* result = process_xmd_content(input, vars);
    assert(result != NULL);
    
    // Verify all expected content is present
    assert(strstr(result, "Welcome Alice!") != NULL);
    assert(strstr(result, "Admin Dashboard") != NULL);
    assert(strstr(result, "Project: XMD Parser") != NULL);
    assert(strstr(result, "System status: OK") != NULL);
    assert(strstr(result, "Thank you for using XMD Parser!") != NULL);
    
    // Verify excluded content is not present
    assert(strstr(result, "User Dashboard") == NULL);
    assert(strstr(result, "Guest Access") == NULL);
    assert(strstr(result, "xmd:") == NULL); // No directives should remain
    
    free(result);
    store_destroy(vars);
    printf("✅ Complete workflow test passed\n");
}

/**
 * @brief Test performance with large input
 */
void test_performance(void) {
    printf("Testing performance with large input...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    // Create a large input with many variables and conditionals
    char* large_input = malloc(10000);
    strcpy(large_input, "<!-- xmd:set counter=\"0\" -->\n");
    
    for (int i = 0; i < 100; i++) {
        char line[100];
        snprintf(line, sizeof(line), 
                "Line %d: {{counter}} <!-- xmd:if counter == \"0\" -->Zero<!-- xmd:endif -->\n", i);
        strcat(large_input, line);
    }
    
    char* result = process_xmd_content(large_input, vars);
    assert(result != NULL);
    assert(strlen(result) > 1000); // Should produce substantial output
    
    free(large_input);
    free(result);
    store_destroy(vars);
    printf("✅ Performance test passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("🚀 Starting XMD Processor Test Suite\n");
    printf("=====================================\n\n");
    
    test_basic_variable_substitution();
    test_conditional_logic();
    test_multiline_directives();
    test_nested_conditionals();
    test_command_execution();
    test_variable_edge_cases();
    test_malformed_directives();
    test_complete_workflow();
    test_performance();
    
    printf("\n🎉 All XMD Processor tests passed!\n");
    printf("Total: 9 test suites completed successfully\n");
    
    return 0;
}
