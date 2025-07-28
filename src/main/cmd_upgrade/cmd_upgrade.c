/**
 * @file cmd_upgrade.c
 * @brief XMD upgrade command implementation
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "../../../include/main_internal.h"

// Function prototypes
extern char* get_version(void);
static int check_for_updates(const char* current_version, char* latest_version, size_t version_size);
static int download_release(const char* version, const char* temp_path);
static int install_upgrade(const char* temp_path, const char* install_path);
static int compare_versions(const char* v1, const char* v2);

/**
 * @brief Execute upgrade command
 * @param argc Argument count
 * @param argv Argument vector
 * @return 0 on success, non-zero on error
 */
int cmd_upgrade(int argc, char* argv[]) {
    (void)argc;  // Unused
    (void)argv;  // Unused
    
    printf("XMD Upgrade Tool\n");
    printf("================\n\n");
    
    // Get current version
    char* current_version = get_version();
    printf("Current version: %s\n", current_version);
    
    // Check for updates
    char latest_version[128] = {0};
    printf("Checking for updates...\n");
    
    if (check_for_updates(current_version, latest_version, sizeof(latest_version)) != 0) {
        fprintf(stderr, "Error: Failed to check for updates\n");
        return 1;
    }
    
    // Compare versions
    int cmp = compare_versions(current_version, latest_version);
    if (cmp >= 0) {
        printf("✓ You are already running the latest version (%s)\n", latest_version);
        return 0;
    }
    
    printf("New version available: %s\n", latest_version);
    printf("Downloading update...\n");
    
    // Create temporary file for download
    char temp_path[256];
    snprintf(temp_path, sizeof(temp_path), "/tmp/xmd-upgrade-%s", latest_version);
    
    // Download the new version
    if (download_release(latest_version, temp_path) != 0) {
        fprintf(stderr, "Error: Failed to download update\n");
        return 1;
    }
    
    // Get the path of the current executable
    char exe_path[256];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len == -1) {
        // Fallback for non-Linux systems
        strncpy(exe_path, argv[0], sizeof(exe_path) - 1);
        exe_path[sizeof(exe_path) - 1] = '\0';
    } else {
        exe_path[len] = '\0';
    }
    
    printf("Installing update...\n");
    
    // Install the upgrade
    if (install_upgrade(temp_path, exe_path) != 0) {
        fprintf(stderr, "Error: Failed to install update\n");
        unlink(temp_path);  // Clean up temp file
        return 1;
    }
    
    // Clean up temp file
    unlink(temp_path);
    
    printf("✓ Successfully upgraded to version %s\n", latest_version);
    printf("Please run 'xmd version' to verify the upgrade.\n");
    
    return 0;
}

/**
 * @brief Check for updates using GitHub API
 * @param current_version Current version string
 * @param latest_version Buffer to store latest version
 * @param version_size Size of version buffer
 * @return 0 on success, non-zero on error
 */
static int check_for_updates(const char* current_version, char* latest_version, size_t version_size) {
    (void)current_version;  // Unused for now
    
    // Use curl to query GitHub API
    FILE* fp = popen("curl -s https://api.github.com/repos/akaoio/xmd/releases/latest | grep '\"tag_name\"' | cut -d'\"' -f4", "r");
    if (!fp) {
        return -1;
    }
    
    // Read the version tag
    if (fgets(latest_version, version_size, fp) == NULL) {
        pclose(fp);
        return -1;
    }
    
    // Remove newline
    size_t len = strlen(latest_version);
    if (len > 0 && latest_version[len - 1] == '\n') {
        latest_version[len - 1] = '\0';
    }
    
    // Remove 'v' prefix if present
    if (latest_version[0] == 'v') {
        memmove(latest_version, latest_version + 1, strlen(latest_version));
    }
    
    pclose(fp);
    return 0;
}

/**
 * @brief Download release binary from GitHub
 * @param version Version to download
 * @param temp_path Path to save downloaded file
 * @return 0 on success, non-zero on error
 */
static int download_release(const char* version, const char* temp_path) {
    // Determine platform
    char platform[32];
#ifdef __linux__
    strcpy(platform, "linux");
#elif __APPLE__
    strcpy(platform, "darwin");
#elif _WIN32
    strcpy(platform, "windows");
#else
    strcpy(platform, "unknown");
#endif
    
    // Determine architecture
    char arch[32];
#ifdef __x86_64__
    strcpy(arch, "amd64");
#elif __aarch64__
    strcpy(arch, "arm64");
#elif __arm__
    strcpy(arch, "arm");
#else
    strcpy(arch, "unknown");
#endif
    
    // Build download URL
    char url[512];
    snprintf(url, sizeof(url), 
             "https://github.com/akaoio/xmd/releases/download/v%s/xmd-%s-%s",
             version, platform, arch);
    
    // Download using curl
    char command[1024];
    snprintf(command, sizeof(command), "curl -L -o %s %s", temp_path, url);
    
    int result = system(command);
    if (result != 0) {
        return -1;
    }
    
    // Make the downloaded file executable
    chmod(temp_path, 0755);
    
    return 0;
}

/**
 * @brief Install the upgrade by replacing the current binary
 * @param temp_path Path to new binary
 * @param install_path Path to install location
 * @return 0 on success, non-zero on error
 */
static int install_upgrade(const char* temp_path, const char* install_path) {
    // Create backup of current binary
    char backup_path[512];
    snprintf(backup_path, sizeof(backup_path), "%s.backup", install_path);
    
    // Remove old backup if it exists
    unlink(backup_path);
    
    // Rename current binary to backup
    if (rename(install_path, backup_path) != 0) {
        // If rename fails, try to use sudo
        char command[1024];
        snprintf(command, sizeof(command), "sudo mv %s %s", install_path, backup_path);
        if (system(command) != 0) {
            fprintf(stderr, "Error: Failed to backup current binary. Permission denied?\n");
            fprintf(stderr, "You may need to run: sudo xmd upgrade\n");
            return -1;
        }
    }
    
    // Move new binary to install location
    if (rename(temp_path, install_path) != 0) {
        // If rename fails, try to use sudo
        char command[1024];
        snprintf(command, sizeof(command), "sudo mv %s %s", temp_path, install_path);
        if (system(command) != 0) {
            // Restore backup
            rename(backup_path, install_path);
            return -1;
        }
    }
    
    return 0;
}

/**
 * @brief Compare two version strings
 * @param v1 First version
 * @param v2 Second version
 * @return -1 if v1 < v2, 0 if equal, 1 if v1 > v2
 */
static int compare_versions(const char* v1, const char* v2) {
    // Simple version comparison
    // Remove -dev or other suffixes for comparison
    char clean_v1[128], clean_v2[128];
    strncpy(clean_v1, v1, sizeof(clean_v1) - 1);
    strncpy(clean_v2, v2, sizeof(clean_v2) - 1);
    
    // Find and remove suffixes
    char* suffix = strchr(clean_v1, '-');
    if (suffix) *suffix = '\0';
    suffix = strchr(clean_v2, '-');
    if (suffix) *suffix = '\0';
    
    // Parse versions
    int major1 = 0, minor1 = 0, patch1 = 0;
    int major2 = 0, minor2 = 0, patch2 = 0;
    
    sscanf(clean_v1, "%d.%d.%d", &major1, &minor1, &patch1);
    sscanf(clean_v2, "%d.%d.%d", &major2, &minor2, &patch2);
    
    if (major1 != major2) return major1 - major2;
    if (minor1 != minor2) return minor1 - minor2;
    return patch1 - patch2;
}