/**
 * @file test_shell_transformation.c
 * @brief Test shell-style function call transformation
 * @author XMD Team
 * @date 2025-07-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Function declaration
char* ast_transform_shell_function_call(const char* content);

/**
 * @brief Test shell-style function call transformation
 */
void test_shell_function_transformation() {
    printf("Testing shell-style function call transformation...\n");
    
    // Test simple function call
    char* result = ast_transform_shell_function_call("add 5 3");
    assert(result != NULL);
    printf("  add 5 3 -> %s\n", result);
    assert(strcmp(result, "add(5, 3)") == 0);
    free(result);
    
    // Test function with no arguments
    result = ast_transform_shell_function_call("getValue");
    assert(result != NULL);
    printf("  getValue -> %s\n", result);
    assert(strcmp(result, "getValue()") == 0);
    free(result);
    
    // Test function with quoted arguments
    result = ast_transform_shell_function_call("greet \"John Doe\" world");
    assert(result != NULL);
    printf("  greet \"John Doe\" world -> %s\n", result);
    assert(strcmp(result, "greet(\"John Doe\", world)") == 0);
    free(result);
    
    // Test function with single quoted arguments
    result = ast_transform_shell_function_call("display 'Hello World' file.txt");
    assert(result != NULL);
    printf("  display 'Hello World' file.txt -> %s\n", result);
    assert(strcmp(result, "display('Hello World', file.txt)") == 0);
    free(result);
    
    // Test non-function (should return NULL)
    result = ast_transform_shell_function_call("123 invalid");
    assert(result == NULL);
    printf("  123 invalid -> NULL (correct)\n");
    
    // Test empty input
    result = ast_transform_shell_function_call("");
    assert(result == NULL);
    printf("  (empty) -> NULL (correct)\n");
    
    // Test single word function
    result = ast_transform_shell_function_call("process");
    assert(result != NULL);
    printf("  process -> %s\n", result);
    assert(strcmp(result, "process()") == 0);
    free(result);
    
    printf("✓ Shell function transformation passed\n");
}

int main() {
    printf("=== Shell Function Transformation Tests ===\n");
    
    test_shell_function_transformation();
    
    printf("=== All transformation tests passed! ===\n");
    return 0;
}