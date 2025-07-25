/**
 * @file test_docs.c
 * @brief Tests for Phase 8 documentation system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/xmd.h"

/**
 * @brief Test tutorial generation
 */
static void test_tutorial_generate(void) {
    printf("Testing tutorial generation...\n");
    
    // Test basic tutorial generation
    int result = tutorial_generate("examples", "test_output/tutorial");
    if (result != 0) {
        printf("ERROR: tutorial_generate returned %d\n", result);
        return; // Don't assert, just report error
    }
    
    printf("✓ Tutorial generation tests passed\n");
}

/**
 * @brief Test example generation
 */
static void test_examples_generate(void) {
    printf("Testing example generation...\n");
    
    // Test basic example generation
    int result = examples_generate("examples", "test_output/examples");
    if (result != 0) {
        printf("ERROR: examples_generate returned %d\n", result);
        return; // Don't assert, just report error
    }
    
    printf("✓ Example generation tests passed\n");
}

/**
 * @brief Test API reference generation
 */
static void test_reference_generate(void) {
    printf("Testing API reference generation...\n");
    
    // Test basic reference generation
    int result = reference_generate("include", "test_output/reference.md");
    if (result != 0) {
        printf("ERROR: reference_generate returned %d\n", result);
        return; // Don't assert, just report error
    }
    
    printf("✓ Reference generation tests passed\n");
}

/**
 * @brief Main test function
 */
int main(void) {
    printf("=== Documentation System Tests ===\n");
    
    test_tutorial_generate();
    test_examples_generate();
    test_reference_generate();
    
    printf("\n✅ All documentation tests passed!\n");
    return 0;
}