/**
 * @file ast_substitute_variables.c
 * @brief Implementation of ast_substitute_variables function
 * 
 * This file contains ONLY the ast_substitute_variables function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "module.h"
#include "store.h"
#include "utils.h"
#include "variable.h"
/**
 * @brief Substitute variables in AST text content
 * @param content Text containing variable references
 * @param variables Variable store
 * @return Substituted text (must be freed) or NULL
char* ast_substitute_variables(const char* content, store* variables) {
    if (!content) {
        return NULL;
    }
    
    if (!variables) {
        return xmd_strdup(content);
    // Calculate result size (approximate)
    size_t result_size = strlen(content) * 2;
    char* result = xmd_malloc(result_size);
    if (!result) {
    size_t result_pos = 0;
    const char* pos = content;
    while (*pos) {
        if (*pos == '$' && (pos[1] == '{' || isalnum(pos[1]) || pos[1] == '_')) {
            // Variable reference found
            const char* var_start = pos + 1;
            const char* var_end = NULL;
            
            if (*var_start == '{') {
                // ${variable} format
                var_start++;
                var_end = strchr(var_start, '}');
                if (!var_end) {
                    // Unterminated variable reference
                    XMD_FREE_SAFE(result);
                    return NULL;
                }
            } else {
                // $variable format
                var_end = var_start;
                while (isalnum(*var_end) || *var_end == '_') {
                    var_end++;
            }
            // Extract variable name
            size_t var_len = var_end - var_start;
            char* var_name = xmd_malloc(var_len + 1);
            if (!var_name) {
                XMD_FREE_SAFE(result);
                return NULL;
            strncpy(var_name, var_start, var_len);
            var_name[var_len] = '\0';
            // Look up variable
            variable* var = store_get(variables, var_name);
            XMD_FREE_SAFE(var_name);
            if (var) {
                const char* var_value = variable_to_string(var);
                if (var_value) {
                    size_t value_len = strlen(var_value);
                    
                    // Expand result buffer if needed
                    while (result_pos + value_len >= result_size) {
                        result_size *= 2;
                        char* new_result = xmd_realloc(result, result_size);
                        if (!new_result) {
                            XMD_FREE_SAFE(result);
                            return NULL;
                        }
                        result = new_result;
                    }
                    strcpy(result + result_pos, var_value);
                    result_pos += value_len;
            // Skip past variable reference
            pos = var_end;
            if (*pos == '}') {
                pos++;
        } else {
            // Regular character
            if (result_pos + 1 >= result_size) {
                result_size *= 2;
                char* new_result = xmd_realloc(result, result_size);
                if (!new_result) {
                result = new_result;
            result[result_pos++] = *pos++;
        }
    result[result_pos] = '\0';
    return result;
}
