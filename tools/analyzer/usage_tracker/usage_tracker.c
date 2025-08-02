/**
 * @file usage_tracker.c
 * @brief Track function usage and detect dead functions
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 * Standard C only - no external dependencies
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External development tool - standalone, no XMD dependencies

#define MAX_FUNCTIONS 5000
#define MAX_FUNCTION_NAME 256

typedef struct {
    char name[MAX_FUNCTION_NAME];
    char file_path[512];
    int line_number;
    int call_count;
    int has_declaration;
    int has_definition;
} function_record;

typedef struct {
    function_record functions[MAX_FUNCTIONS];
    int count;
} usage_database;

/**
 * @brief Find function in database by name
 * @param db Usage database
 * @param name Function name to find
 * @return Index if found, -1 if not found
 */
static int find_function(usage_database* db, const char* name) {
    if (!db || !name) {
        return -1;
    }
    
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->functions[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Add or update function record
 * @param db Usage database
 * @param name Function name
 * @param file_path Source file path
 * @param line_number Line number
 * @param type Record type: "DEF", "DECL", or "CALL"
 * @return 1 on success, 0 on failure
 */
static int add_function_record(usage_database* db, const char* name, 
                              const char* file_path, int line_number, 
                              const char* type) {
    if (!db || !name || !file_path || !type) {
        return 0;
    }
    
    int index = find_function(db, name);
    
    if (index == -1) {
        // Add new function
        if (db->count >= MAX_FUNCTIONS) {
            return 0;
        }
        
        index = db->count;
        strncpy(db->functions[index].name, name, MAX_FUNCTION_NAME - 1);
        strncpy(db->functions[index].file_path, file_path, 511);
        db->functions[index].line_number = line_number;
        db->functions[index].call_count = 0;
        db->functions[index].has_declaration = 0;
        db->functions[index].has_definition = 0;
        db->count++;
    }
    
    // Update function record based on type
    if (strcmp(type, "DEF") == 0) {
        db->functions[index].has_definition = 1;
        // Update definition location
        strncpy(db->functions[index].file_path, file_path, 511);
        db->functions[index].line_number = line_number;
    } else if (strcmp(type, "DECL") == 0) {
        db->functions[index].has_declaration = 1;
    } else if (strcmp(type, "CALL") == 0) {
        db->functions[index].call_count++;
    }
    
    return 1;
}

/**
 * @brief Track function usage from analysis file
 * @param analysis_file_path Path to analysis file (output from function_finder)
 * @param output_file Output file for dead function report
 * @return 1 on success, 0 on failure
 */
int usage_tracker(const char* analysis_file_path, FILE* output_file) {
    if (!analysis_file_path || !output_file) {
        return 0;
    }
    
    FILE* analysis_file = fopen(analysis_file_path, "r");
    if (!analysis_file) {
        return 0;
    }
    
    usage_database db;
    db.count = 0;
    memset(db.functions, 0, sizeof(db.functions));
    
    char line[1024];
    while (fgets(line, sizeof(line), analysis_file)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Parse line format: TYPE:FUNCTION_NAME:FILE_PATH:LINE_NUMBER
        char* type = strtok(line, ":");
        char* name = strtok(NULL, ":");
        char* file_path = strtok(NULL, ":");
        char* line_num_str = strtok(NULL, ":");
        
        if (type && name && file_path && line_num_str) {
            int line_number = atoi(line_num_str);
            add_function_record(&db, name, file_path, line_number, type);
        }
    }
    
    fclose(analysis_file);
    
    // Generate dead function report
    fprintf(output_file, "🔍 XMD DEAD FUNCTION ANALYSIS REPORT\n");
    fprintf(output_file, "====================================\n\n");
    fprintf(output_file, "📊 SCAN SUMMARY:\n");
    fprintf(output_file, "• Functions analyzed: %d\n\n", db.count);
    
    int dead_count = 0;
    int ghost_count = 0;
    int orphan_count = 0;
    
    fprintf(output_file, "💀 DEAD FUNCTIONS (defined but never called):\n");
    fprintf(output_file, "---------------------------------------------\n");
    for (int i = 0; i < db.count; i++) {
        function_record* func = &db.functions[i];
        if (func->has_definition && func->call_count == 0 && 
            strcmp(func->name, "main") != 0) {
            fprintf(output_file, "• %s() in %s:%d\n", 
                   func->name, func->file_path, func->line_number);
            dead_count++;
        }
    }
    fprintf(output_file, "Total dead functions: %d\n\n", dead_count);
    
    fprintf(output_file, "👻 GHOST FUNCTIONS (declared but not defined):\n");
    fprintf(output_file, "----------------------------------------------\n");
    for (int i = 0; i < db.count; i++) {
        function_record* func = &db.functions[i];
        if (func->has_declaration && !func->has_definition) {
            fprintf(output_file, "• %s() declared in %s:%d\n", 
                   func->name, func->file_path, func->line_number);
            ghost_count++;
        }
    }
    fprintf(output_file, "Total ghost functions: %d\n\n", ghost_count);
    
    fprintf(output_file, "⚠️  ORPHANED FUNCTIONS (definition only, no declaration):\n");
    fprintf(output_file, "--------------------------------------------------------\n");
    for (int i = 0; i < db.count; i++) {
        function_record* func = &db.functions[i];
        if (func->has_definition && !func->has_declaration && func->call_count > 0) {
            fprintf(output_file, "• %s() in %s:%d\n", 
                   func->name, func->file_path, func->line_number);
            orphan_count++;
        }
    }
    fprintf(output_file, "Total orphaned functions: %d\n\n", orphan_count);
    
    fprintf(output_file, "📋 CLEANUP RECOMMENDATIONS:\n");
    fprintf(output_file, "---------------------------\n");
    fprintf(output_file, "• Remove %d dead functions to reduce codebase\n", dead_count);
    fprintf(output_file, "• Fix %d ghost function declarations\n", ghost_count);
    fprintf(output_file, "• Add declarations for %d orphaned functions\n", orphan_count);
    
    int total_removable = dead_count + ghost_count;
    fprintf(output_file, "• Total removable functions: %d\n", total_removable);
    if (db.count > 0) {
        fprintf(output_file, "• Estimated code reduction: %d%% - %d%%\n", 
               (total_removable * 100) / db.count,
               ((total_removable + orphan_count) * 100) / db.count);
    }
    
    return 1;
}