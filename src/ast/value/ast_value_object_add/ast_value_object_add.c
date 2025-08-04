/**
 * @file ast_value_object_add.c
 * @brief Implementation of ast_value_object_add function
 * 
 * This file contains ONLY the ast_value_object_add function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "utils.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Add key-value pair to object ast_value
 * @param object Object ast_value
 * @param key Key string
 * @param value Value ast_value
 * @return 0 on success, -1 on failure
 */
int ast_value_object_add(ast_value* object, const char* key, ast_value* value) {
    XMD_VALIDATE_PARAMS_3(-1, object, key, value);
    
    if (object->type != AST_VAL_OBJECT) {
        return -1;
    }
    
    // Resize arrays if needed
    size_t new_count = object->value.object_value.pair_count + 1;
    
    char** new_keys = realloc(object->value.object_value.keys, sizeof(char*) * new_count);
    XMD_VALIDATE_PTR_RETURN(new_keys, -1);
    object->value.object_value.keys = new_keys;
    
    ast_value** new_values = realloc(object->value.object_value.values, sizeof(ast_value*) * new_count);
    XMD_VALIDATE_PTR_RETURN(new_values, -1);
    object->value.object_value.values = new_values;
    
    // Copy key
    char* key_copy = xmd_strdup(key);
    XMD_VALIDATE_PTR_RETURN(key_copy, -1);
    
    // Add to arrays
    size_t index = object->value.object_value.pair_count;
    object->value.object_value.keys[index] = key_copy;
    object->value.object_value.values[index] = value;
    object->value.object_value.pair_count = new_count;
    
    return 0;
}