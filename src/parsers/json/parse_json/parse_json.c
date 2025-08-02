/**
 * @file parse_json.c
 * @brief Parse JSON content specifically
 * 
 * This file contains ONLY the parse_json function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/parsers_consolidated.c
 */

#include "../../../../include/variable.h"

// Forward declaration
extern variable* parse_json_value(const char* json);
/**
 * @brief Parse JSON content specifically
 * @param json JSON content string
 * @return Variable containing parsed JSON data or NULL
 */
variable* parse_json(const char* json) {
    return parse_json_value(json);
}
