///
/// LICENSE
///

#include "pch.h"
#include <malloc.h>

namespace lite {

void * CommonAllocator::Alloc (size_t bytes) noexcept {
    return ::malloc(bytes);
}

void * CommonAllocator::Realloc (void * ptr, size_t bytes) noexcept {
    return ::realloc(ptr, bytes);
}

void CommonAllocator::Free (void * ptr) noexcept {
    ::free(ptr);
}

void * CommonAllocator::AllocAligned (size_t bytes, size_t align) noexcept {
    return ::_aligned_malloc(bytes, align);
}

void * CommonAllocator::ReallocAligned (void * ptr, size_t bytes, size_t align) noexcept {
    return ::_aligned_realloc(ptr, bytes, align);
}

void CommonAllocator::FreeAligned (void * ptr, size_t /* align */) noexcept {
    ::_aligned_free(ptr);
}

} // namespace lite
