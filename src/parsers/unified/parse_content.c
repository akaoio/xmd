/**
 * @file parse_content.c
 * @brief Parse content with automatic format detection
 * 
 * This file contains ONLY the parse_content function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/parsers_consolidated.c (with syntax fixes)
 */

#include <string.h>
#include "../../../include/variable.h"

// Parser type enumeration
typedef enum {
    PARSER_TYPE_JSON,
    PARSER_TYPE_YAML,
    PARSER_TYPE_AUTO
} parser_type;

// Forward declarations
extern parser_type detect_parser_type(const char* content);
extern variable* parse_json_value(const char* json);
extern variable* parse_yaml_value(const char* yaml);
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
