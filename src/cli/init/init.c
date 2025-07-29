/**
 * @file init.c
 * @brief Implementation of the xmd init command
 * @author XMD Implementation Team
 * @date 2025-01-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cli.h"

/**
 * @brief Create .xmd directory if it doesn't exist
 * @return 0 on success, -1 on failure
 */
static int create_xmd_directory(void) {
    struct stat st;
    
    // Check if .xmd directory already exists
    if (stat(".xmd", &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            printf("Directory .xmd already exists\n");
            return 0;
        } else {
            fprintf(stderr, "Error: .xmd exists but is not a directory\n");
            return -1;
        }
    }
    
    // Create .xmd directory
    if (mkdir(".xmd", 0755) != 0) {
        perror("Error creating .xmd directory");
        return -1;
    }
    
    printf("Created .xmd directory\n");
    return 0;
}

/**
 * @brief Create default xmd.yaml configuration file
 * @return 0 on success, -1 on failure
 */
static int create_default_config(void) {
    struct stat st;
    
    // Check if config file already exists
    if (stat(".xmd/xmd.yaml", &st) == 0) {
        printf("Configuration file .xmd/xmd.yaml already exists\n");
        return 0;
    }
    
    // Create default configuration
    FILE* config_file = fopen(".xmd/xmd.yaml", "w");
    if (config_file == NULL) {
        perror("Error creating xmd.yaml");
        return -1;
    }
    
    fprintf(config_file, "version: \"1.0\"\n");
    fprintf(config_file, "projects:\n");
    fprintf(config_file, "  default:\n");
    fprintf(config_file, "    entry:\n");
    fprintf(config_file, "      - \"*.md\"\n");
    fprintf(config_file, "    output: \"output.md\"\n");
    fprintf(config_file, "    watch: true\n");
    fprintf(config_file, "\n");
    fprintf(config_file, "  # Example additional project\n");
    fprintf(config_file, "  # docs:\n");
    fprintf(config_file, "  #   entry: \"docs/**/*.md\"\n");
    fprintf(config_file, "  #   output: \"build/documentation.md\"\n");
    
    fclose(config_file);
    
    printf("Created default configuration at .xmd/xmd.yaml\n");
    return 0;
}

/**
 * @brief Initialize XMD project structure
 * @param argc Argument count
 * @param argv Argument vector
 * @return 0 on success, non-zero on failure
 */
int cmd_init(int argc, char* argv[]) {
    (void)argc; // Unused parameter
    (void)argv; // Unused parameter
    
    printf("Initializing XMD project...\n");
    
    // Create .xmd directory
    if (create_xmd_directory() != 0) {
        return 1;
    }
    
    // Create default configuration file
    if (create_default_config() != 0) {
        return 1;
    }
    
    printf("\n✅ XMD project initialized successfully!\n");
    printf("You can now use:\n");
    printf("  xmd          - Process using default project\n");
    printf("  xmd process  - Explicit process command\n");
    printf("  xmd watch    - Watch for file changes\n");
    printf("\nEdit .xmd/xmd.yaml to customize your project configuration.\n");
    
    return 0;
}