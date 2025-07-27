#!/bin/bash
# Fix strdup issues by adding proper headers

files=(
"src/bindings/c_api/preprocess_for_loops/preprocess_for_loops.c"
"src/bindings/c_api/xmd_get_config/xmd_get_config.c"
"src/bindings/c_api/create_result/create_result.c"
"src/bindings/c_api/xmd_set_config/xmd_set_config.c"
"src/executor/executor/set_executor_error/set_executor_error.c"
"src/executor/executor/parse_command_args/parse_command_args.c"
"src/dependency/add_to_cycle_path/add_to_cycle_path.c"
"src/dependency/graph/dependency_graph_topological_sort/dependency_graph_topological_sort.c"
"src/dependency/detector/dependency_get_cycle_path/dependency_get_cycle_path.c"
"src/variable/variable_object_set/variable_object_set.c"
"src/variable/variable_object_keys/variable_object_keys.c"
"src/module/module_add_dependency/module_add_dependency.c"
"src/module/module_new/module_new.c"
"src/module/module_registry_add_search_path/module_registry_add_search_path.c"
"src/module/module_resolve_path/module_resolve_path.c"
"src/loop/for_loop/for_loop.c"
"src/cli/cli_init/cli_init.c"
"src/cli/cli/cli.c"
"src/cli/cli_commands.c"
"src/cli/parser/cli_parse_args/cli_parse_args.c"
"src/import_export/export_directive_new/export_directive_new.c"
"src/import_export/import/import.c"
"src/import_export/import_directive_new/import_directive_new.c"
"src/docs/reference/reference.c"
"src/docs/examples/examples.c"
"src/security/auditor/security_audit_log/security_audit_log.c"
"src/security/auditor/security_audit_init/security_audit_init.c"
"src/security/auditor/security_audit_get_entries/security_audit_get_entries.c"
"src/conditional/if_statement/if_statement.c"
"src/main/cmd_process/cmd_process.c"
"src/main/convert_shorthand_to_process/convert_shorthand_to_process.c"
"src/config/create_default_security/create_default_security.c"
"src/config/create_default_paths/create_default_paths.c"
"src/config/xmd_internal_config_load_file/xmd_internal_config_load_file.c"
"src/config/config_load_file/config_load_file.c"
"src/config/config_set/config_set.c"
"src/config/xmd_internal_config_load_env/xmd_internal_config_load_env.c"
"src/config/xmd_internal_config_add_module_path/xmd_internal_config_add_module_path.c"
"src/config/xmd_internal_config_load_whitelist_env/xmd_internal_config_load_whitelist_env.c"
"src/config/config_load_env/config_load_env.c"
"src/config/xmd_internal_config_set_exec_whitelist/xmd_internal_config_set_exec_whitelist.c"
"src/utils/xmd_strdup/xmd_strdup.c"
"src/store/store_keys/store_keys.c"
"src/sandbox/normalize_path/normalize_path.c"
"src/sandbox/sandbox_config_add_allowed_path/sandbox_config_add_allowed_path.c"
"src/sandbox/sandbox_config_add_whitelist/sandbox_config_add_whitelist.c"
"src/performance/benchmark_run/benchmark_run.c"
"src/performance/benchmark/benchmark.c"
"src/performance/optimizer/apply_constant_folding/apply_constant_folding.c"
"src/xmd_processor/substitute_variables/substitute_variables.c"
"src/xmd_processor/process_xmd_content_enhanced/process_xmd_content_enhanced.c"
"src/xmd_processor/parse_range/parse_range.c"
"src/xmd_processor/process_multiline_directive/process_multiline_directive.c"
"src/xmd_processor/process_directive/process_directive.c"
"src/xmd_processor/process_for/process_for.c"
"src/xmd_processor/process_multiline_block/process_multiline_block.c"
"src/xmd_processor/process_import/process_import.c"
"src/xmd_processor/evaluate_condition/evaluate_condition.c"
"src/xmd_processor/xmd_process_string/xmd_process_string.c"
"src/xmd_processor/process_xmd_content_fixed/process_xmd_content_fixed.c"
"src/xmd_processor/parse_collection/parse_collection.c"
"src/xmd_processor/process_multiline_directive_enhanced/process_multiline_directive_enhanced.c"
"src/xmd_processor/process_set/process_set.c"
"src/error/error_throw/error_throw.c"
"src/resource/limiter/set_limiter_error/set_limiter_error.c"
"src/resource/set_monitor_error/set_monitor_error.c"
"src/output/set_formatter_error/set_formatter_error.c"
"src/output/output_truncate/output_truncate.c"
"src/output/output_format_text/output_format_text.c"
)

for file in "${files[@]}"; do
    if [ -f "$file" ]; then
        # Check if the file already has the needed includes
        if ! grep -q "#define _GNU_SOURCE" "$file" && ! grep -q "#include <string.h>" "$file"; then
            # Create a temporary file with the new headers
            temp_file=$(mktemp)
            
            # Extract the first comment block and add headers after it
            awk '
            BEGIN { in_comment = 0; headers_added = 0 }
            /^\/\*\*/ { in_comment = 1; print; next }
            /\*\// && in_comment { 
                print; 
                if (!headers_added) {
                    print ""
                    print "#define _GNU_SOURCE"
                    print "#include <string.h>"
                    print "#include <stdlib.h>"
                    headers_added = 1
                }
                in_comment = 0; 
                next 
            }
            in_comment { print; next }
            !headers_added && /^#include/ {
                if (!seen_gnu_source) {
                    print "#define _GNU_SOURCE"
                    seen_gnu_source = 1
                }
                if (!seen_string_h && $0 !~ /<string\.h>/) {
                    print "#include <string.h>"
                    seen_string_h = 1
                }
                if (!seen_stdlib_h && $0 !~ /<stdlib\.h>/) {
                    print "#include <stdlib.h>"
                    seen_stdlib_h = 1
                }
                headers_added = 1
                print
                next
            }
            { print }
            ' "$file" > "$temp_file"
            
            mv "$temp_file" "$file"
            echo "Fixed: $file"
        fi
    fi
done
