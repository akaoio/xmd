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

# Main CLI executable
add_executable(xmd_cli src/main_cli/main_cli.c)
target_link_libraries(xmd_cli xmd_lib)

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

add_executable(test_cli test/cli/test_cli.c)
xmd_target_link_libraries(test_cli)

add_executable(test_docs test/docs/test_docs.c)
xmd_target_link_libraries(test_docs)

add_executable(test_devtools test/devtools/test_devtools.c)
xmd_target_link_libraries(test_devtools)

add_executable(test_xmd_processor test/xmd_processor/test_xmd_processor.c)
xmd_target_link_libraries(test_xmd_processor)

# Stress tests (brutal panic battle tests)
add_executable(test_brutal_nesting test/stress/test_brutal_nesting.c)
xmd_target_link_libraries(test_brutal_nesting)

add_executable(test_resource_exhaustion test/stress/test_resource_exhaustion.c)
xmd_target_link_libraries(test_resource_exhaustion)

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
# Re-enabled previously failing tests
add_test(NAME security_tests COMMAND test_security)
add_test(NAME performance_tests COMMAND test_performance)
add_test(NAME cli_tests COMMAND test_cli)
add_test(NAME docs_tests COMMAND test_docs)
add_test(NAME devtools_tests COMMAND test_devtools)
add_test(NAME xmd_processor_tests COMMAND test_xmd_processor)

# Stress tests - now included in main test suite per INSTRUCTIONS.md Rule 17
add_test(NAME brutal_nesting_tests COMMAND test_brutal_nesting)
add_test(NAME resource_exhaustion_tests COMMAND test_resource_exhaustion)

# Custom target to run all tests
add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS test_token_simple test_lexer test_string_duplicate test_string_extract test_memory_allocate test_memory_free_safe test_variable test_store test_template test_conditional test_loop test_flow test_error test_executor test_output test_resource test_module test_import_export test_dependency test_security test_performance test_cli test_docs test_devtools test_xmd_processor test_brutal_nesting test_resource_exhaustion
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