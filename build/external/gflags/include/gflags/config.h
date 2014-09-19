/* Generated from config.h.in during configuration using CMake. */

// ---------------------------------------------------------------------------
// Meta-information

// Name of package.
#define PACKAGE gflags

// Define to the full name of this package.
#define PACKAGE_NAME gflags

// Define to the full name and version of this package.
#define PACKAGE_STRING gflags 2.1.0

// Define to the one symbol short name of this package.
#define PACKAGE_TARNAME gflags-2.1.0

// Define to the version of this package.
#define PACKAGE_VERSION 2.1.0

// Version number of package.
#define VERSION PACKAGE_VERSION

// Define to the address where bug reports for this package should be sent.
#define PACKAGE_BUGREPORT https://code.google.com/p/gflags/issues/

// ---------------------------------------------------------------------------
// Namespace for gflags symbols.
#define GFLAGS_NAMESPACE gflags

// ---------------------------------------------------------------------------
// Available system headers

// Whether sources are compiled on a Windows system
#define WINDOWS (defined(_WIN32) || defined(WIN32) || defined(_WINDOWS))

// Define to 1 if you have the <fnmatch.h> header file.
#define HAVE_FNMATCH_H 1

// Define to 1 if you have the <inttypes.h> header file.
#define HAVE_INTTYPES_H 1

// Define to 1 if you have the <unistd.h> header file.
#define HAVE_UNISTD_H 1

// Define to 1 if you have the <sys/stat.h> header file.
#define HAVE_SYS_STAT_H 1

// Define to 1 if you have the strtoll function.
#define HAVE_STRTOLL 1

// Define to 1 if you have the strtoq function.
#define HAVE_STRTOQ 1

// Define to 1 if you have the <pthread.h> header file.
#define HAVE_PTHREAD 1

// gcc requires this to get PRId64, etc.
#if HAVE_INTTYPES_H && !defined(__STDC_FORMAT_MACROS)
#  define __STDC_FORMAT_MACROS 1
#endif

// ---------------------------------------------------------------------------
// Path separator
#ifndef PATH_SEPARATOR
#  define PATH_SEPARATOR  '/'
#endif

// ---------------------------------------------------------------------------
// Windows-specific definitions
#if !defined(GFLAGS_DLL_DECL)
#  if defined(_MSC_VER)
#    if defined(GFLAGS_DLL_EXPORT)
#      define GFLAGS_DLL_DECL __declspec(dllexport)
#    else
#      define GFLAGS_DLL_DECL __declspec(dllimport)
#    endif
#  else
#    define GFLAGS_DLL_DECL
#  endif
#endif

#if WINDOWS
// This must be defined before the windows.h is included.
// It's needed for mutex.h, to give access to the TryLock method.
#  if !defined(_WIN32_WINNT) && !(defined( __MINGW32__) || defined(__MINGW64__))
#    define _WIN32_WINNT 0x0400
#  endif
#  include "windows_port.h"
#endif
