#pragma once

// Platform detection macros
#if defined(__APPLE__)
    #define PLATFORM_APPLE 1
#else
    #define PLATFORM_APPLE 0
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS 1
#else
    #define PLATFORM_WINDOWS 0
#endif

#if defined(__linux__)
    #define PLATFORM_LINUX 1
#else
    #define PLATFORM_LINUX 0
#endif

// Compiler detection
#if defined(__clang__)
    #define COMPILER_CLANG 1
#else
    #define COMPILER_CLANG 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
    #define COMPILER_GCC 1
#else
    #define COMPILER_GCC 0
#endif

#if defined(_MSC_VER)
    #define COMPILER_MSVC 1
#else
    #define COMPILER_MSVC 0
#endif

// Architecture detection
#if defined(__x86_64__) || defined(_M_X64)
    #define ARCH_X64 1
#else
    #define ARCH_X64 0
#endif

#if defined(__i386) || defined(_M_IX86)
    #define ARCH_X86 1
#else
    #define ARCH_X86 0
#endif

#if defined(__arm__) || defined(_M_ARM)
    #define ARCH_ARM 1
#else
    #define ARCH_ARM 0
#endif

#if defined(__aarch64__) || defined(_M_ARM64)
    #define ARCH_ARM64 1
#else
    #define ARCH_ARM64 0
#endif

// Unused parameter macro
#define UNUSED_PARAM(x) (void)(x)

// Memory allocation macros
#include <cstdlib>
#define MALLOC(size) malloc(size)
#define FREE(ptr) free(ptr)
#define REALLOC(ptr, size) realloc(ptr, size)
#define CALLOC(count, size) calloc(count, size)

// Debug macros
#ifdef DEBUG_BUILD
    #define DEBUG_LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define DEBUG_LOG(fmt, ...) ((void)0)
#endif

// Platform-specific includes
#if PLATFORM_APPLE
    // Forward declarations for Objective-C types to avoid including objc headers
    typedef struct objc_object *id;
    typedef struct objc_class *Class;
    typedef struct objc_selector *SEL;
    typedef struct objc_method *Method;
    typedef struct objc_ivar *Ivar;
    typedef struct objc_category *Category;
    typedef struct objc_property *objc_property_t;
    
    // Define basic Objective-C types
    typedef struct objc_object {
        Class isa;
    } *id;
    
    // Define basic Objective-C constants
    #define nil ((id)0)
    #define Nil ((Class)0)
    #define YES ((BOOL)1)
    #define NO ((BOOL)0)
    
    typedef signed char BOOL;
#endif

