/**
 * @file linter_report.c
 * @brief Report linting results
 * 
 * This file contains ONLY the linter_report function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/devtools_consolidated.c
 */

#include <stdio.h>
#include "../../../../include/devtools.h"
/**
 * @brief Report linting results
 * @param issues Number of issues found
 * @param filename Source filename
  * /
 */
void linter_report(int issues, const char* filename) {
    printf("\nLinting Report for %s:\n", filename ? filename : "content");
    printf("Issues found: %d\n", issues);
    
    if (issues == 0) {
        printf("Status: ✅ PASSED\n");
    } else if (issues <= 5) {
        printf("Status: ⚠️  WARNINGS\n");
    } else {
        printf("Status: ❌ FAILED\n");
    }
}
