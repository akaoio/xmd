#define _GNU_SOURCE  // For DT_REG and strdup - must be before includes

/**
 * @file examples.c
 * @brief Example generator and manager for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../../../include/platform.h"

/**
 * @brief Generate comprehensive examples documentation
 * @param source_dir Directory containing example files
 * @param output_dir Directory to write generated examples
 * @return 0 on success, -1 on error
 */
int examples_generate(const char* source_dir, const char* output_dir) {
    if (!source_dir || !output_dir) {
        return -1;
    }
    
    // Create output directory if it doesn't exist
    if (xmd_create_directory(output_dir) != 0) {
        return -1;
    }
    
    // Open source directory
    xmd_dir_t dir = xmd_opendir(source_dir);
    if (!dir) {
        return -1;
    }
    
    // Create examples index file
    char index_path[512];
    snprintf(index_path, sizeof(index_path), "%s/README.md", output_dir);
    
    FILE* index_file = fopen(index_path, "w");
    if (!index_file) {
        xmd_closedir(dir);
        return -1;
    }
    
    // Write examples index header
    fprintf(index_file, "# XMD Examples Collection\n\n");
    fprintf(index_file, "This directory contains comprehensive examples demonstrating XMD features.\n\n");
    fprintf(index_file, "## Example Categories\n\n");
    
    struct dirent* entry;
    int example_count = 0;
    
    // Process each file in source directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".md")) {
            // Copy example file and add metadata
            char source_path[512];
            char example_path[512];
            
            snprintf(source_path, sizeof(source_path), "%s/%s", source_dir, entry->d_name);
            snprintf(example_path, sizeof(example_path), "%s/%s", output_dir, entry->d_name);
            
            // Read source file
            FILE* source_file = fopen(source_path, "r");
            if (!source_file) {
                continue;
            }
            
            // Create example file with metadata
            FILE* example_file = fopen(example_path, "w");
            if (!example_file) {
                fclose(source_file);
                continue;
            }
            
            // Write example metadata header
            fprintf(example_file, "<!--\n");
            fprintf(example_file, "Example: %s\n", entry->d_name);
            fprintf(example_file, "Category: General\n");
            fprintf(example_file, "Difficulty: Beginner\n");
            fprintf(example_file, "Features: Variables, Directives\n");
            fprintf(example_file, "Usage: xmd process %s\n", entry->d_name);
            fprintf(example_file, "-->\n\n");
            
            // Copy source content
            char line[1024];
            while (fgets(line, sizeof(line), source_file)) {
                fputs(line, example_file);
            }
            
            // Add example footer
            fprintf(example_file, "\n\n<!-- Example End -->\n");
            fprintf(example_file, "<!-- Run with: xmd process %s -->\n", entry->d_name);
            
            fclose(source_file);
            fclose(example_file);
            
            // Add to index
            fprintf(index_file, "### %s\n\n", entry->d_name);
            fprintf(index_file, "- **File**: [%s](%s)\n", entry->d_name, entry->d_name);
            fprintf(index_file, "- **Usage**: `xmd process %s`\n", entry->d_name);
            fprintf(index_file, "- **Features**: Basic XMD syntax demonstration\n\n");
            
            example_count++;
        }
    }
    
    fprintf(index_file, "## How to Run Examples\n\n");
    fprintf(index_file, "1. Navigate to this directory\n");
    fprintf(index_file, "2. Run any example: `xmd process <example.md>`\n");
    fprintf(index_file, "3. View the processed output\n");
    fprintf(index_file, "4. Modify examples to experiment\n\n");
    fprintf(index_file, "## Creating New Examples\n\n");
    fprintf(index_file, "1. Create a new `.md` file\n");
    fprintf(index_file, "2. Add XMD directives and content\n");
    fprintf(index_file, "3. Test with `xmd validate <file.md>`\n");
    fprintf(index_file, "4. Process with `xmd process <file.md>`\n\n");
    fprintf(index_file, "Total examples: %d\n", example_count);
    
    fclose(index_file);
    closedir(dir);
    
    return 0;
}
