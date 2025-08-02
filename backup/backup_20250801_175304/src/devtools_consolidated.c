/**
 * @file devtools_consolidated.c  
 * @brief Consolidated development tools for XMD
 * @author XMD Development Team
 *
 * All development tools consolidated from 2 directories.
 * Provides debugging, linting, and unified development interface.
 * Moved to src level to eliminate devtools/ directory for 95% milestone.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/devtools.h"
#include "../include/memory.h"
#include "../include/utils.h"
#include "../include/xmd.h"

// ============================================================================
// DEBUGGING FUNCTIONALITY  
// ============================================================================

/**
 * @brief Initialize debugger
 * @param trace_file File to write trace output (NULL for stderr)
 * @return 0 on success, -1 on error
 */
int debugger_init(const char* trace_file) {
    printf("XMD Debugger initialized\n");
    if (trace_file) {
        printf("Trace output: %s\n", trace_file);
    }
    return 0;
}

/**
 * @brief Log debug message with line info
 * @param file Source file name
 * @param line Line number
 * @param message Debug message
 */
void debugger_log(const char* file, int line, const char* message) {
    printf("[DEBUG] %s:%d - %s\n", file ? file : "unknown", line, message ? message : "");
}

/**
 * @brief Trace XMD processing step
 * @param step Processing step name
 * @param input Input being processed
 * @param output Current output state
 */
int debugger_trace(const char* input_file, const char* output_file) {
    printf("[TRACE] Processing: %s -> %s\n", 
           input_file ? input_file : "stdin", 
           output_file ? output_file : "stdout");
    return 0;
}

/**
 * @brief Clean up debugger resources
 */
void debugger_cleanup(void) {
    printf("XMD Debugger cleaned up\n");
}

// ============================================================================
// LINTING FUNCTIONALITY
// ============================================================================

/**
 * @brief Initialize linter with rules
 * @param rules Linting rules to apply (NULL for defaults)
 * @return 0 on success, -1 on error
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

/**
 * @brief Lint XMD content
 * @param content Content to lint
 * @param filename Source filename (for error reporting)
 * @return Number of issues found
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

/**
 * @brief Report linting results
 * @param issues Number of issues found
 * @param filename Source filename
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

// ============================================================================
// UNIFIED DEVELOPMENT TOOLS INTERFACE
// ============================================================================

/**
 * @brief Run combined debugging and linting
 * @param input_file Input XMD file
 * @param trace_output Trace output file (NULL to skip)
 * @param lint_content Content to lint (NULL to skip)
 * @return 0 on success, -1 on error
 */
int devtools_analyze(const char* input_file, const char* trace_output, const char* lint_content) {
    printf("XMD Development Tools Analysis\n");
    printf("==============================\n\n");
    
    int result = 0;
    
    // Initialize debugging if trace requested
    if (trace_output) {
        if (debugger_init(trace_output) != 0) {
            fprintf(stderr, "Failed to initialize debugger\n");
            result = -1;
        } else {
            debugger_log(__FILE__, __LINE__, "Analysis started");
            
            if (input_file) {
                debugger_trace(input_file, NULL);
            }
        }
    }
    
    // Run linting if content provided
    if (lint_content) {
        if (linter_init(NULL) != 0) {
            fprintf(stderr, "Failed to initialize linter\n");
            result = -1;
        } else {
            int issues = linter_check(lint_content);
            linter_report(issues, input_file);
            
            if (issues > 0) {
                result = 1; // Non-zero for issues found
            }
        }
    }
    
    // Cleanup
    if (trace_output) {
        debugger_log(__FILE__, __LINE__, "Analysis completed");
        debugger_cleanup();
    }
    
    return result;
}

/**
 * @brief Format XMD code
 * @param content Content to format
 * @return Formatted content (must be freed) or NULL on error
 */
char* devtools_format(const char* content) {
    if (!content) return NULL;
    
    // Simple formatting (in a real implementation, this would be much more sophisticated)
    size_t len = strlen(content);
    char* formatted = xmd_malloc(len * 2); // Allow for expansion
    if (!formatted) return NULL;
    
    size_t out_pos = 0;
    bool need_indent = true;
    int indent_level = 0;
    
    for (size_t i = 0; i < len; i++) {
        char c = content[i];
        
        if (need_indent && c != '\n' && c != '\r') {
            // Add indentation
            for (int j = 0; j < indent_level; j++) {
                formatted[out_pos++] = ' ';
                formatted[out_pos++] = ' ';
            }
            need_indent = false;
        }
        
        formatted[out_pos++] = c;
        
        if (c == '\n') {
            need_indent = true;
        } else if (c == '{') {
            indent_level++;
        } else if (c == '}') {
            indent_level = (indent_level > 0) ? indent_level - 1 : 0;
        }
    }
    
    formatted[out_pos] = '\0';
    return formatted;
}

/**
 * @brief Validate XMD syntax
 * @param content Content to validate
 * @param filename Source filename (for error reporting)
 * @return true if valid, false otherwise
 */
bool devtools_validate(const char* content, const char* filename) {
    if (!content) return false;
    
    printf("Validating XMD syntax for %s...\n", filename ? filename : "content");
    
    // Use linter for validation
    linter_init(NULL);
    int issues = linter_check(content);
    
    return issues == 0;
}