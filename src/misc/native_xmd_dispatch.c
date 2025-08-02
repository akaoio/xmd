/**
 * @file native_xmd_dispatch.c
 * @brief Native XMD content dispatcher - detects and processes native syntax
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Dispatches content to appropriate processor based on syntax type
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../include/native_xmd.h"
#include "../../include/utils.h"
#include "../../include/store.h"

// Forward declaration for AST-based XMD processor
extern char* ast_process_xmd_content(const char* input, store* variables);

/**
 * @brief Check if content uses Genesis's native XMD syntax
 * @param content Input content to analyze
 * @return true if native XMD syntax detected
 */
bool xmd_is_native_syntax(const char* content) {
    if (!content) {
        return false;
    }
    
    // Look for native XMD keywords at start of lines
    const char* pos = content;
    while (*pos) {
        // Skip whitespace at start of line
        while (*pos && (*pos == ' ' || *pos == '\t')) {
            pos++;
        }
        
        // Check for native XMD keywords
        if (strncmp(pos, "set ", 4) == 0 ||
            strncmp(pos, "if ", 3) == 0 ||
            strncmp(pos, "for ", 4) == 0 ||
            strncmp(pos, "while ", 6) == 0 ||
            strncmp(pos, "function ", 9) == 0 ||
            strncmp(pos, "class ", 6) == 0 ||
            strncmp(pos, "print ", 6) == 0 ||
            strstr(pos, "${") != NULL) {  // Native variable syntax
            return true;
        }
        
        // Move to next line
        while (*pos && *pos != '\n') {
            pos++;
        }
        if (*pos == '\n') {
            pos++;
        }
    }
    
    return false;
}

/**
 * @brief Get syntax type name for debugging
 * @param content Input content to analyze  
 * @return Human-readable syntax type name
 */
const char* xmd_get_syntax_name(const char* content) {
    if (!content) {
        return "empty";
    }
    
    if (xmd_is_native_syntax(content)) {
        return "native-xmd";
    }
    
    // Check for HTML comments (legacy XMD syntax)
    if (strstr(content, "<!--") != NULL) {
        return "html-comment-xmd";
    }
    
    return "plain-text";
}

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

/**
 * @brief Evaluate native XMD program and return output
 * @param input Native XMD source code
 * @return Allocated string with program output (caller must free)
 */
char* native_evaluate_program(const char* input) {
    if (!input) {
        return NULL;
    }
    
    // Use dispatch to handle the content
    return xmd_dispatch_content(input);
}