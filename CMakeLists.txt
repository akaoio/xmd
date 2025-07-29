cmake_minimum_required(VERSION 3.21)  # Minimum for reliable C17 support
project(xmd VERSION 0.0.2 LANGUAGES C)

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
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

# Include directories
include_directories(include)
include_directories(src)
include_directories(${CMAKE_BINARY_DIR}/include)  # For generated headers

# XMD Library Sources - dynamically find all C files
file(GLOB_RECURSE XMD_LIB_SOURCES "src/*.c")

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
target_link_libraries(xmd xmd_lib)

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

add_executable(test_long_output test/executor/test_long_output.c)
xmd_target_link_libraries(test_long_output)

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


# Re-enabled previously failing tests
add_executable(test_security test/security/test_security.c)
xmd_target_link_libraries(test_security)

add_executable(test_performance test/performance/test_performance.c)
xmd_target_link_libraries(test_performance)

add_executable(test_real_performance test/performance/test_real_performance.c)
xmd_target_link_libraries(test_real_performance)

add_executable(test_cli test/cli/test_cli.c)
xmd_target_link_libraries(test_cli)

add_executable(test_upgrade_version test/cli/test_upgrade_version.c)
xmd_target_link_libraries(test_upgrade_version)

add_executable(test_docs test/docs/test_docs.c)
xmd_target_link_libraries(test_docs)

add_executable(test_devtools test/devtools/test_devtools.c)
xmd_target_link_libraries(test_devtools)

add_executable(test_xmd_processor test/xmd_processor/test_xmd_processor.c)
xmd_target_link_libraries(test_xmd_processor)

add_executable(test_truncate_fix test/xmd_processor/test_truncate_fix.c)
xmd_target_link_libraries(test_truncate_fix)

# Advanced scripting tests
add_executable(test_advanced_scripting test/xmd_processor/test_advanced_scripting.c)
xmd_target_link_libraries(test_advanced_scripting)

add_executable(test_variable_advanced test/variable/test_variable_advanced.c)
xmd_target_link_libraries(test_variable_advanced)

add_executable(test_multiline_enhanced test/xmd_processor/test_multiline_enhanced.c)
xmd_target_link_libraries(test_multiline_enhanced)

add_executable(test_advanced_integration test/integration/test_advanced_integration.c)
xmd_target_link_libraries(test_advanced_integration)

# Stress tests (brutal panic battle tests)
add_executable(test_brutal_nesting test/stress/test_brutal_nesting.c)
xmd_target_link_libraries(test_brutal_nesting)

add_executable(test_resource_exhaustion test/stress/test_resource_exhaustion.c)
xmd_target_link_libraries(test_resource_exhaustion)

# Integration tests
add_executable(test_c_api_integration test/integration/test_c_api_integration.c)
xmd_target_link_libraries(test_c_api_integration)

# End-to-end tests
add_executable(test_cli_e2e test/e2e/test_cli_e2e.c)
xmd_target_link_libraries(test_cli_e2e)

# Security tests
add_executable(test_sandbox test/security/test_sandbox.c)
xmd_target_link_libraries(test_sandbox)

# AST system tests
add_executable(test_ast_node test/test_ast_node.c)
xmd_target_link_libraries(test_ast_node)

add_executable(test_lexer_enhanced test/test_lexer_enhanced.c)
xmd_target_link_libraries(test_lexer_enhanced)

add_executable(test_lexer_escape_fix test/test_lexer_escape_fix.c)
xmd_target_link_libraries(test_lexer_escape_fix)

add_executable(test_ast_parser test/test_ast_parser.c)
xmd_target_link_libraries(test_ast_parser)

add_executable(test_function_calls test/function/test_function_calls.c)
xmd_target_link_libraries(test_function_calls)

add_executable(test_array_evaluation test/function/test_array_evaluation.c)
xmd_target_link_libraries(test_array_evaluation)

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
add_test(NAME long_output_tests COMMAND test_long_output)
add_test(NAME output_tests COMMAND test_output)
add_test(NAME resource_tests COMMAND test_resource)
add_test(NAME module_tests COMMAND test_module)
add_test(NAME import_export_tests COMMAND test_import_export)
add_test(NAME dependency_tests COMMAND test_dependency)
# Re-enabled previously failing tests
add_test(NAME security_tests COMMAND test_security)
add_test(NAME performance_tests COMMAND test_performance)
add_test(NAME real_performance_tests COMMAND test_real_performance)
add_test(NAME cli_tests COMMAND test_cli)
add_test(NAME upgrade_version_tests COMMAND test_upgrade_version)
add_test(NAME docs_tests COMMAND test_docs)
add_test(NAME devtools_tests COMMAND test_devtools)
add_test(NAME xmd_processor_tests COMMAND test_xmd_processor)
add_test(NAME truncate_fix_tests COMMAND test_truncate_fix)
add_test(NAME advanced_scripting_tests COMMAND test_advanced_scripting)
set_tests_properties(advanced_scripting_tests PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME variable_advanced_tests COMMAND test_variable_advanced)
add_test(NAME multiline_enhanced_tests COMMAND test_multiline_enhanced)
set_tests_properties(multiline_enhanced_tests PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME advanced_integration_tests COMMAND test_advanced_integration)
set_tests_properties(advanced_integration_tests PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Stress tests - now included in main test suite per INSTRUCTIONS.md Rule 17
add_test(NAME brutal_nesting_tests COMMAND test_brutal_nesting)
add_test(NAME resource_exhaustion_tests COMMAND test_resource_exhaustion)

# Integration tests
add_test(NAME c_api_integration_tests COMMAND test_c_api_integration)

# End-to-end tests
add_test(NAME cli_e2e_tests COMMAND test_cli_e2e)

# Security tests
add_test(NAME sandbox_tests COMMAND test_sandbox)

# AST system tests
add_test(NAME ast_node_tests COMMAND test_ast_node)
add_test(NAME lexer_enhanced_tests COMMAND test_lexer_enhanced)
add_test(NAME lexer_escape_fix_tests COMMAND test_lexer_escape_fix)
add_test(NAME ast_parser_tests COMMAND test_ast_parser)
add_test(NAME function_call_tests COMMAND test_function_calls)
add_test(NAME array_evaluation_tests COMMAND test_array_evaluation)

# Custom target to run all tests
add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS test_token_simple test_lexer test_string_duplicate test_string_extract test_memory_allocate test_memory_free_safe test_variable test_store test_template test_conditional test_loop test_flow test_error test_executor test_long_output test_output test_resource test_module test_import_export test_dependency test_security test_performance test_cli test_upgrade_version test_docs test_devtools test_xmd_processor test_truncate_fix test_advanced_scripting test_variable_advanced test_multiline_enhanced test_advanced_integration test_brutal_nesting test_resource_exhaustion test_c_api_integration test_cli_e2e test_sandbox test_ast_node test_lexer_enhanced test_lexer_escape_fix test_ast_parser test_function_calls test_array_evaluation
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

