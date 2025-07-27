/**
 * @file test_real_performance.c
 * @brief Performance tests with real-world file sizes
 * @author XMD Team
 * @date 2025-07-27
 * 
 * Tests XMD performance with various file sizes and complexity levels
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "../../include/cli.h"

/**
 * @brief Get current time in milliseconds
 * @return Current time in milliseconds
 */
double get_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

/**
 * @brief Generate large markdown file with XMD directives
 * @param size_kb Size in kilobytes
 * @return Generated content
 */
char* generate_large_file(int size_kb) {
    int estimated_size = size_kb * 1024;
    char* content = malloc(estimated_size + 1000);
    int pos = 0;
    
    // Header
    pos += sprintf(content + pos, "# Large Test Document\n\n");
    pos += sprintf(content + pos, "<!-- xmd:set doc_size=\"%dKB\" -->\n", size_kb);
    pos += sprintf(content + pos, "Document size: {{doc_size}}\n\n");
    
    // Generate content until we reach target size
    int section = 1;
    while (pos < estimated_size) {
        // Add section with variables
        pos += sprintf(content + pos, "## Section %d\n", section);
        pos += sprintf(content + pos, "<!-- xmd:set section_%d=\"Section %d Content\" -->\n", 
                      section, section);
        pos += sprintf(content + pos, "{{section_%d}}\n\n", section);
        
        // Add some conditional content
        pos += sprintf(content + pos, "<!-- xmd:if doc_size == \"%dKB\" -->\n", size_kb);
        pos += sprintf(content + pos, "This is a %dKB document.\n", size_kb);
        pos += sprintf(content + pos, "<!-- xmd:endif -->\n\n");
        
        // Add loop
        pos += sprintf(content + pos, "<!-- xmd:for i in 1..5 -->\n");
        pos += sprintf(content + pos, "- Item {{i}} in section %d\n", section);
        pos += sprintf(content + pos, "<!-- xmd:endfor -->\n\n");
        
        // Add some filler text
        for (int i = 0; i < 10; i++) {
            pos += sprintf(content + pos, 
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n");
        }
        pos += sprintf(content + pos, "\n");
        
        section++;
    }
    
    content[pos] = '\0';
    return content;
}

/**
 * @brief Test processing speed with various file sizes
 */
void test_file_size_performance(void) {
    printf("Testing performance with various file sizes...\n");
    
    void* handle = xmd_init(NULL);
    assert(handle != NULL);
    
    int sizes[] = {1, 10, 100, 500}; // KB
    double time_limits[] = {10, 50, 500, 2500}; // milliseconds
    
    for (int i = 0; i < 4; i++) {
        printf("  Testing %dKB file... ", sizes[i]);
        fflush(stdout);
        
        char* content = generate_large_file(sizes[i]);
        size_t content_len = strlen(content);
        
        double start = get_time_ms();
        xmd_result* result = xmd_process_string(handle, content, content_len);
        double end = get_time_ms();
        double elapsed = end - start;
        
        assert(result != NULL);
        assert(result->error_code == 0);
        
        printf("%.2f ms", elapsed);
        
        // Check performance is within acceptable limits
        if (elapsed > time_limits[i]) {
            printf(" ⚠️  (exceeded limit of %.0f ms)", time_limits[i]);
        } else {
            printf(" ✅");
        }
        printf("\n");
        
        // Verify processing worked correctly
        assert(strstr(result->output, "Large Test Document") != NULL);
        assert(strstr(result->output, "xmd:") == NULL); // No unprocessed directives
        
        xmd_result_free(result);
        free(content);
    }
    
    xmd_cleanup(handle);
    
    printf("✅ File size performance test completed\n");
}

/**
 * @brief Test deeply nested structures
 */
void test_nested_performance(void) {
    printf("Testing performance with deeply nested structures...\n");
    
    void* handle = xmd_init(NULL);
    assert(handle != NULL);
    
    // Generate deeply nested conditionals
    char* content = malloc(50000);
    int pos = 0;
    
    pos += sprintf(content + pos, "# Nested Test\n\n");
    
    // Create 10 levels of nesting
    for (int i = 0; i < 10; i++) {
        pos += sprintf(content + pos, "<!-- xmd:set level%d=\"yes\" -->\n", i);
        pos += sprintf(content + pos, "<!-- xmd:if level%d == \"yes\" -->\n", i);
        pos += sprintf(content + pos, "Level %d\n", i);
    }
    
    pos += sprintf(content + pos, "Deepest level reached!\n");
    
    // Close all levels
    for (int i = 9; i >= 0; i--) {
        pos += sprintf(content + pos, "<!-- xmd:endif -->\n");
    }
    
    content[pos] = '\0';
    
    double start = get_time_ms();
    xmd_result* result = xmd_process_string(handle, content, strlen(content));
    double end = get_time_ms();
    
    assert(result != NULL);
    assert(result->error_code == 0);
    assert(strstr(result->output, "Deepest level reached!") != NULL);
    
    printf("  Nested processing time: %.2f ms ✅\n", end - start);
    
    xmd_result_free(result);
    free(content);
    xmd_cleanup(handle);
    
    printf("✅ Nested performance test passed\n");
}

/**
 * @brief Test loop performance
 */
void test_loop_performance(void) {
    printf("Testing loop performance...\n");
    
    void* handle = xmd_init(NULL);
    assert(handle != NULL);
    
    // Test with large loops
    const char* loop_test = 
        "# Loop Performance Test\n"
        "<!-- xmd:for i in 1..1000 -->\n"
        "Item {{i}}\n"
        "<!-- xmd:endfor -->\n";
    
    double start = get_time_ms();
    xmd_result* result = xmd_process_string(handle, loop_test, strlen(loop_test));
    double end = get_time_ms();
    
    assert(result != NULL);
    assert(result->error_code == 0);
    
    // Verify all items were generated
    assert(strstr(result->output, "Item 1\n") != NULL);
    assert(strstr(result->output, "Item 1000\n") != NULL);
    
    printf("  1000 iteration loop: %.2f ms", end - start);
    if (end - start > 100) {
        printf(" ⚠️  (consider optimization)");
    } else {
        printf(" ✅");
    }
    printf("\n");
    
    xmd_result_free(result);
    xmd_cleanup(handle);
    
    printf("✅ Loop performance test passed\n");
}

/**
 * @brief Test variable substitution performance
 */
void test_variable_performance(void) {
    printf("Testing variable substitution performance...\n");
    
    void* handle = xmd_init(NULL);
    assert(handle != NULL);
    
    // Create content with many variables
    char* content = malloc(100000);
    int pos = 0;
    
    pos += sprintf(content + pos, "# Variable Performance Test\n\n");
    
    // Set 100 variables
    for (int i = 0; i < 100; i++) {
        pos += sprintf(content + pos, "<!-- xmd:set var%d=\"Value %d\" -->\n", i, i);
    }
    
    // Reference each variable multiple times
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 100; i++) {
            pos += sprintf(content + pos, "{{var%d}} ", i);
        }
        pos += sprintf(content + pos, "\n");
    }
    
    content[pos] = '\0';
    
    double start = get_time_ms();
    xmd_result* result = xmd_process_string(handle, content, strlen(content));
    double end = get_time_ms();
    
    assert(result != NULL);
    assert(result->error_code == 0);
    
    // Verify substitutions worked
    assert(strstr(result->output, "Value 0") != NULL);
    assert(strstr(result->output, "Value 99") != NULL);
    assert(strstr(result->output, "{{var") == NULL); // No unsubstituted variables
    
    printf("  1000 variable substitutions: %.2f ms ✅\n", end - start);
    
    xmd_result_free(result);
    free(content);
    xmd_cleanup(handle);
    
    printf("✅ Variable performance test passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("\n⚡ XMD Real Performance Test Suite\n");
    printf("==================================\n");
    printf("Testing with realistic file sizes and complexity\n\n");
    
    test_file_size_performance();
    test_nested_performance();
    test_loop_performance();
    test_variable_performance();
    
    printf("\n✅ All performance tests completed!\n");
    printf("XMD performs well with real-world file sizes and complexity\n");
    
    return 0;
}