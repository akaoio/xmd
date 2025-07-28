
Name: Mango
UID: mango
Role: import ../roles/tech_writer.md
Experty: import ../experties/xmd.md

## TASK: REFACTOR WITHOUT CODE CHANGE

> The current directory tree is not comprehensive and causing much confusion. Some child folders or files stand at the same level with their parents.

## OBJECTIVES

- Move files and folders to proper places.
- Fix naming violations following development principles.
- Reduce confusion, increase code comprehension.
- Only move folders/files to correct places and update paths include/import. DO NOT EDIT LOGIC.

## DEVELOPMENT PRINCIPLES


# XMD Development Principles

Core principles that guide XMD development and ensure maintainable, reliable code.

## Core Philosophy

XMD follows strict architectural principles to maintain simplicity, testability, and modularity. These principles ensure the codebase remains manageable as it grows.

- **Test-Driven Development:** Implement comprehensive unit tests before writing implementation code. Tests must validate real-world scenarios and edge cases to ensure system reliability.

- **Code Isolation:** Enforce strict separation: one function per file, one file per directory. This ensures modularity and maintainability through isolated code units.

- **Naming Convention:** Maintain naming consistency: function name = file name = directory name using snake_case. Structure: `parent/child/child.c` containing `child()` function.

- **Code Organization:** Place all reusable components in `src/common/` hierarchy. Eliminate code duplication by centralizing shared functionality. Example: `src/common/group/child/child.c`.

- **File Size Constraints:** Limit source files to maximum 200 lines of code. This enforces focused, single-purpose functions and maintains cognitive load within manageable bounds.

- **Production-Ready Implementation:** Prohibit placeholder code: no mocks, simplified stubs, TODO comments, or technical debt. All code must be complete, production-grade implementation.

- **Documentation Standards:** Create design notes before implementation: `docs/notes/<YYYYMMDD-HHMM-topic>.md` (≤100 lines). Use Doxygen-compatible comments with required tags: @brief, @struct, @input, @output. Update documentation and tests before code changes.

- **Dependency Isolation:** Prohibit external dependencies. Use exclusively standard C library (C17) and self-contained implementations to ensure portability and reduce attack surface.

- **Implementation Planning:** Mandatory planning before implementation: `docs/plans/<YYYYMMDD-HHMM-plan>/<phase>/phase-instructions.md`. Decompose work into phases with dedicated documentation per phase.

- **Error Handling Protocol:** Implement comprehensive error handling: return meaningful error codes, validate all inputs, handle edge cases. Every function must gracefully manage failure scenarios.

- **Memory Management Discipline:** Enforce strict memory hygiene: validate all pointers before use, free all allocated memory, implement RAII patterns. Zero tolerance for memory leaks or undefined behavior.

- **Build System Architecture:** Use CMake exclusively for build configuration. Prohibit manual Makefile edits. Organize artifacts: build outputs in `build/`, official tests in `test/`, temporary tests in `sandbox/`.



## CURRENT TREE

src/
├── bindings
│   └── c_api
│       ├── c_api.c
│       ├── create_result
│       │   └── create_result.c
│       ├── evaluate_condition
│       │   └── evaluate_condition.c
│       ├── preprocess_for_loops
│       │   └── preprocess_for_loops.c
│       ├── preprocess_if_statements
│       │   └── preprocess_if_statements.c
│       ├── preprocess_variables
│       │   └── preprocess_variables.c
│       ├── xmd_cleanup
│       │   └── xmd_cleanup.c
│       ├── xmd_config_create_default
│       │   └── xmd_config_create_default.c
│       ├── xmd_config_free
│       │   └── xmd_config_free.c
│       ├── xmd_get_config
│       │   └── xmd_get_config.c
│       ├── xmd_get_variable
│       │   └── xmd_get_variable.c
│       ├── xmd_get_version
│       │   └── xmd_get_version.c
│       ├── xmd_init
│       │   └── xmd_init.c
│       ├── xmd_process_file
│       │   └── xmd_process_file.c
│       ├── xmd_processor_create
│       │   └── xmd_processor_create.c
│       ├── xmd_processor_free
│       │   └── xmd_processor_free.c
│       ├── xmd_process_string
│       │   └── xmd_process_string.c
│       ├── xmd_result_free
│       │   └── xmd_result_free.c
│       ├── xmd_set_config
│       │   └── xmd_set_config.c
│       ├── xmd_set_variable
│       │   └── xmd_set_variable.c
│       └── xmd_validate
│           └── xmd_validate.c
├── cli
│   ├── cli
│   │   └── cli.c
│   ├── cli_cleanup
│   │   └── cli_cleanup.c
│   ├── cli_commands.c
│   ├── cli_execute
│   │   └── cli_execute.c
│   ├── cli_init
│   │   └── cli_init.c
│   ├── cli_process_file
│   │   └── cli_process_file.c
│   ├── cli_show_config
│   │   └── cli_show_config.c
│   ├── cli_show_help
│   │   └── cli_show_help.c
│   ├── cli_show_version
│   │   └── cli_show_version.c
│   ├── cli_validate_file
│   │   └── cli_validate_file.c
│   ├── cli_watch_directory
│   │   └── cli_watch_directory.c
│   ├── parser
│   │   ├── cli_parse_args
│   │   │   └── cli_parse_args.c
│   │   ├── is_flag
│   │   │   └── is_flag.c
│   │   ├── parse_command_type
│   │   │   └── parse_command_type.c
│   │   └── parser.c
│   └── plugin_manager_create
│       └── plugin_manager_create.c
├── conditional
│   ├── condition
│   │   └── condition.c
│   ├── condition_context_free
│   │   └── condition_context_free.c
│   ├── condition_context_new
│   │   └── condition_context_new.c
│   ├── condition_evaluate
│   │   └── condition_evaluate.c
│   ├── condition_logical_and
│   │   └── condition_logical_and.c
│   ├── condition_logical_not
│   │   └── condition_logical_not.c
│   ├── condition_logical_or
│   │   └── condition_logical_or.c
│   └── if_statement
│       └── if_statement.c
├── config
│   ├── config
│   │   └── config.c
│   ├── config.c
│   ├── config_create
│   │   └── config_create.c
│   ├── config_destroy
│   │   └── config_destroy.c
│   ├── config_get
│   │   └── config_get.c
│   ├── config_load_env
│   │   └── config_load_env.c
│   ├── config_load_file
│   │   └── config_load_file.c
│   ├── config_set
│   │   └── config_set.c
│   ├── config_validate
│   │   └── config_validate.c
│   ├── create_default_buffers
│   │   └── create_default_buffers.c
│   ├── create_default_limits
│   │   └── create_default_limits.c
│   ├── create_default_paths
│   │   └── create_default_paths.c
│   ├── create_default_precision
│   │   └── create_default_precision.c
│   ├── create_default_security
│   │   └── create_default_security.c
│   ├── create_default_timing
│   │   └── create_default_timing.c
│   ├── find_config_value
│   │   └── find_config_value.c
│   ├── free_paths_config
│   │   └── free_paths_config.c
│   ├── free_security_config
│   │   └── free_security_config.c
│   ├── parse_env_bool
│   │   └── parse_env_bool.c
│   ├── parse_env_double
│   │   └── parse_env_double.c
│   ├── parse_env_size_t
│   │   └── parse_env_size_t.c
│   ├── xmd_internal_config_add_exec_whitelist
│   │   └── xmd_internal_config_add_exec_whitelist.c
│   ├── xmd_internal_config_add_module_path
│   │   └── xmd_internal_config_add_module_path.c
│   ├── xmd_internal_config_free
│   │   └── xmd_internal_config_free.c
│   ├── xmd_internal_config_get_global
│   │   └── xmd_internal_config_get_global.c
│   ├── xmd_internal_config_load_env
│   │   └── xmd_internal_config_load_env.c
│   ├── xmd_internal_config_load_file
│   │   └── xmd_internal_config_load_file.c
│   ├── xmd_internal_config_load_whitelist_env
│   │   └── xmd_internal_config_load_whitelist_env.c
│   ├── xmd_internal_config_new
│   │   └── xmd_internal_config_new.c
│   ├── xmd_internal_config_save_file
│   │   └── xmd_internal_config_save_file.c
│   ├── xmd_internal_config_set_exec_whitelist
│   │   └── xmd_internal_config_set_exec_whitelist.c
│   └── xmd_internal_config_set_global
│       └── xmd_internal_config_set_global.c
├── config_globals
│   └── config_globals.c
├── dependency
│   ├── add_to_cycle_path
│   │   └── add_to_cycle_path.c
│   ├── clear_cycle_path
│   │   └── clear_cycle_path.c
│   ├── dependency_detector_free
│   │   └── dependency_detector_free.c
│   ├── dependency_detector_new
│   │   └── dependency_detector_new.c
│   ├── detector
│   │   ├── clear_cycle_path
│   │   │   └── clear_cycle_path.c
│   │   ├── dependency_check_circular
│   │   │   └── dependency_check_circular.c
│   │   ├── dependency_check_circular_from
│   │   │   └── dependency_check_circular_from.c
│   │   ├── dependency_detector_free
│   │   │   └── dependency_detector_free.c
│   │   ├── dependency_detector_new
│   │   │   └── dependency_detector_new.c
│   │   ├── dependency_get_cycle_path
│   │   │   └── dependency_get_cycle_path.c
│   │   ├── detector.c
│   │   ├── dfs_cycle_detection
│   │   │   └── dfs_cycle_detection.c
│   │   └── reset_visit_states
│   │       └── reset_visit_states.c
│   ├── graph
│   │   ├── calculate_in_degrees
│   │   │   └── calculate_in_degrees.c
│   │   ├── dependency_build_graph
│   │   │   └── dependency_build_graph.c
│   │   ├── dependency_graph_add_dependency
│   │   │   └── dependency_graph_add_dependency.c
│   │   ├── dependency_graph_add_module
│   │   │   └── dependency_graph_add_module.c
│   │   ├── dependency_graph_find_node
│   │   │   └── dependency_graph_find_node.c
│   │   ├── dependency_graph_free
│   │   │   └── dependency_graph_free.c
│   │   ├── dependency_graph_new
│   │   │   └── dependency_graph_new.c
│   │   ├── dependency_graph_topological_sort
│   │   │   └── dependency_graph_topological_sort.c
│   │   ├── dependency_node_add_child
│   │   │   └── dependency_node_add_child.c
│   │   ├── dependency_node_free
│   │   │   └── dependency_node_free.c
│   │   ├── dependency_node_new
│   │   │   └── dependency_node_new.c
│   │   └── graph.c
│   ├── reset_visit_states
│   │   └── reset_visit_states.c
│   └── validator
│       └── dependency_validate_all
│           └── dependency_validate_all.c
├── devtools
│   ├── debugger
│   │   └── debugger.c
│   ├── formatter
│   │   └── formatter.c
│   └── linter
│       └── linter.c
├── docs
│   ├── examples
│   │   └── examples.c
│   ├── reference
│   │   └── reference.c
│   └── tutorial
│       └── tutorial.c
├── error
│   ├── catch_block_begin
│   │   └── catch_block_begin.c
│   ├── catch_block_end
│   │   └── catch_block_end.c
│   ├── error_clear
│   │   └── error_clear.c
│   ├── error_context_free
│   │   └── error_context_free.c
│   ├── error_get_current
│   │   └── error_get_current.c
│   ├── error_handling
│   │   └── error_handling.c
│   ├── error_is_caught
│   │   └── error_is_caught.c
│   ├── error_throw
│   │   └── error_throw.c
│   ├── free_xmd_error
│   │   └── free_xmd_error.c
│   ├── try_block_begin
│   │   └── try_block_begin.c
│   └── try_block_end
│       └── try_block_end.c
├── executor
│   ├── command_result_free
│   │   └── command_result_free.c
│   ├── executor
│   │   ├── command_result_free
│   │   │   └── command_result_free.c
│   │   ├── executor.c
│   │   ├── executor_context_free
│   │   │   └── executor_context_free.c
│   │   ├── executor_context_new
│   │   │   └── executor_context_new.c
│   │   ├── executor_run_command
│   │   │   └── executor_run_command.c
│   │   ├── executor_run_with_timeout
│   │   │   └── executor_run_with_timeout.c
│   │   ├── free_command_args
│   │   │   └── free_command_args.c
│   │   ├── get_time_ms
│   │   │   └── get_time_ms.c
│   │   ├── parse_command_args
│   │   │   └── parse_command_args.c
│   │   ├── read_with_timeout
│   │   │   └── read_with_timeout.c
│   │   └── set_executor_error
│   │       └── set_executor_error.c
│   ├── executor_context_free
│   │   └── executor_context_free.c
│   ├── executor_context_new
│   │   └── executor_context_new.c
│   ├── executor_cross_platform
│   │   └── executor_cross_platform.c
│   ├── executor_run_command
│   │   └── executor_run_command.c
│   └── executor_validate_command
│       └── executor_validate_command.c
├── flow
│   ├── flow_break_statement
│   │   └── flow_break_statement.c
│   ├── flow_context_free
│   │   └── flow_context_free.c
│   ├── flow_context_new
│   │   └── flow_context_new.c
│   ├── flow_continue_statement
│   │   └── flow_continue_statement.c
│   ├── flow_control
│   │   └── flow_control.c
│   ├── flow_get_return_value
│   │   └── flow_get_return_value.c
│   └── flow_return_statement
│       └── flow_return_statement.c
├── import_export
│   ├── export
│   │   └── export.c
│   ├── export_directive_free
│   │   └── export_directive_free.c
│   ├── export_directive_new
│   │   └── export_directive_new.c
│   ├── export_parse_directive
│   │   └── export_parse_directive.c
│   ├── extract_word
│   │   └── extract_word.c
│   ├── import
│   │   └── import.c
│   ├── import_all_symbols
│   │   └── import_all_symbols.c
│   ├── import_directive_free
│   │   └── import_directive_free.c
│   ├── import_directive_new
│   │   └── import_directive_new.c
│   ├── import_export_processor_free
│   │   └── import_export_processor_free.c
│   ├── import_export_processor_new
│   │   └── import_export_processor_new.c
│   ├── import_parse_directive
│   │   └── import_parse_directive.c
│   ├── import_symbol
│   │   └── import_symbol.c
│   └── skip_whitespace
│       └── skip_whitespace.c
├── lexer
│   ├── lexer_advance
│   │   └── lexer_advance.c
│   ├── lexer_at_end
│   │   └── lexer_at_end.c
│   ├── lexer.c
│   ├── lexer_create
│   │   └── lexer_create.c
│   ├── lexer_current_char
│   │   └── lexer_current_char.c
│   ├── lexer_extract_substring
│   │   └── lexer_extract_substring.c
│   ├── lexer_free
│   │   └── lexer_free.c
│   ├── lexer_get_column
│   │   └── lexer_get_column.c
│   ├── lexer_get_line
│   │   └── lexer_get_line.c
│   ├── lexer_get_position
│   │   └── lexer_get_position.c
│   ├── lexer_next_token
│   │   └── lexer_next_token.c
│   ├── lexer_peek_char
│   │   └── lexer_peek_char.c
│   ├── lexer_peek_token
│   │   └── lexer_peek_token.c
│   ├── lexer_read_code_block
│   │   └── lexer_read_code_block.c
│   ├── lexer_read_html_comment
│   │   └── lexer_read_html_comment.c
│   ├── lexer_read_line
│   │   └── lexer_read_line.c
│   ├── lexer_read_text
│   │   └── lexer_read_text.c
│   ├── lexer_read_variable_ref
│   │   └── lexer_read_variable_ref.c
│   ├── lexer_read_xmd_directive
│   │   └── lexer_read_xmd_directive.c
│   ├── lexer_reset
│   │   └── lexer_reset.c
│   ├── lexer_skip_whitespace
│   │   └── lexer_skip_whitespace.c
│   └── lexer_starts_with
│       └── lexer_starts_with.c
├── loop
│   ├── append_to_result
│   │   └── append_to_result.c
│   ├── for_loop
│   │   └── for_loop.c
│   ├── loop_break
│   │   └── loop_break.c
│   ├── loop_context_free
│   │   └── loop_context_free.c
│   ├── loop_context_new
│   │   └── loop_context_new.c
│   ├── loop_continue
│   │   └── loop_continue.c
│   ├── set_loop_error
│   │   └── set_loop_error.c
│   └── while_loop_process
│       └── while_loop_process.c
├── main
│   ├── cleanup_cmd_variables
│   │   └── cleanup_cmd_variables.c
│   ├── cmd_process
│   │   └── cmd_process.c
│   ├── cmd_process_create_config
│   │   └── cmd_process_create_config.c
│   ├── cmd_process_format_output
│   │   └── cmd_process_format_output.c
│   ├── cmd_process_handle_input
│   │   └── cmd_process_handle_input.c
│   ├── cmd_process_parse_args
│   │   └── cmd_process_parse_args.c
│   ├── cmd_process_setup_processor
│   │   └── cmd_process_setup_processor.c
│   ├── cmd_upgrade
│   │   └── cmd_upgrade.c
│   ├── cmd_validate
│   │   └── cmd_validate.c
│   ├── cmd_watch
│   │   └── cmd_watch.c
│   ├── convert_shorthand_to_process
│   │   └── convert_shorthand_to_process.c
│   ├── format_output
│   │   └── format_output.c
│   ├── free_converted_argv
│   │   └── free_converted_argv.c
│   ├── looks_like_file_path
│   │   └── looks_like_file_path.c
│   ├── print_usage
│   │   └── print_usage.c
│   └── print_version
│       └── print_version.c
├── main.c
├── module
│   ├── file_exists
│   │   └── file_exists.c
│   ├── module
│   │   └── module.c
│   ├── module_add_dependency
│   │   └── module_add_dependency.c
│   ├── module_export
│   │   └── module_export.c
│   ├── module_free
│   │   └── module_free.c
│   ├── module_get_export
│   │   └── module_get_export.c
│   ├── module_load_content
│   │   └── module_load_content.c
│   ├── module_new
│   │   └── module_new.c
│   ├── module_registry_add_search_path
│   │   └── module_registry_add_search_path.c
│   ├── module_registry_find
│   │   └── module_registry_find.c
│   ├── module_registry_free
│   │   └── module_registry_free.c
│   ├── module_registry_load
│   │   └── module_registry_load.c
│   ├── module_registry_new
│   │   └── module_registry_new.c
│   ├── module_registry_register
│   │   └── module_registry_register.c
│   └── module_resolve_path
│       └── module_resolve_path.c
├── output
│   ├── formatter
│   │   └── formatter.c
│   ├── output_escape_html
│   │   └── output_escape_html.c
│   ├── output_escape_json
│   │   └── output_escape_json.c
│   ├── output_format_as_code
│   │   └── output_format_as_code.c
│   ├── output_formatter_free
│   │   └── output_formatter_free.c
│   ├── output_format_text
│   │   └── output_format_text.c
│   ├── output_strip_ansi_codes
│   │   └── output_strip_ansi_codes.c
│   ├── output_truncate
│   │   └── output_truncate.c
│   └── set_formatter_error
│       └── set_formatter_error.c
├── performance
│   ├── benchmark
│   │   └── benchmark.c
│   ├── benchmark_generate_report
│   │   └── benchmark_generate_report.c
│   ├── benchmark_run
│   │   └── benchmark_run.c
│   ├── benchmark_suite_destroy
│   │   └── benchmark_suite_destroy.c
│   ├── calculate_stats
│   │   └── calculate_stats.c
│   ├── compare_times
│   │   └── compare_times.c
│   ├── get_time_ns
│   │   └── get_time_ns.c
│   ├── optimizer
│   │   ├── apply_common_subexpression_elimination
│   │   │   └── apply_common_subexpression_elimination.c
│   │   ├── apply_constant_folding
│   │   │   └── apply_constant_folding.c
│   │   ├── apply_dead_code_elimination
│   │   │   └── apply_dead_code_elimination.c
│   │   ├── apply_inline_expansion
│   │   │   └── apply_inline_expansion.c
│   │   ├── apply_loop_unrolling
│   │   │   └── apply_loop_unrolling.c
│   │   ├── optimizer.c
│   │   ├── optimizer_state
│   │   │   └── optimizer_state.c
│   │   ├── perf_optimize_ast
│   │   │   └── perf_optimize_ast.c
│   │   ├── perf_optimizer_cleanup
│   │   │   └── perf_optimizer_cleanup.c
│   │   ├── perf_optimizer_init
│   │   │   └── perf_optimizer_init.c
│   │   └── should_apply_optimization
│   │       └── should_apply_optimization.c
│   ├── profiler
│   │   ├── get_memory_usage
│   │   │   └── get_memory_usage.c
│   │   ├── get_time_ns
│   │   │   └── get_time_ns.c
│   │   ├── perf_profiler_create
│   │   │   └── perf_profiler_create.c
│   │   ├── perf_profiler_destroy
│   │   │   └── perf_profiler_destroy.c
│   │   ├── perf_profiler_generate_report
│   │   │   └── perf_profiler_generate_report.c
│   │   ├── perf_profiler_get_metrics
│   │   │   └── perf_profiler_get_metrics.c
│   │   ├── perf_profiler_record_alloc
│   │   │   └── perf_profiler_record_alloc.c
│   │   ├── perf_profiler_record_cache_hit
│   │   │   └── perf_profiler_record_cache_hit.c
│   │   ├── perf_profiler_record_cache_miss
│   │   │   └── perf_profiler_record_cache_miss.c
│   │   ├── perf_profiler_record_dealloc
│   │   │   └── perf_profiler_record_dealloc.c
│   │   ├── perf_profiler_start
│   │   │   └── perf_profiler_start.c
│   │   ├── perf_profiler_stop
│   │   │   └── perf_profiler_stop.c
│   │   ├── profiler.c
│   │   └── time_diff_ns
│   │       └── time_diff_ns.c
│   └── resize_results_if_needed
│       └── resize_results_if_needed.c
├── platform
│   ├── xmd_aligned_alloc
│   │   └── xmd_aligned_alloc.c
│   ├── xmd_aligned_free
│   │   └── xmd_aligned_free.c
│   ├── xmd_closedir
│   │   └── xmd_closedir.c
│   ├── xmd_create_directory
│   │   └── xmd_create_directory.c
│   ├── xmd_file_exists
│   │   └── xmd_file_exists.c
│   ├── xmd_get_cpu_count
│   │   └── xmd_get_cpu_count.c
│   ├── xmd_get_cpu_time
│   │   └── xmd_get_cpu_time.c
│   ├── xmd_get_fd_count
│   │   └── xmd_get_fd_count.c
│   ├── xmd_get_filename
│   │   └── xmd_get_filename.c
│   ├── xmd_get_memory_size
│   │   └── xmd_get_memory_size.c
│   ├── xmd_get_memory_usage
│   │   └── xmd_get_memory_usage.c
│   ├── xmd_get_tick_count
│   │   └── xmd_get_tick_count.c
│   ├── xmd_get_time
│   │   └── xmd_get_time.c
│   ├── xmd_is_directory
│   │   └── xmd_is_directory.c
│   ├── xmd_mkdir
│   │   └── xmd_mkdir.c
│   ├── xmd_mutex_destroy
│   │   └── xmd_mutex_destroy.c
│   ├── xmd_mutex_init
│   │   └── xmd_mutex_init.c
│   ├── xmd_mutex_lock
│   │   └── xmd_mutex_lock.c
│   ├── xmd_mutex_unlock
│   │   └── xmd_mutex_unlock.c
│   ├── xmd_opendir
│   │   └── xmd_opendir.c
│   ├── xmd_process_close
│   │   └── xmd_process_close.c
│   ├── xmd_process_create
│   │   └── xmd_process_create.c
│   ├── xmd_process_kill
│   │   └── xmd_process_kill.c
│   ├── xmd_process_wait
│   │   └── xmd_process_wait.c
│   ├── xmd_readdir
│   │   └── xmd_readdir.c
│   └── xmd_sleep_ms
│       └── xmd_sleep_ms.c
├── resource
│   ├── count_file_descriptors
│   │   └── count_file_descriptors.c
│   ├── get_elapsed_time_ms
│   │   └── get_elapsed_time_ms.c
│   ├── get_memory_usage
│   │   └── get_memory_usage.c
│   ├── limiter
│   │   ├── limiter.c
│   │   ├── resource_limiter_check_limits
│   │   │   └── resource_limiter_check_limits.c
│   │   ├── resource_limiter_free
│   │   │   └── resource_limiter_free.c
│   │   ├── resource_limiter_new
│   │   │   └── resource_limiter_new.c
│   │   ├── resource_limiter_set_cpu_limit
│   │   │   └── resource_limiter_set_cpu_limit.c
│   │   ├── resource_limiter_set_memory_limit
│   │   │   └── resource_limiter_set_memory_limit.c
│   │   ├── resource_limiter_set_time_limit
│   │   │   └── resource_limiter_set_time_limit.c
│   │   └── set_limiter_error
│   │       └── set_limiter_error.c
│   ├── monitor
│   │   └── monitor.c
│   ├── resource_monitor_free
│   │   └── resource_monitor_free.c
│   ├── resource_monitor_get_usage
│   │   └── resource_monitor_get_usage.c
│   ├── resource_monitor_reset
│   │   └── resource_monitor_reset.c
│   ├── resource_monitor_start
│   │   └── resource_monitor_start.c
│   ├── resource_monitor_stop
│   │   └── resource_monitor_stop.c
│   └── set_monitor_error
│       └── set_monitor_error.c
├── sandbox
│   ├── check_command_injection
│   ├── extract_base_command
│   ├── extract_command_name
│   │   └── extract_command_name.c
│   ├── normalize_path
│   ├── sandbox
│   ├── sandbox_apply_limits
│   │   └── sandbox_apply_limits.c
│   ├── sandbox.c
│   ├── sandbox_check_command_allowed
│   │   └── sandbox_check_command_allowed.c
│   ├── sandbox_check_path_allowed
│   │   └── sandbox_check_path_allowed.c
│   ├── sandbox_config_add_allowed_path
│   │   └── sandbox_config_add_allowed_path.c
│   ├── sandbox_config_add_blacklist
│   │   └── sandbox_config_add_blacklist.c
│   ├── sandbox_config_add_whitelist
│   │   └── sandbox_config_add_whitelist.c
│   ├── sandbox_config_free
│   │   └── sandbox_config_free.c
│   ├── sandbox_config_new
│   │   └── sandbox_config_new.c
│   ├── sandbox_context_free
│   │   └── sandbox_context_free.c
│   └── sandbox_context_new
│       └── sandbox_context_new.c
├── security
│   ├── auditor
│   │   ├── auditor.c
│   │   ├── audit_state
│   │   │   └── audit_state.c
│   │   ├── expand_entries_array
│   │   │   └── expand_entries_array.c
│   │   ├── get_timestamp_ms
│   │   │   └── get_timestamp_ms.c
│   │   ├── security_audit_cleanup
│   │   │   └── security_audit_cleanup.c
│   │   ├── security_audit_get_entries
│   │   │   └── security_audit_get_entries.c
│   │   ├── security_audit_init
│   │   │   └── security_audit_init.c
│   │   ├── security_audit_log
│   │   │   └── security_audit_log.c
│   │   └── write_audit_entry_to_file
│   │       └── write_audit_entry_to_file.c
│   ├── sanitizer
│   │   ├── sanitizer.c
│   │   ├── security_sanitize_command_output
│   │   │   └── security_sanitize_command_output.c
│   │   ├── security_sanitize_html
│   │   │   └── security_sanitize_html.c
│   │   └── security_sanitize_output
│   │       └── security_sanitize_output.c
│   └── validator
│       ├── security_validate_command
│       │   └── security_validate_command.c
│       ├── security_validate_input
│       │   └── security_validate_input.c
│       ├── security_validate_path
│       │   └── security_validate_path.c
│       └── validator.c
├── store
│   ├── store_clear
│   │   └── store_clear.c
│   ├── store_create
│   │   └── store_create.c
│   ├── store_destroy
│   │   └── store_destroy.c
│   ├── store_entry_create
│   │   └── store_entry_create.c
│   ├── store_entry_destroy
│   │   └── store_entry_destroy.c
│   ├── store_get
│   │   └── store_get.c
│   ├── store_has
│   │   └── store_has.c
│   ├── store_keys
│   │   └── store_keys.c
│   ├── store_ops
│   │   ├── store_clear
│   │   │   └── store_clear.c
│   │   ├── store_has
│   │   │   └── store_has.c
│   │   ├── store_keys
│   │   │   └── store_keys.c
│   │   ├── store_ops.c
│   │   ├── store_remove
│   │   │   └── store_remove.c
│   │   └── store_size
│   │       └── store_size.c
│   ├── store_remove
│   │   └── store_remove.c
│   ├── store_resize
│   │   └── store_resize.c
│   ├── store_set
│   │   └── store_set.c
│   └── store_size
│       └── store_size.c
├── template
│   ├── extract_variable_name
│   │   └── extract_variable_name.c
│   ├── find_next_variable
│   │   └── find_next_variable.c
│   ├── template.c
│   ├── template_context_create
│   │   └── template_context_create.c
│   ├── template_context_destroy
│   │   └── template_context_destroy.c
│   ├── template_extract
│   │   └── template_extract.c
│   ├── template_extract_variables
│   │   └── template_extract_variables.c
│   ├── template_has_variables
│   │   └── template_has_variables.c
│   ├── template_process
│   │   └── template_process.c
│   └── template_validate
│       └── template_validate.c
├── token
│   ├── token_copy
│   │   └── token_copy.c
│   ├── token_create
│   │   └── token_create.c
│   ├── token_duplicate
│   │   └── token_duplicate.c
│   ├── token_equals
│   │   └── token_equals.c
│   ├── token_free
│   │   └── token_free.c
│   ├── token_list_append
│   │   └── token_list_append.c
│   ├── token_list_destroy
│   │   └── token_list_destroy.c
│   ├── token_list_free
│   │   └── token_list_free.c
│   ├── token_list_get
│   │   └── token_list_get.c
│   ├── token_list_length
│   │   └── token_list_length.c
│   ├── token_list_reverse
│   │   └── token_list_reverse.c
│   ├── token_set_value
│   │   └── token_set_value.c
│   ├── token_to_string
│   │   └── token_to_string.c
│   ├── token_type_is_valid
│   │   └── token_type_is_valid.c
│   └── token_type_to_string
│       └── token_type_to_string.c
├── utils
│   ├── memory
│   │   ├── memory_allocate
│   │   │   └── memory_allocate.c
│   │   └── memory_free_safe
│   │       └── memory_free_safe.c
│   ├── string
│   │   ├── string_duplicate
│   │   │   └── string_duplicate.c
│   │   └── string_extract
│   │       └── string_extract.c
│   ├── utils.c
│   ├── xmd_calloc
│   │   └── xmd_calloc.c
│   ├── xmd_check_null
│   │   └── xmd_check_null.c
│   ├── xmd_expand_array
│   │   └── xmd_expand_array.c
│   ├── xmd_hash_key
│   │   └── xmd_hash_key.c
│   ├── xmd_malloc
│   │   └── xmd_malloc.c
│   ├── xmd_malloc_safe
│   │   └── xmd_malloc_safe.c
│   ├── xmd_realloc
│   │   └── xmd_realloc.c
│   ├── xmd_strdup
│   │   └── xmd_strdup.c
│   ├── xmd_variable_equals
│   │   └── xmd_variable_equals.c
│   └── xmd_variable_to_number
│       └── xmd_variable_to_number.c
├── variable
│   ├── variable_array_add
│   │   └── variable_array_add.c
│   ├── variable_array_free
│   │   └── variable_array_free.c
│   ├── variable_array_get
│   │   └── variable_array_get.c
│   ├── variable_array_length
│   │   └── variable_array_length.c
│   ├── variable_array_set
│   │   └── variable_array_set.c
│   ├── variable_array_size
│   │   └── variable_array_size.c
│   ├── variable_convert
│   │   └── variable_convert.c
│   ├── variable_copy
│   │   └── variable_copy.c
│   ├── variable_create_array
│   │   └── variable_create_array.c
│   ├── variable_create_boolean
│   │   └── variable_create_boolean.c
│   ├── variable_create_null
│   │   └── variable_create_null.c
│   ├── variable_create_number
│   │   └── variable_create_number.c
│   ├── variable_create_object
│   │   └── variable_create_object.c
│   ├── variable_create_string
│   │   └── variable_create_string.c
│   ├── variable_equals
│   │   └── variable_equals.c
│   ├── variable_extended
│   │   ├── variable_extended.c
│   │   ├── variable_get_boolean
│   │   │   └── variable_get_boolean.c
│   │   ├── variable_get_number
│   │   │   └── variable_get_number.c
│   │   └── variable_get_string
│   │       └── variable_get_string.c
│   ├── variable_get_type
│   │   └── variable_get_type.c
│   ├── variable_new_array
│   │   └── variable_new_array.c
│   ├── variable_object_find_key
│   │   └── variable_object_find_key.c
│   ├── variable_object_free
│   │   └── variable_object_free.c
│   ├── variable_object_get
│   │   └── variable_object_get.c
│   ├── variable_object_keys
│   │   └── variable_object_keys.c
│   ├── variable_object_remove
│   │   └── variable_object_remove.c
│   ├── variable_object_set
│   │   └── variable_object_set.c
│   ├── variable_object_size
│   │   └── variable_object_size.c
│   ├── variable_ref
│   │   └── variable_ref.c
│   ├── variable_to_boolean
│   │   └── variable_to_boolean.c
│   ├── variable_to_number
│   │   └── variable_to_number.c
│   ├── variable_to_string
│   │   └── variable_to_string.c
│   ├── variable_unref
│   │   └── variable_unref.c
│   └── variable_unref_single
│       └── variable_unref.c
└── xmd_processor
    ├── api
    ├── backup_variable_scope
    │   └── backup_variable_scope.c
    ├── context
    ├── create_context
    │   └── create_context.c
    ├── directives
    ├── evaluate_condition
    │   └── evaluate_condition.c
    ├── execute_command
    │   └── execute_command.c
    ├── find_matching_endfor
    │   └── find_matching_endfor.c
    ├── get_version
    │   └── get_version.c
    ├── is_multiline_directive
    │   └── is_multiline_directive.c
    ├── parse_array_literal
    │   └── parse_array_literal.c
    ├── parse_collection
    │   └── parse_collection.c
    ├── parse_range
    │   └── parse_range.c
    ├── process_cmd_function
    │   └── process_cmd_function.c
    ├── process_directive
    │   └── process_directive.c
    ├── process_elif
    │   └── process_elif.c
    ├── process_else
    │   └── process_else.c
    ├── process_endif
    │   └── process_endif.c
    ├── process_exec
    │   └── process_exec.c
    ├── process_for
    │   └── process_for.c
    ├── process_if
    │   └── process_if.c
    ├── process_import
    │   └── process_import.c
    ├── process_loop_body
    │   └── process_loop_body.c
    ├── process_multiline_block
    │   └── process_multiline_block.c
    ├── process_multiline_directive
    │   └── process_multiline_directive.c
    ├── process_multiline_directive_enhanced
    │   └── process_multiline_directive_enhanced.c
    ├── process_print_function
    │   └── process_print_function.c
    ├── process_script_block
    │   └── process_script_block.c
    ├── process_set
    │   └── process_set.c
    ├── process_text_with_directives
    │   └── process_text_with_directives.c
    ├── process_xmd_content
    │   └── process_xmd_content.c
    ├── process_xmd_content_enhanced
    │   └── process_xmd_content_enhanced.c
    ├── process_xmd_content_fixed
    │   └── process_xmd_content_fixed.c
    ├── process_xmd_directive
    │   └── process_xmd_directive.c
    ├── restore_variable_scope
    │   └── restore_variable_scope.c
    ├── should_execute_block
    │   └── should_execute_block.c
    ├── substitute_variables
    │   └── substitute_variables.c
    ├── trim_whitespace
    │   └── trim_whitespace.c
    ├── utilities
    ├── xmd_error_string
    │   └── xmd_error_string.c
    ├── xmd_process_string
    │   └── xmd_process_string.c
    └── xmd_validate_syntax
        └── xmd_validate_syntax.c

499 directories, 467 files
