
#ifndef XMD_AST_EVALUATOR_H
#define XMD_AST_EVALUATOR_H

#include "store.h"
#include "ast.h"

/* Forward declarations */
typedef struct ast_evaluator ast_evaluator;

/**
 * @brief AST-based XMD content processor (replaces all string-based processors)
 * @param input Input content containing XMD directives in HTML comments
 * @param variables Variable store for processing
 * @return Processed content (caller must free) or NULL on error
 */
char* ast_process_xmd_content(const char* input, store* variables);

#endif /* XMD_AST_EVALUATOR_H */
