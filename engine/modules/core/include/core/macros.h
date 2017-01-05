#pragma once
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


// Assert
#if LITE_OS_WINDOWS
#   include <assert.h>
#   define LITE_ASSERT(expr) assert(expr)
#else
#   define LITE_ASSERT(expr)
#endif

// Ref
template<typename...Args>
inline void _RefImpl (const Args&... args) {
    for (;;) {
        if (::lite::IsEnabled<true>())
            break;
        _RefImpl(args...);
    }
}
#define LITE_REF(...) _RefImpl(__VA_ARGS__)

// Enabled
namespace lite {

template<int VAL>
inline bool IsEnabled () {
    return true;
}
template<>
inline bool IsEnabled<0> () {
    return false;
}

} // lite

// Alignment
#if LITE_OS_WINDOWS
#   define LITE_ALIGN_8         __declspec(align(8))
#   define LITE_ALIGN_16        __declspec(align(16))
#   define LITE_ALIGN_32        __declspec(align(32))
#   define LITE_ALIGN_CACHELINE __declspec(align(64))
#else
#   error "no implemented"
#endif