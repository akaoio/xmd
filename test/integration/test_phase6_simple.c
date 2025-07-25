/**
 * @file test_phase6_simple.c
 * @brief Simple integration tests for Phase 6 Security & Performance components
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "../../include/security.h"
#include "../../include/performance.h"
#include "../../include/token.h"

/**
 * @brief Test basic integration of security and performance components
 */
static void test_basic_integration(void) {
    printf("Testing basic integration...\n");
    
    // Initialize profiler
    perf_profiler* profiler = perf_profiler_create();
    assert(profiler != NULL);
    
    // Initialize security audit
    char temp_file[] = "/tmp/xmd_phase6_simple_XXXXXX";
    int fd = mkstemp(temp_file);
    assert(fd != -1);
    close(fd);
    assert(security_audit_init(temp_file) == 0);
    
    // Start profiling
    assert(perf_profiler_start(profiler) == 0);
    
    // Test security validation with profiling
    const char* test_inputs[] = {
        "normal text",
        "<script>alert('xss')</script>",
        "../../../etc/passwd",
        "'; DROP TABLE users; --"
    };
    
    for (int i = 0; i < 4; i++) {
        perf_profiler_record_alloc(profiler, strlen(test_inputs[i]));
        
        security_result result = security_validate_input(test_inputs[i], 1000);
        
        if (result == SECURITY_VALID) {
            perf_profiler_record_cache_hit(profiler);
        } else {
            perf_profiler_record_cache_miss(profiler);
            
            // Log security event
            SECURITY_AUDIT(AUDIT_INPUT_VALIDATION, "Validation failed", result);
        }
        
        // Test sanitization
        char* sanitized = security_sanitize_output(test_inputs[i]);
        if (sanitized) {
            size_t sanitized_len = strlen(sanitized);
            perf_profiler_record_alloc(profiler, sanitized_len);
            free(sanitized);
            perf_profiler_record_dealloc(profiler, sanitized_len);
        }
        
        perf_profiler_record_dealloc(profiler, strlen(test_inputs[i]));
    }
    
    // Stop profiling
    assert(perf_profiler_stop(profiler) == 0);
    
    // Verify metrics
    const perf_metrics* metrics = perf_profiler_get_metrics(profiler);
    assert(metrics != NULL);
    assert(metrics->execution_time_ns > 0);
    assert(metrics->allocations >= 4);
    assert(metrics->cache_hits >= 1);
    assert(metrics->cache_misses >= 1);
    
    // Generate reports
    char* perf_report = perf_profiler_generate_report(profiler);
    assert(perf_report != NULL);
    assert(strstr(perf_report, "Performance Profile Report") != NULL);
    free(perf_report);
    
    // Verify audit entries
    security_audit_entry* entries = NULL;
    size_t count = 0;
    assert(security_audit_get_entries(0, UINT64_MAX, &entries, &count) == 0);
    assert(count >= 1);
    free(entries);
    
    // Cleanup
    perf_profiler_destroy(profiler);
    security_audit_cleanup();
    unlink(temp_file);
    
    printf("✓ Basic integration tests passed\n");
}

/**
 * @brief Test optimizer initialization and basic functionality
 */
static void test_optimizer_integration(void) {
    printf("Testing optimizer integration...\n");
    
    // Test optimizer with different levels
    perf_optimization_level levels[] = {
        PERF_OPT_NONE,
        PERF_OPT_BASIC,
        PERF_OPT_AGGRESSIVE,
        PERF_OPT_MAXIMUM
    };
    
    for (int i = 0; i < 4; i++) {
        assert(perf_optimizer_init(levels[i]) == 0);
        
        // Test with NULL inputs (should handle gracefully)
        assert(perf_optimize_ast(NULL, NULL, AST_OPT_CONSTANT_FOLDING) == -1);
        
        perf_optimizer_cleanup();
    }
    
    printf("✓ Optimizer integration tests passed\n");
}

/**
 * @brief Simple benchmark test function
 */
static int benchmark_test_func(void* data) {
    (void)data; // Unused
    
    // Simulate some work with security and performance components
    security_result result = security_validate_input("test", 100);
    (void)result;
    
    return 0;
}

/**
 * @brief Test benchmark integration
 */
static void test_benchmark_integration(void) {
    printf("Testing benchmark integration...\n");
    
    // Create benchmark suite
    benchmark_suite* suite = benchmark_suite_create("Phase 6 Integration");
    assert(suite != NULL);
    
    // Run benchmark
    assert(benchmark_run(suite, "Security Validation", benchmark_test_func, NULL, 5) == 0);
    
    // Generate report
    char* report = benchmark_generate_report(suite);
    assert(report != NULL);
    assert(strstr(report, "Benchmark Report") != NULL);
    free(report);
    
    benchmark_suite_destroy(suite);
    
    printf("✓ Benchmark integration tests passed\n");
}

/**
 * @brief Test error handling across components
 */
static void test_error_handling_integration(void) {
    printf("Testing error handling integration...\n");
    
    // Test security with invalid inputs
    assert(security_validate_input(NULL, 100) == SECURITY_INVALID_INPUT);
    assert(security_sanitize_output(NULL) == NULL);
    
    // Test performance with invalid inputs
    assert(perf_profiler_start(NULL) == -1);
    assert(perf_profiler_get_metrics(NULL) == NULL);
    
    // Test optimizer without initialization
    assert(perf_optimize_ast(NULL, NULL, AST_OPT_CONSTANT_FOLDING) == -1);
    
    // Test benchmark with invalid inputs
    assert(benchmark_suite_create(NULL) == NULL);
    assert(benchmark_generate_report(NULL) == NULL);
    
    printf("✓ Error handling integration tests passed\n");
}

/**
 * @brief Main integration test function
 */
int main(void) {
    printf("=== Phase 6 Simple Integration Tests ===\n");
    
    test_basic_integration();
    test_optimizer_integration();
    test_benchmark_integration();
    test_error_handling_integration();
    
    printf("\n✅ All Phase 6 simple integration tests passed!\n");
    return 0;
}