cmake_minimum_required(VERSION 3.12)
project(XMD VERSION 0.0.2 LANGUAGES C)

# Set C standard - XMD requires C17
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add compile flags for debugging and warnings
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# Default to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Collect all source files recursively
file(GLOB_RECURSE XMD_SOURCES 
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

# Remove main.c from the general sources (we'll add it separately)
list(REMOVE_ITEM XMD_SOURCES "${CMAKE_SOURCE_DIR}/src/main.c")

# NOTE: ast_create_* functions are required - they are called extensively by parsers
# Do not exclude them from the build

# Also remove more duplicate implementations found in subdirectories
file(GLOB_RECURSE MORE_DUPLICATES
    "${CMAKE_SOURCE_DIR}/src/ast/node/util/*.c"
    "${CMAKE_SOURCE_DIR}/src/ast/node/misc/*.c"
    "${CMAKE_SOURCE_DIR}/src/ast/evaluator/expression/ast_evaluate_await/*.c"
    "${CMAKE_SOURCE_DIR}/src/ast/parser/function/ast_parse_function/*.c"
    "${CMAKE_SOURCE_DIR}/src/ast/parser/function/ast_parse_potential_function_call/*.c"
    "${CMAKE_SOURCE_DIR}/src/ast/parser/conditional/ast_parse_conditional/*.c"
    "${CMAKE_SOURCE_DIR}/src/ast/parser/object/ast_parse_object_creation/*.c"
    "${CMAKE_SOURCE_DIR}/src/ast/parser/output/ast_parse_print/*.c"
    "${CMAKE_SOURCE_DIR}/src/ast/parser/program/ast_parse_program/*.c"
    "${CMAKE_SOURCE_DIR}/src/ast/parser/variable/ast_parse_multiple_variables_handler/*.c"
    "${CMAKE_SOURCE_DIR}/src/bindings/c_api/configuration/xmd_get_config/*.c"
    "${CMAKE_SOURCE_DIR}/src/bindings/c_api/configuration/xmd_set_config/*.c"
)
list(REMOVE_ITEM XMD_SOURCES ${MORE_DUPLICATES})

# Print diagnostic information
message(STATUS "Found ${CMAKE_SOURCE_DIR}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Count source files for reporting
list(LENGTH XMD_SOURCES XMD_SOURCE_COUNT)
message(STATUS "Found ${XMD_SOURCE_COUNT} source files (excluding main.c)")

# Create the main executable
add_executable(xmd 
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${XMD_SOURCES}
)

# Link math library if needed
find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(xmd ${MATH_LIBRARY})
endif()

# Platform-specific linking
if(WIN32)
    # Windows-specific libraries
    target_link_libraries(xmd ws2_32)
elseif(UNIX AND NOT APPLE)
    # Linux-specific libraries
    target_link_libraries(xmd pthread dl)
elseif(APPLE)
    # macOS-specific libraries
    target_link_libraries(xmd pthread)
endif()

# Version configuration
configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/version.cmake.in"
    "${CMAKE_SOURCE_DIR}/include/version_info.h"
    @ONLY
)

# Install target
install(TARGETS xmd DESTINATION bin)

# Print summary
message(STATUS "")
message(STATUS "🚀 XMD Build Configuration:")
message(STATUS "  Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  Source Files: ${XMD_SOURCE_COUNT} + main.c")
message(STATUS "  Target: xmd executable")
message(STATUS "")