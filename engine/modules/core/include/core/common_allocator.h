///
/// LICENSE
///

/// CommonAllocator

#pragma once

LITE_NAMESPACE_BEGIN(lite)

class CommonAllocator {
public:
    static void * Alloc (size_t bytes);
    static void * Realloc (void * ptr, size_t bytes);
    static void   Free (void * ptr);

    static void * AllocAligned (size_t bytes, size_t align);
    static void * ReallocAligned (void * ptr, size_t bytes, size_t align);
    static void   FreeAligned (void * ptr, size_t align);
};

LITE_NAMESPACE_END(lite)

