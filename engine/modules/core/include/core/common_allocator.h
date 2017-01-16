///
/// LICENSE
///

/// CommonAllocator

#pragma once

LITE_NAMESPACE_BEGIN(lite)

class CommonAllocator {
public:
    static void * Alloc (size_t bytes);
    static void Free (void * ptr);
};

LITE_NAMESPACE_END(lite)

