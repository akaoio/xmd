/**
 * @file test_c_api_integration.c
 * @brief Integration test for C API layer
 * @author XMD Team
 * @date 2025-07-27
 * 
 * This test ensures the C API layer properly integrates with the core processor.
 * It would have caught the stub implementation issue.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/cli.h"

/**
 * @brief Test xmd exec through C API
 */
void test_exec_through_c_api(void) {
    printf("Testing xmd exec through C API layer...\n");
    
    // Initialize XMD
    void* handle = xmd_init(NULL);
    assert(handle != NULL);
    
    // Test simple exec command
    const char* input = "<!-- xmd exec echo \"Hello from C API\" -->\n";
    xmd_result* result = xmd_process_string(handle, input, strlen(input));
    
    assert(result != NULL);
    assert(result->error_code == 0);
    assert(result->output != NULL);
    
    // The critical test: output should contain the executed command's result
    // NOT just the wrapped input!
    assert(strstr(result->output, "Hello from C API") != NULL);
    assert(strstr(result->output, "<!-- xmd exec") == NULL); // Directive should be processed
    
    printf("Output: %s\n", result->output);
    
    xmd_result_free(result);
    xmd_cleanup(handle);
    
    printf("✅ C API exec test passed\n");
}

/**
 * @brief Test variable processing through C API
 */
void test_variables_through_c_api(void) {
    printf("Testing variables through C API layer...\n");
    
    void* handle = xmd_init(NULL);
    assert(handle != NULL);
    
    // Test with xmd set directive instead
    const char* input = "<!-- xmd set name=\"TestUser\" -->\nHello {{name}}!";
    xmd_result* result = xmd_process_string(handle, input, strlen(input));
    
    assert(result != NULL);
    assert(result->error_code == 0);
    assert(strstr(result->output, "Hello TestUser!") != NULL);
    assert(strstr(result->output, "xmd set") == NULL); // Directive should be processed
    
    xmd_result_free(result);
    xmd_cleanup(handle);
    
    printf("✅ C API variable test passed\n");
}

/**
 * @brief Test that stub implementation fails this test
 */
void test_stub_detection(void) {
    printf("Testing stub implementation detection...\n");
    
    void* handle = xmd_init(NULL);
    assert(handle != NULL);
    
    const char* input = "Test content";
    xmd_result* result = xmd_process_string(handle, input, strlen(input));
    
    assert(result != NULL);
    
    // A stub that just wraps with comments would produce this:
    const char* stub_output = "<!-- XMD Processed Content -->\nTest content\n<!-- End XMD Processing -->";
    
    // Our output should NOT be the stub output
    if (strcmp(result->output, stub_output) == 0) {
        fprintf(stderr, "❌ ERROR: C API is using stub implementation!\n");
        assert(0); // Force test failure
    }
    
    xmd_result_free(result);
    xmd_cleanup(handle);
    
    printf("✅ Stub detection test passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("\n🔍 C API Integration Test Suite\n");
    printf("================================\n");
    printf("This test verifies the C API layer properly integrates with core XMD.\n\n");
    
    test_exec_through_c_api();
    test_variables_through_c_api();
    test_stub_detection();
    
    printf("\n✅ All C API integration tests passed!\n");
    printf("The C API is properly connected to the core processor.\n");
    
    return 0;
}
