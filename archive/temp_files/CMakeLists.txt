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

# XMD Library Sources - CONSOLIDATED FILES ONLY (95% milestone cleanup)
# Use only consolidated files at src level, ignore original directories
set(XMD_LIB_SOURCES
    # AST module (refactored to hierarchical structure - Phase 3 complete)
    "src/ast/evaluator/assignment/ast_evaluate_assignment.c"
    "src/ast/evaluator/control/ast_evaluate_conditional.c"
    "src/ast/evaluator/expression/ast_evaluate_binary_op.c"
    "src/ast/evaluator/expression/ast_evaluate_identifier.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_delete.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_exists.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_list.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_read.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_write.c"
    "src/ast/evaluator/function/ast_evaluate_function_call.c"
    "src/ast/evaluator/function/ast_evaluate_function_def.c"
    "src/ast/evaluator/loop/ast_evaluate_loop.c"
    "src/ast/evaluator/loop/ast_evaluate_while_loop.c"
    "src/ast/evaluator/program/ast_evaluate_program_node.c"
    "src/ast/node/create/ast_create_array_access.c"
    "src/ast/node/create/ast_create_array_literal.c"
    "src/ast/node/create/ast_create_assignment.c"
    "src/ast/node/create/ast_create_binary_op.c"
    "src/ast/node/create/ast_create_block.c"
    "src/ast/node/create/ast_create_boolean_literal.c"
    "src/ast/node/create/ast_create_break_statement.c"
    "src/ast/node/create/ast_create_class_def.c"
    "src/ast/node/create/ast_create_conditional.c"
    "src/ast/node/create/ast_create_continue_statement.c"
    "src/ast/node/create/ast_create_function_call.c"
    "src/ast/node/create/ast_create_function_def.c"
    "src/ast/node/create/ast_create_identifier.c"
    "src/ast/node/create/ast_create_loop.c"
    "src/ast/node/create/ast_create_method_def.c"
    "src/ast/node/create/ast_create_number_literal.c"
    "src/ast/node/create/ast_create_program.c"
    "src/ast/node/create/ast_create_string_literal.c"
    "src/ast/node/free/ast_free.c"
    "src/ast/node/util/ast_add_argument.c"
    "src/ast/node/util/ast_add_element.c"
    "src/ast/node/util/ast_add_method.c"
    "src/ast/node/util/ast_add_parameter.c"
    "src/ast/node/util/ast_add_statement.c"
    "src/ast/parser/class/ast_parse_class.c"
    "src/ast/parser/class/ast_parse_method.c"
    "src/ast/parser/control/ast_parse_elif.c"
    "src/ast/parser/control/ast_parse_else.c"
    "src/ast/parser/control/ast_parse_if_block.c"
    "src/ast/parser/control/ast_parse_if_then.c"
    "src/ast/parser/expression/ast_parse_comparison_expression.c"
    "src/ast/parser/expression/ast_parse_expression.c"
    "src/ast/parser/expression/ast_parse_math_expression.c"
    "src/ast/parser/expression/ast_parse_primary.c"
    "src/ast/parser/function/ast_parse_function.c"
    "src/ast/parser/literal/ast_parse_array_assignment.c"
    "src/ast/parser/literal/ast_parse_number_literal.c"
    "src/ast/parser/literal/ast_parse_string_literal.c"
    "src/ast/parser/loop/ast_parse_loop.c"
    "src/ast/parser/loop/ast_parse_range_loop.c"
    "src/ast/parser/loop/ast_parse_while.c"
    "src/ast/parser/program/ast_parse_program.c"
    "src/ast/parser/statement/ast_parse_statement.c"
    "src/ast/value/ast_value_create_array.c"
    "src/ast/value/ast_value_create_boolean.c"
    "src/ast/value/ast_value_create_number.c"
    "src/ast/value/ast_value_create_string.c"
    "src/ast/value/ast_value_free.c"
    "src/ast/value/ast_value_from_variable.c"
    "src/ast/value/ast_value_to_string.c"
    "src/ast/value/ast_value_to_variable.c"
    "src/bindings_consolidated.c" 
    "src/config_consolidated.c"
    "src/devtools_consolidated.c"
    "src/docs_consolidated.c"
    "src/import_consolidated.c"
    "src/lexer_consolidated.c"
    "src/native_xmd_consolidated.c"
    "src/parsers_consolidated.c"
    "src/systems_consolidated.c"
    "src/performance.c"
    "src/platform.c"
    "src/resource.c"
    "src/security.c"
    # Token module (refactored to hierarchical structure)
    "src/token/convert/token_to_string.c"
    "src/token/create/token_create.c"
    "src/token/list/token_list_append.c"
    "src/token/list/token_list_destroy.c"
    "src/token/list/token_list_free.c"
    "src/token/list/token_list_get.c"
    "src/token/list/token_list_length.c"
    "src/token/list/token_list_reverse.c"
    "src/token/memory/token_free.c"
    "src/token/operations/token_copy.c"
    "src/token/operations/token_duplicate.c"
    "src/token/operations/token_equals.c"
    "src/token/operations/token_set_value.c"
    "src/token/type/token_type_is_valid.c"
    "src/token/type/token_type_to_string.c"
    "src/utils_consolidated.c"
    # Variable module (refactored to hierarchical structure)
    "src/variable/array/variable_array_add.c"
    "src/variable/array/variable_array_free.c"
    "src/variable/array/variable_array_get.c"
    "src/variable/array/variable_array_length.c"
    "src/variable/array/variable_array_set.c"
    "src/variable/array/variable_array_size.c"
    "src/variable/create/variable_create_array.c"
    "src/variable/create/variable_create_boolean.c"
    "src/variable/create/variable_create_null.c"
    "src/variable/create/variable_create_number.c"
    "src/variable/create/variable_create_object.c"
    "src/variable/create/variable_create_string.c"
    "src/variable/create/variable_new_array.c"
    "src/variable/memory/variable_ref.c"
    "src/variable/memory/variable_unref.c"
    "src/variable/object/variable_object_find_key.c"
    "src/variable/object/variable_object_free.c"
    "src/variable/object/variable_object_get.c"
    "src/variable/object/variable_object_keys.c"
    "src/variable/object/variable_object_remove.c"
    "src/variable/object/variable_object_set.c"
    "src/variable/object/variable_object_size.c"
    "src/variable/operations/variable_copy.c"
    "src/variable/operations/variable_equals.c"
    "src/variable/operations/variable_get_boolean.c"
    "src/variable/operations/variable_get_number.c"
    "src/variable/operations/variable_get_string.c"
    "src/variable/operations/variable_get_type.c"
    "src/variable/operations/variable_to_boolean.c"
    "src/variable/operations/variable_to_number.c"
    "src/variable/operations/variable_to_string.c"
    # Store module (refactored to hierarchical structure)
    "src/store/create/store_create.c"
    "src/store/memory/store_destroy.c"
    "src/store/operations/store_clear.c"
    "src/store/operations/store_get.c"
    "src/store/operations/store_has.c"
    "src/store/operations/store_keys.c"
    "src/store/operations/store_remove.c"
    "src/store/operations/store_set.c"
    "src/store/operations/store_size.c"
    # Misc functions from refactoring (includes AST support functions)
    "src/misc/ast_create_class_def.c"
    "src/misc/ast_create_directive.c"
    "src/misc/ast_create_file_delete.c"
    "src/misc/ast_create_file_exists.c"
    "src/misc/ast_create_file_list.c"
    "src/misc/ast_create_file_read.c"
    "src/misc/ast_create_file_write.c"
    "src/misc/ast_create_method_def.c"
    "src/misc/ast_create_return.c"
    "src/misc/ast_create_unary_op.c"
    "src/misc/ast_create_variable_ref.c"
    "src/misc/ast_evaluate.c"
    "src/misc/ast_evaluate_block.c"
    "src/misc/ast_evaluate_break.c"
    "src/misc/ast_evaluate_continue.c"
    "src/misc/ast_evaluator_create.c"
    "src/misc/ast_evaluator_free.c"
    "src/misc/ast_functions_cleanup.c"
    "src/misc/ast_functions_init.c"
    "src/misc/ast_parse_conditional.c"
    "src/misc/ast_parse_multiple_variables_handler.c"
    "src/misc/ast_parse_object_creation.c"
    "src/misc/ast_parse_potential_function_call.c"
    "src/misc/ast_parse_print.c"
    "src/misc/ast_parse_single_value.c"
    "src/misc/ast_substitute_variables.c"
    "src/misc/ast_value_array_add.c"
    "src/misc/hash_key.c"
    "src/misc/variable_convert.c"
    "src/misc/variable_extended.c"
    
    # Remaining core files (eliminating ALL single-file directories)
    "src/dependency.c"
    "src/parser_utils.c"
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
# add_executable(test_token_simple test/token/test_token.c)
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
# add_executable(test_conditional test/conditional/test_conditional.c)
# xmd_target_link_libraries(test_conditional)

# add_executable(test_loop test/loop/test_loop.c)
# xmd_target_link_libraries(test_loop)

# add_executable(test_flow test/flow/test_flow.c)
# xmd_target_link_libraries(test_flow)

# add_executable(test_error test/error/test_error.c)
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

