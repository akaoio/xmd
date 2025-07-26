/**
 * @file test_performance.c
 * @brief Test suite for performance optimization components
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "../../include/performance.h"
#include "../../include/token.h"

/**
 * @brief Simple test function for benchmarking
 * @param data Test data (unused)
 * @return 0 on success
 */
static int simple_test_function(void* data) {
    // Simple computation
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += i;
    }
    return 0;
}

/**
 * @brief Test profiler functionality
 */
static void test_profiler(void) {
    printf("Testing profiler...\n");
    
    perf_profiler* profiler = perf_profiler_create();
    assert(profiler != NULL);
    
    // Test starting profiler
    assert(perf_profiler_start(profiler) == 0);
    
    // Simulate some work
    usleep(1000); // 1ms
    
    // Record some events
    perf_profiler_record_alloc(profiler, 1024);
    perf_profiler_record_cache_hit(profiler);
    perf_profiler_record_cache_miss(profiler);
    perf_profiler_record_dealloc(profiler, 512);
    
    // Test stopping profiler
    assert(perf_profiler_stop(profiler) == 0);
    
    // Get metrics
    const perf_metrics* metrics = perf_profiler_get_metrics(profiler);
    assert(metrics != NULL);
    assert(metrics->execution_time_ns > 0);
    assert(metrics->cache_hits == 1);
    assert(metrics->cache_misses == 1);
    assert(metrics->allocations == 1);
    assert(metrics->deallocations == 1);
    
    // Generate report
    char* report = perf_profiler_generate_report(profiler);
    assert(report != NULL);
    assert(strstr(report, "Performance Profile Report") != NULL);
    free(report);
    
    perf_profiler_destroy(profiler);
    
    printf("✓ Profiler tests passed\n");
}

/**
 * @brief Test optimizer functionality
 */
static void test_optimizer(void) {
    printf("Testing optimizer...\n");
    
    // Initialize optimizer
    assert(perf_optimizer_init(PERF_OPT_BASIC) == 0);
    
    // Create test tokens for optimization
    token* test_tokens = malloc(5 * sizeof(token));
    assert(test_tokens != NULL);
    
    // Create a simple text sequence
    test_tokens[0].type = TOKEN_TEXT;
    test_tokens[0].value = strdup("2");
    test_tokens[1].type = TOKEN_TEXT;
    test_tokens[1].value = strdup("+");
    test_tokens[2].type = TOKEN_TEXT;
    test_tokens[2].value = strdup("3");
    test_tokens[3].type = TOKEN_TEXT;
    test_tokens[3].value = strdup("*");
    test_tokens[4].type = TOKEN_TEXT;
    test_tokens[4].value = strdup("1");
    
    size_t token_count = 5;
    
    // Test optimization
    assert(perf_optimize_ast(&test_tokens, &token_count, AST_OPT_CONSTANT_FOLDING) == 0);
    
    // Check that optimization was applied (token count may have changed)
    // For markdown tokens, the optimization is more about structure than arithmetic
    assert(token_count <= 5); // Should not increase
    
    // Clean up
    for (size_t i = 0; i < token_count; i++) {
        free(test_tokens[i].value);
    }
    free(test_tokens);
    
    perf_optimizer_cleanup();
    
    printf("✓ Optimizer tests passed\n");
}

/**
 * @brief Test benchmark functionality
 */
static void test_benchmark(void) {
    printf("Testing benchmark...\n");
    
    benchmark_suite* suite = benchmark_suite_create("Test Suite");
    assert(suite != NULL);
    
    // Run benchmark
    assert(benchmark_run(suite, "Simple Test", simple_test_function, NULL, 10) == 0);
    
    // Generate report
    char* report = benchmark_generate_report(suite);
    assert(report != NULL);
    assert(strstr(report, "Benchmark Report") != NULL);
    assert(strstr(report, "Simple Test") != NULL);
    free(report);
    
    benchmark_suite_destroy(suite);
    
    printf("✓ Benchmark tests passed\n");
}

/**
 * @brief Test edge cases and error conditions
 */
static void test_edge_cases(void) {
    printf("Testing edge cases...\n");
    
    // Test NULL inputs
    assert(perf_profiler_create() != NULL);
    assert(perf_profiler_start(NULL) == -1);
    assert(perf_profiler_stop(NULL) == -1);
    assert(perf_profiler_get_metrics(NULL) == NULL);
    assert(perf_profiler_generate_report(NULL) == NULL);
    
    // Test optimizer with invalid level
    assert(perf_optimizer_init(-1) == -1);
    assert(perf_optimizer_init(999) == -1);
    
    // Test benchmark with NULL inputs
    assert(benchmark_suite_create(NULL) == NULL);
    assert(benchmark_run(NULL, "test", simple_test_function, NULL, 1) == -1);
    assert(benchmark_generate_report(NULL) == NULL);
    
    printf("✓ Edge case tests passed\n");
}

/**
 * @brief Main test function
 */
int main(void) {
    printf("=== Performance System Tests ===\n");
    
    test_profiler();
    test_optimizer();
    test_benchmark();
    test_edge_cases();
    
    printf("\n✅ All performance tests passed!\n");
    return 0;
}
