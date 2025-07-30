#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmd_uninstall.h"

int cmd_uninstall(int argc, char* argv[]) {
    char response[10];
    char exe_path[4096];
    ssize_t len;
    
    // Get the path to the current executable
    len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len == -1) {
        fprintf(stderr, "Error: Could not determine executable path\n");
        return EXIT_FAILURE;
    }
    exe_path[len] = '\0';
    
    printf("This will remove XMD from: %s\n", exe_path);
    printf("Are you sure you want to uninstall XMD? (Y/N): ");
    fflush(stdout);
    
    if (fgets(response, sizeof(response), stdin) == NULL) {
        fprintf(stderr, "Error reading response\n");
        return EXIT_FAILURE;
    }
    
    // Remove newline
    response[strcspn(response, "\n")] = 0;
    
    if (strcasecmp(response, "y") != 0 && strcasecmp(response, "yes") != 0) {
        printf("Uninstall cancelled.\n");
        return EXIT_SUCCESS;
    }
    
    printf("Uninstalling XMD...\n");
    
    // Remove the executable
    if (unlink(exe_path) != 0) {
        perror("Error removing XMD");
        fprintf(stderr, "You may need to run with sudo or manually remove: %s\n", exe_path);
        return EXIT_FAILURE;
    }
    
    printf("XMD has been successfully uninstalled.\n");
    return EXIT_SUCCESS;
}