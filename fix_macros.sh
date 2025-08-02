#!/bin/bash

FILES_TO_FIX=(
    "/data/data/com.termux/files/home/xmd/src/ast/value/ast_value_create_string/ast_value_create_string.c"
    "/data/data/com.termux/files/home/xmd/src/ast/value/ast_value_create_number/ast_value_create_number.c"
    "/data/data/com.termux/files/home/xmd/src/ast/value/ast_value_create_boolean/ast_value_create_boolean.c"
    "/data/data/com.termux/files/home/xmd/src/ast/value/ast_value_to_string/ast_value_to_string.c"
    "/data/data/com.termux/files/home/xmd/src/ast/value/misc/ast_value_array_add.c"
    "/data/data/com.termux/files/home/xmd/src/token/create/token_create.c"
    "/data/data/com.termux/files/home/xmd/src/token/operations/token_set_value/token_set_value.c"
    "/data/data/com.termux/files/home/xmd/src/token/operations/token_duplicate/token_duplicate.c"
    "/data/data/com.termux/files/home/xmd/src/token/operations/token_copy/token_copy.c"
    "/data/data/com.termux/files/home/xmd/src/token/list/token_list_get/token_list_get.c"
    "/data/data/com.termux/files/home/xmd/src/token/list/token_list_append/token_list_append.c"
    "/data/data/com.termux/files/home/xmd/src/token/convert/token_to_string.c"
    "/data/data/com.termux/files/home/xmd/src/variable/create/variable_create_consolidated/variable_create_consolidated.c"
    "/data/data/com.termux/files/home/xmd/src/variable/create/variable_create_array/variable_create_array.c"
    "/data/data/com.termux/files/home/xmd/src/variable/create/variable_create_number/variable_create_number.c"
    "/data/data/com.termux/files/home/xmd/src/variable/create/variable_create_string/variable_create_string.c"
    "/data/data/com.termux/files/home/xmd/src/variable/operations/variable_copy/variable_copy.c"
    "/data/data/com.termux/files/home/xmd/src/variable/object/variable_object_set/variable_object_set.c"
    "/data/data/com.termux/files/home/xmd/src/variable/object/variable_object_get/variable_object_get.c"
    "/data/data/com.termux/files/home/xmd/src/store/operations/store_set/store_set.c"
    "/data/data/com.termux/files/home/xmd/src/store/operations/store_get/store_get.c"
    "/data/data/com.termux/files/home/xmd/src/store/operations/store_remove/store_remove.c"
)

echo "Files to fix: ${#FILES_TO_FIX[@]}"
for file in "${FILES_TO_FIX[@]}"; do
    echo "$file"
done