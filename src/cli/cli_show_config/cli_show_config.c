/**
 * @file cli_show_config.c
 * @brief CLI configuration display function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <sys/stat.h>

#define XMD_VERSION "1.0.0"
#define XMD_BUILD_DATE __DATE__

/**
 * @brief Show configuration
 * @param config_file Config file path (NULL for default)
 * @return Exit code
 */
int cli_show_config(const char* config_file) {
    printf("XMD Configuration:\n");
    printf("=================\n");
    printf("Version: %s\n", XMD_VERSION);
    printf("Build Date: %s\n", XMD_BUILD_DATE);
    
    if (config_file) {
        printf("Config File: %s\n", config_file);
        
        // Check if config file exists
        struct stat st;
        if (stat(config_file, &st) == 0) {
            printf("Config Status: Found\n");
        } else {
            printf("Config Status: Not found\n");
        }
    } else {
        printf("Config File: Default (none specified)\n");
    }
    
    printf("Default Settings:\n");
    printf("- Debug Mode: Off\n");
    printf("- Verbose Mode: Off\n");
    printf("- Output Format: Auto-detect\n");
    
    return 0;
}