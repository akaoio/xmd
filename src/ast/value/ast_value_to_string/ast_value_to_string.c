/**
 * @file ast_value_to_string.c
 *
 * @brief Implementation of ast_value_to_string function
 * 
 * This file contains ONLY the ast_value_to_string function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "utils.h"
#include <string.h>
#include "error.h"
#include "utils/common/common_macros.h"
/**
 * @brief Convert AST value to string
 * @param value AST value
 * @return String representation or NULL on error
 */
char* ast_value_to_string(ast_value* value) {
    XMD_NULL_CHECK(value, NULL);
    
    switch (value->type) {
        case AST_VAL_STRING:
            return xmd_strdup(value->value.string_value);
            
        case AST_VAL_NUMBER: {
            char* buffer = xmd_malloc(32);
            if (buffer) {
                snprintf(buffer, 32, "%.6g", value->value.number_value);
            }
            return buffer;
        }
        
        case AST_VAL_BOOLEAN:
            return xmd_strdup(value->value.boolean_value ? "true" : "false");
            
        case AST_VAL_NULL:
            return xmd_strdup("");
            
        case AST_VAL_ARRAY: {
            // Calculate total size needed
            size_t total_size = 3; // "[]\0"
            char** element_strings = xmd_malloc(sizeof(char*) * value->value.array_value.element_count);
            XMD_NULL_CHECK(element_strings, NULL);
            
            // Convert each element to string
            for (size_t i = 0; i < value->value.array_value.element_count; i++) {
                element_strings[i] = ast_value_to_string(value->value.array_value.elements[i]);
                if (!element_strings[i]) {
                    // Clean up on error
                    for (size_t j = 0; j < i; j++) {
                        XMD_FREE_SAFE(element_strings[j]);
                    }
                    XMD_FREE_SAFE(element_strings);
                    return NULL;
                }
                total_size += strlen(element_strings[i]);
                if (i > 0) total_size += 2; // ", "
            }
            
            // Build array string
            char* result = xmd_malloc(total_size);
            if (!result) {
                for (size_t i = 0; i < value->value.array_value.element_count; i++) {
                    XMD_FREE_SAFE(element_strings[i]);
                }
                XMD_FREE_SAFE(element_strings);
                return NULL;
            }
            
            strcpy(result, "[");
            for (size_t i = 0; i < value->value.array_value.element_count; i++) {
                if (i > 0) strcat(result, ", ");
                strcat(result, element_strings[i]);
                XMD_FREE_SAFE(element_strings[i]);
            }
            strcat(result, "]");
            XMD_FREE_SAFE(element_strings);
            return result;
        }
        
        default:
            return NULL;
    }
}
