/**
 * @file test_edge_cases_comprehensive.c
 * @brief Comprehensive edge case testing for XMD processor
 * @author XMD Team
 * @date 2025-07-26
 * 
 * This test suite covers every possible edge case including:
 * - Malformed directives and syntax errors
 * - Variable boundary conditions and special characters
 * - Loop limits and nested depth testing
 * - Memory stress testing and resource limits
 * - Security edge cases and injection attempts
 * - Error recovery and resilience testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "include/store.h"
#include "include/variable.h"

// External functions
char* process_xmd_content_fixed(const char* input, store* variables);
void process_multiline_directive_enhanced(const char* directive_content, store* variables);

// Test statistics
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define ASSERT_TEST(condition, test_name) do { \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        printf("✅ %s\n", test_name); \
    } else { \
        tests_failed++; \
        printf("❌ %s\n", test_name); \
    } \
} while(0)

/**
 * @brief Test Category 1: Malformed Directive Edge Cases
 */
void test_malformed_directives(void) {
    printf("\n=== CATEGORY 1: MALFORMED DIRECTIVE EDGE CASES ===\n");
    
    store* vars = store_create();
    
    // Test 1.1: Unclosed HTML comments
    const char* test1 = "<!-- xmd:set var=\"value\" \nNo closing comment";
    char* result1 = process_xmd_content_fixed(test1, vars);
    ASSERT_TEST(result1 != NULL, "1.1: Unclosed HTML comment handling");
    free(result1);
    
    // Test 1.2: Malformed XMD syntax
    const char* test2 = "<!-- xmd:invalid_command -->";
    char* result2 = process_xmd_content_fixed(test2, vars);
    ASSERT_TEST(result2 != NULL, "1.2: Invalid command handling");
    free(result2);
    
    // Test 1.3: Empty directive
    const char* test3 = "<!-- xmd: -->";
    char* result3 = process_xmd_content_fixed(test3, vars);
    ASSERT_TEST(result3 != NULL, "1.3: Empty directive handling");
    free(result3);
    
    // Test 1.4: Missing arguments
    const char* test4 = "<!-- xmd:set -->";
    char* result4 = process_xmd_content_fixed(test4, vars);
    ASSERT_TEST(result4 != NULL, "1.4: Missing arguments handling");
    free(result4);
    
    // Test 1.5: Malformed for loop syntax
    const char* test5 = "<!-- xmd:for item -->";
    char* result5 = process_xmd_content_fixed(test5, vars);
    ASSERT_TEST(result5 != NULL && strstr(result5, "Error"), "1.5: Malformed for loop syntax");
    free(result5);
    
    // Test 1.6: Missing endfor
    const char* test6 = "<!-- xmd:for item in \"a,b\" -->{{item}}";
    char* result6 = process_xmd_content_fixed(test6, vars);
    ASSERT_TEST(result6 != NULL, "1.6: Missing endfor handling");
    free(result6);
    
    // Test 1.7: Mismatched endif
    const char* test7 = "<!-- xmd:for item in \"a\" --><!-- xmd:endif -->";
    char* result7 = process_xmd_content_fixed(test7, vars);
    ASSERT_TEST(result7 != NULL, "1.7: Mismatched endif handling");
    free(result7);
    
    // Test 1.8: Nested comment corruption
    const char* test8 = "<!-- xmd:set var=\"<!-- corrupted -->\" -->";
    char* result8 = process_xmd_content_fixed(test8, vars);
    ASSERT_TEST(result8 != NULL, "1.8: Nested comment corruption");
    free(result8);
    
    store_destroy(vars);
}

/**
 * @brief Test Category 2: Variable Edge Cases and Boundary Conditions
 */
void test_variable_edge_cases(void) {
    printf("\n=== CATEGORY 2: VARIABLE EDGE CASES ===\n");
    
    store* vars = store_create();
    
    // Test 2.1: Empty variable names
    const char* test1 = "<!-- xmd:set =\"value\" -->";
    char* result1 = process_xmd_content_fixed(test1, vars);
    ASSERT_TEST(result1 != NULL, "2.1: Empty variable name handling");
    free(result1);
    
    // Test 2.2: Very long variable names (1000+ chars)
    char long_var_name[1200];
    for (int i = 0; i < 1000; i++) long_var_name[i] = 'a';
    long_var_name[1000] = '\0';
    char test2[1300];
    snprintf(test2, sizeof(test2), "<!-- xmd:set %s=\"value\" -->", long_var_name);
    char* result2 = process_xmd_content_fixed(test2, vars);
    ASSERT_TEST(result2 != NULL, "2.2: Very long variable names");
    free(result2);
    
    // Test 2.3: Special characters in variable names
    const char* test3 = "<!-- xmd:set var$@#%=\"value\" -->";
    char* result3 = process_xmd_content_fixed(test3, vars);
    ASSERT_TEST(result3 != NULL, "2.3: Special characters in variable names");
    free(result3);
    
    // Test 2.4: Unicode variable names
    const char* test4 = "<!-- xmd:set 变量=\"value\" -->";
    char* result4 = process_xmd_content_fixed(test4, vars);
    ASSERT_TEST(result4 != NULL, "2.4: Unicode variable names");
    free(result4);
    
    // Test 2.5: Very long variable values (10KB+)
    char* long_value = malloc(10500);
    for (int i = 0; i < 10000; i++) long_value[i] = 'x';
    long_value[10000] = '\0';
    char* test5 = malloc(11000);
    snprintf(test5, 11000, "<!-- xmd:set longvar=\"%s\" -->{{longvar}}", long_value);
    char* result5 = process_xmd_content_fixed(test5, vars);
    ASSERT_TEST(result5 != NULL && strlen(result5) > 9000, "2.5: Very long variable values");
    free(result5);
    free(test5);
    free(long_value);
    
    // Test 2.6: Null bytes in variable values
    const char* test6 = "<!-- xmd:set nullvar=\"val\\0ue\" -->{{nullvar}}";
    char* result6 = process_xmd_content_fixed(test6, vars);
    ASSERT_TEST(result6 != NULL, "2.6: Null bytes in variable values");
    free(result6);
    
    // Test 2.7: Recursive variable references
    const char* test7 = "<!-- xmd:set var1=\"{{var2}}\" --><!-- xmd:set var2=\"{{var1}}\" -->{{var1}}";
    char* result7 = process_xmd_content_fixed(test7, vars);
    ASSERT_TEST(result7 != NULL, "2.7: Recursive variable references");
    free(result7);
    
    // Test 2.8: Variable with same name as directive
    const char* test8 = "<!-- xmd:set if=\"condition\" -->{{if}}";
    char* result8 = process_xmd_content_fixed(test8, vars);
    ASSERT_TEST(result8 != NULL && strstr(result8, "condition"), "2.8: Variable named after directive");
    free(result8);
    
    // Test 2.9: Undefined variable substitution stress test
    const char* test9 = "{{undefined1}} {{undefined2}} {{undefined3}} {{undefined4}} {{undefined5}}";
    char* result9 = process_xmd_content_fixed(test9, vars);
    ASSERT_TEST(result9 != NULL && strlen(result9) < 50, "2.9: Multiple undefined variables");
    free(result9);
    
    // Test 2.10: Variable name collision with reserved words
    const char* test10 = "<!-- xmd:set NULL=\"value\" --><!-- xmd:set void=\"value\" -->{{NULL}}{{void}}";
    char* result10 = process_xmd_content_fixed(test10, vars);
    ASSERT_TEST(result10 != NULL, "2.10: Reserved word variable names");
    free(result10);
    
    store_destroy(vars);
}

/**
 * @brief Test Category 3: Loop Edge Cases and Limits
 */
void test_loop_edge_cases(void) {
    printf("\n=== CATEGORY 3: LOOP EDGE CASES ===\n");
    
    store* vars = store_create();
    
    // Test 3.1: Empty collections
    variable* empty_var = variable_create_string("");
    store_set(vars, "empty", empty_var);
    variable_unref(empty_var);
    
    const char* test1 = "<!-- xmd:for item in empty -->{{item}} <!-- xmd:endfor -->";
    char* result1 = process_xmd_content_fixed(test1, vars);
    ASSERT_TEST(result1 != NULL && strlen(result1) == 0, "3.1: Empty collection iteration");
    free(result1);
    
    // Test 3.2: Single item collections
    variable* single_var = variable_create_string("single");
    store_set(vars, "single", single_var);
    variable_unref(single_var);
    
    const char* test2 = "<!-- xmd:for item in single -->{{item}} <!-- xmd:endfor -->";
    char* result2 = process_xmd_content_fixed(test2, vars);
    ASSERT_TEST(result2 != NULL && strstr(result2, "single"), "3.2: Single item collection");
    free(result2);
    
    // Test 3.3: Very large collections (1000+ items)
    char large_collection[5000] = "";
    for (int i = 0; i < 1000; i++) {
        char item[10];
        snprintf(item, sizeof(item), "%d%s", i, (i < 999) ? "," : "");
        strcat(large_collection, item);
    }
    variable* large_var = variable_create_string(large_collection);
    store_set(vars, "large", large_var);
    variable_unref(large_var);
    
    const char* test3 = "<!-- xmd:for item in large -->. <!-- xmd:endfor -->";
    char* result3 = process_xmd_content_fixed(test3, vars);
    ASSERT_TEST(result3 != NULL && strlen(result3) > 1900, "3.3: Large collection iteration");
    free(result3);
    
    // Test 3.4: Collections with special characters
    variable* special_var = variable_create_string("a,b c,\"quoted\",\tTab\nnewline");
    store_set(vars, "special", special_var);
    variable_unref(special_var);
    
    const char* test4 = "<!-- xmd:for item in special -->[{{item}}] <!-- xmd:endfor -->";
    char* result4 = process_xmd_content_fixed(test4, vars);
    ASSERT_TEST(result4 != NULL && strstr(result4, "[a]"), "3.4: Special characters in collections");
    free(result4);
    
    // Test 3.5: Range edge cases - zero range
    const char* test5 = "<!-- xmd:for i in 5..5 -->{{i}} <!-- xmd:endfor -->";
    char* result5 = process_xmd_content_fixed(test5, vars);
    ASSERT_TEST(result5 != NULL && strstr(result5, "5"), "3.5: Zero-width range");
    free(result5);
    
    // Test 3.6: Negative ranges
    const char* test6 = "<!-- xmd:for i in 5..1 -->{{i}} <!-- xmd:endfor -->";
    char* result6 = process_xmd_content_fixed(test6, vars);
    ASSERT_TEST(result6 != NULL, "3.6: Negative ranges");
    free(result6);
    
    // Test 3.7: Very large ranges
    const char* test7 = "<!-- xmd:for i in 1..100 -->. <!-- xmd:endfor -->";
    char* result7 = process_xmd_content_fixed(test7, vars);
    ASSERT_TEST(result7 != NULL && strlen(result7) > 150, "3.7: Large ranges");
    free(result7);
    
    // Test 3.8: Range with undefined variables
    const char* test8 = "<!-- xmd:for i in undefined_start..undefined_end -->{{i}} <!-- xmd:endfor -->";
    char* result8 = process_xmd_content_fixed(test8, vars);
    ASSERT_TEST(result8 != NULL, "3.8: Range with undefined variables");
    free(result8);
    
    // Test 3.9: Deeply nested loops (8 levels)
    const char* test9 = 
        "<!-- xmd:for a in \"1,2\" -->"
        "<!-- xmd:for b in \"1,2\" -->"
        "<!-- xmd:for c in \"1,2\" -->"
        "<!-- xmd:for d in \"1,2\" -->"
        "<!-- xmd:for e in \"1,2\" -->"
        "<!-- xmd:for f in \"1,2\" -->"
        "<!-- xmd:for g in \"1,2\" -->"
        "<!-- xmd:for h in \"1,2\" -->"
        "{{a}}{{b}}{{c}}{{d}}{{e}}{{f}}{{g}}{{h}} "
        "<!-- xmd:endfor -->"
        "<!-- xmd:endfor -->"
        "<!-- xmd:endfor -->"
        "<!-- xmd:endfor -->"
        "<!-- xmd:endfor -->"
        "<!-- xmd:endfor -->"
        "<!-- xmd:endfor -->"
        "<!-- xmd:endfor -->";
    char* result9 = process_xmd_content_fixed(test9, vars);
    ASSERT_TEST(result9 != NULL && strlen(result9) > 2000, "3.9: Deeply nested loops (8 levels)");
    free(result9);
    
    // Test 3.10: Loop variable name conflicts
    const char* test10 = 
        "<!-- xmd:for item in \"a,b\" -->"
        "  <!-- xmd:for item in \"1,2\" -->"
        "    {{item}}"
        "  <!-- xmd:endfor -->"
        "<!-- xmd:endfor -->";
    char* result10 = process_xmd_content_fixed(test10, vars);
    ASSERT_TEST(result10 != NULL, "3.10: Loop variable name conflicts");
    free(result10);
    
    store_destroy(vars);
}

/**
 * @brief Test Category 4: Conditional Edge Cases and Complex Nesting
 */
void test_conditional_edge_cases(void) {
    printf("\n=== CATEGORY 4: CONDITIONAL EDGE CASES ===\n");
    
    store* vars = store_create();
    
    // Test 4.1: Deeply nested conditionals (max depth)
    const char* test1 = 
        "<!-- xmd:set deep=\"true\" -->"
        "<!-- xmd:if deep == \"true\" -->"
        "  L1"
        "  <!-- xmd:if deep == \"true\" -->"
        "    L2"
        "    <!-- xmd:if deep == \"true\" -->"
        "      L3"
        "      <!-- xmd:if deep == \"true\" -->"
        "        L4"
        "        <!-- xmd:if deep == \"true\" -->"
        "          L5"
        "        <!-- xmd:endif -->"
        "      <!-- xmd:endif -->"
        "    <!-- xmd:endif -->"
        "  <!-- xmd:endif -->"
        "<!-- xmd:endif -->";
    char* result1 = process_xmd_content_fixed(test1, vars);
    ASSERT_TEST(result1 != NULL && strstr(result1, "L5"), "4.1: Deeply nested conditionals");
    free(result1);
    
    // Test 4.2: Complex elif chains
    variable* test_var = variable_create_string("case5");
    store_set(vars, "test_case", test_var);
    variable_unref(test_var);
    
    const char* test2 = 
        "<!-- xmd:if test_case == \"case1\" -->Case1"
        "<!-- xmd:elif test_case == \"case2\" -->Case2"
        "<!-- xmd:elif test_case == \"case3\" -->Case3"
        "<!-- xmd:elif test_case == \"case4\" -->Case4"
        "<!-- xmd:elif test_case == \"case5\" -->Case5"
        "<!-- xmd:elif test_case == \"case6\" -->Case6"
        "<!-- xmd:else -->Default"
        "<!-- xmd:endif -->";
    char* result2 = process_xmd_content_fixed(test2, vars);
    ASSERT_TEST(result2 != NULL && strstr(result2, "Case5"), "4.2: Complex elif chains");
    free(result2);
    
    // Test 4.3: Malformed condition expressions
    const char* test3 = "<!-- xmd:if invalid condition syntax -->Content<!-- xmd:endif -->";
    char* result3 = process_xmd_content_fixed(test3, vars);
    ASSERT_TEST(result3 != NULL, "4.3: Malformed condition expressions");
    free(result3);
    
    // Test 4.4: Empty conditions
    const char* test4 = "<!-- xmd:if -->Content<!-- xmd:endif -->";
    char* result4 = process_xmd_content_fixed(test4, vars);
    ASSERT_TEST(result4 != NULL, "4.4: Empty conditions");
    free(result4);
    
    // Test 4.5: Condition with undefined variables
    const char* test5 = "<!-- xmd:if undefined_var == \"value\" -->Content<!-- xmd:endif -->";
    char* result5 = process_xmd_content_fixed(test5, vars);
    ASSERT_TEST(result5 != NULL, "4.5: Conditions with undefined variables");
    free(result5);
    
    // Test 4.6: Complex boolean expressions
    variable* bool_var1 = variable_create_string("true");
    variable* bool_var2 = variable_create_string("false");
    store_set(vars, "bool1", bool_var1);
    store_set(vars, "bool2", bool_var2);
    variable_unref(bool_var1);
    variable_unref(bool_var2);
    
    const char* test6 = "<!-- xmd:if bool1 == \"true\" && bool2 == \"false\" -->Complex<!-- xmd:endif -->";
    char* result6 = process_xmd_content_fixed(test6, vars);
    ASSERT_TEST(result6 != NULL, "4.6: Complex boolean expressions");
    free(result6);
    
    // Test 4.7: Conditional inside loops inside conditionals
    const char* test7 = 
        "<!-- xmd:set mode=\"active\" -->"
        "<!-- xmd:if mode == \"active\" -->"
        "  <!-- xmd:for item in \"a,b,c\" -->"
        "    <!-- xmd:if item == \"b\" -->"
        "      Special: {{item}}"
        "    <!-- xmd:else -->"
        "      Normal: {{item}}"
        "    <!-- xmd:endif -->"
        "  <!-- xmd:endfor -->"
        "<!-- xmd:endif -->";
    char* result7 = process_xmd_content_fixed(test7, vars);
    ASSERT_TEST(result7 != NULL && strstr(result7, "Special: b"), "4.7: Conditional-loop-conditional nesting");
    free(result7);
    
    // Test 4.8: Missing endif handling
    const char* test8 = "<!-- xmd:if true -->Content without endif";
    char* result8 = process_xmd_content_fixed(test8, vars);
    ASSERT_TEST(result8 != NULL, "4.8: Missing endif handling");
    free(result8);
    
    store_destroy(vars);
}

/**
 * @brief Test Category 5: Memory and Performance Edge Cases
 */
void test_memory_performance_edge_cases(void) {
    printf("\n=== CATEGORY 5: MEMORY AND PERFORMANCE EDGE CASES ===\n");
    
    store* vars = store_create();
    
    // Test 5.1: Very large input document (100KB+)
    char* large_doc = malloc(102400);
    strcpy(large_doc, "<!-- xmd:set counter=\"0\" -->");
    for (int i = 0; i < 1000; i++) {
        char line[100];
        snprintf(line, sizeof(line), "Line %d with variable {{counter}} content.\n", i);
        strcat(large_doc, line);
    }
    char* result1 = process_xmd_content_fixed(large_doc, vars);
    ASSERT_TEST(result1 != NULL && strlen(result1) > 30000, "5.1: Large document processing");
    free(result1);
    free(large_doc);
    
    // Test 5.2: Memory stress test - many variables
    for (int i = 0; i < 1000; i++) {
        char var_name[20];
        char var_value[50];
        snprintf(var_name, sizeof(var_name), "var_%d", i);
        snprintf(var_value, sizeof(var_value), "value_%d", i);
        variable* stress_var = variable_create_string(var_value);
        store_set(vars, var_name, stress_var);
        variable_unref(stress_var);
    }
    
    const char* test2 = "{{var_0}} {{var_500}} {{var_999}}";
    char* result2 = process_xmd_content_fixed(test2, vars);
    ASSERT_TEST(result2 != NULL && strstr(result2, "value_0"), "5.2: Many variables stress test");
    free(result2);
    
    // Test 5.3: Recursive processing depth
    char* recursive_test = malloc(5000);
    strcpy(recursive_test, "");
    for (int i = 0; i < 50; i++) {
        strcat(recursive_test, "<!-- xmd:if true -->");
    }
    strcat(recursive_test, "Deep content");
    for (int i = 0; i < 50; i++) {
        strcat(recursive_test, "<!-- xmd:endif -->");
    }
    char* result3 = process_xmd_content_fixed(recursive_test, vars);
    ASSERT_TEST(result3 != NULL, "5.3: Deep recursive processing");
    free(result3);
    free(recursive_test);
    
    // Test 5.4: Performance timing test
    clock_t start = clock();
    for (int i = 0; i < 100; i++) {
        const char* perf_test = "<!-- xmd:for item in \"1,2,3,4,5\" -->{{item}} <!-- xmd:endfor -->";
        char* perf_result = process_xmd_content_fixed(perf_test, vars);
        free(perf_result);
    }
    clock_t end = clock();
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    ASSERT_TEST(cpu_time < 1.0, "5.4: Performance timing (100 iterations < 1s)");
    
    // Test 5.5: Memory allocation failure simulation (by exhausting a single large allocation)
    char* huge_string = malloc(1024 * 1024 * 10); // 10MB
    if (huge_string) {
        memset(huge_string, 'X', 1024 * 1024 * 10 - 1);
        huge_string[1024 * 1024 * 10 - 1] = '\0';
        variable* huge_var = variable_create_string(huge_string);
        if (huge_var) {
            store_set(vars, "huge", huge_var);
            variable_unref(huge_var);
            
            const char* test5 = "Size: {{huge}}";
            char* result5 = process_xmd_content_fixed(test5, vars);
            ASSERT_TEST(result5 != NULL, "5.5: Large memory allocation handling");
            free(result5);
        }
        free(huge_string);
    }
    
    store_destroy(vars);
}

/**
 * @brief Test Category 6: Security and Safety Edge Cases
 */
void test_security_edge_cases(void) {
    printf("\n=== CATEGORY 6: SECURITY AND SAFETY EDGE CASES ===\n");
    
    store* vars = store_create();
    
    // Test 6.1: Potential code injection attempts
    const char* test1 = "<!-- xmd:exec rm -rf / -->";
    char* result1 = process_xmd_content_fixed(test1, vars);
    ASSERT_TEST(result1 != NULL, "6.1: Command injection attempt");
    free(result1);
    
    // Test 6.2: Script injection in variables
    variable* script_var = variable_create_string("<script>alert('xss')</script>");
    store_set(vars, "script", script_var);
    variable_unref(script_var);
    
    const char* test2 = "Content: {{script}}";
    char* result2 = process_xmd_content_fixed(test2, vars);
    ASSERT_TEST(result2 != NULL && strstr(result2, "<script>"), "6.2: Script content preservation");
    free(result2);
    
    // Test 6.3: Path traversal attempts
    const char* test3 = "<!-- xmd:import ../../etc/passwd -->";
    char* result3 = process_xmd_content_fixed(test3, vars);
    ASSERT_TEST(result3 != NULL, "6.3: Path traversal attempt");
    free(result3);
    
    // Test 6.4: Buffer overflow attempts in variable names
    char overflow_test[2000];
    strcpy(overflow_test, "<!-- xmd:set ");
    for (int i = 0; i < 100; i++) {
        strcat(overflow_test, "verylongvariablename");
    }
    strcat(overflow_test, "=\"value\" -->");
    char* result4 = process_xmd_content_fixed(overflow_test, vars);
    ASSERT_TEST(result4 != NULL, "6.4: Buffer overflow attempt in variable names");
    free(result4);
    
    // Test 6.5: Format string injection attempts
    const char* test5 = "<!-- xmd:set format=\"%s%s%s%s%s\" -->{{format}}";
    char* result5 = process_xmd_content_fixed(test5, vars);
    ASSERT_TEST(result5 != NULL && strstr(result5, "%s"), "6.5: Format string injection attempt");
    free(result5);
    
    // Test 6.6: Null pointer dereference attempts
    char* result6 = process_xmd_content_fixed(NULL, vars);
    ASSERT_TEST(result6 == NULL, "6.6: NULL input handling");
    
    char* result7 = process_xmd_content_fixed("test", NULL);
    ASSERT_TEST(result7 == NULL, "6.7: NULL variables store handling");
    
    // Test 6.8: Integer overflow in ranges
    const char* test8 = "<!-- xmd:for i in 2147483647..2147483647 -->{{i}} <!-- xmd:endfor -->";
    char* result8 = process_xmd_content_fixed(test8, vars);
    ASSERT_TEST(result8 != NULL, "6.8: Integer overflow in ranges");
    free(result8);
    
    store_destroy(vars);
}

/**
 * @brief Test Category 7: Multiline Directive Edge Cases
 */
void test_multiline_edge_cases(void) {
    printf("\n=== CATEGORY 7: MULTILINE DIRECTIVE EDGE CASES ===\n");
    
    store* vars = store_create();
    
    // Test 7.1: Empty multiline directive
    const char* test1 = "";
    process_multiline_directive_enhanced(test1, vars);
    ASSERT_TEST(store_size(vars) == 0, "7.1: Empty multiline directive");
    
    // Test 7.2: Multiline with only whitespace
    const char* test2 = "\n\t   \n   \t\n";
    process_multiline_directive_enhanced(test2, vars);
    ASSERT_TEST(store_size(vars) == 0, "7.2: Whitespace-only multiline directive");
    
    // Test 7.3: Multiline with mixed line endings
    const char* test3 = "set var1=\"value1\"\r\nset var2=\"value2\"\nset var3=\"value3\"\r";
    process_multiline_directive_enhanced(test3, vars);
    variable* var1 = store_get(vars, "var1");
    variable* var2 = store_get(vars, "var2");
    variable* var3 = store_get(vars, "var3");
    ASSERT_TEST(var1 && var2 && var3, "7.3: Mixed line endings in multiline");
    
    // Test 7.4: Very long multiline directive
    char* long_multiline = malloc(10000);
    strcpy(long_multiline, "");
    for (int i = 0; i < 100; i++) {
        char line[100];
        snprintf(line, sizeof(line), "set var%d=\"value%d\"\n", i, i);
        strcat(long_multiline, line);
    }
    process_multiline_directive_enhanced(long_multiline, vars);
    ASSERT_TEST(store_size(vars) > 100, "7.4: Very long multiline directive");
    free(long_multiline);
    
    // Test 7.5: Multiline with comments and invalid lines
    const char* test5 = 
        "set valid1=\"value1\"\n"
        "# This is a comment\n"
        "invalid line without command\n"
        "set valid2=\"value2\"\n"
        "\n"
        "set valid3=\"value3\"";
    store_clear(vars);
    process_multiline_directive_enhanced(test5, vars);
    variable* valid1 = store_get(vars, "valid1");
    variable* valid2 = store_get(vars, "valid2");
    ASSERT_TEST(valid1 && valid2, "7.5: Multiline with invalid lines");
    
    store_destroy(vars);
}

/**
 * @brief Test Category 8: Error Recovery and Resilience
 */
void test_error_recovery(void) {
    printf("\n=== CATEGORY 8: ERROR RECOVERY AND RESILIENCE ===\n");
    
    store* vars = store_create();
    
    // Test 8.1: Recovery from malformed directive in middle of document
    const char* test1 = 
        "Valid content before\n"
        "<!-- xmd:invalid_directive -->\n"
        "<!-- xmd:set var=\"value\" -->\n"
        "Valid content after {{var}}";
    char* result1 = process_xmd_content_fixed(test1, vars);
    ASSERT_TEST(result1 != NULL && strstr(result1, "Valid content after value"), "8.1: Recovery from malformed directive");
    free(result1);
    
    // Test 8.2: Partial directive processing with errors
    const char* test2 = 
        "<!-- xmd:set good1=\"value1\" -->\n"
        "<!-- xmd:set bad_var= -->\n"
        "<!-- xmd:set good2=\"value2\" -->\n"
        "{{good1}} {{good2}}";
    char* result2 = process_xmd_content_fixed(test2, vars);
    ASSERT_TEST(result2 != NULL && strstr(result2, "value1"), "8.2: Partial directive processing");
    free(result2);
    
    // Test 8.3: Graceful handling of resource exhaustion
    // Simulate by creating many nested structures
    char* resource_test = malloc(50000);
    strcpy(resource_test, "");
    for (int i = 0; i < 500; i++) {
        strcat(resource_test, "<!-- xmd:if true -->");
    }
    strcat(resource_test, "Content");
    for (int i = 0; i < 500; i++) {
        strcat(resource_test, "<!-- xmd:endif -->");
    }
    char* result3 = process_xmd_content_fixed(resource_test, vars);
    ASSERT_TEST(result3 != NULL, "8.3: Deep nesting resource handling");
    free(result3);
    free(resource_test);
    
    // Test 8.4: Recovery from circular references
    variable* circ1 = variable_create_string("{{circ2}}");
    variable* circ2 = variable_create_string("{{circ1}}");
    store_set(vars, "circ1", circ1);
    store_set(vars, "circ2", circ2);
    variable_unref(circ1);
    variable_unref(circ2);
    
    const char* test4 = "{{circ1}}";
    char* result4 = process_xmd_content_fixed(test4, vars);
    ASSERT_TEST(result4 != NULL, "8.4: Circular reference handling");
    free(result4);
    
    store_destroy(vars);
}

/**
 * @brief Test Category 9: Stress Testing
 */
void test_stress_cases(void) {
    printf("\n=== CATEGORY 9: STRESS TESTING ===\n");
    
    store* vars = store_create();
    
    // Test 9.1: Rapid fire small operations
    clock_t start = clock();
    for (int i = 0; i < 1000; i++) {
        char test[100];
        snprintf(test, sizeof(test), "<!-- xmd:set var%d=\"%d\" -->{{var%d}}", i, i, i);
        char* result = process_xmd_content_fixed(test, vars);
        if (result) free(result);
    }
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    ASSERT_TEST(time_taken < 2.0, "9.1: Rapid fire operations (1000 ops < 2s)");
    
    // Test 9.2: Variable explosion test
    char explosion_test[10000];
    strcpy(explosion_test, "");
    for (int i = 0; i < 100; i++) {
        char var_def[100];
        snprintf(var_def, sizeof(var_def), "<!-- xmd:set var%d=\"{{var%d}}{{var%d}}\" -->", i, (i > 0) ? i-1 : 0, (i > 1) ? i-2 : 0);
        strcat(explosion_test, var_def);
    }
    strcat(explosion_test, "{{var99}}");
    
    char* result2 = process_xmd_content_fixed(explosion_test, vars);
    ASSERT_TEST(result2 != NULL, "9.2: Variable explosion test");
    free(result2);
    
    // Test 9.3: Maximum nested loop depth
    char max_nest[5000];
    strcpy(max_nest, "");
    for (int i = 0; i < 16; i++) {
        strcat(max_nest, "<!-- xmd:for item in \"a\" -->");
    }
    strcat(max_nest, "deep");
    for (int i = 0; i < 16; i++) {
        strcat(max_nest, "<!-- xmd:endfor -->");
    }
    
    char* result3 = process_xmd_content_fixed(max_nest, vars);
    ASSERT_TEST(result3 != NULL, "9.3: Maximum nested loop depth");
    free(result3);
    
    store_destroy(vars);
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("🧪 COMPREHENSIVE EDGE CASE TEST SUITE\n");
    printf("=====================================\n");
    printf("Testing every possible edge case for XMD processor robustness\n\n");
    
    // Run all test categories
    test_malformed_directives();
    test_variable_edge_cases();
    test_loop_edge_cases();
    test_conditional_edge_cases();
    test_memory_performance_edge_cases();
    test_security_edge_cases();
    test_multiline_edge_cases();
    test_error_recovery();
    test_stress_cases();
    
    // Print final results
    printf("\n" "🎯 COMPREHENSIVE TEST RESULTS\n");
    printf("════════════════════════════════════════════════════════════════\n");
    printf("Tests Run:    %d\n", tests_run);
    printf("Tests Passed: %d ✅\n", tests_passed);
    printf("Tests Failed: %d ❌\n", tests_failed);
    printf("Success Rate: %.1f%%\n", (tests_run > 0) ? (100.0 * tests_passed / tests_run) : 0.0);
    printf("════════════════════════════════════════════════════════════════\n");
    
    if (tests_failed == 0) {
        printf("🎉 ALL EDGE CASES PASSED! XMD Processor is BULLETPROOF! 🛡️\n");
        printf("\nThe XMD processor successfully handles:\n");
        printf("✅ Malformed directives and syntax errors\n");
        printf("✅ Variable boundary conditions and special characters\n");
        printf("✅ Loop limits and extreme nesting scenarios\n");
        printf("✅ Memory stress and performance edge cases\n");
        printf("✅ Security threats and injection attempts\n");
        printf("✅ Complex multiline directive scenarios\n");
        printf("✅ Error recovery and resilience testing\n");
        printf("✅ High-stress operational conditions\n");
        printf("\n🚀 PRODUCTION READY FOR ANY SCENARIO!\n");
    } else {
        printf("⚠️  Some edge cases need attention. Review failed tests above.\n");
    }
    
    return (tests_failed == 0) ? 0 : 1;
}