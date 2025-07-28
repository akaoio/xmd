/**
 * @file test_truncate_fix.c
 * @brief Test XMD processor truncation fix for large outputs
 * @author XMD Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/xmd_processor_internal.h"
#include "../../include/store.h"
#include "../../include/variable.h"

/**
 * @brief Test direct exec with large output
 */
void test_direct_exec_large_output() {
    printf("Testing direct exec with large output...\n");
    
    const char* input = "<!-- xmd:exec find /usr -name '*.h' 2>/dev/null | head -1000 -->";
    store* vars = store_create();
    
    char* result = process_xmd_content(input, vars);
    assert(result != NULL);
    
    // Check that output contains multiple lines
    int line_count = 0;
    char* line = strtok(result, "\n");
    while (line) {
        line_count++;
        line = strtok(NULL, "\n");
    }
    
    // Should have many lines of output
    assert(line_count > 100);
    
    free(result);
    store_destroy(vars);
    
    printf("✓ Direct exec large output test passed\n");
}

/**
 * @brief Test set variable from exec with large output
 */
void test_set_var_exec_large_output() {
    printf("Testing set var from exec with large output...\n");
    
    const char* input = "<!-- xmd:set files = exec find /usr -name '*.h' 2>/dev/null | head -1000 -->\n{{files}}";
    store* vars = store_create();
    
    char* result = process_xmd_content(input, vars);
    assert(result != NULL);
    
    // Check that output contains multiple lines
    int line_count = 0;
    char* temp = strdup(result);
    char* line = strtok(temp, "\n");
    while (line) {
        line_count++;
        line = strtok(NULL, "\n");
    }
    free(temp);
    
    // Should have many lines of output
    assert(line_count > 100);
    
    // Check that variable was set
    variable* var = store_get(vars, "files");
    assert(var != NULL);
    
    free(result);
    store_destroy(vars);
    
    printf("✓ Set var exec large output test passed\n");
}

/**
 * @brief Test print function with large variable
 */
void test_print_large_variable() {
    printf("Testing print function with large variable...\n");
    
    const char* input = "<!-- xmd:set data = exec find /usr -name '*.h' 2>/dev/null | head -1000 --><!-- xmd:print(data) -->";
    store* vars = store_create();
    
    char* result = process_xmd_content(input, vars);
    assert(result != NULL);
    
    // Check that output contains multiple lines
    int line_count = 0;
    char* temp = strdup(result);
    char* line = strtok(temp, "\n");
    while (line) {
        line_count++;
        line = strtok(NULL, "\n");
    }
    free(temp);
    
    // Should have many lines of output
    assert(line_count > 100);
    
    free(result);
    store_destroy(vars);
    
    printf("✓ Print large variable test passed\n");
}

/**
 * @brief Main test function
 */
int main() {
    printf("=== XMD Large Output Tests ===\n");
    
    test_direct_exec_large_output();
    test_set_var_exec_large_output();
    test_print_large_variable();
    
    printf("\nAll large output tests passed! ✓\n");
    return 0;
}