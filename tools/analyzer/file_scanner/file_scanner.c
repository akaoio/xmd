/**
 * @file file_scanner.c
 * @brief Scan directory for C source files (Standard C only)
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 * NO external dependencies - uses only Standard C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External development tool - standalone, no XMD dependencies

/**
 * @brief Check if filename has C source extension
 * @param filename Name of file to check
 * @return 1 if C source file, 0 otherwise
 */
static int is_c_source_file(const char* filename) {
    if (!filename) {
        return 0;
    }
    
    size_t len = strlen(filename);
    if (len < 3) {
        return 0;
    }
    
    // Check for .c or .h extension
    return (strcmp(filename + len - 2, ".c") == 0 || 
            strcmp(filename + len - 2, ".h") == 0);
}

/**
 * @brief Scan directory recursively for C source files using standard C only
 * @param dir_path Directory path to scan
 * @param output_file Output file to write file paths
 * @return 1 on success, 0 on failure
 */
int file_scanner(const char* dir_path, FILE* output_file) {
    if (!dir_path || !output_file) {
        return 0;
    }
    
    // Use standard C approach with system() call
    // This follows Genesis principle of Standard C only
    char command[1024];
    snprintf(command, sizeof(command), 
             "find \"%s\" -name \"*.c\" -o -name \"*.h\" 2>/dev/null", dir_path);
    
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        return 0;
    }
    
    char file_path[512];
    while (fgets(file_path, sizeof(file_path), pipe)) {
        // Remove newline
        file_path[strcspn(file_path, "\n")] = 0;
        
        // Validate file path
        if (strlen(file_path) > 0 && is_c_source_file(file_path)) {
            fprintf(output_file, "%s\n", file_path);
        }
    }
    
    pclose(pipe);
    return 1;
}