/**
 * @file performance_internal.h
 * @brief Internal performance management structures
 * @author XMD Team
 */

#ifndef PERFORMANCE_INTERNAL_H
#define PERFORMANCE_INTERNAL_H

#include "performance.h"

/**
 * @brief Internal performance configuration
 */
typedef struct {
    bool optimization_enabled;
    size_t max_cache_size;
} performance_config_t;

#endif /* PERFORMANCE_INTERNAL_H */
