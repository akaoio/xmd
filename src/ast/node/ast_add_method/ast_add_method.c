/**
 * @file ast_add_method.c
 * @brief Implementation of ast_add_method function
 * 
 * This file contains ONLY the ast_add_method function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "module.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Add a method to a class definition
 * @param class_def Class definition node
 * @param method Method node to add
 * @return 0 on success, -1 on error
 */
int ast_add_method(ast_node* class_def, ast_node* method) {
    XMD_VALIDATE_PTRS(-1, class_def, method);
    if (class_def->type != AST_CLASS_DEF) {
        XMD_ERROR_STATUS(-1, "Node is not a class definition");
    }
    
    if (method->type != AST_METHOD_DEF) {
        XMD_ERROR_STATUS(-1, "Node is not a method definition");
    }
    
    // Check if this is the constructor
    if (method->data.method_def.name && 
        strcmp(method->data.method_def.name, "constructor") == 0) {
        // Set as constructor
        if (class_def->data.class_def.constructor) {
            XMD_FREE_NULL(class_def->data.class_def.constructor);
        }
        class_def->data.class_def.constructor = method;
        return 0;
    }
    
    // Regular method - add to methods array
    XMD_REALLOC_VALIDATED(class_def->data.class_def.methods, ast_node*, 
                          (class_def->data.class_def.method_count + 1) * sizeof(ast_node*), -1);
    class_def->data.class_def.methods[class_def->data.class_def.method_count] = method;
    class_def->data.class_def.method_count++;
    return 0;
}
