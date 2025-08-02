/**
 * @file parse_yaml.c
 * @brief Parse YAML content specifically
 * 
 * This file contains ONLY the parse_yaml function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/parsers_consolidated.c
 */

#include "../../../../include/variable.h"

// Forward declaration
extern variable* parse_yaml_value(const char* yaml);
/**
 * @brief Parse YAML content specifically
 * @param yaml YAML content string
 * @return Variable containing parsed YAML data or NULL
 */
variable* parse_yaml(const char* yaml) {
    return parse_yaml_value(yaml);
}
