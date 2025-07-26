cmake_minimum_required(VERSION 3.21)  # Minimum for reliable C17 support
project(xmd VERSION 1.0.0 LANGUAGES C)

# Set C standard - C17 is the minimum required standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)  # Disable compiler-specific extensions

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Platform detection and configuration
if(WIN32)
    set(XMD_PLATFORM_WINDOWS TRUE)
    add_definitions(-DXMD_PLATFORM_WINDOWS=1)
elseif(APPLE)
    set(XMD_PLATFORM_APPLE TRUE)
    add_definitions(-DXMD_PLATFORM_APPLE=1)
    if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
        set(XMD_PLATFORM_IOS TRUE)
        add_definitions(-DXMD_PLATFORM_IOS=1)
    else()
        set(XMD_PLATFORM_MACOS TRUE)
        add_definitions(-DXMD_PLATFORM_MACOS=1)
    endif()
elseif(ANDROID)
    set(XMD_PLATFORM_ANDROID TRUE)
    add_definitions(-DXMD_PLATFORM_ANDROID=1)
elseif(UNIX)
    set(XMD_PLATFORM_LINUX TRUE)
    add_definitions(-DXMD_PLATFORM_LINUX=1)
endif()

# Compiler-specific flags
if(MSVC)
    # Microsoft Visual C++
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /Od /Zi")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2 /DNDEBUG")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    # GCC/Clang
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

# Include directories
include_directories(include)
include_directories(src)

# Core library sources
set(XMD_LIB_SOURCES
    src/token/token_create/token_create.c
    src/token/token_free/token_free.c
    src/token/token_duplicate/token_duplicate.c
    src/token/token_copy/token_copy.c
    src/token/token_type_to_string/token_type_to_string.c
    src/token/token_type_is_valid/token_type_is_valid.c
    src/token/token_equals/token_equals.c
    src/token/token_set_value/token_set_value.c
    src/token/token_list_append/token_list_append.c
    src/token/token_list_length/token_list_length.c
    src/token/token_list_get/token_list_get.c
    src/token/token_list_reverse/token_list_reverse.c
    src/token/token_list_free/token_list_free.c
    src/token/token_list_destroy/token_list_destroy.c
    src/token/token_to_string/token_to_string.c
    src/lexer/lexer_create/lexer_create.c
    src/lexer/lexer_free/lexer_free.c
    src/lexer/lexer_current_char/lexer_current_char.c
    src/lexer/lexer_advance/lexer_advance.c
    src/lexer/lexer_peek_char/lexer_peek_char.c
    src/lexer/lexer_skip_whitespace/lexer_skip_whitespace.c
    src/lexer/lexer_starts_with/lexer_starts_with.c
    src/lexer/lexer_extract_substring/lexer_extract_substring.c
    src/lexer/lexer_read_line/lexer_read_line.c
    src/lexer/lexer_read_html_comment/lexer_read_html_comment.c
    src/lexer/lexer_read_code_block/lexer_read_code_block.c
    src/lexer/lexer_read_variable_ref/lexer_read_variable_ref.c
    src/lexer/lexer_read_xmd_directive/lexer_read_xmd_directive.c
    src/lexer/lexer_read_text/lexer_read_text.c
    src/lexer/lexer_next_token/lexer_next_token.c
    src/lexer/lexer_peek_token/lexer_peek_token.c
    src/lexer/lexer_get_position/lexer_get_position.c
    src/lexer/lexer_get_line/lexer_get_line.c
    src/lexer/lexer_get_column/lexer_get_column.c
    src/lexer/lexer_at_end/lexer_at_end.c
    src/lexer/lexer_reset/lexer_reset.c
    src/utils/string/string_duplicate/string_duplicate.c
    src/utils/string/string_extract/string_extract.c
    src/utils/memory/memory_allocate/memory_allocate.c
    src/utils/memory/memory_free_safe/memory_free_safe.c
    src/variable/variable_create_null/variable_create_null.c
    src/variable/variable_create_boolean/variable_create_boolean.c
    src/variable/variable_create_number/variable_create_number.c
    src/variable/variable_create_string/variable_create_string.c
    src/variable/variable_create_array/variable_create_array.c
    src/variable/variable_create_object/variable_create_object.c
    src/variable/variable_ref/variable_ref.c
    src/variable/variable_unref/variable_unref.c
    src/variable/variable_get_type/variable_get_type.c
    src/variable/variable_to_boolean/variable_to_boolean.c
    src/variable/variable_to_number/variable_to_number.c
    src/variable/variable_to_string/variable_to_string.c
    src/variable/variable_equals/variable_equals.c
    src/variable/variable_copy/variable_copy.c
    src/variable/variable_array_add/variable_array_add.c
    src/variable/variable_array_get/variable_array_get.c
    src/variable/variable_array_set/variable_array_set.c
    src/variable/variable_array_size/variable_array_size.c
    src/variable/variable_object_set/variable_object_set.c
    src/variable/variable_object_get/variable_object_get.c
    src/variable/variable_object_remove/variable_object_remove.c
    src/variable/variable_object_size/variable_object_size.c
    src/variable/variable_object_keys/variable_object_keys.c
    src/variable/variable_array_length/variable_array_length.c
    src/variable/variable_new_array/variable_new_array.c
    src/variable/variable_convert/variable_convert.c
    src/variable/variable_extended/variable_extended.c
    src/store/store_entry_create/store_entry_create.c
    src/store/store_entry_destroy/store_entry_destroy.c
    src/store/store_resize/store_resize.c
    src/store/store_create/store_create.c
    src/store/store_destroy/store_destroy.c
    src/store/store_set/store_set.c
    src/store/store_get/store_get.c
    src/store/store_has/store_has.c
    src/store/store_remove/store_remove.c
    src/store/store_clear/store_clear.c
    src/store/store_size/store_size.c
    src/store/store_keys/store_keys.c
    src/store/store_ops/store_ops.c
    src/template/template_context_create/template_context_create.c
    src/template/template_context_destroy/template_context_destroy.c
    src/template/find_next_variable/find_next_variable.c
    src/template/extract_variable_name/extract_variable_name.c
    src/template/template_process/template_process.c
    src/template/template_extract_variables/template_extract_variables.c
    src/template/template_has_variables/template_has_variables.c
    src/template/template_validate/template_validate.c
    src/template/template_extract/template_extract.c
    src/conditional/condition/condition.c
    src/conditional/if_statement/if_statement.c
    src/loop/for_loop/for_loop.c
    src/flow/flow_control/flow_control.c
    src/error/error_handling/error_handling.c
    src/executor/executor/executor_context_new/executor_context_new.c
    src/executor/executor/executor_context_free/executor_context_free.c
    src/executor/executor/set_executor_error/set_executor_error.c
    src/executor/executor/get_time_ms/get_time_ms.c
    src/executor/executor/read_with_timeout/read_with_timeout.c
    src/executor/executor/parse_command_args/parse_command_args.c
    src/executor/executor/free_command_args/free_command_args.c
    src/executor/executor/executor_run_with_timeout/executor_run_with_timeout.c
    src/executor/executor/executor_run_command/executor_run_command.c
    src/executor/executor/command_result_free/command_result_free.c
    src/executor/executor_cross_platform/executor_cross_platform.c
    src/sandbox/sandbox_config_new/sandbox_config_new.c
    src/sandbox/sandbox_config_free/sandbox_config_free.c
    src/sandbox/sandbox_config_add_whitelist/sandbox_config_add_whitelist.c
    src/sandbox/sandbox_config_add_allowed_path/sandbox_config_add_allowed_path.c
    src/sandbox/sandbox_context_new/sandbox_context_new.c
    src/sandbox/sandbox_context_free/sandbox_context_free.c
    src/sandbox/extract_command_name/extract_command_name.c
    src/sandbox/sandbox_check_command_allowed/sandbox_check_command_allowed.c
    src/sandbox/sandbox_check_path_allowed/sandbox_check_path_allowed.c
    src/sandbox/sandbox_apply_limits/sandbox_apply_limits.c
    src/output/formatter/formatter.c
    src/resource/limiter/limiter.c
    src/resource/monitor/monitor.c
    src/module/module_new/module_new.c
    src/module/module_free/module_free.c
    src/module/module_load_content/module_load_content.c
    src/module/module_add_dependency/module_add_dependency.c
    src/module/module_export/module_export.c
    src/module/module_get_export/module_get_export.c
    src/module/module_registry_new/module_registry_new.c
    src/module/module_registry_free/module_registry_free.c
    src/module/module_registry_add_search_path/module_registry_add_search_path.c
    src/module/module_registry_register/module_registry_register.c
    src/module/module_registry_find/module_registry_find.c
    src/module/module_registry_load/module_registry_load.c
    src/module/file_exists/file_exists.c
    src/module/module_resolve_path/module_resolve_path.c
    src/import_export/import/import.c
    src/import_export/export/export.c
    src/dependency/graph/dependency_node_new/dependency_node_new.c
    src/dependency/graph/dependency_node_free/dependency_node_free.c
    src/dependency/graph/dependency_node_add_child/dependency_node_add_child.c
    src/dependency/graph/dependency_graph_new/dependency_graph_new.c
    src/dependency/graph/dependency_graph_free/dependency_graph_free.c
    src/dependency/graph/dependency_graph_add_module/dependency_graph_add_module.c
    src/dependency/graph/dependency_graph_find_node/dependency_graph_find_node.c
    src/dependency/graph/dependency_graph_add_dependency/dependency_graph_add_dependency.c
    src/dependency/graph/calculate_in_degrees/calculate_in_degrees.c
    src/dependency/graph/dependency_graph_topological_sort/dependency_graph_topological_sort.c
    src/dependency/graph/dependency_build_graph/dependency_build_graph.c
    src/dependency/detector/detector.c
    src/config/create_default_limits/create_default_limits.c
    src/config/create_default_buffers/create_default_buffers.c
    src/config/create_default_paths/create_default_paths.c
    src/config/create_default_security/create_default_security.c
    src/config/create_default_timing/create_default_timing.c
    src/config/create_default_precision/create_default_precision.c
    src/config/xmd_internal_config_new/xmd_internal_config_new.c
    src/config/free_paths_config/free_paths_config.c
    src/config/free_security_config/free_security_config.c
    src/config/xmd_internal_config_free/xmd_internal_config_free.c
    src/config/parse_env_size_t/parse_env_size_t.c
    src/config/parse_env_double/parse_env_double.c
    src/config/parse_env_bool/parse_env_bool.c
    src/config/xmd_internal_config_load_env/xmd_internal_config_load_env.c
    src/config/xmd_internal_config_load_file/xmd_internal_config_load_file.c
    src/config/xmd_internal_config_save_file/xmd_internal_config_save_file.c
    src/config/xmd_internal_config_get_global/xmd_internal_config_get_global.c
    src/config/xmd_internal_config_set_global/xmd_internal_config_set_global.c
    src/config/xmd_internal_config_add_module_path/xmd_internal_config_add_module_path.c
    src/config/xmd_internal_config_add_exec_whitelist/xmd_internal_config_add_exec_whitelist.c
    src/config/xmd_internal_config_set_exec_whitelist/xmd_internal_config_set_exec_whitelist.c
    src/config/xmd_internal_config_load_whitelist_env/xmd_internal_config_load_whitelist_env.c
    src/config/config_globals.c
    src/config/config/config.c
    src/utils/xmd_hash_key/xmd_hash_key.c
    src/utils/xmd_variable_to_number/xmd_variable_to_number.c
    src/utils/xmd_variable_equals/xmd_variable_equals.c
    src/utils/xmd_malloc/xmd_malloc.c
    src/utils/xmd_calloc/xmd_calloc.c
    src/utils/xmd_realloc/xmd_realloc.c
    src/utils/xmd_strdup/xmd_strdup.c
    src/utils/xmd_expand_array/xmd_expand_array.c
    src/utils/xmd_check_null/xmd_check_null.c
    src/utils/xmd_malloc_safe/xmd_malloc_safe.c
    src/security/validator/validator.c
    src/security/sanitizer/sanitizer.c
    
    # Security auditor files
    src/security/auditor/audit_state/audit_state.c
    src/security/auditor/get_timestamp_ms/get_timestamp_ms.c
    src/security/auditor/expand_entries_array/expand_entries_array.c
    src/security/auditor/write_audit_entry_to_file/write_audit_entry_to_file.c
    src/security/auditor/security_audit_init/security_audit_init.c
    src/security/auditor/security_audit_log/security_audit_log.c
    src/security/auditor/security_audit_get_entries/security_audit_get_entries.c
    src/security/auditor/security_audit_cleanup/security_audit_cleanup.c
    
    # Performance components
    src/performance/optimizer/optimizer_state/optimizer_state.c
    src/performance/optimizer/perf_optimizer_init/perf_optimizer_init.c
    src/performance/optimizer/should_apply_optimization/should_apply_optimization.c
    src/performance/optimizer/apply_constant_folding/apply_constant_folding.c
    src/performance/optimizer/apply_dead_code_elimination/apply_dead_code_elimination.c
    src/performance/optimizer/apply_common_subexpression_elimination/apply_common_subexpression_elimination.c
    src/performance/optimizer/apply_loop_unrolling/apply_loop_unrolling.c
    src/performance/optimizer/apply_inline_expansion/apply_inline_expansion.c
    src/performance/optimizer/perf_optimize_ast/perf_optimize_ast.c
    src/performance/optimizer/perf_optimizer_cleanup/perf_optimizer_cleanup.c
    src/performance/profiler/get_time_ns/get_time_ns.c
    src/performance/profiler/time_diff_ns/time_diff_ns.c
    src/performance/profiler/get_memory_usage/get_memory_usage.c
    src/performance/profiler/perf_profiler_create/perf_profiler_create.c
    src/performance/profiler/perf_profiler_start/perf_profiler_start.c
    src/performance/profiler/perf_profiler_stop/perf_profiler_stop.c
    src/performance/profiler/perf_profiler_record_alloc/perf_profiler_record_alloc.c
    src/performance/profiler/perf_profiler_record_dealloc/perf_profiler_record_dealloc.c
    src/performance/profiler/perf_profiler_record_cache_hit/perf_profiler_record_cache_hit.c
    src/performance/profiler/perf_profiler_record_cache_miss/perf_profiler_record_cache_miss.c
    src/performance/profiler/perf_profiler_get_metrics/perf_profiler_get_metrics.c
    src/performance/profiler/perf_profiler_generate_report/perf_profiler_generate_report.c
    src/performance/profiler/perf_profiler_destroy/perf_profiler_destroy.c
    src/performance/benchmark/benchmark.c
    
    # CLI components
    src/cli/cli/cli.c
    src/cli/parser/parser.c
    src/bindings/c_api/c_api.c
    
    # Documentation and Developer Tools
    src/docs/tutorial/tutorial.c
    src/docs/examples/examples.c
    src/docs/reference/reference.c
    src/devtools/debugger/debugger.c
    src/devtools/linter/linter.c
    src/devtools/formatter/formatter.c
    
    # Cross-platform compatibility layer
    src/platform/xmd_get_time/xmd_get_time.c
    src/platform/xmd_sleep_ms/xmd_sleep_ms.c
    src/platform/xmd_get_tick_count/xmd_get_tick_count.c
    src/platform/xmd_process_create/xmd_process_create.c
    src/platform/xmd_process_wait/xmd_process_wait.c
    src/platform/xmd_process_kill/xmd_process_kill.c
    src/platform/xmd_process_close/xmd_process_close.c
    src/platform/xmd_mutex_init/xmd_mutex_init.c
    src/platform/xmd_mutex_lock/xmd_mutex_lock.c
    src/platform/xmd_mutex_unlock/xmd_mutex_unlock.c
    src/platform/xmd_mutex_destroy/xmd_mutex_destroy.c
    src/platform/xmd_mkdir/xmd_mkdir.c
    src/platform/xmd_create_directory/xmd_create_directory.c
    src/platform/xmd_file_exists/xmd_file_exists.c
    src/platform/xmd_is_directory/xmd_is_directory.c
    src/platform/xmd_opendir/xmd_opendir.c
    src/platform/xmd_readdir/xmd_readdir.c
    src/platform/xmd_closedir/xmd_closedir.c
    src/platform/xmd_get_filename/xmd_get_filename.c
    src/platform/xmd_aligned_alloc/xmd_aligned_alloc.c
    src/platform/xmd_aligned_free/xmd_aligned_free.c
    src/platform/xmd_get_cpu_count/xmd_get_cpu_count.c
    src/platform/xmd_get_memory_size/xmd_get_memory_size.c
    src/platform/xmd_get_memory_usage/xmd_get_memory_usage.c
    src/platform/xmd_get_cpu_time/xmd_get_cpu_time.c
    src/platform/xmd_get_fd_count/xmd_get_fd_count.c
    
    # XMD directive processor (modular version)
    src/xmd_processor/context/create_context.c
    src/xmd_processor/context/should_execute_block.c
    src/xmd_processor/execution/execute_command.c
    src/xmd_processor/utilities/trim_whitespace.c
    src/xmd_processor/utilities/substitute_variables.c
    src/xmd_processor/utilities/evaluate_condition.c
    src/xmd_processor/utilities/is_multiline_directive.c
    src/xmd_processor/utilities/process_multiline_directive.c
    src/xmd_processor/utilities/process_multiline_directive_enhanced.c
    src/xmd_processor/utilities/parse_range.c
    src/xmd_processor/utilities/parse_collection.c
    src/xmd_processor/directives/process_exec.c
    src/xmd_processor/directives/process_set.c
    src/xmd_processor/directives/process_if.c
    src/xmd_processor/directives/process_elif.c
    src/xmd_processor/directives/process_else.c
    src/xmd_processor/directives/process_endif.c
    src/xmd_processor/directives/process_import.c
    src/xmd_processor/directives/process_for.c
    src/xmd_processor/directives/process_directive.c
    src/xmd_processor/api/process_xmd_content.c
    src/xmd_processor/api/process_xmd_content_enhanced.c
    src/xmd_processor/api/process_xmd_content_fixed.c
    src/xmd_processor/api/process_xmd_directive.c
    src/xmd_processor/api/process_text_with_directives.c
    src/xmd_processor/api/xmd_process_string.c
    src/xmd_processor/api/xmd_validate_syntax.c
    src/xmd_processor/api/xmd_error_string.c
    
    # Main module functions
    src/main/print_usage/print_usage.c
    src/main/print_version/print_version.c
    src/main/cleanup_cmd_variables/cleanup_cmd_variables.c
    src/main/format_output/format_output.c
    src/main/cmd_process/cmd_process.c
    src/main/cmd_validate/cmd_validate.c
    src/main/looks_like_file_path/looks_like_file_path.c
    src/main/convert_shorthand_to_process/convert_shorthand_to_process.c
    src/main/free_converted_argv/free_converted_argv.c
    
    # C API bindings functions
    src/bindings/c_api/preprocess_variables/preprocess_variables.c
    src/bindings/c_api/preprocess_for_loops/preprocess_for_loops.c
    src/bindings/c_api/evaluate_condition/evaluate_condition.c
    src/bindings/c_api/preprocess_if_statements/preprocess_if_statements.c
    src/bindings/c_api/create_result/create_result.c
    src/bindings/c_api/xmd_cleanup/xmd_cleanup.c
    src/bindings/c_api/xmd_get_version/xmd_get_version.c
    src/bindings/c_api/xmd_result_free/xmd_result_free.c
    src/bindings/c_api/xmd_init/xmd_init.c
    src/bindings/c_api/xmd_process_file/xmd_process_file.c
    src/bindings/c_api/xmd_validate/xmd_validate.c
    src/bindings/c_api/xmd_set_config/xmd_set_config.c
    src/bindings/c_api/xmd_get_config/xmd_get_config.c
    src/bindings/c_api/xmd_set_variable/xmd_set_variable.c
    src/bindings/c_api/xmd_get_variable/xmd_get_variable.c
    src/bindings/c_api/xmd_config_create_default/xmd_config_create_default.c
    src/bindings/c_api/xmd_config_free/xmd_config_free.c
    src/bindings/c_api/xmd_processor_create/xmd_processor_create.c
    src/bindings/c_api/xmd_processor_free/xmd_processor_free.c
    
    # Resource limiter files
    src/resource/limiter/resource_limiter_new/resource_limiter_new.c
    src/resource/limiter/resource_limiter_free/resource_limiter_free.c
    src/resource/limiter/set_limiter_error/set_limiter_error.c
    src/resource/limiter/resource_limiter_set_memory_limit/resource_limiter_set_memory_limit.c
    src/resource/limiter/resource_limiter_set_cpu_limit/resource_limiter_set_cpu_limit.c
    src/resource/limiter/resource_limiter_set_time_limit/resource_limiter_set_time_limit.c
    src/resource/limiter/resource_limiter_check_limits/resource_limiter_check_limits.c
    
    # Store operations files
    src/store/store_ops/store_has/store_has.c
    src/store/store_ops/store_remove/store_remove.c
    src/store/store_ops/store_clear/store_clear.c
    src/store/store_ops/store_size/store_size.c
    src/store/store_ops/store_keys/store_keys.c
    
    # CLI parser files
    src/cli/parser/parse_command_type/parse_command_type.c
    src/cli/parser/is_flag/is_flag.c
    src/cli/parser/cli_parse_args/cli_parse_args.c
    
    # Variable extended files
    src/variable/variable_extended/variable_get_boolean/variable_get_boolean.c
    src/variable/variable_extended/variable_get_number/variable_get_number.c
    src/variable/variable_extended/variable_get_string/variable_get_string.c
)

# Create static library
add_library(xmd_lib STATIC ${XMD_LIB_SOURCES})

# Platform-specific linking
if(XMD_PLATFORM_WINDOWS)
    # Windows-specific libraries
    target_link_libraries(xmd_lib psapi kernel32)
elseif(XMD_PLATFORM_APPLE)
    # macOS-specific libraries
    if(NOT XMD_PLATFORM_IOS)
        target_link_libraries(xmd_lib dl)
    endif()
elseif(XMD_PLATFORM_ANDROID)
    # Android-specific libraries
    target_link_libraries(xmd_lib m log)
else()
    # Linux and other Unix-like systems
    target_link_libraries(xmd_lib pthread dl m)
endif()

# Macro for consistent linking across platforms
macro(xmd_target_link_libraries target_name)
    if(XMD_PLATFORM_WINDOWS)
        target_link_libraries(${target_name} xmd_lib)
    elseif(XMD_PLATFORM_APPLE)
        if(XMD_PLATFORM_IOS)
            target_link_libraries(${target_name} xmd_lib)
        else()
            target_link_libraries(${target_name} xmd_lib dl)
        endif()
    elseif(XMD_PLATFORM_ANDROID)
        target_link_libraries(${target_name} xmd_lib m log)
    else()
        target_link_libraries(${target_name} xmd_lib pthread dl m)
    endif()
endmacro()

# Main executable
add_executable(xmd src/main.c)
xmd_target_link_libraries(xmd)

# Individual test executables for each component
add_executable(test_token_simple test/token/test_token_simple.c)
xmd_target_link_libraries(test_token_simple)

add_executable(test_lexer test/lexer/test_lexer.c)
xmd_target_link_libraries(test_lexer)


add_executable(test_string_duplicate test/utils/string/test_string_duplicate.c)
xmd_target_link_libraries(test_string_duplicate)

add_executable(test_string_extract test/utils/string/test_string_extract.c)
xmd_target_link_libraries(test_string_extract)

add_executable(test_memory_allocate test/utils/memory/test_memory_allocate.c)
xmd_target_link_libraries(test_memory_allocate)

add_executable(test_memory_free_safe test/utils/memory/test_memory_free_safe.c)
xmd_target_link_libraries(test_memory_free_safe)

add_executable(test_variable test/variable/test_variable.c)
xmd_target_link_libraries(test_variable)

add_executable(test_store test/store/test_store.c)
xmd_target_link_libraries(test_store)

add_executable(test_template test/template/test_template.c)
xmd_target_link_libraries(test_template)

# Control Flow tests
add_executable(test_conditional test/conditional/test_conditional_simple.c)
xmd_target_link_libraries(test_conditional)

add_executable(test_loop test/loop/test_loop_simple.c)
xmd_target_link_libraries(test_loop)

add_executable(test_flow test/flow/test_flow_simple.c)
xmd_target_link_libraries(test_flow)

add_executable(test_error test/error/test_error_simple.c)
xmd_target_link_libraries(test_error)

# Integration tests (phase tests removed as trash)

# Command Execution tests
add_executable(test_executor test/executor/test_executor.c)
xmd_target_link_libraries(test_executor)

add_executable(test_output test/output/test_output.c)
xmd_target_link_libraries(test_output)

add_executable(test_resource test/resource/test_resource.c)
xmd_target_link_libraries(test_resource)


# Module System tests
add_executable(test_module test/module/test_module.c)
xmd_target_link_libraries(test_module)

add_executable(test_import_export test/import_export/test_import_export.c)
xmd_target_link_libraries(test_import_export)

add_executable(test_dependency test/dependency/test_dependency.c)
xmd_target_link_libraries(test_dependency)


add_executable(test_security test/security/test_security.c)
xmd_target_link_libraries(test_security)

# Performance tests
add_executable(test_performance test/performance/test_performance.c)
xmd_target_link_libraries(test_performance)

# Performance and documentation integration tests removed (trash)

# CLI tests
add_executable(test_cli test/cli/test_cli.c)
xmd_target_link_libraries(test_cli)

# Documentation and Developer Tools tests
add_executable(test_docs test/docs/test_docs.c)
xmd_target_link_libraries(test_docs)

add_executable(test_devtools test/devtools/test_devtools.c)
xmd_target_link_libraries(test_devtools)

# XMD Processor comprehensive tests
add_executable(test_xmd_processor test/xmd_processor/test_xmd_processor.c)
xmd_target_link_libraries(test_xmd_processor)

# Main CLI executable
add_executable(xmd_cli src/main_cli.c)
xmd_target_link_libraries(xmd_cli)

# Enable testing
enable_testing()

# Add individual tests
add_test(NAME token_tests COMMAND test_token_simple)
add_test(NAME lexer_tests COMMAND test_lexer)
add_test(NAME string_duplicate_tests COMMAND test_string_duplicate)
add_test(NAME string_extract_tests COMMAND test_string_extract)
add_test(NAME memory_allocate_tests COMMAND test_memory_allocate)
add_test(NAME memory_free_safe_tests COMMAND test_memory_free_safe)
add_test(NAME variable_tests COMMAND test_variable)
add_test(NAME store_tests COMMAND test_store)
add_test(NAME template_tests COMMAND test_template)
add_test(NAME conditional_tests COMMAND test_conditional)
add_test(NAME loop_tests COMMAND test_loop)
add_test(NAME flow_tests COMMAND test_flow)
add_test(NAME error_tests COMMAND test_error)
add_test(NAME executor_tests COMMAND test_executor)
add_test(NAME output_tests COMMAND test_output)
add_test(NAME resource_tests COMMAND test_resource)
add_test(NAME module_tests COMMAND test_module)
add_test(NAME import_export_tests COMMAND test_import_export)
add_test(NAME dependency_tests COMMAND test_dependency)
add_test(NAME security_tests COMMAND test_security)
add_test(NAME performance_tests COMMAND test_performance)
add_test(NAME cli_tests COMMAND test_cli)
add_test(NAME docs_tests COMMAND test_docs)
add_test(NAME devtools_tests COMMAND test_devtools)
add_test(NAME xmd_processor_tests COMMAND test_xmd_processor)

# Custom target to run all tests
add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS test_token_simple test_lexer test_string_duplicate test_string_extract test_memory_allocate test_memory_free_safe test_variable test_store test_template test_conditional test_loop test_flow test_error test_executor test_output test_resource test_module test_import_export test_dependency test_security
)

# Coverage (optional)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Install targets
install(TARGETS xmd DESTINATION bin)

# Package information
set(CPACK_PACKAGE_NAME "xmd")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION "eXtended MarkDown - Programmable markdown processor")
set(CPACK_PACKAGE_CONTACT "dev@xmd.io")

include(CPack)