/**
 * @file optimizer_internal.h
 * @brief Internal header for optimizer functions
 * @author XMD Team
 */

#ifndef OPTIMIZER_INTERNAL_H
#define OPTIMIZER_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "performance.h"
#include "token.h"

/**
 * @brief Global optimization state structure
 */
struct optimizer_state_struct {
    perf_optimization_level level;
    bool initialized;
    uint32_t optimizations_applied;
};

/**
 * @brief Global optimization state
 */
extern struct optimizer_state_struct optimizer_state;

// Internal function declarations
bool should_apply_optimization(ast_optimization_pass pass);
uint32_t apply_constant_folding(token** tokens, size_t* token_count);
uint32_t apply_dead_code_elimination(token** tokens, size_t* token_count);
uint32_t apply_common_subexpression_elimination(token** tokens, size_t* token_count);
uint32_t apply_loop_unrolling(token** tokens, size_t* token_count);
uint32_t apply_inline_expansion(token** tokens, size_t* token_count);

// Public function declarations
int perf_optimizer_init(perf_optimization_level level);
int perf_optimize_ast(token** tokens, size_t* token_count, uint32_t passes);
void perf_optimizer_cleanup(void);

#endif /* OPTIMIZER_INTERNAL_H */