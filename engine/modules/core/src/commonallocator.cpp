///
/// LICENSE
///

#include "core_pch.h"
#include <malloc.h>


/// Override Global New/Delete
void * operator new (size_t bytes) {
    return lite::CommonAllocator::Alloc(bytes);
}

void operator delete (void * ptr) noexcept {
    lite::CommonAllocator::Free(ptr);
}


LITE_NAMESPACE_BEGIN(lite)

void * CommonAllocator::Alloc (size_t bytes) {
    return ::malloc(bytes);
}

void * CommonAllocator::Realloc (void * ptr, size_t bytes) {
    return ::realloc(ptr, bytes);
}

void CommonAllocator::Free (void * ptr) {
    ::free(ptr);
}

void * CommonAllocator::AllocAligned (size_t bytes, size_t align) {
    return ::_aligned_malloc(bytes, align);
}

void * CommonAllocator::ReallocAligned (void * ptr, size_t bytes, size_t align) {
    return ::_aligned_realloc(ptr, bytes, align);
}

void CommonAllocator::FreeAligned (void * ptr, size_t /* align */) {
    ::_aligned_free(ptr);
}

LITE_NAMESPACE_END(lite)
