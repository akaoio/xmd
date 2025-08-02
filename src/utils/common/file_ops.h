#ifndef XMD_FILE_OPS_H
#define XMD_FILE_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "common_macros.h"

/**
 * XMD File Operations Utilities
 * Part of Phase 2 Refactoring - Reduce file I/O duplication
 * 
 * These are internal utilities that don't violate the isolation principle
 * because they're static inline functions used as building blocks
 */

/**
 * Read entire file into memory
 * Caller must free the returned buffer
 */
static inline char* xmd_read_file(const char* path) {
    XMD_NULL_CHECK(path, NULL);
    
    FILE* file = fopen(path, "rb");
    if (!file) {
        XMD_WARNING("Cannot open file: %s", path);
        return NULL;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(file);
        return NULL;
    }
    
    // Allocate buffer
    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        XMD_WARNING("Failed to allocate %ld bytes for file", file_size + 1);
        return NULL;
    }
    
    // Read file
    size_t read_size = fread(buffer, 1, file_size, file);
    buffer[read_size] = '\\0';
    
    fclose(file);
    return buffer;
}

/**
 * Write content to file
 * Returns 0 on success, -1 on failure
 */
static inline int xmd_write_file(const char* path, const char* content) {
    XMD_NULL_CHECK(path, -1);
    XMD_NULL_CHECK(content, -1);
    
    FILE* file = fopen(path, "w");
    if (!file) {
        XMD_WARNING("Cannot create file: %s", path);
        return -1;
    }
    
    size_t len = strlen(content);
    size_t written = fwrite(content, 1, len, file);
    
    fclose(file);
    
    if (written != len) {
        XMD_WARNING("Failed to write complete content to %s", path);
        return -1;
    }
    
    return 0;
}

/**
 * Append content to file
 * Returns 0 on success, -1 on failure
 */
static inline int xmd_append_file(const char* path, const char* content) {
    XMD_NULL_CHECK(path, -1);
    XMD_NULL_CHECK(content, -1);
    
    FILE* file = fopen(path, "a");
    if (!file) {
        XMD_WARNING("Cannot open file for append: %s", path);
        return -1;
    }
    
    size_t len = strlen(content);
    size_t written = fwrite(content, 1, len, file);
    
    fclose(file);
    
    if (written != len) {
        XMD_WARNING("Failed to append complete content to %s", path);
        return -1;
    }
    
    return 0;
}

/**
 * Check if file exists
 * Returns 1 if exists, 0 if not
 */
static inline int xmd_file_exists(const char* path) {
    if (!path) return 0;
    
    struct stat st;
    return (stat(path, &st) == 0);
}

/**
 * Get file size
 * Returns size in bytes, or -1 on error
 */
static inline long xmd_file_size(const char* path) {
    XMD_NULL_CHECK(path, -1);
    
    struct stat st;
    if (stat(path, &st) != 0) {
        return -1;
    }
    
    return st.st_size;
}

/**
 * Read file line by line with callback
 * Returns number of lines processed, or -1 on error
 */
typedef int (*xmd_line_callback)(const char* line, size_t line_num, void* user_data);

static inline int xmd_read_lines(const char* path, xmd_line_callback callback, void* user_data) {
    XMD_NULL_CHECK(path, -1);
    XMD_NULL_CHECK(callback, -1);
    
    FILE* file = fopen(path, "r");
    if (!file) {
        XMD_WARNING("Cannot open file: %s", path);
        return -1;
    }
    
    char line[4096];
    size_t line_num = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        
        // Remove trailing newline
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\\n') {
            line[len - 1] = '\\0';
        }
        
        if (callback(line, line_num, user_data) != 0) {
            break;
        }
    }
    
    fclose(file);
    return line_num;
}

/**
 * Create directory if it doesn't exist
 * Returns 0 on success, -1 on failure
 */
static inline int xmd_mkdir(const char* path) {
    XMD_NULL_CHECK(path, -1);
    
    struct stat st;
    if (stat(path, &st) == 0) {
        // Already exists
        return S_ISDIR(st.st_mode) ? 0 : -1;
    }
    
    // Create directory with rwx permissions for owner
    #ifdef _WIN32
        return mkdir(path);
    #else
        return mkdir(path, 0700);
    #endif
}

/**
 * Copy file from source to destination
 * Returns 0 on success, -1 on failure
 */
static inline int xmd_copy_file(const char* src, const char* dest) {
    XMD_NULL_CHECK(src, -1);
    XMD_NULL_CHECK(dest, -1);
    
    char* content = xmd_read_file(src);
    if (!content) {
        return -1;
    }
    
    int result = xmd_write_file(dest, content);
    free(content);
    
    return result;
}

#endif /* XMD_FILE_OPS_H */