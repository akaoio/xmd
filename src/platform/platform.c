/**
 * @file platform.c
 * @brief Cross-platform compatibility layer implementation using C17 standard
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>
#include "../../include/platform.h"

#ifdef XMD_PLATFORM_WINDOWS
    #include <psapi.h>
    #pragma comment(lib, "psapi.lib")
    #pragma comment(lib, "kernel32.lib")
#endif

// =============================================================================
// Time Functions
// =============================================================================

/**
 * @brief Get current high-resolution time
 * @param time Output time structure
 * @return 0 on success, -1 on error
 */
int xmd_get_time(xmd_time_t* time) {
    if (!time) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    LARGE_INTEGER freq, counter;
    if (!QueryPerformanceFrequency(&freq) || !QueryPerformanceCounter(&counter)) {
        return -1;
    }
    time->seconds = counter.QuadPart / freq.QuadPart;
    time->nanoseconds = ((counter.QuadPart % freq.QuadPart) * 1000000000LL) / freq.QuadPart;
#else
    struct timespec ts;
    #ifdef XMD_PLATFORM_MACOS
        clock_gettime(CLOCK_UPTIME_RAW, &ts);
    #else
        clock_gettime(CLOCK_MONOTONIC, &ts);
    #endif
    time->seconds = ts.tv_sec;
    time->nanoseconds = ts.tv_nsec;
#endif
    
    return 0;
}

/**
 * @brief Sleep for specified milliseconds
 * @param milliseconds Time to sleep
 * @return 0 on success, -1 on error
 */
int xmd_sleep_ms(uint32_t milliseconds) {
#ifdef XMD_PLATFORM_WINDOWS
    Sleep(milliseconds);
    return 0;
#else
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    return nanosleep(&ts, NULL) == 0 ? 0 : -1;
#endif
}

/**
 * @brief Get tick count in milliseconds
 * @return Tick count in milliseconds
 */
uint64_t xmd_get_tick_count(void) {
#ifdef XMD_PLATFORM_WINDOWS
    return GetTickCount64();
#else
    xmd_time_t time;
    if (xmd_get_time(&time) != 0) return 0;
    return (uint64_t)time.seconds * 1000 + time.nanoseconds / 1000000;
#endif
}

// =============================================================================
// Process Functions
// =============================================================================

/**
 * @brief Create a new process
 * @param command Command to execute
 * @param argv Command arguments
 * @param process Output process handle
 * @return 0 on success, -1 on error
 */
int xmd_process_create(const char* command, char* const argv[], xmd_process_t* process) {
    if (!command || !process) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    // Build command line
    char cmdline[2048] = {0};
    snprintf(cmdline, sizeof(cmdline), "%s", command);
    if (argv) {
        for (int i = 0; argv[i]; i++) {
            strcat(cmdline, " ");
            strcat(cmdline, argv[i]);
        }
    }
    
    if (!CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        return -1;
    }
    
    CloseHandle(pi.hThread);
    *process = pi.hProcess;
    return 0;
#else
    pid_t pid = fork();
    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        // Child process
        if (argv) {
            execvp(command, argv);
        } else {
            execl(command, command, (char*)NULL);
        }
        exit(127); // If exec fails
    } else {
        // Parent process
        *process = pid;
        return 0;
    }
#endif
}

/**
 * @brief Wait for process to complete
 * @param process Process handle
 * @param exit_code Output exit code
 * @param timeout_ms Timeout in milliseconds
 * @return 0 on success, -1 on error, 1 on timeout
 */
int xmd_process_wait(xmd_process_t process, int* exit_code, uint32_t timeout_ms) {
#ifdef XMD_PLATFORM_WINDOWS
    DWORD wait_result = WaitForSingleObject(process, timeout_ms);
    if (wait_result == WAIT_TIMEOUT) {
        return 1;
    } else if (wait_result == WAIT_OBJECT_0) {
        if (exit_code) {
            DWORD code;
            if (GetExitCodeProcess(process, &code)) {
                *exit_code = (int)code;
            } else {
                *exit_code = -1;
            }
        }
        return 0;
    }
    return -1;
#else
    int status;
    pid_t result;
    
    if (timeout_ms == 0) {
        // No timeout
        result = waitpid(process, &status, 0);
    } else {
        // Implement timeout using alarm signal
        struct sigaction old_action, new_action;
        new_action.sa_handler = SIG_DFL;
        sigemptyset(&new_action.sa_mask);
        new_action.sa_flags = 0;
        
        sigaction(SIGALRM, &new_action, &old_action);
        alarm(timeout_ms / 1000 + 1); // Convert to seconds, round up
        
        result = waitpid(process, &status, 0);
        
        alarm(0); // Cancel alarm
        sigaction(SIGALRM, &old_action, NULL); // Restore old handler
    }
    
    if (result == -1) {
        return -1;
    }
    
    if (exit_code) {
        if (WIFEXITED(status)) {
            *exit_code = WEXITSTATUS(status);
        } else {
            *exit_code = -1;
        }
    }
    
    return 0;
#endif
}

/**
 * @brief Kill a process
 * @param process Process handle
 * @return 0 on success, -1 on error
 */
int xmd_process_kill(xmd_process_t process) {
#ifdef XMD_PLATFORM_WINDOWS
    return TerminateProcess(process, 1) ? 0 : -1;
#else
    return kill(process, SIGTERM) == 0 ? 0 : -1;
#endif
}

/**
 * @brief Close process handle
 * @param process Process handle
 */
void xmd_process_close(xmd_process_t process) {
#ifdef XMD_PLATFORM_WINDOWS
    CloseHandle(process);
#else
    // Nothing to do on POSIX
    (void)process;
#endif
}

// =============================================================================
// Thread Functions
// =============================================================================

/**
 * @brief Initialize mutex
 * @param mutex Mutex to initialize
 * @return 0 on success, -1 on error
 */
int xmd_mutex_init(xmd_mutex_t* mutex) {
    if (!mutex) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    InitializeCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_init(mutex, NULL) == 0 ? 0 : -1;
#endif
}

/**
 * @brief Lock mutex
 * @param mutex Mutex to lock
 * @return 0 on success, -1 on error
 */
int xmd_mutex_lock(xmd_mutex_t* mutex) {
    if (!mutex) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    EnterCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_lock(mutex) == 0 ? 0 : -1;
#endif
}

/**
 * @brief Unlock mutex
 * @param mutex Mutex to unlock
 * @return 0 on success, -1 on error
 */
int xmd_mutex_unlock(xmd_mutex_t* mutex) {
    if (!mutex) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    LeaveCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_unlock(mutex) == 0 ? 0 : -1;
#endif
}

/**
 * @brief Destroy mutex
 * @param mutex Mutex to destroy
 * @return 0 on success, -1 on error
 */
int xmd_mutex_destroy(xmd_mutex_t* mutex) {
    if (!mutex) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    DeleteCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_destroy(mutex) == 0 ? 0 : -1;
#endif
}

// =============================================================================
// Dynamic Library Functions
// =============================================================================

/**
 * @brief Load dynamic library
 * @param path Library path
 * @return Library handle or NULL on error
 */
xmd_library_t xmd_library_load(const char* path) {
    if (!path) return NULL;
    
#ifdef XMD_PLATFORM_WINDOWS
    return LoadLibraryA(path);
#elif defined(XMD_PLATFORM_IOS)
    // Dynamic loading not supported on iOS
    return NULL;
#else
    return dlopen(path, RTLD_LAZY);
#endif
}

/**
 * @brief Get symbol from library
 * @param library Library handle
 * @param name Symbol name
 * @return Symbol address or NULL on error
 */
xmd_symbol_t xmd_library_symbol(xmd_library_t library, const char* name) {
    if (!library || !name) return NULL;
    
#ifdef XMD_PLATFORM_WINDOWS
    return GetProcAddress(library, name);
#elif defined(XMD_PLATFORM_IOS)
    return NULL;
#else
    return dlsym(library, name);
#endif
}

/**
 * @brief Unload library
 * @param library Library handle
 */
void xmd_library_unload(xmd_library_t library) {
    if (!library) return;
    
#ifdef XMD_PLATFORM_WINDOWS
    FreeLibrary(library);
#elif defined(XMD_PLATFORM_IOS)
    // Nothing to do
#else
    dlclose(library);
#endif
}

/**
 * @brief Get library error message
 * @return Error message or NULL
 */
char* xmd_library_error(void) {
#ifdef XMD_PLATFORM_WINDOWS
    static char buffer[256];
    DWORD error = GetLastError();
    if (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, buffer, sizeof(buffer), NULL)) {
        return buffer;
    }
    return NULL;
#elif defined(XMD_PLATFORM_IOS)
    return "Dynamic loading not supported on iOS";
#else
    return dlerror();
#endif
}

// =============================================================================
// File System Functions
// =============================================================================

/**
 * @brief Create directory
 * @param path Directory path
 * @return 0 on success, -1 on error
 */
int xmd_mkdir(const char* path) {
    if (!path) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    return CreateDirectoryA(path, NULL) ? 0 : -1;
#else
    return mkdir(path, 0755) == 0 ? 0 : -1;
#endif
}

/**
 * @brief Create directory with error checking
 * @param path Directory path
 * @return 0 on success, -1 on error
 */
int xmd_create_directory(const char* path) {
    if (!path) return -1;
    
    // Check if directory already exists
    if (xmd_is_directory(path) == 1) {
        return 0; // Already exists
    }
    
    return xmd_mkdir(path);
}

/**
 * @brief Check if file exists
 * @param path File path
 * @return 1 if exists, 0 if not, -1 on error
 */
int xmd_file_exists(const char* path) {
    if (!path) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    DWORD attrs = GetFileAttributesA(path);
    return (attrs != INVALID_FILE_ATTRIBUTES) ? 1 : 0;
#else
    return access(path, F_OK) == 0 ? 1 : 0;
#endif
}

/**
 * @brief Check if path is directory
 * @param path Path to check
 * @return 1 if directory, 0 if not, -1 on error
 */
int xmd_is_directory(const char* path) {
    if (!path) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    DWORD attrs = GetFileAttributesA(path);
    if (attrs == INVALID_FILE_ATTRIBUTES) return -1;
    return (attrs & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0;
#else
    struct stat st;
    if (stat(path, &st) != 0) return -1;
    return S_ISDIR(st.st_mode) ? 1 : 0;
#endif
}

/**
 * @brief Open directory for reading
 * @param path Directory path
 * @return Directory handle or XMD_INVALID_DIR on error
 */
xmd_dir_t xmd_opendir(const char* path) {
    if (!path) return XMD_INVALID_DIR;
    
#ifdef XMD_PLATFORM_WINDOWS
    char search_path[MAX_PATH];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    return _findfirst(search_path, (struct _finddata_t*)malloc(sizeof(struct _finddata_t)));
#else
    return opendir(path);
#endif
}

/**
 * @brief Read directory entry
 * @param dir Directory handle
 * @return Directory entry or NULL on end/error
 */
xmd_dirent_t* xmd_readdir(xmd_dir_t dir) {
    if (dir == XMD_INVALID_DIR) return NULL;
    
#ifdef XMD_PLATFORM_WINDOWS
    static struct _finddata_t entry;
    if (_findnext(dir, &entry) == 0) {
        return &entry;
    }
    return NULL;
#else
    return readdir(dir);
#endif
}

/**
 * @brief Close directory
 * @param dir Directory handle
 */
void xmd_closedir(xmd_dir_t dir) {
    if (dir == XMD_INVALID_DIR) return;
    
#ifdef XMD_PLATFORM_WINDOWS
    _findclose(dir);
#else
    closedir(dir);
#endif
}

/**
 * @brief Get filename from directory entry
 * @param entry Directory entry
 * @return Filename or NULL on error
 */
char* xmd_get_filename(xmd_dirent_t* entry) {
    if (!entry) return NULL;
    
#ifdef XMD_PLATFORM_WINDOWS
    return entry->name;
#else
    return entry->d_name;
#endif
}

// =============================================================================
// Memory Functions
// =============================================================================

/**
 * @brief Allocate aligned memory using C17 compatible approach
 * @param alignment Memory alignment
 * @param size Size to allocate
 * @return Aligned memory or NULL on error
 */
void* xmd_aligned_alloc(size_t alignment, size_t size) {
#ifdef XMD_PLATFORM_WINDOWS
    return _aligned_malloc(size, alignment);
#else
    /* Use POSIX approach for all Unix-like systems including Android/Linux */
    void* ptr;
    if (posix_memalign(&ptr, alignment, size) == 0) {
        return ptr;
    }
    return NULL;
#endif
}

/**
 * @brief Free aligned memory
 * @param ptr Memory to free
 */
void xmd_aligned_free(void* ptr) {
    if (!ptr) return;
    
#ifdef XMD_PLATFORM_WINDOWS
    _aligned_free(ptr);
#else
    free(ptr);
#endif
}

// =============================================================================
// System Information
// =============================================================================

/**
 * @brief Get CPU count
 * @return Number of CPUs
 */
uint32_t xmd_get_cpu_count(void) {
#ifdef XMD_PLATFORM_WINDOWS
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwNumberOfProcessors;
#else
    long cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    return cpu_count > 0 ? (uint32_t)cpu_count : 1;
#endif
}

/**
 * @brief Get total system memory
 * @return Memory size in bytes
 */
uint64_t xmd_get_memory_size(void) {
#ifdef XMD_PLATFORM_WINDOWS
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    if (GlobalMemoryStatusEx(&status)) {
        return status.ullTotalPhys;
    }
    return 0;
#else
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    if (pages > 0 && page_size > 0) {
        return (uint64_t)pages * page_size;
    }
    return 0;
#endif
}

/**
 * @brief Get current process memory usage
 * @return Memory usage in bytes
 */
uint64_t xmd_get_memory_usage(void) {
#ifdef XMD_PLATFORM_WINDOWS
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize;
    }
    return 0;
#elif defined(XMD_PLATFORM_LINUX) && !defined(XMD_PLATFORM_ANDROID)
    FILE* file = fopen("/proc/self/status", "r");
    if (!file) return 0;
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            uint64_t size;
            if (sscanf(line + 6, "%llu", &size) == 1) {
                fclose(file);
                return size * 1024; // Convert KB to bytes
            }
        }
    }
    fclose(file);
    return 0;
#else
    // Fallback for other platforms
    return 0;
#endif
}

/**
 * @brief Get current CPU time for process
 * @return CPU time in milliseconds
 */
long xmd_get_cpu_time(void) {
#ifdef XMD_PLATFORM_WINDOWS
    FILETIME creation, exit, kernel, user;
    if (GetProcessTimes(GetCurrentProcess(), &creation, &exit, &kernel, &user)) {
        ULARGE_INTEGER k, u;
        k.LowPart = kernel.dwLowDateTime;
        k.HighPart = kernel.dwHighDateTime;
        u.LowPart = user.dwLowDateTime;
        u.HighPart = user.dwHighDateTime;
        // Convert 100-nanosecond intervals to milliseconds
        return (long)((k.QuadPart + u.QuadPart) / 10000);
    }
    return 0;
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) * 1000 +
               (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000;
    }
    return 0;
#endif
}

/**
 * @brief Get file descriptor count for current process
 * @return Number of open file descriptors
 */
int xmd_get_fd_count(void) {
#ifdef XMD_PLATFORM_WINDOWS
    // Windows doesn't have a simple way to count handles
    // Return a default estimate
    return 10;
#elif defined(XMD_PLATFORM_LINUX) && !defined(XMD_PLATFORM_ANDROID)
    DIR* fd_dir = opendir("/proc/self/fd");
    if (!fd_dir) return -1;
    
    int count = 0;
    struct dirent* entry;
    while ((entry = readdir(fd_dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            count++;
        }
    }
    closedir(fd_dir);
    return count;
#else
    // Fallback for other platforms
    return 10;
#endif
}