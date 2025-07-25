/**
 * @file test_output.c
 * @brief Test suite for output formatting system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/output.h"

// These functions are now implemented in the main library

/**
 * @brief Test basic output formatting
 */
void test_basic_output_formatting(void) {
    printf("Testing basic output formatting...\n");
    
    OutputFormatter* formatter = output_formatter_new();
    assert(formatter != NULL);
    
    const char* test_input = "Hello, World!\nThis is a test.";
    char* result = NULL;
    
    // Test raw format (no changes)
    int status = output_format_text(formatter, test_input, OUTPUT_FORMAT_RAW, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strcmp(result, test_input) == 0);
    free(result);
    
    // Test code format (should wrap in code block)
    result = NULL;
    status = output_format_text(formatter, test_input, OUTPUT_FORMAT_CODE, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strstr(result, "```") != NULL); // Should contain code block markers
    free(result);
    
    output_formatter_free(formatter);
    
    printf("✓ Basic output formatting tests passed\n");
}

/**
 * @brief Test HTML escaping
 */
void test_html_escaping(void) {
    printf("Testing HTML escaping...\n");
    
    const char* html_input = "<script>alert('xss')</script>&copy;";
    char* result = NULL;
    
    int status = output_escape_html(html_input, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    
    // Check that dangerous characters are escaped
    assert(strstr(result, "&lt;script&gt;") != NULL);
    assert(strstr(result, "&amp;copy;") != NULL);
    assert(strstr(result, "<script>") == NULL); // Should not contain raw script tags
    
    free(result);
    
    // Test empty input
    result = NULL;
    status = output_escape_html("", &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strlen(result) == 0);
    free(result);
    
    // Test NULL input
    result = NULL;
    status = output_escape_html(NULL, &result);
    assert(status == OUTPUT_ERROR);
    
    printf("✓ HTML escaping tests passed\n");
}

/**
 * @brief Test JSON escaping
 */
void test_json_escaping(void) {
    printf("Testing JSON escaping...\n");
    
    const char* json_input = "Hello \"World\"!\nThis has\ttabs and\rcarriage returns.";
    char* result = NULL;
    
    int status = output_escape_json(json_input, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    
    // Check that special characters are escaped
    assert(strstr(result, "\\\"") != NULL); // Quotes should be escaped
    assert(strstr(result, "\\n") != NULL);  // Newlines should be escaped
    assert(strstr(result, "\\t") != NULL);  // Tabs should be escaped
    assert(strstr(result, "\\r") != NULL);  // Carriage returns should be escaped
    
    free(result);
    
    // Test backslash escaping
    result = NULL;
    status = output_escape_json("Path\\to\\file", &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strstr(result, "\\\\") != NULL); // Backslashes should be escaped
    free(result);
    
    printf("✓ JSON escaping tests passed\n");
}

/**
 * @brief Test code block formatting
 */
void test_code_formatting(void) {
    printf("Testing code formatting...\n");
    
    const char* code_input = "function hello() {\n    console.log('Hello!');\n}";
    char* result = NULL;
    
    // Test with language specification
    int status = output_format_as_code(code_input, "javascript", &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strstr(result, "```javascript") != NULL);
    assert(strstr(result, code_input) != NULL);
    assert(strstr(result, "```\n") != NULL || strstr(result, "```") != NULL);
    free(result);
    
    // Test without language specification
    result = NULL;
    status = output_format_as_code(code_input, NULL, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strstr(result, "```") != NULL);
    free(result);
    
    // Test with empty language
    result = NULL;
    status = output_format_as_code(code_input, "", &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strstr(result, "```") != NULL);
    free(result);
    
    printf("✓ Code formatting tests passed\n");
}

/**
 * @brief Test ANSI code stripping
 */
void test_ansi_stripping(void) {
    printf("Testing ANSI code stripping...\n");
    
    const char* ansi_input = "\033[31mRed text\033[0m and \033[1mbold text\033[0m";
    char* result = NULL;
    
    int status = output_strip_ansi_codes(ansi_input, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    
    // Check that ANSI codes are removed
    assert(strstr(result, "\033[") == NULL); // No ANSI escape sequences
    assert(strstr(result, "Red text") != NULL); // Text should remain
    assert(strstr(result, "bold text") != NULL);
    
    free(result);
    
    // Test input without ANSI codes
    result = NULL;
    status = output_strip_ansi_codes("Plain text", &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strcmp(result, "Plain text") == 0);
    free(result);
    
    printf("✓ ANSI stripping tests passed\n");
}

/**
 * @brief Test output truncation
 */
void test_output_truncation(void) {
    printf("Testing output truncation...\n");
    
    const char* long_input = "This is a very long string that should be truncated when it exceeds the maximum length limit.";
    char* result = NULL;
    
    // Test truncation
    int status = output_truncate(long_input, 20, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strlen(result) <= 23); // 20 + 3 for "..."
    assert(strstr(result, "...") != NULL); // Should end with ellipsis
    free(result);
    
    // Test no truncation needed
    result = NULL;
    status = output_truncate("Short", 100, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strcmp(result, "Short") == 0);
    assert(strstr(result, "...") == NULL); // No ellipsis needed
    free(result);
    
    // Test edge case - exact length
    result = NULL;
    status = output_truncate("Exact", 5, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strcmp(result, "Exact") == 0);
    free(result);
    
    printf("✓ Output truncation tests passed\n");
}

/**
 * @brief Test format-specific output
 */
void test_format_specific_output(void) {
    printf("Testing format-specific output...\n");
    
    OutputFormatter* formatter = output_formatter_new();
    const char* test_input = "Sample output with <tags> & \"quotes\"";
    char* result = NULL;
    
    // Test HTML format
    int status = output_format_text(formatter, test_input, OUTPUT_FORMAT_HTML, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    // Should have HTML escaping
    assert(strstr(result, "&lt;tags&gt;") != NULL);
    free(result);
    
    // Test JSON format
    result = NULL;
    status = output_format_text(formatter, test_input, OUTPUT_FORMAT_JSON, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    // Should have JSON escaping
    assert(strstr(result, "\\\"quotes\\\"") != NULL);
    free(result);
    
    // Test Markdown format
    result = NULL;
    status = output_format_text(formatter, test_input, OUTPUT_FORMAT_MARKDOWN, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    // Should preserve most characters for markdown
    free(result);
    
    output_formatter_free(formatter);
    
    printf("✓ Format-specific output tests passed\n");
}

/**
 * @brief Test error handling and edge cases
 */
void test_output_edge_cases(void) {
    printf("Testing output edge cases...\n");
    
    OutputFormatter* formatter = output_formatter_new();
    char* result = NULL;
    
    // Test NULL input
    int status = output_format_text(formatter, NULL, OUTPUT_FORMAT_RAW, &result);
    assert(status == OUTPUT_ERROR);
    
    // Test NULL formatter
    status = output_format_text(NULL, "test", OUTPUT_FORMAT_RAW, &result);
    assert(status == OUTPUT_ERROR);
    
    // Test invalid format
    status = output_format_text(formatter, "test", (OutputFormat)999, &result);
    assert(status == OUTPUT_INVALID_FORMAT);
    
    // Test empty input
    status = output_format_text(formatter, "", OUTPUT_FORMAT_RAW, &result);
    assert(status == OUTPUT_SUCCESS);
    assert(result != NULL);
    assert(strlen(result) == 0);
    free(result);
    
    output_formatter_free(formatter);
    
    // Test double free (should not crash)
    output_formatter_free(NULL);
    
    printf("✓ Output edge case tests passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Output Formatting Tests ===\n");
    
    test_basic_output_formatting();
    test_html_escaping();
    test_json_escaping();
    test_code_formatting();
    test_ansi_stripping();
    test_output_truncation();
    test_format_specific_output();
    test_output_edge_cases();
    
    printf("\n✅ All output formatting tests passed!\n");
    return 0;
}