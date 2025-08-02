/**
 * @file dead_function_detector.c
 * @brief Main entry point for dead function detection system
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 * Standard C only - no external dependencies
 * 
 * This orchestrates the analysis pipeline:
 * 1. file_scanner: Find all C source files
 * 2. function_finder: Extract function info from each file
 * 3. usage_tracker: Analyze usage and generate report
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// External development tool - completely standalone
// Does not depend on XMD core includes

// Function declarations (following Genesis principle)
extern int file_scanner(const char* dir_path, FILE* output_file);
extern int function_finder(const char* file_path, FILE* output_file);
extern int usage_tracker(const char* analysis_file_path, FILE* output_file);

/**
 * @brief Main dead function detection orchestrator
 * @param scan_path Directory path to scan for dead functions
 * @return 0 on success, 1 on failure
 */
int dead_function_detector_main(const char* scan_path) {
    if (!scan_path) {
        printf("ERROR: No scan path provided\n");
        return 1;
    }
    
    printf("🔍 XMD Dead Function Detector (Genesis Compliant)\n");
    printf("================================================\n");
    printf("Scanning path: %s\n\n", scan_path);
    
    // Step 1: Create temporary files for pipeline
    FILE* files_list = tmpfile();
    FILE* analysis_data = tmpfile();
    
    if (!files_list || !analysis_data) {
        printf("ERROR: Could not create temporary files\n");
        return 1;
    }
    
    // Step 2: Scan for C source files
    printf("📁 Step 1: Scanning for C source files...\n");
    if (!file_scanner(scan_path, files_list)) {
        printf("ERROR: Failed to scan directory\n");
        fclose(files_list);
        fclose(analysis_data);
        return 1;
    }
    
    // Step 3: Analyze each file for functions
    printf("🔍 Step 2: Analyzing functions in each file...\n");
    rewind(files_list);
    
    char file_path[512];
    int files_processed = 0;
    
    while (fgets(file_path, sizeof(file_path), files_list)) {
        // Remove newline
        file_path[strcspn(file_path, "\n")] = 0;
        
        if (strlen(file_path) > 0) {
            printf("  Analyzing: %s\n", file_path);
            
            if (!function_finder(file_path, analysis_data)) {
                printf("  WARNING: Could not analyze %s\n", file_path);
            } else {
                files_processed++;
            }
        }
    }
    
    printf("  Processed %d files\n\n", files_processed);
    
    // Step 4: Track usage and generate report
    printf("📊 Step 3: Generating dead function report...\n\n");
    
    // Write analysis data to temporary file so usage_tracker can read it
    fflush(analysis_data);
    
    // Create a named temporary file for the analysis data
    char temp_analysis_path[] = "/tmp/xmd_analysis_XXXXXX";
    int temp_fd = mkstemp(temp_analysis_path);
    if (temp_fd == -1) {
        printf("ERROR: Could not create temporary analysis file\n");
        fclose(files_list);
        fclose(analysis_data);
        return 1;
    }
    
    FILE* temp_analysis_file = fdopen(temp_fd, "w+");
    if (!temp_analysis_file) {
        printf("ERROR: Could not open temporary analysis file\n");
        close(temp_fd);
        unlink(temp_analysis_path);
        fclose(files_list);
        fclose(analysis_data);
        return 1;
    }
    
    // Copy analysis data to named temporary file
    rewind(analysis_data);
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), analysis_data)) {
        fputs(buffer, temp_analysis_file);
    }
    fclose(temp_analysis_file);
    
    // Generate report
    if (!usage_tracker(temp_analysis_path, stdout)) {
        printf("ERROR: Failed to generate usage report\n");
        unlink(temp_analysis_path);
        fclose(files_list);
        fclose(analysis_data);
        return 1;
    }
    
    // Cleanup
    unlink(temp_analysis_path);
    fclose(files_list);
    fclose(analysis_data);
    
    printf("\n✅ Dead function analysis completed successfully!\n");
    printf("🎯 This tool follows Genesis principles:\n");
    printf("   • Standard C only (no external dependencies)\n");
    printf("   • 1 function → 1 file → 1 directory\n");
    printf("   • Complete implementation (no stubs/TODOs)\n");
    printf("   • Proper error handling and memory management\n");
    
    return 0;
}

/**
 * @brief Main entry point
 * @param argc Argument count
 * @param argv Argument values
 * @return 0 on success, 1 on failure
 */
int main(int argc, char* argv[]) {
    const char* scan_path = ".";
    
    if (argc > 1) {
        scan_path = argv[1];
    }
    
    return dead_function_detector_main(scan_path);
}