/**
 * @file test_memory_allocate.c
 * @brief Unit tests for memory_allocate function
 * 
 * Tests the safe memory allocation wrapper with various sizes
 * and edge cases.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "../../../src/utils/memory/memory_allocate/memory_allocate.h"

/**
 * @brief Test memory_allocate with normal size
 */
static void test_memory_allocate_normal(void) {
    void* ptr = memory_allocate(100);
    
    assert(ptr != NULL);
    
    // Test that memory is writable
    memset(ptr, 0, 100);
    
    free(ptr);
    printf("✓ test_memory_allocate_normal\n");
}

/**
 * @brief Test memory_allocate with zero size
 */
static void test_memory_allocate_zero(void) {
    void* ptr = memory_allocate(0);
    
    // Zero allocation should return NULL
    assert(ptr == NULL);
    printf("✓ test_memory_allocate_zero\n");
}

/**
 * @brief Test memory_allocate with small size
 */
static void test_memory_allocate_small(void) {
    void* ptr = memory_allocate(1);
    
    assert(ptr != NULL);
    
    // Test single byte write
    *(char*)ptr = 'A';
    assert(*(char*)ptr == 'A');
    
    free(ptr);
    printf("✓ test_memory_allocate_small\n");
}

/**
 * @brief Test memory_allocate with large size
 */
static void test_memory_allocate_large(void) {
    size_t size = 1024 * 1024; // 1MB
    void* ptr = memory_allocate(size);
    
    assert(ptr != NULL);
    
    // Test that memory is writable
    memset(ptr, 0xFF, size);
    
    free(ptr);
    printf("✓ test_memory_allocate_large\n");
}

/**
 * @brief Test memory_allocate multiple allocations
 */
static void test_memory_allocate_multiple(void) {
    void* ptrs[10];
    
    // Allocate multiple blocks
    for (int i = 0; i < 10; i++) {
        ptrs[i] = memory_allocate((i + 1) * 10);
        assert(ptrs[i] != NULL);
    }
    
    // Verify all pointers are different
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            assert(ptrs[i] != ptrs[j]);
        }
    }
    
    // Free all blocks
    for (int i = 0; i < 10; i++) {
        free(ptrs[i]);
    }
    
    printf("✓ test_memory_allocate_multiple\n");
}

/**
 * @brief Test memory_allocate alignment
 */
static void test_memory_allocate_alignment(void) {
    // Test various sizes for proper alignment
    size_t sizes[] = {1, 7, 8, 15, 16, 31, 32, 63, 64};
    
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        void* ptr = memory_allocate(sizes[i]);
        assert(ptr != NULL);
        
        // Check pointer alignment (should be aligned for any type)
        assert(((uintptr_t)ptr % sizeof(void*)) == 0);
        
        free(ptr);
    }
    
    printf("✓ test_memory_allocate_alignment\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("Running memory_allocate tests...\n");
    
    test_memory_allocate_normal();
    test_memory_allocate_zero();
    test_memory_allocate_small();
    test_memory_allocate_large();
    test_memory_allocate_multiple();
    test_memory_allocate_alignment();
    
    printf("\nAll memory_allocate tests passed!\n");
    return 0;
}
