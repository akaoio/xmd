/**
 * @file reference.c
 * @brief API reference generator for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../../include/platform.h"

/**
 * @brief Generate API reference documentation from header files
 * @param include_dir Directory containing header files
 * @param output_file Output file for generated reference
 * @return 0 on success, -1 on error
 */
int reference_generate(const char* include_dir, const char* output_file) {
    if (!include_dir || !output_file) {
        return -1;
    }
    
    // Open include directory
    xmd_dir_t dir = xmd_opendir(include_dir);
    if (!dir) {
        return -1;
    }
    
    // Create reference file
    FILE* ref_file = fopen(output_file, "w");
    if (!ref_file) {
        xmd_closedir(dir);
        return -1;
    }
    
    // Write reference header
    fprintf(ref_file, "# XMD API Reference\n\n");
    fprintf(ref_file, "This document provides a comprehensive reference for the XMD API.\n\n");
    fprintf(ref_file, "## Table of Contents\n\n");
    
    struct dirent* entry;
    int header_count = 0;
    
    // First pass: generate table of contents
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".h")) {
            char* module_name = strdup(entry->d_name);
            char* dot = strrchr(module_name, '.');
            if (dot) *dot = '\0';
            
            fprintf(ref_file, "- [%s Module](#%s-module)\n", module_name, module_name);
            free(module_name);
            header_count++;
        }
    }
    
    fprintf(ref_file, "\n");
    
    // Rewind directory
    rewinddir(dir);
    
    // Second pass: generate documentation for each header
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".h")) {
            char header_path[512];
            snprintf(header_path, sizeof(header_path), "%s/%s", include_dir, entry->d_name);
            
            // Read header file
            FILE* header_file = fopen(header_path, "r");
            if (!header_file) {
                continue;
            }
            
            char* module_name = strdup(entry->d_name);
            char* dot = strrchr(module_name, '.');
            if (dot) *dot = '\0';
            
            // Write module header
            fprintf(ref_file, "## %s Module\n\n", module_name);
            fprintf(ref_file, "**Header File**: `%s`\n\n", entry->d_name);
            
            // Parse header file for documentation
            char line[1024];
            bool in_comment = false;
            bool found_function = false;
            
            while (fgets(line, sizeof(line), header_file)) {
                // Look for Doxygen comments
                if (strstr(line, "/**")) {
                    in_comment = true;
                    fprintf(ref_file, "### Function Documentation\n\n");
                    continue;
                }
                
                if (strstr(line, "*/")) {
                    in_comment = false;
                    continue;
                }
                
                if (in_comment) {
                    // Extract and format comment content
                    char* comment_start = strstr(line, "*");
                    if (comment_start) {
                        comment_start++; // Skip the '*'
                        while (*comment_start == ' ') comment_start++; // Skip spaces
                        
                        if (strstr(comment_start, "@brief")) {
                            fprintf(ref_file, "**Description**: %s\n", comment_start + 6);
                        } else if (strstr(comment_start, "@param")) {
                            fprintf(ref_file, "- **Parameter**: %s\n", comment_start + 6);
                        } else if (strstr(comment_start, "@return")) {
                            fprintf(ref_file, "- **Returns**: %s\n", comment_start + 7);
                        }
                    }
                }
                
                // Look for function declarations
                if (!in_comment && (strstr(line, "(") && strstr(line, ")") && strstr(line, ";"))) {
                    // This looks like a function declaration
                    char* trimmed = line;
                    while (*trimmed == ' ' || *trimmed == '\t') trimmed++;
                    
                    if (strncmp(trimmed, "typedef", 7) != 0 && strncmp(trimmed, "#", 1) != 0) {
                        fprintf(ref_file, "```c\n%s```\n\n", trimmed);
                        found_function = true;
                    }
                }
            }
            
            if (!found_function) {
                fprintf(ref_file, "This module contains type definitions and constants.\n\n");
            }
            
            fprintf(ref_file, "---\n\n");
            
            fclose(header_file);
            free(module_name);
        }
    }
    
    // Write reference footer
    fprintf(ref_file, "## Usage Examples\n\n");
    fprintf(ref_file, "For practical examples of using these APIs, see the examples directory.\n\n");
    fprintf(ref_file, "## Integration\n\n");
    fprintf(ref_file, "Include the appropriate headers in your C code:\n\n");
    fprintf(ref_file, "```c\n");
    fprintf(ref_file, "#include \"xmd.h\"  // Main XMD interface\n");
    fprintf(ref_file, "#include \"cli.h\" // CLI interface\n");
    fprintf(ref_file, "```\n\n");
    fprintf(ref_file, "Generated from %d header files.\n", header_count);
    
    fclose(ref_file);
    closedir(dir);
    
    return 0;
}
