/**
 * @file parse_env_size_t.c
 * @brief Environment variable size_t parsing function
 * @author XMD Team
 *
 * Implementation of size_t environment variable parsing for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Parse environment variable as size_t
 * @param env_name Environment variable name
 * @param default_value Default value if parsing fails
 * @return Parsed value or default_value
 */
size_t parse_env_size_t(const char* env_name, size_t default_value) {
    const char* env_value = getenv(env_name);
    if (!env_value) {
        return default_value;
    }
    
    char* endptr;
    unsigned long value = strtoul(env_value, &endptr, 10);
    if (*endptr != '\0' || value > SIZE_MAX) {
        return default_value;
    }
    
    return (size_t)value;
}