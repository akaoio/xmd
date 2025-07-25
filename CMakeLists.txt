cmake_minimum_required(VERSION 3.12)
project(xmd VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")

# Include directories
include_directories(include)
include_directories(src)

# Core library sources (Phase 1, 2, 3, 4 & 5)
set(XMD_LIB_SOURCES
    src/token/token.c
    src/lexer/lexer.c
    src/variable/variable.c
    src/variable/variable_convert.c
    src/variable/variable_extended.c
    src/store/store.c
    src/store/store_ops.c
    src/template/template.c
    src/template/template_extract.c
    src/conditional/condition/condition.c
    src/conditional/if_statement/if_statement.c
    src/loop/for_loop/for_loop.c
    src/flow/flow_control/flow_control.c
    src/error/error_handling/error_handling.c
    src/executor/executor/executor.c
    src/sandbox/sandbox/sandbox.c
    src/output/formatter/formatter.c
    src/resource/limiter/limiter.c
    src/resource/monitor/monitor.c
    src/module/module/module.c
    src/import_export/import/import.c
    src/import_export/export/export.c
    src/dependency/graph/graph.c
    src/dependency/detector/detector.c
    src/config/config.c
    src/utils/utils.c
    src/security/validator/validator.c
    src/security/sanitizer/sanitizer.c
    src/security/auditor/auditor.c
    
    # Performance components
    src/performance/optimizer/optimizer.c
    src/performance/profiler/profiler.c
    src/performance/benchmark/benchmark.c
    
    # CLI components
    src/cli/cli/cli.c
    src/cli/parser/parser.c
    src/config/config/config.c
    src/plugin/plugin/plugin.c
    src/bindings/c_api/c_api.c
    
    # Phase 8: Documentation and Developer Tools
    src/docs/tutorial/tutorial.c
    src/docs/examples/examples.c
    src/docs/reference/reference.c
    src/devtools/debugger/debugger.c
    src/devtools/linter/linter.c
    src/devtools/formatter/formatter.c
    
    src/xmd_stubs.c
)

# Create static library
add_library(xmd_lib STATIC ${XMD_LIB_SOURCES})

# Main executable
add_executable(xmd src/main.c)
target_link_libraries(xmd xmd_lib m)

# Individual test executables for each component
add_executable(test_token_simple test/token/test_token_simple.c)
target_link_libraries(test_token_simple xmd_lib m)

add_executable(test_lexer test/lexer/test_lexer.c)
target_link_libraries(test_lexer xmd_lib m)

add_executable(test_variable test/variable/test_variable.c)
target_link_libraries(test_variable xmd_lib m)

add_executable(test_store test/store/test_store.c)
target_link_libraries(test_store xmd_lib m)

add_executable(test_template test/template/test_template.c)
target_link_libraries(test_template xmd_lib m)

# Phase 3 tests (Control Flow)
add_executable(test_conditional test/conditional/test_conditional_simple.c)
target_link_libraries(test_conditional xmd_lib m)

add_executable(test_loop test/loop/test_loop_simple.c)
target_link_libraries(test_loop xmd_lib m)

add_executable(test_flow test/flow/test_flow_simple.c)
target_link_libraries(test_flow xmd_lib m)

add_executable(test_error test/error/test_error_simple.c)
target_link_libraries(test_error xmd_lib m)

# Integration tests
add_executable(test_phase2_integration test/integration/test_phase2_integration.c)
target_link_libraries(test_phase2_integration xmd_lib m)

add_executable(test_phase3_integration test/integration/test_phase3_integration_simple.c)
target_link_libraries(test_phase3_integration xmd_lib m)

# Phase 4 tests (Command Execution)
add_executable(test_executor test/executor/test_executor.c)
target_link_libraries(test_executor xmd_lib m)

add_executable(test_sandbox test/sandbox/test_sandbox.c)
target_link_libraries(test_sandbox xmd_lib m)

add_executable(test_output test/output/test_output.c)
target_link_libraries(test_output xmd_lib m)

add_executable(test_resource test/resource/test_resource.c)
target_link_libraries(test_resource xmd_lib m)

add_executable(test_phase4_integration test/integration/test_phase4_integration_simple.c)
target_link_libraries(test_phase4_integration xmd_lib m)

# Phase 5 tests (Module System)
add_executable(test_module test/module/test_module.c)
target_link_libraries(test_module xmd_lib m)

add_executable(test_import_export test/import_export/test_import_export.c)
target_link_libraries(test_import_export xmd_lib m)

add_executable(test_dependency test/dependency/test_dependency.c)
target_link_libraries(test_dependency xmd_lib m)

add_executable(test_phase5_integration test/integration/test_phase5_integration.c)
target_link_libraries(test_phase5_integration xmd_lib m)

add_executable(test_security test/security/test_security.c)
target_link_libraries(test_security xmd_lib m pthread)

# Performance tests
add_executable(test_performance test/performance/test_performance.c)
target_link_libraries(test_performance xmd_lib m)

# Phase 6 integration tests
add_executable(test_phase6_integration test/integration/test_phase6_simple.c)
target_link_libraries(test_phase6_integration xmd_lib m pthread)

# Phase 8 integration tests
add_executable(test_phase8_integration test/integration/test_phase8_integration.c)
target_link_libraries(test_phase8_integration xmd_lib m)

# CLI tests
add_executable(test_cli test/cli/test_cli.c)
target_link_libraries(test_cli xmd_lib m pthread dl)

# Phase 8 tests
add_executable(test_docs test/docs/test_docs.c)
target_link_libraries(test_docs xmd_lib m)

add_executable(test_devtools test/devtools/test_devtools.c)
target_link_libraries(test_devtools xmd_lib m)

# Main CLI executable
add_executable(xmd_cli src/main_cli.c)
target_link_libraries(xmd_cli xmd_lib m pthread dl)

# Enable testing
enable_testing()

# Add individual tests
add_test(NAME token_tests COMMAND test_token_simple)
add_test(NAME lexer_tests COMMAND test_lexer)
add_test(NAME variable_tests COMMAND test_variable)
add_test(NAME store_tests COMMAND test_store)
add_test(NAME template_tests COMMAND test_template)
add_test(NAME conditional_tests COMMAND test_conditional)
add_test(NAME loop_tests COMMAND test_loop)
add_test(NAME flow_tests COMMAND test_flow)
add_test(NAME error_tests COMMAND test_error)
add_test(NAME phase2_integration_tests COMMAND test_phase2_integration)
add_test(NAME phase3_integration_tests COMMAND test_phase3_integration)
add_test(NAME executor_tests COMMAND test_executor)
add_test(NAME sandbox_tests COMMAND test_sandbox)
add_test(NAME output_tests COMMAND test_output)
add_test(NAME resource_tests COMMAND test_resource)
add_test(NAME phase4_integration_tests COMMAND test_phase4_integration)
add_test(NAME module_tests COMMAND test_module)
add_test(NAME import_export_tests COMMAND test_import_export)
add_test(NAME dependency_tests COMMAND test_dependency)
add_test(NAME phase5_integration_tests COMMAND test_phase5_integration)
add_test(NAME security_tests COMMAND test_security)
add_test(NAME performance_tests COMMAND test_performance)
add_test(NAME phase6_integration_tests COMMAND test_phase6_integration)
add_test(NAME phase8_integration_tests COMMAND test_phase8_integration)
add_test(NAME cli_tests COMMAND test_cli)
add_test(NAME docs_tests COMMAND test_docs)
add_test(NAME devtools_tests COMMAND test_devtools)

# Custom target to run all tests
add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS test_token_simple test_lexer test_variable test_store test_template test_conditional test_loop test_flow test_error test_phase2_integration test_phase3_integration test_executor test_sandbox test_output test_resource test_phase4_integration test_module test_import_export test_dependency test_phase5_integration test_security
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