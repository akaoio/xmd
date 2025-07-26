/**
 * @file preprocess_variables.c
 * @brief Variable preprocessing function
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Preprocess variables by extracting and storing them, and removing set directives
 * @param input Input content
 * @param input_length Input length
 * @param var_store Variable store
 * @param output Output buffer with set directives removed
 * @param output_size Output buffer size
 * @return 0 on success, -1 on error
 */
int preprocess_variables(const char* input, size_t input_length, store* var_store, 
                        char* output, size_t output_size) {
    const char* ptr = input;
    const char* input_end = input + input_length;
    size_t output_pos = 0;
    
    while (ptr < input_end && output_pos < output_size - 1) {
        // Look for set directive
        const char* set_start = strstr(ptr, "<!-- xmd:set ");
        if (!set_start) {
            // No more set directives, copy rest of input
            size_t remaining = input_end - ptr;
            if (output_pos + remaining < output_size - 1) {
                memcpy(output + output_pos, ptr, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Copy content before set directive
        size_t before_len = set_start - ptr;
        if (output_pos + before_len < output_size - 1) {
            memcpy(output + output_pos, ptr, before_len);
            output_pos += before_len;
        }
        
        // Find the end of the set directive
        const char* set_end = strstr(set_start, "-->");
        if (!set_end) {
            // Malformed directive, copy as-is
            if (output_pos + strlen(set_start) < output_size - 1) {
                strcpy(output + output_pos, set_start);
                output_pos += strlen(set_start);
            }
            break;
        }
        set_end += 3; // Skip -->
        
        // Extract set arguments
        const char* args_start = set_start + 13; // Skip "<!-- xmd:set "
        size_t args_len = set_end - 3 - args_start; // Don't include -->
        
        if (args_len > 0 && args_len < 512) {
            char args[512];
            strncpy(args, args_start, args_len);
            args[args_len] = '\0';
            
            // Create a proper directive string for processing
            char directive[600];
            snprintf(directive, sizeof(directive), "xmd:set %s", args);
            
            // Process the set directive
            char dummy_output[64];
            process_xmd_directive(directive, var_store, dummy_output, sizeof(dummy_output));
        }
        
        // Skip the set directive entirely (don't copy to output)
        ptr = set_end;
    }
    
    output[output_pos] = '\0';
    return 0;
}
