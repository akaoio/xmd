/**
 * @file test_phase2_integration.c
 * @brief Phase 2 integration tests
 * @author XMD Team
 *
 * Integration tests to verify Phase 1 (lexer/parser) and Phase 2 (variables/templates)
 * work together correctly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lexer.h"
#include "token.h"
#include "variable.h"
#include "store.h"
#include "template.h"

/**
 * @brief Test basic template processing with markdown
 */
void test_template_with_markdown() {
    printf("Testing template processing with markdown...\n");
    
    // Create a store with some variables
    store* s = store_create();
    variable* name_var = variable_create_string("XMD");
    variable* version_var = variable_create_string("1.0.0");
    
    store_set(s, "project", name_var);
    store_set(s, "version", version_var);
    
    // Create template context
    template_context* ctx = template_context_create(s);
    
    // Test template with markdown-like content
    const char* template = "# {{project}} v{{version}}\n\n"
                          "Welcome to {{project}}! This is version {{version}}.";
    
    char* result = template_process(ctx, template);
    assert(result != NULL);
    
    const char* expected = "# XMD v1.0.0\n\n"
                          "Welcome to XMD! This is version 1.0.0.";
    
    assert(strcmp(result, expected) == 0);
    
    // Clean up
    free(result);
    variable_unref(name_var);
    variable_unref(version_var);
    template_context_destroy(ctx);
    store_destroy(s);
    
    printf("✓ Template with markdown integration test passed\n");
}

/**
 * @brief Test lexer with template-like syntax
 */
void test_lexer_with_template_syntax() {
    printf("Testing lexer with template syntax...\n");
    
    const char* markdown = "# Project {{name}}\n\n"
                          "<!-- xmd set version=\"1.0\" -->\n"
                          "Version: {{version}}";
    
    lexer* lex = lexer_create(markdown);
    assert(lex != NULL);
    
    // First token should be heading
    token* t1 = lexer_next_token(lex);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_HEADING);
    assert(strstr(t1->value, "{{name}}") != NULL);
    
    // Second token should be XMD directive (lexer skips whitespace)
    token* t2 = lexer_next_token(lex);
    assert(t2 != NULL);
    assert(t2->type == TOKEN_XMD_DIRECTIVE);
    assert(strstr(t2->value, "xmd set") != NULL);
    
    // Third token should be text
    token* t3 = lexer_next_token(lex);
    assert(t3 != NULL);
    assert(t3->type == TOKEN_TEXT);
    
    // Fourth token should be variable reference
    token* t4 = lexer_next_token(lex);
    assert(t4 != NULL);
    assert(t4->type == TOKEN_VARIABLE_REF);
    assert(strstr(t4->value, "version") != NULL);
    
    // Clean up
    token_destroy(t1);
    token_destroy(t2);
    token_destroy(t3);
    token_destroy(t4);
    lexer_destroy(lex);
    
    printf("✓ Lexer with template syntax test passed\n");
}

/**
 * @brief Test variable references in tokens
 */
void test_variable_refs_in_tokens() {
    printf("Testing variable references in tokens...\n");
    
    const char* markdown = "Hello {{name}}, welcome to {{project}}!";
    
    lexer* lex = lexer_create(markdown);
    assert(lex != NULL);
    
    // Should get text tokens with variable references
    token* t1 = lexer_next_token(lex);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_TEXT);
    
    // Extract variables from the token content
    size_t var_count = 0;
    char** variables = template_extract_variables(t1->value, &var_count);
    
    if (variables != NULL) {
        assert(var_count >= 1);
        
        // Clean up variables
        for (size_t i = 0; i < var_count; i++) {
            free(variables[i]);
        }
        free(variables);
    }
    
    // Clean up
    token_destroy(t1);
    lexer_destroy(lex);
    
    printf("✓ Variable references in tokens test passed\n");
}

/**
 * @brief Test complete pipeline: lexing -> template processing
 */
void test_complete_pipeline() {
    printf("Testing complete pipeline...\n");
    
    const char* markdown = "# {{title}}\n\nProject: {{name}}";
    
    // Set up variables
    store* s = store_create();
    variable* title_var = variable_create_string("My Project");
    variable* name_var = variable_create_string("XMD");
    
    store_set(s, "title", title_var);
    store_set(s, "name", name_var);
    
    template_context* ctx = template_context_create(s);
    
    // Process the template
    char* processed = template_process(ctx, markdown);
    assert(processed != NULL);
    
    const char* expected = "# My Project\n\nProject: XMD";
    assert(strcmp(processed, expected) == 0);
    
    // Now lex the processed content
    lexer* lex = lexer_create(processed);
    assert(lex != NULL);
    
    token* t1 = lexer_next_token(lex);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_HEADING);
    assert(strcmp(t1->value, "# My Project") == 0);
    
    // Clean up
    free(processed);
    token_destroy(t1);
    lexer_destroy(lex);
    variable_unref(title_var);
    variable_unref(name_var);
    template_context_destroy(ctx);
    store_destroy(s);
    
    printf("✓ Complete pipeline test passed\n");
}

/**
 * @brief Main test function
 */
int main() {
    printf("=== Phase 2 Integration Tests ===\n");
    
    test_template_with_markdown();
    test_lexer_with_template_syntax();
    test_variable_refs_in_tokens();
    test_complete_pipeline();
    
    printf("\n✅ All Phase 2 integration tests passed!\n");
    return 0;
}
