/**
 * @file native_evaluate_program.c
 * @brief Evaluate native XMD program and return output
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

// Forward declaration for dependency
extern char* xmd_dispatch_content(const char* content);

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
