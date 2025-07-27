/**
 * @file process_text_with_directives.c
 * @brief Process text with directives (backward compatibility) implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Process text with directives (for backward compatibility)
 * @param text Text content with directives to process
 * @param var_store Variable store for processing
 * @param output Buffer to store output
 * @param output_size Size of output buffer
 * @return Length of output on success, -1 on error
 */
int process_text_with_directives(const char* text, store* var_store, char* output, size_t output_size) {
    char* result = process_xmd_content(text, var_store);
    if (!result) {
        output[0] = '\0';
        return -1;
    }
    
    size_t result_len = strlen(result);
    if (result_len >= output_size) {
        result_len = output_size - 1;
    }
    
    memcpy(output, result, result_len);
    output[result_len] = '\0';
    
    free(result);
    return result_len;
}
