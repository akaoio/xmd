/**
 * @file tutorial.c
 * @brief Interactive tutorial system for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/platform.h"

/**
 * @brief Generate interactive tutorials from example files
 * @param source_dir Directory containing example files
 * @param output_dir Directory to write generated tutorials
 * @return 0 on success, -1 on error
 */
int tutorial_generate(const char* source_dir, const char* output_dir) {
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
    
    // Create tutorial index file
    char index_path[512];
    snprintf(index_path, sizeof(index_path), "%s/index.md", output_dir);
    
    FILE* index_file = fopen(index_path, "w");
    if (!index_file) {
        xmd_closedir(dir);
        return -1;
    }
    
    // Write tutorial index header
    fprintf(index_file, "# XMD Interactive Tutorials\n\n");
    fprintf(index_file, "Welcome to the XMD tutorial system! These tutorials will guide you through the features of XMD.\n\n");
    fprintf(index_file, "## Available Tutorials\n\n");
    
    xmd_dirent_t* entry;
    int tutorial_count = 0;
    
    // Process each file in source directory
    while ((entry = xmd_readdir(dir)) != NULL) {
        if (strstr(xmd_get_filename(entry), ".md")) {
            // Create tutorial for this file
            char source_path[512];
            char tutorial_path[512];
            
            snprintf(source_path, sizeof(source_path), "%s/%s", source_dir, xmd_get_filename(entry));
            snprintf(tutorial_path, sizeof(tutorial_path), "%s/tutorial_%s", output_dir, xmd_get_filename(entry));
            
            // Read source file
            FILE* source_file = fopen(source_path, "r");
            if (!source_file) {
                continue;
            }
            
            // Create tutorial file
            FILE* tutorial_file = fopen(tutorial_path, "w");
            if (!tutorial_file) {
                fclose(source_file);
                continue;
            }
            
            // Write tutorial header
            fprintf(tutorial_file, "# Tutorial: %s\n\n", xmd_get_filename(entry));
            fprintf(tutorial_file, "This tutorial demonstrates the features shown in `%s`.\n\n", xmd_get_filename(entry));
            fprintf(tutorial_file, "## Original Example\n\n");
            fprintf(tutorial_file, "```xmd\n");
            
            // Copy source content
            char line[1024];
            while (fgets(line, sizeof(line), source_file)) {
                fputs(line, tutorial_file);
            }
            
            fprintf(tutorial_file, "```\n\n");
            fprintf(tutorial_file, "## Step-by-Step Explanation\n\n");
            fprintf(tutorial_file, "1. This example shows XMD syntax in action\n");
            fprintf(tutorial_file, "2. Try modifying the variables and directives\n");
            fprintf(tutorial_file, "3. Run the example with: `xmd process %s`\n\n", xmd_get_filename(entry));
            fprintf(tutorial_file, "## What You Learned\n\n");
            fprintf(tutorial_file, "- XMD syntax and directives\n");
            fprintf(tutorial_file, "- Variable interpolation\n");
            fprintf(tutorial_file, "- Processing workflow\n\n");
            
            fclose(source_file);
            fclose(tutorial_file);
            
            // Add to index
            fprintf(index_file, "- [%s](tutorial_%s)\n", xmd_get_filename(entry), xmd_get_filename(entry));
            tutorial_count++;
        }
    }
    
    fprintf(index_file, "\n## Getting Started\n\n");
    fprintf(index_file, "1. Choose a tutorial from the list above\n");
    fprintf(index_file, "2. Read through the example and explanation\n");
    fprintf(index_file, "3. Try running the examples yourself\n");
    fprintf(index_file, "4. Experiment with modifications\n\n");
    fprintf(index_file, "Generated %d tutorials.\n", tutorial_count);
    
    fclose(index_file);
    xmd_closedir(dir);
    
    return 0;
}
