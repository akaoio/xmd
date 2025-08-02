/**
 * @file parsers_consolidated.c
 * @brief Consolidated parsers for XMD (JSON and YAML)
 * @author XMD Development Team
 *
 * All parser functionality consolidated from 2 directories.
 * Provides unified JSON and YAML parsing with format detection.
 * Moved to src level to eliminate parsers/ directory for 95% milestone.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../include/variable.h"
#include "../include/xmd.h"
#include "../include/memory.h"
#include "../include/utils.h"

// Parser type enumeration
typedef enum {
    PARSER_TYPE_JSON,
    PARSER_TYPE_YAML,
    PARSER_TYPE_AUTO
} parser_type;

// Forward declarations
static variable* parse_json_value(const char* json);
static variable* parse_yaml_value(const char* yaml);
static parser_type detect_parser_type(const char* content);

// ============================================================================
// UNIFIED PARSER TYPE DETECTION
// ============================================================================

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

// ============================================================================
// JSON PARSING FUNCTIONALITY
// ============================================================================

/**
 * @brief Parse JSON string value
 * @param json JSON content
 * @return Variable containing parsed value or NULL
 */
static variable* parse_json_value(const char* json) {
    if (!json) return NULL;
    
    // Skip leading whitespace
    while (isspace(*json)) json++;
    
    // Simple JSON parsing (basic implementation)
    if (*json == '"') {
        // String value
        json++; // Skip opening quote
        const char* end = strchr(json, '"');
        if (!end) return NULL;
        
        size_t len = end - json;
        char* str_value = malloc(len + 1);
        if (!str_value) return NULL;
        
        strncpy(str_value, json, len);
        str_value[len] = '\0';
        
        variable* result = variable_create_string(str_value);
        free(str_value);
        return result;
    } else if (isdigit(*json) || *json == '-') {
        // Number value
        double num_value = strtod(json, NULL);
        return variable_create_number(num_value);
    } else if (strncmp(json, "true", 4) == 0) {
        return variable_create_boolean(true);
    } else if (strncmp(json, "false", 5) == 0) {
        return variable_create_boolean(false);
    } else if (strncmp(json, "null", 4) == 0) {
        return variable_create_null();
    }
    
    // For complex objects/arrays, return as string for now
    return variable_create_string(json);
}

// ============================================================================
// YAML PARSING FUNCTIONALITY
// ============================================================================

/**
 * @brief Parse YAML string value
 * @param yaml YAML content
 * @return Variable containing parsed value or NULL
 */
static variable* parse_yaml_value(const char* yaml) {
    if (!yaml) return NULL;
    
    // Skip leading whitespace
    while (isspace(*yaml)) yaml++;
    
    // Simple YAML parsing (basic implementation)
    if (*yaml == '"' || *yaml == '\'') {
        // Quoted string
        char quote = *yaml;
        yaml++; // Skip opening quote
        const char* end = strchr(yaml, quote);
        if (!end) return NULL;
        
        size_t len = end - yaml;
        char* str_value = malloc(len + 1);
        if (!str_value) return NULL;
        
        strncpy(str_value, yaml, len);
        str_value[len] = '\0';
        
        variable* result = variable_create_string(str_value);
        free(str_value);
        return result;
    } else if (isdigit(*yaml) || *yaml == '-') {
        // Number value
        double num_value = strtod(yaml, NULL);
        return variable_create_number(num_value);
    } else if (strncmp(yaml, "true", 4) == 0 || strncmp(yaml, "yes", 3) == 0) {
        return variable_create_boolean(true);
    } else if (strncmp(yaml, "false", 5) == 0 || strncmp(yaml, "no", 2) == 0) {
        return variable_create_boolean(false);
    } else if (strncmp(yaml, "null", 4) == 0 || strncmp(yaml, "~", 1) == 0) {
        return variable_create_null();
    } else {
        // Unquoted string - find end of value
        const char* end = yaml;
        while (*end && *end != '\n' && *end != '\r') end++;
        
        size_t len = end - yaml;
        char* str_value = malloc(len + 1);
        if (!str_value) return NULL;
        
        strncpy(str_value, yaml, len);
        str_value[len] = '\0';
        
        // Trim trailing whitespace
        char* trim_end = str_value + len - 1;
        while (trim_end > str_value && isspace(*trim_end)) {
            *trim_end = '\0';
            trim_end--;
        }
        
        variable* result = variable_create_string(str_value);
        free(str_value);
        return result;
    }
}

// ============================================================================
// UNIFIED PARSER INTERFACE
// ============================================================================

/**
 * @brief Parse content with automatic format detection
 * @param content Content to parse
 * @param force_type Force specific parser type (NULL for auto-detect)
 * @return Variable containing parsed data or NULL
 */
variable* parse_content(const char* content, const char* force_type) {
    if (!content) return NULL;
    
    parser_type type = PARSER_TYPE_AUTO;
    
    if (force_type) {
        if (strcmp(force_type, "json") == 0) {
            type = PARSER_TYPE_JSON;
        } else if (strcmp(force_type, "yaml") == 0) {
            type = PARSER_TYPE_YAML;
        }
    }
    
    if (type == PARSER_TYPE_AUTO) {
        type = detect_parser_type(content);
    }
    
    switch (type) {
        case PARSER_TYPE_JSON:
            return parse_json_value(content);
        case PARSER_TYPE_YAML:
            return parse_yaml_value(content);
        default:
            return parse_json_value(content); // Fallback
    }
}

/**
 * @brief Parse JSON content specifically
 * @param json JSON content string
 * @return Variable containing parsed JSON data or NULL
 */
variable* parse_json(const char* json) {
    return parse_json_value(json);
}

/**
 * @brief Parse YAML content specifically
 * @param yaml YAML content string
 * @return Variable containing parsed YAML data or NULL
 */
variable* parse_yaml(const char* yaml) {
    return parse_yaml_value(yaml);
}