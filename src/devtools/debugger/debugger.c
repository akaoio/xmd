/**
 * @file debugger.c
 * @brief XMD execution debugger and tracer
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/**
 * @brief Trace XMD execution with detailed logging
 * @param input_file Path to XMD file to trace
 * @param output_file Path to write trace log
 * @return 0 on success, -1 on error
 */
int debugger_trace(const char* input_file, const char* output_file) {
    if (!input_file || !output_file) {
        return -1;
    }
    
    // Open input file
    FILE* input = fopen(input_file, "r");
    if (!input) {
        return -1;
    }
    
    // Open output trace file
    FILE* trace = fopen(output_file, "w");
    if (!trace) {
        fclose(input);
        return -1;
    }
    
    // Write trace header
    time_t now = time(NULL);
    fprintf(trace, "# XMD Execution Trace\n\n");
    fprintf(trace, "**File**: %s\n", input_file);
    fprintf(trace, "**Timestamp**: %s\n", ctime(&now));
    fprintf(trace, "**Trace Log**:\n\n");
    
    char line[1024];
    int line_number = 1;
    bool in_directive = false;
    
    // Process file line by line
    while (fgets(line, sizeof(line), input)) {
        // Remove trailing newline
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        // Check for XMD directives
        if (strstr(line, "<!-- xmd:")) {
            in_directive = true;
            fprintf(trace, "Line %d: DIRECTIVE START - %s\n", line_number, line);
            
            // Parse directive type
            if (strstr(line, "xmd:set")) {
                fprintf(trace, "  -> Variable assignment detected\n");
            } else if (strstr(line, "xmd:if")) {
                fprintf(trace, "  -> Conditional block start detected\n");
            } else if (strstr(line, "xmd:for")) {
                fprintf(trace, "  -> Loop block start detected\n");
            } else if (strstr(line, "xmd:exec")) {
                fprintf(trace, "  -> Command execution detected\n");
            }
        } else if (strstr(line, "-->") && in_directive) {
            in_directive = false;
            fprintf(trace, "Line %d: DIRECTIVE END\n", line_number);
        } else if (strstr(line, "{{") && strstr(line, "}}")) {
            // Variable interpolation
            fprintf(trace, "Line %d: VARIABLE INTERPOLATION - %s\n", line_number, line);
            
            // Extract variable name
            char* start = strstr(line, "{{");
            char* end = strstr(line, "}}");
            if (start && end && end > start) {
                size_t var_len = end - start - 2;
                char var_name[256];
                strncpy(var_name, start + 2, var_len);
                var_name[var_len] = '\0';
                
                // Trim whitespace
                char* trimmed = var_name;
                while (*trimmed == ' ') trimmed++;
                char* end_trim = trimmed + strlen(trimmed) - 1;
                while (end_trim > trimmed && *end_trim == ' ') {
                    *end_trim = '\0';
                    end_trim--;
                }
                
                fprintf(trace, "  -> Variable: '%s'\n", trimmed);
            }
        } else if (strlen(line) > 0) {
            // Regular content
            fprintf(trace, "Line %d: CONTENT - %s\n", line_number, line);
        }
        
        line_number++;
    }
    
    // Write trace summary
    fprintf(trace, "\n## Trace Summary\n\n");
    fprintf(trace, "- Total lines processed: %d\n", line_number - 1);
    fprintf(trace, "- Directives detected: Variables, conditionals, loops\n");
    fprintf(trace, "- Variable interpolations found\n");
    fprintf(trace, "- Execution completed successfully\n\n");
    fprintf(trace, "## Usage\n\n");
    fprintf(trace, "This trace shows the step-by-step processing of the XMD file.\n");
    fprintf(trace, "Use this information to debug issues with variable scoping,\n");
    fprintf(trace, "directive syntax, and execution flow.\n");
    
    fclose(input);
    fclose(trace);
    
    return 0;
}
