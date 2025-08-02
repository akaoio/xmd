/**
 * @file test_user_functions_minimal.c
 * @brief Minimal test for user-defined functions 
 * @author XMD Team
 * @date 2025-07-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/ast_node.h"

/**
 * @brief Test function definition creation only
 */
void test_minimal_function_creation() {
    printf("Testing minimal function definition creation...\n");
    
    source_location loc = {1, 1, "test.xmd"};
    
    // Test if ast_create_function_def exists and works
    ast_node* func_def = ast_create_function_def("test_func", loc);
    if (func_def == NULL) {
        printf("❌ ast_create_function_def returned NULL\n");
        return;
    }
    
    // Check basic properties
    if (func_def->type != AST_FUNCTION_DEF) {
        printf("❌ Wrong AST node type: %d\n", func_def->type);
        ast_free(func_def);
        return;
    }
    
    if (strcmp(func_def->data.function_def.name, "test_func") != 0) {
        printf("❌ Wrong function name: %s\n", func_def->data.function_def.name);
        ast_free(func_def);
        return;
    }
    
    printf("✓ Basic function definition creation passed\n");
    ast_free(func_def);
}

int main() {
    printf("=== Minimal User-Defined Functions Test ===\n");
    
    test_minimal_function_creation();
    
    printf("=== Minimal test completed ===\n");
    return 0;
}