/**
 * @file linter.c
 * @brief XMD syntax and style linter
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * @brief Check XMD syntax and style
 * @param content XMD content to check
 * @return 0 if valid, -1 if errors found
 */
int linter_check(const char* content) {
    if (!content) {
        return -1;
    }
    
    int errors = 0;
    int warnings = 0;
    int line_number = 1;
    
    printf("Running XMD linter...\n\n");
    
    const char* pos = content;
    const char* line_start = pos;
    
    // Track directive balance
    int if_count = 0;
    int for_count = 0;
    int try_count = 0;
    
    while (*pos) {
        if (*pos == '\n') {
            // Process current line
            size_t line_len = pos - line_start;
            char line[1024];
            strncpy(line, line_start, line_len);
            line[line_len] = '\0';
            
            // Check for common issues
            
            // 1. Check for unbalanced directives
            if (strstr(line, "<!-- xmd:if")) {
                if_count++;
            } else if (strstr(line, "<!-- xmd:endif")) {
                if_count--;
                if (if_count < 0) {
                    printf("Error [Line %d]: Unmatched endif directive\n", line_number);
                    errors++;
                    if_count = 0; // Reset to prevent cascade
                }
            }
            
            if (strstr(line, "<!-- xmd:for")) {
                for_count++;
            } else if (strstr(line, "<!-- xmd:endfor")) {
                for_count--;
                if (for_count < 0) {
                    printf("Error [Line %d]: Unmatched endfor directive\n", line_number);
                    errors++;
                    for_count = 0;
                }
            }
            
            if (strstr(line, "<!-- xmd:try")) {
                try_count++;
            } else if (strstr(line, "<!-- xmd:endtry")) {
                try_count--;
                if (try_count < 0) {
                    printf("Error [Line %d]: Unmatched endtry directive\n", line_number);
                    errors++;
                    try_count = 0;
                }
            }
            
            // 2. Check for malformed directives
            if (strstr(line, "<!-- xmd:") && !strstr(line, "-->")) {
                printf("Error [Line %d]: Unclosed XMD directive\n", line_number);
                errors++;
            }
            
            // 3. Check for malformed variable references
            char* var_start = strstr(line, "{{");
            if (var_start) {
                char* var_end = strstr(var_start, "}}");
                if (!var_end) {
                    printf("Error [Line %d]: Unclosed variable reference\n", line_number);
                    errors++;
                } else {
                    // Check variable name validity
                    size_t var_len = var_end - var_start - 2;
                    if (var_len == 0) {
                        printf("Warning [Line %d]: Empty variable reference\n", line_number);
                        warnings++;
                    }
                }
            }
            
            // 4. Style checks
            
            // Check for trailing whitespace
            if (line_len > 0 && isspace(line[line_len-1])) {
                printf("Warning [Line %d]: Trailing whitespace\n", line_number);
                warnings++;
            }
            
            // Check for mixed indentation (basic check)
            bool has_tabs = false;
            bool has_spaces = false;
            for (size_t i = 0; i < line_len && isspace(line[i]); i++) {
                if (line[i] == '\t') has_tabs = true;
                if (line[i] == ' ') has_spaces = true;
            }
            if (has_tabs && has_spaces) {
                printf("Warning [Line %d]: Mixed tabs and spaces for indentation\n", line_number);
                warnings++;
            }
            
            // Move to next line
            line_start = pos + 1;
            line_number++;
        }
        pos++;
    }
    
    // Check final balance
    if (if_count > 0) {
        printf("Error: %d unclosed if directive(s)\n", if_count);
        errors += if_count;
    }
    if (for_count > 0) {
        printf("Error: %d unclosed for directive(s)\n", for_count);
        errors += for_count;
    }
    if (try_count > 0) {
        printf("Error: %d unclosed try directive(s)\n", try_count);
        errors += try_count;
    }
    
    // Print summary
    printf("\nLinter Summary:\n");
    printf("- Lines checked: %d\n", line_number - 1);
    printf("- Errors: %d\n", errors);
    printf("- Warnings: %d\n", warnings);
    
    if (errors == 0 && warnings == 0) {
        printf("✓ No issues found\n");
        return 0;
    } else if (errors == 0) {
        printf("✓ No errors found (warnings can be ignored)\n");
        return 0;
    } else {
        printf("✗ Errors found - fix before processing\n");
        return -1;
    }
}
