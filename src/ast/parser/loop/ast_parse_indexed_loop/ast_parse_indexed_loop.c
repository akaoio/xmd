/**
 * @file ast_parse_indexed_loop.c
 * @brief Implementation of ast_parse_indexed_loop function
 * 
 * This file contains ONLY the ast_parse_indexed_loop function.
 * One function per file - Genesis principle compliance.
 * Parses "for i, item in items" statements (indexed iteration)
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "ast.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Parse indexed loop statement "for i, item in items"
 * @param pos Pointer to current position in input (will be advanced)
 * @return Loop AST node or NULL if not an indexed loop
 */
ast_node* ast_parse_indexed_loop(const char** pos) {
    if (!pos || !*pos) return NULL;
    
    const char* saved_pos = *pos;
    source_location loc = {1, 1, "input"};
    
    // Check for 'for' keyword
    if (strncmp(*pos, "for", 3) != 0 || ((*pos)[3] && !isspace((*pos)[3]))) {
        return NULL;
    }
    *pos += 3;
    
    // Skip whitespace
    while (**pos && isspace(**pos)) (*pos)++;
    
    // Parse first identifier (index variable)
    if (!isalpha(**pos) && **pos != '_') {
        *pos = saved_pos;
        return NULL;
    }
    
    const char* index_start = *pos;
    while (isalnum(**pos) || **pos == '_') (*pos)++;
    const char* index_end = *pos;
    
    // Skip whitespace
    while (**pos && isspace(**pos)) (*pos)++;
    
    // Look for comma
    if (**pos != ',') {
        // Not indexed iteration, restore position
        *pos = saved_pos;
        return NULL;
    }
    (*pos)++; // Skip comma
    
    // Skip whitespace
    while (**pos && isspace(**pos)) (*pos)++;
    
    // Parse second identifier (item variable)
    if (!isalpha(**pos) && **pos != '_') {
        *pos = saved_pos;
        return NULL;
    }
    
    const char* item_start = *pos;
    while (isalnum(**pos) || **pos == '_') (*pos)++;
    const char* item_end = *pos;
    
    // Skip whitespace
    while (**pos && isspace(**pos)) (*pos)++;
    
    // Check for 'in' keyword
    if (strncmp(*pos, "in", 2) != 0 || ((*pos)[2] && !isspace((*pos)[2]))) {
        *pos = saved_pos;
        return NULL;
    }
    *pos += 2;
    
    // Skip whitespace
    while (**pos && isspace(**pos)) (*pos)++;
    
    // Parse iterable expression
    ast_node* iterable = ast_parse_expression(pos);
    if (!iterable) {
        *pos = saved_pos;
        return NULL;
    }
    
    // Skip whitespace
    while (**pos && isspace(**pos)) (*pos)++;
    
    // Parse loop body
    ast_node* body = ast_parse_statement(pos);
    if (!body) {
        ast_free(iterable);
        *pos = saved_pos;
        return NULL;
    }
    
    // Create index variable name
    size_t index_len = index_end - index_start;
    char* index_var = xmd_malloc(index_len + 1);
    if (!index_var) {
        ast_free(iterable);
        ast_free(body);
        return NULL;
    }
    memcpy(index_var, index_start, index_len);
    index_var[index_len] = '\0';
    
    // Create item variable name  
    size_t item_len = item_end - item_start;
    char* item_var = xmd_malloc(item_len + 1);
    if (!item_var) {
        xmd_free(index_var);
        ast_free(iterable);
        ast_free(body);
        return NULL;
    }
    memcpy(item_var, item_start, item_len);
    item_var[item_len] = '\0';
    
    // Create standard loop node with item variable
    ast_node* loop_node = ast_create_loop(item_var, iterable, loc);
    if (!loop_node) {
        xmd_free(index_var);
        xmd_free(item_var);
        ast_free(iterable);
        ast_free(body);
        return NULL;
    }
    
    // Store index variable name in a special way
    // Create combined variable string "index,item" for evaluator to parse
    size_t combined_len = strlen(index_var) + strlen(item_var) + 2;
    char* combined_var = xmd_malloc(combined_len);
    if (!combined_var) {
        xmd_free(index_var);
        xmd_free(item_var);
        ast_free(loop_node);
        return NULL;
    }
    
    snprintf(combined_var, combined_len, "%s,%s", index_var, item_var);
    xmd_free(loop_node->data.loop.variable);
    loop_node->data.loop.variable = combined_var;
    loop_node->data.loop.body = body;
    
    xmd_free(index_var);
    xmd_free(item_var);
    
    return loop_node;
}