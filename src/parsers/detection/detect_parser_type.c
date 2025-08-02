/**
 * @file detect_parser_type.c
 * @brief Detect parser type from content
 * 
 * This file contains ONLY the detect_parser_type function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/parsers_consolidated.c (with syntax fixes)
 */

#include <ctype.h>
#include <string.h>
#include "../../../include/xmd.h"

// Parser type enumeration
typedef enum {
    PARSER_TYPE_JSON,
    PARSER_TYPE_YAML,
    PARSER_TYPE_AUTO
} parser_type;
/**
 * @brief Detect parser type from content
 * @param content Content to analyze
 * @return Detected parser type
 */
static parser_type detect_parser_type(const char* content) {
    if (!content) {
        return PARSER_TYPE_JSON; // Default fallback
    }
    
    // Skip leading whitespace
    while (isspace(*content)) content++;
    
    // Check for JSON patterns
    if (*content == '{' || *content == '[') {
        return PARSER_TYPE_JSON;
    }
    
    // Check for YAML patterns (key: value, - item, etc.)
    const char* line = content;
    while (*line) {
        // Skip whitespace at start of line
        while (isspace(*line) && *line != '\n') line++;
        
        if (*line == '-' && (isspace(line[1]) || line[1] == '\0')) {
            return PARSER_TYPE_YAML; // YAML list item
        }
        
        // Look for key: value pattern
        const char* colon = strchr(line, ':');
        const char* newline = strchr(line, '\n');
        if (colon && (newline == NULL || colon < newline)) {
            // Check if there's whitespace after colon (YAML style)
            if (colon[1] == ' ' || colon[1] == '\t' || colon[1] == '\n' || colon[1] == '\0') {
                return PARSER_TYPE_YAML;
            }
        }
        
        // Move to next line
        if (newline) {
            line = newline + 1;
        } else {
            break;
        }
    }
    
    return PARSER_TYPE_JSON; // Default fallback
}
