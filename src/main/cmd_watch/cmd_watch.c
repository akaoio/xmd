/**
 * @file cmd_watch.c
 * @brief XMD watch command implementation
 * @author XMD Team
 */

#define _GNU_SOURCE
#include <unistd.h>
#include "../../../include/main_internal.h"
#include "../../../include/import_tracker.h"
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
static import_tracker_t* g_import_tracker = NULL;

// Forward declarations
static int process_file_with_output(const char* filepath, const char* input_dir,
                                  const char* output_dir, const char* format, bool verbose);

/**
 * @brief Signal handler for graceful shutdown
 */
static void signal_handler(int sig) {
    (void)sig; // Suppress unused parameter warning
    watch_running = false;
    // Use async-signal-safe write() instead of printf()
    const char* msg = "\nStopping watch...\n";
    write(STDOUT_FILENO, msg, strlen(msg));
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

// Forward declarations
static int process_file_with_output(const char* filepath, const char* input_dir,
                                  const char* output_dir, const char* format, bool verbose);
static int process_single_file_with_output(const char* input_file, const char* output_file,
                                         const char* format, bool verbose);

// Structure to track visited files during recursive processing
typedef struct visited_file {
    char* filepath;
    struct visited_file* next;
} visited_file_t;

// Helper function to check if a file has been visited
static bool is_file_visited(visited_file_t* visited_files, const char* filepath) {
    visited_file_t* current = visited_files;
    while (current) {
        if (strcmp(current->filepath, filepath) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Helper function to add a file to visited list
static visited_file_t* add_visited_file(visited_file_t* visited_files, const char* filepath) {
    visited_file_t* new_visited = malloc(sizeof(visited_file_t));
    if (!new_visited) return visited_files;
    
    new_visited->filepath = strdup(filepath);
    if (!new_visited->filepath) {
        free(new_visited);
        return visited_files;
    }
    
    new_visited->next = visited_files;
    return new_visited;
}

// Helper function to free visited files list
static void free_visited_files(visited_file_t* visited_files) {
    while (visited_files) {
        visited_file_t* current = visited_files;
        visited_files = visited_files->next;
        free(current->filepath);
        free(current);
    }
}

// Internal recursive function with cycle detection
static void process_dependent_files_internal(const char* changed_file, const char* input_dir,
                                           const char* output_dir, const char* format, 
                                           bool verbose, visited_file_t** visited_files,
                                           int depth) {
    if (!g_import_tracker || !changed_file || depth > 10) { // Prevent excessive recursion
        return;
    }
    
    // Check if we've already processed this file to prevent cycles
    if (is_file_visited(*visited_files, changed_file)) {
        if (verbose && depth > 0) {
            printf("🔄 Skipping already processed: %s (cycle prevention)\n", changed_file);
        }
        return;
    }
    
    // Add to visited list
    *visited_files = add_visited_file(*visited_files, changed_file);
    
    // Get all files that import the changed file
    char** importers = NULL;
    int importer_count = 0;
    
    if (import_tracker_get_importers(g_import_tracker, changed_file, &importers, &importer_count)) {
        if (importer_count > 0 && verbose) {
            printf("🔄 Found %d file(s) importing %s (depth %d)\n", importer_count, changed_file, depth);
        }
        
        // Process each importer
        for (int i = 0; i < importer_count; i++) {
            printf("🔄 Reprocessing dependent: %s\n", importers[i]);
            process_file_with_output(importers[i], input_dir, output_dir, format, verbose);
            
            // Recursively process files that import this importer
            process_dependent_files_internal(importers[i], input_dir, output_dir, format, 
                                           verbose, visited_files, depth + 1);
            
            free(importers[i]);
        }
        free(importers);
    }
}

/**
 * @brief Process all files that import the changed file (recursive with cycle detection)
 */
static void process_dependent_files(const char* changed_file, const char* input_dir,
                                  const char* output_dir, const char* format, bool verbose) {
    if (!g_import_tracker || !changed_file) {
        return;
    }
    
    visited_file_t* visited_files = NULL;
    process_dependent_files_internal(changed_file, input_dir, output_dir, format, 
                                   verbose, &visited_files, 0);
    free_visited_files(visited_files);
}

// Forward declaration for @ syntax preprocessing
static char* preprocess_at_syntax(const char* input);

/**
 * @brief Convert @ syntax to HTML comment directives (simplified version)
 */
static char* preprocess_at_syntax(const char* input) {
    if (!input) {
        return NULL;
    }
    
    size_t input_len = strlen(input);
    size_t output_capacity = input_len * 2 + 1; // Extra space for expansions  
    char* output = malloc(output_capacity);
    if (!output) {
        return NULL;
    }
    
    size_t output_pos = 0;
    const char* ptr = input;
    
    while (*ptr) {
        // Look for @ syntax at start of line or after whitespace
        if (*ptr == '@' && (ptr == input || *(ptr-1) == '\n' || *(ptr-1) == ' ' || *(ptr-1) == '\t')) {
            // Check for @import directive
            if (strncmp(ptr, "@import(", 8) == 0) {
                // Find closing parenthesis
                const char* start = ptr + 8;
                const char* end = strchr(start, ')');
                if (end) {
                    // Extract filename (remove quotes if present)
                    size_t filename_len = end - start;
                    char* filename = malloc(filename_len + 1);
                    if (filename) {
                        strncpy(filename, start, filename_len);
                        filename[filename_len] = '\0';
                        
                        // Remove quotes if present
                        char* clean_filename = filename;
                        if (filename[0] == '"' && filename[filename_len-1] == '"') {
                            filename[filename_len-1] = '\0';
                            clean_filename = filename + 1;
                        } else if (filename[0] == '\'' && filename[filename_len-1] == '\'') {
                            filename[filename_len-1] = '\0';
                            clean_filename = filename + 1;
                        }
                        
                        // Ensure we have enough space
                        size_t replacement_len = 15 + strlen(clean_filename) + 4; // "<!-- xmd: import " + filename + " -->"
                        if (output_pos + replacement_len >= output_capacity) {
                            output_capacity = (output_pos + replacement_len) * 2;
                            char* new_output = realloc(output, output_capacity);
                            if (!new_output) {
                                free(filename);
                                free(output);
                                return NULL;
                            }
                            output = new_output;
                        }
                        
                        // Write HTML comment replacement
                        int written = snprintf(output + output_pos, output_capacity - output_pos, 
                                             "<!-- xmd: import %s -->", clean_filename);
                        if (written > 0) {
                            output_pos += written;
                        }
                        
                        free(filename);
                        ptr = end + 1; // Skip past the closing parenthesis
                        continue;
                    }
                }
            }
        }
        
        // Copy character as-is if not part of @ directive
        if (output_pos >= output_capacity - 1) {
            output_capacity *= 2;
            char* new_output = realloc(output, output_capacity);
            if (!new_output) {
                free(output);
                return NULL;
            }
            output = new_output;
        }
        output[output_pos++] = *ptr++;
    }
    
    output[output_pos] = '\0';
    return output;
}

/**
 * @brief Extract and track imports from a processed file
 */
static void track_file_imports(const char* filepath) {
    if (!g_import_tracker || !filepath) {
        return;
    }
    
    // Read the file content
    FILE* file = fopen(filepath, "r");
    if (!file) {
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = malloc(file_size + 1);
    if (!content) {
        fclose(file);
        return;
    }
    
    size_t read_size = fread(content, 1, file_size, file);
    content[read_size] = '\0';
    fclose(file);
    
    // Preprocess @ syntax to HTML comments before extracting imports
    char* processed_content = preprocess_at_syntax(content);
    free(content);
    
    if (!processed_content) {
        return;
    }
    
    // Extract imports from processed content
    char** imports = NULL;
    int import_count = 0;
    
    if (import_tracker_extract_imports(processed_content, filepath, &imports, &import_count)) {
        // Track each import dependency
        for (int i = 0; i < import_count; i++) {
            import_tracker_add_dependency(g_import_tracker, filepath, imports[i]);
            free(imports[i]);
        }
        free(imports);
    }
    
    free(processed_content);
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
            // Track imports for this file
            track_file_imports(filepath);
            
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
        
        if (result == 0) {
            // Track imports for this file
            track_file_imports(filepath);
            
            if (verbose) {
                printf("✅ Successfully processed: %s\n", filepath);
            }
        } else {
            printf("❌ Error processing: %s\n", filepath);
        }
        
        return result;
    }
}

/**
 * @brief Process a single file with direct output path (for file mode)
 */
static int process_single_file_with_output(const char* input_file, const char* output_file,
                                         const char* format, bool verbose) {
    if (verbose) {
        printf("Processing: %s\n", input_file);
    }
    
    if (output_file) {
        // Create output directory if needed
        char* output_dir_path = strdup(output_file);
        char* last_slash = strrchr(output_dir_path, '/');
        if (last_slash) {
            *last_slash = '\0';
            if (create_directory_recursive(output_dir_path) != 0) {
                printf("❌ Failed to create output directory: %s\n", output_dir_path);
                free(output_dir_path);
                return 1;
            }
        }
        free(output_dir_path);
        
        // Create process command arguments with direct output
        char* process_argv[] = { "xmd", "process", (char*)input_file, "-o", (char*)output_file, "--format", (char*)format, NULL };
        
        int result = cmd_process(7, process_argv);
        
        if (result == 0) {
            // Track imports for this file
            track_file_imports(input_file);
            
            if (verbose) {
                printf("✅ Successfully processed: %s → %s\n", input_file, output_file);
            } else {
                printf("✅ %s → %s\n", input_file, output_file);
            }
        } else {
            printf("❌ Error processing: %s\n", input_file);
        }
        
        return result;
    } else {
        // No output file - process to stdout
        char* process_argv[] = { "xmd", "process", (char*)input_file, "--format", (char*)format, NULL };
        
        int result = cmd_process(5, process_argv);
        
        if (result == 0) {
            // Track imports for this file
            track_file_imports(input_file);
            
            if (verbose) {
                printf("✅ Successfully processed: %s\n", input_file);
            }
        } else {
            printf("❌ Error processing: %s\n", input_file);
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
        fprintf(stderr, "Usage: %s watch <input> [output] [options]\n", argv[0]);
        fprintf(stderr, "\nInput modes:\n");
        fprintf(stderr, "  Directory: %s watch <input_dir> [output_dir] [options]\n", argv[0]);
        fprintf(stderr, "  File:      %s watch <input_file.md> <output_file.html> [options]\n", argv[0]);
        fprintf(stderr, "\nOptions:\n");
        fprintf(stderr, "  --output-dir, -o <dir>  Output directory (directory mode only)\n");
        fprintf(stderr, "  --format <fmt>          Output format: markdown, html, json (default: markdown)\n");
        fprintf(stderr, "  --verbose, -v           Verbose output\n");
        fprintf(stderr, "\nExamples:\n");
        fprintf(stderr, "  %s watch src/ dist/                        # Directory mode\n", argv[0]);
        fprintf(stderr, "  %s watch src/file.md dist/file.html        # File mode\n", argv[0]);
        fprintf(stderr, "  %s watch src/ --output-dir dist/ --format html  # With options\n", argv[0]);
        return 1;
    }
    
    const char* input_path = argv[2];
    const char* output_path = NULL;
    const char* format = "markdown";  // Default to markdown for watch
    bool verbose = false;
    bool is_file_mode = false;
    
    // Detect input type: file vs directory
    struct stat input_st;
    if (stat(input_path, &input_st) != 0) {
        fprintf(stderr, "Error: Input '%s' does not exist\n", input_path);
        return 1;
    }
    
    is_file_mode = S_ISREG(input_st.st_mode);
    
    // Check for shorthand: xmd watch <input> <output>
    if (argc >= 4 && argv[3][0] != '-') {
        output_path = argv[3];
    }
    
    // Parse options
    for (int i = (output_path ? 4 : 3); i < argc; i++) {
        if ((strcmp(argv[i], "--output-dir") == 0 || strcmp(argv[i], "-o") == 0) && i + 1 < argc) {
            if (is_file_mode) {
                fprintf(stderr, "Error: --output-dir option not valid in file mode. Use: xmd watch <input.md> <output.html>\n");
                return 1;
            }
            if (output_path) {
                fprintf(stderr, "Error: Output specified both as argument and option\n");
                return 1;
            }
            output_path = argv[++i];
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
    
    // Validate input and output based on mode
    if (is_file_mode) {
        // File mode validation
        if (!is_markdown_file(input_path)) {
            fprintf(stderr, "Error: Input file '%s' must be a .md file\n", input_path);
            return 1;
        }
        
        if (!output_path) {
            fprintf(stderr, "Error: File mode requires output file. Usage: xmd watch <input.md> <output.html>\n");
            return 1;
        }
        
        // Check if output directory exists and create if needed
        char* output_dir_path = strdup(output_path);
        char* last_slash = strrchr(output_dir_path, '/');
        if (last_slash) {
            *last_slash = '\0';
            if (create_directory_recursive(output_dir_path) != 0) {
                printf("❌ Failed to create output directory: %s\n", output_dir_path);
                free(output_dir_path);
                return 1;
            }
        }
        free(output_dir_path);
    } else {
        // Directory mode validation
        if (!S_ISDIR(input_st.st_mode)) {
            fprintf(stderr, "Error: Input '%s' is not a directory\n", input_path);
            return 1;
        }
    }
    
    // Set up signal handling for graceful shutdown
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    // Initialize import tracker
    g_import_tracker = import_tracker_create();
    if (!g_import_tracker) {
        fprintf(stderr, "Error: Failed to create import tracker\n");
        return 1;
    }
    
    // Set global import tracker for watch mode
    // Re-enabling after @ syntax implementation - should be safe now
    xmd_set_global_import_tracker(g_import_tracker);
    
    if (is_file_mode) {
        printf("🔍 Watching file: %s\n", input_path);
        if (output_path) {
            printf("📁 Output file: %s\n", output_path);
        }
    } else {
        printf("🔍 Watching directory: %s\n", input_path);
    }
    printf("📝 Monitoring .md files for changes...\n");
    printf("Press Ctrl+C to stop\n\n");
    
    // Initial scan - different logic for file vs directory mode
    char** files = NULL;
    time_t* mtimes = NULL;
    int file_count = 0;
    
    if (is_file_mode) {
        // File mode: single file in array
        file_count = 1;
        files = malloc(sizeof(char*));
        mtimes = malloc(sizeof(time_t));
        if (!files || !mtimes) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return 1;
        }
        files[0] = strdup(input_path);
        mtimes[0] = get_file_mtime(input_path);
    } else {
        // Directory mode: scan for all markdown files
        if (scan_directory(input_path, &files, &mtimes, &file_count) != 0) {
            fprintf(stderr, "Error: Failed to scan directory\n");
            return 1;
        }
    }
    
    if (verbose && file_count > 0) {
        printf("Found %d markdown file(s):\n", file_count);
        for (int i = 0; i < file_count; i++) {
            printf("  %s\n", files[i]);
        }
        printf("\n");
    }
    
    // Show output configuration
    if (is_file_mode) {
        printf("📄 Output format: %s\n\n", format);
    } else if (output_path) {
        printf("📁 Output directory: %s\n", output_path);
        printf("📄 Output format: %s\n", format);
        printf("\n");
    } else {
        printf("📄 Output: stdout (format: %s)\n\n", format);
    }
    
    // Process all files initially
    for (int i = 0; i < file_count; i++) {
        if (is_file_mode) {
            // File mode: use direct output path
            process_single_file_with_output(files[i], output_path, format, verbose);
        } else {
            // Directory mode: use directory-based processing
            process_file_with_output(files[i], input_path, output_path, format, verbose);
        }
    }
    
    if (file_count > 0) {
        printf("\n✅ Initial processing complete. Watching for changes...\n\n");
    }
    
    // Watch loop
    while (watch_running) {
        // Handle interrupted system calls properly
        if (usleep(500000) == -1 && errno == EINTR) {
            // Signal was received, check if we should continue
            if (!watch_running) break;
        }
        
        // Check existing files for changes
        for (int i = 0; i < file_count; i++) {
            time_t current_mtime = get_file_mtime(files[i]);
            if (current_mtime > mtimes[i]) {
                printf("📝 File changed: %s\n", files[i]);
                
                if (is_file_mode) {
                    // File mode: process single file directly
                    process_single_file_with_output(files[i], output_path, format, verbose);
                    
                    // Process all files that import this changed file (directory needs to be derived)
                    char* file_dir = strdup(files[i]);
                    char* last_slash = strrchr(file_dir, '/');
                    if (last_slash) {
                        *last_slash = '\0';
                        process_dependent_files(files[i], file_dir, NULL, format, verbose);
                    } else {
                        process_dependent_files(files[i], ".", NULL, format, verbose);
                    }
                    free(file_dir);
                } else {
                    // Directory mode: use original logic
                    process_file_with_output(files[i], input_path, output_path, format, verbose);
                    process_dependent_files(files[i], input_path, output_path, format, verbose);
                }
                
                mtimes[i] = current_mtime;
                printf("\n");
            }
        }
        
        // Check if we should stop after processing files
        if (!watch_running) break;
        
        // Check for new files (rescan directory periodically) - only in directory mode
        if (!is_file_mode) {
            static int scan_counter = 0;
            if (++scan_counter >= 10) { // Rescan every 5 seconds
                scan_counter = 0;
                
                char** new_files = NULL;
                time_t* new_mtimes = NULL;
                int new_file_count = 0;
                
                if (scan_directory(input_path, &new_files, &new_mtimes, &new_file_count) == 0) {
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
    }
    
    // Cleanup
    free_file_arrays(files, mtimes, file_count);
    if (g_import_tracker) {
        xmd_set_global_import_tracker(NULL); // Clear global tracker
        import_tracker_free(g_import_tracker);
        g_import_tracker = NULL;
    }
    printf("Watch stopped.\n");
    return 0;
}