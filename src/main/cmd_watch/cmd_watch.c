/**
 * @file cmd_watch.c
 * @brief XMD watch command implementation
 * @author XMD Team
 */

#include "../../../include/main_internal.h"
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>

// Handle systems that don't define DT_REG or PATH_MAX
#ifndef DT_REG
#define DT_REG 8
#endif

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

// Make usleep and strdup available
#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// Ensure strdup is available
#ifndef strdup
char* strdup(const char* s);
#endif

static volatile bool watch_running = true;

/**
 * @brief Signal handler for graceful shutdown
 */
static void signal_handler(int sig) {
    (void)sig; // Suppress unused parameter warning
    watch_running = false;
    printf("\nStopping watch...\n");
}

/**
 * @brief Get file modification time
 */
static time_t get_file_mtime(const char* filepath) {
    struct stat st;
    if (stat(filepath, &st) == 0) {
        return st.st_mtime;
    }
    return 0;
}

/**
 * @brief Check if file is a markdown file
 */
static bool is_markdown_file(const char* filename) {
    if (!filename) return false;
    
    size_t len = strlen(filename);
    if (len < 3) return false;
    
    const char* ext = filename + len - 3;
    return (strcmp(ext, ".md") == 0);
}

/**
 * @brief Create directory recursively
 */
static int create_directory_recursive(const char* path) {
    char temp_path[PATH_MAX];
    char* p = NULL;
    size_t len;
    
    snprintf(temp_path, sizeof(temp_path), "%s", path);
    len = strlen(temp_path);
    
    if (temp_path[len - 1] == '/') {
        temp_path[len - 1] = 0;
    }
    
    for (p = temp_path + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            if (mkdir(temp_path, 0755) != 0 && errno != EEXIST) {
                return -1;
            }
            *p = '/';
        }
    }
    
    if (mkdir(temp_path, 0755) != 0 && errno != EEXIST) {
        return -1;
    }
    
    return 0;
}

/**
 * @brief Generate output file path from input file path
 */
static char* generate_output_path(const char* input_path, const char* input_dir, 
                                 const char* output_dir, const char* format) {
    if (!output_dir) {
        return NULL; // Output to stdout
    }
    
    // Calculate relative path from input_dir
    const char* relative_path = input_path;
    size_t input_dir_len = strlen(input_dir);
    
    // Skip input directory prefix
    if (strncmp(input_path, input_dir, input_dir_len) == 0) {
        relative_path = input_path + input_dir_len;
        while (*relative_path == '/') relative_path++; // Skip leading slashes
    }
    
    // Determine file extension based on format
    const char* ext = ".html";
    if (strcmp(format, "markdown") == 0) {
        ext = ".md";
    } else if (strcmp(format, "json") == 0) {
        ext = ".json";
    }
    
    // Build output path: output_dir + relative_path_without_extension + new_extension
    size_t output_path_len = strlen(output_dir) + strlen(relative_path) + strlen(ext) + 2;
    char* output_path = malloc(output_path_len);
    if (!output_path) return NULL;
    
    // Find the last dot to remove .md extension
    char* relative_copy = strdup(relative_path);
    char* last_dot = strrchr(relative_copy, '.');
    if (last_dot && strcmp(last_dot, ".md") == 0) {
        *last_dot = '\0'; // Remove .md extension
    }
    
    snprintf(output_path, output_path_len, "%s/%s%s", output_dir, relative_copy, ext);
    free(relative_copy);
    
    return output_path;
}

/**
 * @brief Process a single file with output directory support
 */
static int process_file_with_output(const char* filepath, const char* input_dir,
                                  const char* output_dir, const char* format, bool verbose) {
    if (verbose) {
        printf("Processing: %s\n", filepath);
    }
    
    char* output_path = generate_output_path(filepath, input_dir, output_dir, format);
    
    if (output_path) {
        // Create output directory if needed
        char* output_dir_path = strdup(output_path);
        char* last_slash = strrchr(output_dir_path, '/');
        if (last_slash) {
            *last_slash = '\0';
            if (create_directory_recursive(output_dir_path) != 0) {
                printf("❌ Failed to create output directory: %s\n", output_dir_path);
                free(output_dir_path);
                free(output_path);
                return 1;
            }
        }
        free(output_dir_path);
        
        // Create process command arguments with output
        char* process_argv[] = { "xmd", "process", (char*)filepath, "-o", output_path, "--format", (char*)format, NULL };
        
        int result = cmd_process(7, process_argv);
        
        if (result == 0) {
            if (verbose) {
                printf("✅ Successfully processed: %s → %s\n", filepath, output_path);
            } else {
                printf("✅ %s → %s\n", filepath, output_path);
            }
        } else {
            printf("❌ Error processing: %s\n", filepath);
        }
        
        free(output_path);
        return result;
    } else {
        // No output directory - process to stdout
        char* process_argv[] = { "xmd", "process", (char*)filepath, "--format", (char*)format, NULL };
        
        int result = cmd_process(5, process_argv);
        
        if (result == 0 && verbose) {
            printf("✅ Successfully processed: %s\n", filepath);
        } else if (result != 0) {
            printf("❌ Error processing: %s\n", filepath);
        }
        
        return result;
    }
}

/**
 * @brief Check if path is a regular file
 */
static bool is_regular_file(const char* path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return S_ISREG(st.st_mode);
    }
    return false;
}

/**
 * @brief Recursively count markdown files in directory
 */
static int count_markdown_files_recursive(const char* dir_path) {
    DIR* dir = opendir(dir_path);
    if (!dir) {
        return 0;
    }
    
    int count = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // Create full path
        size_t path_len = strlen(dir_path) + strlen(entry->d_name) + 2;
        char* full_path = malloc(path_len);
        snprintf(full_path, path_len, "%s/%s", dir_path, entry->d_name);
        
        struct stat st;
        if (stat(full_path, &st) == 0) {
            if (S_ISREG(st.st_mode) && is_markdown_file(entry->d_name)) {
                count++;
            } else if (S_ISDIR(st.st_mode)) {
                // Recursively count files in subdirectory
                count += count_markdown_files_recursive(full_path);
            }
        }
        free(full_path);
    }
    
    closedir(dir);
    return count;
}

/**
 * @brief Recursively collect markdown files from directory
 */
static void collect_markdown_files_recursive(const char* dir_path, char** files, time_t* mtimes, int* index) {
    DIR* dir = opendir(dir_path);
    if (!dir) {
        return;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // Create full path
        size_t path_len = strlen(dir_path) + strlen(entry->d_name) + 2;
        char* full_path = malloc(path_len);
        snprintf(full_path, path_len, "%s/%s", dir_path, entry->d_name);
        
        struct stat st;
        if (stat(full_path, &st) == 0) {
            if (S_ISREG(st.st_mode) && is_markdown_file(entry->d_name)) {
                files[*index] = full_path;
                mtimes[*index] = st.st_mtime;
                (*index)++;
            } else if (S_ISDIR(st.st_mode)) {
                // Recursively collect files from subdirectory
                collect_markdown_files_recursive(full_path, files, mtimes, index);
                free(full_path);
            } else {
                free(full_path);
            }
        } else {
            free(full_path);
        }
    }
    
    closedir(dir);
}

/**
 * @brief Scan directory recursively for markdown files and their modification times
 */
static int scan_directory(const char* dir_path, char*** files, time_t** mtimes, int* file_count) {
    // First pass: count markdown files recursively
    int count = count_markdown_files_recursive(dir_path);
    
    if (count == 0) {
        *files = NULL;
        *mtimes = NULL;
        *file_count = 0;
        return 0;
    }
    
    // Allocate arrays
    *files = malloc(count * sizeof(char*));
    *mtimes = malloc(count * sizeof(time_t));
    if (!*files || !*mtimes) {
        return -1;
    }
    
    // Second pass: collect files and modification times recursively
    int index = 0;
    collect_markdown_files_recursive(dir_path, *files, *mtimes, &index);
    
    *file_count = index;
    return 0;
}

/**
 * @brief Free file tracking arrays
 */
static void free_file_arrays(char** files, time_t* mtimes, int count) {
    if (files) {
        for (int i = 0; i < count; i++) {
            free(files[i]);
        }
        free(files);
    }
    if (mtimes) {
        free(mtimes);
    }
}

/**
 * @brief Watch command implementation
 */
int cmd_watch(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s watch <input_dir> [output_dir] [options]\n", argv[0]);
        fprintf(stderr, "   or: %s watch <input_dir> --output-dir <output_dir> [options]\n", argv[0]);
        fprintf(stderr, "\nOptions:\n");
        fprintf(stderr, "  --output-dir, -o <dir>  Output directory\n");
        fprintf(stderr, "  --format <fmt>          Output format: markdown, html, json (default: markdown)\n");
        fprintf(stderr, "  --verbose, -v           Verbose output\n");
        fprintf(stderr, "\nExamples:\n");
        fprintf(stderr, "  %s watch src/ dist/                    # Shorthand\n", argv[0]);
        fprintf(stderr, "  %s watch src/ --output-dir dist/       # Standard\n", argv[0]);
        fprintf(stderr, "  %s watch src/ dist/ --format html      # With format\n", argv[0]);
        return 1;
    }
    
    const char* watch_dir = argv[2];
    const char* output_dir = NULL;
    const char* format = "markdown";  // Default to markdown for watch
    bool verbose = false;
    
    // Check for shorthand: xmd watch <input_dir> <output_dir>
    if (argc >= 4 && argv[3][0] != '-') {
        output_dir = argv[3];
    }
    
    // Parse options
    for (int i = (output_dir ? 4 : 3); i < argc; i++) {
        if ((strcmp(argv[i], "--output-dir") == 0 || strcmp(argv[i], "-o") == 0) && i + 1 < argc) {
            if (output_dir) {
                fprintf(stderr, "Error: Output directory specified both as argument and option\n");
                return 1;
            }
            output_dir = argv[++i];
        } else if (strcmp(argv[i], "--format") == 0 && i + 1 < argc) {
            format = argv[++i];
            // Validate format
            if (strcmp(format, "markdown") != 0 && strcmp(format, "html") != 0 && strcmp(format, "json") != 0) {
                fprintf(stderr, "Error: Invalid format '%s'. Valid formats: markdown, html, json\n", format);
                return 1;
            }
        } else if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0) {
            verbose = true;
        } else {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            return 1;
        }
    }
    
    // Verify directory exists
    struct stat st;
    if (stat(watch_dir, &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: Directory '%s' does not exist or is not a directory\n", watch_dir);
        return 1;
    }
    
    // Set up signal handling for graceful shutdown
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    printf("🔍 Watching directory: %s\n", watch_dir);
    printf("📝 Monitoring .md files for changes...\n");
    printf("Press Ctrl+C to stop\n\n");
    
    // Initial scan
    char** files = NULL;
    time_t* mtimes = NULL;
    int file_count = 0;
    
    if (scan_directory(watch_dir, &files, &mtimes, &file_count) != 0) {
        fprintf(stderr, "Error: Failed to scan directory\n");
        return 1;
    }
    
    if (verbose && file_count > 0) {
        printf("Found %d markdown file(s):\n", file_count);
        for (int i = 0; i < file_count; i++) {
            printf("  %s\n", files[i]);
        }
        printf("\n");
    }
    
    // Show output configuration
    if (output_dir) {
        printf("📁 Output directory: %s\n", output_dir);
        printf("📄 Output format: %s\n", format);
        printf("\n");
    } else {
        printf("📄 Output: stdout (format: %s)\n\n", format);
    }
    
    // Process all files initially
    for (int i = 0; i < file_count; i++) {
        process_file_with_output(files[i], watch_dir, output_dir, format, verbose);
    }
    
    if (file_count > 0) {
        printf("\n✅ Initial processing complete. Watching for changes...\n\n");
    }
    
    // Watch loop
    while (watch_running) {
        usleep(500000); // 500ms delay
        
        // Check existing files for changes
        for (int i = 0; i < file_count; i++) {
            time_t current_mtime = get_file_mtime(files[i]);
            if (current_mtime > mtimes[i]) {
                printf("📝 File changed: %s\n", files[i]);
                process_file_with_output(files[i], watch_dir, output_dir, format, verbose);
                mtimes[i] = current_mtime;
                printf("\n");
            }
        }
        
        // Check for new files (rescan directory periodically)
        static int scan_counter = 0;
        if (++scan_counter >= 10) { // Rescan every 5 seconds
            scan_counter = 0;
            
            char** new_files = NULL;
            time_t* new_mtimes = NULL;
            int new_file_count = 0;
            
            if (scan_directory(watch_dir, &new_files, &new_mtimes, &new_file_count) == 0) {
                if (new_file_count > file_count) {
                    printf("📁 New files detected, rescanning...\n");
                    free_file_arrays(files, mtimes, file_count);
                    files = new_files;
                    mtimes = new_mtimes;
                    file_count = new_file_count;
                    
                    if (verbose) {
                        printf("Now watching %d markdown file(s)\n\n", file_count);
                    }
                } else {
                    free_file_arrays(new_files, new_mtimes, new_file_count);
                }
            }
        }
    }
    
    // Cleanup
    free_file_arrays(files, mtimes, file_count);
    printf("Watch stopped.\n");
    return 0;
}