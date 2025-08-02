/**
 * @file ast_evaluator_free.c
 * @brief Implementation of ast_evaluator_free function
 * 
 * This file contains ONLY the ast_evaluator_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "utils/common/common_macros.h"
#include "ast_evaluator.h"
#include "ast_node.h"
#include "error.h"
#include "store.h"
#include "variable.h"
/**
 * @brief Free AST evaluator
 * @param evaluator Evaluator to free
 */
void ast_evaluator_free(ast_evaluator* evaluator) {
    if (!evaluator) {
        return;
    }
    
    // DO NOT destroy variables store - evaluator doesn't own it!
    // The variables store is owned by the processor and will be freed by xmd_processor_free
    XMD_FREE_SAFE(evaluator->output_buffer);
    XMD_FREE_SAFE(evaluator->error_message);
    XMD_FREE_SAFE(evaluator);
}
