/**
 * @file create_default_buffers.c
 * @brief Create default buffer configuration
 * 
 * This file contains ONLY the create_default_buffers function.
 * One function per file - Genesis principle compliance.
 * Extracted from: backup/backup_20250801_184028/src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"

/**
 * @brief Create default buffer sizes
 * @return Default buffer configuration
 */
xmd_buffer_config create_default_buffers(void) {
    xmd_buffer_config buffers;
    
    buffers.line_buffer_size = 1024;         // 1KB line buffer
    buffers.conversion_buffer_size = 4096;   // 4KB conversion buffer 
    buffers.initial_store_capacity = 64;     // Initial store capacity
    buffers.store_load_factor = 0.75;        // Load factor threshold
    
    return buffers;
}
