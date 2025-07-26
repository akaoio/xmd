# Phase 1: Refactor platform.c to comply with one-function-per-file rule

## Objective
Split platform.c (23 functions) into individual files following the pattern:
- 1 file = 1 folder = 1 function
- folder name = file name = function name (snake_case)

## Function Categories and New Structure

### Time Functions
- `xmd_get_time` → `src/platform/xmd_get_time/xmd_get_time.c`
- `xmd_sleep_ms` → `src/platform/xmd_sleep_ms/xmd_sleep_ms.c`
- `xmd_get_tick_count` → `src/platform/xmd_get_tick_count/xmd_get_tick_count.c`
- `xmd_get_cpu_time` → `src/platform/xmd_get_cpu_time/xmd_get_cpu_time.c`

### Process Functions
- `xmd_process_create` → `src/platform/xmd_process_create/xmd_process_create.c`
- `xmd_process_wait` → `src/platform/xmd_process_wait/xmd_process_wait.c`
- `xmd_process_kill` → `src/platform/xmd_process_kill/xmd_process_kill.c`
- `xmd_process_close` → `src/platform/xmd_process_close/xmd_process_close.c`

### Mutex Functions
- `xmd_mutex_init` → `src/platform/xmd_mutex_init/xmd_mutex_init.c`
- `xmd_mutex_lock` → `src/platform/xmd_mutex_lock/xmd_mutex_lock.c`
- `xmd_mutex_unlock` → `src/platform/xmd_mutex_unlock/xmd_mutex_unlock.c`
- `xmd_mutex_destroy` → `src/platform/xmd_mutex_destroy/xmd_mutex_destroy.c`

### File System Functions
- `xmd_mkdir` → `src/platform/xmd_mkdir/xmd_mkdir.c`
- `xmd_create_directory` → `src/platform/xmd_create_directory/xmd_create_directory.c`
- `xmd_file_exists` → `src/platform/xmd_file_exists/xmd_file_exists.c`
- `xmd_is_directory` → `src/platform/xmd_is_directory/xmd_is_directory.c`
- `xmd_opendir` → `src/platform/xmd_opendir/xmd_opendir.c`
- `xmd_closedir` → `src/platform/xmd_closedir/xmd_closedir.c`

### Memory Functions
- `xmd_aligned_free` → `src/platform/xmd_aligned_free/xmd_aligned_free.c`
- `xmd_get_memory_size` → `src/platform/xmd_get_memory_size/xmd_get_memory_size.c`
- `xmd_get_memory_usage` → `src/platform/xmd_get_memory_usage/xmd_get_memory_usage.c`

### System Info Functions
- `xmd_get_cpu_count` → `src/platform/xmd_get_cpu_count/xmd_get_cpu_count.c`
- `xmd_get_fd_count` → `src/platform/xmd_get_fd_count/xmd_get_fd_count.c`

## Implementation Steps
1. Create directory structure
2. Extract each function to its own file
3. Create shared platform_internal.h for common includes
4. Update CMakeLists.txt
5. Test to ensure nothing breaks