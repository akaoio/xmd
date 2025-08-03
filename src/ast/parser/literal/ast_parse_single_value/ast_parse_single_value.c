/**
 * @file ast_parse_single_value.c
 * @brief Implementation of ast_parse_single_value function
 * 
 * This file contains ONLY the ast_parse_single_value function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "variable.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Parse single value (string, number, identifier) without comma handling
 * @param pos Pointer to current position
 * @return Value AST node or NULL
 */
ast_node* ast_parse_single_value(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    const char* start = *pos;
    
    // Skip whitespace
    while (*start && isspace(*start) && *start != '\n') start++;
    if (!*start || *start == '\n') {
        return NULL;
    }
    // Parse string literal
    if (*start == '"') {
        const char* str_start = start;
        return ast_parse_string_literal(&str_start, pos);
    }
    // Parse number
    if (isdigit(*start) || (*start == '-' && isdigit(*(start+1)))) {
        return ast_parse_number_literal(&start, pos);
    }
    // Parse identifier
    const char* id_start = start;
    while (*start && (isalnum(*start) || *start == '_')) {
        start++;
    }
    if (start > id_start) {
        size_t id_len = start - id_start;
        char* id_str;
        XMD_MALLOC_SAFE(id_str, char[id_len + 1], NULL, "ast_parse_single_value: Failed to allocate identifier");
        strncpy(id_str, id_start, id_len);
        id_str[id_len] = '\0';
        source_location loc = {1, 1, "input"};
        ast_node* result = ast_create_identifier(id_str, loc);
        XMD_FREE_SAFE(id_str);
        *pos = start;
        return result;
    }
    return NULL;
}
