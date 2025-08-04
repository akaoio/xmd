/**
 * @file unity.h
 * @brief Minimal Unity-style testing framework for XMD
 * @author XMD Test Framework
 * 
 * ENFORCING PRINCIPLE: test driven -> test first, implement later
 */

#ifndef UNITY_H
#define UNITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test statistics
extern int unity_tests_run;
extern int unity_tests_passed;
extern int unity_tests_failed;

// Color codes for output
#define UNITY_COLOR_GREEN   "\033[32m"
#define UNITY_COLOR_RED     "\033[31m"
#define UNITY_COLOR_YELLOW  "\033[33m"
#define UNITY_COLOR_RESET   "\033[0m"

// Test macros
#define TEST_ASSERT(condition) \
    do { \
        unity_tests_run++; \
        if (condition) { \
            unity_tests_passed++; \
            printf(UNITY_COLOR_GREEN "✓" UNITY_COLOR_RESET " %s:%d: PASS\n", __FILE__, __LINE__); \
        } else { \
            unity_tests_failed++; \
            printf(UNITY_COLOR_RED "✗" UNITY_COLOR_RESET " %s:%d: FAIL - %s\n", __FILE__, __LINE__, #condition); \
        } \
    } while(0)

#define TEST_ASSERT_EQUAL(expected, actual) \
    do { \
        unity_tests_run++; \
        if ((expected) == (actual)) { \
            unity_tests_passed++; \
            printf(UNITY_COLOR_GREEN "✓" UNITY_COLOR_RESET " %s:%d: PASS\n", __FILE__, __LINE__); \
        } else { \
            unity_tests_failed++; \
            printf(UNITY_COLOR_RED "✗" UNITY_COLOR_RESET " %s:%d: FAIL - Expected %d, got %d\n", __FILE__, __LINE__, (int)(expected), (int)(actual)); \
        } \
    } while(0)

#define TEST_ASSERT_STRING_EQUAL(expected, actual) \
    do { \
        unity_tests_run++; \
        if (strcmp((expected), (actual)) == 0) { \
            unity_tests_passed++; \
            printf(UNITY_COLOR_GREEN "✓" UNITY_COLOR_RESET " %s:%d: PASS\n", __FILE__, __LINE__); \
        } else { \
            unity_tests_failed++; \
            printf(UNITY_COLOR_RED "✗" UNITY_COLOR_RESET " %s:%d: FAIL - Expected '%s', got '%s'\n", __FILE__, __LINE__, (expected), (actual)); \
        } \
    } while(0)

#define TEST_ASSERT_NULL(ptr) \
    do { \
        unity_tests_run++; \
        if ((ptr) == NULL) { \
            unity_tests_passed++; \
            printf(UNITY_COLOR_GREEN "✓" UNITY_COLOR_RESET " %s:%d: PASS\n", __FILE__, __LINE__); \
        } else { \
            unity_tests_failed++; \
            printf(UNITY_COLOR_RED "✗" UNITY_COLOR_RESET " %s:%d: FAIL - Expected NULL, got %p\n", __FILE__, __LINE__, (void*)(ptr)); \
        } \
    } while(0)

#define TEST_ASSERT_NOT_NULL(ptr) \
    do { \
        unity_tests_run++; \
        if ((ptr) != NULL) { \
            unity_tests_passed++; \
            printf(UNITY_COLOR_GREEN "✓" UNITY_COLOR_RESET " %s:%d: PASS\n", __FILE__, __LINE__); \
        } else { \
            unity_tests_failed++; \
            printf(UNITY_COLOR_RED "✗" UNITY_COLOR_RESET " %s:%d: FAIL - Expected non-NULL, got NULL\n", __FILE__, __LINE__); \
        } \
    } while(0)

// Test setup/teardown
#define RUN_TEST(test_func) \
    do { \
        printf(UNITY_COLOR_YELLOW "Running " #test_func "..." UNITY_COLOR_RESET "\n"); \
        test_func(); \
    } while(0)

// Initialize Unity
void Unity_Begin(const char* test_suite_name);

// Finalize Unity and return exit code
int Unity_End(void);

#endif // UNITY_H