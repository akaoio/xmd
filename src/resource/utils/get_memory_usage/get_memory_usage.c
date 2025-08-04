/**
 * @file get_memory_usage.c
 * @brief Get current memory usage
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "utils/common/validation_macros.h"

size_t get_memory_usage(void) {
    // Real memory usage implementation using /proc/self/status
    #ifdef __linux__
    XMD_FILE_READ_OPEN(file, "/proc/self/status", 0);
    char line[256];
    size_t vm_rss = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line, "VmRSS: %zu kB", &vm_rss);
            break;
        }
    }
    XMD_FILE_CLOSE_SAFE(file);
    return vm_rss * 1024; // Convert kB to bytes
    #else
    // Fallback for non-Linux systems
    return 0;
    #endif
}
