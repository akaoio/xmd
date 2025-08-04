/**
 * @file ast_parse_try_catch.c
 * @brief Implementation of ast_parse_try_catch function
 * 
 * This file contains ONLY the ast_parse_try_catch function.
 * One function per file - Genesis principle compliance.
 * Parses try-catch error handling statements
 */

#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Parse try-catch statement
 * @param pos Pointer to current position in input (will be advanced)
 * @return Try-catch AST node or NULL on error
 */
ast_node* ast_parse_try_catch(const char** pos) {
    XMD_VALIDATE_PTR_RETURN(pos, NULL);
    XMD_PARSE_VALIDATE_POS(pos, NULL);
    
    const char* start = *pos;
    source_location loc = {1, *pos - start, NULL};
    
    // Expect 'try' keyword
    XMD_PARSE_EXPECT_KEYWORD(pos, "try", NULL);
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse try block
    ast_node* try_block = ast_parse_statement(pos);
    if (!try_block) {
        XMD_ERROR_RETURN(NULL, "Expected statement after 'try'");
    }
    
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Expect 'catch' keyword
    if (strncmp(*pos, "catch", 5) != 0 || ((*pos)[5] && !isspace((*pos)[5]))) {
        ast_free(try_block);
        return NULL;
    }
    *pos += 5;
    
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse optional catch variable name
    char* catch_var = NULL;
    const char* var_start = NULL;
    const char* var_end = NULL;
    
    // Check if there's an identifier for the catch variable
    if (isalpha(**pos) || **pos == '_') {
        var_start = *pos;
        while (isalnum(**pos) || **pos == '_') {
            (*pos)++;
        }
        var_end = *pos;
        
        size_t var_len = var_end - var_start;
        catch_var = xmd_malloc(var_len + 1);
        if (!catch_var) {
            ast_free(try_block);
            return NULL;
        }
        
        memcpy(catch_var, var_start, var_len);
        catch_var[var_len] = '\0';
    }
    
    XMD_PARSE_SKIP_WHITESPACE(pos);
    
    // Parse catch block
    ast_node* catch_block = ast_parse_statement(pos);
    if (!catch_block) {
        ast_free(try_block);
        XMD_FREE_SAFE(catch_var);
        XMD_ERROR_RETURN(NULL, "Expected statement after 'catch'");
    }
    
    // Create try-catch node
    ast_node* try_catch = ast_create_try_catch(try_block, catch_var, catch_block, loc);
    XMD_FREE_SAFE(catch_var);
    
    if (!try_catch) {
        ast_free(try_block);
        ast_free(catch_block);
        return NULL;
    }
    
    return try_catch;
}