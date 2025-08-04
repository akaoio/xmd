/**
 * @file xmd_process_file.c
 * @brief Process XMD file with processor
 * 
 * This file contains ONLY the xmd_process_file function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../../../include/xmd.h"
#include "../../../../../include/c_api_internal.h"
#include "../../../../../include/utils.h"
#include "../../../../../utils/common/common_macros.h"
/**
 * @brief Process XMD file with processor
 * @param processor XMD processor
 * @param filename File to process
 * @return Processing result or NULL on error
  * /
 */
xmd_result* xmd_process_file(xmd_processor* processor, const char* filename) {
    XMD_VALIDATE_PTRS(c_api_create_result(-1, NULL, "Invalid processor or filename"), processor, filename);
    
    // Read file content
    FILE* file = fopen(filename, "r");
    if (!file) {
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "Cannot open file: %s", filename);
        return c_api_create_result(-1, NULL, error_msg);
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content = xmd_malloc(size + 1);
    if (!content) {
        fclose(file);
        return c_api_create_result(-1, NULL, "Memory allocation failed");
    }
    
    fread(content, 1, size, file);
    content[size] = '\0';
    fclose(file);
    // Process content using existing function
    xmd_result* result = xmd_process_string(processor, content, size);
    XMD_FREE_SAFE(content);
    return result;
}
