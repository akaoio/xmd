/**
 * @file linter_check.c
 * @brief Lint XMD content for issues
 * 
 * This file contains ONLY the linter_check function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/devtools_consolidated.c
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../../../include/devtools.h"
/**
 * @brief Lint XMD content
 * @param content Content to lint
 * @return Number of issues found
  * /
 */
int linter_check(const char* content) {
    if (!content) return 0;
    
    int issues = 0;
    
    printf("Linting content...\n");
    
    // Basic linting checks
    size_t len = strlen(content);
    
    // Check for common issues
    if (len == 0) {
        printf("Warning: Empty content\n");
        issues++;
    }
    
    // Check for unterminated strings
    bool in_string = false; 
    for (size_t i = 0; i < len; i++) {
        if (content[i] == '"' && (i == 0 || content[i-1] != '\\')) {
            in_string = !in_string;
        }
    }
    
    if (in_string) {
        printf("Error: Unterminated string literal\n");
        issues++;
    }
    
    // Check for balanced braces
    int brace_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (content[i] == '{') brace_count++;
        else if (content[i] == '}') brace_count--;
    }
    
    if (brace_count != 0) {
        printf("Error: Unbalanced braces (off by %d)\n", brace_count);
        issues++;
    }
    
    if (issues == 0) {
        printf("✅ No issues found\n");
    } else {
        printf("❌ Found %d issue(s)\n", issues);
    }
    
    return issues;
}
