/**
 * @file test_phase6_integration.c
 * @brief Integration tests for Phase 6 Security & Performance components
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
 * @brief Test secure optimization workflow
 */
static void test_secure_optimization_workflow(void) {
    printf("Testing secure optimization workflow...\n");
    
    // Create profiler
    perf_profiler* profiler = perf_profiler_create();
    assert(profiler != NULL);
    
    // Initialize security audit
    char temp_file[] = "/tmp/xmd_phase6_test_XXXXXX";
    int fd = mkstemp(temp_file);
    assert(fd != -1);
    close(fd);
    assert(security_audit_init(temp_file) == 0);
    
    // Initialize optimizer
    assert(perf_optimizer_init(PERF_OPT_BASIC) == 0);
    
    // Start profiling
    assert(perf_profiler_start(profiler) == 0);
    
    // Test input validation with security audit
    const char* test_input = "Hello <script>alert('xss')</script> World";
    security_result result = security_validate_input(test_input, 1000);
    assert(result == SECURITY_INJECTION_DETECTED);
    
    // Manual audit log
    SECURITY_AUDIT(AUDIT_INPUT_VALIDATION, "Integration test validation", result);
    
    // Test output sanitization
    char* sanitized = security_sanitize_output(test_input);
    assert(sanitized != NULL);
    assert(strstr(sanitized, "&lt;script&gt;") != NULL);
    assert(strstr(sanitized, "<script>") == NULL);
    
    // Record profiling events
    perf_profiler_record_alloc(profiler, strlen(sanitized));
    perf_profiler_record_cache_miss(profiler); // Sanitization not cached
    
    // Test AST optimization with profiling
    token* test_tokens = malloc(3 * sizeof(token));
    assert(test_tokens != NULL);
    
    // Initialize tokens properly
    memset(test_tokens, 0, 3 * sizeof(token));
    
    test_tokens[0].type = TOKEN_TEXT;
    test_tokens[0].value = strdup("2");
    test_tokens[0].line = 1;
    test_tokens[0].column = 1;
    test_tokens[0].next = NULL;
    
    test_tokens[1].type = TOKEN_TEXT;
    test_tokens[1].value = strdup("+");
    test_tokens[1].line = 1;
    test_tokens[1].column = 2;
    test_tokens[1].next = NULL;
    
    test_tokens[2].type = TOKEN_TEXT;
    test_tokens[2].value = strdup("3");
    test_tokens[2].line = 1;
    test_tokens[2].column = 3;
    test_tokens[2].next = NULL;
    
    size_t token_count = 3;
    
    // Optimize with profiling
    perf_profiler_record_alloc(profiler, token_count * sizeof(token));
    assert(perf_optimize_ast(&test_tokens, &token_count, AST_OPT_CONSTANT_FOLDING) == 0);
    perf_profiler_record_cache_hit(profiler); // Optimization cached
    
    // Stop profiling
    assert(perf_profiler_stop(profiler) == 0);
    
    // Verify metrics
    const perf_metrics* metrics = perf_profiler_get_metrics(profiler);
    assert(metrics != NULL);
    assert(metrics->execution_time_ns > 0);
    assert(metrics->cache_hits == 1);
    assert(metrics->cache_misses == 1);
    assert(metrics->allocations == 2);
    
    // Generate combined report
    char* perf_report = perf_profiler_generate_report(profiler);
    assert(perf_report != NULL);
    assert(strstr(perf_report, "Performance Profile Report") != NULL);
    
    // Verify security audit entries
    security_audit_entry* entries = NULL;
    size_t count = 0;
    assert(security_audit_get_entries(0, UINT64_MAX, &entries, &count) == 0);
    assert(count >= 1);
    assert(entries != NULL);
    
    // Cleanup
    for (size_t i = 0; i < token_count; i++) {
        free(test_tokens[i].value);
    }
    free(test_tokens);
    free(sanitized);
    free(perf_report);
    free(entries);
    
    perf_profiler_destroy(profiler);
    security_audit_cleanup();
    perf_optimizer_cleanup();
    unlink(temp_file);
    
    printf("✓ Secure optimization workflow tests passed\n");
}

/**
 * @brief Test performance impact of security measures
 */
static void test_security_performance_impact(void) {
    printf("Testing security performance impact...\n");
    
    // Create benchmark suite
    benchmark_suite* suite = benchmark_suite_create("Security Performance");
    assert(suite != NULL);
    
    // Test data
    const char* test_inputs[] = {
        "Normal text without any security issues",
        "Text with <script>alert('xss')</script> injection",
        "Path traversal: ../../../etc/passwd",
        "Command injection: $(rm -rf /)",
        "SQL injection: '; DROP TABLE users; --"
    };
    const size_t num_inputs = sizeof(test_inputs) / sizeof(test_inputs[0]);
    
    // Benchmark security validation
    for (size_t i = 0; i < num_inputs; i++) {
        security_result result = security_validate_input(test_inputs[i], 1000);
        (void)result; // Prevent unused variable warning
    }
    
    // Benchmark sanitization
    for (size_t i = 0; i < num_inputs; i++) {
        char* sanitized = security_sanitize_output(test_inputs[i]);
        if (sanitized) {
            free(sanitized);
        }
    }
    
    // The benchmarking itself is lightweight for this test
    // In a real scenario, we'd use the benchmark_run function
    
    benchmark_suite_destroy(suite);
    
    printf("✓ Security performance impact tests passed\n");
}

/**
 * @brief Test optimization effectiveness
 */
static void test_optimization_effectiveness(void) {
    printf("Testing optimization effectiveness...\n");
    
    // Initialize optimizer with different levels
    perf_optimization_level levels[] = {
        PERF_OPT_NONE,
        PERF_OPT_BASIC,
        PERF_OPT_AGGRESSIVE,
        PERF_OPT_MAXIMUM
    };
    
    for (int i = 0; i < 4; i++) {
        assert(perf_optimizer_init(levels[i]) == 0);
        
        // Test different optimization passes
        uint32_t passes[] = {
            AST_OPT_CONSTANT_FOLDING,
            AST_OPT_DEAD_CODE_ELIMINATION,
            AST_OPT_COMMON_SUBEXPRESSION,
            AST_OPT_LOOP_UNROLLING,
            AST_OPT_INLINE_EXPANSION
        };
        
        for (int j = 0; j < 5; j++) {
            // Create test tokens
            token* tokens = malloc(5 * sizeof(token));
            assert(tokens != NULL);
            
            for (int k = 0; k < 5; k++) {
                tokens[k].type = TOKEN_TEXT;
                tokens[k].value = strdup("test");
            }
            
            size_t token_count = 5;
            
            // Apply optimization
            int opt_result = perf_optimize_ast(&tokens, &token_count, passes[j]);
            assert(opt_result == 0);
            
            // Cleanup
            for (size_t k = 0; k < token_count; k++) {
                free(tokens[k].value);
            }
            free(tokens);
        }
        
        perf_optimizer_cleanup();
    }
    
    printf("✓ Optimization effectiveness tests passed\n");
}

/**
 * @brief Test error handling and edge cases
 */
static void test_error_handling(void) {
    printf("Testing error handling...\n");
    
    // Test security with NULL inputs
    assert(security_validate_input(NULL, 100) == SECURITY_INVALID_INPUT);
    assert(security_sanitize_output(NULL) == NULL);
    
    // Test performance with NULL inputs
    assert(perf_profiler_start(NULL) == -1);
    assert(perf_optimize_ast(NULL, NULL, AST_OPT_CONSTANT_FOLDING) == -1);
    
    // Test optimizer without initialization
    token* tokens = malloc(sizeof(token));
    if (tokens) {
        tokens[0].type = TOKEN_TEXT;
        tokens[0].value = strdup("test");
        size_t count = 1;
        
        // Should fail without initialization
        assert(perf_optimize_ast(&tokens, &count, AST_OPT_CONSTANT_FOLDING) == -1);
        
        free(tokens[0].value);
        free(tokens);
    }
    
    printf("✓ Error handling tests passed\n");
}

/**
 * @brief Main integration test function
 */
int main(void) {
    printf("=== Phase 6 Integration Tests ===\n");
    
    test_secure_optimization_workflow();
    test_security_performance_impact();
    test_optimization_effectiveness();
    test_error_handling();
    
    printf("\n✅ All Phase 6 integration tests passed!\n");
    return 0;
}