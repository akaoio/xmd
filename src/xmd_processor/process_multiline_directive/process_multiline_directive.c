/**
 * @file process_multiline_directive.c
 * @brief Process multiline directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Process multiline directive
 * @param directive_content Content of the multiline directive
 * @param variables Variable store for processing
 */
void process_multiline_directive(const char* directive_content, store* variables) {
    char* content_copy = strdup(directive_content);
    char* line = strtok(content_copy, "\n\r");
    
    while (line) {
        char* trimmed = trim_whitespace(line);
        
        if (strncmp(trimmed, "xmd:", 4) == 0) {
            // Skip initial "xmd:" line
        } else if (strncmp(trimmed, "set ", 4) == 0) {
            // Process set directive
            processor_context temp_ctx = { .variables = variables, .if_stack_size = 0 };
            char dummy[16];
            process_set(trimmed + 4, &temp_ctx, dummy, sizeof(dummy));
        }
        
        line = strtok(NULL, "\n\r");
    }
    
    free(content_copy);
}
