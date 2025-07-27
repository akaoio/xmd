/**
 * @file executor_internal.h
 * @brief Internal header for executor functions
 * @author XMD Team
 */

#ifndef EXECUTOR_INTERNAL_H
#define EXECUTOR_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include "platform.h"
#include "executor.h"

// Internal function declarations
void set_executor_error(ExecutorContext* ctx, const char* message);
long get_time_ms(void);
ssize_t read_with_timeout(int fd, char* buffer, size_t max_size, int timeout_ms);
int parse_command_args(const char* command, char*** args);
void free_command_args(char** args, int argc);

// Public function declarations
ExecutorContext* executor_context_new(void);
void executor_context_free(ExecutorContext* ctx);
int executor_run_with_timeout(ExecutorContext* ctx, const char* command, 
                             int timeout_ms, CommandResult** result);
int executor_run_command(ExecutorContext* ctx, const char* command, CommandResult** result);
void command_result_free(CommandResult* result);

#endif /* EXECUTOR_INTERNAL_H */