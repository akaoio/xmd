/**
 * @file test_lexer.c
 * @brief Comprehensive tests for lexer functionality
 * @author XMD Team
 *
 * Tests lexical analysis including tokenization of markdown elements,
 * XMD directives, and UTF-8 support with position tracking.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lexer.h"
#include "token.h"

/**
 * @brief Test basic lexer creation and destruction
 */
void test_lexer_create_destroy(void) {
    const char* input = "Hello World";
    lexer* lex = lexer_create(input);
    
    assert(lex != NULL);
    assert(lexer_get_position(lex) == 0);
    assert(lexer_get_line(lex) == 1);
    assert(lexer_get_column(lex) == 1);
    
    lexer_destroy(lex);
    
    // Test with NULL input
    lexer* null_lex = lexer_create(NULL);
    assert(null_lex == NULL);
}

/**
 * @brief Test lexing simple text
 */
void test_lexer_simple_text(void) {
    const char* input = "Hello World";
    lexer* lex = lexer_create(input);
    
    token* t = lexer_next_token(lex);
    assert(t != NULL);
    assert(t->type == TOKEN_TEXT);
    assert(strcmp(t->value, "Hello World") == 0);
    assert(t->line == 1);
    assert(t->column == 1);
    
    token_free(t);
    
    // Next token should be EOF
    token* eof = lexer_next_token(lex);
    assert(eof != NULL);
    assert(eof->type == TOKEN_EOF);
    
    token_free(eof);
    lexer_destroy(lex);
}

/**
 * @brief Test lexing markdown headings
 */
void test_lexer_headings(void) {
    const char* input = "# Main Title\n## Sub Title\n### Sub Sub Title";
    lexer* lex = lexer_create(input);
    
    // First heading
    token* t1 = lexer_next_token(lex);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_HEADING);
    assert(strcmp(t1->value, "# Main Title") == 0);
    assert(t1->line == 1);
    assert(t1->column == 1);
    token_free(t1);
    
    // Second heading
    token* t2 = lexer_next_token(lex);
    assert(t2 != NULL);
    assert(t2->type == TOKEN_HEADING);
    assert(strcmp(t2->value, "## Sub Title") == 0);
    assert(t2->line == 2);
    assert(t2->column == 1);
    token_free(t2);
    
    // Third heading
    token* t3 = lexer_next_token(lex);
    assert(t3 != NULL);
    assert(t3->type == TOKEN_HEADING);
    assert(strcmp(t3->value, "### Sub Sub Title") == 0);
    assert(t3->line == 3);
    assert(t3->column == 1);
    token_free(t3);
    
    lexer_destroy(lex);
}

/**
 * @brief Test lexing list items
 */
void test_lexer_list_items(void) {
    const char* input = "- First item\n* Second item\n+ Third item";
    lexer* lex = lexer_create(input);
    
    // Test all three list item types
    const char* expected[] = {"- First item", "* Second item", "+ Third item"};
    
    for (int i = 0; i < 3; i++) {
        token* t = lexer_next_token(lex);
        assert(t != NULL);
        assert(t->type == TOKEN_LIST_ITEM);
        assert(strcmp(t->value, expected[i]) == 0);
        assert(t->line == i + 1);
        assert(t->column == 1);
        token_free(t);
    }
    
    lexer_destroy(lex);
}

/**
 * @brief Test lexing code blocks
 */
void test_lexer_code_blocks(void) {
    const char* input = "```c\nint main() {\n    return 0;\n}\n```";
    lexer* lex = lexer_create(input);
    
    token* t = lexer_next_token(lex);
    assert(t != NULL);
    assert(t->type == TOKEN_CODE_BLOCK);
    assert(strstr(t->value, "```c") != NULL);
    assert(strstr(t->value, "int main()") != NULL);
    assert(strstr(t->value, "```") != NULL);
    assert(t->line == 1);
    assert(t->column == 1);
    
    token_free(t);
    lexer_destroy(lex);
}

/**
 * @brief Test lexing HTML comments
 */
void test_lexer_html_comments(void) {
    const char* input = "<!-- This is a comment -->\n<!-- Another comment -->";
    lexer* lex = lexer_create(input);
    
    // First comment
    token* t1 = lexer_next_token(lex);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_HTML_COMMENT);
    assert(strcmp(t1->value, "<!-- This is a comment -->") == 0);
    assert(t1->line == 1);
    assert(t1->column == 1);
    token_free(t1);
    
    // Second comment
    token* t2 = lexer_next_token(lex);
    assert(t2 != NULL);
    assert(t2->type == TOKEN_HTML_COMMENT);
    assert(strcmp(t2->value, "<!-- Another comment -->") == 0);
    assert(t2->line == 2);
    assert(t2->column == 1);
    token_free(t2);
    
    lexer_destroy(lex);
}

/**
 * @brief Test lexing XMD directives
 */
void test_lexer_xmd_directives(void) {
    const char* input = "<!-- xmd:set name=\"value\" -->\n<!-- xmd:if condition -->";
    lexer* lex = lexer_create(input);
    
    // First directive
    token* t1 = lexer_next_token(lex);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_XMD_DIRECTIVE);
    assert(strcmp(t1->value, "<!-- xmd:set name=\"value\" -->") == 0);
    assert(t1->line == 1);
    assert(t1->column == 1);
    token_free(t1);
    
    // Second directive
    token* t2 = lexer_next_token(lex);
    assert(t2 != NULL);
    assert(t2->type == TOKEN_XMD_DIRECTIVE);
    assert(strcmp(t2->value, "<!-- xmd:if condition -->") == 0);
    assert(t2->line == 2);
    assert(t2->column == 1);
    token_free(t2);
    
    lexer_destroy(lex);
}

/**
 * @brief Test lexing variable references
 */
void test_lexer_variable_references(void) {
    const char* input = "Hello {{name}}, you have {{count}} items.";
    lexer* lex = lexer_create(input);
    
    // First text
    token* t1 = lexer_next_token(lex);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_TEXT);
    assert(strcmp(t1->value, "Hello ") == 0);
    token_free(t1);
    
    // First variable
    token* t2 = lexer_next_token(lex);
    assert(t2 != NULL);
    assert(t2->type == TOKEN_VARIABLE_REF);
    assert(strcmp(t2->value, "{{name}}") == 0);
    token_free(t2);
    
    // Middle text
    token* t3 = lexer_next_token(lex);
    assert(t3 != NULL);
    assert(t3->type == TOKEN_TEXT);
    assert(strcmp(t3->value, ", you have ") == 0);
    token_free(t3);
    
    // Second variable
    token* t4 = lexer_next_token(lex);
    assert(t4 != NULL);
    assert(t4->type == TOKEN_VARIABLE_REF);
    assert(strcmp(t4->value, "{{count}}") == 0);
    token_free(t4);
    
    // Final text
    token* t5 = lexer_next_token(lex);
    assert(t5 != NULL);
    assert(t5->type == TOKEN_TEXT);
    assert(strcmp(t5->value, "items.") == 0);
    token_free(t5);
    
    lexer_destroy(lex);
}

/**
 * @brief Test lexer position tracking
 */
void test_lexer_position_tracking(void) {
    const char* input = "Line 1\nLine 2\nLine 3";
    lexer* lex = lexer_create(input);
    
    assert(lexer_get_line(lex) == 1);
    assert(lexer_get_column(lex) == 1);
    
    token* t1 = lexer_next_token(lex);
    assert(t1 != NULL);
    assert(t1->line == 1);
    assert(t1->column == 1);
    token_free(t1);
    
    token* t2 = lexer_next_token(lex);
    assert(t2 != NULL);
    assert(t2->line == 2);
    assert(t2->column == 1);
    token_free(t2);
    
    token* t3 = lexer_next_token(lex);
    assert(t3 != NULL);
    assert(t3->line == 3);
    assert(t3->column == 1);
    token_free(t3);
    
    lexer_destroy(lex);
}

/**
 * @brief Test lexer with empty input
 */
void test_lexer_empty_input(void) {
    const char* input = "";
    lexer* lex = lexer_create(input);
    
    token* t = lexer_next_token(lex);
    assert(t != NULL);
    assert(t->type == TOKEN_EOF);
    
    token_free(t);
    lexer_destroy(lex);
}

/**
 * @brief Test lexer with whitespace only
 */
void test_lexer_whitespace_only(void) {
    const char* input = "   \n\t  \n   ";
    lexer* lex = lexer_create(input);
    
    token* t = lexer_next_token(lex);
    assert(t != NULL);
    assert(t->type == TOKEN_EOF);
    
    token_free(t);
    lexer_destroy(lex);
}

/**
 * @brief Test lexer peek functionality
 */
void test_lexer_peek(void) {
    const char* input = "Hello World";
    lexer* lex = lexer_create(input);
    
    // Peek should return same token multiple times
    token* peek1 = lexer_peek_token(lex);
    token* peek2 = lexer_peek_token(lex);
    
    assert(peek1 != NULL);
    assert(peek2 != NULL);
    assert(token_equals(peek1, peek2));
    
    // Next should return the same token
    token* next = lexer_next_token(lex);
    assert(token_equals(peek1, next));
    
    token_free(peek1);
    token_free(peek2);
    token_free(next);
    lexer_destroy(lex);
}

/**
 * @brief Test lexer with mixed content
 */
void test_lexer_mixed_content(void) {
    const char* input = 
        "# Title\n"
        "Hello {{name}}!\n"
        "- Item 1\n"
        "- Item 2\n"
        "<!-- xmd:set var=\"value\" -->\n"
        "```\ncode block\n```\n"
        "<!-- comment -->";
    
    lexer* lex = lexer_create(input);
    
    token_type expected_types[] = {
        TOKEN_HEADING,
        TOKEN_TEXT,
        TOKEN_VARIABLE_REF,
        TOKEN_TEXT,
        TOKEN_LIST_ITEM,
        TOKEN_LIST_ITEM,
        TOKEN_XMD_DIRECTIVE,
        TOKEN_CODE_BLOCK,
        TOKEN_HTML_COMMENT,
        TOKEN_EOF
    };
    
    int num_expected = sizeof(expected_types) / sizeof(expected_types[0]);
    
    for (int i = 0; i < num_expected; i++) {
        token* t = lexer_next_token(lex);
        assert(t != NULL);
        assert(t->type == expected_types[i]);
        token_free(t);
    }
    
    lexer_destroy(lex);
}

/**
 * @brief Test lexer error handling
 */
void test_lexer_error_handling(void) {
    // Test with malformed XMD directive
    const char* input = "<!-- xmd:invalid";
    lexer* lex = lexer_create(input);
    
    token* t = lexer_next_token(lex);
    // Should handle gracefully, possibly as HTML comment
    assert(t != NULL);
    token_free(t);
    
    lexer_destroy(lex);
}

/**
 * @brief Test lexer with UTF-8 content
 */
void test_lexer_utf8(void) {
    const char* input = "# Título\nHello 世界 {{name}}!";
    lexer* lex = lexer_create(input);
    
    // Should handle UTF-8 correctly
    token* t1 = lexer_next_token(lex);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_HEADING);
    assert(strstr(t1->value, "Título") != NULL);
    token_free(t1);
    
    token* t2 = lexer_next_token(lex);
    assert(t2 != NULL);
    assert(t2->type == TOKEN_TEXT);
    assert(strstr(t2->value, "世界") != NULL);
    token_free(t2);
    
    lexer_destroy(lex);
}

/**
 * @brief Main test runner for lexer tests
 */
int main(void) {
    printf("Running lexer tests...\n");
    
    test_lexer_create_destroy();
    printf("✓ Lexer creation/destruction\n");
    
    test_lexer_simple_text();
    printf("✓ Simple text lexing\n");
    
    test_lexer_headings();
    printf("✓ Heading lexing\n");
    
    test_lexer_list_items();
    printf("✓ List item lexing\n");
    
    test_lexer_code_blocks();
    printf("✓ Code block lexing\n");
    
    test_lexer_html_comments();
    printf("✓ HTML comment lexing\n");
    
    test_lexer_xmd_directives();
    printf("✓ XMD directive lexing\n");
    
    test_lexer_variable_references();
    printf("✓ Variable reference lexing\n");
    
    test_lexer_position_tracking();
    printf("✓ Position tracking\n");
    
    test_lexer_empty_input();
    printf("✓ Empty input handling\n");
    
    test_lexer_whitespace_only();
    printf("✓ Whitespace-only input\n");
    
    test_lexer_peek();
    printf("✓ Peek functionality\n");
    
    test_lexer_mixed_content();
    printf("✓ Mixed content lexing\n");
    
    test_lexer_error_handling();
    printf("✓ Error handling\n");
    
    test_lexer_utf8();
    printf("✓ UTF-8 support\n");
    
    printf("All lexer tests passed!\n");
    return 0;
}