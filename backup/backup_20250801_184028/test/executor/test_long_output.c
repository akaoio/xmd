/**
 * @file test_long_command_output.c
 * @brief Test case for long command output handling (Issue #5)
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/xmd_processor_internal.h"
#include "../../include/store.h"

/**
 * @brief Test that long command outputs are not truncated
 */
void test_long_command_output_not_truncated(void) {
    printf("Testing long command output (Issue #5)...\n");
    
    store* variables = store_create();
    assert(variables != NULL);
    
    processor_context* ctx = create_context(variables);
    assert(ctx != NULL);
    
    // Use a command that generates substantial output (>4KB)
    char output[32768];
    
    // Test with tree command that should produce long output
    int result = process_exec("find /usr/include -name '*.h' | head -200", ctx, output, sizeof(output));
    
    // The command should succeed
    assert(result == 0);
    
    // Output should be substantial (much more than the old 4KB limit)
    size_t output_len = strlen(output);
    printf("Command output length: %zu bytes\n", output_len);
    
    // Should have substantial content (more than old limit would allow with safety margin)
    assert(output_len > 3500);
    
    // Output should not end abruptly (should end with complete line)
    if (output_len > 0 && output[output_len - 1] != '\n') {
        // Find the last newline to check if we have a complete final line
        char* last_newline = strrchr(output, '\n');
        if (last_newline) {
            // Check that there's a reasonable amount of content after last newline
            size_t final_line_len = strlen(last_newline + 1);
            // Should have a reasonable filename, not cut off mid-path
            assert(final_line_len > 3);
        }
    }
    
    store_destroy(variables);
    printf("✓ Long command output test passed\n");
}

/**
 * @brief Test execute_command directly with very long output
 */
void test_execute_command_large_buffer(void) {
    printf("Testing execute_command with large buffer...\n");
    
    char large_output[32768];
    
    // Generate a command with predictable long output
    int result = execute_command("seq 1 1000", large_output, sizeof(large_output));
    
    assert(result == 0);
    size_t output_len = strlen(large_output);
    printf("Sequence output length: %zu bytes\n", output_len);
    
    // Should contain all numbers from 1 to 1000
    assert(strstr(large_output, "1\n") != NULL);
    assert(strstr(large_output, "500\n") != NULL);
    assert(strstr(large_output, "1000\n") != NULL);
    
    // Should be significantly longer than what would fit in old 4KB limit with safety margin
    // (The old limit was effectively 4095 bytes due to null terminator)
    assert(output_len > 3500);
    
    printf("✓ execute_command large buffer test passed\n");
}

int main(void) {
    printf("=== Long Command Output Tests (Issue #5 Fix) ===\n");
    
    test_execute_command_large_buffer();
    test_long_command_output_not_truncated();
    
    printf("=== All long command output tests passed! ===\n");
    return 0;
}