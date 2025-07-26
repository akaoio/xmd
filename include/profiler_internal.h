/**
 * @file profiler_internal.h
 * @brief Internal header for profiler functions
 * @author XMD Team
 */

#ifndef PROFILER_INTERNAL_H
#define PROFILER_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "platform.h"
#include "performance.h"

// Internal utility function declarations
uint64_t get_time_ns(void);
uint64_t time_diff_ns(const xmd_time_t* start, const xmd_time_t* end);
uint64_t get_memory_usage(void);

// Public function declarations
perf_profiler* perf_profiler_create(void);
int perf_profiler_start(perf_profiler* profiler);
int perf_profiler_stop(perf_profiler* profiler);
void perf_profiler_record_alloc(perf_profiler* profiler, size_t size);
void perf_profiler_record_dealloc(perf_profiler* profiler, size_t size);
void perf_profiler_record_cache_hit(perf_profiler* profiler);
void perf_profiler_record_cache_miss(perf_profiler* profiler);
const perf_metrics* perf_profiler_get_metrics(perf_profiler* profiler);
char* perf_profiler_generate_report(perf_profiler* profiler);
void perf_profiler_destroy(perf_profiler* profiler);

#endif /* PROFILER_INTERNAL_H */