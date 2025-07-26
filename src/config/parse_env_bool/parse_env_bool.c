/**
 * @file parse_env_bool.c
 * @brief Environment variable boolean parsing function
 * @author XMD Team
 *
 * Implementation of boolean environment variable parsing for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Parse environment variable as boolean
 * @param env_name Environment variable name
 * @param default_value Default value if parsing fails
 * @return Parsed value or default_value
 */
bool parse_env_bool(const char* env_name, bool default_value) {
    const char* env_value = getenv(env_name);
    if (!env_value) {
        return default_value;
    }
    
    return (strcmp(env_value, "true") == 0 || 
            strcmp(env_value, "1") == 0 ||
            strcmp(env_value, "yes") == 0);
}