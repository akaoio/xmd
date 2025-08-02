cmake_minimum_required(VERSION 3.21)  # Minimum for reliable C17 support

# Get version from git tag
execute_process(
    COMMAND git describe --tags --abbrev=0
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE XMD_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

# Default if no tags
if(NOT XMD_VERSION)
    set(XMD_VERSION "0.0.0")
endif()

# Remove 'v' prefix if present
string(REPLACE "v" "" XMD_VERSION "${XMD_VERSION}")

project(xmd VERSION ${XMD_VERSION} LANGUAGES C)

# Version information
set(XMD_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(XMD_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(XMD_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(XMD_VERSION_STRING "${PROJECT_VERSION}")

# Get git information
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE XMD_GIT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

execute_process(
    COMMAND git describe --tags --exact-match
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE XMD_GIT_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE XMD_GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

# Get build date
string(TIMESTAMP XMD_BUILD_DATE "%Y-%m-%d %H:%M:%S")

# Generate version header
configure_file(
    "${CMAKE_SOURCE_DIR}/include/version_info.h.in"
    "${CMAKE_BINARY_DIR}/include/version_info.h"
    @ONLY
)

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
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG -flto")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")
endif()

# Include directories
include_directories(include)
include_directories(src)
include_directories(${CMAKE_BINARY_DIR}/include)  # For generated headers

# XMD Library Sources - MODULAR STRUCTURE (Genesis Principle: 1→1→1)
# Use modular structure following Genesis "1 function → 1 file → 1 directory"
set(XMD_LIB_SOURCES
    # AST module (refactored to hierarchical structure)
    "src/ast/ast_process_xmd_content.c"
    "src/ast/evaluator/assignment/ast_evaluate_assignment.c"
    "src/ast/evaluator/ast_evaluator_create/ast_evaluator_create.c"
    "src/ast/evaluator/ast_evaluator_free/ast_evaluator_free.c"
    "src/ast/evaluator/output/ast_evaluator_append_output.c"
    "src/ast/evaluator/misc/ast_evaluate/ast_evaluate.c"
    "src/ast/evaluator/misc/ast_evaluate_block/ast_evaluate_block.c"
    "src/ast/evaluator/control/ast_evaluate_conditional/ast_evaluate_conditional.c"
    "src/ast/evaluator/control/ast_evaluate_break/ast_evaluate_break.c"
    "src/ast/evaluator/control/ast_evaluate_continue/ast_evaluate_continue.c"
    "src/ast/evaluator/expression/ast_evaluate_binary_op/ast_evaluate_binary_op.c"
    "src/ast/evaluator/expression/ast_evaluate_identifier/ast_evaluate_identifier.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_delete/ast_evaluate_file_delete.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_exists/ast_evaluate_file_exists.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_list/ast_evaluate_file_list.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_read/ast_evaluate_file_read.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_write/ast_evaluate_file_write.c"
    "src/ast/evaluator/function/ast_evaluate_function_call/ast_evaluate_function_call.c"
    "src/ast/evaluator/function/ast_evaluate_function_def/ast_evaluate_function_def.c"
    "src/ast/functions/ast_functions_init/ast_functions_init.c"
    "src/ast/evaluator/loop/ast_evaluate_loop/ast_evaluate_loop.c"
    "src/ast/evaluator/loop/ast_evaluate_while_loop/ast_evaluate_while_loop.c"
    "src/ast/evaluator/program/ast_evaluate_program_node.c"
    "src/ast/evaluator/program/ast_evaluate_program/ast_evaluate_program.c"
    "src/ast/node/create/ast_create_array_access.c"
    # "src/ast/node/create/ast_create_literal/ast_create_literal.c"  # Type errors - revert to individual files  
    "src/ast/node/create/ast_create_array_literal/ast_create_array_literal.c"
    "src/ast/node/create/ast_create_boolean_literal/ast_create_boolean_literal.c"
    "src/ast/node/create/ast_create_assignment/ast_create_assignment.c"
    "src/ast/node/create/ast_create_binary_op/ast_create_binary_op.c"
    "src/ast/node/create/ast_create_block/ast_create_block.c"
    "src/ast/node/create/ast_create_break_statement/ast_create_break_statement.c"
    "src/ast/node/create/ast_create_conditional/ast_create_conditional.c"
    "src/ast/node/create/ast_create_continue_statement/ast_create_continue_statement.c"
    "src/ast/node/create/ast_create_function_call/ast_create_function_call.c"
    "src/ast/node/create/ast_create_function_def/ast_create_function_def.c"
    "src/ast/node/create/ast_create_identifier/ast_create_identifier.c"
    "src/ast/node/create/ast_create_class_def/ast_create_class_def.c"
    "src/ast/node/create/ast_create_method_def/ast_create_method_def.c"
    "src/ast/node/misc/ast_create_return/ast_create_return.c"
    "src/ast/node/create/ast_create_loop/ast_create_loop.c"
    "src/ast/node/create/ast_create_number_literal/ast_create_number_literal.c"
    "src/ast/node/create/ast_create_program/ast_create_program.c"
    "src/ast/node/create/ast_create_string_literal/ast_create_string_literal.c"
    "src/ast/node/free/ast_free.c"
    "src/ast/node/util/ast_add_argument/ast_add_argument.c"
    "src/ast/node/util/ast_add_element/ast_add_element.c"
    "src/ast/node/util/ast_add_method/ast_add_method.c"
    "src/ast/node/util/ast_add_parameter/ast_add_parameter.c"
    "src/ast/node/util/ast_add_statement/ast_add_statement.c"
    "src/ast/parser/class/ast_parse_class/ast_parse_class.c"
    "src/ast/parser/class/ast_parse_method/ast_parse_method.c"
    "src/ast/parser/control/ast_parse_elif/ast_parse_elif.c"
    "src/ast/parser/control/ast_parse_else/ast_parse_else.c"
    "src/ast/parser/control/ast_parse_if_block/ast_parse_if_block.c"
    "src/ast/parser/control/ast_parse_if_then/ast_parse_if_then.c"
    "src/ast/parser/expression/ast_parse_comparison_expression/ast_parse_comparison_expression.c"
    "src/ast/parser/expression/ast_parse_expression/ast_parse_expression.c"
    "src/ast/parser/expression/ast_parse_math_expression/ast_parse_math_expression.c"
    "src/ast/parser/expression/ast_parse_primary/ast_parse_primary.c"
    "src/ast/parser/function/ast_parse_function/ast_parse_function.c"
    "src/ast/parser/literal/ast_parse_array_assignment/ast_parse_array_assignment.c"
    "src/ast/parser/literal/ast_parse_number_literal/ast_parse_number_literal.c"
    "src/ast/parser/literal/ast_parse_string_literal/ast_parse_string_literal.c"
    "src/ast/parser/loop/ast_parse_loop/ast_parse_loop.c"
    "src/ast/parser/loop/ast_parse_range_loop/ast_parse_range_loop.c"
    "src/ast/parser/loop/ast_parse_while/ast_parse_while.c"
    "src/ast/parser/program/ast_parse_program.c"
    "src/ast/parser/statement/ast_parse_statement.c"
    "src/ast/parser/output/ast_parse_print.c"
    "src/ast/parser/variable/ast_parse_assignment/ast_parse_assignment.c"
    "src/ast/parser/function/ast_parse_potential_function_call/ast_parse_potential_function_call.c"
    "src/ast/value/ast_value_create_array/ast_value_create_array.c"
    "src/ast/value/ast_value_create_boolean/ast_value_create_boolean.c"
    "src/ast/value/ast_value_create_number/ast_value_create_number.c"
    "src/ast/value/ast_value_create_string/ast_value_create_string.c"
    "src/ast/value/ast_value_free/ast_value_free.c"
    "src/ast/value/ast_value_from_variable/ast_value_from_variable.c"
    "src/ast/value/ast_value_to_string/ast_value_to_string.c"
    "src/ast/value/ast_value_to_variable/ast_value_to_variable.c"
    "src/ast/value/misc/ast_value_array_add.c"
    "src/ast/substitution/ast_interpolate_string.c"
    "src/ast/json/json_functions.c"
    "src/ast/yaml/yaml_functions.c"
    # Bindings module (fully refactored to hierarchical c_api structure) - TEAM COLLABORATION
    "src/bindings/c_api/initialization/xmd_init/xmd_init.c"
    "src/bindings/c_api/initialization/c_api_xmd_init/c_api_xmd_init.c"
    "src/bindings/c_api/initialization/c_api_xmd_cleanup/c_api_xmd_cleanup.c"
    "src/bindings/c_api/configuration/xmd_config_create_default/xmd_config_create_default.c"
    "src/bindings/c_api/configuration/xmd_config_free/xmd_config_free.c"
    "src/bindings/c_api/variables/xmd_set_variable/xmd_set_variable.c"
    "src/bindings/c_api/variables/xmd_get_variable/xmd_get_variable.c"
    "src/bindings/c_api/processor/xmd_processor_create/xmd_processor_create.c"
    "src/bindings/c_api/processor/xmd_processor_free/xmd_processor_free.c"
    "src/bindings/c_api/processing/xmd_process_file/xmd_process_file.c"
    "src/bindings/c_api/processing/xmd_process_string/xmd_process_string.c"
    "src/bindings/c_api/processing/xmd_process_string_api/xmd_process_string_api.c"
    "src/bindings/c_api/results/c_api_create_result/c_api_create_result.c"
    "src/bindings/c_api/results/xmd_result_free/xmd_result_free.c"
    "src/bindings/c_api/version/bindings_get_version/bindings_get_version.c"
    "src/bindings/c_api/version/xmd_get_version/xmd_get_version.c"
    # Config module (real implementation from backup)
    "src/config/create/config_create/config_create.c"
    "src/config/create/config_destroy/config_destroy.c"
    "src/config/create/create_default_limits/create_default_limits.c"
    "src/config/create/create_default_buffers/create_default_buffers.c"
    "src/config/create/create_default_paths/create_default_paths.c"
    "src/config/create/create_default_precision/create_default_precision.c"
    "src/config/create/create_default_security/create_default_security.c"
    "src/config/create/create_default_timing/create_default_timing.c"
    # All consolidated files have been successfully refactored to modular structure!
    # Performance module (refactored to Genesis hierarchical structure - 15 functions)
    "src/performance/timing/get_time_ns.c"
    "src/performance/benchmark/benchmark_run/benchmark_run.c"
    "src/performance/benchmark/benchmark_generate_report/benchmark_generate_report.c"
    "src/performance/benchmark/benchmark_suite_destroy/benchmark_suite_destroy.c"
    "src/performance/profiler/perf_profiler_create/perf_profiler_create.c"
    "src/performance/profiler/perf_profiler_start/perf_profiler_start.c"
    "src/performance/profiler/perf_profiler_stop/perf_profiler_stop.c"
    "src/performance/profiler/perf_profiler_record_alloc/perf_profiler_record_alloc.c"
    "src/performance/profiler/perf_profiler_record_dealloc/perf_profiler_record_dealloc.c"
    "src/performance/profiler/perf_profiler_record_cache_hit/perf_profiler_record_cache_hit.c"
    "src/performance/profiler/perf_profiler_record_cache_miss/perf_profiler_record_cache_miss.c"
    "src/performance/profiler/perf_profiler_generate_report/perf_profiler_generate_report.c"
    "src/performance/profiler/perf_profiler_destroy/perf_profiler_destroy.c"
    "src/performance/profiler/perf_profiler_get_metrics/perf_profiler_get_metrics.c"
    "src/performance/metrics/calculate_stats/calculate_stats.c"
    "src/performance/metrics/compare_times/compare_times.c"
    # Platform module (refactored to Genesis hierarchical structure - 26 functions)
    "src/platform/time/xmd_get_time.c"
    "src/platform/filesystem/xmd_file_exists/xmd_file_exists.c"
    "src/platform/filesystem/xmd_mkdir/xmd_mkdir.c"
    "src/platform/filesystem/xmd_is_directory/xmd_is_directory.c"
    "src/platform/filesystem/xmd_create_directory/xmd_create_directory.c"
    "src/platform/memory/xmd_aligned_alloc/xmd_aligned_alloc.c"
    "src/platform/memory/xmd_aligned_free/xmd_aligned_free.c"
    "src/platform/memory/xmd_get_memory_size/xmd_get_memory_size.c"
    "src/platform/memory/xmd_get_memory_usage/xmd_get_memory_usage.c"
    "src/platform/directory/xmd_opendir/xmd_opendir.c"
    "src/platform/directory/xmd_readdir/xmd_readdir.c"
    "src/platform/directory/xmd_closedir/xmd_closedir.c"
    "src/platform/process/xmd_process_create/xmd_process_create.c"
    "src/platform/process/xmd_process_wait/xmd_process_wait.c"
    "src/platform/process/xmd_process_kill/xmd_process_kill.c"
    "src/platform/process/xmd_process_close/xmd_process_close.c"
    "src/platform/threading/xmd_mutex_init/xmd_mutex_init.c"
    "src/platform/threading/xmd_mutex_lock/xmd_mutex_lock.c"
    "src/platform/threading/xmd_mutex_unlock/xmd_mutex_unlock.c"
    "src/platform/threading/xmd_mutex_destroy/xmd_mutex_destroy.c"
    "src/platform/system/xmd_sleep_ms/xmd_sleep_ms.c"
    "src/platform/system/xmd_get_cpu_count/xmd_get_cpu_count.c"
    "src/platform/system/xmd_get_cpu_time/xmd_get_cpu_time.c"
    "src/platform/system/xmd_get_fd_count/xmd_get_fd_count.c"
    "src/platform/system/xmd_get_tick_count/xmd_get_tick_count.c"
    "src/platform/path/xmd_get_filename.c"
    # Resource module (refactored to Genesis hierarchical structure - 16 functions)
    "src/resource/utils/get_elapsed_time_ms/get_elapsed_time_ms.c"
    "src/resource/utils/get_memory_usage/get_memory_usage.c"
    "src/resource/utils/count_file_descriptors/count_file_descriptors.c"
    "src/resource/utils/set_limiter_error/set_limiter_error.c"
    "src/resource/utils/set_monitor_error/set_monitor_error.c"
    "src/resource/limiter/resource_limiter_new/resource_limiter_new.c"
    "src/resource/limiter/resource_limiter_free/resource_limiter_free.c"
    "src/resource/limiter/resource_limiter_set_memory_limit/resource_limiter_set_memory_limit.c"
    "src/resource/limiter/resource_limiter_set_cpu_limit/resource_limiter_set_cpu_limit.c"
    "src/resource/limiter/resource_limiter_set_time_limit/resource_limiter_set_time_limit.c"
    "src/resource/limiter/resource_limiter_check_limits/resource_limiter_check_limits.c"
    "src/resource/monitor/resource_monitor_start/resource_monitor_start.c"
    "src/resource/monitor/resource_monitor_stop/resource_monitor_stop.c"
    "src/resource/monitor/resource_monitor_reset/resource_monitor_reset.c"
    "src/resource/monitor/resource_monitor_get_usage/resource_monitor_get_usage.c"
    "src/resource/monitor/resource_monitor_free/resource_monitor_free.c"
    # Security module (now properly modularized following Genesis principle)
    "src/security/audit/security_audit_init/security_audit_init.c"
    "src/security/audit/security_audit_log/security_audit_log.c"
    "src/security/audit/security_audit_get_entries/security_audit_get_entries.c"
    "src/security/audit/security_audit_cleanup/security_audit_cleanup.c"
    "src/security/validation/security_validate_command.c"
    "src/security/sanitization/security_sanitize_command_output/security_sanitize_command_output.c"
    "src/security/sanitization/security_sanitize_output/security_sanitize_output.c"
    "src/security/sanitization/security_sanitize_html/security_sanitize_html.c"
    "src/security/sandbox/security_sandbox_init/security_sandbox_init.c"
    "src/security/sandbox/security_sandbox_execute/security_sandbox_execute.c"
    "src/security/sandbox/security_sandbox_cleanup/security_sandbox_cleanup.c"
    "src/security/utilities/is_safe_html_tag/is_safe_html_tag.c"
    "src/security/utilities/extract_tag_name/extract_tag_name.c"
    "src/security/utilities/process_html_tag/process_html_tag.c"
    "src/security/utilities/remove_ansi_codes/remove_ansi_codes.c"
    # Token module (refactored to hierarchical structure)
    "src/token/convert/token_to_string.c"
    "src/token/create/token_create.c"
    "src/token/list/token_list_append/token_list_append.c"
    "src/token/list/token_list_destroy/token_list_destroy.c"
    "src/token/list/token_list_free/token_list_free.c"
    "src/token/list/token_list_get/token_list_get.c"
    "src/token/list/token_list_length/token_list_length.c"
    "src/token/list/token_list_reverse/token_list_reverse.c"
    "src/token/memory/token_free.c"
    "src/token/operations/token_copy/token_copy.c"
    "src/token/operations/token_duplicate/token_duplicate.c"
    "src/token/operations/token_equals/token_equals.c"
    "src/token/operations/token_set_value/token_set_value.c"
    "src/token/type/token_type_is_valid/token_type_is_valid.c"
    "src/token/type/token_type_to_string/token_type_to_string.c"
    # Utils module (refactored to Genesis hierarchical structure)
    "src/utils/memory/xmd_malloc/xmd_malloc.c"
    "src/utils/memory/xmd_calloc/xmd_calloc.c"
    "src/utils/memory/xmd_realloc/xmd_realloc.c"
    "src/utils/memory/xmd_free/xmd_free.c"
    "src/utils/memory/memory_free_safe/memory_free_safe.c"
    "src/utils/hash/xmd_hash_key/xmd_hash_key.c"
    "src/utils/hash/hash_string/hash_string.c"
    "src/utils/misc/xmd_check_null/xmd_check_null.c"
    "src/utils/misc/xmd_expand_array/xmd_expand_array.c"
    "src/utils/string/xmd_strdup/xmd_strdup.c"
    "src/utils/string/string_extract/string_extract.c"
    "src/utils/string/xmd_strcpy_safe/xmd_strcpy_safe.c"
    "src/utils/string/xmd_strcat_safe/xmd_strcat_safe.c"
    "src/utils/string/xmd_strtrim/xmd_strtrim.c"
    # Variable module (refactored to hierarchical structure)
    "src/variable/array/variable_array_add/variable_array_add.c"
    "src/variable/array/variable_array_free/variable_array_free.c"
    "src/variable/array/variable_array_get/variable_array_get.c"
    "src/variable/array/variable_array_length/variable_array_length.c"
    "src/variable/array/variable_array_set/variable_array_set.c"
    "src/variable/array/variable_array_size/variable_array_size.c"
    "src/variable/create/variable_create_array/variable_create_array.c"
    "src/variable/create/variable_create_boolean/variable_create_boolean.c" 
    "src/variable/create/variable_create_null/variable_create_null.c"
    "src/variable/create/variable_create_number/variable_create_number.c"
    "src/variable/create/variable_create_object/variable_create_object.c"
    "src/variable/create/variable_create_string/variable_create_string.c"
    "src/variable/create/variable_new_array/variable_new_array.c"
    "src/variable/memory/variable_ref/variable_ref.c"
    "src/variable/memory/variable_unref/variable_unref.c"
    "src/variable/object/variable_object_find_key/variable_object_find_key.c"
    "src/variable/object/variable_object_free/variable_object_free.c"
    "src/variable/object/variable_object_get/variable_object_get.c"
    "src/variable/object/variable_object_keys/variable_object_keys.c"
    "src/variable/object/variable_object_remove/variable_object_remove.c"
    "src/variable/object/variable_object_set/variable_object_set.c"
    "src/variable/object/variable_object_size/variable_object_size.c"
    "src/variable/operations/variable_copy/variable_copy.c"
    "src/variable/operations/variable_equals/variable_equals.c"
    "src/variable/operations/variable_get_boolean/variable_get_boolean.c"
    "src/variable/operations/variable_get_number/variable_get_number.c"
    "src/variable/operations/variable_get_string/variable_get_string.c"
    "src/variable/operations/variable_get_type/variable_get_type.c"
    "src/variable/operations/variable_to_boolean/variable_to_boolean.c"
    "src/variable/operations/variable_to_number/variable_to_number.c"
    "src/variable/operations/variable_to_string/variable_to_string.c"
    # Store module (refactored to hierarchical structure)
    "src/store/create/store_create.c"
    "src/store/memory/store_destroy.c"
    "src/store/operations/store_clear/store_clear.c"
    "src/store/operations/store_get/store_get.c"
    "src/store/operations/store_has/store_has.c"
    "src/store/operations/store_keys/store_keys.c"
    "src/store/operations/store_remove/store_remove.c"
    "src/store/operations/store_set/store_set.c"
    "src/store/operations/store_size/store_size.c"
    # Misc functions from refactoring
    # Misc module temporarily disabled - files moved to proper Genesis locations
    
    # Dependency module (refactored to Genesis hierarchical structure - 16 functions)
    "src/dependency/detection/dependency_check_circular/dependency_check_circular.c"
    "src/dependency/detection/dependency_check_circular_from/dependency_check_circular_from.c"
    "src/dependency/detection/dependency_detector_new/dependency_detector_new.c"
    "src/dependency/detection/dependency_detector_free/dependency_detector_free.c"
    "src/dependency/graph/dependency_graph_new/dependency_graph_new.c"
    "src/dependency/graph/dependency_graph_free/dependency_graph_free.c"
    "src/dependency/graph/dependency_graph_find_node/dependency_graph_find_node.c"
    "src/dependency/graph/dependency_graph_add_module/dependency_graph_add_module.c"
    "src/dependency/graph/dependency_graph_add_dependency/dependency_graph_add_dependency.c"
    "src/dependency/graph/dependency_graph_topological_sort/dependency_graph_topological_sort.c"
    "src/dependency/graph/dependency_node_new/dependency_node_new.c"
    "src/dependency/graph/dependency_node_free/dependency_node_free.c"
    "src/dependency/graph/dependency_node_add_child/dependency_node_add_child.c"
    "src/dependency/validation/dependency_validate_all.c"
    "src/dependency/utilities/reset_visit_states/reset_visit_states.c"
    "src/dependency/utilities/calculate_in_degrees/calculate_in_degrees.c"
    # "src/parser_utils.c"  # Moved to Genesis structure
    
    # Native XMD system
    "src/misc/native_xmd_dispatch.c"
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

# Create portable binary with static linking where possible
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Static link as much as possible for portability
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBS OFF)
    
    if(APPLE)
        # macOS: static libgcc only
        set_target_properties(xmd PROPERTIES LINK_FLAGS "-static-libgcc")
    elseif(ANDROID)
        # Android: static libgcc and strip for smaller size
        set_target_properties(xmd PROPERTIES 
            LINK_FLAGS "-static-libgcc -s"
        )
    else()
        # Linux: fully static binary
        set_target_properties(xmd PROPERTIES 
            LINK_FLAGS "-static -static-libgcc"
        )
    endif()
    
    # Strip debug symbols for smaller binary
    add_custom_command(TARGET xmd POST_BUILD
        COMMAND strip $<TARGET_FILE:xmd>
        COMMENT "Stripping debug symbols from xmd"
    )
else()
    # Debug builds: keep dynamic linking for easier debugging
    if(NOT ANDROID)
        set_target_properties(xmd PROPERTIES LINK_FLAGS "-static-libgcc")
    endif()
endif()
target_link_libraries(xmd xmd_lib)

# Individual test executables for each component
# DEPRECATED: Transitioning to XMD-based self-testing
# add_executable(test_token_simple test/token/test_token_simple.c)
# xmd_target_link_libraries(test_token_simple)

# add_executable(test_lexer test/lexer/test_lexer.c)
# xmd_target_link_libraries(test_lexer)


# add_executable(test_string_duplicate test/utils/string/test_string_duplicate.c)
# xmd_target_link_libraries(test_string_duplicate)

# add_executable(test_string_extract test/utils/string/test_string_extract.c)
# xmd_target_link_libraries(test_string_extract)

# add_executable(test_memory_allocate test/utils/memory/test_memory_allocate.c)
# xmd_target_link_libraries(test_memory_allocate)

# add_executable(test_memory_free_safe test/utils/memory/test_memory_free_safe.c)
# xmd_target_link_libraries(test_memory_free_safe)

# add_executable(test_variable test/variable/test_variable.c)
# xmd_target_link_libraries(test_variable)

# add_executable(test_store test/store/test_store.c)
# xmd_target_link_libraries(test_store)

# add_executable(test_template test/template/test_template.c)
# xmd_target_link_libraries(test_template)

# Control Flow tests
# add_executable(test_conditional test/conditional/test_conditional_simple.c)
# xmd_target_link_libraries(test_conditional)

# add_executable(test_loop test/loop/test_loop_simple.c)
# xmd_target_link_libraries(test_loop)

# add_executable(test_flow test/flow/test_flow_simple.c)
# xmd_target_link_libraries(test_flow)

# add_executable(test_error test/error/test_error_simple.c)
# xmd_target_link_libraries(test_error)

# Integration tests (phase tests removed as trash)

# Command Execution tests
# add_executable(test_executor test/executor/test_executor.c)
# xmd_target_link_libraries(test_executor)

# add_executable(test_long_output test/executor/test_long_output.c)
# xmd_target_link_libraries(test_long_output)

# add_executable(test_output test/output/test_output.c)
# xmd_target_link_libraries(test_output)

# add_executable(test_resource test/resource/test_resource.c)
# xmd_target_link_libraries(test_resource)


# Module System tests
# add_executable(test_module test/module/test_module.c)
# xmd_target_link_libraries(test_module)

# add_executable(test_import_export test/import_export/test_import_export.c)
# xmd_target_link_libraries(test_import_export)

# add_executable(test_import_xmd_nested test/import/test_import_xmd_nested.c)
# xmd_target_link_libraries(test_import_xmd_nested)

# add_executable(test_import_edge_cases test/import/test_import_edge_cases.c)
# xmd_target_link_libraries(test_import_edge_cases)

# add_executable(test_dependency test/dependency/test_dependency.c)
# xmd_target_link_libraries(test_dependency)


# Re-enabled previously failing tests
# add_executable(test_security test/security/test_security.c)
# xmd_target_link_libraries(test_security)

# add_executable(test_performance test/performance/test_performance.c)
# xmd_target_link_libraries(test_performance)

# add_executable(test_real_performance test/performance/test_real_performance.c)
# xmd_target_link_libraries(test_real_performance)

# add_executable(test_cli test/cli/test_cli.c)
# xmd_target_link_libraries(test_cli)

# add_executable(test_upgrade_version test/cli/test_upgrade_version.c)
# xmd_target_link_libraries(test_upgrade_version)

# add_executable(test_docs test/docs/test_docs.c)
# xmd_target_link_libraries(test_docs)

# add_executable(test_devtools test/devtools/test_devtools.c)
# xmd_target_link_libraries(test_devtools)

# add_executable(test_xmd_processor test/xmd_processor/test_xmd_processor.c)
# xmd_target_link_libraries(test_xmd_processor)

# add_executable(test_truncate_fix test/xmd_processor/test_truncate_fix.c)
# xmd_target_link_libraries(test_truncate_fix)

# Advanced scripting tests
# add_executable(test_advanced_scripting test/xmd_processor/test_advanced_scripting.c)
# xmd_target_link_libraries(test_advanced_scripting)

# add_executable(test_variable_advanced test/variable/test_variable_advanced.c)
# xmd_target_link_libraries(test_variable_advanced)

# add_executable(test_multiline_enhanced test/xmd_processor/test_multiline_enhanced.c)
# xmd_target_link_libraries(test_multiline_enhanced)

# add_executable(test_advanced_integration test/integration/test_advanced_integration.c)
# xmd_target_link_libraries(test_advanced_integration)

# Stress tests (brutal panic battle tests)
# add_executable(test_brutal_nesting test/stress/test_brutal_nesting.c)
# xmd_target_link_libraries(test_brutal_nesting)

# add_executable(test_resource_exhaustion test/stress/test_resource_exhaustion.c)
# xmd_target_link_libraries(test_resource_exhaustion)

# Integration tests
# add_executable(test_c_api_integration test/integration/test_c_api_integration.c)
# xmd_target_link_libraries(test_c_api_integration)

# End-to-end tests
# add_executable(test_cli_e2e test/e2e/test_cli_e2e.c)
# xmd_target_link_libraries(test_cli_e2e)

# Security tests
# add_executable(test_sandbox test/security/test_sandbox.c)
# xmd_target_link_libraries(test_sandbox)

# AST system tests
# add_executable(test_ast_node test/test_ast_node.c)
# xmd_target_link_libraries(test_ast_node)

# add_executable(test_lexer_enhanced test/test_lexer_enhanced.c)
# xmd_target_link_libraries(test_lexer_enhanced)

# add_executable(test_lexer_escape_fix test/test_lexer_escape_fix.c)
# xmd_target_link_libraries(test_lexer_escape_fix)

# add_executable(test_ast_parser test/test_ast_parser.c)
# xmd_target_link_libraries(test_ast_parser)

# add_executable(test_function_calls test/function/test_function_calls.c)
# xmd_target_link_libraries(test_function_calls)

# add_executable(test_array_evaluation test/function/test_array_evaluation.c)
# xmd_target_link_libraries(test_array_evaluation)

# Enable testing
# DEPRECATED: Transitioning to XMD-based self-testing
# enable_testing()

# Add individual tests
# add_test(NAME token_tests COMMAND test_token_simple)
# add_test(NAME lexer_tests COMMAND test_lexer)
# add_test(NAME string_duplicate_tests COMMAND test_string_duplicate)
# add_test(NAME string_extract_tests COMMAND test_string_extract)
# add_test(NAME memory_allocate_tests COMMAND test_memory_allocate)
# add_test(NAME memory_free_safe_tests COMMAND test_memory_free_safe)
# add_test(NAME variable_tests COMMAND test_variable)
# add_test(NAME store_tests COMMAND test_store)
# add_test(NAME template_tests COMMAND test_template)
# add_test(NAME conditional_tests COMMAND test_conditional)
# add_test(NAME loop_tests COMMAND test_loop)
# add_test(NAME flow_tests COMMAND test_flow)
# add_test(NAME error_tests COMMAND test_error)
# add_test(NAME executor_tests COMMAND test_executor)
# add_test(NAME long_output_tests COMMAND test_long_output)
# add_test(NAME output_tests COMMAND test_output)
# add_test(NAME resource_tests COMMAND test_resource)
# add_test(NAME module_tests COMMAND test_module)
# add_test(NAME import_export_tests COMMAND test_import_export)
# add_test(NAME import_xmd_nested_tests COMMAND test_import_xmd_nested)
# add_test(NAME import_edge_cases_tests COMMAND test_import_edge_cases)
# add_test(NAME dependency_tests COMMAND test_dependency)
# Re-enabled previously failing tests
# add_test(NAME security_tests COMMAND test_security)
# add_test(NAME performance_tests COMMAND test_performance)
# add_test(NAME real_performance_tests COMMAND test_real_performance)
# add_test(NAME cli_tests COMMAND test_cli)
# add_test(NAME upgrade_version_tests COMMAND test_upgrade_version)
# add_test(NAME docs_tests COMMAND test_docs)
# add_test(NAME devtools_tests COMMAND test_devtools)
# add_test(NAME xmd_processor_tests COMMAND test_xmd_processor)
# add_test(NAME truncate_fix_tests COMMAND test_truncate_fix)
# add_test(NAME advanced_scripting_tests COMMAND test_advanced_scripting)
# set_tests_properties(advanced_scripting_tests PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
# add_test(NAME variable_advanced_tests COMMAND test_variable_advanced)
# add_test(NAME multiline_enhanced_tests COMMAND test_multiline_enhanced)
# set_tests_properties(multiline_enhanced_tests PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
# add_test(NAME advanced_integration_tests COMMAND test_advanced_integration)
# set_tests_properties(advanced_integration_tests PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Stress tests - now included in main test suite per INSTRUCTIONS.md Rule 17
# add_test(NAME brutal_nesting_tests COMMAND test_brutal_nesting)
# add_test(NAME resource_exhaustion_tests COMMAND test_resource_exhaustion)

# Integration tests
# add_test(NAME c_api_integration_tests COMMAND test_c_api_integration)

# End-to-end tests
# add_test(NAME cli_e2e_tests COMMAND test_cli_e2e)

# Security tests
# add_test(NAME sandbox_tests COMMAND test_sandbox)

# AST system tests
# add_test(NAME ast_node_tests COMMAND test_ast_node)
# add_test(NAME lexer_enhanced_tests COMMAND test_lexer_enhanced)
# add_test(NAME lexer_escape_fix_tests COMMAND test_lexer_escape_fix)
# add_test(NAME ast_parser_tests COMMAND test_ast_parser)
# add_test(NAME function_call_tests COMMAND test_function_calls)
# add_test(NAME array_evaluation_tests COMMAND test_array_evaluation)

# Custom target to run all tests
# add_custom_target(test_all
#     COMMAND ${CMAKE_CTEST_COMMAND} --verbose
#     DEPENDS test_token_simple test_lexer test_string_duplicate test_string_extract test_memory_allocate test_memory_free_safe test_variable test_store test_template test_conditional test_loop test_flow test_error test_executor test_long_output test_output test_resource test_module test_import_export test_dependency test_security test_performance test_cli test_upgrade_version test_docs test_devtools test_xmd_processor test_truncate_fix test_advanced_scripting test_variable_advanced test_multiline_enhanced test_advanced_integration test_brutal_nesting test_resource_exhaustion test_c_api_integration test_cli_e2e test_sandbox test_ast_node test_lexer_enhanced test_lexer_escape_fix test_ast_parser test_function_calls test_array_evaluation
# )

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

