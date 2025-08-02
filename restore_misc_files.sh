#!/bin/bash

echo "🔧 GENESIS LEADER - Restoring corrupted misc files..."

# ast_create_method_def.c
cat > src/misc/ast_create_method_def.c << 'EOF'
/**
 * @file ast_create_method_def.c
 * @brief Implementation of ast_create_method_def function
 * 
 * This file contains ONLY the ast_create_method_def function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Create AST method definition node
 * @param name Method name
 * @param is_private Whether method is private
 * @param loc Source location
 * @return New method def node or NULL on error
 */
ast_node* ast_create_method_def(const char* name, bool is_private, source_location loc) {
    if (!name) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_METHOD_DEF;
    node->data.method_def.name = xmd_strdup(name);
    node->data.method_def.parameters = NULL;
    node->data.method_def.parameter_count = 0;
    node->data.method_def.body = NULL;
    node->data.method_def.is_private = is_private;
    node->location = loc;
    
    if (!node->data.method_def.name) {
        free(node);
        return NULL;
    }
    
    return node;
}
EOF

# ast_create_return.c
cat > src/misc/ast_create_return.c << 'EOF'
/**
 * @file ast_create_return.c
 * @brief Implementation of ast_create_return function
 * 
 * This file contains ONLY the ast_create_return function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Create AST return statement node
 * @param value Return value expression (can be NULL)
 * @param loc Source location
 * @return New return node or NULL on error
 */
ast_node* ast_create_return(ast_node* value, source_location loc) {
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_RETURN;
    node->data.return_stmt.value = value;
    node->location = loc;
    return node;
}
EOF

# ast_create_unary_op.c
cat > src/misc/ast_create_unary_op.c << 'EOF'
/**
 * @file ast_create_unary_op.c
 * @brief Implementation of ast_create_unary_op function
 * 
 * This file contains ONLY the ast_create_unary_op function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Create AST unary operation node
 * @param op Unary operator type
 * @param operand Operand expression
 * @param loc Source location
 * @return New unary op node or NULL on error
 */
ast_node* ast_create_unary_op(unary_operator op, ast_node* operand, source_location loc) {
    if (!operand) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_UNARY_OP;
    node->data.unary_op.op = op;
    node->data.unary_op.operand = operand;
    node->location = loc;
    return node;
}
EOF

# ast_create_variable_ref.c
cat > src/misc/ast_create_variable_ref.c << 'EOF'
/**
 * @file ast_create_variable_ref.c
 * @brief Implementation of ast_create_variable_ref function
 * 
 * This file contains ONLY the ast_create_variable_ref function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Create AST variable reference node
 * @param name Variable name
 * @param loc Source location
 * @return New variable ref node or NULL on error
 */
ast_node* ast_create_variable_ref(const char* name, source_location loc) {
    if (!name) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_VARIABLE_REF;
    node->data.variable_ref.name = xmd_strdup(name);
    node->location = loc;
    
    if (!node->data.variable_ref.name) {
        free(node);
        return NULL;
    }
    
    return node;
}
EOF

echo "✅ Misc files restored successfully"