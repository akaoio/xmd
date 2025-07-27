/**
 * @file cli_show_help.c
 * @brief CLI help display function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>

/**
 * @brief Show CLI help
 * @param program_name Program name
 */
void cli_show_help(const char* program_name) {
    const char* prog = program_name ? program_name : "xmd";
    
    printf("XMD - eXtended MarkDown Processor\n");
    printf("Usage: %s <command> [options]\n\n", prog);
    
    printf("Commands:\n");
    printf("  process <file>     Process a markdown file\n");
    printf("  watch <dir>        Watch directory for changes\n");
    printf("  validate <file>    Validate XMD syntax\n");
    printf("  config             Show configuration\n");
    printf("  help               Show this help\n");
    printf("  version            Show version\n\n");
    
    printf("Options:\n");
    printf("  -o, --output <file>    Output file\n");
    printf("  -c, --config <file>    Configuration file\n");
    printf("  -v, --verbose          Verbose output\n");
    printf("  -q, --quiet            Quiet mode\n");
    printf("  -d, --debug            Debug mode\n");
    printf("  -h, --help             Show help\n");
    printf("      --version          Show version\n\n");
    
    printf("Examples:\n");
    printf("  %s process document.md\n", prog);
    printf("  %s process input.md -o output.md\n", prog);
    printf("  %s watch ./docs --verbose\n", prog);
    printf("  %s validate document.md\n", prog);
}