/**
 * @file devtools_validate.c
 * @brief Validate XMD syntax
 * 
 * This file contains ONLY the devtools_validate function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/devtools_consolidated.c
 */

#include <stdio.h>
#include <stdbool.h>
#include "../../../../include/devtools.h"
/**
 * @brief Validate XMD syntax
 * @param content Content to validate
 * @param filename Source filename (for error reporting)
 * @return true if valid, false otherwise
  * /
 */
bool devtools_validate(const char* content, const char* filename) {
    if (!content) return false;
    
    printf("Validating XMD syntax for %s...\n", filename ? filename : "content");
    
    // Use linter for validation
    linter_init(NULL);
    int issues = linter_check(content);
    
    return issues == 0;
}
