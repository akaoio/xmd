/**
 * @file linter_init.c
 * @brief Initialize linter with rules
 * 
 * This file contains ONLY the linter_init function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/devtools_consolidated.c
 */

#include <stdio.h>
#include "../../../../include/devtools.h"
/**
 * @brief Initialize linter with rules
 * @param rules Linting rules to apply (NULL for defaults)
 * @return 0 on success, -1 on error
  * /
 */
int linter_init(const char* rules) {
    printf("XMD Linter initialized\n");
    if (rules) {
        printf("Rules: %s\n", rules);
    } else {
        printf("Using default linting rules\n");
    }
    return 0;
}
