/**
 * @file xmd_dispatch_content.c
 * @brief Dispatch XMD content to appropriate processor (HTML vs native)
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/native_xmd.h"
#include "../../../include/utils.h"
#include "../../../include/store.h"

// Forward declaration for dependencies
extern bool xmd_is_native_syntax(const char* content);
extern char* ast_process_xmd_content(const char* input, store* variables);

/**
 * @brief Dispatch XMD content to appropriate processor (HTML vs native)
 * @param content Input content to process
 * @return Processed output (caller must free)
 */
char* xmd_dispatch_content(const char* content) {
    if (!content) {
        return NULL;
    }
    
    // Detect content type
    if (xmd_is_native_syntax(content)) {
        // Process as native XMD using AST system
        store* variables = store_create();
        if (!variables) {
            return xmd_strdup(content); // Fallback
        }
        
        char* result = ast_process_xmd_content(content, variables);
        store_destroy(variables);
        
        return result ? result : xmd_strdup(content);
    } else {
        // For now, treat as plain text
        // TODO: Add HTML comment processor if needed
        return xmd_strdup(content);
    }
}