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
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Parse indexed loop statement "for i, item in items"
 * @param pos Pointer to current position in input (will be advanced)
 * @return Loop AST node or NULL if not an indexed loop
 */
ast_node* ast_parse_indexed_loop(const char** pos) {
    XMD_VALIDATE_PTR_RETURN(pos, NULL);
    XMD_PARSE_VALIDATE_POS(pos, NULL);
    
    const char* start = *pos;
    const char* saved_pos = *pos;
    source_location loc = {1, *pos - start, NULL};
    
    // Expect 'for' keyword
    XMD_PARSE_EXPECT_KEYWORD(pos, "for", {
        *pos = saved_pos;
        return NULL;
    });
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse first identifier (index variable)
    const char* index_start;
    const char* index_end;
    XMD_PARSE_IDENTIFIER(pos, index_start, index_end, {
        *pos = saved_pos;
        return NULL;
    });
    
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Look for comma
    if (**pos != ',') {
        // Not indexed iteration, restore position
        *pos = saved_pos;
        return NULL;
    }
    (*pos)++; // Skip comma
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse second identifier (item variable)
    const char* item_start;
    const char* item_end;
    XMD_PARSE_IDENTIFIER(pos, item_start, item_end, {
        *pos = saved_pos;
        return NULL;
    });
    
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Expect 'in' keyword
    XMD_PARSE_EXPECT_KEYWORD(pos, "in", {
        *pos = saved_pos;
        return NULL;
    });
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse iterable expression
    ast_node* iterable = ast_parse_expression(pos);
    if (!iterable) {
        *pos = saved_pos;
        return NULL;
    }
    
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse loop body
    ast_node* body = ast_parse_statement(pos);
    if (!body) {
        ast_free(iterable);
        XMD_ERROR_RETURN(NULL, "Expected statement after 'for i, item in items'");
    }
    
    // Create index variable name
    size_t index_len = index_end - index_start;
    char* index_var;
    XMD_MALLOC_VALIDATED(index_var, char, index_len + 1, {
        ast_free(iterable);
        ast_free(body);
        return NULL;
    });
    memcpy(index_var, index_start, index_len);
    index_var[index_len] = '\0';
    
    // Create item variable name  
    size_t item_len = item_end - item_start;
    char* item_var;
    XMD_MALLOC_VALIDATED(item_var, char, item_len + 1, {
        XMD_FREE_SAFE(index_var);
        ast_free(iterable);
        ast_free(body);
        return NULL;
    });
    memcpy(item_var, item_start, item_len);
    item_var[item_len] = '\0';
    
    // Create standard loop node with item variable (index handling will be done in evaluator)
    ast_node* loop_node = ast_create_loop(item_var, iterable, loc);
    if (!loop_node) {
        XMD_FREE_SAFE(index_var);
        XMD_FREE_SAFE(item_var);
        ast_free(iterable);
        ast_free(body);
        return NULL;
    }
    
    // Store index variable name in a special way - we'll use the loop variable field
    // to store both variables. For now, use item_var as primary.
    XMD_FREE_SAFE(loop_node->data.loop.variable);
    
    // Create combined variable string "index,item" for evaluator to parse
    size_t combined_len = strlen(index_var) + strlen(item_var) + 2;
    char* combined_var;
    XMD_MALLOC_VALIDATED(combined_var, char, combined_len, {
        XMD_FREE_SAFE(index_var);
        XMD_FREE_SAFE(item_var);
        ast_free(loop_node);
        return NULL;
    });
    
    snprintf(combined_var, combined_len, "%s,%s", index_var, item_var);
    loop_node->data.loop.variable = combined_var;
    loop_node->data.loop.body = body;
    
    XMD_FREE_SAFE(index_var);
    XMD_FREE_SAFE(item_var);
    
    return loop_node;
}