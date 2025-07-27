/**
 * @file limiter_internal.h
 * @brief Internal declarations for resource limiter
 * @author XMD Team
 */

#ifndef LIMITER_INTERNAL_H
#define LIMITER_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/resource.h>
#include "../include/resource.h"
#include "../include/config.h"

// Function prototypes (struct is already defined in resource.h)
ResourceLimiter* resource_limiter_new(void);
void resource_limiter_free(ResourceLimiter* limiter);
void set_limiter_error(ResourceLimiter* limiter, const char* message);
int resource_limiter_set_memory_limit(ResourceLimiter* limiter, long max_memory_mb);
int resource_limiter_set_cpu_limit(ResourceLimiter* limiter, long max_cpu_time_ms);
int resource_limiter_set_time_limit(ResourceLimiter* limiter, long max_execution_time_ms);
int resource_limiter_check_limits(ResourceLimiter* limiter, ResourceUsage* usage);

#endif /* LIMITER_INTERNAL_H */