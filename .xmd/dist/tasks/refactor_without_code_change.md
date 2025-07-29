
Name: Mango
UID: mango
Role: 
Experty: 

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

src
├── ast_add_argument
│   └── ast_add_argument.c
├── ast_add_element
│   └── ast_add_element.c
├── ast_add_statement
│   └── ast_add_statement.c
├── ast_create_array_access
│   └── ast_create_array_access.c
├── ast_create_array_literal
│   └── ast_create_array_literal.c
├── ast_create_assignment
│   └── ast_create_assignment.c
├── ast_create_binary_op
│   └── ast_create_binary_op.c
├── ast_create_block
│   └── ast_create_block.c
├── ast_create_boolean_literal
│   └── ast_create_boolean_literal.c
├── ast_create_conditional
│   └── ast_create_conditional.c
├── ast_create_directive
├── ast_create_function_call
│   └── ast_create_function_call.c
├── ast_create_identifier
│   └── ast_create_identifier.c
├── ast_create_loop
│   └── ast_create_loop.c
├── ast_create_number_literal
│   └── ast_create_number_literal.c
├── ast_create_program
│   └── ast_create_program.c
├── ast_create_string_literal
│   └── ast_create_string_literal.c
├── ast_create_unary_op
│   └── ast_create_unary_op.c
├── ast_create_variable_ref
│   └── ast_create_variable_ref.c
├── ast_evaluate
│   └── ast_evaluate.c
├── ast_evaluate_assignment
│   └── ast_evaluate_assignment.c
├── ast_evaluate_concatenation_expression
│   └── ast_evaluate_concatenation_expression.c
├── ast_evaluate_condition
│   └── ast_evaluate_condition.c
├── ast_evaluate_expression
│   └── ast_evaluate_expression.c
├── ast_evaluate_function_call
│   └── ast_evaluate_function_call.c
├── ast_evaluator_create
│   └── ast_evaluator_create.c
├── ast_evaluator_free
│   └── ast_evaluator_free.c
├── ast_free
│   └── ast_free.c
├── ast_parse_array_literal
│   └── ast_parse_array_literal.c
├── ast_parse_assignment
│   └── ast_parse_assignment.c
├── ast_parse_expression
│   └── ast_parse_expression.c
├── ast_parse_function_call
│   └── ast_parse_function_call.c
├── ast_parse_primary
│   └── ast_parse_primary.c
├── ast_parse_program
│   └── ast_parse_program.c
├── ast_parse_statement
│   └── ast_parse_statement.c
├── ast_process_for
│   └── ast_process_for.c
├── ast_substitute_variables
│   └── ast_substitute_variables.c
├── ast_value_create
│   └── ast_value_create.c
├── ast_value_free
│   └── ast_value_free.c
├── ast_value_to_variable
│   └── ast_value_to_variable.c
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
├── lexer_enhanced
│   └── lexer_enhanced.c
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
├── parser_advance_token
│   └── parser_advance_token.c
├── parser_get_error
│   └── parser_get_error.c
├── parser_has_error
│   └── parser_has_error.c
├── parser_peek_token
│   └── parser_peek_token.c
├── parser_set_error
│   └── parser_set_error.c
├── parser_state_create
│   └── parser_state_create.c
├── parser_state_free
│   └── parser_state_free.c
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
├── process_escape_sequences
│   └── process_escape_sequences.c
├── process_set_ast
│   └── process_set_ast.c
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
/
├── bin -> usr/bin
├── boot
│   ├── armbianEnv.txt
│   ├── boot.bmp
│   ├── boot.cmd
│   ├── boot.scr
│   ├── config-6.1.115-vendor-rk35xx
│   ├── dtb -> dtb-6.1.115-vendor-rk35xx
│   ├── dtb-6.1.115-vendor-rk35xx
│   │   └── rockchip
│   │       ├── overlay
│   │       │   ├── armsom-cm5-io-camera-imx219-cs0.dtbo
│   │       │   ├── armsom-cm5-io-camera-ov13850-cs1.dtbo
│   │       │   ├── armsom-cm5-io-display-10hd.dtbo
│   │       │   ├── armsom-cm5-rpi-cm4-io-camera0.dtbo
│   │       │   ├── armsom-cm5-rpi-cm4-io-camera1.dtbo
│   │       │   ├── armsom-cm5-rpi-cm4-io-display.dtbo
│   │       │   ├── armsom-cm5-rpi-display-2.4hd.dtbo
│   │       │   ├── armsom-sige5-camera-ov13850-cs0.dtbo
│   │       │   ├── armsom-sige5-camera-ov13850-cs1.dtbo
│   │       │   ├── armsom-sige5-display-10hd.dtbo
│   │       │   ├── armsom-sige5-rtl8852bs-bluetooth.dtbo
│   │       │   ├── armsom-sige7-camera-imx415-4k.dtbo
│   │       │   ├── armsom-sige7-camera-ov13850-csi0.dtbo
│   │       │   ├── armsom-sige7-camera-ov13850-csi1.dtbo
│   │       │   ├── armsom-sige7-display-10hd.dtbo
│   │       │   ├── armsom-w3-camera-imx419-csi.dtbo
│   │       │   ├── armsom-w3-camera-ov13850-csi.dtbo
│   │       │   ├── armsom-w3-display-10hd.dtbo
│   │       │   ├── hinlink-h88k-240x135-lcd.dtbo
│   │       │   ├── khadas-edge2-cam1.dtbo
│   │       │   ├── khadas-edge2-cam2.dtbo
│   │       │   ├── khadas-edge2-cam3.dtbo
│   │       │   ├── khadas-edge2-display-dsi0.dtbo
│   │       │   ├── khadas-edge2-display-dsi1.dtbo
│   │       │   ├── mixtile-blade3-sata2.dtbo
│   │       │   ├── nanopi-m6-display-dsi0-yx35.dtbo
│   │       │   ├── nanopi-m6-display-dsi1-yx35.dtbo
│   │       │   ├── nanopi-m6-spi-nor-flash.dtbo
│   │       │   ├── orangepi-5-ap6275p.dtbo
│   │       │   ├── orangepi-5-disable-led.dtbo
│   │       │   ├── orangepi-5-lcd1.dtbo
│   │       │   ├── orangepi-5-lcd2.dtbo
│   │       │   ├── orangepi-5-plus-disable-leds.dtbo
│   │       │   ├── orangepi-5-plus-hdmi2-8k.dtbo
│   │       │   ├── orangepi-5-plus-lcd.dtbo
│   │       │   ├── orangepi-5-plus-ov13850.dtbo
│   │       │   ├── orangepi-5-plus-ov13855.dtbo
│   │       │   ├── orangepi-5-plus-sata2.dtbo
│   │       │   ├── orangepi-5-pro-cam1.dtbo
│   │       │   ├── orangepi-5-pro-cam2.dtbo
│   │       │   ├── orangepi-5-pro-disable-leds.dtbo
│   │       │   ├── orangepi-5-pro-lcd.dtbo
│   │       │   ├── orangepi-5-pro-sfc.dtbo
│   │       │   ├── orangepi-5-sata.dtbo
│   │       │   ├── radxa-cm5-io-radxa-camera-4k.dtbo
│   │       │   ├── radxa-cm5-io-radxa-display-10hd.dtbo
│   │       │   ├── radxa-cm5-io-radxa-display-8hd.dtbo
│   │       │   ├── radxa-cm5-io-raspi-7inch-touchscreen.dtbo
│   │       │   ├── radxa-cm5-io-rpi-camera-v2.dtbo
│   │       │   ├── radxa-cm5-io-sata.dtbo
│   │       │   ├── radxa-nx5-io-rpi-camera-v2-cam0.dtbo
│   │       │   ├── radxa-nx5-io-rpi-camera-v2-cam1.dtbo
│   │       │   ├── radxa-zero3-disabled-ethernet.dtbo
│   │       │   ├── radxa-zero3-disabled-wireless.dtbo
│   │       │   ├── radxa-zero3-external-antenna.dtbo
│   │       │   ├── radxa-zero3-rpi-camera-v1.3.dtbo
│   │       │   ├── radxa-zero3-rpi-camera-v2.dtbo
│   │       │   ├── README.rockchip-overlays
│   │       │   ├── rk3528-rock-2-enable-pcie.dtbo
│   │       │   ├── rk3566-roc-pc-sata2.dtbo
│   │       │   ├── rk3568-can0-m0.dtbo
│   │       │   ├── rk3568-can1-m0.dtbo
│   │       │   ├── rk3568-can1-m1.dtbo
│   │       │   ├── rk3568-disable-fiq-debugger.dtbo
│   │       │   ├── rk3568-dwc3-host.dtbo
│   │       │   ├── rk3568-dwc3-otg.dtbo
│   │       │   ├── rk3568-dwc3-peripheral.dtbo
│   │       │   ├── rk3568-fiq-debugger-uart0.dtbo
│   │       │   ├── rk3568-fiq-debugger-uart2m0.dtbo
│   │       │   ├── rk3568-fiq-debugger-uart3m0.dtbo
│   │       │   ├── rk3568-fiq-debugger-uart4m1.dtbo
│   │       │   ├── rk3568-fiq-debugger-uart5m1.dtbo
│   │       │   ├── rk3568-fiq-debugger-uart7m1.dtbo
│   │       │   ├── rk3568-fiq-debugger-uart7m2.dtbo
│   │       │   ├── rk3568-fiq-debugger-uart8m1.dtbo
│   │       │   ├── rk3568-fiq-debugger-uart9m1.dtbo
│   │       │   ├── rk3568-gmac1-disable.dtbo
│   │       │   ├── rk3568-gmac1-enable.dtbo
│   │       │   ├── rk3568-i2c1.dtbo
│   │       │   ├── rk3568-i2c2-disable.dtbo
│   │       │   ├── rk3568-i2c2-m0.dtbo
│   │       │   ├── rk3568-i2c2-m0-pca9555.dtbo
│   │       │   ├── rk3568-i2c2-m1.dtbo
│   │       │   ├── rk3568-i2c3-m0.dtbo
│   │       │   ├── rk3568-i2c4-m0.dtbo
│   │       │   ├── rk3568-npu-disable.dtbo
│   │       │   ├── rk3568-pwm0-disable.dtbo
│   │       │   ├── rk3568-pwm0-m0.dtbo
│   │       │   ├── rk3568-pwm0-m1.dtbo
│   │       │   ├── rk3568-pwm11-m1.dtbo
│   │       │   ├── rk3568-pwm12-m0.dtbo
│   │       │   ├── rk3568-pwm12-m1.dtbo
│   │       │   ├── rk3568-pwm13-m0.dtbo
│   │       │   ├── rk3568-pwm13-m1.dtbo
│   │       │   ├── rk3568-pwm14-m0.dtbo
│   │       │   ├── rk3568-pwm14-m1.dtbo
│   │       │   ├── rk3568-pwm15-m0.dtbo
│   │       │   ├── rk3568-pwm15-m1.dtbo
│   │       │   ├── rk3568-pwm1-m0.dtbo
│   │       │   ├── rk3568-pwm1-m1.dtbo
│   │       │   ├── rk3568-pwm2-m0.dtbo
│   │       │   ├── rk3568-pwm2-m1.dtbo
│   │       │   ├── rk3568-pwm3.dtbo
│   │       │   ├── rk3568-pwm4.dtbo
│   │       │   ├── rk3568-pwm5.dtbo
│   │       │   ├── rk3568-pwm6.dtbo
│   │       │   ├── rk3568-pwm7.dtbo
│   │       │   ├── rk3568-pwm8-m0.dtbo
│   │       │   ├── rk3568-pwm9-m0.dtbo
│   │       │   ├── rk3568-serdes2-pcie.dtbo
│   │       │   ├── rk3568-serdes2-sata.dtbo
│   │       │   ├── rk3568-spi0-m0-cs0-spidev.dtbo
│   │       │   ├── rk3568-spi0-m1-cs0-spidev.dtbo
│   │       │   ├── rk3568-spi1-m1-cs0-spidev.dtbo
│   │       │   ├── rk3568-spi3-m0-cs0-mcp2515.dtbo
│   │       │   ├── rk3568-spi3-m0-cs0-spidev.dtbo
│   │       │   ├── rk3568-spi3-m0-cs1-spidev.dtbo
│   │       │   ├── rk3568-spi3-m1-cs0-enc28j60.dtbo
│   │       │   ├── rk3568-spi3-m1-cs0-mcp2515.dtbo
│   │       │   ├── rk3568-spi3-m1-cs0-mcp2515-gpio4_d1.dtbo
│   │       │   ├── rk3568-spi3-m1-cs0-spidev.dtbo
│   │       │   ├── rk3568-spi3-m1-cs1-spidev.dtbo
│   │       │   ├── rk3568-uart0.dtbo
│   │       │   ├── rk3568-uart1-m1-full.dtbo
│   │       │   ├── rk3568-uart2-m0.dtbo
│   │       │   ├── rk3568-uart3-m0.dtbo
│   │       │   ├── rk3568-uart3-m1.dtbo
│   │       │   ├── rk3568-uart4-m1.dtbo
│   │       │   ├── rk3568-uart5-m0-full.dtbo
│   │       │   ├── rk3568-uart5-m1.dtbo
│   │       │   ├── rk3568-uart7-m1.dtbo
│   │       │   ├── rk3568-uart7-m2.dtbo
│   │       │   ├── rk3568-uart8-m1.dtbo
│   │       │   ├── rk3568-uart9-m1.dtbo
│   │       │   ├── rk3568-w1-gpio3-a5.dtbo
│   │       │   ├── rk3568-w1-gpio3-d1.dtbo
│   │       │   ├── rk3576-can1-m1.dtbo
│   │       │   ├── rk3576-i2c0-m1.dtbo
│   │       │   ├── rk3576-i2c1-m0.dtbo
│   │       │   ├── rk3576-i2c2-m0.dtbo
│   │       │   ├── rk3576-i2c3-m0.dtbo
│   │       │   ├── rk3576-i2c4-m3.dtbo
│   │       │   ├── rk3576-i2c5-m3.dtbo
│   │       │   ├── rk3576-i2c6-m0.dtbo
│   │       │   ├── rk3576-i2c7-m1.dtbo
│   │       │   ├── rk3576-i2c8-m2.dtbo
│   │       │   ├── rk3576-pwm1-ch0-m3.dtbo
│   │       │   ├── rk3576-pwm2-ch6-m2.dtbo
│   │       │   ├── rk3576-pwm2-ch7-m2.dtbo
│   │       │   ├── rk3576-spi4-m0-cs1-spidev.dtbo
│   │       │   ├── rk3576-uart10-m2.dtbo
│   │       │   ├── rk3576-uart2-m2.dtbo
│   │       │   ├── rk3576-uart6-m3.dtbo
│   │       │   ├── rk3576-uart7-m0.dtbo
│   │       │   ├── rk3588-can0-m0.dtbo
│   │       │   ├── rk3588-can1-m0.dtbo
│   │       │   ├── rk3588-can1-m1.dtbo
│   │       │   ├── rk3588-can2-m1.dtbo
│   │       │   ├── rk3588-dwc3-host.dtbo
│   │       │   ├── rk3588-dwc3-peripheral.dtbo
│   │       │   ├── rk3588-hdmirx.dtbo
│   │       │   ├── rk3588-i2c0-m1.dtbo
│   │       │   ├── rk3588-i2c1-m0.dtbo
│   │       │   ├── rk3588-i2c1-m2.dtbo
│   │       │   ├── rk3588-i2c1-m4.dtbo
│   │       │   ├── rk3588-i2c2-m0.dtbo
│   │       │   ├── rk3588-i2c2-m4.dtbo
│   │       │   ├── rk3588-i2c3-m0.dtbo
│   │       │   ├── rk3588-i2c3-m1.dtbo
│   │       │   ├── rk3588-i2c4-m3.dtbo
│   │       │   ├── rk3588-i2c5-m3.dtbo
│   │       │   ├── rk3588-i2c6-m0.dtbo
│   │       │   ├── rk3588-i2c6-m3.dtbo
│   │       │   ├── rk3588-i2c6-m4.dtbo
│   │       │   ├── rk3588-i2c7-m3.dtbo
│   │       │   ├── rk3588-i2c8-m2.dtbo
│   │       │   ├── rk3588-i2c8-m4.dtbo
│   │       │   ├── rk3588-ov13850-c1.dtbo
│   │       │   ├── rk3588-ov13850-c2.dtbo
│   │       │   ├── rk3588-ov13850-c3.dtbo
│   │       │   ├── rk3588-ov13855-c1.dtbo
│   │       │   ├── rk3588-ov13855-c2.dtbo
│   │       │   ├── rk3588-ov13855-c3.dtbo
│   │       │   ├── rk3588-pwm0-m0.dtbo
│   │       │   ├── rk3588-pwm0-m1.dtbo
│   │       │   ├── rk3588-pwm0-m2.dtbo
│   │       │   ├── rk3588-pwm10-m0.dtbo
│   │       │   ├── rk3588-pwm11-m0.dtbo
│   │       │   ├── rk3588-pwm11-m1.dtbo
│   │       │   ├── rk3588-pwm12-m0.dtbo
│   │       │   ├── rk3588-pwm13-m0.dtbo
│   │       │   ├── rk3588-pwm13-m2.dtbo
│   │       │   ├── rk3588-pwm14-m0.dtbo
│   │       │   ├── rk3588-pwm14-m1.dtbo
│   │       │   ├── rk3588-pwm14-m2.dtbo
│   │       │   ├── rk3588-pwm15-m0.dtbo
│   │       │   ├── rk3588-pwm15-m1.dtbo
│   │       │   ├── rk3588-pwm15-m2.dtbo
│   │       │   ├── rk3588-pwm15-m3.dtbo
│   │       │   ├── rk3588-pwm1-m0.dtbo
│   │       │   ├── rk3588-pwm1-m1.dtbo
│   │       │   ├── rk3588-pwm1-m2.dtbo
│   │       │   ├── rk3588-pwm2-m1.dtbo
│   │       │   ├── rk3588-pwm3-m0.dtbo
│   │       │   ├── rk3588-pwm3-m1.dtbo
│   │       │   ├── rk3588-pwm3-m2.dtbo
│   │       │   ├── rk3588-pwm3-m3.dtbo
│   │       │   ├── rk3588-pwm5-m2.dtbo
│   │       │   ├── rk3588-pwm6-m0.dtbo
│   │       │   ├── rk3588-pwm6-m2.dtbo
│   │       │   ├── rk3588-pwm7-m0.dtbo
│   │       │   ├── rk3588-pwm7-m3.dtbo
│   │       │   ├── rk3588-pwm8-m0.dtbo
│   │       │   ├── rk3588-spi0-m1-cs0-spidev.dtbo
│   │       │   ├── rk3588-spi0-m1-cs1-spidev.dtbo
│   │       │   ├── rk3588-spi0-m2-cs0-cs1-spidev.dtbo
│   │       │   ├── rk3588-spi0-m2-cs0-spidev.dtbo
│   │       │   ├── rk3588-spi0-m2-cs1-spidev.dtbo
│   │       │   ├── rk3588-spi1-m1-cs0-spidev.dtbo
│   │       │   ├── rk3588-spi1-m1-cs1-mcp2515-8mhz.dtbo
│   │       │   ├── rk3588-spi1-m1-cs1-spidev.dtbo
│   │       │   ├── rk3588-spi4-m0-cs1-spidev.dtbo
│   │       │   ├── rk3588-spi4-m1-cs0-cs1-spidev.dtbo
│   │       │   ├── rk3588-spi4-m1-cs0-spidev.dtbo
│   │       │   ├── rk3588-spi4-m1-cs1-spidev.dtbo
│   │       │   ├── rk3588-spi4-m2-cs0-spidev.dtbo
│   │       │   ├── rk3588s-roc-pc-sata0.dtbo
│   │       │   ├── rk3588-uart0-m2.dtbo
│   │       │   ├── rk3588-uart1-m1.dtbo
│   │       │   ├── rk3588-uart2-m0.dtbo
│   │       │   ├── rk3588-uart2-m2.dtbo
│   │       │   ├── rk3588-uart3-m0.dtbo
│   │       │   ├── rk3588-uart3-m1.dtbo
│   │       │   ├── rk3588-uart4-m0.dtbo
│   │       │   ├── rk3588-uart4-m2.dtbo
│   │       │   ├── rk3588-uart6-m1.dtbo
│   │       │   ├── rk3588-uart6-m1-full.dtbo
│   │       │   ├── rk3588-uart7-m1.dtbo
│   │       │   ├── rk3588-uart7-m1-full.dtbo
│   │       │   ├── rk3588-uart7-m2.dtbo
│   │       │   ├── rk3588-uart8-m0.dtbo
│   │       │   ├── rk3588-uart8-m0-full.dtbo
│   │       │   ├── rk3588-uart8-m1.dtbo
│   │       │   ├── rk3588-w1-gpio3-b3.dtbo
│   │       │   ├── rk3588-w1-gpio4-b1.dtbo
│   │       │   ├── rock-3a-sata.dtbo
│   │       │   ├── rock-5a-hdmi-8k.dtbo
│   │       │   ├── rock-5a-i2c5-rtc-hym8563.dtbo
│   │       │   ├── rock-5a-radxa-camera-4k.dtbo
│   │       │   ├── rock-5a-radxa-display-10fhd.dtbo
│   │       │   ├── rock-5a-radxa-display-10hd.dtbo
│   │       │   ├── rock-5a-radxa-display-8hd.dtbo
│   │       │   ├── rock-5a-rpi-camera-v2.dtbo
│   │       │   ├── rock-5a-sata.dtbo
│   │       │   ├── rock-5a-spi-nor-flash.dtbo
│   │       │   ├── rock-5a-usb-otg.dtbo
│   │       │   ├── rock-5b-hdmi1-8k.dtbo
│   │       │   ├── rock-5b-hdmi2-8k.dtbo
│   │       │   ├── rock-5b-pd-max-voltage-12v.dtbo
│   │       │   ├── rock-5b-radxa-camera-4k.dtbo
│   │       │   ├── rock-5b-radxa-display-10fhd.dtbo
│   │       │   ├── rock-5b-radxa-display-10hd.dtbo
│   │       │   ├── rock-5b-radxa-display-8hd.dtbo
│   │       │   ├── rock-5b-rpi-camera-v2.dtbo
│   │       │   ├── rock-5b-sata.dtbo
│   │       │   ├── rock-5-itx-enable-sharp-lq133t1jw01-edp-lcd-disable-dp1.dtbo
│   │       │   ├── rock-5-itx-radxa-camera-4k-on-cam0.dtbo
│   │       │   ├── rock-5-itx-radxa-camera-4k-on-cam1.dtbo
│   │       │   ├── rock-5-itx-radxa-display-8hd-on-lcd0.dtbo
│   │       │   ├── rock-5-itx-radxa-display-8hd-on-lcd1.dtbo
│   │       │   ├── rockchip-rk3588-dmc-oc-3500mhz.dtbo
│   │       │   ├── rockchip-rk3588-opp-oc-24ghz.dtbo
│   │       │   ├── rockchip-rk3588-panthor-gpu.dtbo
│   │       │   ├── turing-rk1-sata2.dtbo
│   │       │   ├── yy3568-camera.dtbo
│   │       │   ├── yy3568-display-dsi0.dtbo
│   │       │   ├── yy3568-display-dsi1.dtbo
│   │       │   ├── yy3568-display-edp.dtbo
│   │       │   └── yy3568-sata2.dtbo
│   │       ├── px30-engicam-px30-core-ctouch2.dtb
│   │       ├── px30-engicam-px30-core-ctouch2-of10.dtb
│   │       ├── px30-engicam-px30-core-edimm2.2.dtb
│   │       ├── px30-evb-ddr3-v10-avb.dtb
│   │       ├── px30-evb-ddr3-v10.dtb
│   │       ├── px30-evb-ddr3-v10-linux.dtb
│   │       ├── px30-evb-ddr3-v11-linux.dtb
│   │       ├── px30-evb-ddr4-v10.dtb
│   │       ├── px30-evb-ddr4-v10-linux.dtb
│   │       ├── px30-evb.dtb
│   │       ├── px30-mini-evb-ddr3-v11-avb.dtb
│   │       ├── px30-mini-evb-ddr3-v11.dtb
│   │       ├── rk3308b-evb-amic-v10-amp.dtb
│   │       ├── rk3308b-evb-amic-v10.dtb
│   │       ├── rk3308bs-evb-amic-v11.dtb
│   │       ├── rk3308bs-evb-ddr3-v20-rk618-rgb2dsi.dtb
│   │       ├── rk3308bs-evb-dmic-pdm-v11.dtb
│   │       ├── rk3308bs-evb-mcu-display-v20.dtb
│   │       ├── rk3308bs-evb-mipi-display-v11.dtb
│   │       ├── rk3308bs-evb-rgb-display-v20.dtb
│   │       ├── rk3308-evb-amic-v11.dtb
│   │       ├── rk3308-evb-amic-v13.dtb
│   │       ├── rk3308-evb-audio-amic-v10.dtb
│   │       ├── rk3308-evb-audio-v10-display-rgb.dtb
│   │       ├── rk3308-evb-dmic-pdm-v11.dtb
│   │       ├── rk3308-evb-dmic-pdm-v13.dtb
│   │       ├── rk3308-evb.dtb
│   │       ├── rk3308-roc-cc.dtb
│   │       ├── rk3308-rock-pi-s.dtb
│   │       ├── rk3318-a95x-z2.dtb
│   │       ├── rk3326-863-lp3-v10-avb.dtb
│   │       ├── rk3326-863-lp3-v10.dtb
│   │       ├── rk3326-863-lp3-v10-rkisp1.dtb
│   │       ├── rk3326-evb-lp3-v10-avb.dtb
│   │       ├── rk3326-evb-lp3-v10.dtb
│   │       ├── rk3326-evb-lp3-v10-linux.dtb
│   │       ├── rk3326-evb-lp3-v11-avb.dtb
│   │       ├── rk3326-evb-lp3-v11.dtb
│   │       ├── rk3326-evb-lp3-v12-linux.dtb
│   │       ├── rk3326-odroid-go2.dtb
│   │       ├── rk3328-a1.dtb
│   │       ├── rk3328-evb.dtb
│   │       ├── rk3328-nanopi-r2s.dtb
│   │       ├── rk3328-roc-cc.dtb
│   │       ├── rk3328-rock64.dtb
│   │       ├── rk3328-rock-pi-e.dtb
│   │       ├── rk3328-roc-pc.dtb
│   │       ├── rk3358-evb-ddr3-v10-linux.dtb
│   │       ├── rk3358m-automotive-ddr3-v11-linux.dtb
│   │       ├── rk3358m-vehicle-v10.dtb
│   │       ├── rk3368-evb-act8846.dtb
│   │       ├── rk3368-geekbox.dtb
│   │       ├── rk3368-lion-haikou.dtb
│   │       ├── rk3368-orion-r68-meta.dtb
│   │       ├── rk3368-px5-evb.dtb
│   │       ├── rk3368-r88.dtb
│   │       ├── rk3399-eaidk-610.dtb
│   │       ├── rk3399-evb.dtb
│   │       ├── rk3399-ficus.dtb
│   │       ├── rk3399-firefly.dtb
│   │       ├── rk3399-gru-bob.dtb
│   │       ├── rk3399-gru-kevin.dtb
│   │       ├── rk3399-gru-scarlet-dumo.dtb
│   │       ├── rk3399-gru-scarlet-inx.dtb
│   │       ├── rk3399-gru-scarlet-kd.dtb
│   │       ├── rk3399-hugsun-x99.dtb
│   │       ├── rk3399-khadas-edge-captain.dtb
│   │       ├── rk3399-khadas-edge.dtb
│   │       ├── rk3399-khadas-edge-v.dtb
│   │       ├── rk3399-kobol-helios64.dtb
│   │       ├── rk3399-leez-p710.dtb
│   │       ├── rk3399-nanopc-t4.dtb
│   │       ├── rk3399-nanopi-m4b.dtb
│   │       ├── rk3399-nanopi-m4.dtb
│   │       ├── rk3399-nanopi-neo4.dtb
│   │       ├── rk3399-nanopi-r4s.dtb
│   │       ├── rk3399-nanopi-r4s-enterprise.dtb
│   │       ├── rk3399-orangepi.dtb
│   │       ├── rk3399-pinebook-pro.dtb
│   │       ├── rk3399-pinephone-pro.dtb
│   │       ├── rk3399pro-rock-pi-n10.dtb
│   │       ├── rk3399-puma-haikou.dtb
│   │       ├── rk3399-rock-4c-plus.dtb
│   │       ├── rk3399-rock960.dtb
│   │       ├── rk3399-rock-pi-4a.dtb
│   │       ├── rk3399-rock-pi-4a-plus.dtb
│   │       ├── rk3399-rock-pi-4b.dtb
│   │       ├── rk3399-rock-pi-4b-plus.dtb
│   │       ├── rk3399-rock-pi-4c.dtb
│   │       ├── rk3399-rockpro64.dtb
│   │       ├── rk3399-rockpro64-v2.dtb
│   │       ├── rk3399-roc-pc.dtb
│   │       ├── rk3399-roc-pc-mezzanine.dtb
│   │       ├── rk3399-roc-pc-plus.dtb
│   │       ├── rk3399-sapphire.dtb
│   │       ├── rk3399-sapphire-excavator.dtb
│   │       ├── rk3399-sapphire-excavator-edp-avb.dtb
│   │       ├── rk3528-armsom-sige1.dtb
│   │       ├── rk3528-demo1-lp4-v10.dtb
│   │       ├── rk3528-demo4-ddr4-v10.dtb
│   │       ├── rk3528-demo4-ddr4-v10-linux.dtb
│   │       ├── rk3528-demo6-ddr3-v10.dtb
│   │       ├── rk3528-evb1-ddr4-v10.dtb
│   │       ├── rk3528-evb1-ddr4-v10-linux.dtb
│   │       ├── rk3528-evb1-ddr4-v10-spi-nand-linux.dtb
│   │       ├── rk3528-evb2-ddr3-v10.dtb
│   │       ├── rk3528-evb3-lp4x-v10.dtb
│   │       ├── rk3528-evb4-ddr4-v10.dtb
│   │       ├── rk3528-hinlink-h28k.dtb
│   │       ├── rk3528-hinlink-ht2.dtb
│   │       ├── rk3528-iotest-lp3-v10.dtb
│   │       ├── rk3528-mangopi-m28k.dtb
│   │       ├── rk3528-radxa-e20c.dtb
│   │       ├── rk3528-rock-2a.dtb
│   │       ├── rk3528-rock-2f.dtb
│   │       ├── rk3562-dictpen-test3-v20.dtb
│   │       ├── rk3562-evb1-lp4x-v10.dtb
│   │       ├── rk3562-evb1-lp4x-v10-linux-amp.dtb
│   │       ├── rk3562-evb1-lp4x-v10-linux.dtb
│   │       ├── rk3562-evb1-lp4x-v10-lvds.dtb
│   │       ├── rk3562-evb1-lp4x-v10-mcu-k350c4516t.dtb
│   │       ├── rk3562-evb1-lp4x-v10-rgb2lvds.dtb
│   │       ├── rk3562-evb1-lp4x-v10-rgb-FX070-DHM11BOE-A.dtb
│   │       ├── rk3562-evb1-lp4x-v10-rgb-k350c4516t.dtb
│   │       ├── rk3562-evb1-lp4x-v10-rgb-Q7050ITH2641AA1T.dtb
│   │       ├── rk3562-evb1-lp4x-v10-sii9022-bt1120-to-hdmi.dtb
│   │       ├── rk3562-evb1-lp4x-v10-sii9022-rgb2hdmi.dtb
│   │       ├── rk3562-evb1-lp4x-v10-spdif.dtb
│   │       ├── rk3562-evb2-ddr4-v10.dtb
│   │       ├── rk3562-evb2-ddr4-v10-dual-camera.dtb
│   │       ├── rk3562-evb2-ddr4-v10-image-reverse.dtb
│   │       ├── rk3562-evb2-ddr4-v10-linux-amp.dtb
│   │       ├── rk3562-evb2-ddr4-v10-linux.dtb
│   │       ├── rk3562-evb2-ddr4-v10-pdm-mic-array.dtb
│   │       ├── rk3562-evb2-ddr4-v10-sii9022-bt1120-to-hdmi.dtb
│   │       ├── rk3562-iotest-lp3-v10-dsm.dtb
│   │       ├── rk3562-iotest-lp3-v10.dtb
│   │       ├── rk3562-iotest-lp3-v10-linux.dtb
│   │       ├── rk3562j-core-ddr4-v10.dtb
│   │       ├── rk3562-rk817-tablet-v10.dtb
│   │       ├── rk3562-test1-ddr3-v10.dtb
│   │       ├── rk3562-test2-ddr4-v10.dtb
│   │       ├── rk3562-toybrick-android.dtb
│   │       ├── rk3562-toybrick-linux.dtb
│   │       ├── rk3566-box-demo-v10.dtb
│   │       ├── rk3566-evb1-ddr4-v10.dtb
│   │       ├── rk3566-evb1-ddr4-v10-linux.dtb
│   │       ├── rk3566-evb1-ddr4-v10-lvds.dtb
│   │       ├── rk3566-evb2-lp4x-v10.dtb
│   │       ├── rk3566-evb2-lp4x-v10-edp.dtb
│   │       ├── rk3566-evb2-lp4x-v10-eink.dtb
│   │       ├── rk3566-evb2-lp4x-v10-i2s-mic-array.dtb
│   │       ├── rk3566-evb2-lp4x-v10-linux.dtb
│   │       ├── rk3566-evb2-lp4x-v10-pdm-mic-array.dtb
│   │       ├── rk3566-evb3-ddr3-v10.dtb
│   │       ├── rk3566-evb3-ddr3-v10-linux.dtb
│   │       ├── rk3566-evb5-lp4x-v10.dtb
│   │       ├── rk3566-evb-mipitest-v10.dtb
│   │       ├── rk3566-h96max-v56.dtb
│   │       ├── rk3566-luckfox-core3566.dtb
│   │       ├── rk3566-nanopi-r3-rev01.dtb
│   │       ├── rk3566-orangepi-3b.dtb
│   │       ├── rk3566-orangepi-3b-v1.1.dtb
│   │       ├── rk3566-orangepi-3b-v2.1.dtb
│   │       ├── rk3566-radxa-zero3-ap6212.dtb
│   │       ├── rk3566-radxa-zero3.dtb
│   │       ├── rk3566-rk817-eink.dtb
│   │       ├── rk3566-rk817-eink-w103.dtb
│   │       ├── rk3566-rk817-eink-w6.dtb
│   │       ├── rk3566-rk817-tablet.dtb
│   │       ├── rk3566-rk817-tablet-k108.dtb
│   │       ├── rk3566-rk817-tablet-rkg11.dtb
│   │       ├── rk3566-rk817-tablet-v10.dtb
│   │       ├── rk3566-taishanpi-v10.dtb
│   │       ├── rk3567-evb2-lp4x-v10.dtb
│   │       ├── rk3567-evb2-lp4x-v10-dual-channel-lvds.dtb
│   │       ├── rk3567-evb2-lp4x-v10-one-vp-two-single-channel-lvds.dtb
│   │       ├── rk3567-evb2-lp4x-v10-single-channel-lvds.dtb
│   │       ├── rk3567-evb2-lp4x-v10-two-vp-two-separate-single-channel-lvds.dtb
│   │       ├── rk3568-armsom-sige3.dtb
│   │       ├── rk3568-dshapi-r1.dtb
│   │       ├── rk3568-evb1-ddr4-v10.dtb
│   │       ├── rk3568-evb1-ddr4-v10-dual-camera.dtb
│   │       ├── rk3568-evb1-ddr4-v10-edp-panel.dtb
│   │       ├── rk3568-evb1-ddr4-v10-linux-amp.dtb
│   │       ├── rk3568-evb1-ddr4-v10-linux.dtb
│   │       ├── rk3568-evb1-ddr4-v10-linux-spi-nor.dtb
│   │       ├── rk3568-evb1-ddr4-v10-one-vp-two-single-channel-lvds.dtb
│   │       ├── rk3568-evb1-ddr4-v10-one-vp-two-single-channel-lvds-linux.dtb
│   │       ├── rk3568-evb1-ddr4-v10-single-channel-lvds.dtb
│   │       ├── rk3568-evb1-ddr4-v10-two-vp-two-separate-single-channel-lvds.dtb
│   │       ├── rk3568-evb2-lp4x-v10-bt1120-to-hdmi.dtb
│   │       ├── rk3568-evb2-lp4x-v10.dtb
│   │       ├── rk3568-evb4-lp3-v10.dtb
│   │       ├── rk3568-evb5-ddr4-v10.dtb
│   │       ├── rk3568-evb6-ddr3-v10.dtb
│   │       ├── rk3568-evb6-ddr3-v10-linux.dtb
│   │       ├── rk3568-evb6-ddr3-v10-rk630-bt656-to-cvbs.dtb
│   │       ├── rk3568-evb7-ddr4-v10.dtb
│   │       ├── rk3568-evb8-lp4-v10.dtb
│   │       ├── rk3568-evb8-lp4-v10-linux.dtb
│   │       ├── rk3568-evb-rk628-hdmi2bt1120-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-hdmi2dsi-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-hdmi2dsi-dual-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-hdmi2gvi-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-hdmi2lvds-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-hdmi2lvds-dual-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-rgb2dsi-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-rgb2gvi-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-rgb2hdmi-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-rgb2lvds-ddr4-v10.dtb
│   │       ├── rk3568-evb-rk628-rgb2lvds-dual-ddr4-v10.dtb
│   │       ├── rk3568-hinlink-h66k.dtb
│   │       ├── rk3568-hinlink-h68k.dtb
│   │       ├── rk3568-hinlink-hnas.dtb
│   │       ├── rk3568-iotest-ddr3-v10.dtb
│   │       ├── rk3568-iotest-ddr3-v10-linux.dtb
│   │       ├── rk3568-mixtile-edge2.dtb
│   │       ├── rk3568m-serdes-evb-camera-csi-v10.dtb
│   │       ├── rk3568m-serdes-evb-camera-dvp-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-dsi0-command2dsi-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-dsi0-command2lvds0-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-dsi0-command2rgb-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-dsi1-command2dsi-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-dsi1-command2lvds0-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-dsi1-command2rgb-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-lvds2lvds-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-lvds2rgb-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-rgb2dsi-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-rgb2lvds-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-evb-display-rgb2rgb-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-dsi0-command2dsi-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-dsi0-command2dual_lvds-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-dsi0-command2lvds0-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-dsi0-dsi1-command2dual_lvdsx2-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-dsi1-command2dsi-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-dsi1-command2dual_lvds-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-dsi1-command2lvds0-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-lvds2dsi-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-lvds2dual-lvds-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-lvds2dual-lvds-vehicle-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-lvds2lvds-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-lvds2rgb-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-rgb2dsi-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-rgb2dual-lvds-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-rgb2dual-lvds-vehicle-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-rgb2lvds-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-rgb2rgb-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-super-frame-dsi0-command2dsi-lp4x-v10.dtb
│   │       ├── rk3568m-serdes-v1-evb-display-super-frame-dsi0-command2lvds0-lp4x-v10.dtb
│   │       ├── rk3568-nanopi5-rev01.dtb
│   │       ├── rk3568-nanopi5-rev02.dtb
│   │       ├── rk3568-nanopi5-rev03.dtb
│   │       ├── rk3568-nanopi5-rev04.dtb
│   │       ├── rk3568-nanopi5-rev05.dtb
│   │       ├── rk3568-nanopi5-rev07.dtb
│   │       ├── rk3568-nvr-demo-v10.dtb
│   │       ├── rk3568-nvr-demo-v10-linux.dtb
│   │       ├── rk3568-nvr-demo-v10-linux-spi-nand.dtb
│   │       ├── rk3568-nvr-demo-v12-linux.dtb
│   │       ├── rk3568-nvr-demo-v12-linux-spi-nand.dtb
│   │       ├── rk3568-odroid-m1.dtb
│   │       ├── rk3568-ok3568c.dtb
│   │       ├── rk3568-pcie-ep-lp4x-v10-linux.dtb
│   │       ├── rk3568-radxa-e25.dtb
│   │       ├── rk3568-rock-3a.dtb
│   │       ├── rk3568-swan1-w28.dtb
│   │       ├── rk3568-toybrick-sd0-android.dtb
│   │       ├── rk3568-toybrick-sd0-linux.dtb
│   │       ├── rk3568-toybrick-x0-android.dtb
│   │       ├── rk3568-toybrick-x0-linux.dtb
│   │       ├── rk3568-yy3568.dtb
│   │       ├── rk3576-armsom-cm5-io.dtb
│   │       ├── rk3576-armsom-cm5-rpi-cm4-io.dtb
│   │       ├── rk3576-armsom-sige5.dtb
│   │       ├── rk3576-blueberry-edge-v10.dtb
│   │       ├── rk3576-ebook-color-v10.dtb
│   │       ├── rk3576-ebook-v10.dtb
│   │       ├── rk3576-ebook-x3-v10.dtb
│   │       ├── rk3576-evb1-v10-android9.dtb
│   │       ├── rk3576-evb1-v10.dtb
│   │       ├── rk3576-evb1-v10-edp-NV140QUM-N61.dtb
│   │       ├── rk3576-evb1-v10-hdmi2dp.dtb
│   │       ├── rk3576-evb1-v10-image-reverse-demo.dtb
│   │       ├── rk3576-evb1-v10-ipc-4x-linux.dtb
│   │       ├── rk3576-evb1-v10-ipc-dual-cam-linux.dtb
│   │       ├── rk3576-evb1-v10-linux-amp.dtb
│   │       ├── rk3576-evb1-v10-linux.dtb
│   │       ├── rk3576-evb1-v10-lontium-hdmiin.dtb
│   │       ├── rk3576-evb1-v10-nvp6324-ahd2csi.dtb
│   │       ├── rk3576-evb1-v10-pdm.dtb
│   │       ├── rk3576-evb1-v10-rk621-hdmi2csi.dtb
│   │       ├── rk3576-evb1-v10-rk628-hdmi2csi.dtb
│   │       ├── rk3576-evb1-v10-tp2815-ahd2csi.dtb
│   │       ├── rk3576-evb2-v10.dtb
│   │       ├── rk3576-evb2-v10-linux.dtb
│   │       ├── rk3576-industry-evb-v10.dtb
│   │       ├── rk3576-iotest-v10.dtb
│   │       ├── rk3576-iotest-v10-edp2dp.dtb
│   │       ├── rk3576-iotest-v10-linux.dtb
│   │       ├── rk3576-nvr-v10.dtb
│   │       ├── rk3576s-evb1-v10.dtb
│   │       ├── rk3576s-evb1-v10-linux.dtb
│   │       ├── rk3576s-tablet-v10.dtb
│   │       ├── rk3576-tablet-v10.dtb
│   │       ├── rk3576-tablet-v11.dtb
│   │       ├── rk3576-test1-v10.dtb
│   │       ├── rk3576-test1-v10-eink.dtb
│   │       ├── rk3576-test1-v10-linux.dtb
│   │       ├── rk3576-test1-v10-mcu-k350c4516t.dtb
│   │       ├── rk3576-test1-v10-rgb-Q7050ITH2641AA1T.dtb
│   │       ├── rk3576-test1-v10-rk628-bt1120-2-hdmi.dtb
│   │       ├── rk3576-test1-v10-rk628-hdmi2gvi.dtb
│   │       ├── rk3576-test1-v10-sii9022-bt1120-to-hdmi.dtb
│   │       ├── rk3576-test1-v10-sii9022-rgb2hdmi.dtb
│   │       ├── rk3576-test1-v10-vopl-mipi-display-linux.dtb
│   │       ├── rk3576-test2-v10.dtb
│   │       ├── rk3576-test2-v10-linux.dtb
│   │       ├── rk3576-test3-v10.dtb
│   │       ├── rk3576-test5-v10.dtb
│   │       ├── rk3576-vehicle-evb-v10.dtb
│   │       ├── rk3576-vehicle-evb-v10-linux.dtb
│   │       ├── rk3576-vehicle-evb-v20.dtb
│   │       ├── rk3576-vehicle-evb-v20-linux.dtb
│   │       ├── rk3588-armsom-aim7-io.dtb
│   │       ├── rk3588-armsom-sige7.dtb
│   │       ├── rk3588-armsom-w3.dtb
│   │       ├── rk3588-bananapi-m7.dtb
│   │       ├── rk3588-blade3-v101-linux.dtb
│   │       ├── rk3588-blueberry-edge-v10-linux.dtb
│   │       ├── rk3588-blueberry-edge-v12-linux.dtb
│   │       ├── rk3588-blueberry-edge-v12-maizhuo-linux.dtb
│   │       ├── rk3588-blueberry-edge-v14-linux.dtb
│   │       ├── rk3588-blueberry-minipc-linux.dtb
│   │       ├── rk3588-blueberry-minipc-mizhuo-linux.dtb
│   │       ├── rk3588-coolpi-cm5-genbook.dtb
│   │       ├── rk3588-cyber-aib.dtb
│   │       ├── rk3588-evb1-lp4-v10-dsi-dsc-MV2100UZ1.dtb
│   │       ├── rk3588-evb1-lp4-v10.dtb
│   │       ├── rk3588-evb1-lp4-v10-edp-8lanes-M280DCA.dtb
│   │       ├── rk3588-evb1-lp4-v10-edp-NV140QUM-N61.dtb
│   │       ├── rk3588-evb1-lp4-v10-hdmi2dp.dtb
│   │       ├── rk3588-evb1-lp4-v10-ipc-6x-linux.dtb
│   │       ├── rk3588-evb1-lp4-v10-linux-amp.dtb
│   │       ├── rk3588-evb1-lp4-v10-linux.dtb
│   │       ├── rk3588-evb1-lp4-v10-linux-ipc.dtb
│   │       ├── rk3588-evb1-lp4-v10-lt6911uxc-dual-mipi.dtb
│   │       ├── rk3588-evb1-lp4-v10-lt6911uxe.dtb
│   │       ├── rk3588-evb1-lp4-v10-rk628-hdmi2csi.dtb
│   │       ├── rk3588-evb2-lp4-v10.dtb
│   │       ├── rk3588-evb2-lp4-v10-edp2dp.dtb
│   │       ├── rk3588-evb2-lp4-v10-edp.dtb
│   │       ├── rk3588-evb2-lp4-v10-linux.dtb
│   │       ├── rk3588-evb3-lp5-v10.dtb
│   │       ├── rk3588-evb3-lp5-v10-edp.dtb
│   │       ├── rk3588-evb3-lp5-v10-edp-linux.dtb
│   │       ├── rk3588-evb3-lp5-v10-linux.dtb
│   │       ├── rk3588-evb4-lp4-v10.dtb
│   │       ├── rk3588-evb4-lp4-v10-linux.dtb
│   │       ├── rk3588-evb5-lp4-v10.dtb
│   │       ├── rk3588-evb5-lp4-v10-linux.dtb
│   │       ├── rk3588-evb6-lp4-v10.dtb
│   │       ├── rk3588-evb6-lp4-v10-linux.dtb
│   │       ├── rk3588-evb7-lp4-v10.dtb
│   │       ├── rk3588-evb7-lp4-v10-linux.dtb
│   │       ├── rk3588-evb7-lp4-v10-rk1608-ipc-8x-linux.dtb
│   │       ├── rk3588-evb7-lp4-v11-linux-ipc.dtb
│   │       ├── rk3588-evb7-v11.dtb
│   │       ├── rk3588-evb7-v11-linux.dtb
│   │       ├── rk3588-evb7-v11-rk628-hdmi2csi.dtb
│   │       ├── rk3588-firefly-itx-3588j.dtb
│   │       ├── rk3588-friendlyelec-cm3588-nas.dtb
│   │       ├── rk3588-fxblox-rk1.dtb
│   │       ├── rk3588-hinlink-h88k.dtb
│   │       ├── rk3588-mixtile-core3588e.dtb
│   │       ├── rk3588-nanopc-cm3588-nas.dtb
│   │       ├── rk3588-nanopc-t6.dtb
│   │       ├── rk3588-nanopc-t6-lts.dtb
│   │       ├── rk3588-nvr-demo1-v21-android.dtb
│   │       ├── rk3588-nvr-demo1-v21.dtb
│   │       ├── rk3588-nvr-demo3-v10-android.dtb
│   │       ├── rk3588-nvr-demo3-v10.dtb
│   │       ├── rk3588-nvr-demo-v10-android.dtb
│   │       ├── rk3588-nvr-demo-v10.dtb
│   │       ├── rk3588-nvr-demo-v10-ipc-4x-linux.dtb
│   │       ├── rk3588-nvr-demo-v10-spi-nand.dtb
│   │       ├── rk3588-orangepi-5-max.dtb
│   │       ├── rk3588-orangepi-5-plus.dtb
│   │       ├── rk3588-pcie-ep-demo-v11.dtb
│   │       ├── rk3588-pcie-ep-demo-v11-linux.dtb
│   │       ├── rk3588-radxa-rock-5b+.dtb
│   │       ├── rk3588-rock-5b.dtb
│   │       ├── rk3588-rock-5-itx.dtb
│   │       ├── rk3588-rock-5t.dtb
│   │       ├── rk3588s-9tripod-linux.dtb
│   │       ├── rk3588s-evb1-lp4x-v10.dtb
│   │       ├── rk3588s-evb1-lp4x-v10-linux.dtb
│   │       ├── rk3588s-evb2-lp5-v10.dtb
│   │       ├── rk3588s-evb2-lp5-v10-linux.dtb
│   │       ├── rk3588s-evb3-lp4x-v10.dtb
│   │       ├── rk3588s-evb3-lp4x-v10-linux.dtb
│   │       ├── rk3588s-evb3-lp4x-v10-nvp6158-ahd-to-bt1120.dtb
│   │       ├── rk3588s-evb3-lp4x-v10-rk630-bt656-to-cvbs.dtb
│   │       ├── rk3588s-evb3-lp4x-v10-sii9022-bt1120-to-hdmi.dtb
│   │       ├── rk3588s-evb4-lp4x-v10.dtb
│   │       ├── rk3588s-evb4-lp4x-v10-linux.dtb
│   │       ├── rk3588s-evb8-lp4x-v10.dtb
│   │       ├── rk3588s-khadas-edge2.dtb
│   │       ├── rk3588s-lubancat-4.dtb
│   │       ├── rk3588-smart-am60.dtb
│   │       ├── rk3588s-nanopi-m6.dtb
│   │       ├── rk3588s-nanopi-r6c.dtb
│   │       ├── rk3588s-nanopi-r6s.dtb
│   │       ├── rk3588-som3588-cat.dtb
│   │       ├── rk3588s-orangepi-5b.dtb
│   │       ├── rk3588s-orangepi-5.dtb
│   │       ├── rk3588s-orangepi-5-pro.dtb
│   │       ├── rk3588s-radxa-cm5-io.dtb
│   │       ├── rk3588s-radxa-cm5-rpi-cm4-io.dtb
│   │       ├── rk3588s-radxa-e52c.dtb
│   │       ├── rk3588s-radxa-nx5-io.dtb
│   │       ├── rk3588s-retroled-cm5.dtb
│   │       ├── rk3588s-retro-lite-cm5.dtb
│   │       ├── rk3588s-rock-5a.dtb
│   │       ├── rk3588s-rock-5c.dtb
│   │       ├── rk3588s-roc-pc.dtb
│   │       ├── rk3588s-tablet-rk806-single-v10.dtb
│   │       ├── rk3588s-tablet-v10.dtb
│   │       ├── rk3588s-tablet-v11.dtb
│   │       ├── rk3588s-youyeetoo-r1.dtb
│   │       ├── rk3588-toybrick-x0-android.dtb
│   │       ├── rk3588-toybrick-x0-linux.dtb
│   │       ├── rk3588-turing-rk1.dtb
│   │       ├── rk3588-vehicle-evb-v10.dtb
│   │       ├── rk3588-vehicle-evb-v20.dtb
│   │       ├── rk3588-vehicle-evb-v21.dtb
│   │       ├── rk3588-vehicle-evb-v22.dtb
│   │       ├── rk3588-vehicle-evb-v23.dtb
│   │       ├── rk3588-vehicle-s66-v10.dtb
│   │       └── rk3588-yx-imb3588.dtb
│   ├── Image -> vmlinuz-6.1.115-vendor-rk35xx
│   ├── initrd.img-6.1.115-vendor-rk35xx
│   ├── System.map-6.1.115-vendor-rk35xx
│   ├── uInitrd -> uInitrd-6.1.115-vendor-rk35xx
│   ├── uInitrd-6.1.115-vendor-rk35xx
│   └── vmlinuz-6.1.115-vendor-rk35xx
├── dev
│   ├── autofs
│   ├── block
│   │   ├── 1:0 -> ../ram0
│   │   ├── 252:0 -> ../zram0
│   │   ├── 252:1 -> ../zram1
│   │   ├── 252:2 -> ../zram2
│   │   ├── 259:0 -> ../nvme0n1
│   │   ├── 259:1 -> ../nvme0n1p1
│   │   ├── 31:0 -> ../mtdblock0
│   │   ├── 7:0 -> ../loop0
│   │   ├── 7:1 -> ../loop1
│   │   ├── 7:2 -> ../loop2
│   │   ├── 7:3 -> ../loop3
│   │   ├── 7:4 -> ../loop4
│   │   ├── 7:5 -> ../loop5
│   │   ├── 7:6 -> ../loop6
│   │   ├── 7:7 -> ../loop7
│   │   ├── 7:8 -> ../loop8
│   │   └── 7:9 -> ../loop9
│   ├── btrfs-control
│   ├── bus
│   │   └── usb
│   │       ├── 001
│   │       │   ├── 001
│   │       │   ├── 002
│   │       │   ├── 003
│   │       │   └── 004
│   │       ├── 002
│   │       │   ├── 001
│   │       │   └── 002
│   │       ├── 003
│   │       │   └── 001
│   │       ├── 004
│   │       │   └── 001
│   │       ├── 005
│   │       │   └── 001
│   │       └── 006
│   │           └── 001
│   ├── cec0
│   ├── cec1
│   ├── char
│   │   ├── 10:1 -> ../psaux
│   │   ├── 10:119 -> ../ubi_ctrl
│   │   ├── 10:120 -> ../mali0
│   │   ├── 10:121 -> ../iomux
│   │   ├── 10:122 -> ../rga
│   │   ├── 10:123 -> ../cpu_dma_latency
│   │   ├── 10:124 -> ../crypto
│   │   ├── 10:125 -> ../rkspi-dev2
│   │   ├── 10:126 -> ../sw_sync
│   │   ├── 10:127 -> ../vga_arbiter
│   │   ├── 10:130 -> ../watchdog
│   │   ├── 10:183 -> ../hwrng
│   │   ├── 10:196 -> ../vfio/vfio
│   │   ├── 10:223 -> ../uinput
│   │   ├── 10:229 -> ../fuse
│   │   ├── 10:232 -> ../kvm
│   │   ├── 10:234 -> ../btrfs-control
│   │   ├── 10:235 -> ../autofs
│   │   ├── 10:236 -> ../mapper/control
│   │   ├── 10:237 -> ../loop-control
│   │   ├── 10:239 -> ../uhid
│   │   ├── 10:242 -> ../rfkill
│   │   ├── 1:1 -> ../mem
│   │   ├── 1:11 -> ../kmsg
│   │   ├── 116:1 -> ../snd/seq
│   │   ├── 116:10 -> ../snd/controlC3
│   │   ├── 116:2 -> ../snd/pcmC0D0p
│   │   ├── 116:3 -> ../snd/controlC0
│   │   ├── 116:33 -> ../snd/timer
│   │   ├── 116:4 -> ../snd/pcmC1D0p
│   │   ├── 116:5 -> ../snd/controlC1
│   │   ├── 116:6 -> ../snd/pcmC2D0p
│   │   ├── 116:7 -> ../snd/controlC2
│   │   ├── 116:8 -> ../snd/pcmC3D0p
│   │   ├── 116:9 -> ../snd/pcmC3D0c
│   │   ├── 1:3 -> ../null
│   │   ├── 13:32 -> ../input/mouse0
│   │   ├── 13:33 -> ../input/mouse1
│   │   ├── 13:63 -> ../input/mice
│   │   ├── 13:64 -> ../input/event0
│   │   ├── 13:65 -> ../input/event1
│   │   ├── 13:66 -> ../input/event2
│   │   ├── 13:67 -> ../input/event3
│   │   ├── 13:68 -> ../input/event4
│   │   ├── 13:69 -> ../input/event5
│   │   ├── 13:70 -> ../input/event6
│   │   ├── 13:71 -> ../input/event7
│   │   ├── 13:72 -> ../input/event8
│   │   ├── 13:73 -> ../input/event9
│   │   ├── 13:74 -> ../input/event10
│   │   ├── 13:75 -> ../input/event11
│   │   ├── 13:76 -> ../input/event12
│   │   ├── 13:77 -> ../input/event13
│   │   ├── 13:78 -> ../input/event14
│   │   ├── 13:79 -> ../input/event15
│   │   ├── 13:80 -> ../input/event16
│   │   ├── 1:4 -> ../port
│   │   ├── 1:5 -> ../zero
│   │   ├── 1:7 -> ../full
│   │   ├── 1:8 -> ../random
│   │   ├── 180:96 -> ../usb/hiddev0
│   │   ├── 189:0 -> ../bus/usb/001/001
│   │   ├── 189:1 -> ../bus/usb/001/002
│   │   ├── 189:128 -> ../bus/usb/002/001
│   │   ├── 189:129 -> ../bus/usb/002/002
│   │   ├── 189:2 -> ../bus/usb/001/003
│   │   ├── 189:256 -> ../bus/usb/003/001
│   │   ├── 189:3 -> ../bus/usb/001/004
│   │   ├── 189:384 -> ../bus/usb/004/001
│   │   ├── 189:512 -> ../bus/usb/005/001
│   │   ├── 189:640 -> ../bus/usb/006/001
│   │   ├── 1:9 -> ../urandom
│   │   ├── 226:0 -> ../dri/card0
│   │   ├── 226:1 -> ../dri/card1
│   │   ├── 226:128 -> ../dri/renderD128
│   │   ├── 226:129 -> ../dri/renderD129
│   │   ├── 237:0 -> ../ng0n1
│   │   ├── 238:0 -> ../nvme0
│   │   ├── 239:0 -> ../drm_dp_aux0
│   │   ├── 240:0 -> ../mpp_service
│   │   ├── 242:0 -> ../watchdog0
│   │   ├── 244:0 -> ../iio:device0
│   │   ├── 247:0 -> ../cec0
│   │   ├── 247:1 -> ../cec1
│   │   ├── 250:0 -> ../rtc0
│   │   ├── 251:0 -> ../dma_heap/system
│   │   ├── 251:1 -> ../dma_heap/system-uncached
│   │   ├── 251:2 -> ../dma_heap/reserved
│   │   ├── 253:0 -> ../ttyFIQ0
│   │   ├── 254:0 -> ../gpiochip0
│   │   ├── 254:1 -> ../gpiochip1
│   │   ├── 254:2 -> ../gpiochip2
│   │   ├── 254:3 -> ../gpiochip3
│   │   ├── 254:4 -> ../gpiochip4
│   │   ├── 254:5 -> ../gpiochip5
│   │   ├── 29:0 -> ../fb0
│   │   ├── 4:0 -> ../tty0
│   │   ├── 4:1 -> ../tty1
│   │   ├── 4:10 -> ../tty10
│   │   ├── 4:11 -> ../tty11
│   │   ├── 4:12 -> ../tty12
│   │   ├── 4:13 -> ../tty13
│   │   ├── 4:14 -> ../tty14
│   │   ├── 4:15 -> ../tty15
│   │   ├── 4:16 -> ../tty16
│   │   ├── 4:17 -> ../tty17
│   │   ├── 4:18 -> ../tty18
│   │   ├── 4:19 -> ../tty19
│   │   ├── 4:2 -> ../tty2
│   │   ├── 4:20 -> ../tty20
│   │   ├── 4:21 -> ../tty21
│   │   ├── 4:22 -> ../tty22
│   │   ├── 4:23 -> ../tty23
│   │   ├── 4:24 -> ../tty24
│   │   ├── 4:25 -> ../tty25
│   │   ├── 4:26 -> ../tty26
│   │   ├── 4:27 -> ../tty27
│   │   ├── 4:28 -> ../tty28
│   │   ├── 4:29 -> ../tty29
│   │   ├── 4:3 -> ../tty3
│   │   ├── 4:30 -> ../tty30
│   │   ├── 4:31 -> ../tty31
│   │   ├── 4:32 -> ../tty32
│   │   ├── 4:33 -> ../tty33
│   │   ├── 4:34 -> ../tty34
│   │   ├── 4:35 -> ../tty35
│   │   ├── 4:36 -> ../tty36
│   │   ├── 4:37 -> ../tty37
│   │   ├── 4:38 -> ../tty38
│   │   ├── 4:39 -> ../tty39
│   │   ├── 4:4 -> ../tty4
│   │   ├── 4:40 -> ../tty40
│   │   ├── 4:41 -> ../tty41
│   │   ├── 4:42 -> ../tty42
│   │   ├── 4:43 -> ../tty43
│   │   ├── 4:44 -> ../tty44
│   │   ├── 4:45 -> ../tty45
│   │   ├── 4:46 -> ../tty46
│   │   ├── 4:47 -> ../tty47
│   │   ├── 4:48 -> ../tty48
│   │   ├── 4:49 -> ../tty49
│   │   ├── 4:5 -> ../tty5
│   │   ├── 4:50 -> ../tty50
│   │   ├── 4:51 -> ../tty51
│   │   ├── 4:52 -> ../tty52
│   │   ├── 4:53 -> ../tty53
│   │   ├── 4:54 -> ../tty54
│   │   ├── 4:55 -> ../tty55
│   │   ├── 4:56 -> ../tty56
│   │   ├── 4:57 -> ../tty57
│   │   ├── 4:58 -> ../tty58
│   │   ├── 4:59 -> ../tty59
│   │   ├── 4:6 -> ../tty6
│   │   ├── 4:60 -> ../tty60
│   │   ├── 4:61 -> ../tty61
│   │   ├── 4:62 -> ../tty62
│   │   ├── 4:63 -> ../tty63
│   │   ├── 4:7 -> ../tty7
│   │   ├── 4:73 -> ../ttyS9
│   │   ├── 4:8 -> ../tty8
│   │   ├── 4:9 -> ../tty9
│   │   ├── 5:0 -> ../tty
│   │   ├── 5:1 -> ../console
│   │   ├── 511:0 -> ../hidraw0
│   │   ├── 511:1 -> ../hidraw1
│   │   ├── 511:2 -> ../hidraw2
│   │   ├── 5:2 -> ../ptmx
│   │   ├── 7:0 -> ../vcs
│   │   ├── 7:1 -> ../vcs1
│   │   ├── 7:128 -> ../vcsa
│   │   ├── 7:129 -> ../vcsa1
│   │   ├── 7:130 -> ../vcsa2
│   │   ├── 7:131 -> ../vcsa3
│   │   ├── 7:132 -> ../vcsa4
│   │   ├── 7:133 -> ../vcsa5
│   │   ├── 7:134 -> ../vcsa6
│   │   ├── 7:2 -> ../vcs2
│   │   ├── 7:3 -> ../vcs3
│   │   ├── 7:4 -> ../vcs4
│   │   ├── 7:5 -> ../vcs5
│   │   ├── 7:6 -> ../vcs6
│   │   ├── 7:64 -> ../vcsu
│   │   ├── 7:65 -> ../vcsu1
│   │   ├── 7:66 -> ../vcsu2
│   │   ├── 7:67 -> ../vcsu3
│   │   ├── 7:68 -> ../vcsu4
│   │   ├── 7:69 -> ../vcsu5
│   │   ├── 7:70 -> ../vcsu6
│   │   ├── 89:0 -> ../i2c-0
│   │   ├── 89:1 -> ../i2c-1
│   │   ├── 89:10 -> ../i2c-10
│   │   ├── 89:11 -> ../i2c-11
│   │   ├── 89:3 -> ../i2c-3
│   │   ├── 89:6 -> ../i2c-6
│   │   ├── 89:7 -> ../i2c-7
│   │   ├── 89:9 -> ../i2c-9
│   │   ├── 90:0 -> ../mtd0
│   │   └── 90:1 -> ../mtd0ro
│   ├── console
│   ├── cpu_dma_latency
│   ├── crypto
│   ├── cuse
│   ├── disk
│   │   ├── by-diskseq
│   │   │   ├── 11 -> ../../nvme0n1
│   │   │   ├── 2 -> ../../loop0
│   │   │   ├── 20 -> ../../loop8
│   │   │   ├── 26 -> ../../loop9
│   │   │   ├── 3 -> ../../loop1
│   │   │   ├── 4 -> ../../loop2
│   │   │   ├── 5 -> ../../loop3
│   │   │   ├── 6 -> ../../loop4
│   │   │   ├── 7 -> ../../loop5
│   │   │   ├── 8 -> ../../loop6
│   │   │   └── 9 -> ../../loop7
│   │   ├── by-id
│   │   │   ├── nvme-ADATA_LEGEND_860_2O47292BHCHR -> ../../nvme0n1
│   │   │   ├── nvme-ADATA_LEGEND_860_2O47292BHCHR_1 -> ../../nvme0n1
│   │   │   ├── nvme-ADATA_LEGEND_860_2O47292BHCHR_1-part1 -> ../../nvme0n1p1
│   │   │   ├── nvme-ADATA_LEGEND_860_2O47292BHCHR-part1 -> ../../nvme0n1p1
│   │   │   ├── nvme-eui.324f3437010000004ce0001848434852 -> ../../nvme0n1
│   │   │   └── nvme-eui.324f3437010000004ce0001848434852-part1 -> ../../nvme0n1p1
│   │   ├── by-label
│   │   │   └── armbi_root -> ../../nvme0n1p1
│   │   ├── by-partuuid
│   │   │   └── 6fa267f5-6e57-a042-b044-df5591269502 -> ../../nvme0n1p1
│   │   ├── by-path
│   │   │   ├── platform-fe150000.pcie-pci-0000:01:00.0-nvme-1 -> ../../nvme0n1
│   │   │   └── platform-fe150000.pcie-pci-0000:01:00.0-nvme-1-part1 -> ../../nvme0n1p1
│   │   └── by-uuid
│   │       └── afa0abd9-941e-42e6-8666-944f123a1981 -> ../../nvme0n1p1
│   ├── dma_heap
│   │   ├── reserved
│   │   ├── system
│   │   └── system-uncached
│   ├── dri
│   │   ├── by-path
│   │   │   ├── platform-display-subsystem-card -> ../card0
│   │   │   ├── platform-display-subsystem-render -> ../renderD128
│   │   │   ├── platform-fdab0000.npu-card -> ../card1
│   │   │   └── platform-fdab0000.npu-render -> ../renderD129
│   │   ├── card0
│   │   ├── card1
│   │   ├── renderD128
│   │   └── renderD129
│   ├── drm_dp_aux0
│   ├── fb0
│   ├── fd -> /proc/self/fd
│   ├── full
│   ├── fuse
│   ├── gpiochip0
│   ├── gpiochip1
│   ├── gpiochip2
│   ├── gpiochip3
│   ├── gpiochip4
│   ├── gpiochip5
│   ├── hidraw0
│   ├── hidraw1
│   ├── hidraw2
│   ├── hugepages
│   ├── hwrng
│   ├── i2c-0
│   ├── i2c-1
│   ├── i2c-10
│   ├── i2c-11
│   ├── i2c-3
│   ├── i2c-6
│   ├── i2c-7
│   ├── i2c-9
│   ├── iio:device0
│   ├── initctl -> /run/initctl
│   ├── input
│   │   ├── by-id
│   │   │   ├── usb-1ea7_2.4G_Wireless-event-if01 -> ../event12
│   │   │   ├── usb-1ea7_2.4G_Wireless-event-kbd -> ../event9
│   │   │   ├── usb-1ea7_2.4G_Wireless-if01-event-mouse -> ../event10
│   │   │   └── usb-1ea7_2.4G_Wireless-if01-mouse -> ../mouse0
│   │   ├── by-path
│   │   │   ├── platform-adc-keys-event -> ../event14
│   │   │   ├── platform-dp0-sound-event -> ../event3
│   │   │   ├── platform-es8388-sound-event -> ../event6
│   │   │   ├── platform-fde80000.hdmi-event -> ../event0
│   │   │   ├── platform-fdea0000.hdmi-event -> ../event1
│   │   │   ├── platform-feb20000.spi-cs-0-platform-rk805-pwrkey.10.auto-event -> ../event15
│   │   │   ├── platform-febf0030.pwm-event -> ../event2
│   │   │   ├── platform-hdmi0-sound-event -> ../event4
│   │   │   ├── platform-hdmi1-sound-event -> ../event5
│   │   │   ├── platform-wireless-bluetooth-event -> ../event8
│   │   │   ├── platform-xhci-hcd.12.auto-usb-0:1.4:1.0-event-kbd -> ../event9
│   │   │   ├── platform-xhci-hcd.12.auto-usb-0:1.4:1.1-event -> ../event12
│   │   │   ├── platform-xhci-hcd.12.auto-usb-0:1.4:1.1-event-mouse -> ../event10
│   │   │   └── platform-xhci-hcd.12.auto-usb-0:1.4:1.1-mouse -> ../mouse0
│   │   ├── event0
│   │   ├── event1
│   │   ├── event10
│   │   ├── event11
│   │   ├── event12
│   │   ├── event13
│   │   ├── event14
│   │   ├── event15
│   │   ├── event16
│   │   ├── event2
│   │   ├── event3
│   │   ├── event4
│   │   ├── event5
│   │   ├── event6
│   │   ├── event7
│   │   ├── event8
│   │   ├── event9
│   │   ├── mice
│   │   ├── mouse0
│   │   └── mouse1
│   ├── iomux
│   ├── kmsg
│   ├── kvm
│   ├── log -> /run/systemd/journal/dev-log
│   ├── loop0
│   ├── loop1
│   ├── loop2
│   ├── loop3
│   ├── loop4
│   ├── loop5
│   ├── loop6
│   ├── loop7
│   ├── loop8
│   ├── loop9
│   ├── loop-control
│   ├── mali0
│   ├── mapper
│   │   └── control
│   ├── mem
│   ├── mpp_service
│   ├── mqueue
│   ├── mtd0
│   ├── mtd0ro
│   ├── mtdblock0
│   ├── net
│   │   └── tun
│   ├── ng0n1
│   ├── null
│   ├── nvme0
│   ├── nvme0n1
│   ├── nvme0n1p1
│   ├── port
│   ├── ppp
│   ├── psaux
│   ├── ptmx
│   ├── pts
│   │   ├── 0
│   │   ├── 1
│   │   ├── 2
│   │   └── ptmx
│   ├── ram0
│   ├── random
│   ├── rfkill
│   ├── rga
│   ├── rkspi-dev2
│   ├── rtc -> rtc0
│   ├── rtc0
│   ├── shm
│   ├── snd
│   │   ├── by-path
│   │   │   ├── platform-dp0-sound -> ../controlC0
│   │   │   ├── platform-es8388-sound -> ../controlC3
│   │   │   ├── platform-hdmi0-sound -> ../controlC1
│   │   │   └── platform-hdmi1-sound -> ../controlC2
│   │   ├── controlC0
│   │   ├── controlC1
│   │   ├── controlC2
│   │   ├── controlC3
│   │   ├── pcmC0D0p
│   │   ├── pcmC1D0p
│   │   ├── pcmC2D0p
│   │   ├── pcmC3D0c
│   │   ├── pcmC3D0p
│   │   ├── seq
│   │   └── timer
│   ├── stderr -> /proc/self/fd/2
│   ├── stdin -> /proc/self/fd/0
│   ├── stdout -> /proc/self/fd/1
│   ├── sw_sync
│   ├── tty
│   ├── tty0
│   ├── tty1
│   ├── tty10
│   ├── tty11
│   ├── tty12
│   ├── tty13
│   ├── tty14
│   ├── tty15
│   ├── tty16
│   ├── tty17
│   ├── tty18
│   ├── tty19
│   ├── tty2
│   ├── tty20
│   ├── tty21
│   ├── tty22
│   ├── tty23
│   ├── tty24
│   ├── tty25
│   ├── tty26
│   ├── tty27
│   ├── tty28
│   ├── tty29
│   ├── tty3
│   ├── tty30
│   ├── tty31
│   ├── tty32
│   ├── tty33
│   ├── tty34
│   ├── tty35
│   ├── tty36
│   ├── tty37
│   ├── tty38
│   ├── tty39
│   ├── tty4
│   ├── tty40
│   ├── tty41
│   ├── tty42
│   ├── tty43
│   ├── tty44
│   ├── tty45
│   ├── tty46
│   ├── tty47
│   ├── tty48
│   ├── tty49
│   ├── tty5
│   ├── tty50
│   ├── tty51
│   ├── tty52
│   ├── tty53
│   ├── tty54
│   ├── tty55
│   ├── tty56
│   ├── tty57
│   ├── tty58
│   ├── tty59
│   ├── tty6
│   ├── tty60
│   ├── tty61
│   ├── tty62
│   ├── tty63
│   ├── tty7
│   ├── tty8
│   ├── tty9
│   ├── ttyFIQ0
│   ├── ttyS9
│   ├── ubi_ctrl
│   ├── uhid
│   ├── uinput
│   ├── urandom
│   ├── usb
│   │   └── hiddev0
│   ├── vcs
│   ├── vcs1
│   ├── vcs2
│   ├── vcs3
│   ├── vcs4
│   ├── vcs5
│   ├── vcs6
│   ├── vcsa
│   ├── vcsa1
│   ├── vcsa2
│   ├── vcsa3
│   ├── vcsa4
│   ├── vcsa5
│   ├── vcsa6
│   ├── vcsu
│   ├── vcsu1
│   ├── vcsu2
│   ├── vcsu3
│   ├── vcsu4
│   ├── vcsu5
│   ├── vcsu6
│   ├── vfio
│   │   └── vfio
│   ├── vga_arbiter
│   ├── vhci
│   ├── vhost-net
│   ├── vhost-vsock
│   ├── watchdog
│   ├── watchdog0
│   ├── zero
│   ├── zram0
│   ├── zram1
│   └── zram2
├── etc
│   ├── adduser.conf
│   ├── alsa
│   │   └── conf.d
│   │       ├── 50-pipewire.conf -> /usr/share/alsa/alsa.conf.d/50-pipewire.conf
│   │       └── 99-pipewire-default.conf -> /usr/share/alsa/alsa.conf.d/99-pipewire-default.conf
│   ├── alternatives
│   │   ├── arptables -> /usr/sbin/arptables-nft
│   │   ├── arptables-restore -> /usr/sbin/arptables-nft-restore
│   │   ├── arptables-save -> /usr/sbin/arptables-nft-save
│   │   ├── awk -> /usr/bin/mawk
│   │   ├── awk.1.gz -> /usr/share/man/man1/mawk.1.gz
│   │   ├── babeljs -> /usr/bin/babeljs-7
│   │   ├── babeljs-external-helpers -> /usr/bin/babeljs-7-external-helpers
│   │   ├── babeljs-node -> /usr/bin/babeljs-7-node
│   │   ├── babeljs-parser -> /usr/bin/babeljs-7-parser
│   │   ├── builtins.7.gz -> /usr/share/man/man7/bash-builtins.7.gz
│   │   ├── c++ -> /usr/bin/g++
│   │   ├── c89 -> /usr/bin/c89-gcc
│   │   ├── c89.1.gz -> /usr/share/man/man1/c89-gcc.1.gz
│   │   ├── c99 -> /usr/bin/c99-gcc
│   │   ├── c99.1.gz -> /usr/share/man/man1/c99-gcc.1.gz
│   │   ├── cc -> /usr/bin/gcc
│   │   ├── clang -> /usr/bin/clang-19
│   │   ├── cpp -> /usr/bin/cpp
│   │   ├── default-GM.sf2 -> /usr/share/sounds/sf2/TimGM6mb.sf2
│   │   ├── default-GM.sf3 -> /usr/share/sounds/sf2/TimGM6mb.sf2
│   │   ├── desktop-background -> /usr/share/desktop-base/active-theme/wallpaper/contents/images/1920x1080.svg
│   │   ├── desktop-background.xml -> /usr/share/desktop-base/active-theme/wallpaper/gnome-background.xml
│   │   ├── desktop-grub -> /usr/share/desktop-base/active-theme/grub/grub-4x3.png
│   │   ├── desktop-grub.sh -> /usr/share/desktop-base/active-theme/grub/grub_background.sh
│   │   ├── desktop-lockscreen.xml -> /usr/share/desktop-base/active-theme/lockscreen/gnome-background.xml
│   │   ├── desktop-login-background -> /usr/share/desktop-base/active-theme/login/background.svg
│   │   ├── desktop-plasma5-wallpaper -> /usr/share/desktop-base/active-theme/wallpaper
│   │   ├── desktop-theme -> /usr/share/desktop-base/emerald-theme
│   │   ├── ebtables -> /usr/sbin/ebtables-nft
│   │   ├── ebtables-restore -> /usr/sbin/ebtables-nft-restore
│   │   ├── ebtables-save -> /usr/sbin/ebtables-nft-save
│   │   ├── editor -> /bin/nano
│   │   ├── editor.1.gz -> /usr/share/man/man1/nano.1.gz
│   │   ├── emblem-vendor-128 -> /usr/share/icons/desktop-base/128x128/emblems/emblem-debian.png
│   │   ├── emblem-vendor-256 -> /usr/share/icons/desktop-base/256x256/emblems/emblem-debian.png
│   │   ├── emblem-vendor-64 -> /usr/share/icons/desktop-base/64x64/emblems/emblem-debian.png
│   │   ├── emblem-vendor-scalable -> /usr/share/icons/desktop-base/scalable/emblems/emblem-debian.svg
│   │   ├── emblem-vendor-symbolic-128 -> /usr/share/icons/desktop-base/128x128/emblems/emblem-debian-symbolic.png
│   │   ├── emblem-vendor-symbolic-256 -> /usr/share/icons/desktop-base/256x256/emblems/emblem-debian-symbolic.png
│   │   ├── emblem-vendor-symbolic-64 -> /usr/share/icons/desktop-base/64x64/emblems/emblem-debian-symbolic.png
│   │   ├── emblem-vendor-symbolic-scalable -> /usr/share/icons/desktop-base/scalable/emblems/emblem-debian-symbolic.svg
│   │   ├── emblem-vendor-white-128 -> /usr/share/icons/desktop-base/128x128/emblems/emblem-debian-white.png
│   │   ├── emblem-vendor-white-256 -> /usr/share/icons/desktop-base/256x256/emblems/emblem-debian-white.png
│   │   ├── emblem-vendor-white-64 -> /usr/share/icons/desktop-base/64x64/emblems/emblem-debian-white.png
│   │   ├── emblem-vendor-white-scalable -> /usr/share/icons/desktop-base/scalable/emblems/emblem-debian-white.svg
│   │   ├── figlet -> /usr/bin/figlet-figlet
│   │   ├── figlet.6.gz -> /usr/share/man/man6/figlet-figlet.6.gz
│   │   ├── gdm-smartcard -> /etc/pam.d/gdm-smartcard-sssd-exclusive
│   │   ├── gnome-www-browser -> /usr/bin/chromium
│   │   ├── gstreamer-codec-install -> /usr/libexec/pk-gstreamer-install
│   │   ├── ip6tables -> /usr/sbin/ip6tables-nft
│   │   ├── ip6tables-restore -> /usr/sbin/ip6tables-nft-restore
│   │   ├── ip6tables-save -> /usr/sbin/ip6tables-nft-save
│   │   ├── iptables -> /usr/sbin/iptables-nft
│   │   ├── iptables-restore -> /usr/sbin/iptables-nft-restore
│   │   ├── iptables-save -> /usr/sbin/iptables-nft-save
│   │   ├── js -> /usr/bin/nodejs
│   │   ├── js.1.gz -> /usr/share/man/man1/nodejs.1.gz
│   │   ├── libblas.so.3-aarch64-linux-gnu -> /usr/lib/aarch64-linux-gnu/blas/libblas.so.3
│   │   ├── liblapack.so.3-aarch64-linux-gnu -> /usr/lib/aarch64-linux-gnu/lapack/liblapack.so.3
│   │   ├── lzcat -> /usr/bin/xzcat
│   │   ├── lzcat.1.gz -> /usr/share/man/man1/xzcat.1.gz
│   │   ├── lzcmp -> /usr/bin/xzcmp
│   │   ├── lzcmp.1.gz -> /usr/share/man/man1/xzcmp.1.gz
│   │   ├── lzdiff -> /usr/bin/xzdiff
│   │   ├── lzdiff.1.gz -> /usr/share/man/man1/xzdiff.1.gz
│   │   ├── lzegrep -> /usr/bin/xzegrep
│   │   ├── lzegrep.1.gz -> /usr/share/man/man1/xzegrep.1.gz
│   │   ├── lzfgrep -> /usr/bin/xzfgrep
│   │   ├── lzfgrep.1.gz -> /usr/share/man/man1/xzfgrep.1.gz
│   │   ├── lzgrep -> /usr/bin/xzgrep
│   │   ├── lzgrep.1.gz -> /usr/share/man/man1/xzgrep.1.gz
│   │   ├── lzless -> /usr/bin/xzless
│   │   ├── lzless.1.gz -> /usr/share/man/man1/xzless.1.gz
│   │   ├── lzma -> /usr/bin/xz
│   │   ├── lzma.1.gz -> /usr/share/man/man1/xz.1.gz
│   │   ├── lzmore -> /usr/bin/xzmore
│   │   ├── lzmore.1.gz -> /usr/share/man/man1/xzmore.1.gz
│   │   ├── mt -> /bin/mt-gnu
│   │   ├── mt.1.gz -> /usr/share/man/man1/mt-gnu.1.gz
│   │   ├── nawk -> /usr/bin/mawk
│   │   ├── nawk.1.gz -> /usr/share/man/man1/mawk.1.gz
│   │   ├── open -> /usr/bin/xdg-open
│   │   ├── open.1.gz -> /usr/share/man/man1/xdg-open.1.gz
│   │   ├── pager -> /usr/bin/less
│   │   ├── pager.1.gz -> /usr/share/man/man1/less.1.gz
│   │   ├── pico -> /bin/nano
│   │   ├── pico.1.gz -> /usr/share/man/man1/nano.1.gz
│   │   ├── pinentry -> /usr/bin/pinentry-gnome3
│   │   ├── pinentry.1.gz -> /usr/share/man/man1/pinentry-gnome3.1.gz
│   │   ├── pinentry-x11 -> /usr/bin/pinentry-gnome3
│   │   ├── pinentry-x11.1.gz -> /usr/share/man/man1/pinentry-gnome3.1.gz
│   │   ├── README
│   │   ├── regulatory.db -> /lib/firmware/regulatory.db-debian
│   │   ├── regulatory.db.p7s -> /lib/firmware/regulatory.db.p7s-debian
│   │   ├── rmt -> /usr/sbin/rmt-tar
│   │   ├── rmt.8.gz -> /usr/share/man/man8/rmt-tar.8.gz
│   │   ├── unlzma -> /usr/bin/unxz
│   │   ├── unlzma.1.gz -> /usr/share/man/man1/unxz.1.gz
│   │   ├── vendor-logos -> /usr/share/desktop-base/debian-logos
│   │   ├── which -> /usr/bin/which.debianutils
│   │   ├── which.1.gz -> /usr/share/man/man1/which.debianutils.1.gz
│   │   ├── which.de1.gz -> /usr/share/man/de/man1/which.debianutils.1.gz
│   │   ├── which.es1.gz -> /usr/share/man/es/man1/which.debianutils.1.gz
│   │   ├── which.fr1.gz -> /usr/share/man/fr/man1/which.debianutils.1.gz
│   │   ├── which.it1.gz -> /usr/share/man/it/man1/which.debianutils.1.gz
│   │   ├── which.ja1.gz -> /usr/share/man/ja/man1/which.debianutils.1.gz
│   │   ├── which.pl1.gz -> /usr/share/man/pl/man1/which.debianutils.1.gz
│   │   ├── which.sl1.gz -> /usr/share/man/sl/man1/which.debianutils.1.gz
│   │   ├── x-cursor-theme -> /usr/share/icons/Adwaita/cursor.theme
│   │   ├── x-session-manager -> /usr/bin/gnome-session
│   │   ├── x-session-manager.1.gz -> /usr/share/man/man1/gnome-session.1.gz
│   │   ├── x-terminal-emulator -> /usr/bin/gnome-terminal.wrapper
│   │   ├── x-terminal-emulator.1.gz -> /usr/share/man/man1/gnome-terminal.1.gz
│   │   ├── x-www-browser -> /usr/bin/chromium
│   │   ├── yacc -> /usr/bin/bison.yacc
│   │   └── yaccman -> /usr/share/man/man1/bison.yacc.1.gz
│   ├── apache2
│   │   └── mods-available
│   │       ├── dnssd.conf
│   │       └── dnssd.load
│   ├── apg.conf
│   ├── apparmor
│   │   └── parser.conf
│   ├── apparmor.d
│   │   ├── abi
│   │   │   ├── 3.0
│   │   │   ├── kernel-5.4-outoftree-network
│   │   │   └── kernel-5.4-vanilla
│   │   ├── abstractions
│   │   │   ├── apache2-common
│   │   │   ├── apparmor_api
│   │   │   │   ├── change_profile
│   │   │   │   ├── examine
│   │   │   │   ├── find_mountpoint
│   │   │   │   ├── introspect
│   │   │   │   └── is_enabled
│   │   │   ├── aspell
│   │   │   ├── audio
│   │   │   ├── authentication
│   │   │   ├── base
│   │   │   ├── bash
│   │   │   ├── consoles
│   │   │   ├── crypto
│   │   │   ├── cups-client
│   │   │   ├── dbus
│   │   │   ├── dbus-accessibility
│   │   │   ├── dbus-accessibility-strict
│   │   │   ├── dbus-network-manager-strict
│   │   │   ├── dbus-session
│   │   │   ├── dbus-session-strict
│   │   │   ├── dbus-strict
│   │   │   ├── dconf
│   │   │   ├── dovecot-common
│   │   │   ├── dri-common
│   │   │   ├── dri-enumerate
│   │   │   ├── enchant
│   │   │   ├── evince
│   │   │   ├── exo-open
│   │   │   ├── fcitx
│   │   │   ├── fcitx-strict
│   │   │   ├── fonts
│   │   │   ├── freedesktop.org
│   │   │   ├── gio-open
│   │   │   ├── gnome
│   │   │   ├── gnupg
│   │   │   ├── gtk
│   │   │   ├── gvfs-open
│   │   │   ├── hosts_access
│   │   │   ├── ibus
│   │   │   ├── kde
│   │   │   ├── kde-globals-write
│   │   │   ├── kde-icon-cache-write
│   │   │   ├── kde-language-write
│   │   │   ├── kde-open5
│   │   │   ├── kerberosclient
│   │   │   ├── ldapclient
│   │   │   ├── libpam-systemd
│   │   │   ├── likewise
│   │   │   ├── mdns
│   │   │   ├── mesa
│   │   │   ├── mir
│   │   │   ├── mozc
│   │   │   ├── mysql
│   │   │   ├── nameservice
│   │   │   ├── nis
│   │   │   ├── nss-systemd
│   │   │   ├── nvidia
│   │   │   ├── opencl
│   │   │   ├── opencl-common
│   │   │   ├── opencl-intel
│   │   │   ├── opencl-mesa
│   │   │   ├── opencl-nvidia
│   │   │   ├── opencl-pocl
│   │   │   ├── openssl
│   │   │   ├── orbit2
│   │   │   ├── p11-kit
│   │   │   ├── perl
│   │   │   ├── php
│   │   │   ├── php5
│   │   │   ├── php-worker
│   │   │   ├── postfix-common
│   │   │   ├── private-files
│   │   │   ├── private-files-strict
│   │   │   ├── python
│   │   │   ├── qt5
│   │   │   ├── qt5-compose-cache-write
│   │   │   ├── qt5-settings-write
│   │   │   ├── recent-documents-write
│   │   │   ├── ruby
│   │   │   ├── samba
│   │   │   ├── samba-rpcd
│   │   │   ├── smbpass
│   │   │   ├── snap_browsers
│   │   │   ├── ssl_certs
│   │   │   ├── ssl_keys
│   │   │   ├── svn-repositories
│   │   │   ├── ubuntu-bittorrent-clients
│   │   │   ├── ubuntu-browsers
│   │   │   ├── ubuntu-browsers.d
│   │   │   │   ├── chromium-browser
│   │   │   │   ├── java
│   │   │   │   ├── kde
│   │   │   │   ├── mailto
│   │   │   │   ├── multimedia
│   │   │   │   ├── plugins-common
│   │   │   │   ├── productivity
│   │   │   │   ├── text-editors
│   │   │   │   ├── ubuntu-integration
│   │   │   │   ├── ubuntu-integration-xul
│   │   │   │   └── user-files
│   │   │   ├── ubuntu-console-browsers
│   │   │   ├── ubuntu-console-email
│   │   │   ├── ubuntu-email
│   │   │   ├── ubuntu-feed-readers
│   │   │   ├── ubuntu-gnome-terminal
│   │   │   ├── ubuntu-helpers
│   │   │   ├── ubuntu-konsole
│   │   │   ├── ubuntu-media-players
│   │   │   ├── ubuntu-unity7-base
│   │   │   ├── ubuntu-unity7-launcher
│   │   │   ├── ubuntu-unity7-messaging
│   │   │   ├── ubuntu-xterm
│   │   │   ├── user-download
│   │   │   ├── user-mail
│   │   │   ├── user-manpages
│   │   │   ├── user-tmp
│   │   │   ├── user-write
│   │   │   ├── video
│   │   │   ├── vulkan
│   │   │   ├── wayland
│   │   │   ├── web-data
│   │   │   ├── winbind
│   │   │   ├── wutmp
│   │   │   ├── X
│   │   │   ├── xad
│   │   │   ├── xdg-desktop
│   │   │   └── xdg-open
│   │   ├── disable
│   │   ├── force-complain
│   │   ├── local
│   │   │   ├── lsb_release
│   │   │   ├── nvidia_modprobe
│   │   │   ├── README
│   │   │   ├── usr.bin.evince
│   │   │   ├── usr.bin.man
│   │   │   ├── usr.lib.libreoffice.program.oosplash
│   │   │   ├── usr.lib.libreoffice.program.senddoc
│   │   │   ├── usr.lib.libreoffice.program.soffice.bin
│   │   │   ├── usr.lib.libreoffice.program.xpdfimport
│   │   │   └── usr.lib.snapd.snap-confine.real
│   │   ├── lsb_release
│   │   ├── nvidia_modprobe
│   │   ├── tunables
│   │   │   ├── alias
│   │   │   ├── apparmorfs
│   │   │   ├── dovecot
│   │   │   ├── etc
│   │   │   ├── global
│   │   │   ├── home
│   │   │   ├── home.d
│   │   │   │   ├── site.local
│   │   │   │   └── ubuntu
│   │   │   ├── kernelvars
│   │   │   ├── multiarch
│   │   │   ├── multiarch.d
│   │   │   │   └── site.local
│   │   │   ├── proc
│   │   │   ├── run
│   │   │   ├── securityfs
│   │   │   ├── share
│   │   │   ├── sys
│   │   │   ├── xdg-user-dirs
│   │   │   └── xdg-user-dirs.d
│   │   │       └── site.local
│   │   ├── usr.bin.evince
│   │   ├── usr.bin.man
│   │   ├── usr.lib.libreoffice.program.oosplash
│   │   ├── usr.lib.libreoffice.program.senddoc
│   │   ├── usr.lib.libreoffice.program.soffice.bin
│   │   ├── usr.lib.libreoffice.program.xpdfimport
│   │   └── usr.lib.snapd.snap-confine.real
│   ├── appstream.conf
│   ├── apt
│   │   ├── apt.conf.d
│   │   │   ├── 01autoremove
│   │   │   ├── 02-armbian-compress-indexes
│   │   │   ├── 02-armbian-periodic
│   │   │   ├── 02-armbian-postupdate
│   │   │   ├── 20packagekit
│   │   │   ├── 20snapd.conf
│   │   │   ├── 50appstream
│   │   │   ├── 60icons
│   │   │   ├── 70debconf
│   │   │   ├── 71-armbian-no-recommends
│   │   │   └── 81-armbian-no-languages
│   │   ├── auth.conf.d
│   │   ├── keyrings
│   │   │   └── packages.microsoft.gpg
│   │   ├── preferences.d
│   │   │   ├── armbian
│   │   │   └── frozen-armbian
│   │   ├── sources.list
│   │   ├── sources.list.d
│   │   │   ├── archive_uri-http_apt_llvm_org_bookworm_-bookworm.list
│   │   │   ├── armbian-config.sources
│   │   │   ├── armbian.sources
│   │   │   ├── debian.sources
│   │   │   ├── vscode.list
│   │   │   └── yarn.list
│   │   ├── trusted.gpg
│   │   └── trusted.gpg.d
│   │       ├── apt.llvm.org.asc
│   │       ├── debian-archive-bookworm-automatic.asc
│   │       ├── debian-archive-bookworm-security-automatic.asc
│   │       ├── debian-archive-bookworm-stable.asc
│   │       ├── debian-archive-bullseye-automatic.asc
│   │       ├── debian-archive-bullseye-security-automatic.asc
│   │       ├── debian-archive-bullseye-stable.asc
│   │       ├── debian-archive-trixie-automatic.asc
│   │       ├── debian-archive-trixie-security-automatic.asc
│   │       ├── debian-archive-trixie-stable.asc
│   │       └── microsoft.gpg
│   ├── armbian-distribution-status
│   ├── armbian-image-release
│   ├── armbian-leds.conf
│   ├── armbianmonitor
│   │   └── datasources
│   │       └── soctemp -> /sys/class/hwmon/hwmon0/temp1_input
│   ├── armbian-release
│   ├── armbian.txt
│   ├── avahi
│   │   ├── avahi-daemon.conf
│   │   ├── hosts
│   │   └── services
│   ├── bash.bashrc
│   ├── bash_completion
│   ├── bash_completion.d
│   │   └── git-prompt
│   ├── bindresvport.blacklist
│   ├── binfmt.d
│   ├── bluetooth
│   │   ├── input.conf
│   │   ├── main.conf
│   │   └── network.conf
│   ├── ca-certificates
│   │   └── update.d
│   ├── ca-certificates.conf
│   ├── ca-certificates.conf.dpkg-old
│   ├── chromium
│   │   └── master_preferences
│   ├── chromium.d
│   │   ├── apikeys
│   │   ├── default-flags
│   │   ├── dev-shm
│   │   ├── extensions
│   │   └── README
│   ├── cni
│   │   └── net.d  [error opening dir]
│   ├── console-setup
│   │   ├── cached_ISO-8859-15.acm.gz
│   │   ├── cached_ISO-8859-15_del.kmap.gz
│   │   ├── cached_Lat15-Fixed16.psf.gz
│   │   ├── cached_setup_font.sh
│   │   ├── cached_setup_keyboard.sh
│   │   ├── cached_setup_terminal.sh
│   │   ├── cached_Uni2-Fixed16.psf.gz
│   │   ├── cached_UTF-8_del.kmap.gz
│   │   ├── compose.ARMSCII-8.inc
│   │   ├── compose.CP1251.inc
│   │   ├── compose.CP1255.inc
│   │   ├── compose.CP1256.inc
│   │   ├── compose.GEORGIAN-ACADEMY.inc
│   │   ├── compose.GEORGIAN-PS.inc
│   │   ├── compose.IBM1133.inc
│   │   ├── compose.ISIRI-3342.inc
│   │   ├── compose.ISO-8859-10.inc
│   │   ├── compose.ISO-8859-11.inc
│   │   ├── compose.ISO-8859-13.inc
│   │   ├── compose.ISO-8859-14.inc
│   │   ├── compose.ISO-8859-15.inc
│   │   ├── compose.ISO-8859-16.inc
│   │   ├── compose.ISO-8859-1.inc
│   │   ├── compose.ISO-8859-2.inc
│   │   ├── compose.ISO-8859-3.inc
│   │   ├── compose.ISO-8859-4.inc
│   │   ├── compose.ISO-8859-5.inc
│   │   ├── compose.ISO-8859-6.inc
│   │   ├── compose.ISO-8859-7.inc
│   │   ├── compose.ISO-8859-8.inc
│   │   ├── compose.ISO-8859-9.inc
│   │   ├── compose.KOI8-R.inc
│   │   ├── compose.KOI8-U.inc
│   │   ├── compose.TIS-620.inc
│   │   ├── compose.VISCII.inc
│   │   └── remap.inc
│   ├── containerd
│   │   └── config.toml
│   ├── cron.d
│   │   ├── armbian-check-battery
│   │   ├── armbian-truncate-logs
│   │   ├── armbian-updates
│   │   └── e2scrub_all
│   ├── cron.daily
│   │   ├── apt-compat
│   │   ├── armbian-quotes
│   │   ├── armbian-ram-logging
│   │   ├── debsums
│   │   ├── dpkg
│   │   ├── logrotate
│   │   └── man-db
│   ├── cron.hourly
│   │   └── fake-hwclock
│   ├── cron.monthly
│   │   └── debsums
│   ├── crontab
│   ├── cron.weekly
│   │   ├── debsums
│   │   └── man-db
│   ├── cron.yearly
│   ├── cupshelpers
│   │   └── preferreddrivers.xml
│   ├── dbus-1
│   │   ├── session.d
│   │   └── system.d
│   │       ├── bluetooth.conf
│   │       ├── com.redhat.NewPrinterNotification.conf
│   │       ├── com.redhat.PrinterDriversInstaller.conf
│   │       ├── com.ubuntu.SoftwareProperties.conf
│   │       ├── org.freedesktop.GeoClue2.Agent.conf
│   │       ├── org.freedesktop.GeoClue2.conf
│   │       ├── org.freedesktop.PackageKit.conf
│   │       ├── org.opensuse.CupsPkHelper.Mechanism.conf
│   │       └── wpa_supplicant.conf
│   ├── dconf
│   │   ├── db
│   │   │   ├── ibus
│   │   │   └── ibus.d
│   │   │       └── 00-upstream-settings
│   │   └── profile
│   │       └── ibus
│   ├── debconf.conf
│   ├── debian_version
│   ├── debuginfod
│   │   └── elfutils.urls
│   ├── default
│   │   ├── armbian-firstrun
│   │   ├── armbian-firstrun.dpkg-dist
│   │   ├── armbian-motd
│   │   ├── armbian-motd.dpkg-dist
│   │   ├── armbian-ramlog
│   │   ├── armbian-ramlog.dpkg-dist
│   │   ├── armbian-zram-config
│   │   ├── armbian-zram-config.dpkg-dist
│   │   ├── avahi-daemon
│   │   ├── bluetooth
│   │   ├── console-setup
│   │   ├── cpufrequtils
│   │   ├── cron
│   │   ├── dbus
│   │   ├── debsums
│   │   ├── docker
│   │   ├── fake-hwclock
│   │   ├── hwclock
│   │   ├── keyboard
│   │   ├── locale
│   │   ├── nss
│   │   ├── rng-tools
│   │   ├── rsync
│   │   ├── ssh
│   │   └── useradd
│   ├── deluser.conf
│   ├── dhcp
│   │   └── dhclient-exit-hooks.d
│   │       └── timesyncd
│   ├── dictionaries-common
│   │   └── ispell-default
│   ├── docker
│   │   └── key.json
│   ├── dpkg
│   │   ├── dpkg.cfg
│   │   ├── dpkg.cfg.d
│   │   ├── origins
│   │   │   ├── armbian
│   │   │   └── debian
│   │   ├── shlibs.default
│   │   └── shlibs.override
│   ├── e2scrub.conf
│   ├── emacs
│   │   └── site-start.d
│   │       ├── 50dictionaries-common.el
│   │       └── 50figlet.el
│   ├── environment
│   ├── environment.d
│   │   ├── 90atk-adaptor.conf
│   │   └── 90qt-a11y.conf
│   ├── ethertypes
│   ├── fake-hwclock.data
│   ├── fonts
│   │   ├── conf.avail
│   │   │   ├── 20-unhint-small-dejavu-lgc-sans.conf
│   │   │   ├── 20-unhint-small-dejavu-lgc-sans-mono.conf
│   │   │   ├── 20-unhint-small-dejavu-lgc-serif.conf
│   │   │   ├── 20-unhint-small-dejavu-sans.conf
│   │   │   ├── 20-unhint-small-dejavu-sans-mono.conf
│   │   │   ├── 20-unhint-small-dejavu-serif.conf
│   │   │   ├── 30-droid-noto.conf
│   │   │   ├── 57-dejavu-sans.conf
│   │   │   ├── 57-dejavu-sans-mono.conf
│   │   │   ├── 57-dejavu-serif.conf
│   │   │   ├── 58-dejavu-lgc-sans.conf
│   │   │   ├── 58-dejavu-lgc-sans-mono.conf
│   │   │   └── 58-dejavu-lgc-serif.conf
│   │   ├── conf.d
│   │   │   ├── 10-hinting-slight.conf -> /usr/share/fontconfig/conf.avail/10-hinting-slight.conf
│   │   │   ├── 10-scale-bitmap-fonts.conf -> /usr/share/fontconfig/conf.avail/10-scale-bitmap-fonts.conf
│   │   │   ├── 10-yes-antialias.conf -> /usr/share/fontconfig/conf.avail/10-yes-antialias.conf
│   │   │   ├── 11-lcdfilter-default.conf -> /usr/share/fontconfig/conf.avail/11-lcdfilter-default.conf
│   │   │   ├── 20-unhint-small-dejavu-lgc-sans.conf -> ../conf.avail/20-unhint-small-dejavu-lgc-sans.conf
│   │   │   ├── 20-unhint-small-dejavu-lgc-sans-mono.conf -> ../conf.avail/20-unhint-small-dejavu-lgc-sans-mono.conf
│   │   │   ├── 20-unhint-small-dejavu-lgc-serif.conf -> ../conf.avail/20-unhint-small-dejavu-lgc-serif.conf
│   │   │   ├── 20-unhint-small-dejavu-sans.conf -> ../conf.avail/20-unhint-small-dejavu-sans.conf
│   │   │   ├── 20-unhint-small-dejavu-sans-mono.conf -> ../conf.avail/20-unhint-small-dejavu-sans-mono.conf
│   │   │   ├── 20-unhint-small-dejavu-serif.conf -> ../conf.avail/20-unhint-small-dejavu-serif.conf
│   │   │   ├── 20-unhint-small-vera.conf -> /usr/share/fontconfig/conf.avail/20-unhint-small-vera.conf
│   │   │   ├── 30-metric-aliases.conf -> /usr/share/fontconfig/conf.avail/30-metric-aliases.conf
│   │   │   ├── 30-opensymbol.conf -> /usr/share/fontconfig/conf.avail/30-opensymbol.conf
│   │   │   ├── 40-nonlatin.conf -> /usr/share/fontconfig/conf.avail/40-nonlatin.conf
│   │   │   ├── 45-generic.conf -> /usr/share/fontconfig/conf.avail/45-generic.conf
│   │   │   ├── 45-latin.conf -> /usr/share/fontconfig/conf.avail/45-latin.conf
│   │   │   ├── 48-spacing.conf -> /usr/share/fontconfig/conf.avail/48-spacing.conf
│   │   │   ├── 49-sansserif.conf -> /usr/share/fontconfig/conf.avail/49-sansserif.conf
│   │   │   ├── 50-user.conf -> /usr/share/fontconfig/conf.avail/50-user.conf
│   │   │   ├── 51-local.conf -> /usr/share/fontconfig/conf.avail/51-local.conf
│   │   │   ├── 57-dejavu-sans.conf -> ../conf.avail/57-dejavu-sans.conf
│   │   │   ├── 57-dejavu-sans-mono.conf -> ../conf.avail/57-dejavu-sans-mono.conf
│   │   │   ├── 57-dejavu-serif.conf -> ../conf.avail/57-dejavu-serif.conf
│   │   │   ├── 58-dejavu-lgc-sans.conf -> ../conf.avail/58-dejavu-lgc-sans.conf
│   │   │   ├── 58-dejavu-lgc-sans-mono.conf -> ../conf.avail/58-dejavu-lgc-sans-mono.conf
│   │   │   ├── 58-dejavu-lgc-serif.conf -> ../conf.avail/58-dejavu-lgc-serif.conf
│   │   │   ├── 60-generic.conf -> /usr/share/fontconfig/conf.avail/60-generic.conf
│   │   │   ├── 60-latin.conf -> /usr/share/fontconfig/conf.avail/60-latin.conf
│   │   │   ├── 61-urw-bookman.conf -> /usr/share/fontconfig/conf.avail/urw-bookman.conf
│   │   │   ├── 61-urw-c059.conf -> /usr/share/fontconfig/conf.avail/urw-c059.conf
│   │   │   ├── 61-urw-d050000l.conf -> /usr/share/fontconfig/conf.avail/urw-d050000l.conf
│   │   │   ├── 61-urw-fallback-backwards.conf -> /usr/share/fontconfig/conf.avail/urw-fallback-backwards.conf
│   │   │   ├── 61-urw-fallback-generics.conf -> /usr/share/fontconfig/conf.avail/urw-fallback-generics.conf
│   │   │   ├── 61-urw-gothic.conf -> /usr/share/fontconfig/conf.avail/urw-gothic.conf
│   │   │   ├── 61-urw-nimbus-mono-ps.conf -> /usr/share/fontconfig/conf.avail/urw-nimbus-mono-ps.conf
│   │   │   ├── 61-urw-nimbus-roman.conf -> /usr/share/fontconfig/conf.avail/urw-nimbus-roman.conf
│   │   │   ├── 61-urw-nimbus-sans.conf -> /usr/share/fontconfig/conf.avail/urw-nimbus-sans.conf
│   │   │   ├── 61-urw-p052.conf -> /usr/share/fontconfig/conf.avail/urw-p052.conf
│   │   │   ├── 61-urw-standard-symbols-ps.conf -> /usr/share/fontconfig/conf.avail/urw-standard-symbols-ps.conf
│   │   │   ├── 61-urw-z003.conf -> /usr/share/fontconfig/conf.avail/urw-z003.conf
│   │   │   ├── 65-fonts-persian.conf -> /usr/share/fontconfig/conf.avail/65-fonts-persian.conf
│   │   │   ├── 65-nonlatin.conf -> /usr/share/fontconfig/conf.avail/65-nonlatin.conf
│   │   │   ├── 69-unifont.conf -> /usr/share/fontconfig/conf.avail/69-unifont.conf
│   │   │   ├── 70-no-bitmaps.conf -> /usr/share/fontconfig/conf.avail/70-no-bitmaps.conf
│   │   │   ├── 80-delicious.conf -> /usr/share/fontconfig/conf.avail/80-delicious.conf
│   │   │   ├── 90-synthetic.conf -> /usr/share/fontconfig/conf.avail/90-synthetic.conf
│   │   │   └── README
│   │   └── fonts.conf
│   ├── fstab
│   ├── fuse.conf
│   ├── gai.conf
│   ├── gdb
│   │   ├── gdbinit
│   │   └── gdbinit.d
│   ├── gdm3
│   │   ├── daemon.conf
│   │   ├── greeter.dconf-defaults
│   │   ├── Init
│   │   │   └── Default
│   │   ├── PostLogin
│   │   │   └── Default.sample
│   │   ├── PostSession
│   │   │   └── Default
│   │   ├── PreSession
│   │   │   └── Default
│   │   └── Xsession
│   ├── geoclue
│   │   └── geoclue.conf
│   ├── ghostscript
│   │   ├── cidfmap.d
│   │   │   ├── 90gs-cjk-resource-cns1.conf
│   │   │   ├── 90gs-cjk-resource-gb1.conf
│   │   │   ├── 90gs-cjk-resource-japan1.conf
│   │   │   ├── 90gs-cjk-resource-japan2.conf
│   │   │   └── 90gs-cjk-resource-korea1.conf
│   │   └── fontmap.d
│   │       └── 10fonts-urw-base35.conf
│   ├── glvnd
│   │   └── egl_vendor.d
│   ├── gnome
│   │   └── menus.blacklist
│   ├── gprofng.rc
│   ├── groff
│   │   ├── man.local
│   │   └── mdoc.local
│   ├── group
│   ├── group-
│   ├── gshadow
│   ├── gshadow-
│   ├── gss
│   │   └── mech.d
│   ├── gtk-3.0
│   │   └── im-multipress.conf
│   ├── host.conf
│   ├── hostname
│   ├── hosts
│   ├── hosts.allow
│   ├── hosts.deny
│   ├── ifplugd
│   │   └── action.d
│   │       └── action_wpa -> ../../wpa_supplicant/action_wpa.sh
│   ├── init.d
│   │   ├── alsa-utils
│   │   ├── apparmor
│   │   ├── bluetooth
│   │   ├── console-setup.sh
│   │   ├── cron
│   │   ├── dbus
│   │   ├── docker
│   │   ├── fake-hwclock
│   │   ├── gdm3
│   │   ├── hwclock.sh
│   │   ├── keyboard-setup.sh
│   │   ├── kmod
│   │   ├── procps
│   │   ├── rsync
│   │   ├── speech-dispatcher
│   │   ├── ssh
│   │   ├── sudo
│   │   ├── udev
│   │   └── x11-common
│   ├── initramfs
│   │   └── post-update.d
│   │       └── 99-uboot
│   ├── initramfs-tools
│   │   ├── conf.d
│   │   ├── hooks
│   │   ├── initramfs.conf
│   │   ├── modules
│   │   ├── scripts
│   │   │   ├── init-bottom
│   │   │   ├── init-premount
│   │   │   ├── init-top
│   │   │   ├── local-bottom
│   │   │   ├── local-premount
│   │   │   ├── local-top
│   │   │   ├── nfs-bottom
│   │   │   ├── nfs-premount
│   │   │   ├── nfs-top
│   │   │   └── panic
│   │   └── update-initramfs.conf
│   ├── inputrc
│   ├── insserv.conf.d
│   │   └── gdm3
│   ├── iproute2
│   │   ├── bpf_pinning
│   │   ├── ematch_map
│   │   ├── group
│   │   ├── nl_protos
│   │   ├── rt_dsfield
│   │   ├── rt_protos
│   │   ├── rt_protos.d
│   │   │   └── README
│   │   ├── rt_realms
│   │   ├── rt_scopes
│   │   ├── rt_tables
│   │   └── rt_tables.d
│   │       └── README
│   ├── issue
│   ├── issue.net
│   ├── kernel
│   │   ├── install.d
│   │   ├── postinst.d
│   │   │   ├── initramfs-tools
│   │   │   └── xx-initramfs-cleanup
│   │   ├── postrm.d
│   │   │   ├── initramfs-tools
│   │   │   └── xx-initramfs-cleanup
│   │   ├── preinst.d
│   │   └── prerm.d
│   ├── lcovrc
│   ├── ld.so.cache
│   ├── ld.so.conf
│   ├── ld.so.conf.d
│   │   ├── aarch64-linux-gnu.conf
│   │   └── libc.conf
│   ├── libao.conf
│   ├── libaudit.conf
│   ├── libblockdev
│   │   └── conf.d
│   │       └── 00-default.cfg
│   ├── libnl-3
│   │   ├── classid
│   │   └── pktloc
│   ├── libpaper.d
│   ├── libreoffice
│   │   ├── psprint.conf
│   │   ├── registry
│   │   │   ├── calc.xcd
│   │   │   ├── draw.xcd
│   │   │   ├── gnome.xcd
│   │   │   ├── graphicfilter.xcd
│   │   │   ├── impress.xcd
│   │   │   ├── Langpack-en-US.xcd
│   │   │   ├── lingucomponent.xcd
│   │   │   ├── main.xcd
│   │   │   ├── ogltrans.xcd
│   │   │   ├── oo-ad-ldap.xcd.sample -> /usr/share/doc/libreoffice-common/examples/oo-ad-ldap.xcd.sample
│   │   │   ├── oo-ldap.xcd.sample -> /usr/share/doc/libreoffice-common/examples/oo-ldap.xcd.sample
│   │   │   ├── pdfimport.xcd
│   │   │   ├── res
│   │   │   │   └── fcfg_langpack_en-US.xcd
│   │   │   ├── writer.xcd
│   │   │   └── xsltfilter.xcd
│   │   ├── sofficerc
│   │   └── soffice.sh
│   ├── locale.alias
│   ├── locale.gen
│   ├── localtime -> ../usr/share/zoneinfo/Asia/Ho_Chi_Minh
│   ├── logcheck
│   │   └── ignore.d.server
│   │       ├── gpg-agent
│   │       └── rsyslog
│   ├── login.defs
│   ├── logrotate.conf
│   ├── logrotate.d
│   │   ├── alternatives
│   │   ├── apt
│   │   ├── armbian-hardware-monitor
│   │   ├── btmp
│   │   ├── dpkg
│   │   ├── rsyslog
│   │   ├── speech-dispatcher
│   │   └── wtmp
│   ├── machine-id
│   ├── machine-info
│   ├── magic
│   ├── magic.mime
│   ├── manpath.config
│   ├── mime.types
│   ├── mke2fs.conf
│   ├── modprobe.d
│   │   ├── 8189fs.conf
│   │   └── r8723bs.conf
│   ├── modules
│   ├── modules-load.d
│   │   └── modules.conf -> ../modules
│   ├── motd -> /var/run/motd
│   ├── mtab -> ../proc/self/mounts
│   ├── nanorc
│   ├── netconfig
│   ├── netplan
│   │   ├── 10-dhcp-all-interfaces.yaml
│   │   └── armbian.yaml
│   ├── network
│   │   ├── if-down.d
│   │   │   └── wpasupplicant -> ../../wpa_supplicant/ifupdown.sh
│   │   ├── if-post-down.d
│   │   │   └── wpasupplicant -> ../../wpa_supplicant/ifupdown.sh
│   │   ├── if-pre-up.d
│   │   │   ├── ethtool
│   │   │   └── wpasupplicant -> ../../wpa_supplicant/ifupdown.sh
│   │   └── if-up.d
│   │       ├── ethtool
│   │       └── wpasupplicant -> ../../wpa_supplicant/ifupdown.sh
│   ├── NetworkManager
│   │   ├── conf.d
│   │   │   ├── zz-10-override-wifi-random-mac-disable.conf
│   │   │   └── zz-20-override-wifi-powersave-disable.conf
│   │   ├── dispatcher.d
│   │   │   ├── 01-ifupdown
│   │   │   ├── no-wait.d
│   │   │   ├── pre-down.d
│   │   │   └── pre-up.d
│   │   ├── dnsmasq.d
│   │   ├── dnsmasq-shared.d
│   │   ├── NetworkManager.conf
│   │   └── system-connections
│   │       └── Paul 5G.nmconnection
│   ├── networks
│   ├── nsswitch.conf
│   ├── openal
│   │   └── alsoft.conf
│   ├── openni2
│   │   └── OpenNI.ini
│   ├── opt
│   ├── os-release
│   ├── PackageKit
│   │   ├── PackageKit.conf
│   │   └── Vendor.conf
│   ├── pam.conf
│   ├── pam.d
│   │   ├── chfn
│   │   ├── chpasswd
│   │   ├── chsh
│   │   ├── common-account
│   │   ├── common-auth
│   │   ├── common-password
│   │   ├── common-session
│   │   ├── common-session-noninteractive
│   │   ├── cron
│   │   ├── gdm-autologin
│   │   ├── gdm-fingerprint
│   │   ├── gdm-launch-environment
│   │   ├── gdm-password
│   │   ├── gdm-smartcard -> /etc/alternatives/gdm-smartcard
│   │   ├── gdm-smartcard-pkcs11-exclusive
│   │   ├── gdm-smartcard-sssd-exclusive
│   │   ├── gdm-smartcard-sssd-or-password
│   │   ├── login
│   │   ├── newusers
│   │   ├── other
│   │   ├── passwd
│   │   ├── runuser
│   │   ├── runuser-l
│   │   ├── sshd
│   │   ├── su
│   │   ├── sudo
│   │   ├── sudo-i
│   │   └── su-l
│   ├── papersize
│   ├── passwd
│   ├── passwd-
│   ├── perl
│   │   ├── Net
│   │   │   └── libnet.cfg
│   │   └── XML
│   │       └── SAX
│   │           └── ParserDetails.ini
│   ├── polkit-1
│   │   └── rules.d  [error opening dir]
│   ├── profile
│   ├── profile.d
│   │   ├── apps-bin-path.sh
│   │   ├── armbian-activate-profile-sync-daemon.sh
│   │   ├── armbian-check-first-login-reboot.sh
│   │   ├── armbian-check-first-login.sh
│   │   ├── armbian-lang.sh
│   │   ├── armbian-ssh-title.sh
│   │   ├── bash_completion.sh
│   │   ├── flatpak.sh
│   │   ├── gnome-session_gnomerc.sh
│   │   ├── vte-2.91.sh
│   │   └── vte.csh
│   ├── protocols
│   ├── pulse
│   │   ├── client.conf
│   │   └── client.conf.d
│   ├── python3
│   │   └── debian_config
│   ├── python3.11
│   │   └── sitecustomize.py
│   ├── rc0.d
│   │   ├── K01alsa-utils -> ../init.d/alsa-utils
│   │   ├── K01bluetooth -> ../init.d/bluetooth
│   │   ├── K01docker -> ../init.d/docker
│   │   ├── K01fake-hwclock -> ../init.d/fake-hwclock
│   │   ├── K01gdm3 -> ../init.d/gdm3
│   │   ├── K01hwclock.sh -> ../init.d/hwclock.sh
│   │   ├── K01speech-dispatcher -> ../init.d/speech-dispatcher
│   │   └── K01udev -> ../init.d/udev
│   ├── rc1.d
│   │   ├── K01alsa-utils -> ../init.d/alsa-utils
│   │   ├── K01bluetooth -> ../init.d/bluetooth
│   │   ├── K01docker -> ../init.d/docker
│   │   ├── K01fake-hwclock -> ../init.d/fake-hwclock
│   │   ├── K01gdm3 -> ../init.d/gdm3
│   │   └── K01speech-dispatcher -> ../init.d/speech-dispatcher
│   ├── rc2.d
│   │   ├── K01speech-dispatcher -> ../init.d/speech-dispatcher
│   │   ├── S01bluetooth -> ../init.d/bluetooth
│   │   ├── S01console-setup.sh -> ../init.d/console-setup.sh
│   │   ├── S01cron -> ../init.d/cron
│   │   ├── S01dbus -> ../init.d/dbus
│   │   ├── S01docker -> ../init.d/docker
│   │   ├── S01gdm3 -> ../init.d/gdm3
│   │   ├── S01rsync -> ../init.d/rsync
│   │   ├── S01ssh -> ../init.d/ssh
│   │   └── S01sudo -> ../init.d/sudo
│   ├── rc3.d
│   │   ├── K01speech-dispatcher -> ../init.d/speech-dispatcher
│   │   ├── S01bluetooth -> ../init.d/bluetooth
│   │   ├── S01console-setup.sh -> ../init.d/console-setup.sh
│   │   ├── S01cron -> ../init.d/cron
│   │   ├── S01dbus -> ../init.d/dbus
│   │   ├── S01docker -> ../init.d/docker
│   │   ├── S01gdm3 -> ../init.d/gdm3
│   │   ├── S01rsync -> ../init.d/rsync
│   │   ├── S01ssh -> ../init.d/ssh
│   │   └── S01sudo -> ../init.d/sudo
│   ├── rc4.d
│   │   ├── K01speech-dispatcher -> ../init.d/speech-dispatcher
│   │   ├── S01bluetooth -> ../init.d/bluetooth
│   │   ├── S01console-setup.sh -> ../init.d/console-setup.sh
│   │   ├── S01cron -> ../init.d/cron
│   │   ├── S01dbus -> ../init.d/dbus
│   │   ├── S01docker -> ../init.d/docker
│   │   ├── S01gdm3 -> ../init.d/gdm3
│   │   ├── S01rsync -> ../init.d/rsync
│   │   ├── S01ssh -> ../init.d/ssh
│   │   └── S01sudo -> ../init.d/sudo
│   ├── rc5.d
│   │   ├── K01speech-dispatcher -> ../init.d/speech-dispatcher
│   │   ├── S01bluetooth -> ../init.d/bluetooth
│   │   ├── S01console-setup.sh -> ../init.d/console-setup.sh
│   │   ├── S01cron -> ../init.d/cron
│   │   ├── S01dbus -> ../init.d/dbus
│   │   ├── S01docker -> ../init.d/docker
│   │   ├── S01gdm3 -> ../init.d/gdm3
│   │   ├── S01rsync -> ../init.d/rsync
│   │   ├── S01ssh -> ../init.d/ssh
│   │   └── S01sudo -> ../init.d/sudo
│   ├── rc6.d
│   │   ├── K01alsa-utils -> ../init.d/alsa-utils
│   │   ├── K01bluetooth -> ../init.d/bluetooth
│   │   ├── K01docker -> ../init.d/docker
│   │   ├── K01fake-hwclock -> ../init.d/fake-hwclock
│   │   ├── K01gdm3 -> ../init.d/gdm3
│   │   ├── K01hwclock.sh -> ../init.d/hwclock.sh
│   │   ├── K01speech-dispatcher -> ../init.d/speech-dispatcher
│   │   └── K01udev -> ../init.d/udev
│   ├── rc.local
│   ├── rcS.d
│   │   ├── S01alsa-utils -> ../init.d/alsa-utils
│   │   ├── S01apparmor -> ../init.d/apparmor
│   │   ├── S01fake-hwclock -> ../init.d/fake-hwclock
│   │   ├── S01hwclock.sh -> ../init.d/hwclock.sh
│   │   ├── S01keyboard-setup.sh -> ../init.d/keyboard-setup.sh
│   │   ├── S01kmod -> ../init.d/kmod
│   │   ├── S01procps -> ../init.d/procps
│   │   ├── S01udev -> ../init.d/udev
│   │   └── S01x11-common -> ../init.d/x11-common
│   ├── resolv.conf -> /run/systemd/resolve/stub-resolv.conf
│   ├── rmt -> /usr/sbin/rmt
│   ├── rpc
│   ├── rsyslog.conf
│   ├── rsyslog.d
│   ├── runit
│   │   └── runsvdir
│   │       └── default
│   │           └── ssh -> /etc/sv/ssh
│   ├── rygel.conf
│   ├── sane.d
│   │   ├── abaton.conf
│   │   ├── agfafocus.conf
│   │   ├── apple.conf
│   │   ├── artec.conf
│   │   ├── artec_eplus48u.conf
│   │   ├── avision.conf
│   │   ├── bh.conf
│   │   ├── canon630u.conf
│   │   ├── canon.conf
│   │   ├── canon_dr.conf
│   │   ├── canon_lide70.conf
│   │   ├── canon_pp.conf
│   │   ├── cardscan.conf
│   │   ├── coolscan2.conf
│   │   ├── coolscan3.conf
│   │   ├── coolscan.conf
│   │   ├── dc210.conf
│   │   ├── dc240.conf
│   │   ├── dc25.conf
│   │   ├── dell1600n_net.conf
│   │   ├── dll.conf
│   │   ├── dll.d
│   │   ├── dmc.conf
│   │   ├── epjitsu.conf
│   │   ├── epson2.conf
│   │   ├── epson.conf
│   │   ├── epsonds.conf
│   │   ├── escl.conf
│   │   ├── fujitsu.conf
│   │   ├── genesys.conf
│   │   ├── gphoto2.conf
│   │   ├── gt68xx.conf
│   │   ├── hp3900.conf
│   │   ├── hp4200.conf
│   │   ├── hp5400.conf
│   │   ├── hp.conf
│   │   ├── hpsj5s.conf
│   │   ├── hs2p.conf
│   │   ├── ibm.conf
│   │   ├── kodakaio.conf
│   │   ├── kodak.conf
│   │   ├── kvs1025.conf
│   │   ├── leo.conf
│   │   ├── lexmark.conf
│   │   ├── ma1509.conf
│   │   ├── magicolor.conf
│   │   ├── matsushita.conf
│   │   ├── microtek2.conf
│   │   ├── microtek.conf
│   │   ├── mustek.conf
│   │   ├── mustek_pp.conf
│   │   ├── mustek_usb.conf
│   │   ├── nec.conf
│   │   ├── net.conf
│   │   ├── p5.conf
│   │   ├── pie.conf
│   │   ├── pieusb.conf
│   │   ├── pixma.conf
│   │   ├── plustek.conf
│   │   ├── plustek_pp.conf
│   │   ├── qcam.conf
│   │   ├── ricoh.conf
│   │   ├── rts8891.conf
│   │   ├── s9036.conf
│   │   ├── sceptre.conf
│   │   ├── sharp.conf
│   │   ├── sm3840.conf
│   │   ├── snapscan.conf
│   │   ├── sp15c.conf
│   │   ├── st400.conf
│   │   ├── stv680.conf
│   │   ├── tamarack.conf
│   │   ├── teco1.conf
│   │   ├── teco2.conf
│   │   ├── teco3.conf
│   │   ├── test.conf
│   │   ├── u12.conf
│   │   ├── umax1220u.conf
│   │   ├── umax.conf
│   │   ├── umax_pp.conf
│   │   └── xerox_mfp.conf
│   ├── securetty
│   ├── security
│   │   ├── access.conf
│   │   ├── faillock.conf
│   │   ├── group.conf
│   │   ├── limits.conf
│   │   ├── limits.d
│   │   │   └── 95-pipewire.conf
│   │   ├── namespace.conf
│   │   ├── namespace.d
│   │   ├── namespace.init
│   │   ├── opasswd
│   │   ├── pam_env.conf
│   │   ├── pwquality.conf
│   │   ├── sepermit.conf
│   │   └── time.conf
│   ├── selinux
│   │   └── semanage.conf
│   ├── sensors3.conf
│   ├── sensors.d
│   ├── services
│   ├── sgml
│   │   ├── catalog -> /var/lib/sgml-base/supercatalog
│   │   └── xml-core.cat
│   ├── shadow
│   ├── shadow-
│   ├── shells
│   ├── skel
│   ├── snmp
│   │   └── snmp.conf
│   ├── speech-dispatcher
│   │   ├── clients
│   │   │   └── emacs.conf
│   │   ├── modules
│   │   │   ├── cicero.conf
│   │   │   ├── dtk-generic.conf
│   │   │   ├── epos-generic.conf
│   │   │   ├── espeak.conf
│   │   │   ├── espeak-mbrola-generic.conf
│   │   │   ├── espeak-ng.conf
│   │   │   ├── espeak-ng-mbrola.conf
│   │   │   ├── espeak-ng-mbrola-generic.conf
│   │   │   ├── festival.conf
│   │   │   ├── flite.conf
│   │   │   ├── llia_phon-generic.conf
│   │   │   ├── mary-generic.conf
│   │   │   ├── mimic3-generic.conf
│   │   │   └── swift-generic.conf
│   │   └── speechd.conf
│   ├── ssh
│   │   ├── moduli
│   │   ├── ssh_config
│   │   ├── ssh_config.d
│   │   ├── sshd_config
│   │   ├── sshd_config.d
│   │   ├── sshd_config.ucf-dist
│   │   ├── ssh_host_ecdsa_key
│   │   ├── ssh_host_ecdsa_key.pub
│   │   ├── ssh_host_ed25519_key
│   │   ├── ssh_host_ed25519_key.pub
│   │   ├── ssh_host_rsa_key
│   │   └── ssh_host_rsa_key.pub
│   ├── ssl
│   │   ├── certs
│   │   │   ├── 002c0b4f.0 -> GlobalSign_Root_R46.pem
│   │   │   ├── 02265526.0 -> Entrust_Root_Certification_Authority_-_G2.pem
│   │   │   ├── 062cdee6.0 -> GlobalSign_Root_CA_-_R3.pem
│   │   │   ├── 064e0aa9.0 -> QuoVadis_Root_CA_2_G3.pem
│   │   │   ├── 06dc52d5.0 -> SSL.com_EV_Root_Certification_Authority_RSA_R2.pem
│   │   │   ├── 08063a00.0 -> Security_Communication_RootCA3.pem
│   │   │   ├── 09789157.0 -> Starfield_Services_Root_Certificate_Authority_-_G2.pem
│   │   │   ├── 0a775a30.0 -> GTS_Root_R3.pem
│   │   │   ├── 0b1b94ef.0 -> CFCA_EV_ROOT.pem
│   │   │   ├── 0b9bc432.0 -> ISRG_Root_X2.pem
│   │   │   ├── 0bf05006.0 -> SSL.com_Root_Certification_Authority_ECC.pem
│   │   │   ├── 0f5dc4f3.0 -> UCA_Extended_Validation_Root.pem
│   │   │   ├── 0f6fa695.0 -> GDCA_TrustAUTH_R5_ROOT.pem
│   │   │   ├── 1001acf7.0 -> GTS_Root_R1.pem
│   │   │   ├── 106f3e4d.0 -> Entrust_Root_Certification_Authority_-_EC1.pem
│   │   │   ├── 14bc7599.0 -> emSign_ECC_Root_CA_-_G3.pem
│   │   │   ├── 18856ac4.0 -> SecureSign_RootCA11.pem
│   │   │   ├── 1d3472b9.0 -> GlobalSign_ECC_Root_CA_-_R5.pem
│   │   │   ├── 1e08bfd1.0 -> IdenTrust_Public_Sector_Root_CA_1.pem
│   │   │   ├── 1e09d511.0 -> T-TeleSec_GlobalRoot_Class_2.pem
│   │   │   ├── 244b5494.0 -> DigiCert_High_Assurance_EV_Root_CA.pem
│   │   │   ├── 2923b3f9.0 -> emSign_Root_CA_-_G1.pem
│   │   │   ├── 2ae6433e.0 -> CA_Disig_Root_R2.pem
│   │   │   ├── 2b349938.0 -> AffirmTrust_Commercial.pem
│   │   │   ├── 32888f65.0 -> Hellenic_Academic_and_Research_Institutions_RootCA_2015.pem
│   │   │   ├── 3513523f.0 -> DigiCert_Global_Root_CA.pem
│   │   │   ├── 3bde41ac.0 -> Autoridad_de_Certificacion_Firmaprofesional_CIF_A62634068.pem
│   │   │   ├── 3bde41ac.1 -> Autoridad_de_Certificacion_Firmaprofesional_CIF_A62634068_2.pem
│   │   │   ├── 3e44d2f7.0 -> TrustCor_RootCert_CA-2.pem
│   │   │   ├── 3e45d192.0 -> Hongkong_Post_Root_CA_1.pem
│   │   │   ├── 3fb36b73.0 -> NAVER_Global_Root_Certification_Authority.pem
│   │   │   ├── 40193066.0 -> Certum_Trusted_Network_CA_2.pem
│   │   │   ├── 4042bcee.0 -> ISRG_Root_X1.pem
│   │   │   ├── 40547a79.0 -> COMODO_Certification_Authority.pem
│   │   │   ├── 406c9bb1.0 -> emSign_Root_CA_-_C1.pem
│   │   │   ├── 48bec511.0 -> Certum_Trusted_Network_CA.pem
│   │   │   ├── 4b718d9b.0 -> emSign_ECC_Root_CA_-_C3.pem
│   │   │   ├── 4bfab552.0 -> Starfield_Root_Certificate_Authority_-_G2.pem
│   │   │   ├── 4f316efb.0 -> SwissSign_Gold_CA_-_G2.pem
│   │   │   ├── 5273a94c.0 -> E-Tugra_Certification_Authority.pem
│   │   │   ├── 5443e9e3.0 -> T-TeleSec_GlobalRoot_Class_3.pem
│   │   │   ├── 54657681.0 -> Buypass_Class_2_Root_CA.pem
│   │   │   ├── 57bcb2da.0 -> SwissSign_Silver_CA_-_G2.pem
│   │   │   ├── 5860aaa6.0 -> Security_Communication_ECC_RootCA1.pem
│   │   │   ├── 5931b5bc.0 -> D-TRUST_EV_Root_CA_1_2020.pem
│   │   │   ├── 5a7722fb.0 -> E-Tugra_Global_Root_CA_ECC_v3.pem
│   │   │   ├── 5ad8a5d6.0 -> GlobalSign_Root_CA.pem
│   │   │   ├── 5cd81ad7.0 -> TeliaSonera_Root_CA_v1.pem
│   │   │   ├── 5d3033c5.0 -> TrustCor_RootCert_CA-1.pem
│   │   │   ├── 5e98733a.0 -> Entrust_Root_Certification_Authority_-_G4.pem
│   │   │   ├── 5f15c80c.0 -> TWCA_Global_Root_CA.pem
│   │   │   ├── 5f618aec.0 -> certSIGN_Root_CA_G2.pem
│   │   │   ├── 607986c7.0 -> DigiCert_Global_Root_G2.pem
│   │   │   ├── 626dceaf.0 -> GTS_Root_R2.pem
│   │   │   ├── 653b494a.0 -> Baltimore_CyberTrust_Root.pem
│   │   │   ├── 66445960.0 -> E-Tugra_Global_Root_CA_RSA_v3.pem
│   │   │   ├── 68dd7389.0 -> Hongkong_Post_Root_CA_3.pem
│   │   │   ├── 6b99d060.0 -> Entrust_Root_Certification_Authority.pem
│   │   │   ├── 6d41d539.0 -> Amazon_Root_CA_2.pem
│   │   │   ├── 6fa5da56.0 -> SSL.com_Root_Certification_Authority_RSA.pem
│   │   │   ├── 706f604c.0 -> XRamp_Global_CA_Root.pem
│   │   │   ├── 749e9e03.0 -> QuoVadis_Root_CA_1_G3.pem
│   │   │   ├── 75d1b2ed.0 -> DigiCert_Trusted_Root_G4.pem
│   │   │   ├── 76faf6c0.0 -> QuoVadis_Root_CA_3.pem
│   │   │   ├── 7719f463.0 -> Hellenic_Academic_and_Research_Institutions_ECC_RootCA_2015.pem
│   │   │   ├── 773e07ad.0 -> OISTE_WISeKey_Global_Root_GC_CA.pem
│   │   │   ├── 7a3adc42.0 -> vTrus_Root_CA.pem
│   │   │   ├── 7a780d93.0 -> Certainly_Root_R1.pem
│   │   │   ├── 7aaf71c0.0 -> TrustCor_ECA-1.pem
│   │   │   ├── 7f3d5d1d.0 -> DigiCert_Assured_ID_Root_G3.pem
│   │   │   ├── 8160b96c.0 -> Microsec_e-Szigno_Root_CA_2009.pem
│   │   │   ├── 8508e720.0 -> Certainly_Root_E1.pem
│   │   │   ├── 8cb5ee0f.0 -> Amazon_Root_CA_3.pem
│   │   │   ├── 8d86cdd1.0 -> certSIGN_ROOT_CA.pem
│   │   │   ├── 8d89cda1.0 -> Microsoft_ECC_Root_Certificate_Authority_2017.pem
│   │   │   ├── 8f103249.0 -> Telia_Root_CA_v2.pem
│   │   │   ├── 9046744a.0 -> Sectigo_Public_Server_Authentication_Root_R46.pem
│   │   │   ├── 90c5a3c8.0 -> HiPKI_Root_CA_-_G1.pem
│   │   │   ├── 930ac5d2.0 -> Actalis_Authentication_Root_CA.pem
│   │   │   ├── 93bc0acc.0 -> AffirmTrust_Networking.pem
│   │   │   ├── 9482e63a.0 -> Certum_EC-384_CA.pem
│   │   │   ├── 9846683b.0 -> DigiCert_TLS_ECC_P384_Root_G5.pem
│   │   │   ├── 988a38cb.0 -> NetLock_Arany_=Class_Gold=_Főtanúsítvány.pem
│   │   │   ├── 9b5697b0.0 -> Trustwave_Global_ECC_P256_Certification_Authority.pem
│   │   │   ├── 9c8dfbd4.0 -> AffirmTrust_Premium_ECC.pem
│   │   │   ├── 9d04f354.0 -> DigiCert_Assured_ID_Root_G2.pem
│   │   │   ├── 9ef4a08a.0 -> D-TRUST_BR_Root_CA_1_2020.pem
│   │   │   ├── 9f727ac7.0 -> HARICA_TLS_RSA_Root_CA_2021.pem
│   │   │   ├── a3418fda.0 -> GTS_Root_R4.pem
│   │   │   ├── a94d09e5.0 -> ACCVRAIZ1.pem
│   │   │   ├── ACCVRAIZ1.pem -> /usr/share/ca-certificates/mozilla/ACCVRAIZ1.crt
│   │   │   ├── AC_RAIZ_FNMT-RCM.pem -> /usr/share/ca-certificates/mozilla/AC_RAIZ_FNMT-RCM.crt
│   │   │   ├── AC_RAIZ_FNMT-RCM_SERVIDORES_SEGUROS.pem -> /usr/share/ca-certificates/mozilla/AC_RAIZ_FNMT-RCM_SERVIDORES_SEGUROS.crt
│   │   │   ├── Actalis_Authentication_Root_CA.pem -> /usr/share/ca-certificates/mozilla/Actalis_Authentication_Root_CA.crt
│   │   │   ├── aee5f10d.0 -> Entrust.net_Premium_2048_Secure_Server_CA.pem
│   │   │   ├── AffirmTrust_Commercial.pem -> /usr/share/ca-certificates/mozilla/AffirmTrust_Commercial.crt
│   │   │   ├── AffirmTrust_Networking.pem -> /usr/share/ca-certificates/mozilla/AffirmTrust_Networking.crt
│   │   │   ├── AffirmTrust_Premium_ECC.pem -> /usr/share/ca-certificates/mozilla/AffirmTrust_Premium_ECC.crt
│   │   │   ├── AffirmTrust_Premium.pem -> /usr/share/ca-certificates/mozilla/AffirmTrust_Premium.crt
│   │   │   ├── Amazon_Root_CA_1.pem -> /usr/share/ca-certificates/mozilla/Amazon_Root_CA_1.crt
│   │   │   ├── Amazon_Root_CA_2.pem -> /usr/share/ca-certificates/mozilla/Amazon_Root_CA_2.crt
│   │   │   ├── Amazon_Root_CA_3.pem -> /usr/share/ca-certificates/mozilla/Amazon_Root_CA_3.crt
│   │   │   ├── Amazon_Root_CA_4.pem -> /usr/share/ca-certificates/mozilla/Amazon_Root_CA_4.crt
│   │   │   ├── ANF_Secure_Server_Root_CA.pem -> /usr/share/ca-certificates/mozilla/ANF_Secure_Server_Root_CA.crt
│   │   │   ├── Atos_TrustedRoot_2011.pem -> /usr/share/ca-certificates/mozilla/Atos_TrustedRoot_2011.crt
│   │   │   ├── Autoridad_de_Certificacion_Firmaprofesional_CIF_A62634068_2.pem -> /usr/share/ca-certificates/mozilla/Autoridad_de_Certificacion_Firmaprofesional_CIF_A62634068_2.crt
│   │   │   ├── Autoridad_de_Certificacion_Firmaprofesional_CIF_A62634068.pem -> /usr/share/ca-certificates/mozilla/Autoridad_de_Certificacion_Firmaprofesional_CIF_A62634068.crt
│   │   │   ├── b0e59380.0 -> GlobalSign_ECC_Root_CA_-_R4.pem
│   │   │   ├── b1159c4c.0 -> DigiCert_Assured_ID_Root_CA.pem
│   │   │   ├── b433981b.0 -> ANF_Secure_Server_Root_CA.pem
│   │   │   ├── b66938e9.0 -> Secure_Global_CA.pem
│   │   │   ├── b727005e.0 -> AffirmTrust_Premium.pem
│   │   │   ├── b7a5b843.0 -> TWCA_Root_Certification_Authority.pem
│   │   │   ├── b81b93f0.0 -> AC_RAIZ_FNMT-RCM_SERVIDORES_SEGUROS.pem
│   │   │   ├── Baltimore_CyberTrust_Root.pem -> /usr/share/ca-certificates/mozilla/Baltimore_CyberTrust_Root.crt
│   │   │   ├── bf53fb88.0 -> Microsoft_RSA_Root_Certificate_Authority_2017.pem
│   │   │   ├── Buypass_Class_2_Root_CA.pem -> /usr/share/ca-certificates/mozilla/Buypass_Class_2_Root_CA.crt
│   │   │   ├── Buypass_Class_3_Root_CA.pem -> /usr/share/ca-certificates/mozilla/Buypass_Class_3_Root_CA.crt
│   │   │   ├── c01eb047.0 -> UCA_Global_G2_Root.pem
│   │   │   ├── c28a8a30.0 -> D-TRUST_Root_Class_3_CA_2_2009.pem
│   │   │   ├── ca6e4ad9.0 -> ePKI_Root_Certification_Authority.pem
│   │   │   ├── ca-certificates.crt
│   │   │   ├── CA_Disig_Root_R2.pem -> /usr/share/ca-certificates/mozilla/CA_Disig_Root_R2.crt
│   │   │   ├── cbf06781.0 -> Go_Daddy_Root_Certificate_Authority_-_G2.pem
│   │   │   ├── cc450945.0 -> Izenpe.com.pem
│   │   │   ├── cd58d51e.0 -> Security_Communication_RootCA2.pem
│   │   │   ├── cd8c0d63.0 -> AC_RAIZ_FNMT-RCM.pem
│   │   │   ├── ce5e74ef.0 -> Amazon_Root_CA_1.pem
│   │   │   ├── Certainly_Root_E1.pem -> /usr/share/ca-certificates/mozilla/Certainly_Root_E1.crt
│   │   │   ├── Certainly_Root_R1.pem -> /usr/share/ca-certificates/mozilla/Certainly_Root_R1.crt
│   │   │   ├── Certigna.pem -> /usr/share/ca-certificates/mozilla/Certigna.crt
│   │   │   ├── Certigna_Root_CA.pem -> /usr/share/ca-certificates/mozilla/Certigna_Root_CA.crt
│   │   │   ├── certSIGN_Root_CA_G2.pem -> /usr/share/ca-certificates/mozilla/certSIGN_Root_CA_G2.crt
│   │   │   ├── certSIGN_ROOT_CA.pem -> /usr/share/ca-certificates/mozilla/certSIGN_ROOT_CA.crt
│   │   │   ├── Certum_EC-384_CA.pem -> /usr/share/ca-certificates/mozilla/Certum_EC-384_CA.crt
│   │   │   ├── Certum_Trusted_Network_CA_2.pem -> /usr/share/ca-certificates/mozilla/Certum_Trusted_Network_CA_2.crt
│   │   │   ├── Certum_Trusted_Network_CA.pem -> /usr/share/ca-certificates/mozilla/Certum_Trusted_Network_CA.crt
│   │   │   ├── Certum_Trusted_Root_CA.pem -> /usr/share/ca-certificates/mozilla/Certum_Trusted_Root_CA.crt
│   │   │   ├── CFCA_EV_ROOT.pem -> /usr/share/ca-certificates/mozilla/CFCA_EV_ROOT.crt
│   │   │   ├── Comodo_AAA_Services_root.pem -> /usr/share/ca-certificates/mozilla/Comodo_AAA_Services_root.crt
│   │   │   ├── COMODO_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/COMODO_Certification_Authority.crt
│   │   │   ├── COMODO_ECC_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/COMODO_ECC_Certification_Authority.crt
│   │   │   ├── COMODO_RSA_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/COMODO_RSA_Certification_Authority.crt
│   │   │   ├── d4dae3dd.0 -> D-TRUST_Root_Class_3_CA_2_EV_2009.pem
│   │   │   ├── d52c538d.0 -> DigiCert_TLS_RSA4096_Root_G5.pem
│   │   │   ├── d6325660.0 -> COMODO_RSA_Certification_Authority.pem
│   │   │   ├── d7e8dc79.0 -> QuoVadis_Root_CA_2.pem
│   │   │   ├── d887a5bb.0 -> Trustwave_Global_ECC_P384_Certification_Authority.pem
│   │   │   ├── da0cfd1d.0 -> Sectigo_Public_Server_Authentication_Root_E46.pem
│   │   │   ├── dc4d6a89.0 -> GlobalSign_Root_CA_-_R6.pem
│   │   │   ├── dd8e9d41.0 -> DigiCert_Global_Root_G3.pem
│   │   │   ├── de6d66f3.0 -> Amazon_Root_CA_4.pem
│   │   │   ├── DigiCert_Assured_ID_Root_CA.pem -> /usr/share/ca-certificates/mozilla/DigiCert_Assured_ID_Root_CA.crt
│   │   │   ├── DigiCert_Assured_ID_Root_G2.pem -> /usr/share/ca-certificates/mozilla/DigiCert_Assured_ID_Root_G2.crt
│   │   │   ├── DigiCert_Assured_ID_Root_G3.pem -> /usr/share/ca-certificates/mozilla/DigiCert_Assured_ID_Root_G3.crt
│   │   │   ├── DigiCert_Global_Root_CA.pem -> /usr/share/ca-certificates/mozilla/DigiCert_Global_Root_CA.crt
│   │   │   ├── DigiCert_Global_Root_G2.pem -> /usr/share/ca-certificates/mozilla/DigiCert_Global_Root_G2.crt
│   │   │   ├── DigiCert_Global_Root_G3.pem -> /usr/share/ca-certificates/mozilla/DigiCert_Global_Root_G3.crt
│   │   │   ├── DigiCert_High_Assurance_EV_Root_CA.pem -> /usr/share/ca-certificates/mozilla/DigiCert_High_Assurance_EV_Root_CA.crt
│   │   │   ├── DigiCert_TLS_ECC_P384_Root_G5.pem -> /usr/share/ca-certificates/mozilla/DigiCert_TLS_ECC_P384_Root_G5.crt
│   │   │   ├── DigiCert_TLS_RSA4096_Root_G5.pem -> /usr/share/ca-certificates/mozilla/DigiCert_TLS_RSA4096_Root_G5.crt
│   │   │   ├── DigiCert_Trusted_Root_G4.pem -> /usr/share/ca-certificates/mozilla/DigiCert_Trusted_Root_G4.crt
│   │   │   ├── D-TRUST_BR_Root_CA_1_2020.pem -> /usr/share/ca-certificates/mozilla/D-TRUST_BR_Root_CA_1_2020.crt
│   │   │   ├── D-TRUST_EV_Root_CA_1_2020.pem -> /usr/share/ca-certificates/mozilla/D-TRUST_EV_Root_CA_1_2020.crt
│   │   │   ├── D-TRUST_Root_Class_3_CA_2_2009.pem -> /usr/share/ca-certificates/mozilla/D-TRUST_Root_Class_3_CA_2_2009.crt
│   │   │   ├── D-TRUST_Root_Class_3_CA_2_EV_2009.pem -> /usr/share/ca-certificates/mozilla/D-TRUST_Root_Class_3_CA_2_EV_2009.crt
│   │   │   ├── e113c810.0 -> Certigna.pem
│   │   │   ├── e18bfb83.0 -> QuoVadis_Root_CA_3_G3.pem
│   │   │   ├── e35234b1.0 -> Certum_Trusted_Root_CA.pem
│   │   │   ├── e36a6752.0 -> Atos_TrustedRoot_2011.pem
│   │   │   ├── e73d606e.0 -> OISTE_WISeKey_Global_Root_GB_CA.pem
│   │   │   ├── e868b802.0 -> e-Szigno_Root_CA_2017.pem
│   │   │   ├── e8de2f56.0 -> Buypass_Class_3_Root_CA.pem
│   │   │   ├── ecccd8db.0 -> HARICA_TLS_ECC_Root_CA_2021.pem
│   │   │   ├── ed858448.0 -> vTrus_ECC_Root_CA.pem
│   │   │   ├── ee64a828.0 -> Comodo_AAA_Services_root.pem
│   │   │   ├── eed8c118.0 -> COMODO_ECC_Certification_Authority.pem
│   │   │   ├── ef954a4e.0 -> IdenTrust_Commercial_Root_CA_1.pem
│   │   │   ├── emSign_ECC_Root_CA_-_C3.pem -> /usr/share/ca-certificates/mozilla/emSign_ECC_Root_CA_-_C3.crt
│   │   │   ├── emSign_ECC_Root_CA_-_G3.pem -> /usr/share/ca-certificates/mozilla/emSign_ECC_Root_CA_-_G3.crt
│   │   │   ├── emSign_Root_CA_-_C1.pem -> /usr/share/ca-certificates/mozilla/emSign_Root_CA_-_C1.crt
│   │   │   ├── emSign_Root_CA_-_G1.pem -> /usr/share/ca-certificates/mozilla/emSign_Root_CA_-_G1.crt
│   │   │   ├── Entrust.net_Premium_2048_Secure_Server_CA.pem -> /usr/share/ca-certificates/mozilla/Entrust.net_Premium_2048_Secure_Server_CA.crt
│   │   │   ├── Entrust_Root_Certification_Authority_-_EC1.pem -> /usr/share/ca-certificates/mozilla/Entrust_Root_Certification_Authority_-_EC1.crt
│   │   │   ├── Entrust_Root_Certification_Authority_-_G2.pem -> /usr/share/ca-certificates/mozilla/Entrust_Root_Certification_Authority_-_G2.crt
│   │   │   ├── Entrust_Root_Certification_Authority_-_G4.pem -> /usr/share/ca-certificates/mozilla/Entrust_Root_Certification_Authority_-_G4.crt
│   │   │   ├── Entrust_Root_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/Entrust_Root_Certification_Authority.crt
│   │   │   ├── ePKI_Root_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/ePKI_Root_Certification_Authority.crt
│   │   │   ├── e-Szigno_Root_CA_2017.pem -> /usr/share/ca-certificates/mozilla/e-Szigno_Root_CA_2017.crt
│   │   │   ├── E-Tugra_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/E-Tugra_Certification_Authority.crt
│   │   │   ├── E-Tugra_Global_Root_CA_ECC_v3.pem -> /usr/share/ca-certificates/mozilla/E-Tugra_Global_Root_CA_ECC_v3.crt
│   │   │   ├── E-Tugra_Global_Root_CA_RSA_v3.pem -> /usr/share/ca-certificates/mozilla/E-Tugra_Global_Root_CA_RSA_v3.crt
│   │   │   ├── f081611a.0 -> Go_Daddy_Class_2_CA.pem
│   │   │   ├── f0c70a8d.0 -> SSL.com_EV_Root_Certification_Authority_ECC.pem
│   │   │   ├── f249de83.0 -> Trustwave_Global_Certification_Authority.pem
│   │   │   ├── f30dd6ad.0 -> USERTrust_ECC_Certification_Authority.pem
│   │   │   ├── f3377b1b.0 -> Security_Communication_Root_CA.pem
│   │   │   ├── f387163d.0 -> Starfield_Class_2_CA.pem
│   │   │   ├── f39fc864.0 -> SecureTrust_CA.pem
│   │   │   ├── f51bb24c.0 -> Certigna_Root_CA.pem
│   │   │   ├── fa5da96b.0 -> GLOBALTRUST_2020.pem
│   │   │   ├── fc5a8f99.0 -> USERTrust_RSA_Certification_Authority.pem
│   │   │   ├── fd64f3fc.0 -> TunTrust_Root_CA.pem
│   │   │   ├── fe8a2cd8.0 -> SZAFIR_ROOT_CA2.pem
│   │   │   ├── feffd413.0 -> GlobalSign_Root_E46.pem
│   │   │   ├── ff34af3f.0 -> TUBITAK_Kamu_SM_SSL_Kok_Sertifikasi_-_Surum_1.pem
│   │   │   ├── GDCA_TrustAUTH_R5_ROOT.pem -> /usr/share/ca-certificates/mozilla/GDCA_TrustAUTH_R5_ROOT.crt
│   │   │   ├── GlobalSign_ECC_Root_CA_-_R4.pem -> /usr/share/ca-certificates/mozilla/GlobalSign_ECC_Root_CA_-_R4.crt
│   │   │   ├── GlobalSign_ECC_Root_CA_-_R5.pem -> /usr/share/ca-certificates/mozilla/GlobalSign_ECC_Root_CA_-_R5.crt
│   │   │   ├── GlobalSign_Root_CA.pem -> /usr/share/ca-certificates/mozilla/GlobalSign_Root_CA.crt
│   │   │   ├── GlobalSign_Root_CA_-_R3.pem -> /usr/share/ca-certificates/mozilla/GlobalSign_Root_CA_-_R3.crt
│   │   │   ├── GlobalSign_Root_CA_-_R6.pem -> /usr/share/ca-certificates/mozilla/GlobalSign_Root_CA_-_R6.crt
│   │   │   ├── GlobalSign_Root_E46.pem -> /usr/share/ca-certificates/mozilla/GlobalSign_Root_E46.crt
│   │   │   ├── GlobalSign_Root_R46.pem -> /usr/share/ca-certificates/mozilla/GlobalSign_Root_R46.crt
│   │   │   ├── GLOBALTRUST_2020.pem -> /usr/share/ca-certificates/mozilla/GLOBALTRUST_2020.crt
│   │   │   ├── Go_Daddy_Class_2_CA.pem -> /usr/share/ca-certificates/mozilla/Go_Daddy_Class_2_CA.crt
│   │   │   ├── Go_Daddy_Root_Certificate_Authority_-_G2.pem -> /usr/share/ca-certificates/mozilla/Go_Daddy_Root_Certificate_Authority_-_G2.crt
│   │   │   ├── GTS_Root_R1.pem -> /usr/share/ca-certificates/mozilla/GTS_Root_R1.crt
│   │   │   ├── GTS_Root_R2.pem -> /usr/share/ca-certificates/mozilla/GTS_Root_R2.crt
│   │   │   ├── GTS_Root_R3.pem -> /usr/share/ca-certificates/mozilla/GTS_Root_R3.crt
│   │   │   ├── GTS_Root_R4.pem -> /usr/share/ca-certificates/mozilla/GTS_Root_R4.crt
│   │   │   ├── HARICA_TLS_ECC_Root_CA_2021.pem -> /usr/share/ca-certificates/mozilla/HARICA_TLS_ECC_Root_CA_2021.crt
│   │   │   ├── HARICA_TLS_RSA_Root_CA_2021.pem -> /usr/share/ca-certificates/mozilla/HARICA_TLS_RSA_Root_CA_2021.crt
│   │   │   ├── Hellenic_Academic_and_Research_Institutions_ECC_RootCA_2015.pem -> /usr/share/ca-certificates/mozilla/Hellenic_Academic_and_Research_Institutions_ECC_RootCA_2015.crt
│   │   │   ├── Hellenic_Academic_and_Research_Institutions_RootCA_2015.pem -> /usr/share/ca-certificates/mozilla/Hellenic_Academic_and_Research_Institutions_RootCA_2015.crt
│   │   │   ├── HiPKI_Root_CA_-_G1.pem -> /usr/share/ca-certificates/mozilla/HiPKI_Root_CA_-_G1.crt
│   │   │   ├── Hongkong_Post_Root_CA_1.pem -> /usr/share/ca-certificates/mozilla/Hongkong_Post_Root_CA_1.crt
│   │   │   ├── Hongkong_Post_Root_CA_3.pem -> /usr/share/ca-certificates/mozilla/Hongkong_Post_Root_CA_3.crt
│   │   │   ├── IdenTrust_Commercial_Root_CA_1.pem -> /usr/share/ca-certificates/mozilla/IdenTrust_Commercial_Root_CA_1.crt
│   │   │   ├── IdenTrust_Public_Sector_Root_CA_1.pem -> /usr/share/ca-certificates/mozilla/IdenTrust_Public_Sector_Root_CA_1.crt
│   │   │   ├── ISRG_Root_X1.pem -> /usr/share/ca-certificates/mozilla/ISRG_Root_X1.crt
│   │   │   ├── ISRG_Root_X2.pem -> /usr/share/ca-certificates/mozilla/ISRG_Root_X2.crt
│   │   │   ├── Izenpe.com.pem -> /usr/share/ca-certificates/mozilla/Izenpe.com.crt
│   │   │   ├── Microsec_e-Szigno_Root_CA_2009.pem -> /usr/share/ca-certificates/mozilla/Microsec_e-Szigno_Root_CA_2009.crt
│   │   │   ├── Microsoft_ECC_Root_Certificate_Authority_2017.pem -> /usr/share/ca-certificates/mozilla/Microsoft_ECC_Root_Certificate_Authority_2017.crt
│   │   │   ├── Microsoft_RSA_Root_Certificate_Authority_2017.pem -> /usr/share/ca-certificates/mozilla/Microsoft_RSA_Root_Certificate_Authority_2017.crt
│   │   │   ├── NAVER_Global_Root_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/NAVER_Global_Root_Certification_Authority.crt
│   │   │   ├── NetLock_Arany_=Class_Gold=_Főtanúsítvány.pem -> /usr/share/ca-certificates/mozilla/NetLock_Arany_=Class_Gold=_Főtanúsítvány.crt
│   │   │   ├── OISTE_WISeKey_Global_Root_GB_CA.pem -> /usr/share/ca-certificates/mozilla/OISTE_WISeKey_Global_Root_GB_CA.crt
│   │   │   ├── OISTE_WISeKey_Global_Root_GC_CA.pem -> /usr/share/ca-certificates/mozilla/OISTE_WISeKey_Global_Root_GC_CA.crt
│   │   │   ├── QuoVadis_Root_CA_1_G3.pem -> /usr/share/ca-certificates/mozilla/QuoVadis_Root_CA_1_G3.crt
│   │   │   ├── QuoVadis_Root_CA_2_G3.pem -> /usr/share/ca-certificates/mozilla/QuoVadis_Root_CA_2_G3.crt
│   │   │   ├── QuoVadis_Root_CA_2.pem -> /usr/share/ca-certificates/mozilla/QuoVadis_Root_CA_2.crt
│   │   │   ├── QuoVadis_Root_CA_3_G3.pem -> /usr/share/ca-certificates/mozilla/QuoVadis_Root_CA_3_G3.crt
│   │   │   ├── QuoVadis_Root_CA_3.pem -> /usr/share/ca-certificates/mozilla/QuoVadis_Root_CA_3.crt
│   │   │   ├── Sectigo_Public_Server_Authentication_Root_E46.pem -> /usr/share/ca-certificates/mozilla/Sectigo_Public_Server_Authentication_Root_E46.crt
│   │   │   ├── Sectigo_Public_Server_Authentication_Root_R46.pem -> /usr/share/ca-certificates/mozilla/Sectigo_Public_Server_Authentication_Root_R46.crt
│   │   │   ├── Secure_Global_CA.pem -> /usr/share/ca-certificates/mozilla/Secure_Global_CA.crt
│   │   │   ├── SecureSign_RootCA11.pem -> /usr/share/ca-certificates/mozilla/SecureSign_RootCA11.crt
│   │   │   ├── SecureTrust_CA.pem -> /usr/share/ca-certificates/mozilla/SecureTrust_CA.crt
│   │   │   ├── Security_Communication_ECC_RootCA1.pem -> /usr/share/ca-certificates/mozilla/Security_Communication_ECC_RootCA1.crt
│   │   │   ├── Security_Communication_RootCA2.pem -> /usr/share/ca-certificates/mozilla/Security_Communication_RootCA2.crt
│   │   │   ├── Security_Communication_RootCA3.pem -> /usr/share/ca-certificates/mozilla/Security_Communication_RootCA3.crt
│   │   │   ├── Security_Communication_Root_CA.pem -> /usr/share/ca-certificates/mozilla/Security_Communication_Root_CA.crt
│   │   │   ├── SSL.com_EV_Root_Certification_Authority_ECC.pem -> /usr/share/ca-certificates/mozilla/SSL.com_EV_Root_Certification_Authority_ECC.crt
│   │   │   ├── SSL.com_EV_Root_Certification_Authority_RSA_R2.pem -> /usr/share/ca-certificates/mozilla/SSL.com_EV_Root_Certification_Authority_RSA_R2.crt
│   │   │   ├── SSL.com_Root_Certification_Authority_ECC.pem -> /usr/share/ca-certificates/mozilla/SSL.com_Root_Certification_Authority_ECC.crt
│   │   │   ├── SSL.com_Root_Certification_Authority_RSA.pem -> /usr/share/ca-certificates/mozilla/SSL.com_Root_Certification_Authority_RSA.crt
│   │   │   ├── Starfield_Class_2_CA.pem -> /usr/share/ca-certificates/mozilla/Starfield_Class_2_CA.crt
│   │   │   ├── Starfield_Root_Certificate_Authority_-_G2.pem -> /usr/share/ca-certificates/mozilla/Starfield_Root_Certificate_Authority_-_G2.crt
│   │   │   ├── Starfield_Services_Root_Certificate_Authority_-_G2.pem -> /usr/share/ca-certificates/mozilla/Starfield_Services_Root_Certificate_Authority_-_G2.crt
│   │   │   ├── SwissSign_Gold_CA_-_G2.pem -> /usr/share/ca-certificates/mozilla/SwissSign_Gold_CA_-_G2.crt
│   │   │   ├── SwissSign_Silver_CA_-_G2.pem -> /usr/share/ca-certificates/mozilla/SwissSign_Silver_CA_-_G2.crt
│   │   │   ├── SZAFIR_ROOT_CA2.pem -> /usr/share/ca-certificates/mozilla/SZAFIR_ROOT_CA2.crt
│   │   │   ├── Telia_Root_CA_v2.pem -> /usr/share/ca-certificates/mozilla/Telia_Root_CA_v2.crt
│   │   │   ├── TeliaSonera_Root_CA_v1.pem -> /usr/share/ca-certificates/mozilla/TeliaSonera_Root_CA_v1.crt
│   │   │   ├── TrustCor_ECA-1.pem -> /usr/share/ca-certificates/mozilla/TrustCor_ECA-1.crt
│   │   │   ├── TrustCor_RootCert_CA-1.pem -> /usr/share/ca-certificates/mozilla/TrustCor_RootCert_CA-1.crt
│   │   │   ├── TrustCor_RootCert_CA-2.pem -> /usr/share/ca-certificates/mozilla/TrustCor_RootCert_CA-2.crt
│   │   │   ├── Trustwave_Global_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/Trustwave_Global_Certification_Authority.crt
│   │   │   ├── Trustwave_Global_ECC_P256_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/Trustwave_Global_ECC_P256_Certification_Authority.crt
│   │   │   ├── Trustwave_Global_ECC_P384_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/Trustwave_Global_ECC_P384_Certification_Authority.crt
│   │   │   ├── T-TeleSec_GlobalRoot_Class_2.pem -> /usr/share/ca-certificates/mozilla/T-TeleSec_GlobalRoot_Class_2.crt
│   │   │   ├── T-TeleSec_GlobalRoot_Class_3.pem -> /usr/share/ca-certificates/mozilla/T-TeleSec_GlobalRoot_Class_3.crt
│   │   │   ├── TUBITAK_Kamu_SM_SSL_Kok_Sertifikasi_-_Surum_1.pem -> /usr/share/ca-certificates/mozilla/TUBITAK_Kamu_SM_SSL_Kok_Sertifikasi_-_Surum_1.crt
│   │   │   ├── TunTrust_Root_CA.pem -> /usr/share/ca-certificates/mozilla/TunTrust_Root_CA.crt
│   │   │   ├── TWCA_Global_Root_CA.pem -> /usr/share/ca-certificates/mozilla/TWCA_Global_Root_CA.crt
│   │   │   ├── TWCA_Root_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/TWCA_Root_Certification_Authority.crt
│   │   │   ├── UCA_Extended_Validation_Root.pem -> /usr/share/ca-certificates/mozilla/UCA_Extended_Validation_Root.crt
│   │   │   ├── UCA_Global_G2_Root.pem -> /usr/share/ca-certificates/mozilla/UCA_Global_G2_Root.crt
│   │   │   ├── USERTrust_ECC_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/USERTrust_ECC_Certification_Authority.crt
│   │   │   ├── USERTrust_RSA_Certification_Authority.pem -> /usr/share/ca-certificates/mozilla/USERTrust_RSA_Certification_Authority.crt
│   │   │   ├── vTrus_ECC_Root_CA.pem -> /usr/share/ca-certificates/mozilla/vTrus_ECC_Root_CA.crt
│   │   │   ├── vTrus_Root_CA.pem -> /usr/share/ca-certificates/mozilla/vTrus_Root_CA.crt
│   │   │   └── XRamp_Global_CA_Root.pem -> /usr/share/ca-certificates/mozilla/XRamp_Global_CA_Root.crt
│   │   ├── openssl.cnf
│   │   └── private  [error opening dir]
│   ├── subgid
│   ├── subgid-
│   ├── subuid
│   ├── subuid-
│   ├── sudo.conf
│   ├── sudoers
│   ├── sudoers.d
│   │   └── README
│   ├── sudo_logsrvd.conf
│   ├── sv
│   │   └── ssh
│   │       ├── finish
│   │       ├── log
│   │       │   └── run
│   │       └── run
│   ├── sysctl.conf
│   ├── sysctl.d
│   │   ├── 99-sysctl.conf -> ../sysctl.conf
│   │   └── README.sysctl
│   ├── systemd
│   │   ├── journald.conf
│   │   ├── logind.conf
│   │   ├── network
│   │   │   └── 00-armbian.network.readme
│   │   ├── networkd.conf
│   │   ├── networkd.conf.d
│   │   │   └── mac-duid.conf
│   │   ├── pstore.conf
│   │   ├── resolved.conf
│   │   ├── sleep.conf
│   │   ├── system
│   │   │   ├── basic.target.wants
│   │   │   │   ├── armbian-hardware-monitor.service -> /lib/systemd/system/armbian-hardware-monitor.service
│   │   │   │   ├── armbian-hardware-optimize.service -> /lib/systemd/system/armbian-hardware-optimize.service
│   │   │   │   └── armbian-led-state.service -> /lib/systemd/system/armbian-led-state.service
│   │   │   ├── bluetooth.target.wants
│   │   │   │   └── bluetooth.service -> /lib/systemd/system/bluetooth.service
│   │   │   ├── cloud-final.service.wants
│   │   │   │   └── snapd.seeded.service -> /lib/systemd/system/snapd.seeded.service
│   │   │   ├── dbus-fi.w1.wpa_supplicant1.service -> /lib/systemd/system/wpa_supplicant.service
│   │   │   ├── dbus-org.bluez.service -> /lib/systemd/system/bluetooth.service
│   │   │   ├── dbus-org.freedesktop.Avahi.service -> /lib/systemd/system/avahi-daemon.service
│   │   │   ├── dbus-org.freedesktop.nm-dispatcher.service -> /lib/systemd/system/NetworkManager-dispatcher.service
│   │   │   ├── dbus-org.freedesktop.resolve1.service -> /lib/systemd/system/systemd-resolved.service
│   │   │   ├── dbus-org.freedesktop.timesync1.service -> /lib/systemd/system/systemd-timesyncd.service
│   │   │   ├── default.target.wants
│   │   │   │   └── snap-snapd-24787.mount -> /etc/systemd/system/snap-snapd-24787.mount
│   │   │   ├── display-manager.service -> /lib/systemd/system/gdm3.service
│   │   │   ├── getty@.service.d
│   │   │   ├── getty.target.wants
│   │   │   │   ├── getty@tty1.service -> /lib/systemd/system/getty@.service
│   │   │   │   └── serial-getty@ttyFIQ0.service -> /lib/systemd/system/serial-getty@.service
│   │   │   ├── graphical.target.wants
│   │   │   │   ├── accounts-daemon.service -> /lib/systemd/system/accounts-daemon.service
│   │   │   │   └── udisks2.service -> /lib/systemd/system/udisks2.service
│   │   │   ├── logrotate.service
│   │   │   ├── multi-user.target.wants
│   │   │   │   ├── avahi-daemon.service -> /lib/systemd/system/avahi-daemon.service
│   │   │   │   ├── console-setup.service -> /lib/systemd/system/console-setup.service
│   │   │   │   ├── containerd.service -> /lib/systemd/system/containerd.service
│   │   │   │   ├── cron.service -> /lib/systemd/system/cron.service
│   │   │   │   ├── docker.service -> /lib/systemd/system/docker.service
│   │   │   │   ├── e2scrub_reap.service -> /lib/systemd/system/e2scrub_reap.service
│   │   │   │   ├── NetworkManager.service -> /lib/systemd/system/NetworkManager.service
│   │   │   │   ├── remote-fs.target -> /lib/systemd/system/remote-fs.target
│   │   │   │   ├── rsyslog.service -> /lib/systemd/system/rsyslog.service
│   │   │   │   ├── snap-bare-5.mount -> /etc/systemd/system/snap-bare-5.mount
│   │   │   │   ├── snap-chromium-3205.mount -> /etc/systemd/system/snap-chromium-3205.mount
│   │   │   │   ├── snap-core22-2049.mount -> /etc/systemd/system/snap-core22-2049.mount
│   │   │   │   ├── snap-cups-1102.mount -> /etc/systemd/system/snap-cups-1102.mount
│   │   │   │   ├── snap.cups.cups-browsed.service -> /etc/systemd/system/snap.cups.cups-browsed.service
│   │   │   │   ├── snap.cups.cupsd.service -> /etc/systemd/system/snap.cups.cupsd.service
│   │   │   │   ├── snapd.aa-prompt-listener.service -> /lib/systemd/system/snapd.aa-prompt-listener.service
│   │   │   │   ├── snapd.apparmor.service -> /lib/systemd/system/snapd.apparmor.service
│   │   │   │   ├── snapd.recovery-chooser-trigger.service -> /lib/systemd/system/snapd.recovery-chooser-trigger.service
│   │   │   │   ├── snapd.seeded.service -> /lib/systemd/system/snapd.seeded.service
│   │   │   │   ├── snapd.service -> /lib/systemd/system/snapd.service
│   │   │   │   ├── snap-firefox-6492.mount -> /etc/systemd/system/snap-firefox-6492.mount
│   │   │   │   ├── snap-firefox-6563.mount -> /etc/systemd/system/snap-firefox-6563.mount
│   │   │   │   ├── snap-gnome\x2d42\x2d2204-201.mount -> /etc/systemd/system/snap-gnome\x2d42\x2d2204-201.mount
│   │   │   │   ├── snap-gtk\x2dcommon\x2dthemes-1535.mount -> /etc/systemd/system/snap-gtk\x2dcommon\x2dthemes-1535.mount
│   │   │   │   ├── snap-snapd-24787.mount -> /etc/systemd/system/snap-snapd-24787.mount
│   │   │   │   ├── ssh.service -> /lib/systemd/system/ssh.service
│   │   │   │   └── wpa_supplicant.service -> /lib/systemd/system/wpa_supplicant.service
│   │   │   ├── network-online.target.wants
│   │   │   │   └── NetworkManager-wait-online.service -> /lib/systemd/system/NetworkManager-wait-online.service
│   │   │   ├── serial-getty@.service.d
│   │   │   ├── snap-bare-5.mount
│   │   │   ├── snap-chromium-3205.mount
│   │   │   ├── snap.chromium.daemon.service
│   │   │   ├── snap-core22-2049.mount
│   │   │   ├── snap-cups-1102.mount
│   │   │   ├── snap.cups.cups-browsed.service
│   │   │   ├── snap.cups.cupsd.service
│   │   │   ├── snapd.mounts.target.wants
│   │   │   │   ├── snap-bare-5.mount -> /etc/systemd/system/snap-bare-5.mount
│   │   │   │   ├── snap-chromium-3205.mount -> /etc/systemd/system/snap-chromium-3205.mount
│   │   │   │   ├── snap-core22-2049.mount -> /etc/systemd/system/snap-core22-2049.mount
│   │   │   │   ├── snap-cups-1102.mount -> /etc/systemd/system/snap-cups-1102.mount
│   │   │   │   ├── snap-firefox-6492.mount -> /etc/systemd/system/snap-firefox-6492.mount
│   │   │   │   ├── snap-firefox-6563.mount -> /etc/systemd/system/snap-firefox-6563.mount
│   │   │   │   ├── snap-gnome\x2d42\x2d2204-201.mount -> /etc/systemd/system/snap-gnome\x2d42\x2d2204-201.mount
│   │   │   │   ├── snap-gtk\x2dcommon\x2dthemes-1535.mount -> /etc/systemd/system/snap-gtk\x2dcommon\x2dthemes-1535.mount
│   │   │   │   └── snap-snapd-24787.mount -> /etc/systemd/system/snap-snapd-24787.mount
│   │   │   ├── snap-firefox-6492.mount
│   │   │   ├── snap-firefox-6563.mount
│   │   │   ├── snap-gnome\x2d42\x2d2204-201.mount
│   │   │   ├── snap-gtk\x2dcommon\x2dthemes-1535.mount
│   │   │   ├── snap-snapd-24787.mount
│   │   │   ├── sockets.target.wants
│   │   │   │   ├── avahi-daemon.socket -> /lib/systemd/system/avahi-daemon.socket
│   │   │   │   ├── docker.socket -> /lib/systemd/system/docker.socket
│   │   │   │   └── snapd.socket -> /lib/systemd/system/snapd.socket
│   │   │   ├── sshd.service -> /lib/systemd/system/ssh.service
│   │   │   ├── sysinit.target.wants
│   │   │   │   ├── apparmor.service -> /lib/systemd/system/apparmor.service
│   │   │   │   ├── armbian-ramlog.service -> /lib/systemd/system/armbian-ramlog.service
│   │   │   │   ├── armbian-zram-config.service -> /lib/systemd/system/armbian-zram-config.service
│   │   │   │   ├── fake-hwclock.service -> /lib/systemd/system/fake-hwclock.service
│   │   │   │   ├── keyboard-setup.service -> /lib/systemd/system/keyboard-setup.service
│   │   │   │   ├── systemd-pstore.service -> /lib/systemd/system/systemd-pstore.service
│   │   │   │   ├── systemd-resolved.service -> /lib/systemd/system/systemd-resolved.service
│   │   │   │   └── systemd-timesyncd.service -> /lib/systemd/system/systemd-timesyncd.service
│   │   │   ├── syslog.service -> /lib/systemd/system/rsyslog.service
│   │   │   ├── systemd-firstboot.service -> /dev/null
│   │   │   └── timers.target.wants
│   │   │       ├── apt-daily.timer -> /lib/systemd/system/apt-daily.timer
│   │   │       ├── apt-daily-upgrade.timer -> /lib/systemd/system/apt-daily-upgrade.timer
│   │   │       ├── dpkg-db-backup.timer -> /lib/systemd/system/dpkg-db-backup.timer
│   │   │       ├── e2scrub_all.timer -> /lib/systemd/system/e2scrub_all.timer
│   │   │       ├── fstrim.timer -> /lib/systemd/system/fstrim.timer
│   │   │       ├── logrotate.timer -> /lib/systemd/system/logrotate.timer
│   │   │       └── man-db.timer -> /lib/systemd/system/man-db.timer
│   │   ├── system.conf
│   │   ├── timesyncd.conf
│   │   ├── user
│   │   │   ├── dbus-org.bluez.obex.service -> /usr/lib/systemd/user/obex.service
│   │   │   ├── default.target.wants
│   │   │   │   ├── pipewire-pulse.service -> /usr/lib/systemd/user/pipewire-pulse.service
│   │   │   │   ├── pipewire.service -> /usr/lib/systemd/user/pipewire.service
│   │   │   │   └── tracker-extract-3.service -> /usr/lib/systemd/user/tracker-extract-3.service
│   │   │   ├── gnome-session.target.wants
│   │   │   │   ├── org.freedesktop.IBus.session.GNOME.service -> /usr/lib/systemd/user/org.freedesktop.IBus.session.GNOME.service
│   │   │   │   └── tracker-miner-fs-3.service -> /usr/lib/systemd/user/tracker-miner-fs-3.service
│   │   │   ├── graphical-session-pre.target.wants
│   │   │   │   ├── gcr-ssh-agent.service -> /usr/lib/systemd/user/gcr-ssh-agent.service
│   │   │   │   ├── gnome-keyring-daemon.service -> /usr/lib/systemd/user/gnome-keyring-daemon.service
│   │   │   │   └── xdg-desktop-portal-rewrite-launchers.service -> /usr/lib/systemd/user/xdg-desktop-portal-rewrite-launchers.service
│   │   │   ├── pipewire.service.wants
│   │   │   │   └── wireplumber.service -> /usr/lib/systemd/user/wireplumber.service
│   │   │   └── sockets.target.wants
│   │   │       ├── dirmngr.socket -> /lib/systemd/user/dirmngr.socket
│   │   │       ├── gcr-ssh-agent.socket -> /usr/lib/systemd/user/gcr-ssh-agent.socket
│   │   │       ├── gnome-keyring-daemon.socket -> /usr/lib/systemd/user/gnome-keyring-daemon.socket
│   │   │       ├── gpg-agent-browser.socket -> /lib/systemd/user/gpg-agent-browser.socket
│   │   │       ├── gpg-agent-extra.socket -> /lib/systemd/user/gpg-agent-extra.socket
│   │   │       ├── gpg-agent.socket -> /lib/systemd/user/gpg-agent.socket
│   │   │       ├── gpg-agent-ssh.socket -> /lib/systemd/user/gpg-agent-ssh.socket
│   │   │       ├── pipewire-pulse.socket -> /usr/lib/systemd/user/pipewire-pulse.socket
│   │   │       ├── pipewire.socket -> /usr/lib/systemd/user/pipewire.socket
│   │   │       └── pk-debconf-helper.socket -> /usr/lib/systemd/user/pk-debconf-helper.socket
│   │   └── user.conf
│   ├── terminfo
│   │   └── README
│   ├── texmf
│   │   ├── texmf.d
│   │   │   └── 00debian.cnf
│   │   └── web2c
│   │       ├── mktex.cnf
│   │       └── texmf.cnf
│   ├── timezone
│   ├── timidity
│   │   └── timgm6mb.cfg
│   ├── tmpfiles.d
│   ├── ucf.conf
│   ├── udev
│   │   ├── hwdb.d
│   │   ├── rules.d
│   │   │   ├── 10-wifi-disable-powermanagement.rules
│   │   │   ├── 50-usb-realtek-net.rules
│   │   │   ├── 70-snap.chromium.rules
│   │   │   ├── 70-snap.cups.rules
│   │   │   ├── 70-snap.firefox.rules
│   │   │   ├── 70-snap.snapd.rules
│   │   │   ├── 90-chromium-video.rules
│   │   │   └── 90-naming-audios.rules
│   │   └── udev.conf
│   ├── udisks2
│   │   ├── mount_options.conf.example
│   │   └── udisks2.conf
│   ├── ufw
│   │   └── applications.d
│   │       └── openssh-server
│   ├── update-motd.d
│   │   ├── 00-clear
│   │   ├── 10-armbian-header
│   │   ├── 30-armbian-sysinfo
│   │   ├── 35-armbian-tips
│   │   ├── 41-commands
│   │   └── 98-armbian-autoreboot-warn
│   ├── UPower
│   │   └── UPower.conf
│   ├── vdpau_wrapper.cfg
│   ├── vulkan
│   │   ├── explicit_layer.d
│   │   ├── icd.d
│   │   └── implicit_layer.d
│   ├── wgetrc
│   ├── wireguard  [error opening dir]
│   ├── wpa_supplicant
│   │   ├── action_wpa.sh
│   │   ├── functions.sh
│   │   └── ifupdown.sh
│   ├── X11
│   │   ├── app-defaults
│   │   │   ├── Editres
│   │   │   ├── Editres-color
│   │   │   ├── Viewres
│   │   │   ├── Viewres-color
│   │   │   ├── Xfd
│   │   │   ├── XFontSel
│   │   │   ├── Xmessage
│   │   │   ├── Xmessage-color
│   │   │   └── Xvidtune
│   │   ├── default-display-manager
│   │   ├── fonts
│   │   │   └── Type1
│   │   │       ├── fonts-urw-base35.alias
│   │   │       └── fonts-urw-base35.scale
│   │   ├── rgb.txt
│   │   ├── xkb
│   │   ├── xorg.conf.d
│   │   │   └── 01-armbian-defaults.conf
│   │   ├── Xreset
│   │   ├── Xreset.d
│   │   │   └── README
│   │   ├── Xresources
│   │   │   └── x11-common
│   │   ├── Xsession
│   │   ├── Xsession.d
│   │   │   ├── 20dbus_xdg-runtime
│   │   │   ├── 20flatpak
│   │   │   ├── 20x11-common_process-args
│   │   │   ├── 30x11-common_xresources
│   │   │   ├── 35x11-common_xhost-local
│   │   │   ├── 40x11-common_xsessionrc
│   │   │   ├── 50x11-common_determine-startup
│   │   │   ├── 55gnome-session_gnomerc
│   │   │   ├── 90atk-adaptor
│   │   │   ├── 90gpg-agent
│   │   │   ├── 90qt-a11y
│   │   │   ├── 90x11-common_ssh-agent
│   │   │   └── 99x11-common_start
│   │   └── Xsession.options
│   ├── xattr.conf
│   ├── xdg
│   │   ├── autostart
│   │   │   ├── at-spi-dbus-bus.desktop
│   │   │   ├── geoclue-demo-agent.desktop
│   │   │   ├── gnome-keyring-pkcs11.desktop
│   │   │   ├── gnome-keyring-secrets.desktop
│   │   │   ├── gnome-keyring-ssh.desktop
│   │   │   ├── gnome-shell-overrides-migration.desktop
│   │   │   ├── nm-applet.desktop
│   │   │   ├── orca-autostart.desktop
│   │   │   ├── org.gnome.Evolution-alarm-notify.desktop
│   │   │   ├── org.gnome.SettingsDaemon.A11ySettings.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Color.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Datetime.desktop
│   │   │   ├── org.gnome.SettingsDaemon.DiskUtilityNotify.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Housekeeping.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Keyboard.desktop
│   │   │   ├── org.gnome.SettingsDaemon.MediaKeys.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Power.desktop
│   │   │   ├── org.gnome.SettingsDaemon.PrintNotifications.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Rfkill.desktop
│   │   │   ├── org.gnome.SettingsDaemon.ScreensaverProxy.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Sharing.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Smartcard.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Sound.desktop
│   │   │   ├── org.gnome.SettingsDaemon.UsbProtection.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Wacom.desktop
│   │   │   ├── org.gnome.SettingsDaemon.Wwan.desktop
│   │   │   ├── org.gnome.SettingsDaemon.XSettings.desktop
│   │   │   ├── org.gnome.Software.desktop
│   │   │   ├── snap-userd-autostart.desktop
│   │   │   ├── tracker-miner-fs-3.desktop
│   │   │   ├── user-dirs-update-gtk.desktop
│   │   │   ├── xdg-user-dirs.desktop
│   │   │   └── xdg-user-dirs-kde.desktop
│   │   ├── kcm-about-distrorc
│   │   ├── kickoffrc
│   │   ├── menus
│   │   │   └── gnome-applications.menu
│   │   ├── plasma-workspace
│   │   │   └── env
│   │   │       └── env.sh
│   │   ├── systemd
│   │   │   └── user -> ../../systemd/user
│   │   ├── user-dirs.conf
│   │   ├── user-dirs.defaults
│   │   └── Xwayland-session.d
│   │       ├── 00-at-spi
│   │       ├── 00-xrdb
│   │       └── 10-ibus-x11
│   └── xml
│       ├── catalog
│       ├── catalog.old
│       ├── polkitd.xml
│       ├── polkitd.xml.old
│       ├── xml-core.xml
│       └── xml-core.xml.old
├── home
│   └── x
│       ├── Desktop
│       ├── Documents
│       │   ├── Check if any of these.txt
│       │   ├── Cline
│       │   │   ├── MCP
│       │   │   │   ├── filesystem-server
│       │   │   │   │   ├── node_modules
│       │   │   │   │   │   ├── accepts
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── ajv
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── ajv.bundle.js
│       │   │   │   │   │   │   │   ├── ajv.min.js
│       │   │   │   │   │   │   │   └── ajv.min.js.map
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── ajv.d.ts
│       │   │   │   │   │   │   │   ├── ajv.js
│       │   │   │   │   │   │   │   ├── cache.js
│       │   │   │   │   │   │   │   ├── compile
│       │   │   │   │   │   │   │   │   ├── async.js
│       │   │   │   │   │   │   │   │   ├── equal.js
│       │   │   │   │   │   │   │   │   ├── error_classes.js
│       │   │   │   │   │   │   │   │   ├── formats.js
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── resolve.js
│       │   │   │   │   │   │   │   │   ├── rules.js
│       │   │   │   │   │   │   │   │   ├── schema_obj.js
│       │   │   │   │   │   │   │   │   ├── ucs2length.js
│       │   │   │   │   │   │   │   │   └── util.js
│       │   │   │   │   │   │   │   ├── data.js
│       │   │   │   │   │   │   │   ├── definition_schema.js
│       │   │   │   │   │   │   │   ├── dot
│       │   │   │   │   │   │   │   │   ├── allOf.jst
│       │   │   │   │   │   │   │   │   ├── anyOf.jst
│       │   │   │   │   │   │   │   │   ├── coerce.def
│       │   │   │   │   │   │   │   │   ├── comment.jst
│       │   │   │   │   │   │   │   │   ├── const.jst
│       │   │   │   │   │   │   │   │   ├── contains.jst
│       │   │   │   │   │   │   │   │   ├── custom.jst
│       │   │   │   │   │   │   │   │   ├── defaults.def
│       │   │   │   │   │   │   │   │   ├── definitions.def
│       │   │   │   │   │   │   │   │   ├── dependencies.jst
│       │   │   │   │   │   │   │   │   ├── enum.jst
│       │   │   │   │   │   │   │   │   ├── errors.def
│       │   │   │   │   │   │   │   │   ├── format.jst
│       │   │   │   │   │   │   │   │   ├── if.jst
│       │   │   │   │   │   │   │   │   ├── items.jst
│       │   │   │   │   │   │   │   │   ├── _limitItems.jst
│       │   │   │   │   │   │   │   │   ├── _limit.jst
│       │   │   │   │   │   │   │   │   ├── _limitLength.jst
│       │   │   │   │   │   │   │   │   ├── _limitProperties.jst
│       │   │   │   │   │   │   │   │   ├── missing.def
│       │   │   │   │   │   │   │   │   ├── multipleOf.jst
│       │   │   │   │   │   │   │   │   ├── not.jst
│       │   │   │   │   │   │   │   │   ├── oneOf.jst
│       │   │   │   │   │   │   │   │   ├── pattern.jst
│       │   │   │   │   │   │   │   │   ├── properties.jst
│       │   │   │   │   │   │   │   │   ├── propertyNames.jst
│       │   │   │   │   │   │   │   │   ├── ref.jst
│       │   │   │   │   │   │   │   │   ├── required.jst
│       │   │   │   │   │   │   │   │   ├── uniqueItems.jst
│       │   │   │   │   │   │   │   │   └── validate.jst
│       │   │   │   │   │   │   │   ├── dotjs
│       │   │   │   │   │   │   │   │   ├── allOf.js
│       │   │   │   │   │   │   │   │   ├── anyOf.js
│       │   │   │   │   │   │   │   │   ├── comment.js
│       │   │   │   │   │   │   │   │   ├── const.js
│       │   │   │   │   │   │   │   │   ├── contains.js
│       │   │   │   │   │   │   │   │   ├── custom.js
│       │   │   │   │   │   │   │   │   ├── dependencies.js
│       │   │   │   │   │   │   │   │   ├── enum.js
│       │   │   │   │   │   │   │   │   ├── format.js
│       │   │   │   │   │   │   │   │   ├── if.js
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── items.js
│       │   │   │   │   │   │   │   │   ├── _limitItems.js
│       │   │   │   │   │   │   │   │   ├── _limit.js
│       │   │   │   │   │   │   │   │   ├── _limitLength.js
│       │   │   │   │   │   │   │   │   ├── _limitProperties.js
│       │   │   │   │   │   │   │   │   ├── multipleOf.js
│       │   │   │   │   │   │   │   │   ├── not.js
│       │   │   │   │   │   │   │   │   ├── oneOf.js
│       │   │   │   │   │   │   │   │   ├── pattern.js
│       │   │   │   │   │   │   │   │   ├── properties.js
│       │   │   │   │   │   │   │   │   ├── propertyNames.js
│       │   │   │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   │   │   ├── ref.js
│       │   │   │   │   │   │   │   │   ├── required.js
│       │   │   │   │   │   │   │   │   ├── uniqueItems.js
│       │   │   │   │   │   │   │   │   └── validate.js
│       │   │   │   │   │   │   │   ├── keyword.js
│       │   │   │   │   │   │   │   └── refs
│       │   │   │   │   │   │   │       ├── data.json
│       │   │   │   │   │   │   │       ├── json-schema-draft-04.json
│       │   │   │   │   │   │   │       ├── json-schema-draft-06.json
│       │   │   │   │   │   │   │       ├── json-schema-draft-07.json
│       │   │   │   │   │   │   │       └── json-schema-secure.json
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── scripts
│       │   │   │   │   │   │       ├── bundle.js
│       │   │   │   │   │   │       ├── compile-dots.js
│       │   │   │   │   │   │       ├── info
│       │   │   │   │   │   │       ├── prepare-tests
│       │   │   │   │   │   │       ├── publish-built-version
│       │   │   │   │   │   │       └── travis-gh-pages
│       │   │   │   │   │   ├── ansi-regex
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── ansi-styles
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── balanced-match
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── body-parser
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── read.js
│       │   │   │   │   │   │   │   ├── types
│       │   │   │   │   │   │   │   │   ├── json.js
│       │   │   │   │   │   │   │   │   ├── raw.js
│       │   │   │   │   │   │   │   │   ├── text.js
│       │   │   │   │   │   │   │   │   └── urlencoded.js
│       │   │   │   │   │   │   │   └── utils.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── brace-expansion
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── bytes
│       │   │   │   │   │   │   ├── History.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── Readme.md
│       │   │   │   │   │   ├── call-bind-apply-helpers
│       │   │   │   │   │   │   ├── actualApply.d.ts
│       │   │   │   │   │   │   ├── actualApply.js
│       │   │   │   │   │   │   ├── applyBind.d.ts
│       │   │   │   │   │   │   ├── applyBind.js
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── functionApply.d.ts
│       │   │   │   │   │   │   ├── functionApply.js
│       │   │   │   │   │   │   ├── functionCall.d.ts
│       │   │   │   │   │   │   ├── functionCall.js
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── reflectApply.d.ts
│       │   │   │   │   │   │   ├── reflectApply.js
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── call-bound
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── color-convert
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── conversions.js
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── route.js
│       │   │   │   │   │   ├── color-name
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── content-disposition
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── content-type
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── cookie
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── SECURITY.md
│       │   │   │   │   │   ├── cookie-signature
│       │   │   │   │   │   │   ├── History.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── Readme.md
│       │   │   │   │   │   ├── cors
│       │   │   │   │   │   │   ├── CONTRIBUTING.md
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── cross-spawn
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── enoent.js
│       │   │   │   │   │   │   │   ├── parse.js
│       │   │   │   │   │   │   │   └── util
│       │   │   │   │   │   │   │       ├── escape.js
│       │   │   │   │   │   │   │       ├── readShebang.js
│       │   │   │   │   │   │   │       └── resolveCommand.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── debug
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── src
│       │   │   │   │   │   │       ├── browser.js
│       │   │   │   │   │   │       ├── common.js
│       │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │       └── node.js
│       │   │   │   │   │   ├── depd
│       │   │   │   │   │   │   ├── History.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   └── browser
│       │   │   │   │   │   │   │       └── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── Readme.md
│       │   │   │   │   │   ├── diff
│       │   │   │   │   │   │   ├── CONTRIBUTING.md
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── diff.js
│       │   │   │   │   │   │   │   └── diff.min.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── convert
│       │   │   │   │   │   │   │   │   ├── dmp.js
│       │   │   │   │   │   │   │   │   └── xml.js
│       │   │   │   │   │   │   │   ├── diff
│       │   │   │   │   │   │   │   │   ├── array.js
│       │   │   │   │   │   │   │   │   ├── base.js
│       │   │   │   │   │   │   │   │   ├── character.js
│       │   │   │   │   │   │   │   │   ├── css.js
│       │   │   │   │   │   │   │   │   ├── json.js
│       │   │   │   │   │   │   │   │   ├── line.js
│       │   │   │   │   │   │   │   │   ├── sentence.js
│       │   │   │   │   │   │   │   │   └── word.js
│       │   │   │   │   │   │   │   ├── index.es6.js
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   ├── index.mjs
│       │   │   │   │   │   │   │   ├── patch
│       │   │   │   │   │   │   │   │   ├── apply.js
│       │   │   │   │   │   │   │   │   ├── create.js
│       │   │   │   │   │   │   │   │   ├── merge.js
│       │   │   │   │   │   │   │   │   ├── parse.js
│       │   │   │   │   │   │   │   │   └── reverse.js
│       │   │   │   │   │   │   │   └── util
│       │   │   │   │   │   │   │       ├── array.js
│       │   │   │   │   │   │   │       ├── distance-iterator.js
│       │   │   │   │   │   │   │       └── params.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── release-notes.md
│       │   │   │   │   │   │   └── runtime.js
│       │   │   │   │   │   ├── dunder-proto
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── get.d.ts
│       │   │   │   │   │   │   ├── get.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── set.d.ts
│       │   │   │   │   │   │   ├── set.js
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   ├── get.js
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   └── set.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── eastasianwidth
│       │   │   │   │   │   │   ├── eastasianwidth.js
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── ee-first
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── emoji-regex
│       │   │   │   │   │   │   ├── es2015
│       │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   ├── RGI_Emoji.d.ts
│       │   │   │   │   │   │   │   ├── RGI_Emoji.js
│       │   │   │   │   │   │   │   ├── text.d.ts
│       │   │   │   │   │   │   │   └── text.js
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE-MIT.txt
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── RGI_Emoji.d.ts
│       │   │   │   │   │   │   ├── RGI_Emoji.js
│       │   │   │   │   │   │   ├── text.d.ts
│       │   │   │   │   │   │   └── text.js
│       │   │   │   │   │   ├── encodeurl
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── escape-html
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── Readme.md
│       │   │   │   │   │   ├── es-define-property
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── es-errors
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── eval.d.ts
│       │   │   │   │   │   │   ├── eval.js
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── range.d.ts
│       │   │   │   │   │   │   ├── range.js
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── ref.d.ts
│       │   │   │   │   │   │   ├── ref.js
│       │   │   │   │   │   │   ├── syntax.d.ts
│       │   │   │   │   │   │   ├── syntax.js
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   ├── tsconfig.json
│       │   │   │   │   │   │   ├── type.d.ts
│       │   │   │   │   │   │   ├── type.js
│       │   │   │   │   │   │   ├── uri.d.ts
│       │   │   │   │   │   │   └── uri.js
│       │   │   │   │   │   ├── es-object-atoms
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── isObject.d.ts
│       │   │   │   │   │   │   ├── isObject.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── RequireObjectCoercible.d.ts
│       │   │   │   │   │   │   ├── RequireObjectCoercible.js
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   ├── ToObject.d.ts
│       │   │   │   │   │   │   ├── ToObject.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── etag
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── eventsource
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── index.cjs
│       │   │   │   │   │   │   │   ├── index.cjs.map
│       │   │   │   │   │   │   │   ├── index.d.cts
│       │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   └── index.js.map
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── src
│       │   │   │   │   │   │       ├── errors.ts
│       │   │   │   │   │   │       ├── EventSource.ts
│       │   │   │   │   │   │       ├── index.ts
│       │   │   │   │   │   │       └── types.ts
│       │   │   │   │   │   ├── eventsource-parser
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── index.cjs
│       │   │   │   │   │   │   │   ├── index.cjs.map
│       │   │   │   │   │   │   │   ├── index.d.cts
│       │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   ├── stream.cjs
│       │   │   │   │   │   │   │   ├── stream.cjs.map
│       │   │   │   │   │   │   │   ├── stream.d.cts
│       │   │   │   │   │   │   │   ├── stream.d.ts
│       │   │   │   │   │   │   │   ├── stream.js
│       │   │   │   │   │   │   │   └── stream.js.map
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── src
│       │   │   │   │   │   │   │   ├── errors.ts
│       │   │   │   │   │   │   │   ├── index.ts
│       │   │   │   │   │   │   │   ├── parse.ts
│       │   │   │   │   │   │   │   ├── stream.ts
│       │   │   │   │   │   │   │   └── types.ts
│       │   │   │   │   │   │   └── stream.js
│       │   │   │   │   │   ├── express
│       │   │   │   │   │   │   ├── History.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── application.js
│       │   │   │   │   │   │   │   ├── express.js
│       │   │   │   │   │   │   │   ├── request.js
│       │   │   │   │   │   │   │   ├── response.js
│       │   │   │   │   │   │   │   ├── utils.js
│       │   │   │   │   │   │   │   └── view.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── Readme.md
│       │   │   │   │   │   ├── express-rate-limit
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── index.cjs
│       │   │   │   │   │   │   │   ├── index.d.cts
│       │   │   │   │   │   │   │   ├── index.d.mts
│       │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   └── index.mjs
│       │   │   │   │   │   │   ├── license.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── readme.md
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── fast-deep-equal
│       │   │   │   │   │   │   ├── es6
│       │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   ├── react.d.ts
│       │   │   │   │   │   │   │   └── react.js
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── react.d.ts
│       │   │   │   │   │   │   ├── react.js
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── fast-json-stable-stringify
│       │   │   │   │   │   │   ├── benchmark
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   └── test.json
│       │   │   │   │   │   │   ├── example
│       │   │   │   │   │   │   │   ├── key_cmp.js
│       │   │   │   │   │   │   │   ├── nested.js
│       │   │   │   │   │   │   │   ├── str.js
│       │   │   │   │   │   │   │   └── value_cmp.js
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── test
│       │   │   │   │   │   │       ├── cmp.js
│       │   │   │   │   │   │       ├── nested.js
│       │   │   │   │   │   │       ├── str.js
│       │   │   │   │   │   │       └── to-json.js
│       │   │   │   │   │   ├── finalhandler
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── foreground-child
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   ├── all-signals.d.ts
│       │   │   │   │   │   │   │   │   ├── all-signals.d.ts.map
│       │   │   │   │   │   │   │   │   ├── all-signals.js
│       │   │   │   │   │   │   │   │   ├── all-signals.js.map
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   ├── proxy-signals.d.ts
│       │   │   │   │   │   │   │   │   ├── proxy-signals.d.ts.map
│       │   │   │   │   │   │   │   │   ├── proxy-signals.js
│       │   │   │   │   │   │   │   │   ├── proxy-signals.js.map
│       │   │   │   │   │   │   │   │   ├── watchdog.d.ts
│       │   │   │   │   │   │   │   │   ├── watchdog.d.ts.map
│       │   │   │   │   │   │   │   │   ├── watchdog.js
│       │   │   │   │   │   │   │   │   └── watchdog.js.map
│       │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │       ├── all-signals.d.ts
│       │   │   │   │   │   │   │       ├── all-signals.d.ts.map
│       │   │   │   │   │   │   │       ├── all-signals.js
│       │   │   │   │   │   │   │       ├── all-signals.js.map
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       ├── proxy-signals.d.ts
│       │   │   │   │   │   │   │       ├── proxy-signals.d.ts.map
│       │   │   │   │   │   │   │       ├── proxy-signals.js
│       │   │   │   │   │   │   │       ├── proxy-signals.js.map
│       │   │   │   │   │   │   │       ├── watchdog.d.ts
│       │   │   │   │   │   │   │       ├── watchdog.d.ts.map
│       │   │   │   │   │   │   │       ├── watchdog.js
│       │   │   │   │   │   │   │       └── watchdog.js.map
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── forwarded
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── fresh
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── function-bind
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── implementation.js
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── test
│       │   │   │   │   │   │       └── index.js
│       │   │   │   │   │   ├── get-intrinsic
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── test
│       │   │   │   │   │   │       └── GetIntrinsic.js
│       │   │   │   │   │   ├── get-proto
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── Object.getPrototypeOf.d.ts
│       │   │   │   │   │   │   ├── Object.getPrototypeOf.js
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── Reflect.getPrototypeOf.d.ts
│       │   │   │   │   │   │   ├── Reflect.getPrototypeOf.js
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── glob
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   ├── glob.d.ts
│       │   │   │   │   │   │   │   │   ├── glob.d.ts.map
│       │   │   │   │   │   │   │   │   ├── glob.js
│       │   │   │   │   │   │   │   │   ├── glob.js.map
│       │   │   │   │   │   │   │   │   ├── has-magic.d.ts
│       │   │   │   │   │   │   │   │   ├── has-magic.d.ts.map
│       │   │   │   │   │   │   │   │   ├── has-magic.js
│       │   │   │   │   │   │   │   │   ├── has-magic.js.map
│       │   │   │   │   │   │   │   │   ├── ignore.d.ts
│       │   │   │   │   │   │   │   │   ├── ignore.d.ts.map
│       │   │   │   │   │   │   │   │   ├── ignore.js
│       │   │   │   │   │   │   │   │   ├── ignore.js.map
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   ├── pattern.d.ts
│       │   │   │   │   │   │   │   │   ├── pattern.d.ts.map
│       │   │   │   │   │   │   │   │   ├── pattern.js
│       │   │   │   │   │   │   │   │   ├── pattern.js.map
│       │   │   │   │   │   │   │   │   ├── processor.d.ts
│       │   │   │   │   │   │   │   │   ├── processor.d.ts.map
│       │   │   │   │   │   │   │   │   ├── processor.js
│       │   │   │   │   │   │   │   │   ├── processor.js.map
│       │   │   │   │   │   │   │   │   ├── walker.d.ts
│       │   │   │   │   │   │   │   │   ├── walker.d.ts.map
│       │   │   │   │   │   │   │   │   ├── walker.js
│       │   │   │   │   │   │   │   │   └── walker.js.map
│       │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │       ├── bin.d.mts
│       │   │   │   │   │   │   │       ├── bin.d.mts.map
│       │   │   │   │   │   │   │       ├── bin.mjs
│       │   │   │   │   │   │   │       ├── bin.mjs.map
│       │   │   │   │   │   │   │       ├── glob.d.ts
│       │   │   │   │   │   │   │       ├── glob.d.ts.map
│       │   │   │   │   │   │   │       ├── glob.js
│       │   │   │   │   │   │   │       ├── glob.js.map
│       │   │   │   │   │   │   │       ├── has-magic.d.ts
│       │   │   │   │   │   │   │       ├── has-magic.d.ts.map
│       │   │   │   │   │   │   │       ├── has-magic.js
│       │   │   │   │   │   │   │       ├── has-magic.js.map
│       │   │   │   │   │   │   │       ├── ignore.d.ts
│       │   │   │   │   │   │   │       ├── ignore.d.ts.map
│       │   │   │   │   │   │   │       ├── ignore.js
│       │   │   │   │   │   │   │       ├── ignore.js.map
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       ├── pattern.d.ts
│       │   │   │   │   │   │   │       ├── pattern.d.ts.map
│       │   │   │   │   │   │   │       ├── pattern.js
│       │   │   │   │   │   │   │       ├── pattern.js.map
│       │   │   │   │   │   │   │       ├── processor.d.ts
│       │   │   │   │   │   │   │       ├── processor.d.ts.map
│       │   │   │   │   │   │   │       ├── processor.js
│       │   │   │   │   │   │   │       ├── processor.js.map
│       │   │   │   │   │   │   │       ├── walker.d.ts
│       │   │   │   │   │   │   │       ├── walker.d.ts.map
│       │   │   │   │   │   │   │       ├── walker.js
│       │   │   │   │   │   │   │       └── walker.js.map
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── node_modules
│       │   │   │   │   │   │   │   └── minimatch
│       │   │   │   │   │   │   │       ├── dist
│       │   │   │   │   │   │   │       │   ├── commonjs
│       │   │   │   │   │   │   │       │   │   ├── assert-valid-pattern.d.ts
│       │   │   │   │   │   │   │       │   │   ├── assert-valid-pattern.d.ts.map
│       │   │   │   │   │   │   │       │   │   ├── assert-valid-pattern.js
│       │   │   │   │   │   │   │       │   │   ├── assert-valid-pattern.js.map
│       │   │   │   │   │   │   │       │   │   ├── ast.d.ts
│       │   │   │   │   │   │   │       │   │   ├── ast.d.ts.map
│       │   │   │   │   │   │   │       │   │   ├── ast.js
│       │   │   │   │   │   │   │       │   │   ├── ast.js.map
│       │   │   │   │   │   │   │       │   │   ├── brace-expressions.d.ts
│       │   │   │   │   │   │   │       │   │   ├── brace-expressions.d.ts.map
│       │   │   │   │   │   │   │       │   │   ├── brace-expressions.js
│       │   │   │   │   │   │   │       │   │   ├── brace-expressions.js.map
│       │   │   │   │   │   │   │       │   │   ├── escape.d.ts
│       │   │   │   │   │   │   │       │   │   ├── escape.d.ts.map
│       │   │   │   │   │   │   │       │   │   ├── escape.js
│       │   │   │   │   │   │   │       │   │   ├── escape.js.map
│       │   │   │   │   │   │   │       │   │   ├── index.d.ts
│       │   │   │   │   │   │   │       │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │       │   │   ├── index.js
│       │   │   │   │   │   │   │       │   │   ├── index.js.map
│       │   │   │   │   │   │   │       │   │   ├── package.json
│       │   │   │   │   │   │   │       │   │   ├── unescape.d.ts
│       │   │   │   │   │   │   │       │   │   ├── unescape.d.ts.map
│       │   │   │   │   │   │   │       │   │   ├── unescape.js
│       │   │   │   │   │   │   │       │   │   └── unescape.js.map
│       │   │   │   │   │   │   │       │   └── esm
│       │   │   │   │   │   │   │       │       ├── assert-valid-pattern.d.ts
│       │   │   │   │   │   │   │       │       ├── assert-valid-pattern.d.ts.map
│       │   │   │   │   │   │   │       │       ├── assert-valid-pattern.js
│       │   │   │   │   │   │   │       │       ├── assert-valid-pattern.js.map
│       │   │   │   │   │   │   │       │       ├── ast.d.ts
│       │   │   │   │   │   │   │       │       ├── ast.d.ts.map
│       │   │   │   │   │   │   │       │       ├── ast.js
│       │   │   │   │   │   │   │       │       ├── ast.js.map
│       │   │   │   │   │   │   │       │       ├── brace-expressions.d.ts
│       │   │   │   │   │   │   │       │       ├── brace-expressions.d.ts.map
│       │   │   │   │   │   │   │       │       ├── brace-expressions.js
│       │   │   │   │   │   │   │       │       ├── brace-expressions.js.map
│       │   │   │   │   │   │   │       │       ├── escape.d.ts
│       │   │   │   │   │   │   │       │       ├── escape.d.ts.map
│       │   │   │   │   │   │   │       │       ├── escape.js
│       │   │   │   │   │   │   │       │       ├── escape.js.map
│       │   │   │   │   │   │   │       │       ├── index.d.ts
│       │   │   │   │   │   │   │       │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       │       ├── index.js
│       │   │   │   │   │   │   │       │       ├── index.js.map
│       │   │   │   │   │   │   │       │       ├── package.json
│       │   │   │   │   │   │   │       │       ├── unescape.d.ts
│       │   │   │   │   │   │   │       │       ├── unescape.d.ts.map
│       │   │   │   │   │   │   │       │       ├── unescape.js
│       │   │   │   │   │   │   │       │       └── unescape.js.map
│       │   │   │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       └── README.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── gopd
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── gOPD.d.ts
│       │   │   │   │   │   │   ├── gOPD.js
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── hasown
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── has-symbols
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── shams.d.ts
│       │   │   │   │   │   │   ├── shams.js
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   ├── shams
│       │   │   │   │   │   │   │   │   ├── core-js.js
│       │   │   │   │   │   │   │   │   └── get-own-property-symbols.js
│       │   │   │   │   │   │   │   └── tests.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── http-errors
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── node_modules
│       │   │   │   │   │   │   │   └── statuses
│       │   │   │   │   │   │   │       ├── codes.json
│       │   │   │   │   │   │   │       ├── HISTORY.md
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       └── README.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── iconv-lite
│       │   │   │   │   │   │   ├── Changelog.md
│       │   │   │   │   │   │   ├── encodings
│       │   │   │   │   │   │   │   ├── dbcs-codec.js
│       │   │   │   │   │   │   │   ├── dbcs-data.js
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   ├── internal.js
│       │   │   │   │   │   │   │   ├── sbcs-codec.js
│       │   │   │   │   │   │   │   ├── sbcs-data-generated.js
│       │   │   │   │   │   │   │   ├── sbcs-data.js
│       │   │   │   │   │   │   │   ├── tables
│       │   │   │   │   │   │   │   │   ├── big5-added.json
│       │   │   │   │   │   │   │   │   ├── cp936.json
│       │   │   │   │   │   │   │   │   ├── cp949.json
│       │   │   │   │   │   │   │   │   ├── cp950.json
│       │   │   │   │   │   │   │   │   ├── eucjp.json
│       │   │   │   │   │   │   │   │   ├── gb18030-ranges.json
│       │   │   │   │   │   │   │   │   ├── gbk-added.json
│       │   │   │   │   │   │   │   │   └── shiftjis.json
│       │   │   │   │   │   │   │   ├── utf16.js
│       │   │   │   │   │   │   │   ├── utf32.js
│       │   │   │   │   │   │   │   └── utf7.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── bom-handling.js
│       │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   └── streams.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── inherits
│       │   │   │   │   │   │   ├── inherits_browser.js
│       │   │   │   │   │   │   ├── inherits.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── ipaddr.js
│       │   │   │   │   │   │   ├── ipaddr.min.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── ipaddr.js
│       │   │   │   │   │   │   │   └── ipaddr.js.d.ts
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── @isaacs
│       │   │   │   │   │   │   ├── balanced-match
│       │   │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   │   └── package.json
│       │   │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │   │       └── package.json
│       │   │   │   │   │   │   │   ├── LICENSE.md
│       │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   │   ├── brace-expansion
│       │   │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   │   └── package.json
│       │   │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │   │       └── package.json
│       │   │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   │   └── cliui
│       │   │   │   │   │   │       ├── build
│       │   │   │   │   │   │       │   ├── index.cjs
│       │   │   │   │   │   │       │   ├── index.d.cts
│       │   │   │   │   │   │       │   └── lib
│       │   │   │   │   │   │       │       └── index.js
│       │   │   │   │   │   │       ├── index.mjs
│       │   │   │   │   │   │       ├── LICENSE.txt
│       │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │       └── README.md
│       │   │   │   │   │   ├── isexe
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── mode.js
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── basic.js
│       │   │   │   │   │   │   └── windows.js
│       │   │   │   │   │   ├── is-fullwidth-code-point
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── is-promise
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── index.mjs
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── jackspeak
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   ├── parse-args-cjs.cjs.map
│       │   │   │   │   │   │   │   │   ├── parse-args-cjs.d.cts.map
│       │   │   │   │   │   │   │   │   ├── parse-args.d.ts
│       │   │   │   │   │   │   │   │   └── parse-args.js
│       │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       ├── parse-args.d.ts
│       │   │   │   │   │   │   │       ├── parse-args.d.ts.map
│       │   │   │   │   │   │   │       ├── parse-args.js
│       │   │   │   │   │   │   │       └── parse-args.js.map
│       │   │   │   │   │   │   ├── LICENSE.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── json-schema-traverse
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── spec
│       │   │   │   │   │   │       ├── fixtures
│       │   │   │   │   │   │       │   └── schema.js
│       │   │   │   │   │   │       └── index.spec.js
│       │   │   │   │   │   ├── lru-cache
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   ├── index.min.js
│       │   │   │   │   │   │   │   │   ├── index.min.js.map
│       │   │   │   │   │   │   │   │   └── package.json
│       │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       ├── index.min.js
│       │   │   │   │   │   │   │       ├── index.min.js.map
│       │   │   │   │   │   │   │       └── package.json
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── math-intrinsics
│       │   │   │   │   │   │   ├── abs.d.ts
│       │   │   │   │   │   │   ├── abs.js
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── constants
│       │   │   │   │   │   │   │   ├── maxArrayLength.d.ts
│       │   │   │   │   │   │   │   ├── maxArrayLength.js
│       │   │   │   │   │   │   │   ├── maxSafeInteger.d.ts
│       │   │   │   │   │   │   │   ├── maxSafeInteger.js
│       │   │   │   │   │   │   │   ├── maxValue.d.ts
│       │   │   │   │   │   │   │   └── maxValue.js
│       │   │   │   │   │   │   ├── floor.d.ts
│       │   │   │   │   │   │   ├── floor.js
│       │   │   │   │   │   │   ├── isFinite.d.ts
│       │   │   │   │   │   │   ├── isFinite.js
│       │   │   │   │   │   │   ├── isInteger.d.ts
│       │   │   │   │   │   │   ├── isInteger.js
│       │   │   │   │   │   │   ├── isNaN.d.ts
│       │   │   │   │   │   │   ├── isNaN.js
│       │   │   │   │   │   │   ├── isNegativeZero.d.ts
│       │   │   │   │   │   │   ├── isNegativeZero.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── max.d.ts
│       │   │   │   │   │   │   ├── max.js
│       │   │   │   │   │   │   ├── min.d.ts
│       │   │   │   │   │   │   ├── min.js
│       │   │   │   │   │   │   ├── mod.d.ts
│       │   │   │   │   │   │   ├── mod.js
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── pow.d.ts
│       │   │   │   │   │   │   ├── pow.js
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── round.d.ts
│       │   │   │   │   │   │   ├── round.js
│       │   │   │   │   │   │   ├── sign.d.ts
│       │   │   │   │   │   │   ├── sign.js
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── media-typer
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── merge-descriptors
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── mime-db
│       │   │   │   │   │   │   ├── db.json
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── mime-types
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── mimeScore.js
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── minimatch
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   ├── assert-valid-pattern.d.ts
│       │   │   │   │   │   │   │   │   ├── assert-valid-pattern.d.ts.map
│       │   │   │   │   │   │   │   │   ├── assert-valid-pattern.js
│       │   │   │   │   │   │   │   │   ├── assert-valid-pattern.js.map
│       │   │   │   │   │   │   │   │   ├── ast.d.ts
│       │   │   │   │   │   │   │   │   ├── ast.d.ts.map
│       │   │   │   │   │   │   │   │   ├── ast.js
│       │   │   │   │   │   │   │   │   ├── ast.js.map
│       │   │   │   │   │   │   │   │   ├── brace-expressions.d.ts
│       │   │   │   │   │   │   │   │   ├── brace-expressions.d.ts.map
│       │   │   │   │   │   │   │   │   ├── brace-expressions.js
│       │   │   │   │   │   │   │   │   ├── brace-expressions.js.map
│       │   │   │   │   │   │   │   │   ├── escape.d.ts
│       │   │   │   │   │   │   │   │   ├── escape.d.ts.map
│       │   │   │   │   │   │   │   │   ├── escape.js
│       │   │   │   │   │   │   │   │   ├── escape.js.map
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   ├── unescape.d.ts
│       │   │   │   │   │   │   │   │   ├── unescape.d.ts.map
│       │   │   │   │   │   │   │   │   ├── unescape.js
│       │   │   │   │   │   │   │   │   └── unescape.js.map
│       │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │       ├── assert-valid-pattern.d.ts
│       │   │   │   │   │   │   │       ├── assert-valid-pattern.d.ts.map
│       │   │   │   │   │   │   │       ├── assert-valid-pattern.js
│       │   │   │   │   │   │   │       ├── assert-valid-pattern.js.map
│       │   │   │   │   │   │   │       ├── ast.d.ts
│       │   │   │   │   │   │   │       ├── ast.d.ts.map
│       │   │   │   │   │   │   │       ├── ast.js
│       │   │   │   │   │   │   │       ├── ast.js.map
│       │   │   │   │   │   │   │       ├── brace-expressions.d.ts
│       │   │   │   │   │   │   │       ├── brace-expressions.d.ts.map
│       │   │   │   │   │   │   │       ├── brace-expressions.js
│       │   │   │   │   │   │   │       ├── brace-expressions.js.map
│       │   │   │   │   │   │   │       ├── escape.d.ts
│       │   │   │   │   │   │   │       ├── escape.d.ts.map
│       │   │   │   │   │   │   │       ├── escape.js
│       │   │   │   │   │   │   │       ├── escape.js.map
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       ├── unescape.d.ts
│       │   │   │   │   │   │   │       ├── unescape.d.ts.map
│       │   │   │   │   │   │   │       ├── unescape.js
│       │   │   │   │   │   │   │       └── unescape.js.map
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── minipass
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   └── package.json
│       │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       └── package.json
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── @modelcontextprotocol
│       │   │   │   │   │   │   ├── sdk
│       │   │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   │   ├── cjs
│       │   │   │   │   │   │   │   │   │   ├── cli.d.ts
│       │   │   │   │   │   │   │   │   │   ├── cli.d.ts.map
│       │   │   │   │   │   │   │   │   │   ├── client
│       │   │   │   │   │   │   │   │   │   │   ├── auth.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── auth.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── auth.js
│       │   │   │   │   │   │   │   │   │   │   ├── auth.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── sse.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── sse.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── sse.js
│       │   │   │   │   │   │   │   │   │   │   ├── sse.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.js
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── streamableHttp.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── streamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── streamableHttp.js
│       │   │   │   │   │   │   │   │   │   │   ├── streamableHttp.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── websocket.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── websocket.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── websocket.js
│       │   │   │   │   │   │   │   │   │   │   └── websocket.js.map
│       │   │   │   │   │   │   │   │   │   ├── cli.js
│       │   │   │   │   │   │   │   │   │   ├── cli.js.map
│       │   │   │   │   │   │   │   │   │   ├── examples
│       │   │   │   │   │   │   │   │   │   │   ├── client
│       │   │   │   │   │   │   │   │   │   │   │   ├── multipleClientsParallel.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── multipleClientsParallel.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── multipleClientsParallel.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── multipleClientsParallel.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── parallelToolCallsClient.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── parallelToolCallsClient.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── parallelToolCallsClient.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── parallelToolCallsClient.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleOAuthClient.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleOAuthClient.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleOAuthClient.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleOAuthClient.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStreamableHttp.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStreamableHttp.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── streamableHttpWithSseFallbackClient.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── streamableHttpWithSseFallbackClient.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── streamableHttpWithSseFallbackClient.js
│       │   │   │   │   │   │   │   │   │   │   │   └── streamableHttpWithSseFallbackClient.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── server
│       │   │   │   │   │   │   │   │   │   │   │   ├── demoInMemoryOAuthProvider.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── demoInMemoryOAuthProvider.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── demoInMemoryOAuthProvider.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── demoInMemoryOAuthProvider.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── jsonResponseStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── jsonResponseStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── jsonResponseStreamableHttp.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── jsonResponseStreamableHttp.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── mcpServerOutputSchema.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── mcpServerOutputSchema.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── mcpServerOutputSchema.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── mcpServerOutputSchema.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleSseServer.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleSseServer.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleSseServer.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleSseServer.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStatelessStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStatelessStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStatelessStreamableHttp.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStatelessStreamableHttp.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStreamableHttp.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── simpleStreamableHttp.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── sseAndStreamableHttpCompatibleServer.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── sseAndStreamableHttpCompatibleServer.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── sseAndStreamableHttpCompatibleServer.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── sseAndStreamableHttpCompatibleServer.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── standaloneSseWithGetStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── standaloneSseWithGetStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── standaloneSseWithGetStreamableHttp.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── standaloneSseWithGetStreamableHttp.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── toolWithSampleServer.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── toolWithSampleServer.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── toolWithSampleServer.js
│       │   │   │   │   │   │   │   │   │   │   │   └── toolWithSampleServer.js.map
│       │   │   │   │   │   │   │   │   │   │   └── shared
│       │   │   │   │   │   │   │   │   │   │       ├── inMemoryEventStore.d.ts
│       │   │   │   │   │   │   │   │   │   │       ├── inMemoryEventStore.d.ts.map
│       │   │   │   │   │   │   │   │   │   │       ├── inMemoryEventStore.js
│       │   │   │   │   │   │   │   │   │   │       └── inMemoryEventStore.js.map
│       │   │   │   │   │   │   │   │   │   ├── inMemory.d.ts
│       │   │   │   │   │   │   │   │   │   ├── inMemory.d.ts.map
│       │   │   │   │   │   │   │   │   │   ├── inMemory.js
│       │   │   │   │   │   │   │   │   │   ├── inMemory.js.map
│       │   │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   │   ├── server
│       │   │   │   │   │   │   │   │   │   │   ├── auth
│       │   │   │   │   │   │   │   │   │   │   │   ├── clients.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── clients.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── clients.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── clients.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── errors.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── errors.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── errors.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── errors.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── handlers
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── authorize.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── authorize.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── authorize.js
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── authorize.js.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── metadata.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── metadata.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── metadata.js
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── metadata.js.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── register.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── register.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── register.js
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── register.js.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── revoke.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── revoke.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── revoke.js
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── revoke.js.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── token.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── token.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── token.js
│       │   │   │   │   │   │   │   │   │   │   │   │   └── token.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── middleware
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── allowedMethods.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── allowedMethods.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── allowedMethods.js
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── allowedMethods.js.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── bearerAuth.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── bearerAuth.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── bearerAuth.js
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── bearerAuth.js.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── clientAuth.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── clientAuth.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── clientAuth.js
│       │   │   │   │   │   │   │   │   │   │   │   │   └── clientAuth.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── provider.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── provider.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── provider.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── provider.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── providers
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── proxyProvider.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── proxyProvider.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── proxyProvider.js
│       │   │   │   │   │   │   │   │   │   │   │   │   └── proxyProvider.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── router.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── router.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── router.js
│       │   │   │   │   │   │   │   │   │   │   │   ├── router.js.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── types.d.ts
│       │   │   │   │   │   │   │   │   │   │   │   ├── types.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   │   ├── types.js
│       │   │   │   │   │   │   │   │   │   │   │   └── types.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── completable.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── completable.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── completable.js
│       │   │   │   │   │   │   │   │   │   │   ├── completable.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── mcp.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── mcp.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── mcp.js
│       │   │   │   │   │   │   │   │   │   │   ├── mcp.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── sse.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── sse.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── sse.js
│       │   │   │   │   │   │   │   │   │   │   ├── sse.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.js
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── streamableHttp.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── streamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── streamableHttp.js
│       │   │   │   │   │   │   │   │   │   │   └── streamableHttp.js.map
│       │   │   │   │   │   │   │   │   │   ├── shared
│       │   │   │   │   │   │   │   │   │   │   ├── auth.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── auth.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── auth.js
│       │   │   │   │   │   │   │   │   │   │   ├── auth.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── auth-utils.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── auth-utils.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── auth-utils.js
│       │   │   │   │   │   │   │   │   │   │   ├── auth-utils.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── metadataUtils.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── metadataUtils.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── metadataUtils.js
│       │   │   │   │   │   │   │   │   │   │   ├── metadataUtils.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── protocol.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── protocol.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── protocol.js
│       │   │   │   │   │   │   │   │   │   │   ├── protocol.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.js
│       │   │   │   │   │   │   │   │   │   │   ├── stdio.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── transport.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── transport.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── transport.js
│       │   │   │   │   │   │   │   │   │   │   ├── transport.js.map
│       │   │   │   │   │   │   │   │   │   │   ├── uriTemplate.d.ts
│       │   │   │   │   │   │   │   │   │   │   ├── uriTemplate.d.ts.map
│       │   │   │   │   │   │   │   │   │   │   ├── uriTemplate.js
│       │   │   │   │   │   │   │   │   │   │   └── uriTemplate.js.map
│       │   │   │   │   │   │   │   │   │   ├── types.d.ts
│       │   │   │   │   │   │   │   │   │   ├── types.d.ts.map
│       │   │   │   │   │   │   │   │   │   ├── types.js
│       │   │   │   │   │   │   │   │   │   └── types.js.map
│       │   │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │   │       ├── cli.d.ts
│       │   │   │   │   │   │   │   │       ├── cli.d.ts.map
│       │   │   │   │   │   │   │   │       ├── client
│       │   │   │   │   │   │   │   │       │   ├── auth.d.ts
│       │   │   │   │   │   │   │   │       │   ├── auth.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── auth.js
│       │   │   │   │   │   │   │   │       │   ├── auth.js.map
│       │   │   │   │   │   │   │   │       │   ├── index.d.ts
│       │   │   │   │   │   │   │   │       │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── index.js
│       │   │   │   │   │   │   │   │       │   ├── index.js.map
│       │   │   │   │   │   │   │   │       │   ├── sse.d.ts
│       │   │   │   │   │   │   │   │       │   ├── sse.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── sse.js
│       │   │   │   │   │   │   │   │       │   ├── sse.js.map
│       │   │   │   │   │   │   │   │       │   ├── stdio.d.ts
│       │   │   │   │   │   │   │   │       │   ├── stdio.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── stdio.js
│       │   │   │   │   │   │   │   │       │   ├── stdio.js.map
│       │   │   │   │   │   │   │   │       │   ├── streamableHttp.d.ts
│       │   │   │   │   │   │   │   │       │   ├── streamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── streamableHttp.js
│       │   │   │   │   │   │   │   │       │   ├── streamableHttp.js.map
│       │   │   │   │   │   │   │   │       │   ├── websocket.d.ts
│       │   │   │   │   │   │   │   │       │   ├── websocket.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── websocket.js
│       │   │   │   │   │   │   │   │       │   └── websocket.js.map
│       │   │   │   │   │   │   │   │       ├── cli.js
│       │   │   │   │   │   │   │   │       ├── cli.js.map
│       │   │   │   │   │   │   │   │       ├── examples
│       │   │   │   │   │   │   │   │       │   ├── client
│       │   │   │   │   │   │   │   │       │   │   ├── multipleClientsParallel.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── multipleClientsParallel.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── multipleClientsParallel.js
│       │   │   │   │   │   │   │   │       │   │   ├── multipleClientsParallel.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── parallelToolCallsClient.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── parallelToolCallsClient.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── parallelToolCallsClient.js
│       │   │   │   │   │   │   │   │       │   │   ├── parallelToolCallsClient.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleOAuthClient.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── simpleOAuthClient.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleOAuthClient.js
│       │   │   │   │   │   │   │   │       │   │   ├── simpleOAuthClient.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStreamableHttp.js
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStreamableHttp.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── streamableHttpWithSseFallbackClient.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── streamableHttpWithSseFallbackClient.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── streamableHttpWithSseFallbackClient.js
│       │   │   │   │   │   │   │   │       │   │   └── streamableHttpWithSseFallbackClient.js.map
│       │   │   │   │   │   │   │   │       │   ├── server
│       │   │   │   │   │   │   │   │       │   │   ├── demoInMemoryOAuthProvider.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── demoInMemoryOAuthProvider.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── demoInMemoryOAuthProvider.js
│       │   │   │   │   │   │   │   │       │   │   ├── demoInMemoryOAuthProvider.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── jsonResponseStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── jsonResponseStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── jsonResponseStreamableHttp.js
│       │   │   │   │   │   │   │   │       │   │   ├── jsonResponseStreamableHttp.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── mcpServerOutputSchema.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── mcpServerOutputSchema.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── mcpServerOutputSchema.js
│       │   │   │   │   │   │   │   │       │   │   ├── mcpServerOutputSchema.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleSseServer.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── simpleSseServer.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleSseServer.js
│       │   │   │   │   │   │   │   │       │   │   ├── simpleSseServer.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStatelessStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStatelessStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStatelessStreamableHttp.js
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStatelessStreamableHttp.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStreamableHttp.js
│       │   │   │   │   │   │   │   │       │   │   ├── simpleStreamableHttp.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── sseAndStreamableHttpCompatibleServer.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── sseAndStreamableHttpCompatibleServer.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── sseAndStreamableHttpCompatibleServer.js
│       │   │   │   │   │   │   │   │       │   │   ├── sseAndStreamableHttpCompatibleServer.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── standaloneSseWithGetStreamableHttp.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── standaloneSseWithGetStreamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── standaloneSseWithGetStreamableHttp.js
│       │   │   │   │   │   │   │   │       │   │   ├── standaloneSseWithGetStreamableHttp.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── toolWithSampleServer.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── toolWithSampleServer.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── toolWithSampleServer.js
│       │   │   │   │   │   │   │   │       │   │   └── toolWithSampleServer.js.map
│       │   │   │   │   │   │   │   │       │   └── shared
│       │   │   │   │   │   │   │   │       │       ├── inMemoryEventStore.d.ts
│       │   │   │   │   │   │   │   │       │       ├── inMemoryEventStore.d.ts.map
│       │   │   │   │   │   │   │   │       │       ├── inMemoryEventStore.js
│       │   │   │   │   │   │   │   │       │       └── inMemoryEventStore.js.map
│       │   │   │   │   │   │   │   │       ├── inMemory.d.ts
│       │   │   │   │   │   │   │   │       ├── inMemory.d.ts.map
│       │   │   │   │   │   │   │   │       ├── inMemory.js
│       │   │   │   │   │   │   │   │       ├── inMemory.js.map
│       │   │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │   │       ├── server
│       │   │   │   │   │   │   │   │       │   ├── auth
│       │   │   │   │   │   │   │   │       │   │   ├── clients.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── clients.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── clients.js
│       │   │   │   │   │   │   │   │       │   │   ├── clients.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── errors.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── errors.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── errors.js
│       │   │   │   │   │   │   │   │       │   │   ├── errors.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── handlers
│       │   │   │   │   │   │   │   │       │   │   │   ├── authorize.d.ts
│       │   │   │   │   │   │   │   │       │   │   │   ├── authorize.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── authorize.js
│       │   │   │   │   │   │   │   │       │   │   │   ├── authorize.js.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── metadata.d.ts
│       │   │   │   │   │   │   │   │       │   │   │   ├── metadata.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── metadata.js
│       │   │   │   │   │   │   │   │       │   │   │   ├── metadata.js.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── register.d.ts
│       │   │   │   │   │   │   │   │       │   │   │   ├── register.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── register.js
│       │   │   │   │   │   │   │   │       │   │   │   ├── register.js.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── revoke.d.ts
│       │   │   │   │   │   │   │   │       │   │   │   ├── revoke.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── revoke.js
│       │   │   │   │   │   │   │   │       │   │   │   ├── revoke.js.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── token.d.ts
│       │   │   │   │   │   │   │   │       │   │   │   ├── token.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── token.js
│       │   │   │   │   │   │   │   │       │   │   │   └── token.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── middleware
│       │   │   │   │   │   │   │   │       │   │   │   ├── allowedMethods.d.ts
│       │   │   │   │   │   │   │   │       │   │   │   ├── allowedMethods.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── allowedMethods.js
│       │   │   │   │   │   │   │   │       │   │   │   ├── allowedMethods.js.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── bearerAuth.d.ts
│       │   │   │   │   │   │   │   │       │   │   │   ├── bearerAuth.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── bearerAuth.js
│       │   │   │   │   │   │   │   │       │   │   │   ├── bearerAuth.js.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── clientAuth.d.ts
│       │   │   │   │   │   │   │   │       │   │   │   ├── clientAuth.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── clientAuth.js
│       │   │   │   │   │   │   │   │       │   │   │   └── clientAuth.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── provider.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── provider.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── provider.js
│       │   │   │   │   │   │   │   │       │   │   ├── provider.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── providers
│       │   │   │   │   │   │   │   │       │   │   │   ├── proxyProvider.d.ts
│       │   │   │   │   │   │   │   │       │   │   │   ├── proxyProvider.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   │   ├── proxyProvider.js
│       │   │   │   │   │   │   │   │       │   │   │   └── proxyProvider.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── router.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── router.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── router.js
│       │   │   │   │   │   │   │   │       │   │   ├── router.js.map
│       │   │   │   │   │   │   │   │       │   │   ├── types.d.ts
│       │   │   │   │   │   │   │   │       │   │   ├── types.d.ts.map
│       │   │   │   │   │   │   │   │       │   │   ├── types.js
│       │   │   │   │   │   │   │   │       │   │   └── types.js.map
│       │   │   │   │   │   │   │   │       │   ├── completable.d.ts
│       │   │   │   │   │   │   │   │       │   ├── completable.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── completable.js
│       │   │   │   │   │   │   │   │       │   ├── completable.js.map
│       │   │   │   │   │   │   │   │       │   ├── index.d.ts
│       │   │   │   │   │   │   │   │       │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── index.js
│       │   │   │   │   │   │   │   │       │   ├── index.js.map
│       │   │   │   │   │   │   │   │       │   ├── mcp.d.ts
│       │   │   │   │   │   │   │   │       │   ├── mcp.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── mcp.js
│       │   │   │   │   │   │   │   │       │   ├── mcp.js.map
│       │   │   │   │   │   │   │   │       │   ├── sse.d.ts
│       │   │   │   │   │   │   │   │       │   ├── sse.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── sse.js
│       │   │   │   │   │   │   │   │       │   ├── sse.js.map
│       │   │   │   │   │   │   │   │       │   ├── stdio.d.ts
│       │   │   │   │   │   │   │   │       │   ├── stdio.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── stdio.js
│       │   │   │   │   │   │   │   │       │   ├── stdio.js.map
│       │   │   │   │   │   │   │   │       │   ├── streamableHttp.d.ts
│       │   │   │   │   │   │   │   │       │   ├── streamableHttp.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── streamableHttp.js
│       │   │   │   │   │   │   │   │       │   └── streamableHttp.js.map
│       │   │   │   │   │   │   │   │       ├── shared
│       │   │   │   │   │   │   │   │       │   ├── auth.d.ts
│       │   │   │   │   │   │   │   │       │   ├── auth.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── auth.js
│       │   │   │   │   │   │   │   │       │   ├── auth.js.map
│       │   │   │   │   │   │   │   │       │   ├── auth-utils.d.ts
│       │   │   │   │   │   │   │   │       │   ├── auth-utils.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── auth-utils.js
│       │   │   │   │   │   │   │   │       │   ├── auth-utils.js.map
│       │   │   │   │   │   │   │   │       │   ├── metadataUtils.d.ts
│       │   │   │   │   │   │   │   │       │   ├── metadataUtils.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── metadataUtils.js
│       │   │   │   │   │   │   │   │       │   ├── metadataUtils.js.map
│       │   │   │   │   │   │   │   │       │   ├── protocol.d.ts
│       │   │   │   │   │   │   │   │       │   ├── protocol.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── protocol.js
│       │   │   │   │   │   │   │   │       │   ├── protocol.js.map
│       │   │   │   │   │   │   │   │       │   ├── stdio.d.ts
│       │   │   │   │   │   │   │   │       │   ├── stdio.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── stdio.js
│       │   │   │   │   │   │   │   │       │   ├── stdio.js.map
│       │   │   │   │   │   │   │   │       │   ├── transport.d.ts
│       │   │   │   │   │   │   │   │       │   ├── transport.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── transport.js
│       │   │   │   │   │   │   │   │       │   ├── transport.js.map
│       │   │   │   │   │   │   │   │       │   ├── uriTemplate.d.ts
│       │   │   │   │   │   │   │   │       │   ├── uriTemplate.d.ts.map
│       │   │   │   │   │   │   │   │       │   ├── uriTemplate.js
│       │   │   │   │   │   │   │   │       │   └── uriTemplate.js.map
│       │   │   │   │   │   │   │   │       ├── types.d.ts
│       │   │   │   │   │   │   │   │       ├── types.d.ts.map
│       │   │   │   │   │   │   │   │       ├── types.js
│       │   │   │   │   │   │   │   │       └── types.js.map
│       │   │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   │   └── server-filesystem
│       │   │   │   │   │   │       ├── dist
│       │   │   │   │   │   │       │   ├── index.js
│       │   │   │   │   │   │       │   ├── path-utils.js
│       │   │   │   │   │   │       │   ├── path-validation.js
│       │   │   │   │   │   │       │   └── __tests__
│       │   │   │   │   │   │       │       ├── path-utils.test.js
│       │   │   │   │   │   │       │       └── path-validation.test.js
│       │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │       └── README.md
│       │   │   │   │   │   ├── ms
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── negotiator
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── charset.js
│       │   │   │   │   │   │   │   ├── encoding.js
│       │   │   │   │   │   │   │   ├── language.js
│       │   │   │   │   │   │   │   └── mediaType.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── object-assign
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── object-inspect
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── example
│       │   │   │   │   │   │   │   ├── all.js
│       │   │   │   │   │   │   │   ├── circular.js
│       │   │   │   │   │   │   │   ├── fn.js
│       │   │   │   │   │   │   │   └── inspect.js
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── package-support.json
│       │   │   │   │   │   │   ├── readme.markdown
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   ├── bigint.js
│       │   │   │   │   │   │   │   ├── browser
│       │   │   │   │   │   │   │   │   └── dom.js
│       │   │   │   │   │   │   │   ├── circular.js
│       │   │   │   │   │   │   │   ├── deep.js
│       │   │   │   │   │   │   │   ├── element.js
│       │   │   │   │   │   │   │   ├── err.js
│       │   │   │   │   │   │   │   ├── fakes.js
│       │   │   │   │   │   │   │   ├── fn.js
│       │   │   │   │   │   │   │   ├── global.js
│       │   │   │   │   │   │   │   ├── has.js
│       │   │   │   │   │   │   │   ├── holes.js
│       │   │   │   │   │   │   │   ├── indent-option.js
│       │   │   │   │   │   │   │   ├── inspect.js
│       │   │   │   │   │   │   │   ├── lowbyte.js
│       │   │   │   │   │   │   │   ├── number.js
│       │   │   │   │   │   │   │   ├── quoteStyle.js
│       │   │   │   │   │   │   │   ├── toStringTag.js
│       │   │   │   │   │   │   │   ├── undef.js
│       │   │   │   │   │   │   │   └── values.js
│       │   │   │   │   │   │   ├── test-core-js.js
│       │   │   │   │   │   │   └── util.inspect.js
│       │   │   │   │   │   ├── once
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── once.js
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── on-finished
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── package-json-from-dist
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   └── package.json
│       │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       └── package.json
│       │   │   │   │   │   │   ├── LICENSE.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── parseurl
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── path-key
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── path-scurry
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── commonjs
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   └── package.json
│       │   │   │   │   │   │   │   └── esm
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       └── package.json
│       │   │   │   │   │   │   ├── LICENSE.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── path-to-regexp
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   └── index.js.map
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── Readme.md
│       │   │   │   │   │   ├── pkce-challenge
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── index.browser.d.ts
│       │   │   │   │   │   │   │   ├── index.browser.js
│       │   │   │   │   │   │   │   ├── index.node.cjs
│       │   │   │   │   │   │   │   ├── index.node.d.cts
│       │   │   │   │   │   │   │   ├── index.node.d.ts
│       │   │   │   │   │   │   │   └── index.node.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── @pkgjs
│       │   │   │   │   │   │   └── parseargs
│       │   │   │   │   │   │       ├── CHANGELOG.md
│       │   │   │   │   │   │       ├── examples
│       │   │   │   │   │   │       │   ├── is-default-value.js
│       │   │   │   │   │   │       │   ├── limit-long-syntax.js
│       │   │   │   │   │   │       │   ├── negate.js
│       │   │   │   │   │   │       │   ├── no-repeated-options.js
│       │   │   │   │   │   │       │   ├── ordered-options.mjs
│       │   │   │   │   │   │       │   └── simple-hard-coded.js
│       │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │       ├── internal
│       │   │   │   │   │   │       │   ├── errors.js
│       │   │   │   │   │   │       │   ├── primordials.js
│       │   │   │   │   │   │       │   ├── util.js
│       │   │   │   │   │   │       │   └── validators.js
│       │   │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │       ├── README.md
│       │   │   │   │   │   │       └── utils.js
│       │   │   │   │   │   ├── proxy-addr
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── punycode
│       │   │   │   │   │   │   ├── LICENSE-MIT.txt
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── punycode.es6.js
│       │   │   │   │   │   │   ├── punycode.js
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── qs
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   └── qs.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── formats.js
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   ├── parse.js
│       │   │   │   │   │   │   │   ├── stringify.js
│       │   │   │   │   │   │   │   └── utils.js
│       │   │   │   │   │   │   ├── LICENSE.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── test
│       │   │   │   │   │   │       ├── empty-keys-cases.js
│       │   │   │   │   │   │       ├── parse.js
│       │   │   │   │   │   │       ├── stringify.js
│       │   │   │   │   │   │       └── utils.js
│       │   │   │   │   │   ├── range-parser
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── raw-body
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── SECURITY.md
│       │   │   │   │   │   ├── router
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   │   ├── layer.js
│       │   │   │   │   │   │   │   └── route.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── safe-buffer
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── safer-buffer
│       │   │   │   │   │   │   ├── dangerous.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── Porting-Buffer.md
│       │   │   │   │   │   │   ├── Readme.md
│       │   │   │   │   │   │   ├── safer.js
│       │   │   │   │   │   │   └── tests.js
│       │   │   │   │   │   ├── send
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── serve-static
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── setprototypeof
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── test
│       │   │   │   │   │   │       └── index.js
│       │   │   │   │   │   ├── shebang-command
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── shebang-regex
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── side-channel
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── side-channel-list
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── list.d.ts
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── side-channel-map
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── side-channel-weakmap
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   └── index.js
│       │   │   │   │   │   │   └── tsconfig.json
│       │   │   │   │   │   ├── signal-exit
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── cjs
│       │   │   │   │   │   │   │   │   ├── browser.d.ts
│       │   │   │   │   │   │   │   │   ├── browser.d.ts.map
│       │   │   │   │   │   │   │   │   ├── browser.js
│       │   │   │   │   │   │   │   │   ├── browser.js.map
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.d.ts.map
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── index.js.map
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   ├── signals.d.ts
│       │   │   │   │   │   │   │   │   ├── signals.d.ts.map
│       │   │   │   │   │   │   │   │   ├── signals.js
│       │   │   │   │   │   │   │   │   └── signals.js.map
│       │   │   │   │   │   │   │   └── mjs
│       │   │   │   │   │   │   │       ├── browser.d.ts
│       │   │   │   │   │   │   │       ├── browser.d.ts.map
│       │   │   │   │   │   │   │       ├── browser.js
│       │   │   │   │   │   │   │       ├── browser.js.map
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.d.ts.map
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       ├── signals.d.ts
│       │   │   │   │   │   │   │       ├── signals.d.ts.map
│       │   │   │   │   │   │   │       ├── signals.js
│       │   │   │   │   │   │   │       └── signals.js.map
│       │   │   │   │   │   │   ├── LICENSE.txt
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── statuses
│       │   │   │   │   │   │   ├── codes.json
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── string-width
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── string-width-cjs
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── node_modules
│       │   │   │   │   │   │   │   ├── ansi-regex
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   │   │   ├── emoji-regex
│       │   │   │   │   │   │   │   │   ├── es2015
│       │   │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   │   └── text.js
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── LICENSE-MIT.txt
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   │   │   └── text.js
│       │   │   │   │   │   │   │   └── strip-ansi
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── license
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       └── readme.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── strip-ansi
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── strip-ansi-cjs
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── node_modules
│       │   │   │   │   │   │   │   └── ansi-regex
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── license
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       └── readme.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── toidentifier
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── type-is
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── unpipe
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── uri-js
│       │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   ├── es5
│       │   │   │   │   │   │   │   │   ├── uri.all.d.ts
│       │   │   │   │   │   │   │   │   ├── uri.all.js
│       │   │   │   │   │   │   │   │   ├── uri.all.js.map
│       │   │   │   │   │   │   │   │   ├── uri.all.min.d.ts
│       │   │   │   │   │   │   │   │   ├── uri.all.min.js
│       │   │   │   │   │   │   │   │   └── uri.all.min.js.map
│       │   │   │   │   │   │   │   └── esnext
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── index.js.map
│       │   │   │   │   │   │   │       ├── regexps-iri.d.ts
│       │   │   │   │   │   │   │       ├── regexps-iri.js
│       │   │   │   │   │   │   │       ├── regexps-iri.js.map
│       │   │   │   │   │   │   │       ├── regexps-uri.d.ts
│       │   │   │   │   │   │   │       ├── regexps-uri.js
│       │   │   │   │   │   │   │       ├── regexps-uri.js.map
│       │   │   │   │   │   │   │       ├── schemes
│       │   │   │   │   │   │   │       │   ├── http.d.ts
│       │   │   │   │   │   │   │       │   ├── http.js
│       │   │   │   │   │   │   │       │   ├── http.js.map
│       │   │   │   │   │   │   │       │   ├── https.d.ts
│       │   │   │   │   │   │   │       │   ├── https.js
│       │   │   │   │   │   │   │       │   ├── https.js.map
│       │   │   │   │   │   │   │       │   ├── mailto.d.ts
│       │   │   │   │   │   │   │       │   ├── mailto.js
│       │   │   │   │   │   │   │       │   ├── mailto.js.map
│       │   │   │   │   │   │   │       │   ├── urn.d.ts
│       │   │   │   │   │   │   │       │   ├── urn.js
│       │   │   │   │   │   │   │       │   ├── urn.js.map
│       │   │   │   │   │   │   │       │   ├── urn-uuid.d.ts
│       │   │   │   │   │   │   │       │   ├── urn-uuid.js
│       │   │   │   │   │   │   │       │   ├── urn-uuid.js.map
│       │   │   │   │   │   │   │       │   ├── ws.d.ts
│       │   │   │   │   │   │   │       │   ├── ws.js
│       │   │   │   │   │   │   │       │   ├── ws.js.map
│       │   │   │   │   │   │   │       │   ├── wss.d.ts
│       │   │   │   │   │   │   │       │   ├── wss.js
│       │   │   │   │   │   │   │       │   └── wss.js.map
│       │   │   │   │   │   │   │       ├── uri.d.ts
│       │   │   │   │   │   │   │       ├── uri.js
│       │   │   │   │   │   │   │       ├── uri.js.map
│       │   │   │   │   │   │   │       ├── util.d.ts
│       │   │   │   │   │   │   │       ├── util.js
│       │   │   │   │   │   │   │       └── util.js.map
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── yarn.lock
│       │   │   │   │   │   ├── vary
│       │   │   │   │   │   │   ├── HISTORY.md
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   ├── which
│       │   │   │   │   │   │   ├── bin
│       │   │   │   │   │   │   │   └── node-which
│       │   │   │   │   │   │   ├── CHANGELOG.md
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── which.js
│       │   │   │   │   │   ├── wrap-ansi
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── wrap-ansi-cjs
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   ├── node_modules
│       │   │   │   │   │   │   │   ├── ansi-regex
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   │   │   ├── ansi-styles
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   │   │   ├── emoji-regex
│       │   │   │   │   │   │   │   │   ├── es2015
│       │   │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   │   └── text.js
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── LICENSE-MIT.txt
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   │   │   └── text.js
│       │   │   │   │   │   │   │   ├── string-width
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── license
│       │   │   │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   │   │   └── strip-ansi
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── license
│       │   │   │   │   │   │   │       ├── package.json
│       │   │   │   │   │   │   │       └── readme.md
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   └── readme.md
│       │   │   │   │   │   ├── wrappy
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── wrappy.js
│       │   │   │   │   │   ├── zod
│       │   │   │   │   │   │   ├── index.cjs
│       │   │   │   │   │   │   ├── index.d.cts
│       │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── package.json
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── src
│       │   │   │   │   │   │   │   ├── index.ts
│       │   │   │   │   │   │   │   ├── v3
│       │   │   │   │   │   │   │   │   ├── benchmarks
│       │   │   │   │   │   │   │   │   │   ├── datetime.ts
│       │   │   │   │   │   │   │   │   │   ├── discriminatedUnion.ts
│       │   │   │   │   │   │   │   │   │   ├── index.ts
│       │   │   │   │   │   │   │   │   │   ├── ipv4.ts
│       │   │   │   │   │   │   │   │   │   ├── object.ts
│       │   │   │   │   │   │   │   │   │   ├── primitives.ts
│       │   │   │   │   │   │   │   │   │   ├── realworld.ts
│       │   │   │   │   │   │   │   │   │   ├── string.ts
│       │   │   │   │   │   │   │   │   │   └── union.ts
│       │   │   │   │   │   │   │   │   ├── errors.ts
│       │   │   │   │   │   │   │   │   ├── external.ts
│       │   │   │   │   │   │   │   │   ├── helpers
│       │   │   │   │   │   │   │   │   │   ├── enumUtil.ts
│       │   │   │   │   │   │   │   │   │   ├── errorUtil.ts
│       │   │   │   │   │   │   │   │   │   ├── parseUtil.ts
│       │   │   │   │   │   │   │   │   │   ├── partialUtil.ts
│       │   │   │   │   │   │   │   │   │   ├── typeAliases.ts
│       │   │   │   │   │   │   │   │   │   └── util.ts
│       │   │   │   │   │   │   │   │   ├── index.ts
│       │   │   │   │   │   │   │   │   ├── locales
│       │   │   │   │   │   │   │   │   │   └── en.ts
│       │   │   │   │   │   │   │   │   ├── standard-schema.ts
│       │   │   │   │   │   │   │   │   ├── tests
│       │   │   │   │   │   │   │   │   │   ├── all-errors.test.ts
│       │   │   │   │   │   │   │   │   │   ├── anyunknown.test.ts
│       │   │   │   │   │   │   │   │   │   ├── array.test.ts
│       │   │   │   │   │   │   │   │   │   ├── async-parsing.test.ts
│       │   │   │   │   │   │   │   │   │   ├── async-refinements.test.ts
│       │   │   │   │   │   │   │   │   │   ├── base.test.ts
│       │   │   │   │   │   │   │   │   │   ├── bigint.test.ts
│       │   │   │   │   │   │   │   │   │   ├── branded.test.ts
│       │   │   │   │   │   │   │   │   │   ├── catch.test.ts
│       │   │   │   │   │   │   │   │   │   ├── coerce.test.ts
│       │   │   │   │   │   │   │   │   │   ├── complex.test.ts
│       │   │   │   │   │   │   │   │   │   ├── custom.test.ts
│       │   │   │   │   │   │   │   │   │   ├── date.test.ts
│       │   │   │   │   │   │   │   │   │   ├── deepmasking.test.ts
│       │   │   │   │   │   │   │   │   │   ├── default.test.ts
│       │   │   │   │   │   │   │   │   │   ├── description.test.ts
│       │   │   │   │   │   │   │   │   │   ├── discriminated-unions.test.ts
│       │   │   │   │   │   │   │   │   │   ├── enum.test.ts
│       │   │   │   │   │   │   │   │   │   ├── error.test.ts
│       │   │   │   │   │   │   │   │   │   ├── firstpartyschematypes.test.ts
│       │   │   │   │   │   │   │   │   │   ├── firstparty.test.ts
│       │   │   │   │   │   │   │   │   │   ├── function.test.ts
│       │   │   │   │   │   │   │   │   │   ├── generics.test.ts
│       │   │   │   │   │   │   │   │   │   ├── instanceof.test.ts
│       │   │   │   │   │   │   │   │   │   ├── intersection.test.ts
│       │   │   │   │   │   │   │   │   │   ├── language-server.source.ts
│       │   │   │   │   │   │   │   │   │   ├── language-server.test.ts
│       │   │   │   │   │   │   │   │   │   ├── literal.test.ts
│       │   │   │   │   │   │   │   │   │   ├── map.test.ts
│       │   │   │   │   │   │   │   │   │   ├── masking.test.ts
│       │   │   │   │   │   │   │   │   │   ├── mocker.test.ts
│       │   │   │   │   │   │   │   │   │   ├── Mocker.ts
│       │   │   │   │   │   │   │   │   │   ├── nan.test.ts
│       │   │   │   │   │   │   │   │   │   ├── nativeEnum.test.ts
│       │   │   │   │   │   │   │   │   │   ├── nullable.test.ts
│       │   │   │   │   │   │   │   │   │   ├── number.test.ts
│       │   │   │   │   │   │   │   │   │   ├── object-augmentation.test.ts
│       │   │   │   │   │   │   │   │   │   ├── object-in-es5-env.test.ts
│       │   │   │   │   │   │   │   │   │   ├── object.test.ts
│       │   │   │   │   │   │   │   │   │   ├── optional.test.ts
│       │   │   │   │   │   │   │   │   │   ├── parser.test.ts
│       │   │   │   │   │   │   │   │   │   ├── parseUtil.test.ts
│       │   │   │   │   │   │   │   │   │   ├── partials.test.ts
│       │   │   │   │   │   │   │   │   │   ├── pickomit.test.ts
│       │   │   │   │   │   │   │   │   │   ├── pipeline.test.ts
│       │   │   │   │   │   │   │   │   │   ├── preprocess.test.ts
│       │   │   │   │   │   │   │   │   │   ├── primitive.test.ts
│       │   │   │   │   │   │   │   │   │   ├── promise.test.ts
│       │   │   │   │   │   │   │   │   │   ├── readonly.test.ts
│       │   │   │   │   │   │   │   │   │   ├── record.test.ts
│       │   │   │   │   │   │   │   │   │   ├── recursive.test.ts
│       │   │   │   │   │   │   │   │   │   ├── refine.test.ts
│       │   │   │   │   │   │   │   │   │   ├── safeparse.test.ts
│       │   │   │   │   │   │   │   │   │   ├── set.test.ts
│       │   │   │   │   │   │   │   │   │   ├── standard-schema.test.ts
│       │   │   │   │   │   │   │   │   │   ├── string.test.ts
│       │   │   │   │   │   │   │   │   │   ├── transformer.test.ts
│       │   │   │   │   │   │   │   │   │   ├── tuple.test.ts
│       │   │   │   │   │   │   │   │   │   ├── unions.test.ts
│       │   │   │   │   │   │   │   │   │   ├── validations.test.ts
│       │   │   │   │   │   │   │   │   │   └── void.test.ts
│       │   │   │   │   │   │   │   │   ├── types.ts
│       │   │   │   │   │   │   │   │   └── ZodError.ts
│       │   │   │   │   │   │   │   ├── v4
│       │   │   │   │   │   │   │   │   ├── classic
│       │   │   │   │   │   │   │   │   │   ├── checks.ts
│       │   │   │   │   │   │   │   │   │   ├── coerce.ts
│       │   │   │   │   │   │   │   │   │   ├── compat.ts
│       │   │   │   │   │   │   │   │   │   ├── errors.ts
│       │   │   │   │   │   │   │   │   │   ├── external.ts
│       │   │   │   │   │   │   │   │   │   ├── index.ts
│       │   │   │   │   │   │   │   │   │   ├── iso.ts
│       │   │   │   │   │   │   │   │   │   ├── parse.ts
│       │   │   │   │   │   │   │   │   │   ├── schemas.ts
│       │   │   │   │   │   │   │   │   │   └── tests
│       │   │   │   │   │   │   │   │   │       ├── anyunknown.test.ts
│       │   │   │   │   │   │   │   │   │       ├── array.test.ts
│       │   │   │   │   │   │   │   │   │       ├── assignability.test.ts
│       │   │   │   │   │   │   │   │   │       ├── async-parsing.test.ts
│       │   │   │   │   │   │   │   │   │       ├── async-refinements.test.ts
│       │   │   │   │   │   │   │   │   │       ├── base.test.ts
│       │   │   │   │   │   │   │   │   │       ├── bigint.test.ts
│       │   │   │   │   │   │   │   │   │       ├── brand.test.ts
│       │   │   │   │   │   │   │   │   │       ├── catch.test.ts
│       │   │   │   │   │   │   │   │   │       ├── coalesce.test.ts
│       │   │   │   │   │   │   │   │   │       ├── coerce.test.ts
│       │   │   │   │   │   │   │   │   │       ├── continuability.test.ts
│       │   │   │   │   │   │   │   │   │       ├── custom.test.ts
│       │   │   │   │   │   │   │   │   │       ├── date.test.ts
│       │   │   │   │   │   │   │   │   │       ├── datetime.test.ts
│       │   │   │   │   │   │   │   │   │       ├── default.test.ts
│       │   │   │   │   │   │   │   │   │       ├── description.test.ts
│       │   │   │   │   │   │   │   │   │       ├── discriminated-unions.test.ts
│       │   │   │   │   │   │   │   │   │       ├── enum.test.ts
│       │   │   │   │   │   │   │   │   │       ├── error.test.ts
│       │   │   │   │   │   │   │   │   │       ├── error-utils.test.ts
│       │   │   │   │   │   │   │   │   │       ├── file.test.ts
│       │   │   │   │   │   │   │   │   │       ├── firstparty.test.ts
│       │   │   │   │   │   │   │   │   │       ├── function.test.ts
│       │   │   │   │   │   │   │   │   │       ├── generics.test.ts
│       │   │   │   │   │   │   │   │   │       ├── index.test.ts
│       │   │   │   │   │   │   │   │   │       ├── instanceof.test.ts
│       │   │   │   │   │   │   │   │   │       ├── intersection.test.ts
│       │   │   │   │   │   │   │   │   │       ├── json.test.ts
│       │   │   │   │   │   │   │   │   │       ├── lazy.test.ts
│       │   │   │   │   │   │   │   │   │       ├── literal.test.ts
│       │   │   │   │   │   │   │   │   │       ├── map.test.ts
│       │   │   │   │   │   │   │   │   │       ├── nan.test.ts
│       │   │   │   │   │   │   │   │   │       ├── nested-refine.test.ts
│       │   │   │   │   │   │   │   │   │       ├── nonoptional.test.ts
│       │   │   │   │   │   │   │   │   │       ├── nullable.test.ts
│       │   │   │   │   │   │   │   │   │       ├── number.test.ts
│       │   │   │   │   │   │   │   │   │       ├── object.test.ts
│       │   │   │   │   │   │   │   │   │       ├── optional.test.ts
│       │   │   │   │   │   │   │   │   │       ├── partial.test.ts
│       │   │   │   │   │   │   │   │   │       ├── pickomit.test.ts
│       │   │   │   │   │   │   │   │   │       ├── pipe.test.ts
│       │   │   │   │   │   │   │   │   │       ├── prefault.test.ts
│       │   │   │   │   │   │   │   │   │       ├── preprocess.test.ts
│       │   │   │   │   │   │   │   │   │       ├── primitive.test.ts
│       │   │   │   │   │   │   │   │   │       ├── promise.test.ts
│       │   │   │   │   │   │   │   │   │       ├── prototypes.test.ts
│       │   │   │   │   │   │   │   │   │       ├── readonly.test.ts
│       │   │   │   │   │   │   │   │   │       ├── record.test.ts
│       │   │   │   │   │   │   │   │   │       ├── recursive-types.test.ts
│       │   │   │   │   │   │   │   │   │       ├── refine.test.ts
│       │   │   │   │   │   │   │   │   │       ├── registries.test.ts
│       │   │   │   │   │   │   │   │   │       ├── set.test.ts
│       │   │   │   │   │   │   │   │   │       ├── standard-schema.test.ts
│       │   │   │   │   │   │   │   │   │       ├── stringbool.test.ts
│       │   │   │   │   │   │   │   │   │       ├── string-formats.test.ts
│       │   │   │   │   │   │   │   │   │       ├── string.test.ts
│       │   │   │   │   │   │   │   │   │       ├── template-literal.test.ts
│       │   │   │   │   │   │   │   │   │       ├── to-json-schema.test.ts
│       │   │   │   │   │   │   │   │   │       ├── transform.test.ts
│       │   │   │   │   │   │   │   │   │       ├── tuple.test.ts
│       │   │   │   │   │   │   │   │   │       ├── union.test.ts
│       │   │   │   │   │   │   │   │   │       ├── validations.test.ts
│       │   │   │   │   │   │   │   │   │       └── void.test.ts
│       │   │   │   │   │   │   │   │   ├── core
│       │   │   │   │   │   │   │   │   │   ├── api.ts
│       │   │   │   │   │   │   │   │   │   ├── checks.ts
│       │   │   │   │   │   │   │   │   │   ├── config.ts
│       │   │   │   │   │   │   │   │   │   ├── core.ts
│       │   │   │   │   │   │   │   │   │   ├── doc.ts
│       │   │   │   │   │   │   │   │   │   ├── errors.ts
│       │   │   │   │   │   │   │   │   │   ├── function.ts
│       │   │   │   │   │   │   │   │   │   ├── index.ts
│       │   │   │   │   │   │   │   │   │   ├── json-schema.ts
│       │   │   │   │   │   │   │   │   │   ├── parse.ts
│       │   │   │   │   │   │   │   │   │   ├── regexes.ts
│       │   │   │   │   │   │   │   │   │   ├── registries.ts
│       │   │   │   │   │   │   │   │   │   ├── schemas.ts
│       │   │   │   │   │   │   │   │   │   ├── standard-schema.ts
│       │   │   │   │   │   │   │   │   │   ├── tests
│       │   │   │   │   │   │   │   │   │   │   ├── index.test.ts
│       │   │   │   │   │   │   │   │   │   │   └── locales
│       │   │   │   │   │   │   │   │   │   │       ├── be.test.ts
│       │   │   │   │   │   │   │   │   │   │       ├── en.test.ts
│       │   │   │   │   │   │   │   │   │   │       ├── ru.test.ts
│       │   │   │   │   │   │   │   │   │   │       └── tr.test.ts
│       │   │   │   │   │   │   │   │   │   ├── to-json-schema.ts
│       │   │   │   │   │   │   │   │   │   ├── util.ts
│       │   │   │   │   │   │   │   │   │   ├── versions.ts
│       │   │   │   │   │   │   │   │   │   └── zsf.ts
│       │   │   │   │   │   │   │   │   ├── index.ts
│       │   │   │   │   │   │   │   │   ├── locales
│       │   │   │   │   │   │   │   │   │   ├── ar.ts
│       │   │   │   │   │   │   │   │   │   ├── az.ts
│       │   │   │   │   │   │   │   │   │   ├── be.ts
│       │   │   │   │   │   │   │   │   │   ├── ca.ts
│       │   │   │   │   │   │   │   │   │   ├── cs.ts
│       │   │   │   │   │   │   │   │   │   ├── de.ts
│       │   │   │   │   │   │   │   │   │   ├── en.ts
│       │   │   │   │   │   │   │   │   │   ├── eo.ts
│       │   │   │   │   │   │   │   │   │   ├── es.ts
│       │   │   │   │   │   │   │   │   │   ├── fa.ts
│       │   │   │   │   │   │   │   │   │   ├── fi.ts
│       │   │   │   │   │   │   │   │   │   ├── fr-CA.ts
│       │   │   │   │   │   │   │   │   │   ├── fr.ts
│       │   │   │   │   │   │   │   │   │   ├── he.ts
│       │   │   │   │   │   │   │   │   │   ├── hu.ts
│       │   │   │   │   │   │   │   │   │   ├── id.ts
│       │   │   │   │   │   │   │   │   │   ├── index.ts
│       │   │   │   │   │   │   │   │   │   ├── it.ts
│       │   │   │   │   │   │   │   │   │   ├── ja.ts
│       │   │   │   │   │   │   │   │   │   ├── kh.ts
│       │   │   │   │   │   │   │   │   │   ├── ko.ts
│       │   │   │   │   │   │   │   │   │   ├── mk.ts
│       │   │   │   │   │   │   │   │   │   ├── ms.ts
│       │   │   │   │   │   │   │   │   │   ├── nl.ts
│       │   │   │   │   │   │   │   │   │   ├── no.ts
│       │   │   │   │   │   │   │   │   │   ├── ota.ts
│       │   │   │   │   │   │   │   │   │   ├── pl.ts
│       │   │   │   │   │   │   │   │   │   ├── ps.ts
│       │   │   │   │   │   │   │   │   │   ├── pt.ts
│       │   │   │   │   │   │   │   │   │   ├── ru.ts
│       │   │   │   │   │   │   │   │   │   ├── sl.ts
│       │   │   │   │   │   │   │   │   │   ├── sv.ts
│       │   │   │   │   │   │   │   │   │   ├── ta.ts
│       │   │   │   │   │   │   │   │   │   ├── th.ts
│       │   │   │   │   │   │   │   │   │   ├── tr.ts
│       │   │   │   │   │   │   │   │   │   ├── ua.ts
│       │   │   │   │   │   │   │   │   │   ├── ur.ts
│       │   │   │   │   │   │   │   │   │   ├── vi.ts
│       │   │   │   │   │   │   │   │   │   ├── zh-CN.ts
│       │   │   │   │   │   │   │   │   │   └── zh-TW.ts
│       │   │   │   │   │   │   │   │   └── mini
│       │   │   │   │   │   │   │   │       ├── checks.ts
│       │   │   │   │   │   │   │   │       ├── coerce.ts
│       │   │   │   │   │   │   │   │       ├── external.ts
│       │   │   │   │   │   │   │   │       ├── index.ts
│       │   │   │   │   │   │   │   │       ├── iso.ts
│       │   │   │   │   │   │   │   │       ├── parse.ts
│       │   │   │   │   │   │   │   │       ├── schemas.ts
│       │   │   │   │   │   │   │   │       └── tests
│       │   │   │   │   │   │   │   │           ├── assignability.test.ts
│       │   │   │   │   │   │   │   │           ├── brand.test.ts
│       │   │   │   │   │   │   │   │           ├── checks.test.ts
│       │   │   │   │   │   │   │   │           ├── computed.test.ts
│       │   │   │   │   │   │   │   │           ├── error.test.ts
│       │   │   │   │   │   │   │   │           ├── functions.test.ts
│       │   │   │   │   │   │   │   │           ├── index.test.ts
│       │   │   │   │   │   │   │   │           ├── number.test.ts
│       │   │   │   │   │   │   │   │           ├── object.test.ts
│       │   │   │   │   │   │   │   │           ├── prototypes.test.ts
│       │   │   │   │   │   │   │   │           ├── recursive-types.test.ts
│       │   │   │   │   │   │   │   │           └── string.test.ts
│       │   │   │   │   │   │   │   └── v4-mini
│       │   │   │   │   │   │   │       └── index.ts
│       │   │   │   │   │   │   ├── v3
│       │   │   │   │   │   │   │   ├── errors.cjs
│       │   │   │   │   │   │   │   ├── errors.d.cts
│       │   │   │   │   │   │   │   ├── errors.d.ts
│       │   │   │   │   │   │   │   ├── errors.js
│       │   │   │   │   │   │   │   ├── external.cjs
│       │   │   │   │   │   │   │   ├── external.d.cts
│       │   │   │   │   │   │   │   ├── external.d.ts
│       │   │   │   │   │   │   │   ├── external.js
│       │   │   │   │   │   │   │   ├── helpers
│       │   │   │   │   │   │   │   │   ├── enumUtil.cjs
│       │   │   │   │   │   │   │   │   ├── enumUtil.d.cts
│       │   │   │   │   │   │   │   │   ├── enumUtil.d.ts
│       │   │   │   │   │   │   │   │   ├── enumUtil.js
│       │   │   │   │   │   │   │   │   ├── errorUtil.cjs
│       │   │   │   │   │   │   │   │   ├── errorUtil.d.cts
│       │   │   │   │   │   │   │   │   ├── errorUtil.d.ts
│       │   │   │   │   │   │   │   │   ├── errorUtil.js
│       │   │   │   │   │   │   │   │   ├── parseUtil.cjs
│       │   │   │   │   │   │   │   │   ├── parseUtil.d.cts
│       │   │   │   │   │   │   │   │   ├── parseUtil.d.ts
│       │   │   │   │   │   │   │   │   ├── parseUtil.js
│       │   │   │   │   │   │   │   │   ├── partialUtil.cjs
│       │   │   │   │   │   │   │   │   ├── partialUtil.d.cts
│       │   │   │   │   │   │   │   │   ├── partialUtil.d.ts
│       │   │   │   │   │   │   │   │   ├── partialUtil.js
│       │   │   │   │   │   │   │   │   ├── typeAliases.cjs
│       │   │   │   │   │   │   │   │   ├── typeAliases.d.cts
│       │   │   │   │   │   │   │   │   ├── typeAliases.d.ts
│       │   │   │   │   │   │   │   │   ├── typeAliases.js
│       │   │   │   │   │   │   │   │   ├── util.cjs
│       │   │   │   │   │   │   │   │   ├── util.d.cts
│       │   │   │   │   │   │   │   │   ├── util.d.ts
│       │   │   │   │   │   │   │   │   └── util.js
│       │   │   │   │   │   │   │   ├── index.cjs
│       │   │   │   │   │   │   │   ├── index.d.cts
│       │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   ├── locales
│       │   │   │   │   │   │   │   │   ├── en.cjs
│       │   │   │   │   │   │   │   │   ├── en.d.cts
│       │   │   │   │   │   │   │   │   ├── en.d.ts
│       │   │   │   │   │   │   │   │   └── en.js
│       │   │   │   │   │   │   │   ├── standard-schema.cjs
│       │   │   │   │   │   │   │   ├── standard-schema.d.cts
│       │   │   │   │   │   │   │   ├── standard-schema.d.ts
│       │   │   │   │   │   │   │   ├── standard-schema.js
│       │   │   │   │   │   │   │   ├── types.cjs
│       │   │   │   │   │   │   │   ├── types.d.cts
│       │   │   │   │   │   │   │   ├── types.d.ts
│       │   │   │   │   │   │   │   ├── types.js
│       │   │   │   │   │   │   │   ├── ZodError.cjs
│       │   │   │   │   │   │   │   ├── ZodError.d.cts
│       │   │   │   │   │   │   │   ├── ZodError.d.ts
│       │   │   │   │   │   │   │   └── ZodError.js
│       │   │   │   │   │   │   ├── v4
│       │   │   │   │   │   │   │   ├── classic
│       │   │   │   │   │   │   │   │   ├── checks.cjs
│       │   │   │   │   │   │   │   │   ├── checks.d.cts
│       │   │   │   │   │   │   │   │   ├── checks.d.ts
│       │   │   │   │   │   │   │   │   ├── checks.js
│       │   │   │   │   │   │   │   │   ├── coerce.cjs
│       │   │   │   │   │   │   │   │   ├── coerce.d.cts
│       │   │   │   │   │   │   │   │   ├── coerce.d.ts
│       │   │   │   │   │   │   │   │   ├── coerce.js
│       │   │   │   │   │   │   │   │   ├── compat.cjs
│       │   │   │   │   │   │   │   │   ├── compat.d.cts
│       │   │   │   │   │   │   │   │   ├── compat.d.ts
│       │   │   │   │   │   │   │   │   ├── compat.js
│       │   │   │   │   │   │   │   │   ├── errors.cjs
│       │   │   │   │   │   │   │   │   ├── errors.d.cts
│       │   │   │   │   │   │   │   │   ├── errors.d.ts
│       │   │   │   │   │   │   │   │   ├── errors.js
│       │   │   │   │   │   │   │   │   ├── external.cjs
│       │   │   │   │   │   │   │   │   ├── external.d.cts
│       │   │   │   │   │   │   │   │   ├── external.d.ts
│       │   │   │   │   │   │   │   │   ├── external.js
│       │   │   │   │   │   │   │   │   ├── index.cjs
│       │   │   │   │   │   │   │   │   ├── index.d.cts
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── iso.cjs
│       │   │   │   │   │   │   │   │   ├── iso.d.cts
│       │   │   │   │   │   │   │   │   ├── iso.d.ts
│       │   │   │   │   │   │   │   │   ├── iso.js
│       │   │   │   │   │   │   │   │   ├── parse.cjs
│       │   │   │   │   │   │   │   │   ├── parse.d.cts
│       │   │   │   │   │   │   │   │   ├── parse.d.ts
│       │   │   │   │   │   │   │   │   ├── parse.js
│       │   │   │   │   │   │   │   │   ├── schemas.cjs
│       │   │   │   │   │   │   │   │   ├── schemas.d.cts
│       │   │   │   │   │   │   │   │   ├── schemas.d.ts
│       │   │   │   │   │   │   │   │   └── schemas.js
│       │   │   │   │   │   │   │   ├── core
│       │   │   │   │   │   │   │   │   ├── api.cjs
│       │   │   │   │   │   │   │   │   ├── api.d.cts
│       │   │   │   │   │   │   │   │   ├── api.d.ts
│       │   │   │   │   │   │   │   │   ├── api.js
│       │   │   │   │   │   │   │   │   ├── checks.cjs
│       │   │   │   │   │   │   │   │   ├── checks.d.cts
│       │   │   │   │   │   │   │   │   ├── checks.d.ts
│       │   │   │   │   │   │   │   │   ├── checks.js
│       │   │   │   │   │   │   │   │   ├── core.cjs
│       │   │   │   │   │   │   │   │   ├── core.d.cts
│       │   │   │   │   │   │   │   │   ├── core.d.ts
│       │   │   │   │   │   │   │   │   ├── core.js
│       │   │   │   │   │   │   │   │   ├── doc.cjs
│       │   │   │   │   │   │   │   │   ├── doc.d.cts
│       │   │   │   │   │   │   │   │   ├── doc.d.ts
│       │   │   │   │   │   │   │   │   ├── doc.js
│       │   │   │   │   │   │   │   │   ├── errors.cjs
│       │   │   │   │   │   │   │   │   ├── errors.d.cts
│       │   │   │   │   │   │   │   │   ├── errors.d.ts
│       │   │   │   │   │   │   │   │   ├── errors.js
│       │   │   │   │   │   │   │   │   ├── function.cjs
│       │   │   │   │   │   │   │   │   ├── function.d.cts
│       │   │   │   │   │   │   │   │   ├── function.d.ts
│       │   │   │   │   │   │   │   │   ├── function.js
│       │   │   │   │   │   │   │   │   ├── index.cjs
│       │   │   │   │   │   │   │   │   ├── index.d.cts
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── json-schema.cjs
│       │   │   │   │   │   │   │   │   ├── json-schema.d.cts
│       │   │   │   │   │   │   │   │   ├── json-schema.d.ts
│       │   │   │   │   │   │   │   │   ├── json-schema.js
│       │   │   │   │   │   │   │   │   ├── parse.cjs
│       │   │   │   │   │   │   │   │   ├── parse.d.cts
│       │   │   │   │   │   │   │   │   ├── parse.d.ts
│       │   │   │   │   │   │   │   │   ├── parse.js
│       │   │   │   │   │   │   │   │   ├── regexes.cjs
│       │   │   │   │   │   │   │   │   ├── regexes.d.cts
│       │   │   │   │   │   │   │   │   ├── regexes.d.ts
│       │   │   │   │   │   │   │   │   ├── regexes.js
│       │   │   │   │   │   │   │   │   ├── registries.cjs
│       │   │   │   │   │   │   │   │   ├── registries.d.cts
│       │   │   │   │   │   │   │   │   ├── registries.d.ts
│       │   │   │   │   │   │   │   │   ├── registries.js
│       │   │   │   │   │   │   │   │   ├── schemas.cjs
│       │   │   │   │   │   │   │   │   ├── schemas.d.cts
│       │   │   │   │   │   │   │   │   ├── schemas.d.ts
│       │   │   │   │   │   │   │   │   ├── schemas.js
│       │   │   │   │   │   │   │   │   ├── standard-schema.cjs
│       │   │   │   │   │   │   │   │   ├── standard-schema.d.cts
│       │   │   │   │   │   │   │   │   ├── standard-schema.d.ts
│       │   │   │   │   │   │   │   │   ├── standard-schema.js
│       │   │   │   │   │   │   │   │   ├── to-json-schema.cjs
│       │   │   │   │   │   │   │   │   ├── to-json-schema.d.cts
│       │   │   │   │   │   │   │   │   ├── to-json-schema.d.ts
│       │   │   │   │   │   │   │   │   ├── to-json-schema.js
│       │   │   │   │   │   │   │   │   ├── util.cjs
│       │   │   │   │   │   │   │   │   ├── util.d.cts
│       │   │   │   │   │   │   │   │   ├── util.d.ts
│       │   │   │   │   │   │   │   │   ├── util.js
│       │   │   │   │   │   │   │   │   ├── versions.cjs
│       │   │   │   │   │   │   │   │   ├── versions.d.cts
│       │   │   │   │   │   │   │   │   ├── versions.d.ts
│       │   │   │   │   │   │   │   │   └── versions.js
│       │   │   │   │   │   │   │   ├── index.cjs
│       │   │   │   │   │   │   │   ├── index.d.cts
│       │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   ├── locales
│       │   │   │   │   │   │   │   │   ├── ar.cjs
│       │   │   │   │   │   │   │   │   ├── ar.d.cts
│       │   │   │   │   │   │   │   │   ├── ar.d.ts
│       │   │   │   │   │   │   │   │   ├── ar.js
│       │   │   │   │   │   │   │   │   ├── az.cjs
│       │   │   │   │   │   │   │   │   ├── az.d.cts
│       │   │   │   │   │   │   │   │   ├── az.d.ts
│       │   │   │   │   │   │   │   │   ├── az.js
│       │   │   │   │   │   │   │   │   ├── be.cjs
│       │   │   │   │   │   │   │   │   ├── be.d.cts
│       │   │   │   │   │   │   │   │   ├── be.d.ts
│       │   │   │   │   │   │   │   │   ├── be.js
│       │   │   │   │   │   │   │   │   ├── ca.cjs
│       │   │   │   │   │   │   │   │   ├── ca.d.cts
│       │   │   │   │   │   │   │   │   ├── ca.d.ts
│       │   │   │   │   │   │   │   │   ├── ca.js
│       │   │   │   │   │   │   │   │   ├── cs.cjs
│       │   │   │   │   │   │   │   │   ├── cs.d.cts
│       │   │   │   │   │   │   │   │   ├── cs.d.ts
│       │   │   │   │   │   │   │   │   ├── cs.js
│       │   │   │   │   │   │   │   │   ├── de.cjs
│       │   │   │   │   │   │   │   │   ├── de.d.cts
│       │   │   │   │   │   │   │   │   ├── de.d.ts
│       │   │   │   │   │   │   │   │   ├── de.js
│       │   │   │   │   │   │   │   │   ├── en.cjs
│       │   │   │   │   │   │   │   │   ├── en.d.cts
│       │   │   │   │   │   │   │   │   ├── en.d.ts
│       │   │   │   │   │   │   │   │   ├── en.js
│       │   │   │   │   │   │   │   │   ├── eo.cjs
│       │   │   │   │   │   │   │   │   ├── eo.d.cts
│       │   │   │   │   │   │   │   │   ├── eo.d.ts
│       │   │   │   │   │   │   │   │   ├── eo.js
│       │   │   │   │   │   │   │   │   ├── es.cjs
│       │   │   │   │   │   │   │   │   ├── es.d.cts
│       │   │   │   │   │   │   │   │   ├── es.d.ts
│       │   │   │   │   │   │   │   │   ├── es.js
│       │   │   │   │   │   │   │   │   ├── fa.cjs
│       │   │   │   │   │   │   │   │   ├── fa.d.cts
│       │   │   │   │   │   │   │   │   ├── fa.d.ts
│       │   │   │   │   │   │   │   │   ├── fa.js
│       │   │   │   │   │   │   │   │   ├── fi.cjs
│       │   │   │   │   │   │   │   │   ├── fi.d.cts
│       │   │   │   │   │   │   │   │   ├── fi.d.ts
│       │   │   │   │   │   │   │   │   ├── fi.js
│       │   │   │   │   │   │   │   │   ├── fr-CA.cjs
│       │   │   │   │   │   │   │   │   ├── fr-CA.d.cts
│       │   │   │   │   │   │   │   │   ├── fr-CA.d.ts
│       │   │   │   │   │   │   │   │   ├── fr-CA.js
│       │   │   │   │   │   │   │   │   ├── fr.cjs
│       │   │   │   │   │   │   │   │   ├── fr.d.cts
│       │   │   │   │   │   │   │   │   ├── fr.d.ts
│       │   │   │   │   │   │   │   │   ├── fr.js
│       │   │   │   │   │   │   │   │   ├── he.cjs
│       │   │   │   │   │   │   │   │   ├── he.d.cts
│       │   │   │   │   │   │   │   │   ├── he.d.ts
│       │   │   │   │   │   │   │   │   ├── he.js
│       │   │   │   │   │   │   │   │   ├── hu.cjs
│       │   │   │   │   │   │   │   │   ├── hu.d.cts
│       │   │   │   │   │   │   │   │   ├── hu.d.ts
│       │   │   │   │   │   │   │   │   ├── hu.js
│       │   │   │   │   │   │   │   │   ├── id.cjs
│       │   │   │   │   │   │   │   │   ├── id.d.cts
│       │   │   │   │   │   │   │   │   ├── id.d.ts
│       │   │   │   │   │   │   │   │   ├── id.js
│       │   │   │   │   │   │   │   │   ├── index.cjs
│       │   │   │   │   │   │   │   │   ├── index.d.cts
│       │   │   │   │   │   │   │   │   ├── index.d.ts
│       │   │   │   │   │   │   │   │   ├── index.js
│       │   │   │   │   │   │   │   │   ├── it.cjs
│       │   │   │   │   │   │   │   │   ├── it.d.cts
│       │   │   │   │   │   │   │   │   ├── it.d.ts
│       │   │   │   │   │   │   │   │   ├── it.js
│       │   │   │   │   │   │   │   │   ├── ja.cjs
│       │   │   │   │   │   │   │   │   ├── ja.d.cts
│       │   │   │   │   │   │   │   │   ├── ja.d.ts
│       │   │   │   │   │   │   │   │   ├── ja.js
│       │   │   │   │   │   │   │   │   ├── kh.cjs
│       │   │   │   │   │   │   │   │   ├── kh.d.cts
│       │   │   │   │   │   │   │   │   ├── kh.d.ts
│       │   │   │   │   │   │   │   │   ├── kh.js
│       │   │   │   │   │   │   │   │   ├── ko.cjs
│       │   │   │   │   │   │   │   │   ├── ko.d.cts
│       │   │   │   │   │   │   │   │   ├── ko.d.ts
│       │   │   │   │   │   │   │   │   ├── ko.js
│       │   │   │   │   │   │   │   │   ├── mk.cjs
│       │   │   │   │   │   │   │   │   ├── mk.d.cts
│       │   │   │   │   │   │   │   │   ├── mk.d.ts
│       │   │   │   │   │   │   │   │   ├── mk.js
│       │   │   │   │   │   │   │   │   ├── ms.cjs
│       │   │   │   │   │   │   │   │   ├── ms.d.cts
│       │   │   │   │   │   │   │   │   ├── ms.d.ts
│       │   │   │   │   │   │   │   │   ├── ms.js
│       │   │   │   │   │   │   │   │   ├── nl.cjs
│       │   │   │   │   │   │   │   │   ├── nl.d.cts
│       │   │   │   │   │   │   │   │   ├── nl.d.ts
│       │   │   │   │   │   │   │   │   ├── nl.js
│       │   │   │   │   │   │   │   │   ├── no.cjs
│       │   │   │   │   │   │   │   │   ├── no.d.cts
│       │   │   │   │   │   │   │   │   ├── no.d.ts
│       │   │   │   │   │   │   │   │   ├── no.js
│       │   │   │   │   │   │   │   │   ├── ota.cjs
│       │   │   │   │   │   │   │   │   ├── ota.d.cts
│       │   │   │   │   │   │   │   │   ├── ota.d.ts
│       │   │   │   │   │   │   │   │   ├── ota.js
│       │   │   │   │   │   │   │   │   ├── pl.cjs
│       │   │   │   │   │   │   │   │   ├── pl.d.cts
│       │   │   │   │   │   │   │   │   ├── pl.d.ts
│       │   │   │   │   │   │   │   │   ├── pl.js
│       │   │   │   │   │   │   │   │   ├── ps.cjs
│       │   │   │   │   │   │   │   │   ├── ps.d.cts
│       │   │   │   │   │   │   │   │   ├── ps.d.ts
│       │   │   │   │   │   │   │   │   ├── ps.js
│       │   │   │   │   │   │   │   │   ├── pt.cjs
│       │   │   │   │   │   │   │   │   ├── pt.d.cts
│       │   │   │   │   │   │   │   │   ├── pt.d.ts
│       │   │   │   │   │   │   │   │   ├── pt.js
│       │   │   │   │   │   │   │   │   ├── ru.cjs
│       │   │   │   │   │   │   │   │   ├── ru.d.cts
│       │   │   │   │   │   │   │   │   ├── ru.d.ts
│       │   │   │   │   │   │   │   │   ├── ru.js
│       │   │   │   │   │   │   │   │   ├── sl.cjs
│       │   │   │   │   │   │   │   │   ├── sl.d.cts
│       │   │   │   │   │   │   │   │   ├── sl.d.ts
│       │   │   │   │   │   │   │   │   ├── sl.js
│       │   │   │   │   │   │   │   │   ├── sv.cjs
│       │   │   │   │   │   │   │   │   ├── sv.d.cts
│       │   │   │   │   │   │   │   │   ├── sv.d.ts
│       │   │   │   │   │   │   │   │   ├── sv.js
│       │   │   │   │   │   │   │   │   ├── ta.cjs
│       │   │   │   │   │   │   │   │   ├── ta.d.cts
│       │   │   │   │   │   │   │   │   ├── ta.d.ts
│       │   │   │   │   │   │   │   │   ├── ta.js
│       │   │   │   │   │   │   │   │   ├── th.cjs
│       │   │   │   │   │   │   │   │   ├── th.d.cts
│       │   │   │   │   │   │   │   │   ├── th.d.ts
│       │   │   │   │   │   │   │   │   ├── th.js
│       │   │   │   │   │   │   │   │   ├── tr.cjs
│       │   │   │   │   │   │   │   │   ├── tr.d.cts
│       │   │   │   │   │   │   │   │   ├── tr.d.ts
│       │   │   │   │   │   │   │   │   ├── tr.js
│       │   │   │   │   │   │   │   │   ├── ua.cjs
│       │   │   │   │   │   │   │   │   ├── ua.d.cts
│       │   │   │   │   │   │   │   │   ├── ua.d.ts
│       │   │   │   │   │   │   │   │   ├── ua.js
│       │   │   │   │   │   │   │   │   ├── ur.cjs
│       │   │   │   │   │   │   │   │   ├── ur.d.cts
│       │   │   │   │   │   │   │   │   ├── ur.d.ts
│       │   │   │   │   │   │   │   │   ├── ur.js
│       │   │   │   │   │   │   │   │   ├── vi.cjs
│       │   │   │   │   │   │   │   │   ├── vi.d.cts
│       │   │   │   │   │   │   │   │   ├── vi.d.ts
│       │   │   │   │   │   │   │   │   ├── vi.js
│       │   │   │   │   │   │   │   │   ├── zh-CN.cjs
│       │   │   │   │   │   │   │   │   ├── zh-CN.d.cts
│       │   │   │   │   │   │   │   │   ├── zh-CN.d.ts
│       │   │   │   │   │   │   │   │   ├── zh-CN.js
│       │   │   │   │   │   │   │   │   ├── zh-TW.cjs
│       │   │   │   │   │   │   │   │   ├── zh-TW.d.cts
│       │   │   │   │   │   │   │   │   ├── zh-TW.d.ts
│       │   │   │   │   │   │   │   │   └── zh-TW.js
│       │   │   │   │   │   │   │   └── mini
│       │   │   │   │   │   │   │       ├── checks.cjs
│       │   │   │   │   │   │   │       ├── checks.d.cts
│       │   │   │   │   │   │   │       ├── checks.d.ts
│       │   │   │   │   │   │   │       ├── checks.js
│       │   │   │   │   │   │   │       ├── coerce.cjs
│       │   │   │   │   │   │   │       ├── coerce.d.cts
│       │   │   │   │   │   │   │       ├── coerce.d.ts
│       │   │   │   │   │   │   │       ├── coerce.js
│       │   │   │   │   │   │   │       ├── external.cjs
│       │   │   │   │   │   │   │       ├── external.d.cts
│       │   │   │   │   │   │   │       ├── external.d.ts
│       │   │   │   │   │   │   │       ├── external.js
│       │   │   │   │   │   │   │       ├── index.cjs
│       │   │   │   │   │   │   │       ├── index.d.cts
│       │   │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │   │       ├── index.js
│       │   │   │   │   │   │   │       ├── iso.cjs
│       │   │   │   │   │   │   │       ├── iso.d.cts
│       │   │   │   │   │   │   │       ├── iso.d.ts
│       │   │   │   │   │   │   │       ├── iso.js
│       │   │   │   │   │   │   │       ├── parse.cjs
│       │   │   │   │   │   │   │       ├── parse.d.cts
│       │   │   │   │   │   │   │       ├── parse.d.ts
│       │   │   │   │   │   │   │       ├── parse.js
│       │   │   │   │   │   │   │       ├── schemas.cjs
│       │   │   │   │   │   │   │       ├── schemas.d.cts
│       │   │   │   │   │   │   │       ├── schemas.d.ts
│       │   │   │   │   │   │   │       └── schemas.js
│       │   │   │   │   │   │   └── v4-mini
│       │   │   │   │   │   │       ├── index.cjs
│       │   │   │   │   │   │       ├── index.d.cts
│       │   │   │   │   │   │       ├── index.d.ts
│       │   │   │   │   │   │       └── index.js
│       │   │   │   │   │   └── zod-to-json-schema
│       │   │   │   │   │       ├── changelog.md
│       │   │   │   │   │       ├── contributing.md
│       │   │   │   │   │       ├── createIndex.ts
│       │   │   │   │   │       ├── dist
│       │   │   │   │   │       │   ├── cjs
│       │   │   │   │   │       │   │   ├── errorMessages.js
│       │   │   │   │   │       │   │   ├── getRelativePath.js
│       │   │   │   │   │       │   │   ├── index.js
│       │   │   │   │   │       │   │   ├── Options.js
│       │   │   │   │   │       │   │   ├── package.json
│       │   │   │   │   │       │   │   ├── parseDef.js
│       │   │   │   │   │       │   │   ├── parsers
│       │   │   │   │   │       │   │   │   ├── any.js
│       │   │   │   │   │       │   │   │   ├── array.js
│       │   │   │   │   │       │   │   │   ├── bigint.js
│       │   │   │   │   │       │   │   │   ├── boolean.js
│       │   │   │   │   │       │   │   │   ├── branded.js
│       │   │   │   │   │       │   │   │   ├── catch.js
│       │   │   │   │   │       │   │   │   ├── date.js
│       │   │   │   │   │       │   │   │   ├── default.js
│       │   │   │   │   │       │   │   │   ├── effects.js
│       │   │   │   │   │       │   │   │   ├── enum.js
│       │   │   │   │   │       │   │   │   ├── intersection.js
│       │   │   │   │   │       │   │   │   ├── literal.js
│       │   │   │   │   │       │   │   │   ├── map.js
│       │   │   │   │   │       │   │   │   ├── nativeEnum.js
│       │   │   │   │   │       │   │   │   ├── never.js
│       │   │   │   │   │       │   │   │   ├── nullable.js
│       │   │   │   │   │       │   │   │   ├── null.js
│       │   │   │   │   │       │   │   │   ├── number.js
│       │   │   │   │   │       │   │   │   ├── object.js
│       │   │   │   │   │       │   │   │   ├── optional.js
│       │   │   │   │   │       │   │   │   ├── pipeline.js
│       │   │   │   │   │       │   │   │   ├── promise.js
│       │   │   │   │   │       │   │   │   ├── readonly.js
│       │   │   │   │   │       │   │   │   ├── record.js
│       │   │   │   │   │       │   │   │   ├── set.js
│       │   │   │   │   │       │   │   │   ├── string.js
│       │   │   │   │   │       │   │   │   ├── tuple.js
│       │   │   │   │   │       │   │   │   ├── undefined.js
│       │   │   │   │   │       │   │   │   ├── union.js
│       │   │   │   │   │       │   │   │   └── unknown.js
│       │   │   │   │   │       │   │   ├── parseTypes.js
│       │   │   │   │   │       │   │   ├── Refs.js
│       │   │   │   │   │       │   │   ├── selectParser.js
│       │   │   │   │   │       │   │   └── zodToJsonSchema.js
│       │   │   │   │   │       │   ├── esm
│       │   │   │   │   │       │   │   ├── errorMessages.js
│       │   │   │   │   │       │   │   ├── getRelativePath.js
│       │   │   │   │   │       │   │   ├── index.js
│       │   │   │   │   │       │   │   ├── Options.js
│       │   │   │   │   │       │   │   ├── package.json
│       │   │   │   │   │       │   │   ├── parseDef.js
│       │   │   │   │   │       │   │   ├── parsers
│       │   │   │   │   │       │   │   │   ├── any.js
│       │   │   │   │   │       │   │   │   ├── array.js
│       │   │   │   │   │       │   │   │   ├── bigint.js
│       │   │   │   │   │       │   │   │   ├── boolean.js
│       │   │   │   │   │       │   │   │   ├── branded.js
│       │   │   │   │   │       │   │   │   ├── catch.js
│       │   │   │   │   │       │   │   │   ├── date.js
│       │   │   │   │   │       │   │   │   ├── default.js
│       │   │   │   │   │       │   │   │   ├── effects.js
│       │   │   │   │   │       │   │   │   ├── enum.js
│       │   │   │   │   │       │   │   │   ├── intersection.js
│       │   │   │   │   │       │   │   │   ├── literal.js
│       │   │   │   │   │       │   │   │   ├── map.js
│       │   │   │   │   │       │   │   │   ├── nativeEnum.js
│       │   │   │   │   │       │   │   │   ├── never.js
│       │   │   │   │   │       │   │   │   ├── nullable.js
│       │   │   │   │   │       │   │   │   ├── null.js
│       │   │   │   │   │       │   │   │   ├── number.js
│       │   │   │   │   │       │   │   │   ├── object.js
│       │   │   │   │   │       │   │   │   ├── optional.js
│       │   │   │   │   │       │   │   │   ├── pipeline.js
│       │   │   │   │   │       │   │   │   ├── promise.js
│       │   │   │   │   │       │   │   │   ├── readonly.js
│       │   │   │   │   │       │   │   │   ├── record.js
│       │   │   │   │   │       │   │   │   ├── set.js
│       │   │   │   │   │       │   │   │   ├── string.js
│       │   │   │   │   │       │   │   │   ├── tuple.js
│       │   │   │   │   │       │   │   │   ├── undefined.js
│       │   │   │   │   │       │   │   │   ├── union.js
│       │   │   │   │   │       │   │   │   └── unknown.js
│       │   │   │   │   │       │   │   ├── parseTypes.js
│       │   │   │   │   │       │   │   ├── Refs.js
│       │   │   │   │   │       │   │   ├── selectParser.js
│       │   │   │   │   │       │   │   └── zodToJsonSchema.js
│       │   │   │   │   │       │   └── types
│       │   │   │   │   │       │       ├── errorMessages.d.ts
│       │   │   │   │   │       │       ├── getRelativePath.d.ts
│       │   │   │   │   │       │       ├── index.d.ts
│       │   │   │   │   │       │       ├── Options.d.ts
│       │   │   │   │   │       │       ├── parseDef.d.ts
│       │   │   │   │   │       │       ├── parsers
│       │   │   │   │   │       │       │   ├── any.d.ts
│       │   │   │   │   │       │       │   ├── array.d.ts
│       │   │   │   │   │       │       │   ├── bigint.d.ts
│       │   │   │   │   │       │       │   ├── boolean.d.ts
│       │   │   │   │   │       │       │   ├── branded.d.ts
│       │   │   │   │   │       │       │   ├── catch.d.ts
│       │   │   │   │   │       │       │   ├── date.d.ts
│       │   │   │   │   │       │       │   ├── default.d.ts
│       │   │   │   │   │       │       │   ├── effects.d.ts
│       │   │   │   │   │       │       │   ├── enum.d.ts
│       │   │   │   │   │       │       │   ├── intersection.d.ts
│       │   │   │   │   │       │       │   ├── literal.d.ts
│       │   │   │   │   │       │       │   ├── map.d.ts
│       │   │   │   │   │       │       │   ├── nativeEnum.d.ts
│       │   │   │   │   │       │       │   ├── never.d.ts
│       │   │   │   │   │       │       │   ├── nullable.d.ts
│       │   │   │   │   │       │       │   ├── null.d.ts
│       │   │   │   │   │       │       │   ├── number.d.ts
│       │   │   │   │   │       │       │   ├── object.d.ts
│       │   │   │   │   │       │       │   ├── optional.d.ts
│       │   │   │   │   │       │       │   ├── pipeline.d.ts
│       │   │   │   │   │       │       │   ├── promise.d.ts
│       │   │   │   │   │       │       │   ├── readonly.d.ts
│       │   │   │   │   │       │       │   ├── record.d.ts
│       │   │   │   │   │       │       │   ├── set.d.ts
│       │   │   │   │   │       │       │   ├── string.d.ts
│       │   │   │   │   │       │       │   ├── tuple.d.ts
│       │   │   │   │   │       │       │   ├── undefined.d.ts
│       │   │   │   │   │       │       │   ├── union.d.ts
│       │   │   │   │   │       │       │   └── unknown.d.ts
│       │   │   │   │   │       │       ├── parseTypes.d.ts
│       │   │   │   │   │       │       ├── Refs.d.ts
│       │   │   │   │   │       │       ├── selectParser.d.ts
│       │   │   │   │   │       │       └── zodToJsonSchema.d.ts
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── package.json
│       │   │   │   │   │       ├── postcjs.ts
│       │   │   │   │   │       ├── postesm.ts
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       └── SECURITY.md
│       │   │   │   │   ├── package.json
│       │   │   │   │   └── package-lock.json
│       │   │   │   ├── github-mcp-server
│       │   │   │   │   ├── cmd
│       │   │   │   │   │   ├── github-mcp-server
│       │   │   │   │   │   │   ├── generate_docs.go
│       │   │   │   │   │   │   └── main.go
│       │   │   │   │   │   └── mcpcurl
│       │   │   │   │   │       ├── main.go
│       │   │   │   │   │       └── README.md
│       │   │   │   │   ├── CODE_OF_CONDUCT.md
│       │   │   │   │   ├── CONTRIBUTING.md
│       │   │   │   │   ├── Dockerfile
│       │   │   │   │   ├── docs
│       │   │   │   │   │   ├── error-handling.md
│       │   │   │   │   │   ├── host-integration.md
│       │   │   │   │   │   ├── remote-server.md
│       │   │   │   │   │   └── testing.md
│       │   │   │   │   ├── e2e
│       │   │   │   │   │   ├── e2e_test.go
│       │   │   │   │   │   └── README.md
│       │   │   │   │   ├── github-mcp-server
│       │   │   │   │   ├── go.mod
│       │   │   │   │   ├── go.sum
│       │   │   │   │   ├── internal
│       │   │   │   │   │   ├── ghmcp
│       │   │   │   │   │   │   └── server.go
│       │   │   │   │   │   ├── githubv4mock
│       │   │   │   │   │   │   ├── githubv4mock.go
│       │   │   │   │   │   │   ├── local_round_tripper.go
│       │   │   │   │   │   │   ├── objects_are_equal_values.go
│       │   │   │   │   │   │   ├── objects_are_equal_values_test.go
│       │   │   │   │   │   │   └── query.go
│       │   │   │   │   │   └── toolsnaps
│       │   │   │   │   │       ├── toolsnaps.go
│       │   │   │   │   │       └── toolsnaps_test.go
│       │   │   │   │   ├── LICENSE
│       │   │   │   │   ├── pkg
│       │   │   │   │   │   ├── errors
│       │   │   │   │   │   │   ├── error.go
│       │   │   │   │   │   │   └── error_test.go
│       │   │   │   │   │   ├── github
│       │   │   │   │   │   │   ├── actions.go
│       │   │   │   │   │   │   ├── actions_test.go
│       │   │   │   │   │   │   ├── code_scanning.go
│       │   │   │   │   │   │   ├── code_scanning_test.go
│       │   │   │   │   │   │   ├── context_tools.go
│       │   │   │   │   │   │   ├── context_tools_test.go
│       │   │   │   │   │   │   ├── dependabot.go
│       │   │   │   │   │   │   ├── dependabot_test.go
│       │   │   │   │   │   │   ├── discussions.go
│       │   │   │   │   │   │   ├── discussions_test.go
│       │   │   │   │   │   │   ├── dynamic_tools.go
│       │   │   │   │   │   │   ├── helper_test.go
│       │   │   │   │   │   │   ├── issues.go
│       │   │   │   │   │   │   ├── issues_test.go
│       │   │   │   │   │   │   ├── notifications.go
│       │   │   │   │   │   │   ├── notifications_test.go
│       │   │   │   │   │   │   ├── pullrequests.go
│       │   │   │   │   │   │   ├── pullrequests_test.go
│       │   │   │   │   │   │   ├── repositories.go
│       │   │   │   │   │   │   ├── repositories_test.go
│       │   │   │   │   │   │   ├── repository_resource.go
│       │   │   │   │   │   │   ├── repository_resource_test.go
│       │   │   │   │   │   │   ├── search.go
│       │   │   │   │   │   │   ├── search_test.go
│       │   │   │   │   │   │   ├── search_utils.go
│       │   │   │   │   │   │   ├── secret_scanning.go
│       │   │   │   │   │   │   ├── secret_scanning_test.go
│       │   │   │   │   │   │   ├── server.go
│       │   │   │   │   │   │   ├── server_test.go
│       │   │   │   │   │   │   ├── tools.go
│       │   │   │   │   │   │   └── __toolsnaps__
│       │   │   │   │   │   │       ├── add_issue_comment.snap
│       │   │   │   │   │   │       ├── add_pull_request_review_comment_to_pending_review.snap
│       │   │   │   │   │   │       ├── assign_copilot_to_issue.snap
│       │   │   │   │   │   │       ├── create_and_submit_pull_request_review.snap
│       │   │   │   │   │   │       ├── create_branch.snap
│       │   │   │   │   │   │       ├── create_issue.snap
│       │   │   │   │   │   │       ├── create_or_update_file.snap
│       │   │   │   │   │   │       ├── create_pending_pull_request_review.snap
│       │   │   │   │   │   │       ├── create_pull_request.snap
│       │   │   │   │   │   │       ├── create_repository.snap
│       │   │   │   │   │   │       ├── delete_file.snap
│       │   │   │   │   │   │       ├── delete_pending_pull_request_review.snap
│       │   │   │   │   │   │       ├── dismiss_notification.snap
│       │   │   │   │   │   │       ├── fork_repository.snap
│       │   │   │   │   │   │       ├── get_code_scanning_alert.snap
│       │   │   │   │   │   │       ├── get_commit.snap
│       │   │   │   │   │   │       ├── get_dependabot_alert.snap
│       │   │   │   │   │   │       ├── get_file_contents.snap
│       │   │   │   │   │   │       ├── get_issue_comments.snap
│       │   │   │   │   │   │       ├── get_issue.snap
│       │   │   │   │   │   │       ├── get_me.snap
│       │   │   │   │   │   │       ├── get_notification_details.snap
│       │   │   │   │   │   │       ├── get_pull_request_comments.snap
│       │   │   │   │   │   │       ├── get_pull_request_diff.snap
│       │   │   │   │   │   │       ├── get_pull_request_files.snap
│       │   │   │   │   │   │       ├── get_pull_request_reviews.snap
│       │   │   │   │   │   │       ├── get_pull_request.snap
│       │   │   │   │   │   │       ├── get_pull_request_status.snap
│       │   │   │   │   │   │       ├── get_tag.snap
│       │   │   │   │   │   │       ├── list_branches.snap
│       │   │   │   │   │   │       ├── list_code_scanning_alerts.snap
│       │   │   │   │   │   │       ├── list_commits.snap
│       │   │   │   │   │   │       ├── list_dependabot_alerts.snap
│       │   │   │   │   │   │       ├── list_issues.snap
│       │   │   │   │   │   │       ├── list_notifications.snap
│       │   │   │   │   │   │       ├── list_pull_requests.snap
│       │   │   │   │   │   │       ├── list_tags.snap
│       │   │   │   │   │   │       ├── manage_notification_subscription.snap
│       │   │   │   │   │   │       ├── manage_repository_notification_subscription.snap
│       │   │   │   │   │   │       ├── mark_all_notifications_read.snap
│       │   │   │   │   │   │       ├── merge_pull_request.snap
│       │   │   │   │   │   │       ├── push_files.snap
│       │   │   │   │   │   │       ├── request_copilot_review.snap
│       │   │   │   │   │   │       ├── search_code.snap
│       │   │   │   │   │   │       ├── search_issues.snap
│       │   │   │   │   │   │       ├── search_pull_requests.snap
│       │   │   │   │   │   │       ├── search_repositories.snap
│       │   │   │   │   │   │       ├── search_users.snap
│       │   │   │   │   │   │       ├── submit_pending_pull_request_review.snap
│       │   │   │   │   │   │       ├── update_issue.snap
│       │   │   │   │   │   │       ├── update_pull_request_branch.snap
│       │   │   │   │   │   │       └── update_pull_request.snap
│       │   │   │   │   │   ├── log
│       │   │   │   │   │   │   ├── io.go
│       │   │   │   │   │   │   └── io_test.go
│       │   │   │   │   │   ├── raw
│       │   │   │   │   │   │   ├── raw.go
│       │   │   │   │   │   │   ├── raw_mock.go
│       │   │   │   │   │   │   └── raw_test.go
│       │   │   │   │   │   ├── toolsets
│       │   │   │   │   │   │   ├── toolsets.go
│       │   │   │   │   │   │   └── toolsets_test.go
│       │   │   │   │   │   └── translations
│       │   │   │   │   │       └── translations.go
│       │   │   │   │   ├── README.md
│       │   │   │   │   ├── script
│       │   │   │   │   │   ├── generate-docs
│       │   │   │   │   │   ├── get-discussions
│       │   │   │   │   │   ├── get-me
│       │   │   │   │   │   ├── licenses
│       │   │   │   │   │   ├── licenses-check
│       │   │   │   │   │   ├── lint
│       │   │   │   │   │   ├── prettyprint-log
│       │   │   │   │   │   ├── tag-release
│       │   │   │   │   │   └── test
│       │   │   │   │   ├── SECURITY.md
│       │   │   │   │   ├── SUPPORT.md
│       │   │   │   │   ├── third-party
│       │   │   │   │   │   ├── github.com
│       │   │   │   │   │   │   ├── fsnotify
│       │   │   │   │   │   │   │   └── fsnotify
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── github
│       │   │   │   │   │   │   │   └── github-mcp-server
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── google
│       │   │   │   │   │   │   │   ├── go-github
│       │   │   │   │   │   │   │   │   ├── v71
│       │   │   │   │   │   │   │   │   │   └── github
│       │   │   │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   │   │   └── v72
│       │   │   │   │   │   │   │   │       └── github
│       │   │   │   │   │   │   │   │           └── LICENSE
│       │   │   │   │   │   │   │   ├── go-querystring
│       │   │   │   │   │   │   │   │   └── query
│       │   │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   │   └── uuid
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── go-openapi
│       │   │   │   │   │   │   │   ├── jsonpointer
│       │   │   │   │   │   │   │   │   └── LICENSE
│       │   │   │   │   │   │   │   └── swag
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── gorilla
│       │   │   │   │   │   │   │   └── mux
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── go-viper
│       │   │   │   │   │   │   │   └── mapstructure
│       │   │   │   │   │   │   │       └── v2
│       │   │   │   │   │   │   │           └── LICENSE
│       │   │   │   │   │   │   ├── inconshreveable
│       │   │   │   │   │   │   │   └── mousetrap
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── josephburnett
│       │   │   │   │   │   │   │   └── jd
│       │   │   │   │   │   │   │       └── v2
│       │   │   │   │   │   │   │           └── LICENSE
│       │   │   │   │   │   │   ├── josharian
│       │   │   │   │   │   │   │   └── intern
│       │   │   │   │   │   │   │       └── license.md
│       │   │   │   │   │   │   ├── mailru
│       │   │   │   │   │   │   │   └── easyjson
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── mark3labs
│       │   │   │   │   │   │   │   └── mcp-go
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── migueleliasweb
│       │   │   │   │   │   │   │   └── go-github-mock
│       │   │   │   │   │   │   │       └── src
│       │   │   │   │   │   │   │           └── mock
│       │   │   │   │   │   │   │               └── LICENSE
│       │   │   │   │   │   │   ├── pelletier
│       │   │   │   │   │   │   │   └── go-toml
│       │   │   │   │   │   │   │       └── v2
│       │   │   │   │   │   │   │           └── LICENSE
│       │   │   │   │   │   │   ├── sagikazarmark
│       │   │   │   │   │   │   │   └── locafero
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── shurcooL
│       │   │   │   │   │   │   │   ├── githubv4
│       │   │   │   │   │   │   │   │   └── LICENSE
│       │   │   │   │   │   │   │   └── graphql
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── sirupsen
│       │   │   │   │   │   │   │   └── logrus
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── sourcegraph
│       │   │   │   │   │   │   │   └── conc
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── spf13
│       │   │   │   │   │   │   │   ├── afero
│       │   │   │   │   │   │   │   │   └── LICENSE.txt
│       │   │   │   │   │   │   │   ├── cast
│       │   │   │   │   │   │   │   │   └── LICENSE
│       │   │   │   │   │   │   │   ├── cobra
│       │   │   │   │   │   │   │   │   └── LICENSE.txt
│       │   │   │   │   │   │   │   ├── pflag
│       │   │   │   │   │   │   │   │   └── LICENSE
│       │   │   │   │   │   │   │   └── viper
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── subosito
│       │   │   │   │   │   │   │   └── gotenv
│       │   │   │   │   │   │   │       └── LICENSE
│       │   │   │   │   │   │   ├── yosida95
│       │   │   │   │   │   │   │   └── uritemplate
│       │   │   │   │   │   │   │       └── v3
│       │   │   │   │   │   │   │           └── LICENSE
│       │   │   │   │   │   │   └── yudai
│       │   │   │   │   │   │       └── golcs
│       │   │   │   │   │   │           └── LICENSE
│       │   │   │   │   │   ├── golang.org
│       │   │   │   │   │   │   └── x
│       │   │   │   │   │   │       ├── exp
│       │   │   │   │   │   │       │   └── LICENSE
│       │   │   │   │   │   │       ├── sys
│       │   │   │   │   │   │       │   ├── unix
│       │   │   │   │   │   │       │   │   └── LICENSE
│       │   │   │   │   │   │       │   └── windows
│       │   │   │   │   │   │       │       └── LICENSE
│       │   │   │   │   │   │       ├── text
│       │   │   │   │   │   │       │   └── LICENSE
│       │   │   │   │   │   │       └── time
│       │   │   │   │   │   │           └── rate
│       │   │   │   │   │   │               └── LICENSE
│       │   │   │   │   │   └── gopkg.in
│       │   │   │   │   │       ├── yaml.v2
│       │   │   │   │   │       │   ├── LICENSE
│       │   │   │   │   │       │   └── NOTICE
│       │   │   │   │   │       └── yaml.v3
│       │   │   │   │   │           ├── LICENSE
│       │   │   │   │   │           └── NOTICE
│       │   │   │   │   ├── third-party-licenses.darwin.md
│       │   │   │   │   ├── third-party-licenses.linux.md
│       │   │   │   │   └── third-party-licenses.windows.md
│       │   │   │   └── memory-server
│       │   │   ├── Rules
│       │   │   └── Workflows
│       │   ├── DO NOT DELETE
│       │   │   └── github-recovery-codes.txt
│       │   ├── Hiện nay hệ thống đã tích.txt
│       │   ├── make the code base compatible.txt
│       │   └── The code base folder structure.txt
│       ├── Downloads
│       │   └── github-recovery-codes.txt
│       ├── go
│       │   ├── api
│       │   │   ├── except.txt
│       │   │   ├── go1.10.txt
│       │   │   ├── go1.11.txt
│       │   │   ├── go1.12.txt
│       │   │   ├── go1.13.txt
│       │   │   ├── go1.14.txt
│       │   │   ├── go1.15.txt
│       │   │   ├── go1.16.txt
│       │   │   ├── go1.17.txt
│       │   │   ├── go1.18.txt
│       │   │   ├── go1.19.txt
│       │   │   ├── go1.1.txt
│       │   │   ├── go1.20.txt
│       │   │   ├── go1.21.txt
│       │   │   ├── go1.2.txt
│       │   │   ├── go1.3.txt
│       │   │   ├── go1.4.txt
│       │   │   ├── go1.5.txt
│       │   │   ├── go1.6.txt
│       │   │   ├── go1.7.txt
│       │   │   ├── go1.8.txt
│       │   │   ├── go1.9.txt
│       │   │   ├── go1.txt
│       │   │   └── README
│       │   ├── bin
│       │   │   ├── go
│       │   │   └── gofmt
│       │   ├── codereview.cfg
│       │   ├── CONTRIBUTING.md
│       │   ├── doc
│       │   │   ├── asm.html
│       │   │   ├── go1.17_spec.html
│       │   │   ├── godebug.md
│       │   │   ├── go_mem.html
│       │   │   └── go_spec.html
│       │   ├── go.env
│       │   ├── lib
│       │   │   └── time
│       │   │       ├── mkzip.go
│       │   │       ├── README
│       │   │       ├── update.bash
│       │   │       └── zoneinfo.zip
│       │   ├── LICENSE
│       │   ├── misc
│       │   │   ├── cgo
│       │   │   │   └── gmp
│       │   │   │       ├── fib.go
│       │   │   │       ├── gmp.go
│       │   │   │       └── pi.go
│       │   │   ├── chrome
│       │   │   │   └── gophertool
│       │   │   │       ├── background.html
│       │   │   │       ├── background.js
│       │   │   │       ├── gopher.js
│       │   │   │       ├── gopher.png
│       │   │   │       ├── manifest.json
│       │   │   │       ├── popup.html
│       │   │   │       ├── popup.js
│       │   │   │       └── README.txt
│       │   │   ├── editors
│       │   │   ├── go_android_exec
│       │   │   │   ├── exitcode_test.go
│       │   │   │   ├── main.go
│       │   │   │   └── README
│       │   │   ├── go.mod
│       │   │   ├── ios
│       │   │   │   ├── clangwrap.sh
│       │   │   │   ├── detect.go
│       │   │   │   ├── go_ios_exec.go
│       │   │   │   └── README
│       │   │   ├── linkcheck
│       │   │   │   └── linkcheck.go
│       │   │   └── wasm
│       │   │       ├── go_js_wasm_exec
│       │   │       ├── go_wasip1_wasm_exec
│       │   │       ├── wasm_exec.html
│       │   │       ├── wasm_exec.js
│       │   │       └── wasm_exec_node.js
│       │   ├── PATENTS
│       │   ├── pkg
│       │   │   ├── include
│       │   │   │   ├── asm_amd64.h
│       │   │   │   ├── asm_ppc64x.h
│       │   │   │   ├── funcdata.h
│       │   │   │   └── textflag.h
│       │   │   ├── mod
│       │   │   │   ├── cache
│       │   │   │   │   └── download
│       │   │   │   │       ├── github.com
│       │   │   │   │       │   ├── fsnotify
│       │   │   │   │       │   │   └── fsnotify
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v1.8.0.info
│       │   │   │   │       │   │           ├── v1.8.0.lock
│       │   │   │   │       │   │           ├── v1.8.0.mod
│       │   │   │   │       │   │           ├── v1.8.0.zip
│       │   │   │   │       │   │           └── v1.8.0.ziphash
│       │   │   │   │       │   ├── google
│       │   │   │   │       │   │   ├── go-github
│       │   │   │   │       │   │   │   ├── v71
│       │   │   │   │       │   │   │   │   └── @v
│       │   │   │   │       │   │   │   │       ├── list
│       │   │   │   │       │   │   │   │       ├── v71.0.0.info
│       │   │   │   │       │   │   │   │       ├── v71.0.0.lock
│       │   │   │   │       │   │   │   │       ├── v71.0.0.mod
│       │   │   │   │       │   │   │   │       ├── v71.0.0.zip
│       │   │   │   │       │   │   │   │       └── v71.0.0.ziphash
│       │   │   │   │       │   │   │   └── v72
│       │   │   │   │       │   │   │       └── @v
│       │   │   │   │       │   │   │           ├── list
│       │   │   │   │       │   │   │           ├── v72.0.0.info
│       │   │   │   │       │   │   │           ├── v72.0.0.lock
│       │   │   │   │       │   │   │           ├── v72.0.0.mod
│       │   │   │   │       │   │   │           ├── v72.0.0.zip
│       │   │   │   │       │   │   │           └── v72.0.0.ziphash
│       │   │   │   │       │   │   ├── go-querystring
│       │   │   │   │       │   │   │   └── @v
│       │   │   │   │       │   │   │       ├── list
│       │   │   │   │       │   │   │       ├── v1.1.0.info
│       │   │   │   │       │   │   │       ├── v1.1.0.lock
│       │   │   │   │       │   │   │       ├── v1.1.0.mod
│       │   │   │   │       │   │   │       ├── v1.1.0.zip
│       │   │   │   │       │   │   │       └── v1.1.0.ziphash
│       │   │   │   │       │   │   └── uuid
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v1.6.0.info
│       │   │   │   │       │   │           ├── v1.6.0.lock
│       │   │   │   │       │   │           ├── v1.6.0.mod
│       │   │   │   │       │   │           ├── v1.6.0.zip
│       │   │   │   │       │   │           └── v1.6.0.ziphash
│       │   │   │   │       │   ├── gorilla
│       │   │   │   │       │   │   └── mux
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v1.8.0.info
│       │   │   │   │       │   │           ├── v1.8.0.lock
│       │   │   │   │       │   │           ├── v1.8.0.mod
│       │   │   │   │       │   │           ├── v1.8.0.zip
│       │   │   │   │       │   │           └── v1.8.0.ziphash
│       │   │   │   │       │   ├── go-viper
│       │   │   │   │       │   │   └── mapstructure
│       │   │   │   │       │   │       └── v2
│       │   │   │   │       │   │           └── @v
│       │   │   │   │       │   │               ├── list
│       │   │   │   │       │   │               ├── v2.3.0.info
│       │   │   │   │       │   │               ├── v2.3.0.lock
│       │   │   │   │       │   │               ├── v2.3.0.mod
│       │   │   │   │       │   │               ├── v2.3.0.zip
│       │   │   │   │       │   │               └── v2.3.0.ziphash
│       │   │   │   │       │   ├── mark3labs
│       │   │   │   │       │   │   └── mcp-go
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v0.32.0.info
│       │   │   │   │       │   │           ├── v0.32.0.lock
│       │   │   │   │       │   │           ├── v0.32.0.mod
│       │   │   │   │       │   │           ├── v0.32.0.zip
│       │   │   │   │       │   │           └── v0.32.0.ziphash
│       │   │   │   │       │   ├── migueleliasweb
│       │   │   │   │       │   │   └── go-github-mock
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v1.3.0.info
│       │   │   │   │       │   │           ├── v1.3.0.lock
│       │   │   │   │       │   │           ├── v1.3.0.mod
│       │   │   │   │       │   │           ├── v1.3.0.zip
│       │   │   │   │       │   │           └── v1.3.0.ziphash
│       │   │   │   │       │   ├── pelletier
│       │   │   │   │       │   │   └── go-toml
│       │   │   │   │       │   │       └── v2
│       │   │   │   │       │   │           └── @v
│       │   │   │   │       │   │               ├── list
│       │   │   │   │       │   │               ├── v2.2.3.info
│       │   │   │   │       │   │               ├── v2.2.3.lock
│       │   │   │   │       │   │               ├── v2.2.3.mod
│       │   │   │   │       │   │               ├── v2.2.3.zip
│       │   │   │   │       │   │               └── v2.2.3.ziphash
│       │   │   │   │       │   ├── sagikazarmark
│       │   │   │   │       │   │   └── locafero
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v0.9.0.info
│       │   │   │   │       │   │           ├── v0.9.0.lock
│       │   │   │   │       │   │           ├── v0.9.0.mod
│       │   │   │   │       │   │           ├── v0.9.0.zip
│       │   │   │   │       │   │           └── v0.9.0.ziphash
│       │   │   │   │       │   ├── shurcoo!l
│       │   │   │   │       │   │   ├── githubv4
│       │   │   │   │       │   │   │   └── @v
│       │   │   │   │       │   │   │       ├── list
│       │   │   │   │       │   │   │       ├── v0.0.0-20240727222349-48295856cce7.info
│       │   │   │   │       │   │   │       ├── v0.0.0-20240727222349-48295856cce7.lock
│       │   │   │   │       │   │   │       ├── v0.0.0-20240727222349-48295856cce7.mod
│       │   │   │   │       │   │   │       ├── v0.0.0-20240727222349-48295856cce7.zip
│       │   │   │   │       │   │   │       └── v0.0.0-20240727222349-48295856cce7.ziphash
│       │   │   │   │       │   │   └── graphql
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v0.0.0-20230722043721-ed46e5a46466.info
│       │   │   │   │       │   │           ├── v0.0.0-20230722043721-ed46e5a46466.lock
│       │   │   │   │       │   │           ├── v0.0.0-20230722043721-ed46e5a46466.mod
│       │   │   │   │       │   │           ├── v0.0.0-20230722043721-ed46e5a46466.zip
│       │   │   │   │       │   │           └── v0.0.0-20230722043721-ed46e5a46466.ziphash
│       │   │   │   │       │   ├── sirupsen
│       │   │   │   │       │   │   └── logrus
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v1.9.3.info
│       │   │   │   │       │   │           ├── v1.9.3.lock
│       │   │   │   │       │   │           ├── v1.9.3.mod
│       │   │   │   │       │   │           ├── v1.9.3.zip
│       │   │   │   │       │   │           └── v1.9.3.ziphash
│       │   │   │   │       │   ├── sourcegraph
│       │   │   │   │       │   │   └── conc
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v0.3.0.info
│       │   │   │   │       │   │           ├── v0.3.0.lock
│       │   │   │   │       │   │           ├── v0.3.0.mod
│       │   │   │   │       │   │           ├── v0.3.0.zip
│       │   │   │   │       │   │           └── v0.3.0.ziphash
│       │   │   │   │       │   ├── spf13
│       │   │   │   │       │   │   ├── afero
│       │   │   │   │       │   │   │   └── @v
│       │   │   │   │       │   │   │       ├── list
│       │   │   │   │       │   │   │       ├── v1.14.0.info
│       │   │   │   │       │   │   │       ├── v1.14.0.lock
│       │   │   │   │       │   │   │       ├── v1.14.0.mod
│       │   │   │   │       │   │   │       ├── v1.14.0.zip
│       │   │   │   │       │   │   │       └── v1.14.0.ziphash
│       │   │   │   │       │   │   ├── cast
│       │   │   │   │       │   │   │   └── @v
│       │   │   │   │       │   │   │       ├── list
│       │   │   │   │       │   │   │       ├── v1.7.1.info
│       │   │   │   │       │   │   │       ├── v1.7.1.lock
│       │   │   │   │       │   │   │       ├── v1.7.1.mod
│       │   │   │   │       │   │   │       ├── v1.7.1.zip
│       │   │   │   │       │   │   │       └── v1.7.1.ziphash
│       │   │   │   │       │   │   ├── cobra
│       │   │   │   │       │   │   │   └── @v
│       │   │   │   │       │   │   │       ├── list
│       │   │   │   │       │   │   │       ├── v1.9.1.info
│       │   │   │   │       │   │   │       ├── v1.9.1.lock
│       │   │   │   │       │   │   │       ├── v1.9.1.mod
│       │   │   │   │       │   │   │       ├── v1.9.1.zip
│       │   │   │   │       │   │   │       └── v1.9.1.ziphash
│       │   │   │   │       │   │   ├── pflag
│       │   │   │   │       │   │   │   └── @v
│       │   │   │   │       │   │   │       ├── list
│       │   │   │   │       │   │   │       ├── v1.0.6.info
│       │   │   │   │       │   │   │       ├── v1.0.6.lock
│       │   │   │   │       │   │   │       ├── v1.0.6.mod
│       │   │   │   │       │   │   │       ├── v1.0.6.zip
│       │   │   │   │       │   │   │       └── v1.0.6.ziphash
│       │   │   │   │       │   │   └── viper
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v1.20.1.info
│       │   │   │   │       │   │           ├── v1.20.1.lock
│       │   │   │   │       │   │           ├── v1.20.1.mod
│       │   │   │   │       │   │           ├── v1.20.1.zip
│       │   │   │   │       │   │           └── v1.20.1.ziphash
│       │   │   │   │       │   ├── subosito
│       │   │   │   │       │   │   └── gotenv
│       │   │   │   │       │   │       └── @v
│       │   │   │   │       │   │           ├── list
│       │   │   │   │       │   │           ├── v1.6.0.info
│       │   │   │   │       │   │           ├── v1.6.0.lock
│       │   │   │   │       │   │           ├── v1.6.0.mod
│       │   │   │   │       │   │           ├── v1.6.0.zip
│       │   │   │   │       │   │           └── v1.6.0.ziphash
│       │   │   │   │       │   └── yosida95
│       │   │   │   │       │       └── uritemplate
│       │   │   │   │       │           └── v3
│       │   │   │   │       │               └── @v
│       │   │   │   │       │                   ├── list
│       │   │   │   │       │                   ├── v3.0.2.info
│       │   │   │   │       │                   ├── v3.0.2.lock
│       │   │   │   │       │                   ├── v3.0.2.mod
│       │   │   │   │       │                   ├── v3.0.2.zip
│       │   │   │   │       │                   └── v3.0.2.ziphash
│       │   │   │   │       ├── golang.org
│       │   │   │   │       │   ├── toolchain
│       │   │   │   │       │   │   └── @v
│       │   │   │   │       │   │       ├── v0.0.1-go1.23.7.linux-arm64.lock
│       │   │   │   │       │   │       ├── v0.0.1-go1.23.7.linux-arm64.zip
│       │   │   │   │       │   │       └── v0.0.1-go1.23.7.linux-arm64.ziphash
│       │   │   │   │       │   └── x
│       │   │   │   │       │       ├── sys
│       │   │   │   │       │       │   └── @v
│       │   │   │   │       │       │       ├── list
│       │   │   │   │       │       │       ├── v0.31.0.info
│       │   │   │   │       │       │       ├── v0.31.0.lock
│       │   │   │   │       │       │       ├── v0.31.0.mod
│       │   │   │   │       │       │       ├── v0.31.0.zip
│       │   │   │   │       │       │       └── v0.31.0.ziphash
│       │   │   │   │       │       ├── text
│       │   │   │   │       │       │   └── @v
│       │   │   │   │       │       │       ├── list
│       │   │   │   │       │       │       ├── v0.23.0.info
│       │   │   │   │       │       │       ├── v0.23.0.lock
│       │   │   │   │       │       │       ├── v0.23.0.mod
│       │   │   │   │       │       │       ├── v0.23.0.zip
│       │   │   │   │       │       │       └── v0.23.0.ziphash
│       │   │   │   │       │       └── time
│       │   │   │   │       │           └── @v
│       │   │   │   │       │               ├── list
│       │   │   │   │       │               ├── v0.5.0.info
│       │   │   │   │       │               ├── v0.5.0.lock
│       │   │   │   │       │               ├── v0.5.0.mod
│       │   │   │   │       │               ├── v0.5.0.zip
│       │   │   │   │       │               └── v0.5.0.ziphash
│       │   │   │   │       ├── gopkg.in
│       │   │   │   │       │   └── yaml.v3
│       │   │   │   │       │       └── @v
│       │   │   │   │       │           ├── list
│       │   │   │   │       │           ├── v3.0.1.info
│       │   │   │   │       │           ├── v3.0.1.lock
│       │   │   │   │       │           ├── v3.0.1.mod
│       │   │   │   │       │           ├── v3.0.1.zip
│       │   │   │   │       │           └── v3.0.1.ziphash
│       │   │   │   │       └── sumdb
│       │   │   │   │           └── sum.golang.org
│       │   │   │   │               ├── lookup
│       │   │   │   │               │   └── golang.org
│       │   │   │   │               │       └── toolchain@v0.0.1-go1.23.7.linux-arm64
│       │   │   │   │               └── tile
│       │   │   │   │                   └── 8
│       │   │   │   │                       ├── 0
│       │   │   │   │                       │   ├── x136
│       │   │   │   │                       │   │   └── 895
│       │   │   │   │                       │   └── x155
│       │   │   │   │                       │       └── 697.p
│       │   │   │   │                       │           └── 111
│       │   │   │   │                       ├── 1
│       │   │   │   │                       │   ├── 534
│       │   │   │   │                       │   └── 608.p
│       │   │   │   │                       │       └── 49
│       │   │   │   │                       ├── 2
│       │   │   │   │                       │   └── 002.p
│       │   │   │   │                       │       └── 96
│       │   │   │   │                       └── 3
│       │   │   │   │                           └── 000.p
│       │   │   │   │                               └── 2
│       │   │   │   ├── github.com
│       │   │   │   │   ├── fsnotify
│       │   │   │   │   │   └── fsnotify@v1.8.0
│       │   │   │   │   │       ├── backend_fen.go
│       │   │   │   │   │       ├── backend_fen_test.go
│       │   │   │   │   │       ├── backend_inotify.go
│       │   │   │   │   │       ├── backend_inotify_test.go
│       │   │   │   │   │       ├── backend_kqueue.go
│       │   │   │   │   │       ├── backend_kqueue_test.go
│       │   │   │   │   │       ├── backend_other.go
│       │   │   │   │   │       ├── backend_windows.go
│       │   │   │   │   │       ├── backend_windows_test.go
│       │   │   │   │   │       ├── CHANGELOG.md
│       │   │   │   │   │       ├── cmd
│       │   │   │   │   │       │   └── fsnotify
│       │   │   │   │   │       │       ├── closewrite.go
│       │   │   │   │   │       │       ├── dedup.go
│       │   │   │   │   │       │       ├── file.go
│       │   │   │   │   │       │       ├── main.go
│       │   │   │   │   │       │       └── watch.go
│       │   │   │   │   │       ├── CONTRIBUTING.md
│       │   │   │   │   │       ├── fsnotify.go
│       │   │   │   │   │       ├── fsnotify_test.go
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── go.sum
│       │   │   │   │   │       ├── helpers_test.go
│       │   │   │   │   │       ├── internal
│       │   │   │   │   │       │   ├── darwin.go
│       │   │   │   │   │       │   ├── debug_darwin.go
│       │   │   │   │   │       │   ├── debug_dragonfly.go
│       │   │   │   │   │       │   ├── debug_freebsd.go
│       │   │   │   │   │       │   ├── debug_kqueue.go
│       │   │   │   │   │       │   ├── debug_linux.go
│       │   │   │   │   │       │   ├── debug_netbsd.go
│       │   │   │   │   │       │   ├── debug_openbsd.go
│       │   │   │   │   │       │   ├── debug_solaris.go
│       │   │   │   │   │       │   ├── debug_windows.go
│       │   │   │   │   │       │   ├── freebsd.go
│       │   │   │   │   │       │   ├── internal.go
│       │   │   │   │   │       │   ├── unix2.go
│       │   │   │   │   │       │   ├── unix.go
│       │   │   │   │   │       │   ├── windows.go
│       │   │   │   │   │       │   └── ztest
│       │   │   │   │   │       │       ├── diff.go
│       │   │   │   │   │       │       └── diff_test.go
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       ├── system_bsd.go
│       │   │   │   │   │       ├── system_darwin.go
│       │   │   │   │   │       ├── test
│       │   │   │   │   │       │   └── kqueue.c
│       │   │   │   │   │       └── testdata
│       │   │   │   │   │           ├── watch-dir
│       │   │   │   │   │           │   ├── bug-277
│       │   │   │   │   │           │   ├── create-cyclic-symlink
│       │   │   │   │   │           │   ├── create-dev
│       │   │   │   │   │           │   ├── create-dir
│       │   │   │   │   │           │   ├── create-empty-file
│       │   │   │   │   │           │   ├── create-fifo
│       │   │   │   │   │           │   ├── create-file-with-data
│       │   │   │   │   │           │   ├── create-unresolvable-symlink
│       │   │   │   │   │           │   ├── dir-only
│       │   │   │   │   │           │   ├── make-file-unreadable
│       │   │   │   │   │           │   ├── multiple-creates
│       │   │   │   │   │           │   ├── only-chmod
│       │   │   │   │   │           │   ├── only-create
│       │   │   │   │   │           │   ├── only-remove
│       │   │   │   │   │           │   ├── only-rename
│       │   │   │   │   │           │   ├── only-write
│       │   │   │   │   │           │   ├── op-all
│       │   │   │   │   │           │   ├── op-closeread
│       │   │   │   │   │           │   ├── op-closewrite
│       │   │   │   │   │           │   ├── op-open
│       │   │   │   │   │           │   ├── op-read
│       │   │   │   │   │           │   ├── remove-symlink
│       │   │   │   │   │           │   ├── remove-while-watching-parent
│       │   │   │   │   │           │   ├── rename-file
│       │   │   │   │   │           │   ├── rename-from-other-watch
│       │   │   │   │   │           │   ├── rename-from-unwatched
│       │   │   │   │   │           │   ├── rename-from-unwatched-overwrite
│       │   │   │   │   │           │   ├── rename-overwrite
│       │   │   │   │   │           │   ├── rename-symlink
│       │   │   │   │   │           │   ├── rename-to-unwatched
│       │   │   │   │   │           │   ├── rename-watched-dir
│       │   │   │   │   │           │   ├── subdir
│       │   │   │   │   │           │   ├── symlink-dir
│       │   │   │   │   │           │   ├── symlink-file
│       │   │   │   │   │           │   ├── symlink-nofollow
│       │   │   │   │   │           │   ├── truncate-file
│       │   │   │   │   │           │   ├── unreadable-file
│       │   │   │   │   │           │   ├── watch-dir-inside-watched
│       │   │   │   │   │           │   ├── watch-file-inside-watched-dir
│       │   │   │   │   │           │   └── watch-twice
│       │   │   │   │   │           ├── watch-file
│       │   │   │   │   │           │   ├── chmod
│       │   │   │   │   │           │   ├── chmod-after-write
│       │   │   │   │   │           │   ├── op-all
│       │   │   │   │   │           │   ├── op-closeread
│       │   │   │   │   │           │   ├── op-closewrite
│       │   │   │   │   │           │   ├── op-open
│       │   │   │   │   │           │   ├── op-read
│       │   │   │   │   │           │   ├── overwrite-watched-file
│       │   │   │   │   │           │   ├── overwrite-watched-file-with-watched-file
│       │   │   │   │   │           │   ├── re-add-renamed-filed
│       │   │   │   │   │           │   ├── remove-watched-file
│       │   │   │   │   │           │   ├── rename-watched-file
│       │   │   │   │   │           │   └── watch-twice
│       │   │   │   │   │           ├── watch-recurse
│       │   │   │   │   │           │   ├── add-dir
│       │   │   │   │   │           │   ├── add-file
│       │   │   │   │   │           │   ├── remove-dir
│       │   │   │   │   │           │   ├── remove-recursive
│       │   │   │   │   │           │   ├── remove-watched-dir
│       │   │   │   │   │           │   └── rename-dir
│       │   │   │   │   │           └── watch-symlink
│       │   │   │   │   │               ├── nofollow-dir
│       │   │   │   │   │               ├── nofollow-file
│       │   │   │   │   │               ├── to-dir
│       │   │   │   │   │               ├── to-dir-relative
│       │   │   │   │   │               ├── to-file
│       │   │   │   │   │               └── to-file-relative
│       │   │   │   │   ├── google
│       │   │   │   │   │   ├── go-github
│       │   │   │   │   │   │   ├── v71@v71.0.0
│       │   │   │   │   │   │   │   ├── AUTHORS
│       │   │   │   │   │   │   │   ├── CONTRIBUTING.md
│       │   │   │   │   │   │   │   ├── github
│       │   │   │   │   │   │   │   │   ├── actions_artifacts.go
│       │   │   │   │   │   │   │   │   ├── actions_artifacts_test.go
│       │   │   │   │   │   │   │   │   ├── actions_cache.go
│       │   │   │   │   │   │   │   │   ├── actions_cache_test.go
│       │   │   │   │   │   │   │   │   ├── actions.go
│       │   │   │   │   │   │   │   │   ├── actions_hosted_runners.go
│       │   │   │   │   │   │   │   │   ├── actions_hosted_runners_test.go
│       │   │   │   │   │   │   │   │   ├── actions_oidc.go
│       │   │   │   │   │   │   │   │   ├── actions_oidc_test.go
│       │   │   │   │   │   │   │   │   ├── actions_permissions_enterprise.go
│       │   │   │   │   │   │   │   │   ├── actions_permissions_enterprise_test.go
│       │   │   │   │   │   │   │   │   ├── actions_permissions_orgs.go
│       │   │   │   │   │   │   │   │   ├── actions_permissions_orgs_test.go
│       │   │   │   │   │   │   │   │   ├── actions_required_workflows.go
│       │   │   │   │   │   │   │   │   ├── actions_required_workflows_test.go
│       │   │   │   │   │   │   │   │   ├── actions_runner_groups.go
│       │   │   │   │   │   │   │   │   ├── actions_runner_groups_test.go
│       │   │   │   │   │   │   │   │   ├── actions_runners.go
│       │   │   │   │   │   │   │   │   ├── actions_runners_test.go
│       │   │   │   │   │   │   │   │   ├── actions_secrets.go
│       │   │   │   │   │   │   │   │   ├── actions_secrets_test.go
│       │   │   │   │   │   │   │   │   ├── actions_variables.go
│       │   │   │   │   │   │   │   │   ├── actions_variables_test.go
│       │   │   │   │   │   │   │   │   ├── actions_workflow_jobs.go
│       │   │   │   │   │   │   │   │   ├── actions_workflow_jobs_test.go
│       │   │   │   │   │   │   │   │   ├── actions_workflow_runs.go
│       │   │   │   │   │   │   │   │   ├── actions_workflow_runs_test.go
│       │   │   │   │   │   │   │   │   ├── actions_workflows.go
│       │   │   │   │   │   │   │   │   ├── actions_workflows_test.go
│       │   │   │   │   │   │   │   │   ├── activity_events.go
│       │   │   │   │   │   │   │   │   ├── activity_events_test.go
│       │   │   │   │   │   │   │   │   ├── activity.go
│       │   │   │   │   │   │   │   │   ├── activity_notifications.go
│       │   │   │   │   │   │   │   │   ├── activity_notifications_test.go
│       │   │   │   │   │   │   │   │   ├── activity_star.go
│       │   │   │   │   │   │   │   │   ├── activity_star_test.go
│       │   │   │   │   │   │   │   │   ├── activity_test.go
│       │   │   │   │   │   │   │   │   ├── activity_watching.go
│       │   │   │   │   │   │   │   │   ├── activity_watching_test.go
│       │   │   │   │   │   │   │   │   ├── admin.go
│       │   │   │   │   │   │   │   │   ├── admin_orgs.go
│       │   │   │   │   │   │   │   │   ├── admin_orgs_test.go
│       │   │   │   │   │   │   │   │   ├── admin_stats.go
│       │   │   │   │   │   │   │   │   ├── admin_stats_test.go
│       │   │   │   │   │   │   │   │   ├── admin_test.go
│       │   │   │   │   │   │   │   │   ├── admin_users.go
│       │   │   │   │   │   │   │   │   ├── admin_users_test.go
│       │   │   │   │   │   │   │   │   ├── apps.go
│       │   │   │   │   │   │   │   │   ├── apps_hooks_deliveries.go
│       │   │   │   │   │   │   │   │   ├── apps_hooks_deliveries_test.go
│       │   │   │   │   │   │   │   │   ├── apps_hooks.go
│       │   │   │   │   │   │   │   │   ├── apps_hooks_test.go
│       │   │   │   │   │   │   │   │   ├── apps_installation.go
│       │   │   │   │   │   │   │   │   ├── apps_installation_test.go
│       │   │   │   │   │   │   │   │   ├── apps_manifest.go
│       │   │   │   │   │   │   │   │   ├── apps_manifest_test.go
│       │   │   │   │   │   │   │   │   ├── apps_marketplace.go
│       │   │   │   │   │   │   │   │   ├── apps_marketplace_test.go
│       │   │   │   │   │   │   │   │   ├── apps_test.go
│       │   │   │   │   │   │   │   │   ├── attestations.go
│       │   │   │   │   │   │   │   │   ├── authorizations.go
│       │   │   │   │   │   │   │   │   ├── authorizations_test.go
│       │   │   │   │   │   │   │   │   ├── billing.go
│       │   │   │   │   │   │   │   │   ├── billing_test.go
│       │   │   │   │   │   │   │   │   ├── checks.go
│       │   │   │   │   │   │   │   │   ├── checks_test.go
│       │   │   │   │   │   │   │   │   ├── code_scanning.go
│       │   │   │   │   │   │   │   │   ├── code_scanning_test.go
│       │   │   │   │   │   │   │   │   ├── codesofconduct.go
│       │   │   │   │   │   │   │   │   ├── codesofconduct_test.go
│       │   │   │   │   │   │   │   │   ├── codespaces.go
│       │   │   │   │   │   │   │   │   ├── codespaces_secrets.go
│       │   │   │   │   │   │   │   │   ├── codespaces_secrets_test.go
│       │   │   │   │   │   │   │   │   ├── codespaces_test.go
│       │   │   │   │   │   │   │   │   ├── copilot.go
│       │   │   │   │   │   │   │   │   ├── copilot_test.go
│       │   │   │   │   │   │   │   │   ├── dependabot_alerts.go
│       │   │   │   │   │   │   │   │   ├── dependabot_alerts_test.go
│       │   │   │   │   │   │   │   │   ├── dependabot.go
│       │   │   │   │   │   │   │   │   ├── dependabot_secrets.go
│       │   │   │   │   │   │   │   │   ├── dependabot_secrets_test.go
│       │   │   │   │   │   │   │   │   ├── dependency_graph.go
│       │   │   │   │   │   │   │   │   ├── dependency_graph_snapshots.go
│       │   │   │   │   │   │   │   │   ├── dependency_graph_snapshots_test.go
│       │   │   │   │   │   │   │   │   ├── dependency_graph_test.go
│       │   │   │   │   │   │   │   │   ├── doc.go
│       │   │   │   │   │   │   │   │   ├── emojis.go
│       │   │   │   │   │   │   │   │   ├── emojis_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_actions_hosted_runners.go
│       │   │   │   │   │   │   │   │   ├── enterprise_actions_hosted_runners_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_actions_runner_groups.go
│       │   │   │   │   │   │   │   │   ├── enterprise_actions_runner_groups_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_actions_runners.go
│       │   │   │   │   │   │   │   │   ├── enterprise_actions_runners_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_audit_log.go
│       │   │   │   │   │   │   │   │   ├── enterprise_audit_log_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_code_security_and_analysis.go
│       │   │   │   │   │   │   │   │   ├── enterprise_code_security_and_analysis_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise.go
│       │   │   │   │   │   │   │   │   ├── enterprise_manage_ghes_config.go
│       │   │   │   │   │   │   │   │   ├── enterprise_manage_ghes_config_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_manage_ghes.go
│       │   │   │   │   │   │   │   │   ├── enterprise_manage_ghes_maintenance.go
│       │   │   │   │   │   │   │   │   ├── enterprise_manage_ghes_maintenance_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_manage_ghes_ssh.go
│       │   │   │   │   │   │   │   │   ├── enterprise_manage_ghes_ssh_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_manage_ghes_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_network_configurations.go
│       │   │   │   │   │   │   │   │   ├── enterprise_network_configurations_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_properties.go
│       │   │   │   │   │   │   │   │   ├── enterprise_properties_test.go
│       │   │   │   │   │   │   │   │   ├── enterprise_rules.go
│       │   │   │   │   │   │   │   │   ├── enterprise_rules_test.go
│       │   │   │   │   │   │   │   │   ├── event.go
│       │   │   │   │   │   │   │   │   ├── event_test.go
│       │   │   │   │   │   │   │   │   ├── event_types.go
│       │   │   │   │   │   │   │   │   ├── event_types_test.go
│       │   │   │   │   │   │   │   │   ├── examples_test.go
│       │   │   │   │   │   │   │   │   ├── gen-accessors.go
│       │   │   │   │   │   │   │   │   ├── gen-stringify-test.go
│       │   │   │   │   │   │   │   │   ├── gists_comments.go
│       │   │   │   │   │   │   │   │   ├── gists_comments_test.go
│       │   │   │   │   │   │   │   │   ├── gists.go
│       │   │   │   │   │   │   │   │   ├── gists_test.go
│       │   │   │   │   │   │   │   │   ├── git_blobs.go
│       │   │   │   │   │   │   │   │   ├── git_blobs_test.go
│       │   │   │   │   │   │   │   │   ├── git_commits.go
│       │   │   │   │   │   │   │   │   ├── git_commits_test.go
│       │   │   │   │   │   │   │   │   ├── git.go
│       │   │   │   │   │   │   │   │   ├── github-accessors.go
│       │   │   │   │   │   │   │   │   ├── github-accessors_test.go
│       │   │   │   │   │   │   │   │   ├── github.go
│       │   │   │   │   │   │   │   │   ├── github-stringify_test.go
│       │   │   │   │   │   │   │   │   ├── github_test.go
│       │   │   │   │   │   │   │   │   ├── gitignore.go
│       │   │   │   │   │   │   │   │   ├── gitignore_test.go
│       │   │   │   │   │   │   │   │   ├── git_refs.go
│       │   │   │   │   │   │   │   │   ├── git_refs_test.go
│       │   │   │   │   │   │   │   │   ├── git_tags.go
│       │   │   │   │   │   │   │   │   ├── git_tags_test.go
│       │   │   │   │   │   │   │   │   ├── git_trees.go
│       │   │   │   │   │   │   │   │   ├── git_trees_test.go
│       │   │   │   │   │   │   │   │   ├── interactions.go
│       │   │   │   │   │   │   │   │   ├── interactions_orgs.go
│       │   │   │   │   │   │   │   │   ├── interactions_orgs_test.go
│       │   │   │   │   │   │   │   │   ├── interactions_repos.go
│       │   │   │   │   │   │   │   │   ├── interactions_repos_test.go
│       │   │   │   │   │   │   │   │   ├── interactions_test.go
│       │   │   │   │   │   │   │   │   ├── issue_import.go
│       │   │   │   │   │   │   │   │   ├── issue_import_test.go
│       │   │   │   │   │   │   │   │   ├── issues_assignees.go
│       │   │   │   │   │   │   │   │   ├── issues_assignees_test.go
│       │   │   │   │   │   │   │   │   ├── issues_comments.go
│       │   │   │   │   │   │   │   │   ├── issues_comments_test.go
│       │   │   │   │   │   │   │   │   ├── issues_events.go
│       │   │   │   │   │   │   │   │   ├── issues_events_test.go
│       │   │   │   │   │   │   │   │   ├── issues.go
│       │   │   │   │   │   │   │   │   ├── issues_labels.go
│       │   │   │   │   │   │   │   │   ├── issues_labels_test.go
│       │   │   │   │   │   │   │   │   ├── issues_milestones.go
│       │   │   │   │   │   │   │   │   ├── issues_milestones_test.go
│       │   │   │   │   │   │   │   │   ├── issues_test.go
│       │   │   │   │   │   │   │   │   ├── issues_timeline.go
│       │   │   │   │   │   │   │   │   ├── issues_timeline_test.go
│       │   │   │   │   │   │   │   │   ├── licenses.go
│       │   │   │   │   │   │   │   │   ├── licenses_test.go
│       │   │   │   │   │   │   │   │   ├── markdown.go
│       │   │   │   │   │   │   │   │   ├── markdown_test.go
│       │   │   │   │   │   │   │   │   ├── messages.go
│       │   │   │   │   │   │   │   │   ├── messages_test.go
│       │   │   │   │   │   │   │   │   ├── meta.go
│       │   │   │   │   │   │   │   │   ├── meta_test.go
│       │   │   │   │   │   │   │   │   ├── migrations.go
│       │   │   │   │   │   │   │   │   ├── migrations_source_import.go
│       │   │   │   │   │   │   │   │   ├── migrations_source_import_test.go
│       │   │   │   │   │   │   │   │   ├── migrations_test.go
│       │   │   │   │   │   │   │   │   ├── migrations_user.go
│       │   │   │   │   │   │   │   │   ├── migrations_user_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_actions_allowed.go
│       │   │   │   │   │   │   │   │   ├── orgs_actions_allowed_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_actions_permissions.go
│       │   │   │   │   │   │   │   │   ├── orgs_actions_permissions_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_attestations.go
│       │   │   │   │   │   │   │   │   ├── orgs_attestations_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_audit_log.go
│       │   │   │   │   │   │   │   │   ├── orgs_audit_log_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_codesecurity_configurations.go
│       │   │   │   │   │   │   │   │   ├── orgs_codesecurity_configurations_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_credential_authorizations.go
│       │   │   │   │   │   │   │   │   ├── orgs_credential_authorizations_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_custom_repository_roles.go
│       │   │   │   │   │   │   │   │   ├── orgs_custom_repository_roles_test.go
│       │   │   │   │   │   │   │   │   ├── orgs.go
│       │   │   │   │   │   │   │   │   ├── orgs_hooks_configuration.go
│       │   │   │   │   │   │   │   │   ├── orgs_hooks_configuration_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_hooks_deliveries.go
│       │   │   │   │   │   │   │   │   ├── orgs_hooks_deliveries_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_hooks.go
│       │   │   │   │   │   │   │   │   ├── orgs_hooks_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_issue_types.go
│       │   │   │   │   │   │   │   │   ├── orgs_issue_types_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_members.go
│       │   │   │   │   │   │   │   │   ├── orgs_members_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_network_configurations.go
│       │   │   │   │   │   │   │   │   ├── orgs_network_configurations_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_organization_roles.go
│       │   │   │   │   │   │   │   │   ├── orgs_organization_roles_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_outside_collaborators.go
│       │   │   │   │   │   │   │   │   ├── orgs_outside_collaborators_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_packages.go
│       │   │   │   │   │   │   │   │   ├── orgs_packages_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_personal_access_tokens.go
│       │   │   │   │   │   │   │   │   ├── orgs_personal_access_tokens_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_properties.go
│       │   │   │   │   │   │   │   │   ├── orgs_properties_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_rules.go
│       │   │   │   │   │   │   │   │   ├── orgs_rules_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_security_managers.go
│       │   │   │   │   │   │   │   │   ├── orgs_security_managers_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_test.go
│       │   │   │   │   │   │   │   │   ├── orgs_users_blocking.go
│       │   │   │   │   │   │   │   │   ├── orgs_users_blocking_test.go
│       │   │   │   │   │   │   │   │   ├── packages.go
│       │   │   │   │   │   │   │   │   ├── packages_test.go
│       │   │   │   │   │   │   │   │   ├── pulls_comments.go
│       │   │   │   │   │   │   │   │   ├── pulls_comments_test.go
│       │   │   │   │   │   │   │   │   ├── pulls.go
│       │   │   │   │   │   │   │   │   ├── pulls_reviewers.go
│       │   │   │   │   │   │   │   │   ├── pulls_reviewers_test.go
│       │   │   │   │   │   │   │   │   ├── pulls_reviews.go
│       │   │   │   │   │   │   │   │   ├── pulls_reviews_test.go
│       │   │   │   │   │   │   │   │   ├── pulls_test.go
│       │   │   │   │   │   │   │   │   ├── pulls_threads.go
│       │   │   │   │   │   │   │   │   ├── pulls_threads_test.go
│       │   │   │   │   │   │   │   │   ├── rate_limit.go
│       │   │   │   │   │   │   │   │   ├── rate_limit_test.go
│       │   │   │   │   │   │   │   │   ├── reactions.go
│       │   │   │   │   │   │   │   │   ├── reactions_test.go
│       │   │   │   │   │   │   │   │   ├── repos_actions_access.go
│       │   │   │   │   │   │   │   │   ├── repos_actions_access_test.go
│       │   │   │   │   │   │   │   │   ├── repos_actions_allowed.go
│       │   │   │   │   │   │   │   │   ├── repos_actions_allowed_test.go
│       │   │   │   │   │   │   │   │   ├── repos_actions_permissions.go
│       │   │   │   │   │   │   │   │   ├── repos_actions_permissions_test.go
│       │   │   │   │   │   │   │   │   ├── repos_attestations.go
│       │   │   │   │   │   │   │   │   ├── repos_attestations_test.go
│       │   │   │   │   │   │   │   │   ├── repos_autolinks.go
│       │   │   │   │   │   │   │   │   ├── repos_autolinks_test.go
│       │   │   │   │   │   │   │   │   ├── repos_codeowners.go
│       │   │   │   │   │   │   │   │   ├── repos_codeowners_test.go
│       │   │   │   │   │   │   │   │   ├── repos_collaborators.go
│       │   │   │   │   │   │   │   │   ├── repos_collaborators_test.go
│       │   │   │   │   │   │   │   │   ├── repos_comments.go
│       │   │   │   │   │   │   │   │   ├── repos_comments_test.go
│       │   │   │   │   │   │   │   │   ├── repos_commits.go
│       │   │   │   │   │   │   │   │   ├── repos_commits_test.go
│       │   │   │   │   │   │   │   │   ├── repos_community_health.go
│       │   │   │   │   │   │   │   │   ├── repos_community_health_test.go
│       │   │   │   │   │   │   │   │   ├── repos_contents.go
│       │   │   │   │   │   │   │   │   ├── repos_contents_test.go
│       │   │   │   │   │   │   │   │   ├── repos_deployment_branch_policies.go
│       │   │   │   │   │   │   │   │   ├── repos_deployment_branch_policies_test.go
│       │   │   │   │   │   │   │   │   ├── repos_deployment_protection_rules.go
│       │   │   │   │   │   │   │   │   ├── repos_deployment_protection_rules_test.go
│       │   │   │   │   │   │   │   │   ├── repos_deployments.go
│       │   │   │   │   │   │   │   │   ├── repos_deployments_test.go
│       │   │   │   │   │   │   │   │   ├── repos_environments.go
│       │   │   │   │   │   │   │   │   ├── repos_environments_test.go
│       │   │   │   │   │   │   │   │   ├── repos_forks.go
│       │   │   │   │   │   │   │   │   ├── repos_forks_test.go
│       │   │   │   │   │   │   │   │   ├── repos.go
│       │   │   │   │   │   │   │   │   ├── repos_hooks_configuration.go
│       │   │   │   │   │   │   │   │   ├── repos_hooks_configuration_test.go
│       │   │   │   │   │   │   │   │   ├── repos_hooks_deliveries.go
│       │   │   │   │   │   │   │   │   ├── repos_hooks_deliveries_test.go
│       │   │   │   │   │   │   │   │   ├── repos_hooks.go
│       │   │   │   │   │   │   │   │   ├── repos_hooks_test.go
│       │   │   │   │   │   │   │   │   ├── repos_invitations.go
│       │   │   │   │   │   │   │   │   ├── repos_invitations_test.go
│       │   │   │   │   │   │   │   │   ├── repos_keys.go
│       │   │   │   │   │   │   │   │   ├── repos_keys_test.go
│       │   │   │   │   │   │   │   │   ├── repos_lfs.go
│       │   │   │   │   │   │   │   │   ├── repos_lfs_test.go
│       │   │   │   │   │   │   │   │   ├── repos_merging.go
│       │   │   │   │   │   │   │   │   ├── repos_merging_test.go
│       │   │   │   │   │   │   │   │   ├── repos_pages.go
│       │   │   │   │   │   │   │   │   ├── repos_pages_test.go
│       │   │   │   │   │   │   │   │   ├── repos_prereceive_hooks.go
│       │   │   │   │   │   │   │   │   ├── repos_prereceive_hooks_test.go
│       │   │   │   │   │   │   │   │   ├── repos_properties.go
│       │   │   │   │   │   │   │   │   ├── repos_properties_test.go
│       │   │   │   │   │   │   │   │   ├── repos_releases.go
│       │   │   │   │   │   │   │   │   ├── repos_releases_test.go
│       │   │   │   │   │   │   │   │   ├── repos_rules.go
│       │   │   │   │   │   │   │   │   ├── repos_rules_test.go
│       │   │   │   │   │   │   │   │   ├── repos_stats.go
│       │   │   │   │   │   │   │   │   ├── repos_stats_test.go
│       │   │   │   │   │   │   │   │   ├── repos_statuses.go
│       │   │   │   │   │   │   │   │   ├── repos_statuses_test.go
│       │   │   │   │   │   │   │   │   ├── repos_tags.go
│       │   │   │   │   │   │   │   │   ├── repos_tags_test.go
│       │   │   │   │   │   │   │   │   ├── repos_test.go
│       │   │   │   │   │   │   │   │   ├── repos_traffic.go
│       │   │   │   │   │   │   │   │   ├── repos_traffic_test.go
│       │   │   │   │   │   │   │   │   ├── rules.go
│       │   │   │   │   │   │   │   │   ├── rules_test.go
│       │   │   │   │   │   │   │   │   ├── scim.go
│       │   │   │   │   │   │   │   │   ├── scim_test.go
│       │   │   │   │   │   │   │   │   ├── search.go
│       │   │   │   │   │   │   │   │   ├── search_test.go
│       │   │   │   │   │   │   │   │   ├── secret_scanning.go
│       │   │   │   │   │   │   │   │   ├── secret_scanning_test.go
│       │   │   │   │   │   │   │   │   ├── security_advisories.go
│       │   │   │   │   │   │   │   │   ├── security_advisories_test.go
│       │   │   │   │   │   │   │   │   ├── strings.go
│       │   │   │   │   │   │   │   │   ├── strings_test.go
│       │   │   │   │   │   │   │   │   ├── teams_discussion_comments.go
│       │   │   │   │   │   │   │   │   ├── teams_discussion_comments_test.go
│       │   │   │   │   │   │   │   │   ├── teams_discussions.go
│       │   │   │   │   │   │   │   │   ├── teams_discussions_test.go
│       │   │   │   │   │   │   │   │   ├── teams.go
│       │   │   │   │   │   │   │   │   ├── teams_members.go
│       │   │   │   │   │   │   │   │   ├── teams_members_test.go
│       │   │   │   │   │   │   │   │   ├── teams_test.go
│       │   │   │   │   │   │   │   │   ├── timestamp.go
│       │   │   │   │   │   │   │   │   ├── timestamp_test.go
│       │   │   │   │   │   │   │   │   ├── users_administration.go
│       │   │   │   │   │   │   │   │   ├── users_administration_test.go
│       │   │   │   │   │   │   │   │   ├── users_attestations.go
│       │   │   │   │   │   │   │   │   ├── users_attestations_test.go
│       │   │   │   │   │   │   │   │   ├── users_blocking.go
│       │   │   │   │   │   │   │   │   ├── users_blocking_test.go
│       │   │   │   │   │   │   │   │   ├── users_emails.go
│       │   │   │   │   │   │   │   │   ├── users_emails_test.go
│       │   │   │   │   │   │   │   │   ├── users_followers.go
│       │   │   │   │   │   │   │   │   ├── users_followers_test.go
│       │   │   │   │   │   │   │   │   ├── users.go
│       │   │   │   │   │   │   │   │   ├── users_gpg_keys.go
│       │   │   │   │   │   │   │   │   ├── users_gpg_keys_test.go
│       │   │   │   │   │   │   │   │   ├── users_keys.go
│       │   │   │   │   │   │   │   │   ├── users_keys_test.go
│       │   │   │   │   │   │   │   │   ├── users_packages.go
│       │   │   │   │   │   │   │   │   ├── users_packages_test.go
│       │   │   │   │   │   │   │   │   ├── users_ssh_signing_keys.go
│       │   │   │   │   │   │   │   │   ├── users_ssh_signing_keys_test.go
│       │   │   │   │   │   │   │   │   ├── users_test.go
│       │   │   │   │   │   │   │   │   ├── with_appengine.go
│       │   │   │   │   │   │   │   │   └── without_appengine.go
│       │   │   │   │   │   │   │   ├── go.mod
│       │   │   │   │   │   │   │   ├── go.sum
│       │   │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   │   ├── openapi_operations.yaml
│       │   │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   │   ├── REVIEWERS
│       │   │   │   │   │   │   │   ├── script
│       │   │   │   │   │   │   │   │   ├── fmt.sh
│       │   │   │   │   │   │   │   │   ├── generate.sh
│       │   │   │   │   │   │   │   │   ├── lint.sh
│       │   │   │   │   │   │   │   │   ├── metadata.sh
│       │   │   │   │   │   │   │   │   └── test.sh
│       │   │   │   │   │   │   │   └── test
│       │   │   │   │   │   │   │       ├── fields
│       │   │   │   │   │   │   │       │   └── fields.go
│       │   │   │   │   │   │   │       ├── integration
│       │   │   │   │   │   │   │       │   ├── activity_test.go
│       │   │   │   │   │   │   │       │   ├── audit_log_test.go
│       │   │   │   │   │   │   │       │   ├── authorizations_test.go
│       │   │   │   │   │   │   │       │   ├── doc.go
│       │   │   │   │   │   │   │       │   ├── github_test.go
│       │   │   │   │   │   │   │       │   ├── issues_test.go
│       │   │   │   │   │   │   │       │   ├── misc_test.go
│       │   │   │   │   │   │   │       │   ├── pulls_test.go
│       │   │   │   │   │   │   │       │   ├── repos_test.go
│       │   │   │   │   │   │   │       │   └── users_test.go
│       │   │   │   │   │   │   │       └── README.md
│       │   │   │   │   │   │   └── v72@v72.0.0
│       │   │   │   │   │   │       ├── AUTHORS
│       │   │   │   │   │   │       ├── CONTRIBUTING.md
│       │   │   │   │   │   │       ├── github
│       │   │   │   │   │   │       │   ├── actions_artifacts.go
│       │   │   │   │   │   │       │   ├── actions_artifacts_test.go
│       │   │   │   │   │   │       │   ├── actions_cache.go
│       │   │   │   │   │   │       │   ├── actions_cache_test.go
│       │   │   │   │   │   │       │   ├── actions.go
│       │   │   │   │   │   │       │   ├── actions_hosted_runners.go
│       │   │   │   │   │   │       │   ├── actions_hosted_runners_test.go
│       │   │   │   │   │   │       │   ├── actions_oidc.go
│       │   │   │   │   │   │       │   ├── actions_oidc_test.go
│       │   │   │   │   │   │       │   ├── actions_permissions_enterprise.go
│       │   │   │   │   │   │       │   ├── actions_permissions_enterprise_test.go
│       │   │   │   │   │   │       │   ├── actions_permissions_orgs.go
│       │   │   │   │   │   │       │   ├── actions_permissions_orgs_test.go
│       │   │   │   │   │   │       │   ├── actions_runner_groups.go
│       │   │   │   │   │   │       │   ├── actions_runner_groups_test.go
│       │   │   │   │   │   │       │   ├── actions_runners.go
│       │   │   │   │   │   │       │   ├── actions_runners_test.go
│       │   │   │   │   │   │       │   ├── actions_secrets.go
│       │   │   │   │   │   │       │   ├── actions_secrets_test.go
│       │   │   │   │   │   │       │   ├── actions_variables.go
│       │   │   │   │   │   │       │   ├── actions_variables_test.go
│       │   │   │   │   │   │       │   ├── actions_workflow_jobs.go
│       │   │   │   │   │   │       │   ├── actions_workflow_jobs_test.go
│       │   │   │   │   │   │       │   ├── actions_workflow_runs.go
│       │   │   │   │   │   │       │   ├── actions_workflow_runs_test.go
│       │   │   │   │   │   │       │   ├── actions_workflows.go
│       │   │   │   │   │   │       │   ├── actions_workflows_test.go
│       │   │   │   │   │   │       │   ├── activity_events.go
│       │   │   │   │   │   │       │   ├── activity_events_test.go
│       │   │   │   │   │   │       │   ├── activity.go
│       │   │   │   │   │   │       │   ├── activity_notifications.go
│       │   │   │   │   │   │       │   ├── activity_notifications_test.go
│       │   │   │   │   │   │       │   ├── activity_star.go
│       │   │   │   │   │   │       │   ├── activity_star_test.go
│       │   │   │   │   │   │       │   ├── activity_test.go
│       │   │   │   │   │   │       │   ├── activity_watching.go
│       │   │   │   │   │   │       │   ├── activity_watching_test.go
│       │   │   │   │   │   │       │   ├── admin.go
│       │   │   │   │   │   │       │   ├── admin_orgs.go
│       │   │   │   │   │   │       │   ├── admin_orgs_test.go
│       │   │   │   │   │   │       │   ├── admin_stats.go
│       │   │   │   │   │   │       │   ├── admin_stats_test.go
│       │   │   │   │   │   │       │   ├── admin_test.go
│       │   │   │   │   │   │       │   ├── admin_users.go
│       │   │   │   │   │   │       │   ├── admin_users_test.go
│       │   │   │   │   │   │       │   ├── apps.go
│       │   │   │   │   │   │       │   ├── apps_hooks_deliveries.go
│       │   │   │   │   │   │       │   ├── apps_hooks_deliveries_test.go
│       │   │   │   │   │   │       │   ├── apps_hooks.go
│       │   │   │   │   │   │       │   ├── apps_hooks_test.go
│       │   │   │   │   │   │       │   ├── apps_installation.go
│       │   │   │   │   │   │       │   ├── apps_installation_test.go
│       │   │   │   │   │   │       │   ├── apps_manifest.go
│       │   │   │   │   │   │       │   ├── apps_manifest_test.go
│       │   │   │   │   │   │       │   ├── apps_marketplace.go
│       │   │   │   │   │   │       │   ├── apps_marketplace_test.go
│       │   │   │   │   │   │       │   ├── apps_test.go
│       │   │   │   │   │   │       │   ├── attestations.go
│       │   │   │   │   │   │       │   ├── authorizations.go
│       │   │   │   │   │   │       │   ├── authorizations_test.go
│       │   │   │   │   │   │       │   ├── billing.go
│       │   │   │   │   │   │       │   ├── billing_test.go
│       │   │   │   │   │   │       │   ├── checks.go
│       │   │   │   │   │   │       │   ├── checks_test.go
│       │   │   │   │   │   │       │   ├── code_scanning.go
│       │   │   │   │   │   │       │   ├── code_scanning_test.go
│       │   │   │   │   │   │       │   ├── codesofconduct.go
│       │   │   │   │   │   │       │   ├── codesofconduct_test.go
│       │   │   │   │   │   │       │   ├── codespaces.go
│       │   │   │   │   │   │       │   ├── codespaces_secrets.go
│       │   │   │   │   │   │       │   ├── codespaces_secrets_test.go
│       │   │   │   │   │   │       │   ├── codespaces_test.go
│       │   │   │   │   │   │       │   ├── copilot.go
│       │   │   │   │   │   │       │   ├── copilot_test.go
│       │   │   │   │   │   │       │   ├── dependabot_alerts.go
│       │   │   │   │   │   │       │   ├── dependabot_alerts_test.go
│       │   │   │   │   │   │       │   ├── dependabot.go
│       │   │   │   │   │   │       │   ├── dependabot_secrets.go
│       │   │   │   │   │   │       │   ├── dependabot_secrets_test.go
│       │   │   │   │   │   │       │   ├── dependency_graph.go
│       │   │   │   │   │   │       │   ├── dependency_graph_snapshots.go
│       │   │   │   │   │   │       │   ├── dependency_graph_snapshots_test.go
│       │   │   │   │   │   │       │   ├── dependency_graph_test.go
│       │   │   │   │   │   │       │   ├── doc.go
│       │   │   │   │   │   │       │   ├── emojis.go
│       │   │   │   │   │   │       │   ├── emojis_test.go
│       │   │   │   │   │   │       │   ├── enterprise_actions_hosted_runners.go
│       │   │   │   │   │   │       │   ├── enterprise_actions_hosted_runners_test.go
│       │   │   │   │   │   │       │   ├── enterprise_actions_runner_groups.go
│       │   │   │   │   │   │       │   ├── enterprise_actions_runner_groups_test.go
│       │   │   │   │   │   │       │   ├── enterprise_actions_runners.go
│       │   │   │   │   │   │       │   ├── enterprise_actions_runners_test.go
│       │   │   │   │   │   │       │   ├── enterprise_audit_log.go
│       │   │   │   │   │   │       │   ├── enterprise_audit_log_test.go
│       │   │   │   │   │   │       │   ├── enterprise_code_security_and_analysis.go
│       │   │   │   │   │   │       │   ├── enterprise_code_security_and_analysis_test.go
│       │   │   │   │   │   │       │   ├── enterprise.go
│       │   │   │   │   │   │       │   ├── enterprise_manage_ghes_config.go
│       │   │   │   │   │   │       │   ├── enterprise_manage_ghes_config_test.go
│       │   │   │   │   │   │       │   ├── enterprise_manage_ghes.go
│       │   │   │   │   │   │       │   ├── enterprise_manage_ghes_maintenance.go
│       │   │   │   │   │   │       │   ├── enterprise_manage_ghes_maintenance_test.go
│       │   │   │   │   │   │       │   ├── enterprise_manage_ghes_ssh.go
│       │   │   │   │   │   │       │   ├── enterprise_manage_ghes_ssh_test.go
│       │   │   │   │   │   │       │   ├── enterprise_manage_ghes_test.go
│       │   │   │   │   │   │       │   ├── enterprise_network_configurations.go
│       │   │   │   │   │   │       │   ├── enterprise_network_configurations_test.go
│       │   │   │   │   │   │       │   ├── enterprise_properties.go
│       │   │   │   │   │   │       │   ├── enterprise_properties_test.go
│       │   │   │   │   │   │       │   ├── enterprise_rules.go
│       │   │   │   │   │   │       │   ├── enterprise_rules_test.go
│       │   │   │   │   │   │       │   ├── event.go
│       │   │   │   │   │   │       │   ├── event_test.go
│       │   │   │   │   │   │       │   ├── event_types.go
│       │   │   │   │   │   │       │   ├── event_types_test.go
│       │   │   │   │   │   │       │   ├── examples_test.go
│       │   │   │   │   │   │       │   ├── gen-accessors.go
│       │   │   │   │   │   │       │   ├── gen-stringify-test.go
│       │   │   │   │   │   │       │   ├── gists_comments.go
│       │   │   │   │   │   │       │   ├── gists_comments_test.go
│       │   │   │   │   │   │       │   ├── gists.go
│       │   │   │   │   │   │       │   ├── gists_test.go
│       │   │   │   │   │   │       │   ├── git_blobs.go
│       │   │   │   │   │   │       │   ├── git_blobs_test.go
│       │   │   │   │   │   │       │   ├── git_commits.go
│       │   │   │   │   │   │       │   ├── git_commits_test.go
│       │   │   │   │   │   │       │   ├── git.go
│       │   │   │   │   │   │       │   ├── github-accessors.go
│       │   │   │   │   │   │       │   ├── github-accessors_test.go
│       │   │   │   │   │   │       │   ├── github.go
│       │   │   │   │   │   │       │   ├── github-stringify_test.go
│       │   │   │   │   │   │       │   ├── github_test.go
│       │   │   │   │   │   │       │   ├── gitignore.go
│       │   │   │   │   │   │       │   ├── gitignore_test.go
│       │   │   │   │   │   │       │   ├── git_refs.go
│       │   │   │   │   │   │       │   ├── git_refs_test.go
│       │   │   │   │   │   │       │   ├── git_tags.go
│       │   │   │   │   │   │       │   ├── git_tags_test.go
│       │   │   │   │   │   │       │   ├── git_trees.go
│       │   │   │   │   │   │       │   ├── git_trees_test.go
│       │   │   │   │   │   │       │   ├── interactions.go
│       │   │   │   │   │   │       │   ├── interactions_orgs.go
│       │   │   │   │   │   │       │   ├── interactions_orgs_test.go
│       │   │   │   │   │   │       │   ├── interactions_repos.go
│       │   │   │   │   │   │       │   ├── interactions_repos_test.go
│       │   │   │   │   │   │       │   ├── interactions_test.go
│       │   │   │   │   │   │       │   ├── issue_import.go
│       │   │   │   │   │   │       │   ├── issue_import_test.go
│       │   │   │   │   │   │       │   ├── issues_assignees.go
│       │   │   │   │   │   │       │   ├── issues_assignees_test.go
│       │   │   │   │   │   │       │   ├── issues_comments.go
│       │   │   │   │   │   │       │   ├── issues_comments_test.go
│       │   │   │   │   │   │       │   ├── issues_events.go
│       │   │   │   │   │   │       │   ├── issues_events_test.go
│       │   │   │   │   │   │       │   ├── issues.go
│       │   │   │   │   │   │       │   ├── issues_labels.go
│       │   │   │   │   │   │       │   ├── issues_labels_test.go
│       │   │   │   │   │   │       │   ├── issues_milestones.go
│       │   │   │   │   │   │       │   ├── issues_milestones_test.go
│       │   │   │   │   │   │       │   ├── issues_test.go
│       │   │   │   │   │   │       │   ├── issues_timeline.go
│       │   │   │   │   │   │       │   ├── issues_timeline_test.go
│       │   │   │   │   │   │       │   ├── licenses.go
│       │   │   │   │   │   │       │   ├── licenses_test.go
│       │   │   │   │   │   │       │   ├── markdown.go
│       │   │   │   │   │   │       │   ├── markdown_test.go
│       │   │   │   │   │   │       │   ├── messages.go
│       │   │   │   │   │   │       │   ├── messages_test.go
│       │   │   │   │   │   │       │   ├── meta.go
│       │   │   │   │   │   │       │   ├── meta_test.go
│       │   │   │   │   │   │       │   ├── migrations.go
│       │   │   │   │   │   │       │   ├── migrations_source_import.go
│       │   │   │   │   │   │       │   ├── migrations_source_import_test.go
│       │   │   │   │   │   │       │   ├── migrations_test.go
│       │   │   │   │   │   │       │   ├── migrations_user.go
│       │   │   │   │   │   │       │   ├── migrations_user_test.go
│       │   │   │   │   │   │       │   ├── orgs_actions_allowed.go
│       │   │   │   │   │   │       │   ├── orgs_actions_allowed_test.go
│       │   │   │   │   │   │       │   ├── orgs_actions_permissions.go
│       │   │   │   │   │   │       │   ├── orgs_actions_permissions_test.go
│       │   │   │   │   │   │       │   ├── orgs_attestations.go
│       │   │   │   │   │   │       │   ├── orgs_attestations_test.go
│       │   │   │   │   │   │       │   ├── orgs_audit_log.go
│       │   │   │   │   │   │       │   ├── orgs_audit_log_test.go
│       │   │   │   │   │   │       │   ├── orgs_codesecurity_configurations.go
│       │   │   │   │   │   │       │   ├── orgs_codesecurity_configurations_test.go
│       │   │   │   │   │   │       │   ├── orgs_credential_authorizations.go
│       │   │   │   │   │   │       │   ├── orgs_credential_authorizations_test.go
│       │   │   │   │   │   │       │   ├── orgs_custom_repository_roles.go
│       │   │   │   │   │   │       │   ├── orgs_custom_repository_roles_test.go
│       │   │   │   │   │   │       │   ├── orgs.go
│       │   │   │   │   │   │       │   ├── orgs_hooks_configuration.go
│       │   │   │   │   │   │       │   ├── orgs_hooks_configuration_test.go
│       │   │   │   │   │   │       │   ├── orgs_hooks_deliveries.go
│       │   │   │   │   │   │       │   ├── orgs_hooks_deliveries_test.go
│       │   │   │   │   │   │       │   ├── orgs_hooks.go
│       │   │   │   │   │   │       │   ├── orgs_hooks_test.go
│       │   │   │   │   │   │       │   ├── orgs_issue_types.go
│       │   │   │   │   │   │       │   ├── orgs_issue_types_test.go
│       │   │   │   │   │   │       │   ├── orgs_members.go
│       │   │   │   │   │   │       │   ├── orgs_members_test.go
│       │   │   │   │   │   │       │   ├── orgs_network_configurations.go
│       │   │   │   │   │   │       │   ├── orgs_network_configurations_test.go
│       │   │   │   │   │   │       │   ├── orgs_organization_roles.go
│       │   │   │   │   │   │       │   ├── orgs_organization_roles_test.go
│       │   │   │   │   │   │       │   ├── orgs_outside_collaborators.go
│       │   │   │   │   │   │       │   ├── orgs_outside_collaborators_test.go
│       │   │   │   │   │   │       │   ├── orgs_packages.go
│       │   │   │   │   │   │       │   ├── orgs_packages_test.go
│       │   │   │   │   │   │       │   ├── orgs_personal_access_tokens.go
│       │   │   │   │   │   │       │   ├── orgs_personal_access_tokens_test.go
│       │   │   │   │   │   │       │   ├── orgs_properties.go
│       │   │   │   │   │   │       │   ├── orgs_properties_test.go
│       │   │   │   │   │   │       │   ├── orgs_rules.go
│       │   │   │   │   │   │       │   ├── orgs_rules_test.go
│       │   │   │   │   │   │       │   ├── orgs_security_managers.go
│       │   │   │   │   │   │       │   ├── orgs_security_managers_test.go
│       │   │   │   │   │   │       │   ├── orgs_test.go
│       │   │   │   │   │   │       │   ├── orgs_users_blocking.go
│       │   │   │   │   │   │       │   ├── orgs_users_blocking_test.go
│       │   │   │   │   │   │       │   ├── packages.go
│       │   │   │   │   │   │       │   ├── packages_test.go
│       │   │   │   │   │   │       │   ├── pulls_comments.go
│       │   │   │   │   │   │       │   ├── pulls_comments_test.go
│       │   │   │   │   │   │       │   ├── pulls.go
│       │   │   │   │   │   │       │   ├── pulls_reviewers.go
│       │   │   │   │   │   │       │   ├── pulls_reviewers_test.go
│       │   │   │   │   │   │       │   ├── pulls_reviews.go
│       │   │   │   │   │   │       │   ├── pulls_reviews_test.go
│       │   │   │   │   │   │       │   ├── pulls_test.go
│       │   │   │   │   │   │       │   ├── pulls_threads.go
│       │   │   │   │   │   │       │   ├── pulls_threads_test.go
│       │   │   │   │   │   │       │   ├── rate_limit.go
│       │   │   │   │   │   │       │   ├── rate_limit_test.go
│       │   │   │   │   │   │       │   ├── reactions.go
│       │   │   │   │   │   │       │   ├── reactions_test.go
│       │   │   │   │   │   │       │   ├── repos_actions_access.go
│       │   │   │   │   │   │       │   ├── repos_actions_access_test.go
│       │   │   │   │   │   │       │   ├── repos_actions_allowed.go
│       │   │   │   │   │   │       │   ├── repos_actions_allowed_test.go
│       │   │   │   │   │   │       │   ├── repos_actions_permissions.go
│       │   │   │   │   │   │       │   ├── repos_actions_permissions_test.go
│       │   │   │   │   │   │       │   ├── repos_attestations.go
│       │   │   │   │   │   │       │   ├── repos_attestations_test.go
│       │   │   │   │   │   │       │   ├── repos_autolinks.go
│       │   │   │   │   │   │       │   ├── repos_autolinks_test.go
│       │   │   │   │   │   │       │   ├── repos_codeowners.go
│       │   │   │   │   │   │       │   ├── repos_codeowners_test.go
│       │   │   │   │   │   │       │   ├── repos_collaborators.go
│       │   │   │   │   │   │       │   ├── repos_collaborators_test.go
│       │   │   │   │   │   │       │   ├── repos_comments.go
│       │   │   │   │   │   │       │   ├── repos_comments_test.go
│       │   │   │   │   │   │       │   ├── repos_commits.go
│       │   │   │   │   │   │       │   ├── repos_commits_test.go
│       │   │   │   │   │   │       │   ├── repos_community_health.go
│       │   │   │   │   │   │       │   ├── repos_community_health_test.go
│       │   │   │   │   │   │       │   ├── repos_contents.go
│       │   │   │   │   │   │       │   ├── repos_contents_test.go
│       │   │   │   │   │   │       │   ├── repos_deployment_branch_policies.go
│       │   │   │   │   │   │       │   ├── repos_deployment_branch_policies_test.go
│       │   │   │   │   │   │       │   ├── repos_deployment_protection_rules.go
│       │   │   │   │   │   │       │   ├── repos_deployment_protection_rules_test.go
│       │   │   │   │   │   │       │   ├── repos_deployments.go
│       │   │   │   │   │   │       │   ├── repos_deployments_test.go
│       │   │   │   │   │   │       │   ├── repos_environments.go
│       │   │   │   │   │   │       │   ├── repos_environments_test.go
│       │   │   │   │   │   │       │   ├── repos_forks.go
│       │   │   │   │   │   │       │   ├── repos_forks_test.go
│       │   │   │   │   │   │       │   ├── repos.go
│       │   │   │   │   │   │       │   ├── repos_hooks_configuration.go
│       │   │   │   │   │   │       │   ├── repos_hooks_configuration_test.go
│       │   │   │   │   │   │       │   ├── repos_hooks_deliveries.go
│       │   │   │   │   │   │       │   ├── repos_hooks_deliveries_test.go
│       │   │   │   │   │   │       │   ├── repos_hooks.go
│       │   │   │   │   │   │       │   ├── repos_hooks_test.go
│       │   │   │   │   │   │       │   ├── repos_invitations.go
│       │   │   │   │   │   │       │   ├── repos_invitations_test.go
│       │   │   │   │   │   │       │   ├── repos_keys.go
│       │   │   │   │   │   │       │   ├── repos_keys_test.go
│       │   │   │   │   │   │       │   ├── repos_lfs.go
│       │   │   │   │   │   │       │   ├── repos_lfs_test.go
│       │   │   │   │   │   │       │   ├── repos_merging.go
│       │   │   │   │   │   │       │   ├── repos_merging_test.go
│       │   │   │   │   │   │       │   ├── repos_pages.go
│       │   │   │   │   │   │       │   ├── repos_pages_test.go
│       │   │   │   │   │   │       │   ├── repos_prereceive_hooks.go
│       │   │   │   │   │   │       │   ├── repos_prereceive_hooks_test.go
│       │   │   │   │   │   │       │   ├── repos_properties.go
│       │   │   │   │   │   │       │   ├── repos_properties_test.go
│       │   │   │   │   │   │       │   ├── repos_releases.go
│       │   │   │   │   │   │       │   ├── repos_releases_test.go
│       │   │   │   │   │   │       │   ├── repos_rules.go
│       │   │   │   │   │   │       │   ├── repos_rules_test.go
│       │   │   │   │   │   │       │   ├── repos_stats.go
│       │   │   │   │   │   │       │   ├── repos_stats_test.go
│       │   │   │   │   │   │       │   ├── repos_statuses.go
│       │   │   │   │   │   │       │   ├── repos_statuses_test.go
│       │   │   │   │   │   │       │   ├── repos_tags.go
│       │   │   │   │   │   │       │   ├── repos_tags_test.go
│       │   │   │   │   │   │       │   ├── repos_test.go
│       │   │   │   │   │   │       │   ├── repos_traffic.go
│       │   │   │   │   │   │       │   ├── repos_traffic_test.go
│       │   │   │   │   │   │       │   ├── rules.go
│       │   │   │   │   │   │       │   ├── rules_test.go
│       │   │   │   │   │   │       │   ├── scim.go
│       │   │   │   │   │   │       │   ├── scim_test.go
│       │   │   │   │   │   │       │   ├── search.go
│       │   │   │   │   │   │       │   ├── search_test.go
│       │   │   │   │   │   │       │   ├── secret_scanning.go
│       │   │   │   │   │   │       │   ├── secret_scanning_test.go
│       │   │   │   │   │   │       │   ├── security_advisories.go
│       │   │   │   │   │   │       │   ├── security_advisories_test.go
│       │   │   │   │   │   │       │   ├── strings.go
│       │   │   │   │   │   │       │   ├── strings_test.go
│       │   │   │   │   │   │       │   ├── teams_discussion_comments.go
│       │   │   │   │   │   │       │   ├── teams_discussion_comments_test.go
│       │   │   │   │   │   │       │   ├── teams_discussions.go
│       │   │   │   │   │   │       │   ├── teams_discussions_test.go
│       │   │   │   │   │   │       │   ├── teams.go
│       │   │   │   │   │   │       │   ├── teams_members.go
│       │   │   │   │   │   │       │   ├── teams_members_test.go
│       │   │   │   │   │   │       │   ├── teams_test.go
│       │   │   │   │   │   │       │   ├── timestamp.go
│       │   │   │   │   │   │       │   ├── timestamp_test.go
│       │   │   │   │   │   │       │   ├── users_administration.go
│       │   │   │   │   │   │       │   ├── users_administration_test.go
│       │   │   │   │   │   │       │   ├── users_attestations.go
│       │   │   │   │   │   │       │   ├── users_attestations_test.go
│       │   │   │   │   │   │       │   ├── users_blocking.go
│       │   │   │   │   │   │       │   ├── users_blocking_test.go
│       │   │   │   │   │   │       │   ├── users_emails.go
│       │   │   │   │   │   │       │   ├── users_emails_test.go
│       │   │   │   │   │   │       │   ├── users_followers.go
│       │   │   │   │   │   │       │   ├── users_followers_test.go
│       │   │   │   │   │   │       │   ├── users.go
│       │   │   │   │   │   │       │   ├── users_gpg_keys.go
│       │   │   │   │   │   │       │   ├── users_gpg_keys_test.go
│       │   │   │   │   │   │       │   ├── users_keys.go
│       │   │   │   │   │   │       │   ├── users_keys_test.go
│       │   │   │   │   │   │       │   ├── users_packages.go
│       │   │   │   │   │   │       │   ├── users_packages_test.go
│       │   │   │   │   │   │       │   ├── users_ssh_signing_keys.go
│       │   │   │   │   │   │       │   ├── users_ssh_signing_keys_test.go
│       │   │   │   │   │   │       │   ├── users_test.go
│       │   │   │   │   │   │       │   ├── with_appengine.go
│       │   │   │   │   │   │       │   └── without_appengine.go
│       │   │   │   │   │   │       ├── go.mod
│       │   │   │   │   │   │       ├── go.sum
│       │   │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │   │       ├── openapi_operations.yaml
│       │   │   │   │   │   │       ├── README.md
│       │   │   │   │   │   │       ├── REVIEWERS
│       │   │   │   │   │   │       ├── script
│       │   │   │   │   │   │       │   ├── fmt.sh
│       │   │   │   │   │   │       │   ├── generate.sh
│       │   │   │   │   │   │       │   ├── lint.sh
│       │   │   │   │   │   │       │   ├── metadata.sh
│       │   │   │   │   │   │       │   └── test.sh
│       │   │   │   │   │   │       └── test
│       │   │   │   │   │   │           ├── fields
│       │   │   │   │   │   │           │   └── fields.go
│       │   │   │   │   │   │           ├── integration
│       │   │   │   │   │   │           │   ├── activity_test.go
│       │   │   │   │   │   │           │   ├── audit_log_test.go
│       │   │   │   │   │   │           │   ├── authorizations_test.go
│       │   │   │   │   │   │           │   ├── doc.go
│       │   │   │   │   │   │           │   ├── github_test.go
│       │   │   │   │   │   │           │   ├── issues_test.go
│       │   │   │   │   │   │           │   ├── misc_test.go
│       │   │   │   │   │   │           │   ├── pulls_test.go
│       │   │   │   │   │   │           │   ├── repos_test.go
│       │   │   │   │   │   │           │   └── users_test.go
│       │   │   │   │   │   │           └── README.md
│       │   │   │   │   │   ├── go-querystring@v1.1.0
│       │   │   │   │   │   │   ├── CONTRIBUTING.md
│       │   │   │   │   │   │   ├── go.mod
│       │   │   │   │   │   │   ├── go.sum
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── query
│       │   │   │   │   │   │   │   ├── encode.go
│       │   │   │   │   │   │   │   └── encode_test.go
│       │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   └── uuid@v1.6.0
│       │   │   │   │   │       ├── CHANGELOG.md
│       │   │   │   │   │       ├── CONTRIBUTING.md
│       │   │   │   │   │       ├── CONTRIBUTORS
│       │   │   │   │   │       ├── dce.go
│       │   │   │   │   │       ├── doc.go
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── hash.go
│       │   │   │   │   │       ├── json_test.go
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── marshal.go
│       │   │   │   │   │       ├── node.go
│       │   │   │   │   │       ├── node_js.go
│       │   │   │   │   │       ├── node_net.go
│       │   │   │   │   │       ├── null.go
│       │   │   │   │   │       ├── null_test.go
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       ├── seq_test.go
│       │   │   │   │   │       ├── sql.go
│       │   │   │   │   │       ├── sql_test.go
│       │   │   │   │   │       ├── time.go
│       │   │   │   │   │       ├── util.go
│       │   │   │   │   │       ├── uuid.go
│       │   │   │   │   │       ├── uuid_test.go
│       │   │   │   │   │       ├── version1.go
│       │   │   │   │   │       ├── version4.go
│       │   │   │   │   │       ├── version6.go
│       │   │   │   │   │       └── version7.go
│       │   │   │   │   ├── gorilla
│       │   │   │   │   │   └── mux@v1.8.0
│       │   │   │   │   │       ├── AUTHORS
│       │   │   │   │   │       ├── bench_test.go
│       │   │   │   │   │       ├── doc.go
│       │   │   │   │   │       ├── example_authentication_middleware_test.go
│       │   │   │   │   │       ├── example_cors_method_middleware_test.go
│       │   │   │   │   │       ├── example_route_test.go
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── middleware.go
│       │   │   │   │   │       ├── middleware_test.go
│       │   │   │   │   │       ├── mux.go
│       │   │   │   │   │       ├── mux_httpserver_test.go
│       │   │   │   │   │       ├── mux_test.go
│       │   │   │   │   │       ├── old_test.go
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       ├── regexp.go
│       │   │   │   │   │       ├── regexp_test.go
│       │   │   │   │   │       ├── route.go
│       │   │   │   │   │       └── test_helpers.go
│       │   │   │   │   ├── go-viper
│       │   │   │   │   │   └── mapstructure
│       │   │   │   │   │       └── v2@v2.3.0
│       │   │   │   │   │           ├── CHANGELOG.md
│       │   │   │   │   │           ├── decode_hooks.go
│       │   │   │   │   │           ├── decode_hooks_test.go
│       │   │   │   │   │           ├── errors.go
│       │   │   │   │   │           ├── flake.lock
│       │   │   │   │   │           ├── flake.nix
│       │   │   │   │   │           ├── go.mod
│       │   │   │   │   │           ├── internal
│       │   │   │   │   │           │   └── errors
│       │   │   │   │   │           │       ├── errors.go
│       │   │   │   │   │           │       ├── join.go
│       │   │   │   │   │           │       └── join_go1_19.go
│       │   │   │   │   │           ├── LICENSE
│       │   │   │   │   │           ├── mapstructure_benchmark_test.go
│       │   │   │   │   │           ├── mapstructure_bugs_test.go
│       │   │   │   │   │           ├── mapstructure_examples_test.go
│       │   │   │   │   │           ├── mapstructure.go
│       │   │   │   │   │           ├── mapstructure_test.go
│       │   │   │   │   │           ├── README.md
│       │   │   │   │   │           ├── reflect_go1_19.go
│       │   │   │   │   │           └── reflect_go1_20.go
│       │   │   │   │   ├── mark3labs
│       │   │   │   │   │   └── mcp-go@v0.32.0
│       │   │   │   │   │       ├── client
│       │   │   │   │   │       │   ├── client.go
│       │   │   │   │   │       │   ├── http.go
│       │   │   │   │   │       │   ├── http_test.go
│       │   │   │   │   │       │   ├── inprocess.go
│       │   │   │   │   │       │   ├── inprocess_test.go
│       │   │   │   │   │       │   ├── interface.go
│       │   │   │   │   │       │   ├── oauth.go
│       │   │   │   │   │       │   ├── oauth_test.go
│       │   │   │   │   │       │   ├── sse.go
│       │   │   │   │   │       │   ├── sse_test.go
│       │   │   │   │   │       │   ├── stdio.go
│       │   │   │   │   │       │   ├── stdio_test.go
│       │   │   │   │   │       │   └── transport
│       │   │   │   │   │       │       ├── inprocess.go
│       │   │   │   │   │       │       ├── interface.go
│       │   │   │   │   │       │       ├── oauth.go
│       │   │   │   │   │       │       ├── oauth_test.go
│       │   │   │   │   │       │       ├── oauth_utils.go
│       │   │   │   │   │       │       ├── oauth_utils_test.go
│       │   │   │   │   │       │       ├── sse.go
│       │   │   │   │   │       │       ├── sse_oauth_test.go
│       │   │   │   │   │       │       ├── sse_test.go
│       │   │   │   │   │       │       ├── stdio.go
│       │   │   │   │   │       │       ├── stdio_test.go
│       │   │   │   │   │       │       ├── streamable_http.go
│       │   │   │   │   │       │       ├── streamable_http_oauth_test.go
│       │   │   │   │   │       │       └── streamable_http_test.go
│       │   │   │   │   │       ├── CODE_OF_CONDUCT.md
│       │   │   │   │   │       ├── CONTRIBUTING.md
│       │   │   │   │   │       ├── examples
│       │   │   │   │   │       │   ├── custom_context
│       │   │   │   │   │       │   │   └── main.go
│       │   │   │   │   │       │   ├── dynamic_path
│       │   │   │   │   │       │   │   └── main.go
│       │   │   │   │   │       │   ├── everything
│       │   │   │   │   │       │   │   └── main.go
│       │   │   │   │   │       │   ├── filesystem_stdio_client
│       │   │   │   │   │       │   │   └── main.go
│       │   │   │   │   │       │   ├── oauth_client
│       │   │   │   │   │       │   │   ├── main.go
│       │   │   │   │   │       │   │   └── README.md
│       │   │   │   │   │       │   ├── simple_client
│       │   │   │   │   │       │   │   └── main.go
│       │   │   │   │   │       │   └── typed_tools
│       │   │   │   │   │       │       └── main.go
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── go.sum
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── logo.png
│       │   │   │   │   │       ├── mcp
│       │   │   │   │   │       │   ├── prompts.go
│       │   │   │   │   │       │   ├── resources.go
│       │   │   │   │   │       │   ├── tools.go
│       │   │   │   │   │       │   ├── tools_test.go
│       │   │   │   │   │       │   ├── typed_tools.go
│       │   │   │   │   │       │   ├── typed_tools_test.go
│       │   │   │   │   │       │   ├── types.go
│       │   │   │   │   │       │   ├── types_test.go
│       │   │   │   │   │       │   └── utils.go
│       │   │   │   │   │       ├── mcptest
│       │   │   │   │   │       │   ├── mcptest.go
│       │   │   │   │   │       │   └── mcptest_test.go
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       ├── SECURITY.md
│       │   │   │   │   │       ├── server
│       │   │   │   │   │       │   ├── errors.go
│       │   │   │   │   │       │   ├── hooks.go
│       │   │   │   │   │       │   ├── http_transport_options.go
│       │   │   │   │   │       │   ├── internal
│       │   │   │   │   │       │   │   └── gen
│       │   │   │   │   │       │   │       ├── data.go
│       │   │   │   │   │       │   │       ├── hooks.go.tmpl
│       │   │   │   │   │       │   │       ├── main.go
│       │   │   │   │   │       │   │       ├── README.md
│       │   │   │   │   │       │   │       └── request_handler.go.tmpl
│       │   │   │   │   │       │   ├── request_handler.go
│       │   │   │   │   │       │   ├── resource_test.go
│       │   │   │   │   │       │   ├── server.go
│       │   │   │   │   │       │   ├── server_race_test.go
│       │   │   │   │   │       │   ├── server_test.go
│       │   │   │   │   │       │   ├── session.go
│       │   │   │   │   │       │   ├── session_test.go
│       │   │   │   │   │       │   ├── sse.go
│       │   │   │   │   │       │   ├── sse_test.go
│       │   │   │   │   │       │   ├── stdio.go
│       │   │   │   │   │       │   ├── stdio_test.go
│       │   │   │   │   │       │   ├── streamable_http.go
│       │   │   │   │   │       │   └── streamable_http_test.go
│       │   │   │   │   │       ├── testdata
│       │   │   │   │   │       │   └── mockstdio_server.go
│       │   │   │   │   │       ├── util
│       │   │   │   │   │       │   └── logger.go
│       │   │   │   │   │       └── www
│       │   │   │   │   │           ├── bun.lock
│       │   │   │   │   │           ├── docs
│       │   │   │   │   │           │   ├── pages
│       │   │   │   │   │           │   │   ├── clients
│       │   │   │   │   │           │   │   │   ├── basics.mdx
│       │   │   │   │   │           │   │   │   ├── index.mdx
│       │   │   │   │   │           │   │   │   ├── operations.mdx
│       │   │   │   │   │           │   │   │   └── transports.mdx
│       │   │   │   │   │           │   │   ├── core-concepts.mdx
│       │   │   │   │   │           │   │   ├── getting-started.mdx
│       │   │   │   │   │           │   │   ├── index.mdx
│       │   │   │   │   │           │   │   ├── quick-start.mdx
│       │   │   │   │   │           │   │   ├── servers
│       │   │   │   │   │           │   │   │   ├── advanced.mdx
│       │   │   │   │   │           │   │   │   ├── basics.mdx
│       │   │   │   │   │           │   │   │   ├── index.mdx
│       │   │   │   │   │           │   │   │   ├── prompts.mdx
│       │   │   │   │   │           │   │   │   ├── resources.mdx
│       │   │   │   │   │           │   │   │   └── tools.mdx
│       │   │   │   │   │           │   │   └── transports
│       │   │   │   │   │           │   │       ├── http.mdx
│       │   │   │   │   │           │   │       ├── index.mdx
│       │   │   │   │   │           │   │       ├── inprocess.mdx
│       │   │   │   │   │           │   │       ├── sse.mdx
│       │   │   │   │   │           │   │       └── stdio.mdx
│       │   │   │   │   │           │   ├── public
│       │   │   │   │   │           │   │   └── logo.png
│       │   │   │   │   │           │   └── styles.css
│       │   │   │   │   │           ├── package.json
│       │   │   │   │   │           ├── README.md
│       │   │   │   │   │           ├── tsconfig.json
│       │   │   │   │   │           └── vocs.config.ts
│       │   │   │   │   ├── migueleliasweb
│       │   │   │   │   │   └── go-github-mock@v1.3.0
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── go.sum
│       │   │   │   │   │       ├── hack
│       │   │   │   │   │       │   └── gen.sh
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── main.go
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       └── src
│       │   │   │   │   │           ├── gen
│       │   │   │   │   │           │   ├── gen.go
│       │   │   │   │   │           │   ├── gen_mutations.go
│       │   │   │   │   │           │   └── gen_test.go
│       │   │   │   │   │           └── mock
│       │   │   │   │   │               ├── endpointpattern.go
│       │   │   │   │   │               ├── endpointpattern_test.go
│       │   │   │   │   │               ├── server.go
│       │   │   │   │   │               ├── server_options_external_test.go
│       │   │   │   │   │               ├── server_options.go
│       │   │   │   │   │               ├── server_options_test.go
│       │   │   │   │   │               ├── server_test.go
│       │   │   │   │   │               └── utils.go
│       │   │   │   │   ├── pelletier
│       │   │   │   │   │   └── go-toml
│       │   │   │   │   │       └── v2@v2.2.3
│       │   │   │   │   │           ├── benchmark
│       │   │   │   │   │           │   ├── bench_datasets_test.go
│       │   │   │   │   │           │   ├── benchmark_test.go
│       │   │   │   │   │           │   ├── benchmark.toml
│       │   │   │   │   │           │   └── testdata
│       │   │   │   │   │           │       ├── canada.toml.gz
│       │   │   │   │   │           │       ├── citm_catalog.toml.gz
│       │   │   │   │   │           │       ├── code.toml.gz
│       │   │   │   │   │           │       ├── config.toml.gz
│       │   │   │   │   │           │       ├── example.toml.gz
│       │   │   │   │   │           │       └── twitter.toml.gz
│       │   │   │   │   │           ├── ci.sh
│       │   │   │   │   │           ├── cmd
│       │   │   │   │   │           │   ├── gotoml-test-decoder
│       │   │   │   │   │           │   │   └── main.go
│       │   │   │   │   │           │   ├── gotoml-test-encoder
│       │   │   │   │   │           │   │   └── gotoml-test-encoder.go
│       │   │   │   │   │           │   ├── jsontoml
│       │   │   │   │   │           │   │   ├── main.go
│       │   │   │   │   │           │   │   └── main_test.go
│       │   │   │   │   │           │   ├── tomljson
│       │   │   │   │   │           │   │   ├── main.go
│       │   │   │   │   │           │   │   └── main_test.go
│       │   │   │   │   │           │   ├── tomll
│       │   │   │   │   │           │   │   ├── main.go
│       │   │   │   │   │           │   │   └── main_test.go
│       │   │   │   │   │           │   └── tomltestgen
│       │   │   │   │   │           │       └── main.go
│       │   │   │   │   │           ├── CONTRIBUTING.md
│       │   │   │   │   │           ├── decode.go
│       │   │   │   │   │           ├── doc.go
│       │   │   │   │   │           ├── Dockerfile
│       │   │   │   │   │           ├── errors.go
│       │   │   │   │   │           ├── errors_test.go
│       │   │   │   │   │           ├── example_text_marshaling_test.go
│       │   │   │   │   │           ├── fast_test.go
│       │   │   │   │   │           ├── fuzz_test.go
│       │   │   │   │   │           ├── go.mod
│       │   │   │   │   │           ├── go.sum
│       │   │   │   │   │           ├── internal
│       │   │   │   │   │           │   ├── characters
│       │   │   │   │   │           │   │   ├── ascii.go
│       │   │   │   │   │           │   │   └── utf8.go
│       │   │   │   │   │           │   ├── cli
│       │   │   │   │   │           │   │   ├── cli.go
│       │   │   │   │   │           │   │   └── cli_test.go
│       │   │   │   │   │           │   ├── danger
│       │   │   │   │   │           │   │   ├── danger.go
│       │   │   │   │   │           │   │   ├── danger_test.go
│       │   │   │   │   │           │   │   └── typeid.go
│       │   │   │   │   │           │   ├── imported_tests
│       │   │   │   │   │           │   │   ├── marshal_imported_test.go
│       │   │   │   │   │           │   │   └── unmarshal_imported_test.go
│       │   │   │   │   │           │   ├── testsuite
│       │   │   │   │   │           │   │   ├── add.go
│       │   │   │   │   │           │   │   ├── json.go
│       │   │   │   │   │           │   │   ├── parser.go
│       │   │   │   │   │           │   │   ├── rm.go
│       │   │   │   │   │           │   │   └── testsuite.go
│       │   │   │   │   │           │   └── tracker
│       │   │   │   │   │           │       ├── key.go
│       │   │   │   │   │           │       ├── seen.go
│       │   │   │   │   │           │       ├── seen_test.go
│       │   │   │   │   │           │       └── tracker.go
│       │   │   │   │   │           ├── LICENSE
│       │   │   │   │   │           ├── localtime.go
│       │   │   │   │   │           ├── localtime_test.go
│       │   │   │   │   │           ├── marshaler.go
│       │   │   │   │   │           ├── marshaler_test.go
│       │   │   │   │   │           ├── ossfuzz
│       │   │   │   │   │           │   └── fuzz.go
│       │   │   │   │   │           ├── README.md
│       │   │   │   │   │           ├── SECURITY.md
│       │   │   │   │   │           ├── strict.go
│       │   │   │   │   │           ├── testdata
│       │   │   │   │   │           │   └── fuzz
│       │   │   │   │   │           │       └── FuzzUnmarshal
│       │   │   │   │   │           │           ├── 0c08b924aa26af23d16b77029b4f5567a96af93402e0472fef7b837b37580d7c
│       │   │   │   │   │           │           ├── 249a017d8ffa0d88d41c594ada5399f764833f64050180cb39f106d12666853f
│       │   │   │   │   │           │           ├── 391ce67b866d58464d067c5981e99951fd499896453a2fe2779a6bfe7df11bf5
│       │   │   │   │   │           │           ├── 49ae83283c5cfbed874bcacbfb342de107b69c2a3d3c35c2d99f67345fe89946
│       │   │   │   │   │           │           ├── 69ea82e85bb4ad966ae86bb05eea3af69ed1a826c846f1bf2282f329b4d8fb36
│       │   │   │   │   │           │           ├── 746910fac6deb42e7e62dce60b333c81c39d844a122c9075894c023400e8fdbf
│       │   │   │   │   │           │           ├── 844d1171a3adc95e51627f0e9378bbaa193fe2d0284f4ba8ed19a5226a8cbc74
│       │   │   │   │   │           │           ├── 900c54b5071113ae2a5365b3156377ddd775b9d38add61629544903cb9c94b00
│       │   │   │   │   │           │           ├── c87e8eb4e8fa40fd3c89d8ed16a049ce81592ded710965ee29a4e506eb5427b3
│       │   │   │   │   │           │           ├── d0e5d6fc3b865cfae5480c01f301b87c932722ae0c1d692deea413349ea028be
│       │   │   │   │   │           │           └── d2cecea5b8ee5f148419671cef0644178cdba1ee91d3f295be38da576e89ef40
│       │   │   │   │   │           ├── toml.abnf
│       │   │   │   │   │           ├── toml_testgen_support_test.go
│       │   │   │   │   │           ├── toml_testgen_test.go
│       │   │   │   │   │           ├── types.go
│       │   │   │   │   │           ├── unmarshaler.go
│       │   │   │   │   │           ├── unmarshaler_test.go
│       │   │   │   │   │           └── unstable
│       │   │   │   │   │               ├── ast.go
│       │   │   │   │   │               ├── benchmark_test.go
│       │   │   │   │   │               ├── builder.go
│       │   │   │   │   │               ├── doc.go
│       │   │   │   │   │               ├── kind.go
│       │   │   │   │   │               ├── parser.go
│       │   │   │   │   │               ├── parser_test.go
│       │   │   │   │   │               ├── scanner.go
│       │   │   │   │   │               └── unmarshaler.go
│       │   │   │   │   ├── sagikazarmark
│       │   │   │   │   │   └── locafero@v0.9.0
│       │   │   │   │   │       ├── example_unix_test.go
│       │   │   │   │   │       ├── example_windows_test.go
│       │   │   │   │   │       ├── file_type.go
│       │   │   │   │   │       ├── finder.go
│       │   │   │   │   │       ├── finder_test.go
│       │   │   │   │   │       ├── flake.lock
│       │   │   │   │   │       ├── flake.nix
│       │   │   │   │   │       ├── glob.go
│       │   │   │   │   │       ├── glob_windows.go
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── go.sum
│       │   │   │   │   │       ├── helpers.go
│       │   │   │   │   │       ├── justfile
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       └── testdata
│       │   │   │   │   │           ├── etc
│       │   │   │   │   │           │   └── config.yaml
│       │   │   │   │   │           └── home
│       │   │   │   │   │               └── user
│       │   │   │   │   │                   └── config.yaml
│       │   │   │   │   ├── shurcoo!l
│       │   │   │   │   │   ├── githubv4@v0.0.0-20240727222349-48295856cce7
│       │   │   │   │   │   │   ├── doc.go
│       │   │   │   │   │   │   ├── enum.go
│       │   │   │   │   │   │   ├── example
│       │   │   │   │   │   │   │   └── githubv4dev
│       │   │   │   │   │   │   │       └── main.go
│       │   │   │   │   │   │   ├── example_test.go
│       │   │   │   │   │   │   ├── gen.go
│       │   │   │   │   │   │   ├── githubv4.go
│       │   │   │   │   │   │   ├── githubv4_test.go
│       │   │   │   │   │   │   ├── go.mod
│       │   │   │   │   │   │   ├── input.go
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── scalar.go
│       │   │   │   │   │   │   └── scalar_test.go
│       │   │   │   │   │   └── graphql@v0.0.0-20230722043721-ed46e5a46466
│       │   │   │   │   │       ├── doc.go
│       │   │   │   │   │       ├── example
│       │   │   │   │   │       │   └── graphqldev
│       │   │   │   │   │       │       └── main.go
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── graphql.go
│       │   │   │   │   │       ├── graphql_test.go
│       │   │   │   │   │       ├── ident
│       │   │   │   │   │       │   ├── ident.go
│       │   │   │   │   │       │   └── ident_test.go
│       │   │   │   │   │       ├── internal
│       │   │   │   │   │       │   └── jsonutil
│       │   │   │   │   │       │       ├── benchmark_test.go
│       │   │   │   │   │       │       ├── graphql.go
│       │   │   │   │   │       │       └── graphql_test.go
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── query.go
│       │   │   │   │   │       ├── query_test.go
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       ├── scalar.go
│       │   │   │   │   │       └── scalar_test.go
│       │   │   │   │   ├── sirupsen
│       │   │   │   │   │   └── logrus@v1.9.3
│       │   │   │   │   │       ├── alt_exit.go
│       │   │   │   │   │       ├── alt_exit_test.go
│       │   │   │   │   │       ├── appveyor.yml
│       │   │   │   │   │       ├── buffer_pool.go
│       │   │   │   │   │       ├── CHANGELOG.md
│       │   │   │   │   │       ├── doc.go
│       │   │   │   │   │       ├── entry.go
│       │   │   │   │   │       ├── entry_test.go
│       │   │   │   │   │       ├── example_basic_test.go
│       │   │   │   │   │       ├── example_custom_caller_test.go
│       │   │   │   │   │       ├── example_default_field_value_test.go
│       │   │   │   │   │       ├── example_function_test.go
│       │   │   │   │   │       ├── example_global_hook_test.go
│       │   │   │   │   │       ├── example_hook_test.go
│       │   │   │   │   │       ├── exported.go
│       │   │   │   │   │       ├── formatter_bench_test.go
│       │   │   │   │   │       ├── formatter.go
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── go.sum
│       │   │   │   │   │       ├── hooks
│       │   │   │   │   │       │   ├── syslog
│       │   │   │   │   │       │   │   ├── README.md
│       │   │   │   │   │       │   │   ├── syslog.go
│       │   │   │   │   │       │   │   └── syslog_test.go
│       │   │   │   │   │       │   ├── test
│       │   │   │   │   │       │   │   ├── test.go
│       │   │   │   │   │       │   │   └── test_test.go
│       │   │   │   │   │       │   └── writer
│       │   │   │   │   │       │       ├── README.md
│       │   │   │   │   │       │       ├── writer.go
│       │   │   │   │   │       │       └── writer_test.go
│       │   │   │   │   │       ├── hooks.go
│       │   │   │   │   │       ├── hook_test.go
│       │   │   │   │   │       ├── internal
│       │   │   │   │   │       │   └── testutils
│       │   │   │   │   │       │       └── testutils.go
│       │   │   │   │   │       ├── json_formatter.go
│       │   │   │   │   │       ├── json_formatter_test.go
│       │   │   │   │   │       ├── level_test.go
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── logger_bench_test.go
│       │   │   │   │   │       ├── logger.go
│       │   │   │   │   │       ├── logger_test.go
│       │   │   │   │   │       ├── logrus.go
│       │   │   │   │   │       ├── logrus_test.go
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       ├── terminal_check_appengine.go
│       │   │   │   │   │       ├── terminal_check_bsd.go
│       │   │   │   │   │       ├── terminal_check_js.go
│       │   │   │   │   │       ├── terminal_check_notappengine.go
│       │   │   │   │   │       ├── terminal_check_no_terminal.go
│       │   │   │   │   │       ├── terminal_check_solaris.go
│       │   │   │   │   │       ├── terminal_check_unix.go
│       │   │   │   │   │       ├── terminal_check_windows.go
│       │   │   │   │   │       ├── text_formatter.go
│       │   │   │   │   │       ├── text_formatter_test.go
│       │   │   │   │   │       ├── travis
│       │   │   │   │   │       │   ├── cross_build.sh
│       │   │   │   │   │       │   └── install.sh
│       │   │   │   │   │       ├── writer.go
│       │   │   │   │   │       └── writer_test.go
│       │   │   │   │   ├── sourcegraph
│       │   │   │   │   │   └── conc@v0.3.0
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── go.sum
│       │   │   │   │   │       ├── internal
│       │   │   │   │   │       │   └── multierror
│       │   │   │   │   │       │       ├── multierror_go119.go
│       │   │   │   │   │       │       └── multierror_go120.go
│       │   │   │   │   │       ├── iter
│       │   │   │   │   │       │   ├── iter.go
│       │   │   │   │   │       │   ├── iter_test.go
│       │   │   │   │   │       │   ├── map.go
│       │   │   │   │   │       │   └── map_test.go
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── panics
│       │   │   │   │   │       │   ├── panics.go
│       │   │   │   │   │       │   ├── panics_test.go
│       │   │   │   │   │       │   ├── try.go
│       │   │   │   │   │       │   └── try_test.go
│       │   │   │   │   │       ├── pool
│       │   │   │   │   │       │   ├── context_pool.go
│       │   │   │   │   │       │   ├── context_pool_test.go
│       │   │   │   │   │       │   ├── error_pool.go
│       │   │   │   │   │       │   ├── error_pool_test.go
│       │   │   │   │   │       │   ├── pool.go
│       │   │   │   │   │       │   ├── pool_test.go
│       │   │   │   │   │       │   ├── result_context_pool.go
│       │   │   │   │   │       │   ├── result_context_pool_test.go
│       │   │   │   │   │       │   ├── result_error_pool.go
│       │   │   │   │   │       │   ├── result_error_pool_test.go
│       │   │   │   │   │       │   ├── result_pool.go
│       │   │   │   │   │       │   └── result_pool_test.go
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       ├── stream
│       │   │   │   │   │       │   ├── stream.go
│       │   │   │   │   │       │   └── stream_test.go
│       │   │   │   │   │       ├── waitgroup.go
│       │   │   │   │   │       └── waitgroup_test.go
│       │   │   │   │   ├── spf13
│       │   │   │   │   │   ├── afero@v1.14.0
│       │   │   │   │   │   │   ├── afero.go
│       │   │   │   │   │   │   ├── afero_test.go
│       │   │   │   │   │   │   ├── appveyor.yml
│       │   │   │   │   │   │   ├── basepath.go
│       │   │   │   │   │   │   ├── basepath_test.go
│       │   │   │   │   │   │   ├── cacheOnReadFs.go
│       │   │   │   │   │   │   ├── composite_test.go
│       │   │   │   │   │   │   ├── const_bsds.go
│       │   │   │   │   │   │   ├── const_win_unix.go
│       │   │   │   │   │   │   ├── copyOnWriteFs.go
│       │   │   │   │   │   │   ├── copyOnWriteFs_test.go
│       │   │   │   │   │   │   ├── go.mod
│       │   │   │   │   │   │   ├── go.sum
│       │   │   │   │   │   │   ├── httpFs.go
│       │   │   │   │   │   │   ├── internal
│       │   │   │   │   │   │   │   └── common
│       │   │   │   │   │   │   │       └── adapters.go
│       │   │   │   │   │   │   ├── iofs.go
│       │   │   │   │   │   │   ├── iofs_test.go
│       │   │   │   │   │   │   ├── ioutil.go
│       │   │   │   │   │   │   ├── ioutil_test.go
│       │   │   │   │   │   │   ├── LICENSE.txt
│       │   │   │   │   │   │   ├── lstater.go
│       │   │   │   │   │   │   ├── lstater_test.go
│       │   │   │   │   │   │   ├── match.go
│       │   │   │   │   │   │   ├── match_test.go
│       │   │   │   │   │   │   ├── mem
│       │   │   │   │   │   │   │   ├── dir.go
│       │   │   │   │   │   │   │   ├── dirmap.go
│       │   │   │   │   │   │   │   ├── file.go
│       │   │   │   │   │   │   │   └── file_test.go
│       │   │   │   │   │   │   ├── memmap.go
│       │   │   │   │   │   │   ├── memmap_test.go
│       │   │   │   │   │   │   ├── os.go
│       │   │   │   │   │   │   ├── path.go
│       │   │   │   │   │   │   ├── path_test.go
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── readonlyfs.go
│       │   │   │   │   │   │   ├── regexpfs.go
│       │   │   │   │   │   │   ├── ro_regexp_test.go
│       │   │   │   │   │   │   ├── symlink.go
│       │   │   │   │   │   │   ├── symlink_test.go
│       │   │   │   │   │   │   ├── tarfs
│       │   │   │   │   │   │   │   ├── file.go
│       │   │   │   │   │   │   │   ├── fs.go
│       │   │   │   │   │   │   │   ├── tarfs_test.go
│       │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │       └── t.tar
│       │   │   │   │   │   │   ├── unionFile.go
│       │   │   │   │   │   │   ├── util.go
│       │   │   │   │   │   │   ├── util_test.go
│       │   │   │   │   │   │   └── zipfs
│       │   │   │   │   │   │       ├── file.go
│       │   │   │   │   │   │       ├── file_test.go
│       │   │   │   │   │   │       ├── fs.go
│       │   │   │   │   │   │       ├── testdata
│       │   │   │   │   │   │       │   ├── small.zip
│       │   │   │   │   │   │       │   └── t.zip
│       │   │   │   │   │   │       └── zipfs_test.go
│       │   │   │   │   │   ├── cast@v1.7.1
│       │   │   │   │   │   │   ├── caste.go
│       │   │   │   │   │   │   ├── cast.go
│       │   │   │   │   │   │   ├── cast_test.go
│       │   │   │   │   │   │   ├── go.mod
│       │   │   │   │   │   │   ├── go.sum
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── Makefile
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   └── timeformattype_string.go
│       │   │   │   │   │   ├── cobra@v1.9.1
│       │   │   │   │   │   │   ├── active_help.go
│       │   │   │   │   │   │   ├── active_help_test.go
│       │   │   │   │   │   │   ├── args.go
│       │   │   │   │   │   │   ├── args_test.go
│       │   │   │   │   │   │   ├── assets
│       │   │   │   │   │   │   │   └── CobraMain.png
│       │   │   │   │   │   │   ├── bash_completions.go
│       │   │   │   │   │   │   ├── bash_completions_test.go
│       │   │   │   │   │   │   ├── bash_completionsV2.go
│       │   │   │   │   │   │   ├── bash_completionsV2_test.go
│       │   │   │   │   │   │   ├── cobra.go
│       │   │   │   │   │   │   ├── cobra_test.go
│       │   │   │   │   │   │   ├── command.go
│       │   │   │   │   │   │   ├── command_notwin.go
│       │   │   │   │   │   │   ├── command_test.go
│       │   │   │   │   │   │   ├── command_win.go
│       │   │   │   │   │   │   ├── completions.go
│       │   │   │   │   │   │   ├── completions_test.go
│       │   │   │   │   │   │   ├── CONDUCT.md
│       │   │   │   │   │   │   ├── CONTRIBUTING.md
│       │   │   │   │   │   │   ├── doc
│       │   │   │   │   │   │   │   ├── cmd_test.go
│       │   │   │   │   │   │   │   ├── man_docs.go
│       │   │   │   │   │   │   │   ├── man_docs_test.go
│       │   │   │   │   │   │   │   ├── man_examples_test.go
│       │   │   │   │   │   │   │   ├── md_docs.go
│       │   │   │   │   │   │   │   ├── md_docs_test.go
│       │   │   │   │   │   │   │   ├── rest_docs.go
│       │   │   │   │   │   │   │   ├── rest_docs_test.go
│       │   │   │   │   │   │   │   ├── util.go
│       │   │   │   │   │   │   │   ├── yaml_docs.go
│       │   │   │   │   │   │   │   └── yaml_docs_test.go
│       │   │   │   │   │   │   ├── fish_completions.go
│       │   │   │   │   │   │   ├── fish_completions_test.go
│       │   │   │   │   │   │   ├── flag_groups.go
│       │   │   │   │   │   │   ├── flag_groups_test.go
│       │   │   │   │   │   │   ├── go.mod
│       │   │   │   │   │   │   ├── go.sum
│       │   │   │   │   │   │   ├── LICENSE.txt
│       │   │   │   │   │   │   ├── MAINTAINERS
│       │   │   │   │   │   │   ├── Makefile
│       │   │   │   │   │   │   ├── powershell_completions.go
│       │   │   │   │   │   │   ├── powershell_completions_test.go
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── shell_completions.go
│       │   │   │   │   │   │   ├── site
│       │   │   │   │   │   │   │   └── content
│       │   │   │   │   │   │   │       ├── active_help.md
│       │   │   │   │   │   │   │       ├── completions
│       │   │   │   │   │   │   │       │   ├── bash.md
│       │   │   │   │   │   │   │       │   ├── fish.md
│       │   │   │   │   │   │   │       │   ├── _index.md
│       │   │   │   │   │   │   │       │   ├── powershell.md
│       │   │   │   │   │   │   │       │   └── zsh.md
│       │   │   │   │   │   │   │       ├── docgen
│       │   │   │   │   │   │   │       │   ├── _index.md
│       │   │   │   │   │   │   │       │   ├── man.md
│       │   │   │   │   │   │   │       │   ├── md.md
│       │   │   │   │   │   │   │       │   ├── rest.md
│       │   │   │   │   │   │   │       │   └── yaml.md
│       │   │   │   │   │   │   │       ├── projects_using_cobra.md
│       │   │   │   │   │   │   │       └── user_guide.md
│       │   │   │   │   │   │   ├── zsh_completions.go
│       │   │   │   │   │   │   └── zsh_completions_test.go
│       │   │   │   │   │   ├── pflag@v1.0.6
│       │   │   │   │   │   │   ├── bool.go
│       │   │   │   │   │   │   ├── bool_slice.go
│       │   │   │   │   │   │   ├── bool_slice_test.go
│       │   │   │   │   │   │   ├── bool_test.go
│       │   │   │   │   │   │   ├── bytes.go
│       │   │   │   │   │   │   ├── bytes_test.go
│       │   │   │   │   │   │   ├── count.go
│       │   │   │   │   │   │   ├── count_test.go
│       │   │   │   │   │   │   ├── duration.go
│       │   │   │   │   │   │   ├── duration_slice.go
│       │   │   │   │   │   │   ├── duration_slice_test.go
│       │   │   │   │   │   │   ├── example_test.go
│       │   │   │   │   │   │   ├── export_test.go
│       │   │   │   │   │   │   ├── flag.go
│       │   │   │   │   │   │   ├── flag_test.go
│       │   │   │   │   │   │   ├── float32.go
│       │   │   │   │   │   │   ├── float32_slice.go
│       │   │   │   │   │   │   ├── float32_slice_test.go
│       │   │   │   │   │   │   ├── float64.go
│       │   │   │   │   │   │   ├── float64_slice.go
│       │   │   │   │   │   │   ├── float64_slice_test.go
│       │   │   │   │   │   │   ├── golangflag.go
│       │   │   │   │   │   │   ├── golangflag_test.go
│       │   │   │   │   │   │   ├── go.mod
│       │   │   │   │   │   │   ├── go.sum
│       │   │   │   │   │   │   ├── int16.go
│       │   │   │   │   │   │   ├── int32.go
│       │   │   │   │   │   │   ├── int32_slice.go
│       │   │   │   │   │   │   ├── int32_slice_test.go
│       │   │   │   │   │   │   ├── int64.go
│       │   │   │   │   │   │   ├── int64_slice.go
│       │   │   │   │   │   │   ├── int64_slice_test.go
│       │   │   │   │   │   │   ├── int8.go
│       │   │   │   │   │   │   ├── int.go
│       │   │   │   │   │   │   ├── int_slice.go
│       │   │   │   │   │   │   ├── int_slice_test.go
│       │   │   │   │   │   │   ├── ip.go
│       │   │   │   │   │   │   ├── ipmask.go
│       │   │   │   │   │   │   ├── ipnet.go
│       │   │   │   │   │   │   ├── ipnet_slice.go
│       │   │   │   │   │   │   ├── ipnet_slice_test.go
│       │   │   │   │   │   │   ├── ipnet_test.go
│       │   │   │   │   │   │   ├── ip_slice.go
│       │   │   │   │   │   │   ├── ip_slice_test.go
│       │   │   │   │   │   │   ├── ip_test.go
│       │   │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   │   ├── printusage_test.go
│       │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   ├── string_array.go
│       │   │   │   │   │   │   ├── string_array_test.go
│       │   │   │   │   │   │   ├── string.go
│       │   │   │   │   │   │   ├── string_slice.go
│       │   │   │   │   │   │   ├── string_slice_test.go
│       │   │   │   │   │   │   ├── string_to_int64.go
│       │   │   │   │   │   │   ├── string_to_int64_test.go
│       │   │   │   │   │   │   ├── string_to_int.go
│       │   │   │   │   │   │   ├── string_to_int_test.go
│       │   │   │   │   │   │   ├── string_to_string.go
│       │   │   │   │   │   │   ├── string_to_string_test.go
│       │   │   │   │   │   │   ├── uint16.go
│       │   │   │   │   │   │   ├── uint32.go
│       │   │   │   │   │   │   ├── uint64.go
│       │   │   │   │   │   │   ├── uint8.go
│       │   │   │   │   │   │   ├── uint.go
│       │   │   │   │   │   │   ├── uint_slice.go
│       │   │   │   │   │   │   ├── uint_slice_test.go
│       │   │   │   │   │   │   └── verify
│       │   │   │   │   │   │       ├── all.sh
│       │   │   │   │   │   │       ├── gofmt.sh
│       │   │   │   │   │   │       └── golint.sh
│       │   │   │   │   │   └── viper@v1.20.1
│       │   │   │   │   │       ├── encoding.go
│       │   │   │   │   │       ├── encoding_test.go
│       │   │   │   │   │       ├── experimental.go
│       │   │   │   │   │       ├── file.go
│       │   │   │   │   │       ├── finder_example_test.go
│       │   │   │   │   │       ├── finder.go
│       │   │   │   │   │       ├── finder_test.go
│       │   │   │   │   │       ├── flags.go
│       │   │   │   │   │       ├── flags_test.go
│       │   │   │   │   │       ├── flake.lock
│       │   │   │   │   │       ├── flake.nix
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── go.sum
│       │   │   │   │   │       ├── internal
│       │   │   │   │   │       │   ├── encoding
│       │   │   │   │   │       │   │   ├── dotenv
│       │   │   │   │   │       │   │   │   ├── codec.go
│       │   │   │   │   │       │   │   │   ├── codec_test.go
│       │   │   │   │   │       │   │   │   └── map_utils.go
│       │   │   │   │   │       │   │   ├── json
│       │   │   │   │   │       │   │   │   ├── codec.go
│       │   │   │   │   │       │   │   │   └── codec_test.go
│       │   │   │   │   │       │   │   ├── toml
│       │   │   │   │   │       │   │   │   ├── codec.go
│       │   │   │   │   │       │   │   │   └── codec_test.go
│       │   │   │   │   │       │   │   └── yaml
│       │   │   │   │   │       │   │       ├── codec.go
│       │   │   │   │   │       │   │       └── codec_test.go
│       │   │   │   │   │       │   ├── features
│       │   │   │   │   │       │   │   ├── bind_struct_default.go
│       │   │   │   │   │       │   │   ├── bind_struct.go
│       │   │   │   │   │       │   │   ├── finder_default.go
│       │   │   │   │   │       │   │   └── finder.go
│       │   │   │   │   │       │   └── testutil
│       │   │   │   │   │       │       └── filepath.go
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── logger.go
│       │   │   │   │   │       ├── Makefile
│       │   │   │   │   │       ├── overrides_test.go
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       ├── remote.go
│       │   │   │   │   │       ├── TROUBLESHOOTING.md
│       │   │   │   │   │       ├── UPDATES.md
│       │   │   │   │   │       ├── util.go
│       │   │   │   │   │       ├── util_test.go
│       │   │   │   │   │       ├── viper.go
│       │   │   │   │   │       ├── viper_test.go
│       │   │   │   │   │       └── viper_yaml_test.go
│       │   │   │   │   ├── subosito
│       │   │   │   │   │   └── gotenv@v1.6.0
│       │   │   │   │   │       ├── CHANGELOG.md
│       │   │   │   │   │       ├── fixtures
│       │   │   │   │   │       │   ├── exported.env
│       │   │   │   │   │       │   ├── plain.env
│       │   │   │   │   │       │   ├── quoted.env
│       │   │   │   │   │       │   ├── utf16be_bom.env
│       │   │   │   │   │       │   ├── utf16le_bom.env
│       │   │   │   │   │       │   ├── utf8_bom.env
│       │   │   │   │   │       │   ├── vars.env
│       │   │   │   │   │       │   └── yaml.env
│       │   │   │   │   │       ├── go.mod
│       │   │   │   │   │       ├── go.sum
│       │   │   │   │   │       ├── gotenv.go
│       │   │   │   │   │       ├── gotenv_test.go
│       │   │   │   │   │       ├── LICENSE
│       │   │   │   │   │       ├── README.md
│       │   │   │   │   │       └── scanner_test.go
│       │   │   │   │   └── yosida95
│       │   │   │   │       └── uritemplate
│       │   │   │   │           └── v3@v3.0.2
│       │   │   │   │               ├── compile.go
│       │   │   │   │               ├── equals.go
│       │   │   │   │               ├── equals_test.go
│       │   │   │   │               ├── error.go
│       │   │   │   │               ├── escape.go
│       │   │   │   │               ├── expression.go
│       │   │   │   │               ├── go.mod
│       │   │   │   │               ├── go.sum
│       │   │   │   │               ├── LICENSE
│       │   │   │   │               ├── machine.go
│       │   │   │   │               ├── match.go
│       │   │   │   │               ├── match_test.go
│       │   │   │   │               ├── parse.go
│       │   │   │   │               ├── prog.go
│       │   │   │   │               ├── README.rst
│       │   │   │   │               ├── uritemplate.go
│       │   │   │   │               ├── uritemplate_test.go
│       │   │   │   │               └── value.go
│       │   │   │   ├── golang.org
│       │   │   │   │   ├── toolchain@v0.0.1-go1.23.7.linux-arm64
│       │   │   │   │   │   ├── bin
│       │   │   │   │   │   │   ├── go
│       │   │   │   │   │   │   └── gofmt
│       │   │   │   │   │   ├── codereview.cfg
│       │   │   │   │   │   ├── CONTRIBUTING.md
│       │   │   │   │   │   ├── go.env
│       │   │   │   │   │   ├── lib
│       │   │   │   │   │   │   └── time
│       │   │   │   │   │   │       ├── mkzip.go
│       │   │   │   │   │   │       ├── README
│       │   │   │   │   │   │       ├── update.bash
│       │   │   │   │   │   │       └── zoneinfo.zip
│       │   │   │   │   │   ├── LICENSE
│       │   │   │   │   │   ├── PATENTS
│       │   │   │   │   │   ├── pkg
│       │   │   │   │   │   │   ├── include
│       │   │   │   │   │   │   │   ├── asm_amd64.h
│       │   │   │   │   │   │   │   ├── asm_ppc64x.h
│       │   │   │   │   │   │   │   ├── funcdata.h
│       │   │   │   │   │   │   │   └── textflag.h
│       │   │   │   │   │   │   └── tool
│       │   │   │   │   │   │       └── linux_arm64
│       │   │   │   │   │   │           ├── addr2line
│       │   │   │   │   │   │           ├── asm
│       │   │   │   │   │   │           ├── buildid
│       │   │   │   │   │   │           ├── cgo
│       │   │   │   │   │   │           ├── compile
│       │   │   │   │   │   │           ├── covdata
│       │   │   │   │   │   │           ├── cover
│       │   │   │   │   │   │           ├── doc
│       │   │   │   │   │   │           ├── fix
│       │   │   │   │   │   │           ├── link
│       │   │   │   │   │   │           ├── nm
│       │   │   │   │   │   │           ├── objdump
│       │   │   │   │   │   │           ├── pack
│       │   │   │   │   │   │           ├── pprof
│       │   │   │   │   │   │           ├── preprofile
│       │   │   │   │   │   │           ├── test2json
│       │   │   │   │   │   │           ├── trace
│       │   │   │   │   │   │           └── vet
│       │   │   │   │   │   ├── README.md
│       │   │   │   │   │   ├── SECURITY.md
│       │   │   │   │   │   ├── src
│       │   │   │   │   │   │   ├── all.bash
│       │   │   │   │   │   │   ├── all.bat
│       │   │   │   │   │   │   ├── all.rc
│       │   │   │   │   │   │   ├── archive
│       │   │   │   │   │   │   │   ├── tar
│       │   │   │   │   │   │   │   │   ├── common.go
│       │   │   │   │   │   │   │   │   ├── example_test.go
│       │   │   │   │   │   │   │   │   ├── format.go
│       │   │   │   │   │   │   │   │   ├── fuzz_test.go
│       │   │   │   │   │   │   │   │   ├── reader.go
│       │   │   │   │   │   │   │   │   ├── reader_test.go
│       │   │   │   │   │   │   │   │   ├── stat_actime1.go
│       │   │   │   │   │   │   │   │   ├── stat_actime2.go
│       │   │   │   │   │   │   │   │   ├── stat_unix.go
│       │   │   │   │   │   │   │   │   ├── strconv.go
│       │   │   │   │   │   │   │   │   ├── strconv_test.go
│       │   │   │   │   │   │   │   │   ├── tar_test.go
│       │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   ├── file-and-dir.tar
│       │   │   │   │   │   │   │   │   │   ├── gnu-incremental.tar
│       │   │   │   │   │   │   │   │   │   ├── gnu-long-nul.tar
│       │   │   │   │   │   │   │   │   │   ├── gnu-multi-hdrs.tar
│       │   │   │   │   │   │   │   │   │   ├── gnu-nil-sparse-data.tar
│       │   │   │   │   │   │   │   │   │   ├── gnu-nil-sparse-hole.tar
│       │   │   │   │   │   │   │   │   │   ├── gnu-not-utf8.tar
│       │   │   │   │   │   │   │   │   │   ├── gnu-sparse-big.tar
│       │   │   │   │   │   │   │   │   │   ├── gnu.tar
│       │   │   │   │   │   │   │   │   │   ├── gnu-utf8.tar
│       │   │   │   │   │   │   │   │   │   ├── hardlink.tar
│       │   │   │   │   │   │   │   │   │   ├── hdr-only.tar
│       │   │   │   │   │   │   │   │   │   ├── invalid-go17.tar
│       │   │   │   │   │   │   │   │   │   ├── issue10968.tar
│       │   │   │   │   │   │   │   │   │   ├── issue11169.tar
│       │   │   │   │   │   │   │   │   │   ├── issue12435.tar
│       │   │   │   │   │   │   │   │   │   ├── neg-size.tar
│       │   │   │   │   │   │   │   │   │   ├── nil-uid.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-bad-hdr-file.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-bad-hdr-large.tar.bz2
│       │   │   │   │   │   │   │   │   │   ├── pax-bad-mtime-file.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-global-records.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-multi-hdrs.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-nil-sparse-data.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-nil-sparse-hole.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-nul-path.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-nul-xattrs.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-path-hdr.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-pos-size-file.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-records.tar
│       │   │   │   │   │   │   │   │   │   ├── pax-sparse-big.tar
│       │   │   │   │   │   │   │   │   │   ├── pax.tar
│       │   │   │   │   │   │   │   │   │   ├── small2.txt
│       │   │   │   │   │   │   │   │   │   ├── small.txt
│       │   │   │   │   │   │   │   │   │   ├── sparse-formats.tar
│       │   │   │   │   │   │   │   │   │   ├── star.tar
│       │   │   │   │   │   │   │   │   │   ├── trailing-slash.tar
│       │   │   │   │   │   │   │   │   │   ├── ustar-file-devs.tar
│       │   │   │   │   │   │   │   │   │   ├── ustar-file-reg.tar
│       │   │   │   │   │   │   │   │   │   ├── ustar.tar
│       │   │   │   │   │   │   │   │   │   ├── v7.tar
│       │   │   │   │   │   │   │   │   │   ├── writer-big-long.tar
│       │   │   │   │   │   │   │   │   │   ├── writer-big.tar
│       │   │   │   │   │   │   │   │   │   ├── writer.tar
│       │   │   │   │   │   │   │   │   │   └── xattrs.tar
│       │   │   │   │   │   │   │   │   ├── writer.go
│       │   │   │   │   │   │   │   │   └── writer_test.go
│       │   │   │   │   │   │   │   └── zip
│       │   │   │   │   │   │   │       ├── example_test.go
│       │   │   │   │   │   │   │       ├── fuzz_test.go
│       │   │   │   │   │   │   │       ├── reader.go
│       │   │   │   │   │   │   │       ├── reader_test.go
│       │   │   │   │   │   │   │       ├── register.go
│       │   │   │   │   │   │   │       ├── struct.go
│       │   │   │   │   │   │   │       ├── testdata
│       │   │   │   │   │   │   │       │   ├── comment-truncated.zip
│       │   │   │   │   │   │   │       │   ├── crc32-not-streamed.zip
│       │   │   │   │   │   │   │       │   ├── dd.zip
│       │   │   │   │   │   │   │       │   ├── dupdir.zip
│       │   │   │   │   │   │   │       │   ├── go-no-datadesc-sig.zip.base64
│       │   │   │   │   │   │   │       │   ├── gophercolor16x16.png
│       │   │   │   │   │   │   │       │   ├── go-with-datadesc-sig.zip
│       │   │   │   │   │   │   │       │   ├── readme.notzip
│       │   │   │   │   │   │   │       │   ├── readme.zip
│       │   │   │   │   │   │   │       │   ├── subdir.zip
│       │   │   │   │   │   │   │       │   ├── symlink.zip
│       │   │   │   │   │   │   │       │   ├── test-badbase.zip
│       │   │   │   │   │   │   │       │   ├── test-baddirsz.zip
│       │   │   │   │   │   │   │       │   ├── test-prefix.zip
│       │   │   │   │   │   │   │       │   ├── test-trailing-junk.zip
│       │   │   │   │   │   │   │       │   ├── test.zip
│       │   │   │   │   │   │   │       │   ├── time-22738.zip
│       │   │   │   │   │   │   │       │   ├── time-7zip.zip
│       │   │   │   │   │   │   │       │   ├── time-go.zip
│       │   │   │   │   │   │   │       │   ├── time-infozip.zip
│       │   │   │   │   │   │   │       │   ├── time-osx.zip
│       │   │   │   │   │   │   │       │   ├── time-win7.zip
│       │   │   │   │   │   │   │       │   ├── time-winrar.zip
│       │   │   │   │   │   │   │       │   ├── time-winzip.zip
│       │   │   │   │   │   │   │       │   ├── unix.zip
│       │   │   │   │   │   │   │       │   ├── utf8-7zip.zip
│       │   │   │   │   │   │   │       │   ├── utf8-infozip.zip
│       │   │   │   │   │   │   │       │   ├── utf8-osx.zip
│       │   │   │   │   │   │   │       │   ├── utf8-winrar.zip
│       │   │   │   │   │   │   │       │   ├── utf8-winzip.zip
│       │   │   │   │   │   │   │       │   ├── winxp.zip
│       │   │   │   │   │   │   │       │   ├── zip64-2.zip
│       │   │   │   │   │   │   │       │   └── zip64.zip
│       │   │   │   │   │   │   │       ├── writer.go
│       │   │   │   │   │   │   │       ├── writer_test.go
│       │   │   │   │   │   │   │       └── zip_test.go
│       │   │   │   │   │   │   ├── arena
│       │   │   │   │   │   │   │   ├── arena.go
│       │   │   │   │   │   │   │   └── arena_test.go
│       │   │   │   │   │   │   ├── bootstrap.bash
│       │   │   │   │   │   │   ├── bufio
│       │   │   │   │   │   │   │   ├── bufio.go
│       │   │   │   │   │   │   │   ├── bufio_test.go
│       │   │   │   │   │   │   │   ├── example_test.go
│       │   │   │   │   │   │   │   ├── export_test.go
│       │   │   │   │   │   │   │   ├── scan.go
│       │   │   │   │   │   │   │   └── scan_test.go
│       │   │   │   │   │   │   ├── buildall.bash
│       │   │   │   │   │   │   ├── builtin
│       │   │   │   │   │   │   │   └── builtin.go
│       │   │   │   │   │   │   ├── bytes
│       │   │   │   │   │   │   │   ├── boundary_test.go
│       │   │   │   │   │   │   │   ├── buffer.go
│       │   │   │   │   │   │   │   ├── buffer_test.go
│       │   │   │   │   │   │   │   ├── bytes.go
│       │   │   │   │   │   │   │   ├── bytes_js_wasm_test.go
│       │   │   │   │   │   │   │   ├── bytes_test.go
│       │   │   │   │   │   │   │   ├── compare_test.go
│       │   │   │   │   │   │   │   ├── example_test.go
│       │   │   │   │   │   │   │   ├── export_test.go
│       │   │   │   │   │   │   │   ├── reader.go
│       │   │   │   │   │   │   │   └── reader_test.go
│       │   │   │   │   │   │   ├── clean.bash
│       │   │   │   │   │   │   ├── clean.bat
│       │   │   │   │   │   │   ├── clean.rc
│       │   │   │   │   │   │   ├── cmd
│       │   │   │   │   │   │   │   ├── addr2line
│       │   │   │   │   │   │   │   │   ├── addr2line_test.go
│       │   │   │   │   │   │   │   │   └── main.go
│       │   │   │   │   │   │   │   ├── api
│       │   │   │   │   │   │   │   │   ├── api_test.go
│       │   │   │   │   │   │   │   │   ├── boring_test.go
│       │   │   │   │   │   │   │   │   ├── main_test.go
│       │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │       └── src
│       │   │   │   │   │   │   │   │           ├── issue21181
│       │   │   │   │   │   │   │   │           │   ├── dep
│       │   │   │   │   │   │   │   │           │   │   ├── p_amd64.go
│       │   │   │   │   │   │   │   │           │   │   └── p.go
│       │   │   │   │   │   │   │   │           │   ├── indirect
│       │   │   │   │   │   │   │   │           │   │   └── p.go
│       │   │   │   │   │   │   │   │           │   └── p
│       │   │   │   │   │   │   │   │           │       ├── p_amd64.go
│       │   │   │   │   │   │   │   │           │       ├── p_generic.go
│       │   │   │   │   │   │   │   │           │       └── p.go
│       │   │   │   │   │   │   │   │           ├── issue29837
│       │   │   │   │   │   │   │   │           │   └── p
│       │   │   │   │   │   │   │   │           │       └── README
│       │   │   │   │   │   │   │   │           ├── issue64958
│       │   │   │   │   │   │   │   │           │   └── p
│       │   │   │   │   │   │   │   │           │       └── p.go
│       │   │   │   │   │   │   │   │           └── pkg
│       │   │   │   │   │   │   │   │               ├── p1
│       │   │   │   │   │   │   │   │               │   ├── golden.txt
│       │   │   │   │   │   │   │   │               │   └── p1.go
│       │   │   │   │   │   │   │   │               ├── p2
│       │   │   │   │   │   │   │   │               │   ├── golden.txt
│       │   │   │   │   │   │   │   │               │   └── p2.go
│       │   │   │   │   │   │   │   │               ├── p3
│       │   │   │   │   │   │   │   │               │   ├── golden.txt
│       │   │   │   │   │   │   │   │               │   └── p3.go
│       │   │   │   │   │   │   │   │               └── p4
│       │   │   │   │   │   │   │   │                   ├── golden.txt
│       │   │   │   │   │   │   │   │                   └── p4.go
│       │   │   │   │   │   │   │   ├── asm
│       │   │   │   │   │   │   │   │   ├── doc.go
│       │   │   │   │   │   │   │   │   ├── internal
│       │   │   │   │   │   │   │   │   │   ├── arch
│       │   │   │   │   │   │   │   │   │   │   ├── arch.go
│       │   │   │   │   │   │   │   │   │   │   ├── arm64.go
│       │   │   │   │   │   │   │   │   │   │   ├── arm.go
│       │   │   │   │   │   │   │   │   │   │   ├── loong64.go
│       │   │   │   │   │   │   │   │   │   │   ├── mips.go
│       │   │   │   │   │   │   │   │   │   │   ├── ppc64.go
│       │   │   │   │   │   │   │   │   │   │   ├── riscv64.go
│       │   │   │   │   │   │   │   │   │   │   └── s390x.go
│       │   │   │   │   │   │   │   │   │   ├── asm
│       │   │   │   │   │   │   │   │   │   │   ├── asm.go
│       │   │   │   │   │   │   │   │   │   │   ├── endtoend_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── expr_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── line_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── operand_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── parse.go
│       │   │   │   │   │   │   │   │   │   │   ├── pseudo_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── 386enc.s
│       │   │   │   │   │   │   │   │   │   │       ├── 386.s
│       │   │   │   │   │   │   │   │   │   │       ├── amd64dynlinkerror.s
│       │   │   │   │   │   │   │   │   │   │       ├── amd64enc_extra.s
│       │   │   │   │   │   │   │   │   │   │       ├── amd64enc.s
│       │   │   │   │   │   │   │   │   │   │       ├── amd64error.s
│       │   │   │   │   │   │   │   │   │   │       ├── amd64.s
│       │   │   │   │   │   │   │   │   │   │       ├── arm64enc.s
│       │   │   │   │   │   │   │   │   │   │       ├── arm64error.s
│       │   │   │   │   │   │   │   │   │   │       ├── arm64.s
│       │   │   │   │   │   │   │   │   │   │       ├── armerror.s
│       │   │   │   │   │   │   │   │   │   │       ├── arm.s
│       │   │   │   │   │   │   │   │   │   │       ├── armv6.s
│       │   │   │   │   │   │   │   │   │   │       ├── avx512enc
│       │   │   │   │   │   │   │   │   │   │       │   ├── aes_avx512f.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512_4fmaps.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512_4vnniw.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512_bitalg.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512bw.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512cd.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512dq.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512er.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512f.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512_ifma.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512pf.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512_vbmi2.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512_vbmi.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512_vnni.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── avx512_vpopcntdq.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── gfni_avx512f.s
│       │   │   │   │   │   │   │   │   │   │       │   └── vpclmulqdq_avx512f.s
│       │   │   │   │   │   │   │   │   │   │       ├── buildtagerror.s
│       │   │   │   │   │   │   │   │   │   │       ├── duperror.s
│       │   │   │   │   │   │   │   │   │   │       ├── loong64enc1.s
│       │   │   │   │   │   │   │   │   │   │       ├── loong64enc2.s
│       │   │   │   │   │   │   │   │   │   │       ├── loong64enc3.s
│       │   │   │   │   │   │   │   │   │   │       ├── loong64.s
│       │   │   │   │   │   │   │   │   │   │       ├── mips64.s
│       │   │   │   │   │   │   │   │   │   │       ├── mips.s
│       │   │   │   │   │   │   │   │   │   │       ├── ppc64_p10.s
│       │   │   │   │   │   │   │   │   │   │       ├── ppc64.s
│       │   │   │   │   │   │   │   │   │   │       ├── riscv64error.s
│       │   │   │   │   │   │   │   │   │   │       ├── riscv64.s
│       │   │   │   │   │   │   │   │   │   │       └── s390x.s
│       │   │   │   │   │   │   │   │   │   ├── flags
│       │   │   │   │   │   │   │   │   │   │   └── flags.go
│       │   │   │   │   │   │   │   │   │   └── lex
│       │   │   │   │   │   │   │   │   │       ├── input.go
│       │   │   │   │   │   │   │   │   │       ├── lex.go
│       │   │   │   │   │   │   │   │   │       ├── lex_test.go
│       │   │   │   │   │   │   │   │   │       ├── slice.go
│       │   │   │   │   │   │   │   │   │       ├── stack.go
│       │   │   │   │   │   │   │   │   │       └── tokenizer.go
│       │   │   │   │   │   │   │   │   └── main.go
│       │   │   │   │   │   │   │   ├── buildid
│       │   │   │   │   │   │   │   │   ├── buildid.go
│       │   │   │   │   │   │   │   │   └── doc.go
│       │   │   │   │   │   │   │   ├── cgo
│       │   │   │   │   │   │   │   │   ├── ast.go
│       │   │   │   │   │   │   │   │   ├── ast_go118.go
│       │   │   │   │   │   │   │   │   ├── ast_go1.go
│       │   │   │   │   │   │   │   │   ├── doc.go
│       │   │   │   │   │   │   │   │   ├── gcc.go
│       │   │   │   │   │   │   │   │   ├── godefs.go
│       │   │   │   │   │   │   │   │   ├── internal
│       │   │   │   │   │   │   │   │   │   ├── cgotest
│       │   │   │   │   │   │   │   │   │   │   └── overlaydir.go
│       │   │   │   │   │   │   │   │   │   ├── swig
│       │   │   │   │   │   │   │   │   │   │   ├── swig_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── callback
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.cc
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.h
│       │   │   │   │   │   │   │   │   │   │       │   └── main.swigcxx
│       │   │   │   │   │   │   │   │   │   │       └── stdio
│       │   │   │   │   │   │   │   │   │   │           ├── main.go
│       │   │   │   │   │   │   │   │   │   │           └── main.swig
│       │   │   │   │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   │   │   │   ├── backdoor.go
│       │   │   │   │   │   │   │   │   │   │   ├── buildid_linux.go
│       │   │   │   │   │   │   │   │   │   │   ├── callback_c.c
│       │   │   │   │   │   │   │   │   │   │   ├── callback_c_gc.c
│       │   │   │   │   │   │   │   │   │   │   ├── callback_c_gccgo.c
│       │   │   │   │   │   │   │   │   │   │   ├── callback.go
│       │   │   │   │   │   │   │   │   │   │   ├── callback_windows.go
│       │   │   │   │   │   │   │   │   │   │   ├── callstub_linux_ppc64le.go
│       │   │   │   │   │   │   │   │   │   │   ├── cgo_linux_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cgo_stubs_android_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cgo_stubs_ppc64x_internal_linking_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cgo_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cgo_thread_lock.go
│       │   │   │   │   │   │   │   │   │   │   ├── cgo_unix_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cthread_unix.c
│       │   │   │   │   │   │   │   │   │   │   ├── cthread_windows.c
│       │   │   │   │   │   │   │   │   │   │   ├── gcc68255
│       │   │   │   │   │   │   │   │   │   │   │   ├── a.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── c.c
│       │   │   │   │   │   │   │   │   │   │   │   └── c.h
│       │   │   │   │   │   │   │   │   │   │   ├── gcc68255.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue1435.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue18146.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue20266
│       │   │   │   │   │   │   │   │   │   │   │   └── issue20266.h
│       │   │   │   │   │   │   │   │   │   │   ├── issue20266.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue20910.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue21897b.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue21897.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue23555a
│       │   │   │   │   │   │   │   │   │   │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue23555b
│       │   │   │   │   │   │   │   │   │   │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue23555.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue24161arg
│       │   │   │   │   │   │   │   │   │   │   │   ├── def.go
│       │   │   │   │   │   │   │   │   │   │   │   └── use.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue24161_darwin_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue24161e0
│       │   │   │   │   │   │   │   │   │   │   │   └── main.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue24161e1
│       │   │   │   │   │   │   │   │   │   │   │   └── main.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue24161e2
│       │   │   │   │   │   │   │   │   │   │   │   └── main.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue24161res
│       │   │   │   │   │   │   │   │   │   │   │   └── restype.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue26213
│       │   │   │   │   │   │   │   │   │   │   │   ├── jni.h
│       │   │   │   │   │   │   │   │   │   │   │   └── test26213.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue26430
│       │   │   │   │   │   │   │   │   │   │   │   ├── a.go
│       │   │   │   │   │   │   │   │   │   │   │   └── b.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue26430.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue26743
│       │   │   │   │   │   │   │   │   │   │   │   ├── a.go
│       │   │   │   │   │   │   │   │   │   │   │   └── b.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue26743.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue27054
│       │   │   │   │   │   │   │   │   │   │   │   ├── egl.h
│       │   │   │   │   │   │   │   │   │   │   │   └── test27054.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue27340
│       │   │   │   │   │   │   │   │   │   │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue27340.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue29563
│       │   │   │   │   │   │   │   │   │   │   │   ├── weak1.c
│       │   │   │   │   │   │   │   │   │   │   │   ├── weak2.c
│       │   │   │   │   │   │   │   │   │   │   │   └── weak.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue29563.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue30527
│       │   │   │   │   │   │   │   │   │   │   │   ├── a.go
│       │   │   │   │   │   │   │   │   │   │   │   └── b.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue30527.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue31891.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue4029.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue4029.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue4029w.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue41761a
│       │   │   │   │   │   │   │   │   │   │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue41761.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue42018.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue42018_windows.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue42495.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue4273b.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue4273.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue4339.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue4339.h
│       │   │   │   │   │   │   │   │   │   │   ├── issue43639
│       │   │   │   │   │   │   │   │   │   │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue43639.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue52611a
│       │   │   │   │   │   │   │   │   │   │   │   ├── a.go
│       │   │   │   │   │   │   │   │   │   │   │   └── b.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue52611b
│       │   │   │   │   │   │   │   │   │   │   │   ├── a.go
│       │   │   │   │   │   │   │   │   │   │   │   └── b.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue52611.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue5548_c.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue5740a.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue5740b.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue6833_c.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue6907export_c.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue6997_linux.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue6997_linux.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue7234_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue8148.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue8148.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue8331.h
│       │   │   │   │   │   │   │   │   │   │   ├── issue8517.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue8517_windows.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue8517_windows.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue8694.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue8756
│       │   │   │   │   │   │   │   │   │   │   │   └── issue8756.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue8756.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue8811.c
│       │   │   │   │   │   │   │   │   │   │   ├── issue8828
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue8828.c
│       │   │   │   │   │   │   │   │   │   │   │   └── trivial.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue8828.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue9026
│       │   │   │   │   │   │   │   │   │   │   │   └── issue9026.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue9026.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue9400
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_386.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_amd64x.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_arm64.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_arm.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_loong64.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_mips64x.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_mipsx.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_ppc64x.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_riscv64.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── asm_s390x.s
│       │   │   │   │   │   │   │   │   │   │   │   ├── gccgo.go
│       │   │   │   │   │   │   │   │   │   │   │   └── stubs.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue9400_linux.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue9510a
│       │   │   │   │   │   │   │   │   │   │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue9510b
│       │   │   │   │   │   │   │   │   │   │   │   └── b.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue9510.go
│       │   │   │   │   │   │   │   │   │   │   ├── linux_ppc64le_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── seh_internal_windows_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── seh_windows_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── setgid2_linux.go
│       │   │   │   │   │   │   │   │   │   │   ├── setgid_linux.go
│       │   │   │   │   │   │   │   │   │   │   ├── sigaltstack.go
│       │   │   │   │   │   │   │   │   │   │   ├── sigprocmask.c
│       │   │   │   │   │   │   │   │   │   │   ├── sigprocmask.go
│       │   │   │   │   │   │   │   │   │   │   ├── stubtest_linux_ppc64le.S
│       │   │   │   │   │   │   │   │   │   │   ├── test26213.go
│       │   │   │   │   │   │   │   │   │   │   ├── test.go
│       │   │   │   │   │   │   │   │   │   │   ├── test_unix.go
│       │   │   │   │   │   │   │   │   │   │   ├── test_windows.go
│       │   │   │   │   │   │   │   │   │   │   ├── testx.c
│       │   │   │   │   │   │   │   │   │   │   ├── testx.go
│       │   │   │   │   │   │   │   │   │   │   └── typeparam.go
│       │   │   │   │   │   │   │   │   │   ├── testcarchive
│       │   │   │   │   │   │   │   │   │   │   ├── carchive_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── libgo
│       │   │   │   │   │   │   │   │   │   │       │   └── libgo.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo10
│       │   │   │   │   │   │   │   │   │   │       │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo2
│       │   │   │   │   │   │   │   │   │   │       │   └── libgo2.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo3
│       │   │   │   │   │   │   │   │   │   │       │   └── libgo3.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo4
│       │   │   │   │   │   │   │   │   │   │       │   └── libgo4.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo6
│       │   │   │   │   │   │   │   │   │   │       │   └── sigprof.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo7
│       │   │   │   │   │   │   │   │   │   │       │   └── sink.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo8
│       │   │   │   │   │   │   │   │   │   │       │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo9
│       │   │   │   │   │   │   │   │   │   │       │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       ├── main10.c
│       │   │   │   │   │   │   │   │   │   │       ├── main2.c
│       │   │   │   │   │   │   │   │   │   │       ├── main3.c
│       │   │   │   │   │   │   │   │   │   │       ├── main4.c
│       │   │   │   │   │   │   │   │   │   │       ├── main5.c
│       │   │   │   │   │   │   │   │   │   │       ├── main6.c
│       │   │   │   │   │   │   │   │   │   │       ├── main7.c
│       │   │   │   │   │   │   │   │   │   │       ├── main8.c
│       │   │   │   │   │   │   │   │   │   │       ├── main9.c
│       │   │   │   │   │   │   │   │   │   │       ├── main.c
│       │   │   │   │   │   │   │   │   │   │       ├── main_unix.c
│       │   │   │   │   │   │   │   │   │   │       ├── main_windows.c
│       │   │   │   │   │   │   │   │   │   │       └── p
│       │   │   │   │   │   │   │   │   │   │           └── p.go
│       │   │   │   │   │   │   │   │   │   ├── testcshared
│       │   │   │   │   │   │   │   │   │   │   ├── cshared_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── go2c2go
│       │   │   │   │   │   │   │   │   │   │       │   ├── go
│       │   │   │   │   │   │   │   │   │   │       │   │   └── shlib.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── m1
│       │   │   │   │   │   │   │   │   │   │       │   │   ├── c.c
│       │   │   │   │   │   │   │   │   │   │       │   │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── m2
│       │   │   │   │   │   │   │   │   │   │       │       └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue36233
│       │   │   │   │   │   │   │   │   │   │       │   └── issue36233.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo
│       │   │   │   │   │   │   │   │   │   │       │   └── libgo.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo2
│       │   │   │   │   │   │   │   │   │   │       │   ├── dup2.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── dup3.go
│       │   │   │   │   │   │   │   │   │   │       │   └── libgo2.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo4
│       │   │   │   │   │   │   │   │   │   │       │   └── libgo4.go
│       │   │   │   │   │   │   │   │   │   │       ├── libgo5
│       │   │   │   │   │   │   │   │   │   │       │   └── libgo5.go
│       │   │   │   │   │   │   │   │   │   │       ├── main0.c
│       │   │   │   │   │   │   │   │   │   │       ├── main1.c
│       │   │   │   │   │   │   │   │   │   │       ├── main2.c
│       │   │   │   │   │   │   │   │   │   │       ├── main3.c
│       │   │   │   │   │   │   │   │   │   │       ├── main4.c
│       │   │   │   │   │   │   │   │   │   │       ├── main5.c
│       │   │   │   │   │   │   │   │   │   │       └── p
│       │   │   │   │   │   │   │   │   │   │           └── p.go
│       │   │   │   │   │   │   │   │   │   ├── testerrors
│       │   │   │   │   │   │   │   │   │   │   ├── argposition_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── badsym_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── errors_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── ptr_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── err1.go
│       │   │   │   │   │   │   │   │   │   │       ├── err2.go
│       │   │   │   │   │   │   │   │   │   │       ├── err4.go
│       │   │   │   │   │   │   │   │   │   │       ├── err5.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue11097a.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue11097b.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue14669.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue18452.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue18889.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue28069.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue28721.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue33061.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue42580.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue50710.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue67517.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue67707.go
│       │   │   │   │   │   │   │   │   │   │       ├── long_double_size.go
│       │   │   │   │   │   │   │   │   │   │       ├── malloc.go
│       │   │   │   │   │   │   │   │   │   │       └── notmatchedcfunction.go
│       │   │   │   │   │   │   │   │   │   ├── testfortran
│       │   │   │   │   │   │   │   │   │   │   ├── fortran_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── helloworld
│       │   │   │   │   │   │   │   │   │   │       │   └── helloworld.f90
│       │   │   │   │   │   │   │   │   │   │       └── testprog
│       │   │   │   │   │   │   │   │   │   │           ├── answer.f90
│       │   │   │   │   │   │   │   │   │   │           └── fortran.go
│       │   │   │   │   │   │   │   │   │   ├── testgodefs
│       │   │   │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   │   │   ├── anonunion.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── bitfields.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── fieldtypedef.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue37479.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue37621.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue38649.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue39534.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue48396.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue8478.go
│       │   │   │   │   │   │   │   │   │   │   │   └── main.go
│       │   │   │   │   │   │   │   │   │   │   └── testgodefs_test.go
│       │   │   │   │   │   │   │   │   │   ├── testlife
│       │   │   │   │   │   │   │   │   │   │   ├── life_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── c-life.c
│       │   │   │   │   │   │   │   │   │   │       ├── life.go
│       │   │   │   │   │   │   │   │   │   │       ├── life.h
│       │   │   │   │   │   │   │   │   │   │       ├── main.go
│       │   │   │   │   │   │   │   │   │   │       └── main.out
│       │   │   │   │   │   │   │   │   │   ├── testnocgo
│       │   │   │   │   │   │   │   │   │   │   ├── nocgo.go
│       │   │   │   │   │   │   │   │   │   │   └── nocgo_test.go
│       │   │   │   │   │   │   │   │   │   ├── testplugin
│       │   │   │   │   │   │   │   │   │   │   ├── altpath
│       │   │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │   │       ├── common
│       │   │   │   │   │   │   │   │   │   │   │       │   └── common.go
│       │   │   │   │   │   │   │   │   │   │   │       └── plugin-mismatch
│       │   │   │   │   │   │   │   │   │   │   │           └── main.go
│       │   │   │   │   │   │   │   │   │   │   ├── plugin_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── checkdwarf
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── common
│       │   │   │   │   │   │   │   │   │   │       │   └── common.go
│       │   │   │   │   │   │   │   │   │   │       ├── forkexec
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── host
│       │   │   │   │   │   │   │   │   │   │       │   └── host.go
│       │   │   │   │   │   │   │   │   │   │       ├── iface
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── iface_a
│       │   │   │   │   │   │   │   │   │   │       │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       ├── iface_b
│       │   │   │   │   │   │   │   │   │   │       │   └── b.go
│       │   │   │   │   │   │   │   │   │   │       ├── iface_i
│       │   │   │   │   │   │   │   │   │   │       │   └── i.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue18584
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue18676
│       │   │   │   │   │   │   │   │   │   │       │   ├── dynamodbstreamsevt
│       │   │   │   │   │   │   │   │   │   │       │   │   └── definition.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue19418
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue19529
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue19534
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue22175
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── plugin1.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin2.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue22295.pkg
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue24351
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue25756
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin
│       │   │   │   │   │   │   │   │   │   │       │       ├── c-life.c
│       │   │   │   │   │   │   │   │   │   │       │       ├── life.go
│       │   │   │   │   │   │   │   │   │   │       │       └── life.h
│       │   │   │   │   │   │   │   │   │   │       ├── issue44956
│       │   │   │   │   │   │   │   │   │   │       │   ├── base
│       │   │   │   │   │   │   │   │   │   │       │   │   └── base.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── plugin1.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin2.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue52937
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue53989
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── p
│       │   │   │   │   │   │   │   │   │   │       │   │   └── p.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue62430
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue67976
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── mangle
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── method
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── method2
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── p
│       │   │   │   │   │   │   │   │   │   │       │   │   └── p.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── method3
│       │   │   │   │   │   │   │   │   │   │       │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── p
│       │   │   │   │   │   │   │   │   │   │       │   │   └── p.go
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin.go
│       │   │   │   │   │   │   │   │   │   │       ├── plugin1
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin1.go
│       │   │   │   │   │   │   │   │   │   │       ├── plugin2
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin2.go
│       │   │   │   │   │   │   │   │   │   │       ├── sub
│       │   │   │   │   │   │   │   │   │   │       │   └── plugin1
│       │   │   │   │   │   │   │   │   │   │       │       └── plugin1.go
│       │   │   │   │   │   │   │   │   │   │       ├── unnamed1
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       └── unnamed2
│       │   │   │   │   │   │   │   │   │   │           └── main.go
│       │   │   │   │   │   │   │   │   │   ├── testsanitizers
│       │   │   │   │   │   │   │   │   │   │   ├── asan_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cc_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cshared_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── empty_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── libfuzzer_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── msan_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   │   │   ├── arena_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan1_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan2_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan3_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan4_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan5_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_global1_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_global2_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_global3_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_global4_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_global5.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_linkerx
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │   │   │   └── p
│       │   │   │   │   │   │   │   │   │   │   │   │       └── p.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_unsafe_fail1.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_unsafe_fail2.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_unsafe_fail3.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── asan_useAfterReturn.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── libfuzzer1.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── libfuzzer2.c
│       │   │   │   │   │   │   │   │   │   │   │   ├── libfuzzer2.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan2_cmsan.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan2.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan3.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan4.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan5.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan6.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan7.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan8.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan_fail.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── msan_shared.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan10.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan11.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan12.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan13.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan14.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan15.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan2.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan3.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan4.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan5.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan6.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan7.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan8.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan9.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tsan.go
│       │   │   │   │   │   │   │   │   │   │   │   └── tsan_shared.go
│       │   │   │   │   │   │   │   │   │   │   └── tsan_test.go
│       │   │   │   │   │   │   │   │   │   ├── testshared
│       │   │   │   │   │   │   │   │   │   │   ├── shared_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── dep2
│       │   │   │   │   │   │   │   │   │   │       │   └── dep2.go
│       │   │   │   │   │   │   │   │   │   │       ├── dep3
│       │   │   │   │   │   │   │   │   │   │       │   └── dep3.go
│       │   │   │   │   │   │   │   │   │   │       ├── depBase
│       │   │   │   │   │   │   │   │   │   │       │   ├── asm.s
│       │   │   │   │   │   │   │   │   │   │       │   ├── dep.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── gccgo.go
│       │   │   │   │   │   │   │   │   │   │       │   └── stubs.go
│       │   │   │   │   │   │   │   │   │   │       ├── depBaseInternal
│       │   │   │   │   │   │   │   │   │   │       │   └── dep.go
│       │   │   │   │   │   │   │   │   │   │       ├── division
│       │   │   │   │   │   │   │   │   │   │       │   └── division.go
│       │   │   │   │   │   │   │   │   │   │       ├── exe
│       │   │   │   │   │   │   │   │   │   │       │   └── exe.go
│       │   │   │   │   │   │   │   │   │   │       ├── exe2
│       │   │   │   │   │   │   │   │   │   │       │   └── exe2.go
│       │   │   │   │   │   │   │   │   │   │       ├── exe3
│       │   │   │   │   │   │   │   │   │   │       │   └── exe3.go
│       │   │   │   │   │   │   │   │   │   │       ├── execgo
│       │   │   │   │   │   │   │   │   │   │       │   └── exe.go
│       │   │   │   │   │   │   │   │   │   │       ├── explicit
│       │   │   │   │   │   │   │   │   │   │       │   └── explicit.go
│       │   │   │   │   │   │   │   │   │   │       ├── gcdata
│       │   │   │   │   │   │   │   │   │   │       │   ├── main
│       │   │   │   │   │   │   │   │   │   │       │   │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       │   └── p
│       │   │   │   │   │   │   │   │   │   │       │       └── p.go
│       │   │   │   │   │   │   │   │   │   │       ├── global
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── globallib
│       │   │   │   │   │   │   │   │   │   │       │   └── global.go
│       │   │   │   │   │   │   │   │   │   │       ├── iface
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── iface_a
│       │   │   │   │   │   │   │   │   │   │       │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       ├── iface_b
│       │   │   │   │   │   │   │   │   │   │       │   └── b.go
│       │   │   │   │   │   │   │   │   │   │       ├── iface_i
│       │   │   │   │   │   │   │   │   │   │       │   └── i.go
│       │   │   │   │   │   │   │   │   │   │       ├── implicit
│       │   │   │   │   │   │   │   │   │   │       │   └── implicit.go
│       │   │   │   │   │   │   │   │   │   │       ├── implicitcmd
│       │   │   │   │   │   │   │   │   │   │       │   └── implicitcmd.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue25065
│       │   │   │   │   │   │   │   │   │   │       │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue30768
│       │   │   │   │   │   │   │   │   │   │       │   ├── issue30768lib
│       │   │   │   │   │   │   │   │   │   │       │   │   └── lib.go
│       │   │   │   │   │   │   │   │   │   │       │   └── x_test.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue39777
│       │   │   │   │   │   │   │   │   │   │       │   ├── a
│       │   │   │   │   │   │   │   │   │   │       │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       │   └── b
│       │   │   │   │   │   │   │   │   │   │       │       └── b.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue44031
│       │   │   │   │   │   │   │   │   │   │       │   ├── a
│       │   │   │   │   │   │   │   │   │   │       │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── b
│       │   │   │   │   │   │   │   │   │   │       │   │   └── b.go
│       │   │   │   │   │   │   │   │   │   │       │   └── main
│       │   │   │   │   │   │   │   │   │   │       │       └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue47837
│       │   │   │   │   │   │   │   │   │   │       │   ├── a
│       │   │   │   │   │   │   │   │   │   │       │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       │   └── main
│       │   │   │   │   │   │   │   │   │   │       │       └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue58966
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── issue62277
│       │   │   │   │   │   │   │   │   │   │       │   ├── issue62277_test.go
│       │   │   │   │   │   │   │   │   │   │       │   └── p
│       │   │   │   │   │   │   │   │   │   │       │       └── p.go
│       │   │   │   │   │   │   │   │   │   │       └── trivial
│       │   │   │   │   │   │   │   │   │   │           └── trivial.go
│       │   │   │   │   │   │   │   │   │   ├── testso
│       │   │   │   │   │   │   │   │   │   │   ├── so_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── so
│       │   │   │   │   │   │   │   │   │   │       │   ├── cgoso.c
│       │   │   │   │   │   │   │   │   │   │       │   ├── cgoso_c.c
│       │   │   │   │   │   │   │   │   │   │       │   ├── cgoso.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── cgoso_unix.go
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       └── sovar
│       │   │   │   │   │   │   │   │   │   │           ├── cgoso_c.c
│       │   │   │   │   │   │   │   │   │   │           ├── cgoso_c.h
│       │   │   │   │   │   │   │   │   │   │           ├── cgoso.go
│       │   │   │   │   │   │   │   │   │   │           └── main.go
│       │   │   │   │   │   │   │   │   │   ├── teststdio
│       │   │   │   │   │   │   │   │   │   │   ├── stdio_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── chain.go
│       │   │   │   │   │   │   │   │   │   │       ├── chain.out
│       │   │   │   │   │   │   │   │   │   │       ├── fib.go
│       │   │   │   │   │   │   │   │   │   │       ├── fib.out
│       │   │   │   │   │   │   │   │   │   │       ├── hello.go
│       │   │   │   │   │   │   │   │   │   │       ├── hello.out
│       │   │   │   │   │   │   │   │   │   │       └── stdio
│       │   │   │   │   │   │   │   │   │   │           ├── file.go
│       │   │   │   │   │   │   │   │   │   │           └── stdio.go
│       │   │   │   │   │   │   │   │   │   └── testtls
│       │   │   │   │   │   │   │   │   │       ├── tls.c
│       │   │   │   │   │   │   │   │   │       ├── tls.go
│       │   │   │   │   │   │   │   │   │       ├── tls_none.go
│       │   │   │   │   │   │   │   │   │       └── tls_test.go
│       │   │   │   │   │   │   │   │   ├── main.go
│       │   │   │   │   │   │   │   │   ├── out.go
│       │   │   │   │   │   │   │   │   ├── util.go
│       │   │   │   │   │   │   │   │   └── zdefaultcc.go
│       │   │   │   │   │   │   │   ├── compile
│       │   │   │   │   │   │   │   │   ├── abi-internal.md
│       │   │   │   │   │   │   │   │   ├── default.pgo
│       │   │   │   │   │   │   │   │   ├── doc.go
│       │   │   │   │   │   │   │   │   ├── internal
│       │   │   │   │   │   │   │   │   │   ├── abi
│       │   │   │   │   │   │   │   │   │   │   └── abiutils.go
│       │   │   │   │   │   │   │   │   │   ├── abt
│       │   │   │   │   │   │   │   │   │   │   ├── avlint32.go
│       │   │   │   │   │   │   │   │   │   │   └── avlint32_test.go
│       │   │   │   │   │   │   │   │   │   ├── amd64
│       │   │   │   │   │   │   │   │   │   │   ├── galign.go
│       │   │   │   │   │   │   │   │   │   │   ├── ggen.go
│       │   │   │   │   │   │   │   │   │   │   ├── ssa.go
│       │   │   │   │   │   │   │   │   │   │   └── versions_test.go
│       │   │   │   │   │   │   │   │   │   ├── arm
│       │   │   │   │   │   │   │   │   │   │   ├── galign.go
│       │   │   │   │   │   │   │   │   │   │   ├── ggen.go
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   ├── arm64
│       │   │   │   │   │   │   │   │   │   │   ├── galign.go
│       │   │   │   │   │   │   │   │   │   │   ├── ggen.go
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   ├── base
│       │   │   │   │   │   │   │   │   │   │   ├── base.go
│       │   │   │   │   │   │   │   │   │   │   ├── bootstrap_false.go
│       │   │   │   │   │   │   │   │   │   │   ├── bootstrap_true.go
│       │   │   │   │   │   │   │   │   │   │   ├── debug.go
│       │   │   │   │   │   │   │   │   │   │   ├── flag.go
│       │   │   │   │   │   │   │   │   │   │   ├── hashdebug.go
│       │   │   │   │   │   │   │   │   │   │   ├── hashdebug_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── link.go
│       │   │   │   │   │   │   │   │   │   │   ├── mapfile_mmap.go
│       │   │   │   │   │   │   │   │   │   │   ├── mapfile_read.go
│       │   │   │   │   │   │   │   │   │   │   ├── print.go
│       │   │   │   │   │   │   │   │   │   │   └── timings.go
│       │   │   │   │   │   │   │   │   │   ├── bitvec
│       │   │   │   │   │   │   │   │   │   │   └── bv.go
│       │   │   │   │   │   │   │   │   │   ├── compare
│       │   │   │   │   │   │   │   │   │   │   ├── compare.go
│       │   │   │   │   │   │   │   │   │   │   └── compare_test.go
│       │   │   │   │   │   │   │   │   │   ├── coverage
│       │   │   │   │   │   │   │   │   │   │   └── cover.go
│       │   │   │   │   │   │   │   │   │   ├── devirtualize
│       │   │   │   │   │   │   │   │   │   │   ├── devirtualize.go
│       │   │   │   │   │   │   │   │   │   │   ├── pgo.go
│       │   │   │   │   │   │   │   │   │   │   └── pgo_test.go
│       │   │   │   │   │   │   │   │   │   ├── dwarfgen
│       │   │   │   │   │   │   │   │   │   │   ├── dwarf.go
│       │   │   │   │   │   │   │   │   │   │   ├── dwinl.go
│       │   │   │   │   │   │   │   │   │   │   ├── marker.go
│       │   │   │   │   │   │   │   │   │   │   ├── scope.go
│       │   │   │   │   │   │   │   │   │   │   └── scope_test.go
│       │   │   │   │   │   │   │   │   │   ├── escape
│       │   │   │   │   │   │   │   │   │   │   ├── assign.go
│       │   │   │   │   │   │   │   │   │   │   ├── call.go
│       │   │   │   │   │   │   │   │   │   │   ├── escape.go
│       │   │   │   │   │   │   │   │   │   │   ├── expr.go
│       │   │   │   │   │   │   │   │   │   │   ├── graph.go
│       │   │   │   │   │   │   │   │   │   │   ├── leaks.go
│       │   │   │   │   │   │   │   │   │   │   ├── solve.go
│       │   │   │   │   │   │   │   │   │   │   ├── stmt.go
│       │   │   │   │   │   │   │   │   │   │   └── utils.go
│       │   │   │   │   │   │   │   │   │   ├── gc
│       │   │   │   │   │   │   │   │   │   │   ├── compile.go
│       │   │   │   │   │   │   │   │   │   │   ├── export.go
│       │   │   │   │   │   │   │   │   │   │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │   ├── obj.go
│       │   │   │   │   │   │   │   │   │   │   └── util.go
│       │   │   │   │   │   │   │   │   │   ├── importer
│       │   │   │   │   │   │   │   │   │   │   ├── exportdata.go
│       │   │   │   │   │   │   │   │   │   │   ├── gcimporter.go
│       │   │   │   │   │   │   │   │   │   │   ├── gcimporter_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── iimport.go
│       │   │   │   │   │   │   │   │   │   │   ├── support.go
│       │   │   │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   │   │   ├── a.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── alias.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── b.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── exports.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── generics.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue15920.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue20046.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue25301.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue25596.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── p.go
│       │   │   │   │   │   │   │   │   │   │   │   └── versions
│       │   │   │   │   │   │   │   │   │   │   │       └── test.go
│       │   │   │   │   │   │   │   │   │   │   └── ureader.go
│       │   │   │   │   │   │   │   │   │   ├── inline
│       │   │   │   │   │   │   │   │   │   │   ├── inl.go
│       │   │   │   │   │   │   │   │   │   │   ├── inlheur
│       │   │   │   │   │   │   │   │   │   │   │   ├── actualexprpropbits_string.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── analyze_func_callsites.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── analyze_func_flags.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── analyze_func_params.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── analyze_func_returns.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── analyze.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── callsite.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── cspropbits_string.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── debugflags_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── dumpscores_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── eclassify.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── funcpropbits_string.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── funcprops_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── funcprop_string.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── function_properties.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── names.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── parampropbits_string.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── pstate_string.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── resultpropbits_string.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── scoreadjusttyp_string.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── score_callresult_uses.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── scoring.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── serialize.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── dumpscores.go
│       │   │   │   │   │   │   │   │   │   │   │   │   └── props
│       │   │   │   │   │   │   │   │   │   │   │   │       ├── acrosscall.go
│       │   │   │   │   │   │   │   │   │   │   │   │       ├── calls.go
│       │   │   │   │   │   │   │   │   │   │   │   │       ├── funcflags.go
│       │   │   │   │   │   │   │   │   │   │   │   │       ├── params.go
│       │   │   │   │   │   │   │   │   │   │   │   │       ├── README.txt
│       │   │   │   │   │   │   │   │   │   │   │   │       ├── returns2.go
│       │   │   │   │   │   │   │   │   │   │   │   │       └── returns.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── texpr_classify_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── trace_off.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── trace_on.go
│       │   │   │   │   │   │   │   │   │   │   │   └── tserial_test.go
│       │   │   │   │   │   │   │   │   │   │   └── interleaved
│       │   │   │   │   │   │   │   │   │   │       └── interleaved.go
│       │   │   │   │   │   │   │   │   │   ├── ir
│       │   │   │   │   │   │   │   │   │   │   ├── abi.go
│       │   │   │   │   │   │   │   │   │   │   ├── bitset.go
│       │   │   │   │   │   │   │   │   │   │   ├── cfg.go
│       │   │   │   │   │   │   │   │   │   │   ├── check_reassign_no.go
│       │   │   │   │   │   │   │   │   │   │   ├── check_reassign_yes.go
│       │   │   │   │   │   │   │   │   │   │   ├── class_string.go
│       │   │   │   │   │   │   │   │   │   │   ├── const.go
│       │   │   │   │   │   │   │   │   │   │   ├── copy.go
│       │   │   │   │   │   │   │   │   │   │   ├── dump.go
│       │   │   │   │   │   │   │   │   │   │   ├── expr.go
│       │   │   │   │   │   │   │   │   │   │   ├── fmt.go
│       │   │   │   │   │   │   │   │   │   │   ├── func.go
│       │   │   │   │   │   │   │   │   │   │   ├── func_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── ir.go
│       │   │   │   │   │   │   │   │   │   │   ├── mini.go
│       │   │   │   │   │   │   │   │   │   │   ├── mknode.go
│       │   │   │   │   │   │   │   │   │   │   ├── name.go
│       │   │   │   │   │   │   │   │   │   │   ├── node_gen.go
│       │   │   │   │   │   │   │   │   │   │   ├── node.go
│       │   │   │   │   │   │   │   │   │   │   ├── op_string.go
│       │   │   │   │   │   │   │   │   │   │   ├── package.go
│       │   │   │   │   │   │   │   │   │   │   ├── reassign_consistency_check.go
│       │   │   │   │   │   │   │   │   │   │   ├── reassignment.go
│       │   │   │   │   │   │   │   │   │   │   ├── scc.go
│       │   │   │   │   │   │   │   │   │   │   ├── sizeof_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── stmt.go
│       │   │   │   │   │   │   │   │   │   │   ├── symtab.go
│       │   │   │   │   │   │   │   │   │   │   ├── type.go
│       │   │   │   │   │   │   │   │   │   │   ├── val.go
│       │   │   │   │   │   │   │   │   │   │   └── visit.go
│       │   │   │   │   │   │   │   │   │   ├── liveness
│       │   │   │   │   │   │   │   │   │   │   ├── arg.go
│       │   │   │   │   │   │   │   │   │   │   ├── bvset.go
│       │   │   │   │   │   │   │   │   │   │   ├── intervals.go
│       │   │   │   │   │   │   │   │   │   │   ├── intervals_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── mergelocals.go
│       │   │   │   │   │   │   │   │   │   │   └── plive.go
│       │   │   │   │   │   │   │   │   │   ├── logopt
│       │   │   │   │   │   │   │   │   │   │   ├── log_opts.go
│       │   │   │   │   │   │   │   │   │   │   └── logopt_test.go
│       │   │   │   │   │   │   │   │   │   ├── loong64
│       │   │   │   │   │   │   │   │   │   │   ├── galign.go
│       │   │   │   │   │   │   │   │   │   │   ├── ggen.go
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   ├── loopvar
│       │   │   │   │   │   │   │   │   │   │   ├── loopvar.go
│       │   │   │   │   │   │   │   │   │   │   ├── loopvar_test.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── for_complicated_esc_address.go
│       │   │   │   │   │   │   │   │   │   │       ├── for_esc_address.go
│       │   │   │   │   │   │   │   │   │   │       ├── for_esc_closure.go
│       │   │   │   │   │   │   │   │   │   │       ├── for_esc_method.go
│       │   │   │   │   │   │   │   │   │   │       ├── for_esc_minimal_closure.go
│       │   │   │   │   │   │   │   │   │   │       ├── for_nested.go
│       │   │   │   │   │   │   │   │   │   │       ├── inlines
│       │   │   │   │   │   │   │   │   │   │       │   ├── a
│       │   │   │   │   │   │   │   │   │   │       │   │   └── a.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── b
│       │   │   │   │   │   │   │   │   │   │       │   │   └── b.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── c
│       │   │   │   │   │   │   │   │   │   │       │   │   └── c.go
│       │   │   │   │   │   │   │   │   │   │       │   └── main.go
│       │   │   │   │   │   │   │   │   │   │       ├── opt-121.go
│       │   │   │   │   │   │   │   │   │   │       ├── opt-122.go
│       │   │   │   │   │   │   │   │   │   │       ├── opt.go
│       │   │   │   │   │   │   │   │   │   │       ├── range_esc_address.go
│       │   │   │   │   │   │   │   │   │   │       ├── range_esc_closure.go
│       │   │   │   │   │   │   │   │   │   │       ├── range_esc_method.go
│       │   │   │   │   │   │   │   │   │   │       └── range_esc_minimal_closure.go
│       │   │   │   │   │   │   │   │   │   ├── mips
│       │   │   │   │   │   │   │   │   │   │   ├── galign.go
│       │   │   │   │   │   │   │   │   │   │   ├── ggen.go
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   ├── mips64
│       │   │   │   │   │   │   │   │   │   │   ├── galign.go
│       │   │   │   │   │   │   │   │   │   │   ├── ggen.go
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   ├── noder
│       │   │   │   │   │   │   │   │   │   │   ├── codes.go
│       │   │   │   │   │   │   │   │   │   │   ├── export.go
│       │   │   │   │   │   │   │   │   │   │   ├── helpers.go
│       │   │   │   │   │   │   │   │   │   │   ├── import.go
│       │   │   │   │   │   │   │   │   │   │   ├── irgen.go
│       │   │   │   │   │   │   │   │   │   │   ├── lex.go
│       │   │   │   │   │   │   │   │   │   │   ├── lex_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── linker.go
│       │   │   │   │   │   │   │   │   │   │   ├── noder.go
│       │   │   │   │   │   │   │   │   │   │   ├── posmap.go
│       │   │   │   │   │   │   │   │   │   │   ├── quirks.go
│       │   │   │   │   │   │   │   │   │   │   ├── reader.go
│       │   │   │   │   │   │   │   │   │   │   ├── stencil.go
│       │   │   │   │   │   │   │   │   │   │   ├── stmt.go
│       │   │   │   │   │   │   │   │   │   │   ├── types.go
│       │   │   │   │   │   │   │   │   │   │   ├── unified.go
│       │   │   │   │   │   │   │   │   │   │   └── writer.go
│       │   │   │   │   │   │   │   │   │   ├── objw
│       │   │   │   │   │   │   │   │   │   │   ├── objw.go
│       │   │   │   │   │   │   │   │   │   │   └── prog.go
│       │   │   │   │   │   │   │   │   │   ├── pgoir
│       │   │   │   │   │   │   │   │   │   │   └── irgraph.go
│       │   │   │   │   │   │   │   │   │   ├── pkginit
│       │   │   │   │   │   │   │   │   │   │   ├── initAsanGlobals.go
│       │   │   │   │   │   │   │   │   │   │   └── init.go
│       │   │   │   │   │   │   │   │   │   ├── ppc64
│       │   │   │   │   │   │   │   │   │   │   ├── galign.go
│       │   │   │   │   │   │   │   │   │   │   ├── ggen.go
│       │   │   │   │   │   │   │   │   │   │   ├── opt.go
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   ├── rangefunc
│       │   │   │   │   │   │   │   │   │   │   ├── rangefunc_test.go
│       │   │   │   │   │   │   │   │   │   │   └── rewrite.go
│       │   │   │   │   │   │   │   │   │   ├── reflectdata
│       │   │   │   │   │   │   │   │   │   │   ├── alg.go
│       │   │   │   │   │   │   │   │   │   │   ├── alg_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── helpers.go
│       │   │   │   │   │   │   │   │   │   │   └── reflect.go
│       │   │   │   │   │   │   │   │   │   ├── riscv64
│       │   │   │   │   │   │   │   │   │   │   ├── galign.go
│       │   │   │   │   │   │   │   │   │   │   ├── ggen.go
│       │   │   │   │   │   │   │   │   │   │   ├── gsubr.go
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   ├── rttype
│       │   │   │   │   │   │   │   │   │   │   └── rttype.go
│       │   │   │   │   │   │   │   │   │   ├── s390x
│       │   │   │   │   │   │   │   │   │   │   ├── galign.go
│       │   │   │   │   │   │   │   │   │   │   ├── ggen.go
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   ├── ssa
│       │   │   │   │   │   │   │   │   │   │   ├── addressingmodes.go
│       │   │   │   │   │   │   │   │   │   │   ├── allocators.go
│       │   │   │   │   │   │   │   │   │   │   ├── bench_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── biasedsparsemap.go
│       │   │   │   │   │   │   │   │   │   │   ├── block.go
│       │   │   │   │   │   │   │   │   │   │   ├── branchelim.go
│       │   │   │   │   │   │   │   │   │   │   ├── branchelim_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cache.go
│       │   │   │   │   │   │   │   │   │   │   ├── checkbce.go
│       │   │   │   │   │   │   │   │   │   │   ├── check.go
│       │   │   │   │   │   │   │   │   │   │   ├── compile.go
│       │   │   │   │   │   │   │   │   │   │   ├── config.go
│       │   │   │   │   │   │   │   │   │   │   ├── copyelim.go
│       │   │   │   │   │   │   │   │   │   │   ├── copyelim_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── critical.go
│       │   │   │   │   │   │   │   │   │   │   ├── cse.go
│       │   │   │   │   │   │   │   │   │   │   ├── cse_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── deadcode.go
│       │   │   │   │   │   │   │   │   │   │   ├── deadcode_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── deadstore.go
│       │   │   │   │   │   │   │   │   │   │   ├── deadstore_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── debug.go
│       │   │   │   │   │   │   │   │   │   │   ├── debug_lines_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── debug_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── decompose.go
│       │   │   │   │   │   │   │   │   │   │   ├── dom.go
│       │   │   │   │   │   │   │   │   │   │   ├── dom_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── expand_calls.go
│       │   │   │   │   │   │   │   │   │   │   ├── export_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── flagalloc.go
│       │   │   │   │   │   │   │   │   │   │   ├── flags_amd64_test.s
│       │   │   │   │   │   │   │   │   │   │   ├── flags_arm64_test.s
│       │   │   │   │   │   │   │   │   │   │   ├── flags_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── fmahash_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── func.go
│       │   │   │   │   │   │   │   │   │   │   ├── func_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── fuse_branchredirect.go
│       │   │   │   │   │   │   │   │   │   │   ├── fuse_comparisons.go
│       │   │   │   │   │   │   │   │   │   │   ├── fuse.go
│       │   │   │   │   │   │   │   │   │   │   ├── fuse_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── _gen
│       │   │   │   │   │   │   │   │   │   │   │   ├── 386Ops.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── 386.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── 386splitload.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── allocators.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── AMD64latelower.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── AMD64Ops.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── AMD64.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── AMD64splitload.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── ARM64latelower.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── ARM64Ops.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── ARM64.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── ARMOps.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── ARM.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── cover.bash
│       │   │   │   │   │   │   │   │   │   │   │   ├── dec64Ops.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── dec64.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── decOps.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── dec.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── genericOps.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── generic.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── LOONG64Ops.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── LOONG64.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── main.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── MIPS64Ops.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── MIPS64.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── MIPSOps.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── MIPS.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── PPC64latelower.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── PPC64Ops.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── PPC64.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── README
│       │   │   │   │   │   │   │   │   │   │   │   ├── RISCV64latelower.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── RISCV64Ops.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── RISCV64.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── rulegen.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── S390XOps.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── S390X.rules
│       │   │   │   │   │   │   │   │   │   │   │   ├── WasmOps.go
│       │   │   │   │   │   │   │   │   │   │   │   └── Wasm.rules
│       │   │   │   │   │   │   │   │   │   │   ├── generate.go
│       │   │   │   │   │   │   │   │   │   │   ├── html.go
│       │   │   │   │   │   │   │   │   │   │   ├── id.go
│       │   │   │   │   │   │   │   │   │   │   ├── layout.go
│       │   │   │   │   │   │   │   │   │   │   ├── lca.go
│       │   │   │   │   │   │   │   │   │   │   ├── lca_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── likelyadjust.go
│       │   │   │   │   │   │   │   │   │   │   ├── location.go
│       │   │   │   │   │   │   │   │   │   │   ├── loopbce.go
│       │   │   │   │   │   │   │   │   │   │   ├── loopreschedchecks.go
│       │   │   │   │   │   │   │   │   │   │   ├── looprotate.go
│       │   │   │   │   │   │   │   │   │   │   ├── lower.go
│       │   │   │   │   │   │   │   │   │   │   ├── magic.go
│       │   │   │   │   │   │   │   │   │   │   ├── magic_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── memcombine.go
│       │   │   │   │   │   │   │   │   │   │   ├── nilcheck.go
│       │   │   │   │   │   │   │   │   │   │   ├── nilcheck_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── numberlines.go
│       │   │   │   │   │   │   │   │   │   │   ├── opGen.go
│       │   │   │   │   │   │   │   │   │   │   ├── op.go
│       │   │   │   │   │   │   │   │   │   │   ├── opt.go
│       │   │   │   │   │   │   │   │   │   │   ├── passbm_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── phiopt.go
│       │   │   │   │   │   │   │   │   │   │   ├── poset.go
│       │   │   │   │   │   │   │   │   │   │   ├── poset_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── print.go
│       │   │   │   │   │   │   │   │   │   │   ├── prove.go
│       │   │   │   │   │   │   │   │   │   │   ├── README.md
│       │   │   │   │   │   │   │   │   │   │   ├── regalloc.go
│       │   │   │   │   │   │   │   │   │   │   ├── regalloc_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewrite386.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewrite386splitload.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteAMD64.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteAMD64latelower.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteAMD64splitload.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteARM64.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteARM64latelower.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteARM.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteCond_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewritedec64.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewritedec.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewritegeneric.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewrite.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteLOONG64.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteMIPS64.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteMIPS.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewritePPC64.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewritePPC64latelower.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteRISCV64.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteRISCV64latelower.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteS390X.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewrite_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── rewriteWasm.go
│       │   │   │   │   │   │   │   │   │   │   ├── sccp.go
│       │   │   │   │   │   │   │   │   │   │   ├── sccp_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── schedule.go
│       │   │   │   │   │   │   │   │   │   │   ├── schedule_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── shift_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── shortcircuit.go
│       │   │   │   │   │   │   │   │   │   │   ├── shortcircuit_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── sizeof_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── softfloat.go
│       │   │   │   │   │   │   │   │   │   │   ├── sparsemap.go
│       │   │   │   │   │   │   │   │   │   │   ├── sparsemappos.go
│       │   │   │   │   │   │   │   │   │   │   ├── sparseset.go
│       │   │   │   │   │   │   │   │   │   │   ├── sparsetree.go
│       │   │   │   │   │   │   │   │   │   │   ├── stackalloc.go
│       │   │   │   │   │   │   │   │   │   │   ├── stmtlines_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   │   │   ├── b53456.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── convertline.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── fma.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── hist.dlv-dbg.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── hist.dlv-opt.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── hist.gdb-dbg.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── hist.gdb-opt.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── hist.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── i22558.dlv-dbg.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── i22558.gdb-dbg.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── i22558.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── i22600.dlv-dbg-race.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── i22600.gdb-dbg-race.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── i22600.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── infloop.dlv-opt.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── infloop.gdb-opt.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── infloop.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── inline-dump.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── pushback.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── sayhi.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── scopes.dlv-dbg.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── scopes.dlv-opt.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── scopes.gdb-dbg.nexts
│       │   │   │   │   │   │   │   │   │   │   │   ├── scopes.gdb-opt.nexts
│       │   │   │   │   │   │   │   │   │   │   │   └── scopes.go
│       │   │   │   │   │   │   │   │   │   │   ├── tighten.go
│       │   │   │   │   │   │   │   │   │   │   ├── TODO
│       │   │   │   │   │   │   │   │   │   │   ├── trim.go
│       │   │   │   │   │   │   │   │   │   │   ├── tuple.go
│       │   │   │   │   │   │   │   │   │   │   ├── value.go
│       │   │   │   │   │   │   │   │   │   │   ├── writebarrier.go
│       │   │   │   │   │   │   │   │   │   │   ├── writebarrier_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── xposmap.go
│       │   │   │   │   │   │   │   │   │   │   ├── zcse.go
│       │   │   │   │   │   │   │   │   │   │   └── zeroextension_test.go
│       │   │   │   │   │   │   │   │   │   ├── ssagen
│       │   │   │   │   │   │   │   │   │   │   ├── abi.go
│       │   │   │   │   │   │   │   │   │   │   ├── arch.go
│       │   │   │   │   │   │   │   │   │   │   ├── nowb.go
│       │   │   │   │   │   │   │   │   │   │   ├── pgen.go
│       │   │   │   │   │   │   │   │   │   │   ├── phi.go
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   ├── staticdata
│       │   │   │   │   │   │   │   │   │   │   ├── data.go
│       │   │   │   │   │   │   │   │   │   │   └── embed.go
│       │   │   │   │   │   │   │   │   │   ├── staticinit
│       │   │   │   │   │   │   │   │   │   │   └── sched.go
│       │   │   │   │   │   │   │   │   │   ├── syntax
│       │   │   │   │   │   │   │   │   │   │   ├── branches.go
│       │   │   │   │   │   │   │   │   │   │   ├── dumper.go
│       │   │   │   │   │   │   │   │   │   │   ├── dumper_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── error_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── issues_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── nodes.go
│       │   │   │   │   │   │   │   │   │   │   ├── nodes_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── operator_string.go
│       │   │   │   │   │   │   │   │   │   │   ├── parser.go
│       │   │   │   │   │   │   │   │   │   │   ├── parser_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── pos.go
│       │   │   │   │   │   │   │   │   │   │   ├── positions.go
│       │   │   │   │   │   │   │   │   │   │   ├── printer.go
│       │   │   │   │   │   │   │   │   │   │   ├── printer_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── scanner.go
│       │   │   │   │   │   │   │   │   │   │   ├── scanner_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── source.go
│       │   │   │   │   │   │   │   │   │   │   ├── syntax.go
│       │   │   │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   │   │   ├── chans.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── fallthrough.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── interface.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue20789.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue23385.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue23434.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue31092.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue43527.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue43674.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue46558.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue47704.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue48382.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue49205.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue49482.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue52391.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue56022.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue60599.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue63835.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── issue65790.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── linalg.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── map2.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── map.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── sample.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── slices.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── smoketest.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── tparams.go
│       │   │   │   │   │   │   │   │   │   │   │   └── typeset.go
│       │   │   │   │   │   │   │   │   │   │   ├── testing.go
│       │   │   │   │   │   │   │   │   │   │   ├── testing_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── tokens.go
│       │   │   │   │   │   │   │   │   │   │   ├── token_string.go
│       │   │   │   │   │   │   │   │   │   │   ├── type.go
│       │   │   │   │   │   │   │   │   │   │   └── walk.go
│       │   │   │   │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   │   │   │   ├── abiutilsaux_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── abiutils_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── align_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── bench_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── clobberdead_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── constFold_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── dep_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── divconst_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── fixedbugs_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── float_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── global_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── iface_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── inl_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── inst_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── intrinsics_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue50182_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue53888_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── issue57434_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── lang_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── logic_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── math_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── memcombine_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── mergelocals_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── mulconst_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── pgo_devirtualize_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── pgo_inl_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── race.go
│       │   │   │   │   │   │   │   │   │   │   ├── README
│       │   │   │   │   │   │   │   │   │   │   ├── reproduciblebuilds_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── shift_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── ssa_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── switch_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   │   │   ├── addressed_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── append_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── arithBoundary_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── arithConst_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── arith_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── array_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── assert_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── break_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── chan_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── closure_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── cmpConst_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── cmp_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── compound_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── copy_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── ctl_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── deferNoReturn_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── divbyzero_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── dupLoad_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── flowgraph_generator1.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── fp_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── gen
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── arithBoundaryGen.go
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── arithConstGen.go
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── cmpConstGen.go
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── constFoldGen.go
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── copyGen.go
│       │   │   │   │   │   │   │   │   │   │   │   │   └── zeroGen.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── loadstore_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── map_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── mergelocals
│       │   │   │   │   │   │   │   │   │   │   │   │   └── integration.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── mysort
│       │   │   │   │   │   │   │   │   │   │   │   │   └── mysort.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── namedReturn_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── pgo
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── devirtualize
│       │   │   │   │   │   │   │   │   │   │   │   │   │   ├── devirt.go
│       │   │   │   │   │   │   │   │   │   │   │   │   │   ├── devirt.pprof
│       │   │   │   │   │   │   │   │   │   │   │   │   │   ├── devirt.pprof.node_map
│       │   │   │   │   │   │   │   │   │   │   │   │   │   ├── devirt_test.go
│       │   │   │   │   │   │   │   │   │   │   │   │   │   └── mult.pkg
│       │   │   │   │   │   │   │   │   │   │   │   │   │       └── mult.go
│       │   │   │   │   │   │   │   │   │   │   │   │   └── inline
│       │   │   │   │   │   │   │   │   │   │   │   │       ├── inline_hot.go
│       │   │   │   │   │   │   │   │   │   │   │   │       ├── inline_hot.pprof
│       │   │   │   │   │   │   │   │   │   │   │   │       ├── inline_hot.pprof.node_map
│       │   │   │   │   │   │   │   │   │   │   │   │       └── inline_hot_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── phi_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── ptrsort.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── ptrsort.out
│       │   │   │   │   │   │   │   │   │   │   │   ├── regalloc_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── reproducible
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── issue20272.go
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── issue27013.go
│       │   │   │   │   │   │   │   │   │   │   │   │   ├── issue30202.go
│       │   │   │   │   │   │   │   │   │   │   │   │   └── issue38068.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── short_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── slice_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── sqrtConst_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── string_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── unsafe_test.go
│       │   │   │   │   │   │   │   │   │   │   │   └── zero_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── test.go
│       │   │   │   │   │   │   │   │   │   │   ├── truncconst_test.go
│       │   │   │   │   │   │   │   │   │   │   └── zerorange_test.go
│       │   │   │   │   │   │   │   │   │   ├── typebits
│       │   │   │   │   │   │   │   │   │   │   └── typebits.go
│       │   │   │   │   │   │   │   │   │   ├── typecheck
│       │   │   │   │   │   │   │   │   │   │   ├── bexport.go
│       │   │   │   │   │   │   │   │   │   │   ├── _builtin
│       │   │   │   │   │   │   │   │   │   │   │   ├── coverage.go
│       │   │   │   │   │   │   │   │   │   │   │   └── runtime.go
│       │   │   │   │   │   │   │   │   │   │   ├── builtin.go
│       │   │   │   │   │   │   │   │   │   │   ├── builtin_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── const.go
│       │   │   │   │   │   │   │   │   │   │   ├── dcl.go
│       │   │   │   │   │   │   │   │   │   │   ├── export.go
│       │   │   │   │   │   │   │   │   │   │   ├── expr.go
│       │   │   │   │   │   │   │   │   │   │   ├── func.go
│       │   │   │   │   │   │   │   │   │   │   ├── iexport.go
│       │   │   │   │   │   │   │   │   │   │   ├── iimport.go
│       │   │   │   │   │   │   │   │   │   │   ├── mkbuiltin.go
│       │   │   │   │   │   │   │   │   │   │   ├── stmt.go
│       │   │   │   │   │   │   │   │   │   │   ├── subr.go
│       │   │   │   │   │   │   │   │   │   │   ├── syms.go
│       │   │   │   │   │   │   │   │   │   │   ├── target.go
│       │   │   │   │   │   │   │   │   │   │   ├── typecheck.go
│       │   │   │   │   │   │   │   │   │   │   ├── type.go
│       │   │   │   │   │   │   │   │   │   │   └── universe.go
│       │   │   │   │   │   │   │   │   │   ├── types
│       │   │   │   │   │   │   │   │   │   │   ├── alg.go
│       │   │   │   │   │   │   │   │   │   │   ├── algkind_string.go
│       │   │   │   │   │   │   │   │   │   │   ├── fmt.go
│       │   │   │   │   │   │   │   │   │   │   ├── goversion.go
│       │   │   │   │   │   │   │   │   │   │   ├── identity.go
│       │   │   │   │   │   │   │   │   │   │   ├── kind_string.go
│       │   │   │   │   │   │   │   │   │   │   ├── pkg.go
│       │   │   │   │   │   │   │   │   │   │   ├── size.go
│       │   │   │   │   │   │   │   │   │   │   ├── sizeof_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── sort.go
│       │   │   │   │   │   │   │   │   │   │   ├── sym.go
│       │   │   │   │   │   │   │   │   │   │   ├── sym_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── type.go
│       │   │   │   │   │   │   │   │   │   │   ├── type_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── universe.go
│       │   │   │   │   │   │   │   │   │   │   └── utils.go
│       │   │   │   │   │   │   │   │   │   ├── types2
│       │   │   │   │   │   │   │   │   │   │   ├── alias.go
│       │   │   │   │   │   │   │   │   │   │   ├── api.go
│       │   │   │   │   │   │   │   │   │   │   ├── api_predicates.go
│       │   │   │   │   │   │   │   │   │   │   ├── api_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── array.go
│       │   │   │   │   │   │   │   │   │   │   ├── assignments.go
│       │   │   │   │   │   │   │   │   │   │   ├── basic.go
│       │   │   │   │   │   │   │   │   │   │   ├── builtins.go
│       │   │   │   │   │   │   │   │   │   │   ├── builtins_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── call.go
│       │   │   │   │   │   │   │   │   │   │   ├── chan.go
│       │   │   │   │   │   │   │   │   │   │   ├── check.go
│       │   │   │   │   │   │   │   │   │   │   ├── check_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── compiler_internal.go
│       │   │   │   │   │   │   │   │   │   │   ├── compilersupport.go
│       │   │   │   │   │   │   │   │   │   │   ├── const.go
│       │   │   │   │   │   │   │   │   │   │   ├── context.go
│       │   │   │   │   │   │   │   │   │   │   ├── context_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── conversions.go
│       │   │   │   │   │   │   │   │   │   │   ├── decl.go
│       │   │   │   │   │   │   │   │   │   │   ├── errorcalls_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── errors.go
│       │   │   │   │   │   │   │   │   │   │   ├── errors_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── errsupport.go
│       │   │   │   │   │   │   │   │   │   │   ├── example_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── expr.go
│       │   │   │   │   │   │   │   │   │   │   ├── format.go
│       │   │   │   │   │   │   │   │   │   │   ├── gccgosizes.go
│       │   │   │   │   │   │   │   │   │   │   ├── gcsizes.go
│       │   │   │   │   │   │   │   │   │   │   ├── hilbert_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── importer_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── index.go
│       │   │   │   │   │   │   │   │   │   │   ├── infer.go
│       │   │   │   │   │   │   │   │   │   │   ├── initorder.go
│       │   │   │   │   │   │   │   │   │   │   ├── instantiate.go
│       │   │   │   │   │   │   │   │   │   │   ├── instantiate_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── interface.go
│       │   │   │   │   │   │   │   │   │   │   ├── issues_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── labels.go
│       │   │   │   │   │   │   │   │   │   │   ├── lookup.go
│       │   │   │   │   │   │   │   │   │   │   ├── lookup_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── main_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── map.go
│       │   │   │   │   │   │   │   │   │   │   ├── mono.go
│       │   │   │   │   │   │   │   │   │   │   ├── mono_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── named.go
│       │   │   │   │   │   │   │   │   │   │   ├── named_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── object.go
│       │   │   │   │   │   │   │   │   │   │   ├── object_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── objset.go
│       │   │   │   │   │   │   │   │   │   │   ├── operand.go
│       │   │   │   │   │   │   │   │   │   │   ├── package.go
│       │   │   │   │   │   │   │   │   │   │   ├── pointer.go
│       │   │   │   │   │   │   │   │   │   │   ├── predicates.go
│       │   │   │   │   │   │   │   │   │   │   ├── resolver.go
│       │   │   │   │   │   │   │   │   │   │   ├── resolver_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── return.go
│       │   │   │   │   │   │   │   │   │   │   ├── scope.go
│       │   │   │   │   │   │   │   │   │   │   ├── selection.go
│       │   │   │   │   │   │   │   │   │   │   ├── self_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── signature.go
│       │   │   │   │   │   │   │   │   │   │   ├── sizeof_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── sizes.go
│       │   │   │   │   │   │   │   │   │   │   ├── sizes_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── slice.go
│       │   │   │   │   │   │   │   │   │   │   ├── stdlib_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── stmt.go
│       │   │   │   │   │   │   │   │   │   │   ├── struct.go
│       │   │   │   │   │   │   │   │   │   │   ├── subst.go
│       │   │   │   │   │   │   │   │   │   │   ├── termlist.go
│       │   │   │   │   │   │   │   │   │   │   ├── termlist_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   │   │   ├── local
│       │   │   │   │   │   │   │   │   │   │   │   │   └── issue47996.go
│       │   │   │   │   │   │   │   │   │   │   │   └── manual.go
│       │   │   │   │   │   │   │   │   │   │   ├── tuple.go
│       │   │   │   │   │   │   │   │   │   │   ├── type.go
│       │   │   │   │   │   │   │   │   │   │   ├── typelists.go
│       │   │   │   │   │   │   │   │   │   │   ├── typeparam.go
│       │   │   │   │   │   │   │   │   │   │   ├── typeset.go
│       │   │   │   │   │   │   │   │   │   │   ├── typeset_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── typestring.go
│       │   │   │   │   │   │   │   │   │   │   ├── typestring_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── typeterm.go
│       │   │   │   │   │   │   │   │   │   │   ├── typeterm_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── typexpr.go
│       │   │   │   │   │   │   │   │   │   │   ├── under.go
│       │   │   │   │   │   │   │   │   │   │   ├── unify.go
│       │   │   │   │   │   │   │   │   │   │   ├── union.go
│       │   │   │   │   │   │   │   │   │   │   ├── universe.go
│       │   │   │   │   │   │   │   │   │   │   ├── util.go
│       │   │   │   │   │   │   │   │   │   │   ├── util_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── validtype.go
│       │   │   │   │   │   │   │   │   │   │   └── version.go
│       │   │   │   │   │   │   │   │   │   ├── walk
│       │   │   │   │   │   │   │   │   │   │   ├── assign.go
│       │   │   │   │   │   │   │   │   │   │   ├── builtin.go
│       │   │   │   │   │   │   │   │   │   │   ├── closure.go
│       │   │   │   │   │   │   │   │   │   │   ├── compare.go
│       │   │   │   │   │   │   │   │   │   │   ├── complit.go
│       │   │   │   │   │   │   │   │   │   │   ├── convert.go
│       │   │   │   │   │   │   │   │   │   │   ├── expr.go
│       │   │   │   │   │   │   │   │   │   │   ├── order.go
│       │   │   │   │   │   │   │   │   │   │   ├── range.go
│       │   │   │   │   │   │   │   │   │   │   ├── select.go
│       │   │   │   │   │   │   │   │   │   │   ├── stmt.go
│       │   │   │   │   │   │   │   │   │   │   ├── switch.go
│       │   │   │   │   │   │   │   │   │   │   ├── temp.go
│       │   │   │   │   │   │   │   │   │   │   └── walk.go
│       │   │   │   │   │   │   │   │   │   ├── wasm
│       │   │   │   │   │   │   │   │   │   │   └── ssa.go
│       │   │   │   │   │   │   │   │   │   └── x86
│       │   │   │   │   │   │   │   │   │       ├── galign.go
│       │   │   │   │   │   │   │   │   │       ├── ggen.go
│       │   │   │   │   │   │   │   │   │       └── ssa.go
│       │   │   │   │   │   │   │   │   ├── main.go
│       │   │   │   │   │   │   │   │   ├── profile.sh
│       │   │   │   │   │   │   │   │   └── README.md
│       │   │   │   │   │   │   │   ├── covdata
│       │   │   │   │   │   │   │   │   ├── argsmerge.go
│       │   │   │   │   │   │   │   │   ├── covdata.go
│       │   │   │   │   │   │   │   │   ├── doc.go
│       │   │   │   │   │   │   │   │   ├── dump.go
│       │   │   │   │   │   │   │   │   ├── export_test.go
│       │   │   │   │   │   │   │   │   ├── merge.go
│       │   │   │   │   │   │   │   │   ├── metamerge.go
│       │   │   │   │   │   │   │   │   ├── subtractintersect.go
│       │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   ├── dep.go
│       │   │   │   │   │   │   │   │   │   ├── prog1.go
│       │   │   │   │   │   │   │   │   │   └── prog2.go
│       │   │   │   │   │   │   │   │   └── tool_test.go
│       │   │   │   │   │   │   │   ├── cover
│       │   │   │   │   │   │   │   │   ├── cfg_test.go
│       │   │   │   │   │   │   │   │   ├── cover.go
│       │   │   │   │   │   │   │   │   ├── cover_test.go
│       │   │   │   │   │   │   │   │   ├── doc.go
│       │   │   │   │   │   │   │   │   ├── export_test.go
│       │   │   │   │   │   │   │   │   ├── func.go
│       │   │   │   │   │   │   │   │   ├── html.go
│       │   │   │   │   │   │   │   │   ├── pkgname_test.go
│       │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │       ├── directives.go
│       │   │   │   │   │   │   │   │       ├── html
│       │   │   │   │   │   │   │   │       │   ├── html.go
│       │   │   │   │   │   │   │   │       │   ├── html.golden
│       │   │   │   │   │   │   │   │       │   └── html_test.go
│       │   │   │   │   │   │   │   │       ├── main.go
│       │   │   │   │   │   │   │   │       ├── p.go
│       │   │   │   │   │   │   │   │       ├── pkgcfg
│       │   │   │   │   │   │   │   │       │   ├── a
│       │   │   │   │   │   │   │   │       │   │   ├── a2.go
│       │   │   │   │   │   │   │   │       │   │   ├── a.go
│       │   │   │   │   │   │   │   │       │   │   └── a_test.go
│       │   │   │   │   │   │   │   │       │   ├── noFuncsNoTests
│       │   │   │   │   │   │   │   │       │   │   └── nfnt.go
│       │   │   │   │   │   │   │   │       │   └── yesFuncsNoTests
│       │   │   │   │   │   │   │   │       │       └── yfnt.go
│       │   │   │   │   │   │   │   │       ├── profile.cov
│       │   │   │   │   │   │   │   │       └── test.go
│       │   │   │   │   │   │   │   ├── dist
│       │   │   │   │   │   │   │   │   ├── build.go
│       │   │   │   │   │   │   │   │   ├── buildgo.go
│       │   │   │   │   │   │   │   │   ├── buildruntime.go
│       │   │   │   │   │   │   │   │   ├── buildtag.go
│       │   │   │   │   │   │   │   │   ├── buildtag_test.go
│       │   │   │   │   │   │   │   │   ├── build_test.go
│       │   │   │   │   │   │   │   │   ├── buildtool.go
│       │   │   │   │   │   │   │   │   ├── doc.go
│       │   │   │   │   │   │   │   │   ├── exec.go
│       │   │   │   │   │   │   │   │   ├── imports.go
│       │   │   │   │   │   │   │   │   ├── main.go
│       │   │   │   │   │   │   │   │   ├── notgo120.go
│       │   │   │   │   │   │   │   │   ├── quoted.go
│       │   │   │   │   │   │   │   │   ├── README
│       │   │   │   │   │   │   │   │   ├── supported_test.go
│       │   │   │   │   │   │   │   │   ├── sys_default.go
│       │   │   │   │   │   │   │   │   ├── sys_windows.go
│       │   │   │   │   │   │   │   │   ├── test.go
│       │   │   │   │   │   │   │   │   ├── testjson.go
│       │   │   │   │   │   │   │   │   ├── testjson_test.go
│       │   │   │   │   │   │   │   │   ├── util_gccgo.go
│       │   │   │   │   │   │   │   │   ├── util_gc.go
│       │   │   │   │   │   │   │   │   ├── util.go
│       │   │   │   │   │   │   │   │   ├── vfp_arm.s
│       │   │   │   │   │   │   │   │   └── vfp_default.s
│       │   │   │   │   │   │   │   ├── distpack
│       │   │   │   │   │   │   │   │   ├── archive.go
│       │   │   │   │   │   │   │   │   ├── archive_test.go
│       │   │   │   │   │   │   │   │   ├── pack.go
│       │   │   │   │   │   │   │   │   └── test.go
│       │   │   │   │   │   │   │   ├── doc
│       │   │   │   │   │   │   │   │   ├── dirs.go
│       │   │   │   │   │   │   │   │   ├── doc_test.go
│       │   │   │   │   │   │   │   │   ├── main.go
│       │   │   │   │   │   │   │   │   ├── pkg.go
│       │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │       ├── merge
│       │   │   │   │   │   │   │   │       │   ├── aa.go
│       │   │   │   │   │   │   │   │       │   └── bb.go
│       │   │   │   │   │   │   │   │       ├── nested
│       │   │   │   │   │   │   │   │       │   ├── empty
│       │   │   │   │   │   │   │   │       │   │   └── empty.go
│       │   │   │   │   │   │   │   │       │   ├── ignore.go
│       │   │   │   │   │   │   │   │       │   └── nested
│       │   │   │   │   │   │   │   │       │       └── real.go
│       │   │   │   │   │   │   │   │       └── pkg.go
│       │   │   │   │   │   │   │   ├── fix
│       │   │   │   │   │   │   │   │   ├── buildtag.go
│       │   │   │   │   │   │   │   │   ├── buildtag_test.go
│       │   │   │   │   │   │   │   │   ├── cftype.go
│       │   │   │   │   │   │   │   │   ├── cftype_test.go
│       │   │   │   │   │   │   │   │   ├── context.go
│       │   │   │   │   │   │   │   │   ├── context_test.go
│       │   │   │   │   │   │   │   │   ├── doc.go
│       │   │   │   │   │   │   │   │   ├── egltype.go
│       │   │   │   │   │   │   │   │   ├── egltype_test.go
│       │   │   │   │   │   │   │   │   ├── fix.go
│       │   │   │   │   │   │   │   │   ├── gotypes.go
│       │   │   │   │   │   │   │   │   ├── gotypes_test.go
│       │   │   │   │   │   │   │   │   ├── import_test.go
│       │   │   │   │   │   │   │   │   ├── jnitype.go
│       │   │   │   │   │   │   │   │   ├── jnitype_test.go
│       │   │   │   │   │   │   │   │   ├── main.go
│       │   │   │   │   │   │   │   │   ├── main_test.go
│       │   │   │   │   │   │   │   │   ├── netipv6zone.go
│       │   │   │   │   │   │   │   │   ├── netipv6zone_test.go
│       │   │   │   │   │   │   │   │   ├── printerconfig.go
│       │   │   │   │   │   │   │   │   ├── printerconfig_test.go
│       │   │   │   │   │   │   │   │   └── typecheck.go
│       │   │   │   │   │   │   │   ├── go
│       │   │   │   │   │   │   │   │   ├── alldocs.go
│       │   │   │   │   │   │   │   │   ├── chdir_test.go
│       │   │   │   │   │   │   │   │   ├── export_test.go
│       │   │   │   │   │   │   │   │   ├── go11.go
│       │   │   │   │   │   │   │   │   ├── go_boring_test.go
│       │   │   │   │   │   │   │   │   ├── go_test.go
│       │   │   │   │   │   │   │   │   ├── go_unix_test.go
│       │   │   │   │   │   │   │   │   ├── go_windows_test.go
│       │   │   │   │   │   │   │   │   ├── help_test.go
│       │   │   │   │   │   │   │   │   ├── init_test.go
│       │   │   │   │   │   │   │   │   ├── internal
│       │   │   │   │   │   │   │   │   │   ├── auth
│       │   │   │   │   │   │   │   │   │   │   ├── auth.go
│       │   │   │   │   │   │   │   │   │   │   ├── netrc.go
│       │   │   │   │   │   │   │   │   │   │   └── netrc_test.go
│       │   │   │   │   │   │   │   │   │   ├── base
│       │   │   │   │   │   │   │   │   │   │   ├── base.go
│       │   │   │   │   │   │   │   │   │   │   ├── env.go
│       │   │   │   │   │   │   │   │   │   │   ├── flag.go
│       │   │   │   │   │   │   │   │   │   │   ├── goflags.go
│       │   │   │   │   │   │   │   │   │   │   ├── limit.go
│       │   │   │   │   │   │   │   │   │   │   ├── path.go
│       │   │   │   │   │   │   │   │   │   │   ├── signal.go
│       │   │   │   │   │   │   │   │   │   │   ├── signal_notunix.go
│       │   │   │   │   │   │   │   │   │   │   ├── signal_unix.go
│       │   │   │   │   │   │   │   │   │   │   └── tool.go
│       │   │   │   │   │   │   │   │   │   ├── bug
│       │   │   │   │   │   │   │   │   │   │   └── bug.go
│       │   │   │   │   │   │   │   │   │   ├── cache
│       │   │   │   │   │   │   │   │   │   │   ├── cache.go
│       │   │   │   │   │   │   │   │   │   │   ├── cache_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── default.go
│       │   │   │   │   │   │   │   │   │   │   ├── hash.go
│       │   │   │   │   │   │   │   │   │   │   ├── hash_test.go
│       │   │   │   │   │   │   │   │   │   │   └── prog.go
│       │   │   │   │   │   │   │   │   │   ├── cfg
│       │   │   │   │   │   │   │   │   │   │   ├── bench_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cfg.go
│       │   │   │   │   │   │   │   │   │   │   ├── lookpath.go
│       │   │   │   │   │   │   │   │   │   │   └── zdefaultcc.go
│       │   │   │   │   │   │   │   │   │   ├── clean
│       │   │   │   │   │   │   │   │   │   │   └── clean.go
│       │   │   │   │   │   │   │   │   │   ├── cmdflag
│       │   │   │   │   │   │   │   │   │   │   └── flag.go
│       │   │   │   │   │   │   │   │   │   ├── doc
│       │   │   │   │   │   │   │   │   │   │   └── doc.go
│       │   │   │   │   │   │   │   │   │   ├── envcmd
│       │   │   │   │   │   │   │   │   │   │   ├── env.go
│       │   │   │   │   │   │   │   │   │   │   └── env_test.go
│       │   │   │   │   │   │   │   │   │   ├── fix
│       │   │   │   │   │   │   │   │   │   │   └── fix.go
│       │   │   │   │   │   │   │   │   │   ├── fmtcmd
│       │   │   │   │   │   │   │   │   │   │   └── fmt.go
│       │   │   │   │   │   │   │   │   │   ├── fsys
│       │   │   │   │   │   │   │   │   │   │   ├── fsys.go
│       │   │   │   │   │   │   │   │   │   │   └── fsys_test.go
│       │   │   │   │   │   │   │   │   │   ├── generate
│       │   │   │   │   │   │   │   │   │   │   ├── generate.go
│       │   │   │   │   │   │   │   │   │   │   └── generate_test.go
│       │   │   │   │   │   │   │   │   │   ├── gover
│       │   │   │   │   │   │   │   │   │   │   ├── gomod.go
│       │   │   │   │   │   │   │   │   │   │   ├── gover.go
│       │   │   │   │   │   │   │   │   │   │   ├── gover_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── local.go
│       │   │   │   │   │   │   │   │   │   │   ├── mod.go
│       │   │   │   │   │   │   │   │   │   │   ├── mod_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── toolchain.go
│       │   │   │   │   │   │   │   │   │   │   ├── toolchain_test.go
│       │   │   │   │   │   │   │   │   │   │   └── version.go
│       │   │   │   │   │   │   │   │   │   ├── help
│       │   │   │   │   │   │   │   │   │   │   ├── helpdoc.go
│       │   │   │   │   │   │   │   │   │   │   └── help.go
│       │   │   │   │   │   │   │   │   │   ├── imports
│       │   │   │   │   │   │   │   │   │   │   ├── build.go
│       │   │   │   │   │   │   │   │   │   │   ├── read.go
│       │   │   │   │   │   │   │   │   │   │   ├── read_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── scan.go
│       │   │   │   │   │   │   │   │   │   │   ├── scan_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── tags.go
│       │   │   │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │   │   │       ├── android
│       │   │   │   │   │   │   │   │   │   │       │   ├── a_android.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── b_android_arm64.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── c_linux.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── d_linux_arm64.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── e.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── f.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── g.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── tags.txt
│       │   │   │   │   │   │   │   │   │   │       │   └── want.txt
│       │   │   │   │   │   │   │   │   │   │       ├── illumos
│       │   │   │   │   │   │   │   │   │   │       │   ├── a_illumos.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── b_illumos_amd64.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── c_solaris.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── d_solaris_amd64.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── e.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── f.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── g.go
│       │   │   │   │   │   │   │   │   │   │       │   ├── tags.txt
│       │   │   │   │   │   │   │   │   │   │       │   └── want.txt
│       │   │   │   │   │   │   │   │   │   │       └── star
│       │   │   │   │   │   │   │   │   │   │           ├── tags.txt
│       │   │   │   │   │   │   │   │   │   │           ├── want.txt
│       │   │   │   │   │   │   │   │   │   │           ├── x1.go
│       │   │   │   │   │   │   │   │   │   │           ├── x_darwin.go
│       │   │   │   │   │   │   │   │   │   │           ├── x.go
│       │   │   │   │   │   │   │   │   │   │           └── x_windows.go
│       │   │   │   │   │   │   │   │   │   ├── list
│       │   │   │   │   │   │   │   │   │   │   ├── context.go
│       │   │   │   │   │   │   │   │   │   │   └── list.go
│       │   │   │   │   │   │   │   │   │   ├── load
│       │   │   │   │   │   │   │   │   │   │   ├── flag.go
│       │   │   │   │   │   │   │   │   │   │   ├── flag_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── godebug.go
│       │   │   │   │   │   │   │   │   │   │   ├── path.go
│       │   │   │   │   │   │   │   │   │   │   ├── pkg.go
│       │   │   │   │   │   │   │   │   │   │   ├── pkg_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── search.go
│       │   │   │   │   │   │   │   │   │   │   └── test.go
│       │   │   │   │   │   │   │   │   │   ├── lockedfile
│       │   │   │   │   │   │   │   │   │   │   ├── internal
│       │   │   │   │   │   │   │   │   │   │   │   └── filelock
│       │   │   │   │   │   │   │   │   │   │   │       ├── filelock_fcntl.go
│       │   │   │   │   │   │   │   │   │   │   │       ├── filelock.go
│       │   │   │   │   │   │   │   │   │   │   │       ├── filelock_other.go
│       │   │   │   │   │   │   │   │   │   │   │       ├── filelock_test.go
│       │   │   │   │   │   │   │   │   │   │   │       ├── filelock_unix.go
│       │   │   │   │   │   │   │   │   │   │   │       └── filelock_windows.go
│       │   │   │   │   │   │   │   │   │   │   ├── lockedfile_filelock.go
│       │   │   │   │   │   │   │   │   │   │   ├── lockedfile.go
│       │   │   │   │   │   │   │   │   │   │   ├── lockedfile_plan9.go
│       │   │   │   │   │   │   │   │   │   │   ├── lockedfile_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── mutex.go
│       │   │   │   │   │   │   │   │   │   │   └── transform_test.go
│       │   │   │   │   │   │   │   │   │   ├── mmap
│       │   │   │   │   │   │   │   │   │   │   ├── mmap.go
│       │   │   │   │   │   │   │   │   │   │   ├── mmap_other.go
│       │   │   │   │   │   │   │   │   │   │   ├── mmap_unix.go
│       │   │   │   │   │   │   │   │   │   │   └── mmap_windows.go
│       │   │   │   │   │   │   │   │   │   ├── modcmd
│       │   │   │   │   │   │   │   │   │   │   ├── download.go
│       │   │   │   │   │   │   │   │   │   │   ├── edit.go
│       │   │   │   │   │   │   │   │   │   │   ├── graph.go
│       │   │   │   │   │   │   │   │   │   │   ├── init.go
│       │   │   │   │   │   │   │   │   │   │   ├── mod.go
│       │   │   │   │   │   │   │   │   │   │   ├── tidy.go
│       │   │   │   │   │   │   │   │   │   │   ├── vendor.go
│       │   │   │   │   │   │   │   │   │   │   ├── verify.go
│       │   │   │   │   │   │   │   │   │   │   └── why.go
│       │   │   │   │   │   │   │   │   │   ├── modfetch
│       │   │   │   │   │   │   │   │   │   │   ├── bootstrap.go
│       │   │   │   │   │   │   │   │   │   │   ├── cache.go
│       │   │   │   │   │   │   │   │   │   │   ├── cache_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── codehost
│       │   │   │   │   │   │   │   │   │   │   │   ├── codehost.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── git.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── git_test.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── shell.go
│       │   │   │   │   │   │   │   │   │   │   │   ├── svn.go
│       │   │   │   │   │   │   │   │   │   │   │   └── vcs.go
│       │   │   │   │   │   │   │   │   │   │   ├── coderepo.go
│       │   │   │   │   │   │   │   │   │   │   ├── coderepo_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── fetch.go
│       │   │   │   │   │   │   │   │   │   │   ├── key.go
│       │   │   │   │   │   │   │   │   │   │   ├── proxy.go
│       │   │   │   │   │   │   │   │   │   │   ├── repo.go
│       │   │   │   │   │   │   │   │   │   │   ├── sumdb.go
│       │   │   │   │   │   │   │   │   │   │   ├── toolchain.go
│       │   │   │   │   │   │   │   │   │   │   └── zip_sum_test
│       │   │   │   │   │   │   │   │   │   │       ├── testdata
│       │   │   │   │   │   │   │   │   │   │       │   └── zip_sums.csv
│       │   │   │   │   │   │   │   │   │   │       └── zip_sum_test.go
│       │   │   │   │   │   │   │   │   │   ├── modget
│       │   │   │   │   │   │   │   │   │   │   ├── get.go
│       │   │   │   │   │   │   │   │   │   │   └── query.go
│       │   │   │   │   │   │   │   │   │   ├── modindex
│       │   │   │   │   │   │   │   │   │   │   ├── build.go
│       │   │   │   │   │   │   │   │   │   │   ├── build_read.go
│       │   │   │   │   │   │   │   │   │   │   ├── index_format.txt
│       │   │   │   │   │   │   │   │   │   │   ├── index_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── read.go
│       │   │   │   │   │   │   │   │   │   │   ├── scan.go
│       │   │   │   │   │   │   │   │   │   │   ├── syslist.go
│       │   │   │   │   │   │   │   │   │   │   ├── syslist_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── testdata
│       │   │   │   │   │   │   │   │   │   │   │   └── ignore_non_source
│       │   │   │   │   │   │   │   │   │   │   │       ├── a.syso
│       │   │   │   │   │   │   │   │   │   │   │       ├── bar.json
│       │   │   │   │   │   │   │   │   │   │   │       ├── baz.log
│       │   │   │   │   │   │   │   │   │   │   │       ├── b.go
│       │   │   │   │   │   │   │   │   │   │   │       └── c.c
│       │   │   │   │   │   │   │   │   │   │   └── write.go
│       │   │   │   │   │   │   │   │   │   ├── modinfo
│       │   │   │   │   │   │   │   │   │   │   └── info.go
│       │   │   │   │   │   │   │   │   │   ├── modload
│       │   │   │   │   │   │   │   │   │   │   ├── build.go
│       │   │   │   │   │   │   │   │   │   │   ├── buildlist.go
│       │   │   │   │   │   │   │   │   │   │   ├── edit.go
│       │   │   │   │   │   │   │   │   │   │   ├── help.go
│       │   │   │   │   │   │   │   │   │   │   ├── import.go
│       │   │   │   │   │   │   │   │   │   │   ├── import_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── init.go
│       │   │   │   │   │   │   │   │   │   │   ├── list.go
│       │   │   │   │   │   │   │   │   │   │   ├── load.go
│       │   │   │   │   │   │   │   │   │   │   ├── modfile.go
│       │   │   │   │   │   │   │   │   │   │   ├── mvs.go
│       │   │   │   │   │   │   │   │   │   │   ├── mvs_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── query.go
│       │   │   │   │   │   │   │   │   │   │   ├── query_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── search.go
│       │   │   │   │   │   │   │   │   │   │   ├── stat_openfile.go
│       │   │   │   │   │   │   │   │   │   │   ├── stat_unix.go
│       │   │   │   │   │   │   │   │   │   │   ├── stat_windows.go
│       │   │   │   │   │   │   │   │   │   │   └── vendor.go
│       │   │   │   │   │   │   │   │   │   ├── mvs
│       │   │   │   │   │   │   │   │   │   │   ├── errors.go
│       │   │   │   │   │   │   │   │   │   │   ├── graph.go
│       │   │   │   │   │   │   │   │   │   │   ├── mvs.go
│       │   │   │   │   │   │   │   │   │   │   └── mvs_test.go
│       │   │   │   │   │   │   │   │   │   ├── par
│       │   │   │   │   │   │   │   │   │   │   ├── queue.go
│       │   │   │   │   │   │   │   │   │   │   ├── queue_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── work.go
│       │   │   │   │   │   │   │   │   │   │   └── work_test.go
│       │   │   │   │   │   │   │   │   │   ├── robustio
│       │   │   │   │   │   │   │   │   │   │   ├── robustio_darwin.go
│       │   │   │   │   │   │   │   │   │   │   ├── robustio_flaky.go
│       │   │   │   │   │   │   │   │   │   │   ├── robustio.go
│       │   │   │   │   │   │   │   │   │   │   ├── robustio_other.go
│       │   │   │   │   │   │   │   │   │   │   └── robustio_windows.go
│       │   │   │   │   │   │   │   │   │   ├── run
│       │   │   │   │   │   │   │   │   │   │   └── run.go
│       │   │   │   │   │   │   │   │   │   ├── script
│       │   │   │   │   │   │   │   │   │   │   ├── cmds.go
│       │   │   │   │   │   │   │   │   │   │   ├── cmds_nonunix.go
│       │   │   │   │   │   │   │   │   │   │   ├── cmds_unix.go
│       │   │   │   │   │   │   │   │   │   │   ├── conds.go
│       │   │   │   │   │   │   │   │   │   │   ├── engine.go
│       │   │   │   │   │   │   │   │   │   │   ├── errors.go
│       │   │   │   │   │   │   │   │   │   │   ├── scripttest
│       │   │   │   │   │   │   │   │   │   │   │   └── scripttest.go
│       │   │   │   │   │   │   │   │   │   │   └── state.go
│       │   │   │   │   │   │   │   │   │   ├── search
│       │   │   │   │   │   │   │   │   │   │   └── search.go
│       │   │   │   │   │   │   │   │   │   ├── str
│       │   │   │   │   │   │   │   │   │   │   ├── path.go
│       │   │   │   │   │   │   │   │   │   │   ├── str.go
│       │   │   │   │   │   │   │   │   │   │   └── str_test.go
│       │   │   │   │   │   │   │   │   │   ├── telemetrycmd
│       │   │   │   │   │   │   │   │   │   │   └── telemetry.go
│       │   │   │   │   │   │   │   │   │   ├── telemetrystats
│       │   │   │   │   │   │   │   │   │   │   ├── telemetrystats_bootstrap.go
│       │   │   │   │   │   │   │   │   │   │   ├── telemetrystats.go
│       │   │   │   │   │   │   │   │   │   │   ├── version_other.go
│       │   │   │   │   │   │   │   │   │   │   ├── version_unix.go
│       │   │   │   │   │   │   │   │   │   │   └── version_windows.go
│       │   │   │   │   │   │   │   │   │   ├── test
│       │   │   │   │   │   │   │   │   │   │   ├── cover.go
│       │   │   │   │   │   │   │   │   │   │   ├── flagdefs.go
│       │   │   │   │   │   │   │   │   │   │   ├── flagdefs_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── genflags.go
│       │   │   │   │   │   │   │   │   │   │   ├── internal
│       │   │   │   │   │   │   │   │   │   │   │   └── genflags
│       │   │   │   │   │   │   │   │   │   │   │       ├── testflag.go
│       │   │   │   │   │   │   │   │   │   │   │       └── vetflag.go
│       │   │   │   │   │   │   │   │   │   │   ├── testflag.go
│       │   │   │   │   │   │   │   │   │   │   ├── test.go
│       │   │   │   │   │   │   │   │   │   │   ├── test_nonunix.go
│       │   │   │   │   │   │   │   │   │   │   └── test_unix.go
│       │   │   │   │   │   │   │   │   │   ├── tool
│       │   │   │   │   │   │   │   │   │   │   └── tool.go
│       │   │   │   │   │   │   │   │   │   ├── toolchain
│       │   │   │   │   │   │   │   │   │   │   ├── exec.go
│       │   │   │   │   │   │   │   │   │   │   ├── exec_stub.go
│       │   │   │   │   │   │   │   │   │   │   ├── path_none.go
│       │   │   │   │   │   │   │   │   │   │   ├── path_plan9.go
│       │   │   │   │   │   │   │   │   │   │   ├── path_unix.go
│       │   │   │   │   │   │   │   │   │   │   ├── path_windows.go
│       │   │   │   │   │   │   │   │   │   │   ├── select.go
│       │   │   │   │   │   │   │   │   │   │   ├── switch.go
│       │   │   │   │   │   │   │   │   │   │   ├── toolchain_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── umask_none.go
│       │   │   │   │   │   │   │   │   │   │   └── umask_unix.go
│       │   │   │   │   │   │   │   │   │   ├── trace
│       │   │   │   │   │   │   │   │   │   │   └── trace.go
│       │   │   │   │   │   │   │   │   │   ├── vcs
│       │   │   │   │   │   │   │   │   │   │   ├── discovery.go
│       │   │   │   │   │   │   │   │   │   │   ├── discovery_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── vcs.go
│       │   │   │   │   │   │   │   │   │   │   └── vcs_test.go
│       │   │   │   │   │   │   │   │   │   ├── vcweb
│       │   │   │   │   │   │   │   │   │   │   ├── auth.go
│       │   │   │   │   │   │   │   │   │   │   ├── bzr.go
│       │   │   │   │   │   │   │   │   │   │   ├── dir.go
│       │   │   │   │   │   │   │   │   │   │   ├── fossil.go
│       │   │   │   │   │   │   │   │   │   │   ├── git.go
│       │   │   │   │   │   │   │   │   │   │   ├── hg.go
│       │   │   │   │   │   │   │   │   │   │   ├── insecure.go
│       │   │   │   │   │   │   │   │   │   │   ├── script.go
│       │   │   │   │   │   │   │   │   │   │   ├── svn.go
│       │   │   │   │   │   │   │   │   │   │   ├── vcstest
│       │   │   │   │   │   │   │   │   │   │   │   ├── vcstest.go
│       │   │   │   │   │   │   │   │   │   │   │   └── vcstest_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── vcweb.go
│       │   │   │   │   │   │   │   │   │   │   └── vcweb_test.go
│       │   │   │   │   │   │   │   │   │   ├── version
│       │   │   │   │   │   │   │   │   │   │   └── version.go
│       │   │   │   │   │   │   │   │   │   ├── vet
│       │   │   │   │   │   │   │   │   │   │   ├── vetflag.go
│       │   │   │   │   │   │   │   │   │   │   └── vet.go
│       │   │   │   │   │   │   │   │   │   ├── web
│       │   │   │   │   │   │   │   │   │   │   ├── api.go
│       │   │   │   │   │   │   │   │   │   │   ├── bootstrap.go
│       │   │   │   │   │   │   │   │   │   │   ├── file_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── http.go
│       │   │   │   │   │   │   │   │   │   │   ├── url.go
│       │   │   │   │   │   │   │   │   │   │   ├── url_other.go
│       │   │   │   │   │   │   │   │   │   │   ├── url_other_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── url_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── url_windows.go
│       │   │   │   │   │   │   │   │   │   │   └── url_windows_test.go
│       │   │   │   │   │   │   │   │   │   ├── work
│       │   │   │   │   │   │   │   │   │   │   ├── action.go
│       │   │   │   │   │   │   │   │   │   │   ├── build.go
│       │   │   │   │   │   │   │   │   │   │   ├── buildid.go
│       │   │   │   │   │   │   │   │   │   │   ├── build_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── cover.go
│       │   │   │   │   │   │   │   │   │   │   ├── exec.go
│       │   │   │   │   │   │   │   │   │   │   ├── exec_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── gccgo.go
│       │   │   │   │   │   │   │   │   │   │   ├── gc.go
│       │   │   │   │   │   │   │   │   │   │   ├── init.go
│       │   │   │   │   │   │   │   │   │   │   ├── security.go
│       │   │   │   │   │   │   │   │   │   │   ├── security_test.go
│       │   │   │   │   │   │   │   │   │   │   ├── shell.go
│       │   │   │   │   │   │   │   │   │   │   └── shell_test.go
│       │   │   │   │   │   │   │   │   │   └── workcmd
│       │   │   │   │   │   │   │   │   │       ├── edit.go
│       │   │   │   │   │   │   │   │   │       ├── init.go
│       │   │   │   │   │   │   │   │   │       ├── sync.go
│       │   │   │   │   │   │   │   │   │       ├── use.go
│       │   │   │   │   │   │   │   │   │       ├── vendor.go
│       │   │   │   │   │   │   │   │   │       └── work.go
│       │   │   │   │   │   │   │   │   ├── main.go
│       │   │   │   │   │   │   │   │   ├── note_test.go
│       │   │   │   │   │   │   │   │   ├── proxy_test.go
│       │   │   │   │   │   │   │   │   ├── scriptcmds_test.go
│       │   │   │   │   │   │   │   │   ├── scriptconds_test.go
│       │   │   │   │   │   │   │   │   ├── scriptreadme_test.go
│       │   │   │   │   │   │   │   │   ├── script_test.go
│       │   │   │   │   │   │   │   │   ├── stop_other_test.go
│       │   │   │   │   │   │   │   │   ├── stop_unix_test.go
│       │   │   │   │   │   │   │   │   ├── terminal_test.go
│       │   │   │   │   │   │   │   │   └── testdata
│       │   │   │   │   │   │   │   │       ├── addmod.go
│       │   │   │   │   │   │   │   │       ├── mod
│       │   │   │   │   │   │   │   │       │   ├── example.com_ambiguous_a_b_v0.0.0-empty.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_ambiguous_a_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_badchain_a_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_badchain_a_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_badchain_b_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_badchain_b_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_badchain_c_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_badchain_c_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_cmd_v1.0.0-exclude.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_cmd_v1.0.0-newerself.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_cmd_v1.0.0-replace.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_cmd_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_cmd_v1.9.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_depends_on_generics_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_deprecated_a_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_deprecated_a_v1.9.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_deprecated_b_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_deprecated_b_v1.9.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_dotgo.go_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_dotname_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_downgrade_v2.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_downgrade_v2_v2.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_fuzzfail_v0.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_fuzzfail_v0.2.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_generics_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_incompatiblewithsub_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_incompatiblewithsub_v2.0.0+incompatible.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_invalidpath_v1_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_join_subpkg_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_join_subpkg_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_join_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_join_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_latemigrate_v2_v2.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_latemigrate_v2_v2.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_missingpkg_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_missingpkg_v1.0.1-beta.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_nest_sub_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_nest_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_nest_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_newcycle_a_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_newcycle_a_v1.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_newcycle_b_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_noroot_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_noroot_v1.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_notags_v0.0.0-20190507143103-cc8cbe209b64.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_printversion_v0.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_printversion_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_pseudoupgrade_v0.0.0-20190430073000-30950c05d534.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_pseudoupgrade_v0.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_pseudoupgrade_v0.1.1-0.20190429073117-b5426c86b553.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_quote_v1.5.2.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_ambiguous_nested_v1.9.0-bad.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_ambiguous_other_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_ambiguous_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_incompatible_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_incompatible_v2.0.0+incompatible.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_missingmod_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_missingmod_v1.9.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_newergoversion_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_newergoversion_v1.2.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_noupgrade_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.0.0-block.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.0.0-blockwithcomment.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.0.0-empty.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.0.0-long.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.0.0-multiline1.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.0.0-multiline2.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.0.0-order.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.0.0-unprintable.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.0.1-order.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rationale_v1.9.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rename_v1.0.0-bad.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_rename_v1.9.0-new.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_all_v1.9.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_prerelease_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_prerelease_v1.9.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_prerelease_v1.9.1-pre.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_prev_v1.0.0-bad.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_prev_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_prev_v1.9.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_pseudo_v0.0.0-20200325131415-0123456789ab
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_pseudo_v1.0.0-bad.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_self_pseudo_v1.9.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_v1.0.0-bad.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_v1.0.0-good.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_v1.0.0-unused.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_retract_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_split-incompatible_subpkg_v0.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_split-incompatible_v2.0.0+incompatible.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_split-incompatible_v2.1.0-pre+incompatible.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_split_subpkg_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_split_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_split_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_stack_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_stack_v1.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_tools_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_undeprecated_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_undeprecated_v1.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_usemissingpre_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_version_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_version_v1.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── example.com_version_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.net_ambiguous_nested_v0.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.net_ambiguous_v0.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.net_ambiguous_v0.2.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.net_pkgadded_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.net_pkgadded_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── example.net_pkgadded_v1.2.0.txt
│       │   │   │   │   │   │   │   │       │   ├── github.com_dmitshur-test_modtest5_v0.0.0-20190619020302-197a620e0c9a.txt
│       │   │   │   │   │   │   │   │       │   ├── github.com_dmitshur-test_modtest5_v0.5.0-alpha.0.20190619023908-3da23a9deb9e.txt
│       │   │   │   │   │   │   │   │       │   ├── github.com_dmitshur-test_modtest5_v0.5.0-alpha.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_notx_useinternal_v0.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.18.1.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.18.3.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.18.5.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.18.7.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.18.9.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.18.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.22.0.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.22.1.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.22.3.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.22.5.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.22.7.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.22.9.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.22rc1.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.23.0.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.23.5.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.23.9.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.24rc1.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.aix-ppc64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.android-386.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.android-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.android-arm64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.android-arm.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.darwin-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.darwin-arm64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.dragonfly-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.freebsd-386.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.freebsd-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.freebsd-arm64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.freebsd-arm.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.freebsd-riscv64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.illumos-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.ios-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.ios-arm64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.js-wasm.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-386.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-arm64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-arm.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-loong64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-mips64x.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-mipsx.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-ppc64le.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-ppc64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-riscv64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.linux-s390x.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.netbsd-386.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.netbsd-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.netbsd-arm64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.netbsd-arm.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.openbsd-386.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.openbsd-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.openbsd-arm64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.openbsd-arm.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.openbsd-mips64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.openbsd-ppc64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.openbsd-riscv64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.plan9-386.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.plan9-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.plan9-arm.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.solaris-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.windows-386.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.windows-amd64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.windows-arm64.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_toolchain_v0.0.1-go1.999testmod.windows-arm.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_x_internal_v0.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_x_text_v0.0.0-20170915032832-14c0d48ead0c.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_x_text_v0.3.0.txt
│       │   │   │   │   │   │   │   │       │   ├── golang.org_x_useinternal_v0.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── gopkg.in_dummy.v2-unstable_v2.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── not-rsc.io_quote_v0.1.0-nomod.txt
│       │   │   │   │   │   │   │   │       │   ├── patch.example.com_depofdirectpatch_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── patch.example.com_depofdirectpatch_v1.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── patch.example.com_direct_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── patch.example.com_direct_v1.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── patch.example.com_direct_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── patch.example.com_indirect_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── patch.example.com_indirect_v1.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── patch.example.com_indirect_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── README
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_badfile1_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_badfile2_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_badfile3_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_badfile4_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_badfile5_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_badmod_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_badsum_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_badsum_v1.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_badzip_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_breaker_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_breaker_v2.0.0+incompatible.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_breaker_v2.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_!c!g!o_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_fortune_v0.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_fortune_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_fortune_v2_v2.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_future_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_needall_v0.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_needgo1183_v0.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_needgo118_v0.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_needgo121_v0.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_needgo1223_v0.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_needgo122_v0.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_needgo123_v0.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_needgo124_v0.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_panicnil_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_panicnil_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v0.0.0-20180214005133-e7a685a342c0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v0.0.0-20180214005840-23179ee8a569.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v0.0.0-20180628003336-dd9747d19b04.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v0.0.0-20180709153244-fd906ed3b100.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v0.0.0-20180709160352-0d003b9c4bfa.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v0.0.0-20180709162749-b44a0b17b2d1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v0.0.0-20180709162816-fe488b867524.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v0.0.0-20180709162918-a91498bed0a7.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v0.0.0-20180710144737-5d9f230bcfba.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.1.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.2.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.2.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.3.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.4.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.5.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.5.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_!q!u!o!t!e_v1.5.2.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.5.2.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v1.5.3-pre1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_!q!u!o!t!e_v1.5.3-!p!r!e.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v2.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v2_v2.0.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_quote_v3_v3.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_sampler_v1.0.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_sampler_v1.2.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_sampler_v1.2.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_sampler_v1.3.0.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_sampler_v1.3.1.txt
│       │   │   │   │   │   │   │   │       │   ├── rsc.io_sampler_v1.99.99.txt
│       │   │   │   │   │   │   │   │       │   └── rsc.io_testonly_v1.0.0.txt
│       │   │   │   │   │   │   │   │       ├── savedir.go
│       │   │   │   │   │   │   │   │       ├── script
│       │   │   │   │   │   │   │   │       │   ├── autocgo.txt
│       │   │   │   │   │   │   │   │       │   ├── badgo.txt
│       │   │   │   │   │   │   │   │       │   ├── bug.txt
│       │   │   │   │   │   │   │   │       │   ├── build_acl_windows.txt
│       │   │   │   │   │   │   │   │       │   ├── build_arm.txt
│       │   │   │   │   │   │   │   │       │   ├── build_buildvcs_auto.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cache_arch_mode.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cache_compile.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cache_disabled.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cache_gomips.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cache_link.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cache_output.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cache_pgo.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cache_trimpath.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cc_cache_issue64423.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cd_gopath_different.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cgo_consistent_results.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cgo_error.txt
│       │   │   │   │   │   │   │   │       │   ├── build_concurrent_backend.txt
│       │   │   │   │   │   │   │   │       │   ├── build_cwd_newline.txt
│       │   │   │   │   │   │   │   │       │   ├── build_darwin_cc_arch.txt
│       │   │   │   │   │   │   │   │       │   ├── build_dash_n_cgo.txt
│       │   │   │   │   │   │   │   │       │   ├── build_dash_o_dev_null.txt
│       │   │   │   │   │   │   │   │       │   ├── build_dash_x.txt
│       │   │   │   │   │   │   │   │       │   ├── build_exe.txt
│       │   │   │   │   │   │   │   │       │   ├── build_gcflags_order.txt
│       │   │   │   │   │   │   │   │       │   ├── build_gcflags.txt
│       │   │   │   │   │   │   │   │       │   ├── build_git_missing_tree.txt
│       │   │   │   │   │   │   │   │       │   ├── build_gopath_order.txt
│       │   │   │   │   │   │   │   │       │   ├── build_GOTMPDIR.txt
│       │   │   │   │   │   │   │   │       │   ├── build_ignore_leading_bom.txt
│       │   │   │   │   │   │   │   │       │   ├── build_import_comment.txt
│       │   │   │   │   │   │   │   │       │   ├── build_import_cycle.txt
│       │   │   │   │   │   │   │   │       │   ├── build_internal.txt
│       │   │   │   │   │   │   │   │       │   ├── build_issue59571.txt
│       │   │   │   │   │   │   │   │       │   ├── build_issue62156.txt
│       │   │   │   │   │   │   │   │       │   ├── build_issue6480.txt
│       │   │   │   │   │   │   │   │       │   ├── build_issue_65528.txt
│       │   │   │   │   │   │   │   │       │   ├── build_link_x_import_path_escape.txt
│       │   │   │   │   │   │   │   │       │   ├── build_multi_main.txt
│       │   │   │   │   │   │   │   │       │   ├── build_n_cgo.txt
│       │   │   │   │   │   │   │   │       │   ├── build_negative_p.txt
│       │   │   │   │   │   │   │   │       │   ├── build_nocache.txt
│       │   │   │   │   │   │   │   │       │   ├── build_no_go.txt
│       │   │   │   │   │   │   │   │       │   ├── build_output.txt
│       │   │   │   │   │   │   │   │       │   ├── build_overlay.txt
│       │   │   │   │   │   │   │   │       │   ├── build_patterns_outside_gopath.txt
│       │   │   │   │   │   │   │   │       │   ├── build_pgo_auto_multi.txt
│       │   │   │   │   │   │   │   │       │   ├── build_pgo_auto.txt
│       │   │   │   │   │   │   │   │       │   ├── build_pgo.txt
│       │   │   │   │   │   │   │   │       │   ├── build_pie_race.txt
│       │   │   │   │   │   │   │   │       │   ├── build_plugin_non_main.txt
│       │   │   │   │   │   │   │   │       │   ├── build_plugin_reproducible.txt
│       │   │   │   │   │   │   │   │       │   ├── build_relative_pkgdir.txt
│       │   │   │   │   │   │   │   │       │   ├── build_relative_tmpdir.txt
│       │   │   │   │   │   │   │   │       │   ├── build_repeated_godebug_issue62346.txt
│       │   │   │   │   │   │   │   │       │   ├── build_runtime_gcflags.txt
│       │   │   │   │   │   │   │   │       │   ├── build_shorten_pkg.txt
│       │   │   │   │   │   │   │   │       │   ├── build_single_error.txt
│       │   │   │   │   │   │   │   │       │   ├── build_static.txt
│       │   │   │   │   │   │   │   │       │   ├── build_tag_goexperiment.txt
│       │   │   │   │   │   │   │   │       │   ├── build_tags_no_comma.txt
│       │   │   │   │   │   │   │   │       │   ├── build_test_only.txt
│       │   │   │   │   │   │   │   │       │   ├── build_trimpath_cgo.txt
│       │   │   │   │   │   │   │   │       │   ├── build_trimpath_goroot.txt
│       │   │   │   │   │   │   │   │       │   ├── build_trimpath.txt
│       │   │   │   │   │   │   │   │       │   ├── build_unsupported_goos.txt
│       │   │   │   │   │   │   │   │       │   ├── build_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── cache_unix.txt
│       │   │   │   │   │   │   │   │       │   ├── cache_vet.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_asm_error.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_bad_directives.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_badmethod_issue57926.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_depends_on_syscall.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_flag_contains_space.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_long_cmd.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_path_space_quote.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_path_space.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_path.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_stale_precompiled.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_stale.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_suspect_flag_force_external.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_syso_issue29253.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_trimpath_macro.txt
│       │   │   │   │   │   │   │   │       │   ├── cgo_undef.txt
│       │   │   │   │   │   │   │   │       │   ├── chdir.txt
│       │   │   │   │   │   │   │   │       │   ├── check_goexperiment.txt
│       │   │   │   │   │   │   │   │       │   ├── clean_binary.txt
│       │   │   │   │   │   │   │   │       │   ├── clean_cache_n.txt
│       │   │   │   │   │   │   │   │       │   ├── clean_testcache.txt
│       │   │   │   │   │   │   │   │       │   ├── cmd_import_error.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_asm.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_atomic_pkgall.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_blank_func_decl.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_build_cmdline_pkgs.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_build_pkg_select.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_build_simple.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_cgo_extra_file.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_cgo_extra_test.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_cgo.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_cgo_xtest.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_coverpkg_partial.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_coverpkg_with_init.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_coverprofile_multipkg.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_dash_c.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_dep_loop.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_dot_import.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_error.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_import_main_loop.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_list.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_main_import_path.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_mod_empty.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_modes.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_pattern.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_pkgall_imports.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_pkgall_multiple_mains.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_pkgall_runtime.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_runs.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_single_vs_multiple.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_statements.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_swig.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_sync_atomic_import.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_test_localpkg_filepath.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_test_pkgselect.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_test_race_issue56370.txt
│       │   │   │   │   │   │   │   │       │   ├── cover_var_init_order.txt
│       │   │   │   │   │   │   │   │       │   ├── cpu_profile_twice.txt
│       │   │   │   │   │   │   │   │       │   ├── darwin_lto_library_ldflag.txt
│       │   │   │   │   │   │   │   │       │   ├── darwin_no_cgo.txt
│       │   │   │   │   │   │   │   │       │   ├── devnull.txt
│       │   │   │   │   │   │   │   │       │   ├── dist_list_missing.txt
│       │   │   │   │   │   │   │   │       │   ├── doc.txt
│       │   │   │   │   │   │   │   │       │   ├── embed_brackets.txt
│       │   │   │   │   │   │   │   │       │   ├── embed_fmt.txt
│       │   │   │   │   │   │   │   │       │   ├── embed.txt
│       │   │   │   │   │   │   │   │       │   ├── env_cache.txt
│       │   │   │   │   │   │   │   │       │   ├── env_changed.txt
│       │   │   │   │   │   │   │   │       │   ├── env_cross_build.txt
│       │   │   │   │   │   │   │   │       │   ├── env_exp.txt
│       │   │   │   │   │   │   │   │       │   ├── env_gomod_issue61455.txt
│       │   │   │   │   │   │   │   │       │   ├── env_issue46807.txt
│       │   │   │   │   │   │   │   │       │   ├── env_sanitize.txt
│       │   │   │   │   │   │   │   │       │   ├── env_unset.txt
│       │   │   │   │   │   │   │   │       │   ├── env_write.txt
│       │   │   │   │   │   │   │   │       │   ├── fileline.txt
│       │   │   │   │   │   │   │   │       │   ├── fmt_load_errors.txt
│       │   │   │   │   │   │   │   │       │   ├── fsys_walk.txt
│       │   │   │   │   │   │   │   │       │   ├── gccgo_link_c.txt
│       │   │   │   │   │   │   │   │       │   ├── gccgo_link_ldflags.txt
│       │   │   │   │   │   │   │   │       │   ├── gccgo_mangle.txt
│       │   │   │   │   │   │   │   │       │   ├── gccgo_m.txt
│       │   │   │   │   │   │   │   │       │   ├── gcflags_patterns.txt
│       │   │   │   │   │   │   │   │       │   ├── generate_bad_imports.txt
│       │   │   │   │   │   │   │   │       │   ├── generate_env.txt
│       │   │   │   │   │   │   │   │       │   ├── generate_goroot_PATH.txt
│       │   │   │   │   │   │   │   │       │   ├── generate_invalid.txt
│       │   │   │   │   │   │   │   │       │   ├── generate.txt
│       │   │   │   │   │   │   │   │       │   ├── generate_workspace.txt
│       │   │   │   │   │   │   │   │       │   ├── get_404_meta.txt
│       │   │   │   │   │   │   │   │       │   ├── get_insecure_no_longer_supported.txt
│       │   │   │   │   │   │   │   │       │   ├── get_insecure.txt
│       │   │   │   │   │   │   │   │       │   ├── get_issue53955.txt
│       │   │   │   │   │   │   │   │       │   ├── go_badcmd.txt
│       │   │   │   │   │   │   │   │       │   ├── godebug_default.txt
│       │   │   │   │   │   │   │   │       │   ├── godebug_unknown.txt
│       │   │   │   │   │   │   │   │       │   ├── goflags.txt
│       │   │   │   │   │   │   │   │       │   ├── goline_order.txt
│       │   │   │   │   │   │   │   │       │   ├── gopath_install.txt
│       │   │   │   │   │   │   │   │       │   ├── gopath_local.txt
│       │   │   │   │   │   │   │   │       │   ├── gopath_paths.txt
│       │   │   │   │   │   │   │   │       │   ├── gopath_std_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── gopath_vendor_dup_err.txt
│       │   │   │   │   │   │   │   │       │   ├── goroot_executable_trimpath.txt
│       │   │   │   │   │   │   │   │       │   ├── goroot_executable.txt
│       │   │   │   │   │   │   │   │       │   ├── gotoolchain_issue66175.txt
│       │   │   │   │   │   │   │   │       │   ├── gotoolchain_local.txt
│       │   │   │   │   │   │   │   │       │   ├── gotoolchain_loop.txt
│       │   │   │   │   │   │   │   │       │   ├── gotoolchain_modcmds.txt
│       │   │   │   │   │   │   │   │       │   ├── gotoolchain_net.txt
│       │   │   │   │   │   │   │   │       │   ├── gotoolchain_path.txt
│       │   │   │   │   │   │   │   │       │   ├── gotoolchain_version.txt
│       │   │   │   │   │   │   │   │       │   ├── govcs.txt
│       │   │   │   │   │   │   │   │       │   ├── go_version.txt
│       │   │   │   │   │   │   │   │       │   ├── help.txt
│       │   │   │   │   │   │   │   │       │   ├── import_cycle.txt
│       │   │   │   │   │   │   │   │       │   ├── import_ignore.txt
│       │   │   │   │   │   │   │   │       │   ├── import_main.txt
│       │   │   │   │   │   │   │   │       │   ├── import_unix_tag.txt
│       │   │   │   │   │   │   │   │       │   ├── index.txt
│       │   │   │   │   │   │   │   │       │   ├── install_cgo_excluded.txt
│       │   │   │   │   │   │   │   │       │   ├── install_cleans_build.txt
│       │   │   │   │   │   │   │   │       │   ├── install_cmd_gobin.txt
│       │   │   │   │   │   │   │   │       │   ├── install_cross_gobin.txt
│       │   │   │   │   │   │   │   │       │   ├── install_dep_version.txt
│       │   │   │   │   │   │   │   │       │   ├── install_goroot_targets.txt
│       │   │   │   │   │   │   │   │       │   ├── install_modcacherw_issue64282.txt
│       │   │   │   │   │   │   │   │       │   ├── install_move_not_stale.txt
│       │   │   │   │   │   │   │   │       │   ├── install_msan_and_race_and_asan_require_cgo.txt
│       │   │   │   │   │   │   │   │       │   ├── install_rebuild_removed.txt
│       │   │   │   │   │   │   │   │       │   ├── install_relative_gobin_fail.txt
│       │   │   │   │   │   │   │   │       │   ├── install_shadow_gopath.txt
│       │   │   │   │   │   │   │   │       │   ├── issue36000.txt
│       │   │   │   │   │   │   │   │       │   ├── issue53586.txt
│       │   │   │   │   │   │   │   │       │   ├── ldflag.txt
│       │   │   │   │   │   │   │   │       │   ├── link_external_undef.txt
│       │   │   │   │   │   │   │   │       │   ├── link_matching_actionid.txt
│       │   │   │   │   │   │   │   │       │   ├── linkname.txt
│       │   │   │   │   │   │   │   │       │   ├── link_syso_deps.txt
│       │   │   │   │   │   │   │   │       │   ├── link_syso_issue33139.txt
│       │   │   │   │   │   │   │   │       │   ├── list_all_gobuild.txt
│       │   │   │   │   │   │   │   │       │   ├── list_ambiguous_path.txt
│       │   │   │   │   │   │   │   │       │   ├── list_bad_import.txt
│       │   │   │   │   │   │   │   │       │   ├── list_buildmod_reason_issue67587.txt
│       │   │   │   │   │   │   │   │       │   ├── list_case_collision.txt
│       │   │   │   │   │   │   │   │       │   ├── list_cgo_compiled_importmap.txt
│       │   │   │   │   │   │   │   │       │   ├── list_compiled_files_issue28749.txt
│       │   │   │   │   │   │   │   │       │   ├── list_compiled_imports.txt
│       │   │   │   │   │   │   │   │       │   ├── list_compiler_output.txt
│       │   │   │   │   │   │   │   │       │   ├── list_constraints.txt
│       │   │   │   │   │   │   │   │       │   ├── list_dedup_packages.txt
│       │   │   │   │   │   │   │   │       │   ├── list_empty_import.txt
│       │   │   │   │   │   │   │   │       │   ├── list_err_cycle.txt
│       │   │   │   │   │   │   │   │       │   ├── list_err_stack.txt
│       │   │   │   │   │   │   │   │       │   ├── list_export_embed.txt
│       │   │   │   │   │   │   │   │       │   ├── list_export_e.txt
│       │   │   │   │   │   │   │   │       │   ├── list_find_nodeps.txt
│       │   │   │   │   │   │   │   │       │   ├── list_find.txt
│       │   │   │   │   │   │   │   │       │   ├── list_gofile_in_goroot.txt
│       │   │   │   │   │   │   │   │       │   ├── list_gomod_in_gopath.txt
│       │   │   │   │   │   │   │   │       │   ├── list_goroot_symlink.txt
│       │   │   │   │   │   │   │   │       │   ├── list_import_cycle_deps_errors.txt
│       │   │   │   │   │   │   │   │       │   ├── list_import_err.txt
│       │   │   │   │   │   │   │   │       │   ├── list_importmap.txt
│       │   │   │   │   │   │   │   │       │   ├── list_issue_56509.txt
│       │   │   │   │   │   │   │   │       │   ├── list_issue_59905.txt
│       │   │   │   │   │   │   │   │       │   ├── list_json_fields.txt
│       │   │   │   │   │   │   │   │       │   ├── list_json_issue64946.txt
│       │   │   │   │   │   │   │   │       │   ├── list_json_with_f.txt
│       │   │   │   │   │   │   │   │       │   ├── list_legacy_mod.txt
│       │   │   │   │   │   │   │   │       │   ├── list_linkshared.txt
│       │   │   │   │   │   │   │   │       │   ├── list_load_err.txt
│       │   │   │   │   │   │   │   │       │   ├── list_module_when_error.txt
│       │   │   │   │   │   │   │   │       │   ├── list_n_cover.txt
│       │   │   │   │   │   │   │   │       │   ├── list_overlay.txt
│       │   │   │   │   │   │   │   │       │   ├── list_parse_err.txt
│       │   │   │   │   │   │   │   │       │   ├── list_perm.txt
│       │   │   │   │   │   │   │   │       │   ├── list_pgo_issue66218.txt
│       │   │   │   │   │   │   │   │       │   ├── list_pkgconfig_error.txt
│       │   │   │   │   │   │   │   │       │   ├── list_replace_absolute_windows.txt
│       │   │   │   │   │   │   │   │       │   ├── list_reserved.txt
│       │   │   │   │   │   │   │   │       │   ├── list_retractions_issue66403.txt
│       │   │   │   │   │   │   │   │       │   ├── list_shadow.txt
│       │   │   │   │   │   │   │   │       │   ├── list_split_main.txt
│       │   │   │   │   │   │   │   │       │   ├── list_std.txt
│       │   │   │   │   │   │   │   │       │   ├── list_std_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── list_swigcxx.txt
│       │   │   │   │   │   │   │   │       │   ├── list_symlink_dotdotdot.txt
│       │   │   │   │   │   │   │   │       │   ├── list_symlink_internal.txt
│       │   │   │   │   │   │   │   │       │   ├── list_symlink_issue35941.txt
│       │   │   │   │   │   │   │   │       │   ├── list_symlink.txt
│       │   │   │   │   │   │   │   │       │   ├── list_symlink_vendor_issue14054.txt
│       │   │   │   │   │   │   │   │       │   ├── list_symlink_vendor_issue15201.txt
│       │   │   │   │   │   │   │   │       │   ├── list_test_cycle.txt
│       │   │   │   │   │   │   │   │       │   ├── list_testdata.txt
│       │   │   │   │   │   │   │   │       │   ├── list_test_err.txt
│       │   │   │   │   │   │   │   │       │   ├── list_test_e.txt
│       │   │   │   │   │   │   │   │       │   ├── list_test_imports.txt
│       │   │   │   │   │   │   │   │       │   ├── list_test_non_go_files.txt
│       │   │   │   │   │   │   │   │       │   ├── list_test_simple.txt
│       │   │   │   │   │   │   │   │       │   ├── list_wildcard_skip_nonmatching.txt
│       │   │   │   │   │   │   │   │       │   ├── load_test_pkg_err.txt
│       │   │   │   │   │   │   │   │       │   ├── malformed_gosum_issue62345.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_all.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_alt_goroot.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_ambiguous_import.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_auth.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_bad_domain.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_bad_filenames.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_build_info_err.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_build_tags.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_build_trimpath_issue48557.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_build_versioned.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_cache_dir.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_cache_rw.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_case_cgo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_case.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_clean_cache.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_concurrent.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_convert_git.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_deprecate_message.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_dir.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_doc_path.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_doc.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_domain_root.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_dot.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_concurrent_read.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_exec_toolchain.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_git_bareRepository.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_git_decorate_full.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_hash.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_insecure_redirect.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_issue51114.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_json.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_partial.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_private_vcs.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_replace_file.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_svn.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download_too_many_redirects.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_download.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_edit_go.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_edit_no_modcache.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_edit_toolchain.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_edit.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_empty_err.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_enabled.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_errors_pos.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_e.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_exclude_go121.txt
│       │   │   │   │   │   │   │   │       │   ├── modfile_flag.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_file_proxy.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_fileproxy_vcs_missing_issue51589.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_find.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_fs_patterns.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_ambiguous_arg.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_ambiguous_import.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_ambiguous_pkg.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_boost.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_changes.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_commit.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_deprecated.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_deprecate_install.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_direct.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_downadd_indirect.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_downgrade_missing.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_downgrade.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_downup_artifact.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_downup_indirect_pruned.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_downup_indirect.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_downup_pseudo_artifact.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_errors.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_exec_toolchain.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_extra.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_fallback.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_fossil.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_future.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_go_file.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_hash.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_incompatible.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_indirect.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_insecure_redirect.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_issue37438.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_issue47650.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_issue47979.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_issue48511.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_issue56494.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_issue60490.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_issue65363.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_latest_pseudo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_lazy_indirect.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_lazy_upgrade_lazy.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_local.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_main.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_major.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_missing_ziphash.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_getmode_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_moved.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_newcycle.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_none.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_nopkgs.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_patchbound.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_patchcycle.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_patchmod.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_patch.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_patterns.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_pkgtags.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_prefer_incompatible.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_promote_implicit.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_pseudo_other_branch.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_pseudo_prefix.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_pseudo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_replaced.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_retract_ambiguous.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_retract.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_split.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_sum_noroot.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_tags.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_test.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_toolchain.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_trailing_slash.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_update_unrelated_sum.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_upgrade_pseudo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_upgrade.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_get_wild.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_getx.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_git_export_subst.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_gobuild_import.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_gofmt_invalid.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_goline_old.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_goline_too_new.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_goline.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_gomodcache.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_gomodcache_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_gonoproxy.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_gopkg_unstable.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_goroot_errors.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_go_version_missing.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_go_version_mixed.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_go_version.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_graph.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_graph_version.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_help.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_import_cycle.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_import_issue41113.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_import_issue42891.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_import_meta.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_import_mod.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_import_toolchain.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_import.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_import_v1suffix.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_import_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_indirect_main.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_indirect_nospace.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_indirect_tidy.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_indirect.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_init_empty.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_init_invalid_major.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_init_path.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_init_tidy.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_insecure_issue63845.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_install_hint.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_install_pkg_version.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_install_versioned.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_internal.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_in_testdata_dir.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_invalid_path_dotname.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_invalid_path_plus.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_invalid_path.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_invalid_version.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_issue35270.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_issue35317.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_lazy_consistency.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_lazy_downgrade.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_lazy_import_allmod.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_lazy_new_import.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_lazy_test_horizon.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_lazy_test_of_test_dep.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_bad_import.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_command_line_arguments.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_compiled_concurrent.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_deprecated_replace.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_deprecated.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_direct.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_direct_work.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_dir.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_e_readonly.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_issue61415.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_issue61423.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_m.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_odd_tags.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_pseudo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_replace_dir.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_retract.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_std.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_sums.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_test_cycle.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_test.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_update_nolatest.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_upgrade_pseudo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_list_upgrade.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_load_badchain.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_load_badmod.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_load_badzip.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_load_replace_mismatch.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_local_replace.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_missingpkg_prerelease.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_missing_repo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_modinfo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_multirepo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_no_gopath.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_nomod.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_notall.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_off_init.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_off.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_outside.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_overlay.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_patterns.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_patterns_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_permissions.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_perm.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_prefer_compatible.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_proxy_errors.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_proxy_https.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_proxy_invalid.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_proxy_list.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_pseudo_cache.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_query_empty.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_query_exclude.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_query_main.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_query.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_readonly.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_replace_gopkgin.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_replace_import.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_replace_readonly.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_replace.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_require_exclude.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retention.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retract_fix_version.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retract_incompatible.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retract_noupgrade.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retract_pseudo_base.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retract_rationale.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retract_rename.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retract_replace.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retract.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_retract_versions.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_run_flags_issue64738.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_run_issue52331.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_run_nonmain.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_run_path.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_run_pkgerror.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_run_pkg_version.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_skip_write.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_stale.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_std_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_string_alias.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sum_ambiguous.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sumdb_cache.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sumdb_file_path.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sumdb_golang.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sumdb_proxy.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sumdb.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sum_issue56222.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sum_lookup.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sum_readonly.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_sum_replaced.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_symlink_dotgo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_symlink.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tagged_import_cycle.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_test_cached.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_test_files.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_test.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_compat_added.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_compat_ambiguous.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_compat_deleted.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_compat_implicit.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_compat_incompatible.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_compat_irrelevant.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_compat.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_convergence_loop.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_convergence.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_cycle.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_diff.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_downgrade_ambiguous.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_duplicates.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_error.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_indirect.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_issue60313.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_lazy_self.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_newroot.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_oldgo.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_old.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_quote.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_replace_old.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_replace.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_sum.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_support_buildx.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_symlink_issue35941.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_temp.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_version_tooold.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_tidy_version.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_toolchain_slash.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_toolchain.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_update_sum_readonly.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_upgrade_patch.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vcs_missing.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_auto.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_build.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_collision.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_embed.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_gomod.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_goversion.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_issue46867.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_nodeps.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_redundant_requirement.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_replace.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_trimpath.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_unused_only.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_vendor_unused.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_verify.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_verify_work.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_versions.txt
│       │   │   │   │   │   │   │   │       │   ├── mod_why.txt
│       │   │   │   │   │   │   │   │       │   ├── noncanonical_import.txt
│       │   │   │   │   │   │   │   │       │   ├── old_tidy_toolchain.txt
│       │   │   │   │   │   │   │   │       │   ├── pattern_syntax_error.txt
│       │   │   │   │   │   │   │   │       │   ├── prevent_sys_unix_import.txt
│       │   │   │   │   │   │   │   │       │   ├── README
│       │   │   │   │   │   │   │   │       │   ├── repro_build.txt
│       │   │   │   │   │   │   │   │       │   ├── reuse_git.txt
│       │   │   │   │   │   │   │   │       │   ├── run_dirs.txt
│       │   │   │   │   │   │   │   │       │   ├── run_hello_pkg.txt
│       │   │   │   │   │   │   │   │       │   ├── run_hello.txt
│       │   │   │   │   │   │   │   │       │   ├── run_internal.txt
│       │   │   │   │   │   │   │   │       │   ├── run_issue11709.txt
│       │   │   │   │   │   │   │   │       │   ├── run_issue51125.txt
│       │   │   │   │   │   │   │   │       │   ├── run_set_executable_name.txt
│       │   │   │   │   │   │   │   │       │   ├── run_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── run_vers.txt
│       │   │   │   │   │   │   │   │       │   ├── run_wildcard.txt
│       │   │   │   │   │   │   │   │       │   ├── run_work_versioned.txt
│       │   │   │   │   │   │   │   │       │   ├── script_help.txt
│       │   │   │   │   │   │   │   │       │   ├── script_wait.txt
│       │   │   │   │   │   │   │   │       │   ├── slashpath.txt
│       │   │   │   │   │   │   │   │       │   ├── src_file.txt
│       │   │   │   │   │   │   │   │       │   ├── std_vendor.txt
│       │   │   │   │   │   │   │   │       │   ├── telemetry.txt
│       │   │   │   │   │   │   │   │       │   ├── test2json_interrupt.txt
│       │   │   │   │   │   │   │   │       │   ├── test_android_issue62123.txt
│       │   │   │   │   │   │   │   │       │   ├── test_bad_example.txt
│       │   │   │   │   │   │   │   │       │   ├── test_badtest.txt
│       │   │   │   │   │   │   │   │       │   ├── test_benchmark_1x.txt
│       │   │   │   │   │   │   │   │       │   ├── test_benchmark_chatty_fail.txt
│       │   │   │   │   │   │   │   │       │   ├── test_benchmark_chatty_success.txt
│       │   │   │   │   │   │   │   │       │   ├── test_benchmark_fatal.txt
│       │   │   │   │   │   │   │   │       │   ├── test_benchmark_labels.txt
│       │   │   │   │   │   │   │   │       │   ├── test_benchmark_timeout.txt
│       │   │   │   │   │   │   │   │       │   ├── test_build_failure.txt
│       │   │   │   │   │   │   │   │       │   ├── test_buildvcs.txt
│       │   │   │   │   │   │   │   │       │   ├── test_cache_inputs.txt
│       │   │   │   │   │   │   │   │       │   ├── test_chatty_fail.txt
│       │   │   │   │   │   │   │   │       │   ├── test_chatty_parallel_fail.txt
│       │   │   │   │   │   │   │   │       │   ├── test_chatty_parallel_success_run.txt
│       │   │   │   │   │   │   │   │       │   ├── test_chatty_parallel_success.txt
│       │   │   │   │   │   │   │   │       │   ├── test_chatty_success.txt
│       │   │   │   │   │   │   │   │       │   ├── test_cleanup_failnow.txt
│       │   │   │   │   │   │   │   │       │   ├── test_compile_binary.txt
│       │   │   │   │   │   │   │   │       │   ├── test_compile_multi_pkg.txt
│       │   │   │   │   │   │   │   │       │   ├── test_compile_tempfile.txt
│       │   │   │   │   │   │   │   │       │   ├── test_deadline.txt
│       │   │   │   │   │   │   │   │       │   ├── test_empty.txt
│       │   │   │   │   │   │   │   │       │   ├── test_env_term.txt
│       │   │   │   │   │   │   │   │       │   ├── test_example_goexit.txt
│       │   │   │   │   │   │   │   │       │   ├── test_exit.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fail_fast.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fail_newline.txt
│       │   │   │   │   │   │   │   │       │   ├── test_finished_subtest_goroutines.txt
│       │   │   │   │   │   │   │   │       │   ├── test_flags.txt
│       │   │   │   │   │   │   │   │       │   ├── test_flag.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fullpath.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_cache.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_cgo.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_chatty.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_cleanup.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_cov.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_deadline.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_dup_cache.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_err_deadlock.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_fuzztime.txt
│       │   │   │   │   │   │   │   │       │   ├── test_fuzz_io_error.txt
│    