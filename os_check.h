/* os_check.h - single-header OS detection.
 *
 * Two ways to use it:
 *
 *   1. Compile-time (for platform-only imports):
 *        #if OS_CHECK_WINDOWS
 *        #  include <windows.h>
 *        #else
 *        #  include <unistd.h>
 *        #endif
 *
 *   2. Runtime (plain if):
 *        if (is_windows()) { ... }
 *
 * Every OS_CHECK_* macro is 0 or 1. Exactly one of the per-OS predicates is
 * true. The rest are aggregates: is_linux() is false on Android (use
 * is_linux_kernel() for the kernel); is_bsd(), is_unix(), is_posix() and
 * is_nt() (Windows NT family).
 *
 * Define OS_CHECK_STRICT to make an unknown OS a compile error instead of
 * silently reporting "unknown".
 */
#ifndef OS_CHECK_H
#define OS_CHECK_H

#if defined(__APPLE__)
#  include <TargetConditionals.h>
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#  define OS_CHECK_WINDOWS 1
#else
#  define OS_CHECK_WINDOWS 0
#endif

#if defined(__ANDROID__)
#  define OS_CHECK_ANDROID 1
#else
#  define OS_CHECK_ANDROID 0
#endif

#if defined(__APPLE__) && defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#  define OS_CHECK_IOS 1
#else
#  define OS_CHECK_IOS 0
#endif

#if defined(__APPLE__) && (!defined(TARGET_OS_IPHONE) || !TARGET_OS_IPHONE)
#  define OS_CHECK_MACOS 1
#else
#  define OS_CHECK_MACOS 0
#endif

#if (defined(__linux__) || defined(__linux) || defined(linux)) && !OS_CHECK_ANDROID
#  define OS_CHECK_LINUX 1
#else
#  define OS_CHECK_LINUX 0
#endif

#if defined(__FreeBSD__)
#  define OS_CHECK_FREEBSD 1
#else
#  define OS_CHECK_FREEBSD 0
#endif

#if defined(__OpenBSD__)
#  define OS_CHECK_OPENBSD 1
#else
#  define OS_CHECK_OPENBSD 0
#endif

#if defined(__NetBSD__)
#  define OS_CHECK_NETBSD 1
#else
#  define OS_CHECK_NETBSD 0
#endif

#define OS_CHECK_BSD \
    (OS_CHECK_FREEBSD || OS_CHECK_OPENBSD || OS_CHECK_NETBSD)

#define OS_CHECK_UNIX \
    (OS_CHECK_LINUX || OS_CHECK_MACOS || OS_CHECK_IOS || OS_CHECK_ANDROID || \
     OS_CHECK_BSD)

/* POSIX-style userspace (everything here except Windows; Cygwin counts as
 * Windows because _WIN32 is defined there). */
#define OS_CHECK_POSIX OS_CHECK_UNIX

/* Windows NT family (NT, 2000, XP, ... 11). */
#define OS_CHECK_NT OS_CHECK_WINDOWS

#define OS_CHECK_KNOWN \
    (OS_CHECK_WINDOWS || OS_CHECK_UNIX)

#if defined(OS_CHECK_STRICT) && !OS_CHECK_KNOWN
#  error "os_check: unknown operating system"
#endif

#if defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#  define OS_CHECK_INLINE static inline
#elif defined(_MSC_VER)
#  define OS_CHECK_INLINE static __inline
#else
#  define OS_CHECK_INLINE static
#endif

#ifdef __cplusplus
extern "C" {
#endif

OS_CHECK_INLINE int is_windows(void) { return OS_CHECK_WINDOWS; }
OS_CHECK_INLINE int is_linux(void)   { return OS_CHECK_LINUX;   }
OS_CHECK_INLINE int is_macos(void)   { return OS_CHECK_MACOS;   }
OS_CHECK_INLINE int is_ios(void)     { return OS_CHECK_IOS;     }
OS_CHECK_INLINE int is_android(void) { return OS_CHECK_ANDROID; }
OS_CHECK_INLINE int is_freebsd(void) { return OS_CHECK_FREEBSD; }
OS_CHECK_INLINE int is_openbsd(void) { return OS_CHECK_OPENBSD; }
OS_CHECK_INLINE int is_netbsd(void)  { return OS_CHECK_NETBSD;  }

OS_CHECK_INLINE int is_bsd(void)   { return OS_CHECK_BSD;   }
OS_CHECK_INLINE int is_unix(void)  { return OS_CHECK_UNIX;  }
OS_CHECK_INLINE int is_posix(void) { return OS_CHECK_POSIX; }
OS_CHECK_INLINE int is_nt(void)    { return OS_CHECK_NT;    }

/* Linux kernel, including Android (which is Linux-based). */
OS_CHECK_INLINE int is_linux_kernel(void)
{
    return OS_CHECK_LINUX || OS_CHECK_ANDROID;
}

OS_CHECK_INLINE const char *os_name(void)
{
#if OS_CHECK_WINDOWS
    return "windows";
#elif OS_CHECK_ANDROID
    return "android";
#elif OS_CHECK_IOS
    return "ios";
#elif OS_CHECK_MACOS
    return "macos";
#elif OS_CHECK_LINUX
    return "linux";
#elif OS_CHECK_FREEBSD
    return "freebsd";
#elif OS_CHECK_OPENBSD
    return "openbsd";
#elif OS_CHECK_NETBSD
    return "netbsd";
#else
    return "unknown";
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* OS_CHECK_H */
