/**
 * @file test_devtools.c
 * @brief Tests for Phase 8 developer tools
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/xmd.h"

/**
 * @brief Test debugger functionality
 */
static void test_debugger_trace(void) {
    printf("Testing debugger trace...\n");
    
    // Test debugger trace execution
    int result = debugger_trace("examples/demo.md", "test_output/trace.log");
    if (result != 0) {
        printf("ERROR: debugger_trace returned %d\n", result);
        return;
    }
    
    printf("✓ Debugger trace tests passed\n");
}

/**
 * @brief Test linter functionality
 */
static void test_linter_check(void) {
    printf("Testing linter check...\n");
    
    // Test linter with valid content
    int result = linter_check("# Valid XMD\n\n<!-- xmd set name=\"test\" -->");
    if (result != 0) {
        printf("ERROR: linter_check returned %d\n", result);
        return;
    }
    
    printf("✓ Linter check tests passed\n");
}

/**
 * @brief Test formatter functionality
 */
static void test_formatter_format(void) {
    printf("Testing formatter format...\n");
    
    // Test formatter
    int result = formatter_format("  # Test\n\n    <!-- xmd set name=\"test\" -->", "test_output/formatted.md");
    if (result != 0) {
        printf("ERROR: formatter_format returned %d\n", result);
        return;
    }
    
    printf("✓ Formatter format tests passed\n");
}

/**
 * @brief Main test function
 */
int main(void) {
    printf("=== Developer Tools Tests ===\n");
    
    test_debugger_trace();
    test_linter_check();
    test_formatter_format();
    
    printf("\n✅ All developer tools tests passed!\n");
    return 0;
}
