/**
 * @file parse_env_double.c
 * @brief Environment variable double parsing function
 * @author XMD Team
 *
 * Implementation of double environment variable parsing for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Parse environment variable as double
 * @param env_name Environment variable name
 * @param default_value Default value if parsing fails
 * @return Parsed value or default_value
 */
double parse_env_double(const char* env_name, double default_value) {
    const char* env_value = getenv(env_name);
    if (!env_value) {
        return default_value;
    }
    
    char* endptr;
    double value = strtod(env_value, &endptr);
    if (*endptr != '\0') {
        return default_value;
    }
    
    return value;
}