/**
 * @file unity.c
 * @brief Unity testing framework implementation
 * 
 * ENFORCING PRINCIPLE: One function per file
 * This file contains ONLY Unity framework globals and initialization
 */

#include "unity.h"

// Global test statistics
int unity_tests_run = 0;
int unity_tests_passed = 0;
int unity_tests_failed = 0;

/**
 * @brief Initialize Unity test framework
 * @param test_suite_name Name of the test suite
 */
void Unity_Begin(const char* test_suite_name) {
    unity_tests_run = 0;
    unity_tests_passed = 0;
    unity_tests_failed = 0;
    
    printf("\n" UNITY_COLOR_YELLOW "=== XMD TEST SUITE: %s ===" UNITY_COLOR_RESET "\n", 
           test_suite_name ? test_suite_name : "Unknown");
}

/**
 * @brief Finalize Unity and print results
 * @return 0 if all tests passed, 1 if any failed
 */
int Unity_End(void) {
    printf("\n" UNITY_COLOR_YELLOW "=== TEST RESULTS ===" UNITY_COLOR_RESET "\n");
    printf("Tests Run: %d\n", unity_tests_run);
    printf(UNITY_COLOR_GREEN "Passed: %d" UNITY_COLOR_RESET "\n", unity_tests_passed);
    
    if (unity_tests_failed > 0) {
        printf(UNITY_COLOR_RED "Failed: %d" UNITY_COLOR_RESET "\n", unity_tests_failed);
        printf(UNITY_COLOR_RED "❌ TEST SUITE FAILED" UNITY_COLOR_RESET "\n");
        return 1;
    } else {
        printf(UNITY_COLOR_GREEN "✅ ALL TESTS PASSED" UNITY_COLOR_RESET "\n");
        return 0;
    }
}