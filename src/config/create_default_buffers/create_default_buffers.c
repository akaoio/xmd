/**
 * @file create_default_buffers.c
 * @brief Default buffer configuration creation function
 * @author XMD Team
 *
 * Implementation of default buffer configuration creation for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Create default buffer configuration
 * @return Default buffer configuration
 */
xmd_buffer_config create_default_buffers(void) {
    xmd_buffer_config buffers = {
        .line_buffer_size = 256,
        .conversion_buffer_size = 64,
        .initial_store_capacity = 16,
        .store_load_factor = 0.75
    };
    return buffers;
}