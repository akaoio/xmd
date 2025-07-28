/**
 * @file ast_evaluator_free.c
 * @brief Free AST evaluator
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include "../../include/ast_evaluator.h"

/**
 * @brief Free AST evaluator
 * @param evaluator Evaluator to free
 */
void ast_evaluator_free(ast_evaluator* evaluator) {
    if (!evaluator) {
        return;
    }
    
    free(evaluator->error_message);
    free(evaluator);
}