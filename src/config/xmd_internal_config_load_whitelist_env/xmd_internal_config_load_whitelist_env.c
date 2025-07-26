/**
 * @file xmd_internal_config_load_whitelist_env.c
 * @brief Load whitelist from environment variable function
 * @author XMD Team
 *
 * Implementation of environment-based whitelist loading for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Load whitelist from environment variable
 * @param config Configuration to modify
 * @param env_name Environment variable name
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_load_whitelist_env(xmd_internal_config* config, const char* env_name) {
    if (!config || !env_name) {
        return -1;
    }
    
    const char* env_value = getenv(env_name);
    if (!env_value) {
        return 0; // No environment variable set, keep current whitelist
    }
    
    // Parse comma-separated list
    char* env_copy = strdup(env_value);
    if (!env_copy) {
        return -1;
    }
    
    // Count entries
    size_t count = 1;
    char* p = env_copy;
    while (*p) {
        if (*p == ',') count++;
        p++;
    }
    
    // Allocate array for executable names
    const char** executables = malloc(count * sizeof(char*));
    if (!executables) {
        free(env_copy);
        return -1;
    }
    
    // Parse entries
    size_t index = 0;
    char* token = strtok(env_copy, ",");
    while (token && index < count) {
        // Trim whitespace
        while (*token == ' ' || *token == '\t') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && (*end == ' ' || *end == '\t')) end--;
        *(end + 1) = '\0';
        
        executables[index++] = token;
        token = strtok(NULL, ",");
    }
    
    // Set the whitelist
    int result = xmd_internal_config_set_exec_whitelist(config, executables, index);
    
    free(executables);
    free(env_copy);
    return result;
}