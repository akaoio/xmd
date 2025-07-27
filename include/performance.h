/**
 * @file performance.h
 * @brief Performance optimization and profiling system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct xmd_context xmd_context;
typedef struct token token;

/**
 * @brief Performance optimization levels
 */
typedef enum {
    PERF_OPT_NONE = 0,
    PERF_OPT_BASIC = 1,
    PERF_OPT_AGGRESSIVE = 2,
    PERF_OPT_MAXIMUM = 3
} perf_optimization_level;

/**
 * @brief Performance metrics structure
 */
typedef struct perf_metrics {
    uint64_t parse_time_ns;         ///< Parsing time in nanoseconds
    uint64_t execution_time_ns;     ///< Execution time in nanoseconds
    uint64_t memory_peak_bytes;     ///< Peak memory usage in bytes
    uint64_t memory_current_bytes;  ///< Current memory usage in bytes
    uint32_t cache_hits;            ///< Number of cache hits
    uint32_t cache_misses;          ///< Number of cache misses
    uint32_t allocations;           ///< Number of allocations
    uint32_t deallocations;         ///< Number of deallocations
} perf_metrics;

/**
 * @brief Performance profiler structure
 */
typedef struct perf_profiler {
    perf_metrics metrics;
    xmd_time_t start_time;
    xmd_time_t end_time;
    bool is_active;
    char* profile_data;
    size_t profile_size;
} perf_profiler;

/**
 * @brief AST optimization pass type
 */
typedef enum {
    AST_OPT_CONSTANT_FOLDING = 1,
    AST_OPT_DEAD_CODE_ELIMINATION = 2,
    AST_OPT_COMMON_SUBEXPRESSION = 4,
    AST_OPT_LOOP_UNROLLING = 8,
    AST_OPT_INLINE_EXPANSION = 16,
    AST_OPT_ALL = 31
} ast_optimization_pass;

/**
 * @brief Benchmark result structure
 */
typedef struct benchmark_result {
    char* test_name;
    uint64_t min_time_ns;
    uint64_t max_time_ns;
    uint64_t avg_time_ns;
    uint64_t median_time_ns;
    uint32_t iterations;
    double throughput_ops_per_sec;
} benchmark_result;

/**
 * @brief Benchmark suite structure
 */
typedef struct benchmark_suite {
    benchmark_result* results;
    size_t result_count;
    size_t result_capacity;
    char* suite_name;
} benchmark_suite;

// =============================================================================
// AST Optimizer Functions
// =============================================================================

/**
 * @brief Initialize AST optimizer
 * @param level Optimization level
 * @return 0 on success, -1 on error
 */
int perf_optimizer_init(perf_optimization_level level);

/**
 * @brief Optimize AST with specified passes
 * @param tokens Array of tokens to optimize
 * @param token_count Number of tokens
 * @param passes Optimization passes to apply
 * @return 0 on success, -1 on error
 */
int perf_optimize_ast(token** tokens, size_t* token_count, uint32_t passes);

/**
 * @brief Cleanup optimizer resources
 */
void perf_optimizer_cleanup(void);

// =============================================================================
// Performance Profiler Functions
// =============================================================================

/**
 * @brief Initialize performance profiler
 * @return Profiler instance or NULL on error
 */
perf_profiler* perf_profiler_create(void);

/**
 * @brief Start profiling session
 * @param profiler Profiler instance
 * @return 0 on success, -1 on error
 */
int perf_profiler_start(perf_profiler* profiler);

/**
 * @brief Stop profiling session
 * @param profiler Profiler instance
 * @return 0 on success, -1 on error
 */
int perf_profiler_stop(perf_profiler* profiler);

/**
 * @brief Record memory allocation
 * @param profiler Profiler instance
 * @param size Size of allocation
 */
void perf_profiler_record_alloc(perf_profiler* profiler, size_t size);

/**
 * @brief Record memory deallocation
 * @param profiler Profiler instance
 * @param size Size of deallocation
 */
void perf_profiler_record_dealloc(perf_profiler* profiler, size_t size);

/**
 * @brief Record cache hit
 * @param profiler Profiler instance
 */
void perf_profiler_record_cache_hit(perf_profiler* profiler);

/**
 * @brief Record cache miss
 * @param profiler Profiler instance
 */
void perf_profiler_record_cache_miss(perf_profiler* profiler);

/**
 * @brief Get current metrics
 * @param profiler Profiler instance
 * @return Pointer to metrics or NULL on error
 */
const perf_metrics* perf_profiler_get_metrics(perf_profiler* profiler);

/**
 * @brief Generate profiling report
 * @param profiler Profiler instance
 * @return Report string (must be freed) or NULL on error
 */
char* perf_profiler_generate_report(perf_profiler* profiler);

/**
 * @brief Destroy profiler instance
 * @param profiler Profiler instance
 */
void perf_profiler_destroy(perf_profiler* profiler);

// =============================================================================
// Benchmark Functions
// =============================================================================

/**
 * @brief Create benchmark suite
 * @param name Suite name
 * @return Suite instance or NULL on error
 */
benchmark_suite* benchmark_suite_create(const char* name);

/**
 * @brief Run benchmark function
 * @param suite Benchmark suite
 * @param test_name Test name
 * @param test_func Function to benchmark
 * @param test_data Data to pass to function
 * @param iterations Number of iterations
 * @return 0 on success, -1 on error
 */
int benchmark_run(benchmark_suite* suite, const char* test_name,
                  int (*test_func)(void*), void* test_data, uint32_t iterations);

/**
 * @brief Generate benchmark report
 * @param suite Benchmark suite
 * @return Report string (must be freed) or NULL on error
 */
char* benchmark_generate_report(benchmark_suite* suite);

/**
 * @brief Destroy benchmark suite
 * @param suite Benchmark suite
 */
void benchmark_suite_destroy(benchmark_suite* suite);

/**
 * @brief Get current time in nanoseconds
 * @return Time in nanoseconds
 */
uint64_t get_time_ns(void);

/**
 * @brief Calculate statistics from timing data
 * @param times Array of timing measurements
 * @param count Number of measurements
 * @param result Benchmark result to populate
 */
void calculate_stats(uint64_t* times, uint32_t count, benchmark_result* result);

/**
 * @brief Resize results array if needed
 * @param suite Benchmark suite
 * @return 0 on success, -1 on error
 */
int resize_results_if_needed(benchmark_suite* suite);

/**
 * @brief Compare function for sorting times
 * @param a First time value
 * @param b Second time value
 * @return Comparison result
 */
int compare_times(const void* a, const void* b);

// =============================================================================
// Utility Macros
// =============================================================================

/**
 * @brief Profile a code block
 */
#define PERF_PROFILE_BLOCK(profiler, name, block) \
    do { \
        if (profiler) perf_profiler_start(profiler); \
        block \
        if (profiler) perf_profiler_stop(profiler); \
    } while(0)

/**
 * @brief Record allocation with profiler if available
 */
#define PERF_RECORD_ALLOC(profiler, size) \
    do { \
        if (profiler) perf_profiler_record_alloc(profiler, size); \
    } while(0)

/**
 * @brief Record deallocation with profiler if available
 */
#define PERF_RECORD_DEALLOC(profiler, size) \
    do { \
        if (profiler) perf_profiler_record_dealloc(profiler, size); \
    } while(0)

/**
 * @brief Record cache hit with profiler if available
 */
#define PERF_RECORD_CACHE_HIT(profiler) \
    do { \
        if (profiler) perf_profiler_record_cache_hit(profiler); \
    } while(0)

/**
 * @brief Record cache miss with profiler if available
 */
#define PERF_RECORD_CACHE_MISS(profiler) \
    do { \
        if (profiler) perf_profiler_record_cache_miss(profiler); \
    } while(0)

#ifdef __cplusplus
}
#endif

#endif // PERFORMANCE_H
