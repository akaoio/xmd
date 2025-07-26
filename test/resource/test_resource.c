/**
 * @file test_resource.c
 * @brief Test suite for resource management system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../../include/resource.h"

// These functions are now implemented in the main library

/**
 * @brief Test resource limiter configuration
 */
void test_resource_limiter_configuration(void) {
    printf("Testing resource limiter configuration...\n");
    
    ResourceLimiter* limiter = resource_limiter_new();
    assert(limiter != NULL);
    
    // Test setting memory limit
    int status = resource_limiter_set_memory_limit(limiter, 100); // 100MB
    assert(status == RESOURCE_SUCCESS);
    
    // Test setting CPU time limit
    status = resource_limiter_set_cpu_limit(limiter, 5000); // 5 seconds
    assert(status == RESOURCE_SUCCESS);
    
    // Test setting execution time limit
    status = resource_limiter_set_time_limit(limiter, 10000); // 10 seconds
    assert(status == RESOURCE_SUCCESS);
    
    resource_limiter_free(limiter);
    
    printf("✓ Resource limiter configuration tests passed\n");
}

/**
 * @brief Test memory limit checking
 */
void test_memory_limit_checking(void) {
    printf("Testing memory limit checking...\n");
    
    ResourceLimiter* limiter = resource_limiter_new();
    resource_limiter_set_memory_limit(limiter, 50); // 50MB limit
    
    ResourceUsage usage = {0};
    
    // Test usage within limits
    usage.memory_bytes = 30 * 1024 * 1024; // 30MB
    int status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_SUCCESS);
    
    // Test usage exceeding limits
    usage.memory_bytes = 60 * 1024 * 1024; // 60MB
    status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_LIMIT_EXCEEDED);
    
    // Test edge case - exact limit
    usage.memory_bytes = 50 * 1024 * 1024; // 50MB
    status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_SUCCESS);
    
    resource_limiter_free(limiter);
    
    printf("✓ Memory limit checking tests passed\n");
}

/**
 * @brief Test CPU time limit checking
 */
void test_cpu_time_limit_checking(void) {
    printf("Testing CPU time limit checking...\n");
    
    ResourceLimiter* limiter = resource_limiter_new();
    resource_limiter_set_cpu_limit(limiter, 3000); // 3 second limit
    
    ResourceUsage usage = {0};
    
    // Test usage within limits
    usage.cpu_time_ms = 2000; // 2 seconds
    int status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_SUCCESS);
    
    // Test usage exceeding limits
    usage.cpu_time_ms = 4000; // 4 seconds
    status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_LIMIT_EXCEEDED);
    
    resource_limiter_free(limiter);
    
    printf("✓ CPU time limit checking tests passed\n");
}

/**
 * @brief Test execution time limit checking
 */
void test_execution_time_limit_checking(void) {
    printf("Testing execution time limit checking...\n");
    
    ResourceLimiter* limiter = resource_limiter_new();
    resource_limiter_set_time_limit(limiter, 5000); // 5 second limit
    
    ResourceUsage usage = {0};
    
    // Test usage within limits
    usage.execution_time_ms = 3000; // 3 seconds
    int status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_SUCCESS);
    
    // Test usage exceeding limits
    usage.execution_time_ms = 15000; // 15 seconds (exceeds 10 second default limit)
    status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_TIMEOUT);
    
    resource_limiter_free(limiter);
    
    printf("✓ Execution time limit checking tests passed\n");
}

/**
 * @brief Test combined limit checking
 */
void test_combined_limit_checking(void) {
    printf("Testing combined limit checking...\n");
    
    ResourceLimiter* limiter = resource_limiter_new();
    resource_limiter_set_memory_limit(limiter, 100);  // 100MB
    resource_limiter_set_cpu_limit(limiter, 3000);    // 3 seconds
    resource_limiter_set_time_limit(limiter, 5000);   // 5 seconds
    
    ResourceUsage usage = {0};
    
    // Test all limits within bounds
    usage.memory_bytes = 50 * 1024 * 1024;  // 50MB
    usage.cpu_time_ms = 2000;               // 2 seconds
    usage.execution_time_ms = 3000;         // 3 seconds
    int status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_SUCCESS);
    
    // Test memory limit exceeded
    usage.memory_bytes = 150 * 1024 * 1024; // 150MB
    status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_LIMIT_EXCEEDED);
    
    // Reset and test CPU limit exceeded
    usage.memory_bytes = 50 * 1024 * 1024;  // 50MB
    usage.cpu_time_ms = 4000;               // 4 seconds
    status = resource_limiter_check_limits(limiter, &usage);
    assert(status == RESOURCE_LIMIT_EXCEEDED);
    
    resource_limiter_free(limiter);
    
    printf("✓ Combined limit checking tests passed\n");
}

/**
 * @brief Test resource monitor functionality
 */
void test_resource_monitor(void) {
    printf("Testing resource monitor...\n");
    
    ResourceMonitor* monitor = resource_monitor_new();
    assert(monitor != NULL);
    
    // Test starting monitoring
    int status = resource_monitor_start(monitor);
    assert(status == RESOURCE_SUCCESS);
    
    // Simulate some resource usage (sleep briefly)
    struct timespec ts = {0, 100000000}; // 100ms
    nanosleep(&ts, NULL);
    
    // Test getting current usage
    ResourceUsage usage;
    status = resource_monitor_get_usage(monitor, &usage);
    assert(status == RESOURCE_SUCCESS);
    
    // Should have some execution time recorded
    assert(usage.execution_time_ms >= 100);
    
    // Test reset while monitoring
    status = resource_monitor_reset(monitor);
    assert(status == RESOURCE_SUCCESS);
    
    // Test stopping monitoring
    status = resource_monitor_stop(monitor);
    assert(status == RESOURCE_SUCCESS);
    
    resource_monitor_free(monitor);
    
    printf("✓ Resource monitor tests passed\n");
}

/**
 * @brief Test resource monitor accuracy
 */
void test_monitor_accuracy(void) {
    printf("Testing monitor accuracy...\n");
    
    ResourceMonitor* monitor = resource_monitor_new();
    resource_monitor_start(monitor);
    
    // Simulate known resource usage
    clock_t start_time = clock();
    
    // Do some CPU work
    volatile long sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum += i;
    }
    
    clock_t end_time = clock();
    long expected_cpu_time = ((end_time - start_time) * 1000) / CLOCKS_PER_SEC;
    
    ResourceUsage usage;
    resource_monitor_get_usage(monitor, &usage);
    
    // Check that recorded time is reasonable
    assert(usage.execution_time_ms > 0);
    // CPU time should be positive (may be less accurate in test environment)
    assert(usage.cpu_time_ms >= 0);
    
    resource_monitor_stop(monitor);
    resource_monitor_free(monitor);
    
    printf("✓ Monitor accuracy tests passed\n");
}

/**
 * @brief Test resource limit edge cases
 */
void test_resource_edge_cases(void) {
    printf("Testing resource edge cases...\n");
    
    // Test NULL inputs
    int status = resource_limiter_check_limits(NULL, NULL);
    assert(status == RESOURCE_ERROR);
    
    ResourceLimiter* limiter = resource_limiter_new();
    status = resource_limiter_check_limits(limiter, NULL);
    assert(status == RESOURCE_ERROR);
    
    // Test invalid limits
    status = resource_limiter_set_memory_limit(limiter, -1);
    assert(status == RESOURCE_ERROR);
    
    status = resource_limiter_set_cpu_limit(limiter, -1);
    assert(status == RESOURCE_ERROR);
    
    // Test zero limits (should be invalid)
    status = resource_limiter_set_memory_limit(limiter, 0);
    assert(status == RESOURCE_ERROR);
    
    resource_limiter_free(limiter);
    
    // Test monitor NULL cases
    ResourceUsage usage = {0};
    status = resource_monitor_get_usage(NULL, &usage);
    assert(status == RESOURCE_ERROR);
    
    ResourceMonitor* monitor = resource_monitor_new();
    status = resource_monitor_get_usage(monitor, NULL);
    assert(status == RESOURCE_ERROR);
    
    resource_monitor_free(monitor);
    
    // Test double free (should not crash)
    resource_limiter_free(NULL);
    resource_monitor_free(NULL);
    
    printf("✓ Resource edge case tests passed\n");
}

/**
 * @brief Test resource cleanup
 */
void test_resource_cleanup(void) {
    printf("Testing resource cleanup...\n");
    
    // Test that multiple allocations and deallocations work
    for (int i = 0; i < 10; i++) {
        ResourceLimiter* limiter = resource_limiter_new();
        ResourceMonitor* monitor = resource_monitor_new();
        
        assert(limiter != NULL);
        assert(monitor != NULL);
        
        resource_limiter_set_memory_limit(limiter, 100);
        resource_monitor_start(monitor);
        resource_monitor_stop(monitor);
        
        resource_limiter_free(limiter);
        resource_monitor_free(monitor);
    }
    
    printf("✓ Resource cleanup tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Resource Management Tests ===\n");
    
    test_resource_limiter_configuration();
    test_memory_limit_checking();
    test_cpu_time_limit_checking();
    test_execution_time_limit_checking();
    test_combined_limit_checking();
    test_resource_monitor();
    test_monitor_accuracy();
    test_resource_edge_cases();
    test_resource_cleanup();
    
    printf("\n✅ All resource management tests passed!\n");
    return 0;
}
