/**
 * @file test_memory_free_safe.c
 * @brief Unit tests for memory_free_safe function
 * 
 * Tests the safe memory deallocation wrapper with various scenarios
 * including NULL pointers and double-free prevention.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../../include/utils.h"

/**
 * @brief Test memory_free_safe with valid pointer
 */
static void test_memory_free_safe_valid(void) {
    void* ptr = malloc(100);
    assert(ptr != NULL);
    
    memory_free_safe(&ptr);
    
    // Pointer should be set to NULL after free
    assert(ptr == NULL);
    printf("✓ test_memory_free_safe_valid\n");
}

/**
 * @brief Test memory_free_safe with NULL pointer
 */
static void test_memory_free_safe_null(void) {
    void* ptr = NULL;
    
    // Should handle NULL gracefully
    memory_free_safe(&ptr);
    
    assert(ptr == NULL);
    printf("✓ test_memory_free_safe_null\n");
}

/**
 * @brief Test memory_free_safe with NULL pointer argument
 */
static void test_memory_free_safe_null_arg(void) {
    // Should handle NULL argument gracefully
    memory_free_safe(NULL);
    
    printf("✓ test_memory_free_safe_null_arg\n");
}

/**
 * @brief Test memory_free_safe prevents double free
 */
static void test_memory_free_safe_double_free(void) {
    void* ptr = malloc(50);
    assert(ptr != NULL);
    
    // First free
    memory_free_safe(&ptr);
    assert(ptr == NULL);
    
    // Second free should be safe
    memory_free_safe(&ptr);
    assert(ptr == NULL);
    
    printf("✓ test_memory_free_safe_double_free\n");
}

/**
 * @brief Test memory_free_safe with multiple pointers
 */
static void test_memory_free_safe_multiple(void) {
    void* ptr1 = malloc(10);
    void* ptr2 = malloc(20);
    void* ptr3 = malloc(30);
    
    assert(ptr1 != NULL);
    assert(ptr2 != NULL);
    assert(ptr3 != NULL);
    
    memory_free_safe(&ptr1);
    memory_free_safe(&ptr2);
    memory_free_safe(&ptr3);
    
    assert(ptr1 == NULL);
    assert(ptr2 == NULL);
    assert(ptr3 == NULL);
    
    printf("✓ test_memory_free_safe_multiple\n");
}

/**
 * @brief Test memory_free_safe with array
 */
static void test_memory_free_safe_array(void) {
    int* arr = malloc(sizeof(int) * 100);
    assert(arr != NULL);
    
    // Initialize array
    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }
    
    void* ptr = arr;
    memory_free_safe(&ptr);
    
    assert(ptr == NULL);
    printf("✓ test_memory_free_safe_array\n");
}

/**
 * @brief Test memory_free_safe with struct
 */
static void test_memory_free_safe_struct(void) {
    typedef struct {
        int value;
        char* str;
    } TestStruct;
    
    TestStruct* s = malloc(sizeof(TestStruct));
    assert(s != NULL);
    
    s->value = 42;
    s->str = malloc(20);
    assert(s->str != NULL);
    
    // Free inner pointer first
    void* inner = s->str;
    memory_free_safe(&inner);
    
    // Then free struct
    void* outer = s;
    memory_free_safe(&outer);
    
    assert(inner == NULL);
    assert(outer == NULL);
    
    printf("✓ test_memory_free_safe_struct\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("Running memory_free_safe tests...\n");
    
    test_memory_free_safe_valid();
    test_memory_free_safe_null();
    test_memory_free_safe_null_arg();
    test_memory_free_safe_double_free();
    test_memory_free_safe_multiple();
    test_memory_free_safe_array();
    test_memory_free_safe_struct();
    
    printf("\nAll memory_free_safe tests passed!\n");
    return 0;
}
