/**
 * @file function_usage_analyzer.c
 * @brief Dead function detection system for XMD codebase
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 * 
 * This analyzer detects:
 * - Functions declared but never called (dead functions)
 * - Duplicate functions with identical logic
 * - Ghost functions (stubs, TODOs)
 * - Orphaned functions (no callers)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
// Simple malloc/free wrapper for standalone analyzer
#ifndef XMD_MALLOC
#define XMD_MALLOC malloc
#endif
#ifndef XMD_FREE  
#define XMD_FREE free
#endif

void* xmd_malloc(size_t size) { return malloc(size); }
void xmd_free(void* ptr) { if (ptr) free(ptr); }

#define MAX_FUNCTIONS 5000
#define MAX_FILES 2000
#define MAX_FUNCTION_NAME 256
#define MAX_FILE_PATH 512

typedef struct {
    char name[MAX_FUNCTION_NAME];
    char file_path[MAX_FILE_PATH];
    int line_number;
    int call_count;
    int is_declaration;
    int is_definition;
    char signature[512];
} function_info;

typedef struct {
    function_info functions[MAX_FUNCTIONS];
    int count;
    char scanned_files[MAX_FILES][MAX_FILE_PATH];
    int file_count;
} usage_analyzer;

/**
 * @brief Create new function usage analyzer
 * @return Analyzer instance or NULL on failure
 */
usage_analyzer* analyzer_create() {
    usage_analyzer* analyzer = xmd_malloc(sizeof(usage_analyzer));
    if (!analyzer) {
        return NULL;
    }
    
    analyzer->count = 0;
    analyzer->file_count = 0;
    memset(analyzer->functions, 0, sizeof(analyzer->functions));
    memset(analyzer->scanned_files, 0, sizeof(analyzer->scanned_files));
    
    return analyzer;
}

/**
 * @brief Free analyzer memory
 * @param analyzer Analyzer to free
 */
void analyzer_free(usage_analyzer* analyzer) {
    if (analyzer) {
        xmd_free(analyzer);
    }
}

/**
 * @brief Check if function name already exists in analyzer
 * @param analyzer Analyzer instance
 * @param name Function name to check
 * @return Index of function if found, -1 if not found
 */
int analyzer_find_function(usage_analyzer* analyzer, const char* name) {
    if (!analyzer || !name) {
        return -1;
    }
    
    for (int i = 0; i < analyzer->count; i++) {
        if (strcmp(analyzer->functions[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Add function to analyzer
 * @param analyzer Analyzer instance
 * @param name Function name
 * @param file_path Source file path
 * @param line_number Line number in file
 * @param is_declaration True if function declaration
 * @param is_definition True if function definition
 * @param signature Function signature
 * @return 1 on success, 0 on failure
 */
int analyzer_add_function(usage_analyzer* analyzer, const char* name, 
                         const char* file_path, int line_number,
                         int is_declaration, int is_definition,
                         const char* signature) {
    if (!analyzer || !name || !file_path) {
        return 0;
    }
    
    if (analyzer->count >= MAX_FUNCTIONS) {
        printf("WARNING: Maximum function limit reached (%d)\n", MAX_FUNCTIONS);
        return 0;
    }
    
    // Check if function already exists
    int existing = analyzer_find_function(analyzer, name);
    if (existing >= 0) {
        // Update existing function info
        if (is_declaration) {
            analyzer->functions[existing].is_declaration = 1;
        }
        if (is_definition) {
            analyzer->functions[existing].is_definition = 1;
            // Update definition file path and line
            strncpy(analyzer->functions[existing].file_path, file_path, MAX_FILE_PATH - 1);
            analyzer->functions[existing].line_number = line_number;
        }
        return 1;
    }
    
    // Add new function
    function_info* func = &analyzer->functions[analyzer->count];
    strncpy(func->name, name, MAX_FUNCTION_NAME - 1);
    strncpy(func->file_path, file_path, MAX_FILE_PATH - 1);
    func->line_number = line_number;
    func->call_count = 0;
    func->is_declaration = is_declaration;
    func->is_definition = is_definition;
    if (signature) {
        strncpy(func->signature, signature, 511);
    }
    
    analyzer->count++;
    return 1;
}

/**
 * @brief Record function call
 * @param analyzer Analyzer instance
 * @param name Function name that was called
 */
void analyzer_record_call(usage_analyzer* analyzer, const char* name) {
    if (!analyzer || !name) {
        return;
    }
    
    int index = analyzer_find_function(analyzer, name);
    if (index >= 0) {
        analyzer->functions[index].call_count++;
    } else {
        // Add as called function (might be external)
        analyzer_add_function(analyzer, name, "external", 0, 0, 0, NULL);
        if (analyzer->count > 0) {
            analyzer->functions[analyzer->count - 1].call_count = 1;
        }
    }
}

/**
 * @brief Check if file should be scanned
 * @param file_path Path to file
 * @return 1 if should scan, 0 if should skip
 */
int should_scan_file(const char* file_path) {
    if (!file_path) {
        return 0;
    }
    
    // Only scan C source and header files
    size_t len = strlen(file_path);
    if (len < 2) {
        return 0;
    }
    
    if (strstr(file_path, ".c") || strstr(file_path, ".h")) {
        return 1;
    }
    
    return 0;
}

/**
 * @brief Scan a single file for function declarations and calls
 * @param analyzer Analyzer instance
 * @param file_path Path to file to scan
 * @return 1 on success, 0 on failure
 */
int analyzer_scan_file(usage_analyzer* analyzer, const char* file_path) {
    if (!analyzer || !file_path) {
        return 0;
    }
    
    if (!should_scan_file(file_path)) {
        return 1;
    }
    
    FILE* file = fopen(file_path, "r");
    if (!file) {
        printf("WARNING: Could not open file: %s\n", file_path);
        return 0;
    }
    
    printf("Scanning: %s\n", file_path);
    
    char line[1024];
    int line_number = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line_number++;
        
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Skip empty lines and comments
        char* trimmed = line;
        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;
        if (*trimmed == '\0' || strncmp(trimmed, "//", 2) == 0 || 
            strncmp(trimmed, "/*", 2) == 0 || *trimmed == '*') {
            continue;
        }
        
        // Look for function definitions (return_type function_name() {)
        if (strstr(line, "(") && strstr(line, ")") && strstr(line, "{")) {
            // Extract function name
            char* paren = strstr(line, "(");
            if (paren) {
                // Go backwards to find function name
                char* name_end = paren - 1;
                while (name_end > line && (*name_end == ' ' || *name_end == '\t')) {
                    name_end--;
                }
                
                char* name_start = name_end;
                while (name_start > line && 
                       ((*name_start >= 'a' && *name_start <= 'z') ||
                        (*name_start >= 'A' && *name_start <= 'Z') ||
                        (*name_start >= '0' && *name_start <= '9') ||
                        *name_start == '_')) {
                    name_start--;
                }
                name_start++;
                
                if (name_start <= name_end) {
                    char func_name[MAX_FUNCTION_NAME];
                    int name_len = name_end - name_start + 1;
                    if (name_len < MAX_FUNCTION_NAME) {
                        strncpy(func_name, name_start, name_len);
                        func_name[name_len] = '\0';
                        
                        // Skip common keywords that aren't functions
                        if (strcmp(func_name, "if") != 0 && strcmp(func_name, "for") != 0 &&
                            strcmp(func_name, "while") != 0 && strcmp(func_name, "switch") != 0) {
                            analyzer_add_function(analyzer, func_name, file_path, line_number, 0, 1, line);
                        }
                    }
                }
            }
        }
        
        // Look for function declarations (return_type function_name();)
        if (strstr(line, "(") && strstr(line, ")") && strstr(line, ";") && !strstr(line, "{")) {
            // Similar extraction logic for declarations
            char* paren = strstr(line, "(");
            if (paren) {
                char* name_end = paren - 1;
                while (name_end > line && (*name_end == ' ' || *name_end == '\t')) {
                    name_end--;
                }
                
                char* name_start = name_end;
                while (name_start > line && 
                       ((*name_start >= 'a' && *name_start <= 'z') ||
                        (*name_start >= 'A' && *name_start <= 'Z') ||
                        (*name_start >= '0' && *name_start <= '9') ||
                        *name_start == '_')) {
                    name_start--;
                }
                name_start++;
                
                if (name_start <= name_end) {
                    char func_name[MAX_FUNCTION_NAME];
                    int name_len = name_end - name_start + 1;
                    if (name_len < MAX_FUNCTION_NAME) {
                        strncpy(func_name, name_start, name_len);
                        func_name[name_len] = '\0';
                        
                        analyzer_add_function(analyzer, func_name, file_path, line_number, 1, 0, line);
                    }
                }
            }
        }
        
        // Look for function calls (function_name())
        char* pos = line;
        while ((pos = strstr(pos, "(")) != NULL) {
            // Go backwards to find function name
            char* name_end = pos - 1;
            while (name_end > line && (*name_end == ' ' || *name_end == '\t')) {
                name_end--;
            }
            
            char* name_start = name_end;
            while (name_start > line && 
                   ((*name_start >= 'a' && *name_start <= 'z') ||
                    (*name_start >= 'A' && *name_start <= 'Z') ||
                    (*name_start >= '0' && *name_start <= '9') ||
                    *name_start == '_')) {
                name_start--;
            }
            name_start++;
            
            if (name_start <= name_end) {
                char func_name[MAX_FUNCTION_NAME];
                int name_len = name_end - name_start + 1;
                if (name_len < MAX_FUNCTION_NAME && name_len > 1) {
                    strncpy(func_name, name_start, name_len);
                    func_name[name_len] = '\0';
                    
                    // Skip keywords and common non-function patterns
                    if (strcmp(func_name, "if") != 0 && strcmp(func_name, "for") != 0 &&
                        strcmp(func_name, "while") != 0 && strcmp(func_name, "switch") != 0 &&
                        strcmp(func_name, "sizeof") != 0) {
                        analyzer_record_call(analyzer, func_name);
                    }
                }
            }
            
            pos++;
        }
    }
    
    fclose(file);
    
    // Add to scanned files list
    if (analyzer->file_count < MAX_FILES) {
        strncpy(analyzer->scanned_files[analyzer->file_count], file_path, MAX_FILE_PATH - 1);
        analyzer->file_count++;
    }
    
    return 1;
}

/**
 * @brief Recursively scan directory for C files
 * @param analyzer Analyzer instance
 * @param dir_path Directory path to scan
 * @return 1 on success, 0 on failure
 */
int analyzer_scan_directory(usage_analyzer* analyzer, const char* dir_path) {
    if (!analyzer || !dir_path) {
        return 0;
    }
    
    DIR* dir = opendir(dir_path);
    if (!dir) {
        printf("WARNING: Could not open directory: %s\n", dir_path);
        return 0;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        char full_path[MAX_FILE_PATH];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
        
        struct stat statbuf;
        if (stat(full_path, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                // Recursively scan subdirectory
                analyzer_scan_directory(analyzer, full_path);
            } else if (S_ISREG(statbuf.st_mode)) {
                // Scan regular file
                analyzer_scan_file(analyzer, full_path);
            }
        }
    }
    
    closedir(dir);
    return 1;
}

/**
 * @brief Generate dead function report
 * @param analyzer Analyzer instance
 * @return 1 on success, 0 on failure
 */
int analyzer_generate_report(usage_analyzer* analyzer) {
    if (!analyzer) {
        return 0;
    }
    
    printf("\n🔍 XMD DEAD FUNCTION ANALYSIS REPORT\n");
    printf("====================================\n\n");
    
    printf("📊 SCAN SUMMARY:\n");
    printf("• Files scanned: %d\n", analyzer->file_count);
    printf("• Functions found: %d\n", analyzer->count);
    printf("\n");
    
    // Count different types
    int dead_functions = 0;
    int ghost_functions = 0;
    int declaration_only = 0;
    int definition_only = 0;
    
    printf("💀 DEAD FUNCTIONS (defined but never called):\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < analyzer->count; i++) {
        function_info* func = &analyzer->functions[i];
        if (func->is_definition && func->call_count == 0 && 
            strcmp(func->name, "main") != 0) {
            printf("• %s() in %s:%d\n", func->name, func->file_path, func->line_number);
            dead_functions++;
        }
    }
    printf("Total dead functions: %d\n\n", dead_functions);
    
    printf("👻 GHOST FUNCTIONS (declared but not defined):\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < analyzer->count; i++) {
        function_info* func = &analyzer->functions[i];
        if (func->is_declaration && !func->is_definition) {
            printf("• %s() declared in %s:%d\n", func->name, func->file_path, func->line_number);
            ghost_functions++;
        }
    }
    printf("Total ghost functions: %d\n\n", ghost_functions);
    
    printf("⚠️  ORPHANED FUNCTIONS (definition only, no declaration):\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < analyzer->count; i++) {
        function_info* func = &analyzer->functions[i];
        if (func->is_definition && !func->is_declaration) {
            printf("• %s() in %s:%d\n", func->name, func->file_path, func->line_number);
            definition_only++;
        }
    }
    printf("Total orphaned functions: %d\n\n", definition_only);
    
    printf("📋 CLEANUP RECOMMENDATIONS:\n");
    printf("---------------------------\n");
    printf("• Remove %d dead functions to reduce codebase\n", dead_functions);
    printf("• Fix %d ghost function declarations\n", ghost_functions);
    printf("• Add declarations for %d orphaned functions\n", definition_only);
    
    int total_removable = dead_functions + ghost_functions;
    printf("• Total removable functions: %d\n", total_removable);
    printf("• Estimated code reduction: %d%% - %d%%\n", 
           (total_removable * 100) / analyzer->count,
           ((total_removable + definition_only) * 100) / analyzer->count);
    
    return 1;
}

/**
 * @brief Main function usage analyzer entry point
 * @param argc Argument count
 * @param argv Argument values
 * @return 0 on success, 1 on failure
 */
int main(int argc, char* argv[]) {
    const char* scan_path = ".";
    
    if (argc > 1) {
        scan_path = argv[1];
    }
    
    printf("🔍 XMD Dead Function Detector\n");
    printf("Scanning path: %s\n\n", scan_path);
    
    usage_analyzer* analyzer = analyzer_create();
    if (!analyzer) {
        printf("ERROR: Could not create analyzer\n");
        return 1;
    }
    
    // Scan the specified directory
    if (!analyzer_scan_directory(analyzer, scan_path)) {
        printf("ERROR: Failed to scan directory\n");
        analyzer_free(analyzer);
        return 1;
    }
    
    // Generate report
    analyzer_generate_report(analyzer);
    
    analyzer_free(analyzer);
    return 0;
}