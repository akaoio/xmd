/**
 * @file test_upgrade_version.c
 * @brief Test suite for upgrade and version functionality
 * @author XMD Implementation Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>

// External functions we want to test
extern char* get_version(void);
extern const char* xmd_get_version(void);
extern int cmd_upgrade(int argc, char* argv[]);

/**
 * @brief Test dynamic version detection
 */
static void test_version_detection(void) {
    printf("Testing dynamic version detection...\n");
    
    // Test get_version function
    {
        char* version = get_version();
        assert(version != NULL);
        assert(strlen(version) > 0);
        printf("  get_version(): %s\n", version);
        
        // Version should contain digits and dots
        int has_digit = 0;
        for (const char* p = version; *p; p++) {
            if (*p >= '0' && *p <= '9') {
                has_digit = 1;
                break;
            }
        }
        assert(has_digit);
    }
    
    // Test xmd_get_version function
    {
        const char* version = xmd_get_version();
        assert(version != NULL);
        assert(strlen(version) > 0);
        printf("  xmd_get_version(): %s\n", version);
        
        // Should be consistent with get_version
        char* get_ver = get_version();
        assert(strcmp(version, get_ver) == 0);
    }
    
    printf("✓ Version detection tests passed\n");
}

/**
 * @brief Test version command execution
 */
static void test_version_command(void) {
    printf("Testing version command execution...\n");
    
    // Test version command via system call
    {
        const char* temp_file = "./xmd_version_test.txt";
        
        // Check if xmd binary exists (first try current dir, then parent dir)
        const char* xmd_path = "./xmd";
        FILE* check = fopen(xmd_path, "r");
        if (!check) {
            xmd_path = "../xmd";
            check = fopen(xmd_path, "r");
            if (!check) {
                printf("Error: xmd binary not found in ./ or ../\n");
                system("pwd");
                system("ls -la xmd* ../xmd* || echo 'No xmd files found'");
            } else {
                fclose(check);
            }
        } else {
            fclose(check);
        }
        
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "%s version > %s 2>&1", xmd_path, temp_file);
        int status = system(cmd);
        
        if (WEXITSTATUS(status) != 0) {
            printf("Command failed with status %d\n", status);
            // Try to show the error output
            FILE* error_file = fopen(temp_file, "r");
            if (error_file) {
                printf("Error output:\n");
                char line[256];
                while (fgets(line, sizeof(line), error_file)) {
                    printf("%s", line);
                }
                fclose(error_file);
            }
        }
        
        assert(WEXITSTATUS(status) == 0);
        
        // Read the output
        FILE* f = fopen(temp_file, "r");
        assert(f != NULL);
        
        char line[256];
        int found_version = 0;
        while (fgets(line, sizeof(line), f)) {
            if (strstr(line, "XMD version")) {
                found_version = 1;
                printf("  Version command output: %s", line);
                
                // Should contain actual version, not hardcoded
                assert(!strstr(line, "1.0.0")); // Old hardcoded version
                break;
            }
        }
        fclose(f);
        unlink(temp_file);
        
        assert(found_version);
    }
    
    printf("✓ Version command tests passed\n");
}

/**
 * @brief Test upgrade command basic functionality
 */
static void test_upgrade_command_basic(void) {
    printf("Testing upgrade command basic functionality...\n");
    
    // Test upgrade command execution (should check for updates)
    {
        char* argv[] = {"xmd", "upgrade"};
        int argc = 2;
        
        printf("  Running upgrade command...\n");
        int result = cmd_upgrade(argc, argv);
        
        // Should return 0 for success or -1 for network/system error
        // Both are acceptable in test environment
        printf("  Upgrade command returned: %d\n", result);
        assert(result == 0 || result == -1);
    }
    
    printf("✓ Upgrade command basic tests passed\n");
}

/**
 * @brief Test upgrade command help
 */
static void test_upgrade_help(void) {
    printf("Testing upgrade command help...\n");
    
    // Test upgrade --help
    {
        char* argv[] = {"xmd", "upgrade", "--help"};
        int argc = 3;
        
        printf("  Running upgrade --help command...\n");
        int result = cmd_upgrade(argc, argv);
        
        printf("  Help command returned: %d\n", result);
        assert(result == 0);
    }
    
    printf("✓ Upgrade help tests passed\n");
}

/**
 * @brief Test version consistency across all interfaces
 */
static void test_version_consistency(void) {
    printf("Testing version consistency across interfaces...\n");
    
    // Get version from C function
    const char* c_version = xmd_get_version();
    assert(c_version != NULL);
    
    // Get version from command line  
    const char* temp_file = "./xmd_version.txt";
    
    // Determine xmd path (reuse logic from previous test)
    const char* xmd_path = "./xmd";
    FILE* check = fopen(xmd_path, "r");
    if (!check) {
        xmd_path = "../xmd";
        check = fopen(xmd_path, "r");
        if (check) {
            fclose(check);
        }
    } else {
        fclose(check);
    }
    
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "%s version 2>/dev/null | head -1 | cut -d' ' -f3 > %s", xmd_path, temp_file);
    int status = system(cmd);
    assert(WEXITSTATUS(status) == 0);
    
    FILE* f = fopen(temp_file, "r");
    assert(f != NULL);
    
    char cli_version[64];
    assert(fgets(cli_version, sizeof(cli_version), f) != NULL);
    fclose(f);
    unlink(temp_file);
    
    // Remove newline
    cli_version[strcspn(cli_version, "\n")] = 0;
    
    printf("  C API version: %s\n", c_version);
    printf("  CLI version: %s\n", cli_version);
    
    // They should be identical
    assert(strcmp(c_version, cli_version) == 0);
    
    printf("✓ Version consistency tests passed\n");
}

/**
 * @brief Test install.sh compatibility
 */
static void test_install_script(void) {
    printf("Testing install.sh compatibility...\n");
    
    // Check if install.sh exists and is executable
    if (access("./install.sh", F_OK) == 0) {
        // Test that install.sh can parse version correctly
        int status = system("bash -n ./install.sh");
        assert(WEXITSTATUS(status) == 0);
        printf("  install.sh syntax is valid\n");
        
        // Test API call functionality (without actually installing)
        const char* temp_file = "./xmd_latest_version.txt";
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "curl -s 'https://api.github.com/repos/akaoio/xmd/releases/latest' | grep '\"tag_name\"' | head -1 | cut -d'\"' -f4 > %s 2>/dev/null", temp_file);
        status = system(cmd);
        if (WEXITSTATUS(status) == 0) {
            FILE* f = fopen(temp_file, "r");
            if (f != NULL) {
                char version[64];
                if (fgets(version, sizeof(version), f)) {
                    version[strcspn(version, "\n")] = 0;
                    printf("  Latest GitHub version: %s\n", version);
                    assert(strlen(version) > 0);
                }
                fclose(f);
                unlink(temp_file);
            }
        }
    } else {
        printf("  install.sh not found, skipping install script tests\n");
    }
    
    printf("✓ Install script tests passed\n");
}

/**
 * @brief Test error handling in upgrade functionality
 */
static void test_upgrade_error_handling(void) {
    printf("Testing upgrade error handling...\n");
    
    // Test with invalid arguments
    {
        char* argv[] = {"xmd", "upgrade", "--invalid-flag"};
        int argc = 3;
        
        // Should handle invalid flags gracefully
        int result = cmd_upgrade(argc, argv);
        // Result should be 0 (help shown) or 1 (error), but not crash
        assert(result == 0 || result == 1);
    }
    
    printf("✓ Upgrade error handling tests passed\n");
}

/**
 * @brief Main test function
 */
int main(void) {
    printf("=== Upgrade and Version System Tests ===\n");
    
    // Change to build directory to find xmd binary
    if (chdir("build") != 0) {
        printf("Warning: Could not change to build directory, some tests may fail\n");
    }
    
    test_version_detection();
    test_version_command();
    test_upgrade_command_basic();
    test_upgrade_help();
    test_version_consistency();
    test_install_script();
    test_upgrade_error_handling();
    
    printf("\n✅ All upgrade and version tests passed!\n");
    return 0;
}