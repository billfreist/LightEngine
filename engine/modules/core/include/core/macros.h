///
/// LICENSE
///

#pragma once

#ifndef LITE_CORE_H_INCLUDED
#   error "core.h must be included first"
#endif
#define LITE_MACROS_H_INCLUDED

#undef NULL
#define NULL nullptr

// OS specific
#if defined(_WIN32) || defined(_WIN64)
#   define LITE_OS_WINDOWS 1
#   define WIN32_LEAN_AND_MEAN
#else
#   define LITE_OS_WINDOWS 0
#endif


// Force inline
#if LITE_OS_WINDOWS
#   define LITE_FORCE_INLINE __forceinline
#else
#   define LITE_FORCE_INLINE __attribute__((always_inline))
#endif


// Assert
#if LITE_OS_WINDOWS
#   include <assert.h>
#   define LITE_ASSERT(expr) assert(expr)
#else
#   define LITE_ASSERT(expr)
#endif

// Array Size
template<class T, uint32_t N>
constexpr uint32_t lite_ArraySizeImpl (const T (&)[N]) { return N; }
#define LITE_ARRAY_SIZE(a) lite_ArraySizeImpl(a)

// Ref
template<typename...Args>
inline void lite_RefImpl (const Args&... args) {
    for (;;) {
        if (::lite::IsEnabled<true>())
            break;
        lite_RefImpl(args...);
    }
}
#define LITE_REF(...) lite_RefImpl(__VA_ARGS__)

// Alignment
#if LITE_OS_WINDOWS
#   define LITE_ALIGN_8         __declspec(align(8))
#   define LITE_ALIGN_16        __declspec(align(16))
#   define LITE_ALIGN_32        __declspec(align(32))
#   define LITE_ALIGN_CACHELINE __declspec(align(64))
#else
#   error "no implemented"
#endif

//
// Concatenation
//
#define LITE_CONCAT(a, b) _LITE_CONCAT(a, b)
#define _LITE_CONCAT(a, b) a##b

//
// Stringify
//
#define LITE_STRINGIFY(s)  _LITE_STRINGIFY(s)
#define _LITE_STRINGIFY(s) #s

//
// Macro VA arguments
//
#define LITE_ARG_COUNT(...) _LITE_ARG_COUNT LITE_ARGS_FROWARD(__VA_ARGS__, 6, 5, 4, 3, 2, 1)
#define _LITE_ARG_COUNT(_1, _2, _3, _4, _5, _6, COUNT, ...) COUNT

#define LITE_ARGS_FROWARD(...) _LITE_ARGS_FROWARD_OPEN __VA_ARGS__ _LITE_ARGS_FROWARD_CLOSE
#define _LITE_ARGS_FROWARD_OPEN (
#define _LITE_ARGS_FROWARD_CLOSE )

//
// Macro dispatching
//
#define LITE_MACRO_DISPATCH(prefix, ...) _LITE_MACRO_DISPATCH(prefix, LITE_ARG_COUNT(__VA_ARGS__) )
#define _LITE_MACRO_DISPATCH(prefix, count) LITE_CONCAT(prefix, count)

//
// Namespace
//
#define LITE_NAMESPACE_BEGIN(...) LITE_MACRO_DISPATCH(_LITE_NAMESPACE_BEGIN_, __VA_ARGS__) LITE_ARGS_FROWARD(__VA_ARGS__)
#define LITE_NAMESPACE_END(...)   LITE_MACRO_DISPATCH(_LITE_NAMESPACE_END_, __VA_ARGS__) LITE_ARGS_FROWARD(__VA_ARGS__)

#define _LITE_NAMESPACE_BEGIN_1(a1)                     namespace a1 {
#define _LITE_NAMESPACE_BEGIN_2(a1, a2)                 _LITE_NAMESPACE_BEGIN_1(a1)                 _LITE_NAMESPACE_BEGIN_1(a2)
#define _LITE_NAMESPACE_BEGIN_3(a1, a2, a3)             _LITE_NAMESPACE_BEGIN_2(a1, a2)             _LITE_NAMESPACE_BEGIN_1(a3)
#define _LITE_NAMESPACE_BEGIN_4(a1, a2, a3, a4)         _LITE_NAMESPACE_BEGIN_3(a1, a2, a3)         _LITE_NAMESPACE_BEGIN_1(a4)
#define _LITE_NAMESPACE_BEGIN_5(a1, a2, a3, a4, a5)     _LITE_NAMESPACE_BEGIN_4(a1, a2, a3, a4)     _LITE_NAMESPACE_BEGIN_1(a5)
#define _LITE_NAMESPACE_BEGIN_6(a1, a2, a3, a4, a5, a6) _LITE_NAMESPACE_BEGIN_5(a1, a2, a3, a4, a5) _LITE_NAMESPACE_BEGIN_1(a6)

#define _LITE_NAMESPACE_END_1(a1)                     }
#define _LITE_NAMESPACE_END_2(a1, a2)                 _LITE_NAMESPACE_END_1(a1)                 _LITE_NAMESPACE_END_1(a2)
#define _LITE_NAMESPACE_END_3(a1, a2, a3)             _LITE_NAMESPACE_END_2(a1, a2)             _LITE_NAMESPACE_END_1(a3)
#define _LITE_NAMESPACE_END_4(a1, a2, a3, a4)         _LITE_NAMESPACE_END_3(a1, a2, a3)         _LITE_NAMESPACE_END_1(a4)
#define _LITE_NAMESPACE_END_5(a1, a2, a3, a4, a5)     _LITE_NAMESPACE_END_4(a1, a2, a3, a4)     _LITE_NAMESPACE_END_1(a5)
#define _LITE_NAMESPACE_END_6(a1, a2, a3, a4, a5, a6) _LITE_NAMESPACE_END_5(a1, a2, a3, a4, a5) _LITE_NAMESPACE_END_1(a6)
