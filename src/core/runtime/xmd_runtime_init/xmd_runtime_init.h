#ifndef XMD_RUNTIME_INIT_H
#define XMD_RUNTIME_INIT_H

#include <stdbool.h>

typedef struct {
    bool debug_mode;
    bool strict_mode;
    bool safe_mode;
    int max_stack_depth;
    int max_recursion_depth;
    const char* version;
} xmd_runtime_config;

bool xmd_runtime_init(const xmd_runtime_config* config);

#endif
