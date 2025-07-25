/**
 * @file platform.h
 * @brief Cross-platform compatibility layer for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 * 
 * REQUIREMENTS: C17 standard or later (no C11/C99 fallbacks)
 * 
 * This header provides platform detection and abstraction for:
 * - Windows (x86, x64, ARM64)
 * - macOS (Intel, Apple Silicon)
 * - Linux (x86, x64, ARM, ARM64)
 * - Android (ARM, ARM64, x86, x64)
 * - iOS (ARM64, x64 simulator)
 */

#ifndef PLATFORM_H
#define PLATFORM_H

/* Enforce C17 minimum standard */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201710L
#error "XMD requires C17 standard or later. Please compile with -std=c17 or newer."
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// Platform Detection
// =============================================================================

// Operating System Detection
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define XMD_PLATFORM_WINDOWS 1
    #ifdef _WIN64
        #define XMD_PLATFORM_WIN64 1
    #else
        #define XMD_PLATFORM_WIN32 1
    #endif
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #define XMD_PLATFORM_APPLE 1
    #if TARGET_OS_IPHONE
        #define XMD_PLATFORM_IOS 1
    #elif TARGET_OS_MAC
        #define XMD_PLATFORM_MACOS 1
    #endif
#elif defined(__ANDROID__)
    #define XMD_PLATFORM_ANDROID 1
    #define XMD_PLATFORM_LINUX 1
#elif defined(__linux__)
    #define XMD_PLATFORM_LINUX 1
#elif defined(__unix__) || defined(__unix)
    #define XMD_PLATFORM_UNIX 1
#else
    #define XMD_PLATFORM_UNKNOWN 1
#endif

// Architecture Detection
#if defined(_M_X64) || defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) || defined(__amd64)
    #define XMD_ARCH_X64 1
#elif defined(_M_IX86) || defined(__i386__) || defined(__i386) || defined(i386)
    #define XMD_ARCH_X86 1
#elif defined(_M_ARM64) || defined(__aarch64__)
    #define XMD_ARCH_ARM64 1
#elif defined(_M_ARM) || defined(__arm__)
    #define XMD_ARCH_ARM 1
#else
    #define XMD_ARCH_UNKNOWN 1
#endif

// Compiler Detection
#if defined(_MSC_VER)
    #define XMD_COMPILER_MSVC 1
#elif defined(__GNUC__)
    #define XMD_COMPILER_GCC 1
#elif defined(__clang__)
    #define XMD_COMPILER_CLANG 1
#endif

// =============================================================================
// Platform-Specific Includes
// =============================================================================

#ifdef XMD_PLATFORM_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <process.h>
    #include <io.h>
    #include <direct.h>
    #include <sys/stat.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/time.h>
    #include <dirent.h>
    #include <fcntl.h>
    #include <signal.h>
    
    #ifndef XMD_PLATFORM_ANDROID
        #include <sys/wait.h>
        #include <sys/resource.h>
    #endif
    
    
    #if defined(XMD_PLATFORM_LINUX) && !defined(XMD_PLATFORM_ANDROID)
        #include <pthread.h>
    #endif
#endif

// =============================================================================
// Type Definitions
// =============================================================================

// Process/Thread Types
#ifdef XMD_PLATFORM_WINDOWS
    typedef HANDLE xmd_process_t;
    typedef HANDLE xmd_thread_t;
    typedef CRITICAL_SECTION xmd_mutex_t;
#else
    typedef pid_t xmd_process_t;
    typedef pthread_t xmd_thread_t;
    typedef pthread_mutex_t xmd_mutex_t;
#endif

// File/Directory Types
#ifdef XMD_PLATFORM_WINDOWS
    typedef struct _finddata_t xmd_dirent_t;
    typedef intptr_t xmd_dir_t;
    #define XMD_INVALID_DIR ((xmd_dir_t)-1)
#else
    typedef struct dirent xmd_dirent_t;
    typedef DIR* xmd_dir_t;
    #define XMD_INVALID_DIR NULL
#endif

// Time Types
typedef struct {
    int64_t seconds;
    int64_t nanoseconds;
} xmd_time_t;

// =============================================================================
// Function Declarations
// =============================================================================

// Time Functions
int xmd_get_time(xmd_time_t* time);
int xmd_sleep_ms(uint32_t milliseconds);
uint64_t xmd_get_tick_count(void);

// Process Functions
int xmd_process_create(const char* command, char* const argv[], xmd_process_t* process);
int xmd_process_wait(xmd_process_t process, int* exit_code, uint32_t timeout_ms);
int xmd_process_kill(xmd_process_t process);
void xmd_process_close(xmd_process_t process);

// Thread Functions
int xmd_mutex_init(xmd_mutex_t* mutex);
int xmd_mutex_lock(xmd_mutex_t* mutex);
int xmd_mutex_unlock(xmd_mutex_t* mutex);
int xmd_mutex_destroy(xmd_mutex_t* mutex);


// File System Functions
int xmd_mkdir(const char* path);
int xmd_create_directory(const char* path);
int xmd_file_exists(const char* path);
int xmd_is_directory(const char* path);
xmd_dir_t xmd_opendir(const char* path);
xmd_dirent_t* xmd_readdir(xmd_dir_t dir);
void xmd_closedir(xmd_dir_t dir);
char* xmd_get_filename(xmd_dirent_t* entry);

// Memory Functions
void* xmd_aligned_alloc(size_t alignment, size_t size);
void xmd_aligned_free(void* ptr);

// System Information
uint32_t xmd_get_cpu_count(void);
uint64_t xmd_get_memory_size(void);
uint64_t xmd_get_memory_usage(void);
long xmd_get_cpu_time(void);
int xmd_get_fd_count(void);

// =============================================================================
// Compatibility Macros
// =============================================================================

#ifdef XMD_PLATFORM_WINDOWS
    #define XMD_PATH_SEPARATOR '\\'
    #define XMD_PATH_SEPARATOR_STR "\\"
    #define XMD_LINE_ENDING "\r\n"
    #define XMD_EXECUTABLE_EXTENSION ".exe"
#else
    #define XMD_PATH_SEPARATOR '/'
    #define XMD_PATH_SEPARATOR_STR "/"
    #define XMD_LINE_ENDING "\n"
    #define XMD_EXECUTABLE_EXTENSION ""
#endif

// Attribute Macros
#ifdef XMD_COMPILER_MSVC
    #define XMD_FORCE_INLINE __forceinline
    #define XMD_NO_INLINE __declspec(noinline)
    #define XMD_THREAD_LOCAL __declspec(thread)
    #define XMD_PACKED __pragma(pack(push, 1))
    #define XMD_PACKED_END __pragma(pack(pop))
#elif defined(XMD_COMPILER_GCC) || defined(XMD_COMPILER_CLANG)
    #define XMD_FORCE_INLINE __attribute__((always_inline)) inline
    #define XMD_NO_INLINE __attribute__((noinline))
    #define XMD_THREAD_LOCAL __thread
    #define XMD_PACKED __attribute__((packed))
    #define XMD_PACKED_END
#else
    #define XMD_FORCE_INLINE inline
    #define XMD_NO_INLINE
    #define XMD_THREAD_LOCAL
    #define XMD_PACKED
    #define XMD_PACKED_END
#endif

// Debug Macros
#ifdef _DEBUG
    #define XMD_DEBUG 1
#endif

#ifdef XMD_DEBUG
    #define XMD_ASSERT(x) do { if (!(x)) { fprintf(stderr, "Assertion failed: %s at %s:%d\n", #x, __FILE__, __LINE__); abort(); } } while(0)
#else
    #define XMD_ASSERT(x) ((void)0)
#endif

#ifdef __cplusplus
}
#endif

#endif // PLATFORM_H