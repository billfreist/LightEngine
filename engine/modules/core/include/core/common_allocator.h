///
/// LICENSE
///

/// CommonAllocator

#pragma once

namespace lite {

class CommonAllocator {
public:
    static void * Alloc (size_t bytes);
    static void * Realloc (void * ptr, size_t bytes);
    static void   Free (void * ptr);

    static void * AllocAligned (size_t bytes, size_t align);
    static void * ReallocAligned (void * ptr, size_t bytes, size_t align);
    static void   FreeAligned (void * ptr, size_t align);
};

} // namespace lite


/// Global new/delete overloads
LITE_FORCE_INLINE void * __cdecl operator new (size_t size) {
    return lite::CommonAllocator::Alloc(size);
}

LITE_FORCE_INLINE void __cdecl operator delete (void * ptr) {
    lite::CommonAllocator::Free(ptr);
}

LITE_FORCE_INLINE void * __cdecl operator new[] (size_t size) {
    return lite::CommonAllocator::Alloc(size);
}

LITE_FORCE_INLINE void __cdecl operator delete[] (void * ptr) {
    lite::CommonAllocator::Free(ptr);
}
