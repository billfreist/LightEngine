///
/// LICENSE
///

#include "pch.h"

#include <malloc.h>
#include <core/perf/profiler.h>

namespace lite {

void * CommonAllocator::Alloc (size_t bytes) noexcept {
    void * ptr =  ::malloc(bytes);
    PROFILER_ALLOC(ptr, bytes);
    return ptr;
}

void * CommonAllocator::Realloc (void * ptr, size_t bytes) noexcept {
    PROFILER_FREE(ptr);
    ptr = ::realloc(ptr, bytes);
    PROFILER_ALLOC(ptr, bytes);
    return ptr;
}

void CommonAllocator::Free (void * ptr) noexcept {
    PROFILER_FREE(ptr);
    ::free(ptr);
}

void * CommonAllocator::AllocAligned (size_t bytes, size_t align) noexcept {
    void * ptr = ::_aligned_malloc(bytes, align);
    PROFILER_ALLOC(ptr, bytes);
    return ptr;
}

void * CommonAllocator::ReallocAligned (void * ptr, size_t bytes, size_t align) noexcept {
    PROFILER_FREE(ptr);
    ptr = ::_aligned_realloc(ptr, bytes, align);
    PROFILER_ALLOC(ptr, bytes);
    return ptr;
}

void CommonAllocator::FreeAligned (void * ptr, size_t /* align */) noexcept {
    PROFILER_FREE(ptr);
    ::_aligned_free(ptr);
}

} // namespace lite
