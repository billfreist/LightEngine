///
/// LICENSE
///

/// CommonAllocator

#pragma once

#ifndef LITE_CORE_H_INCLUDED
#   error "Must be included through core.h"
#endif // LITE_CORE_H_INCLUDED

namespace lite {

class CommonAllocator {
public:
    static void * Alloc (size_t bytes) noexcept;
    static void * Realloc (void * ptr, size_t bytes) noexcept;
    static void   Free (void * ptr) noexcept;

    static void * AllocAligned (size_t bytes, size_t align) noexcept;
    static void * ReallocAligned (void * ptr, size_t bytes, size_t align) noexcept;
    static void   FreeAligned (void * ptr, size_t align) noexcept;
};

} // namespace lite


/// Global new/delete overloads
[[nodiscard]] inline void * __cdecl operator new (size_t size) {
    return lite::CommonAllocator::Alloc(size);
}

inline void __cdecl operator delete (void * ptr) {
    lite::CommonAllocator::Free(ptr);
}

[[nodiscard]] inline void * __cdecl operator new[] (size_t size) {
    return lite::CommonAllocator::Alloc(size);
}

inline void __cdecl operator delete[] (void * ptr) {
    lite::CommonAllocator::Free(ptr);
}
