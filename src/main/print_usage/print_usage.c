/**
 * @file print_usage.c
 * @brief Usage information display function
 * @author XMD Team
 *
 * Implementation of usage information display for the XMD main module.
 */

#include "../../../include/main_internal.h"

/**
 * @brief Print usage information
 * @param program_name Name of the program
 */
void print_usage(const char* program_name) {
    printf("XMD - eXtended MarkDown processor v%s\n\n", xmd_get_version());
    printf("Usage: %s <command> [options] <file>\n", program_name);
    printf("   or: <input> | %s <command> [options]\n", program_name);
    printf("   or: %s <input.md> [output.md]  (shorthand)\n\n", program_name);
    printf("Commands:\n");
    printf("  process <file>     Process XMD file and output result\n");
    printf("  process            Process XMD input from stdin (when piped)\n");
    printf("  watch <input_dir> [output_dir]  Watch directory for changes and auto-process\n");
    printf("  validate <file>    Validate XMD syntax without processing\n");
    printf("  version           Show version information\n");
    printf("  help              Show this help message\n\n");
    printf("Options:\n");
    printf("  -o, --output <file>   Output file (default: stdout)\n");
    printf("  -v, --variable <k=v>  Set variable (can be used multiple times)\n");
    printf("  --config <file>       Use configuration file\n");
    printf("  --debug               Enable debug mode\n");
    printf("  --trace               Enable execution tracing\n");
    printf("  --no-exec             Disable command execution\n");
    printf("  --format <fmt>        Output format: markdown, html, json\n");
    printf("\nExamples:\n");
    printf("  %s process input.md -o output.md\n", program_name);
    printf("  %s process template.md -v env=prod -v region=us-east\n", program_name);
    printf("  %s watch src/ dist/ --format html\n", program_name);
    printf("  %s watch ./docs --output-dir ./build --verbose\n", program_name);
    printf("  %s validate document.md\n", program_name);
    printf("\nShorthand Examples:\n");
    printf("  %s input.md                    # Process input.md to stdout\n", program_name);
    printf("  %s input.md output.md          # Process input.md to output.md\n", program_name);
    printf("  echo \"{{name}}\" | %s            # Process stdin to stdout\n", program_name);
    printf("  echo \"{{name}}\" | %s out.md    # Process stdin to out.md\n", program_name);
}