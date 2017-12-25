///
/// LICENSE
///

#pragma once

/// Macros

// Alloc
#define LITE_ALLOC(b)          lite::CommonAllocator::Alloc(b)
#define LITE_REALLOC(ptr, b)   lite::CommonAllocator::Realloc(ptr, b)
#define LITE_FREE(ptr)         lite::CommonAllocator::Free(ptr)

// Aligned Alloc
#define LITE_ALIGNED_ALLOC(b, a)        lite::CommonAllocator::AllocAligned(b, a)
#define LITE_ALIGNED_REALLOC(ptr, b, a) lite::CommonAllocator::ReallocAligned(ptr, b, a)
#define LITE_ALIGNED_FREE(ptr, a)       lite::CommonAllocator::FreeAligned(ptr, a)

// New/Delete
#define LITE_NEW(T)            new(LITE_ALLOC(sizeof(T))) T
#define LITE_DEL(ptr)          lite::Delete(ptr);

// Stack allocations
#define LITE_STACK_ALLOC(T, n) reinterpret_cast<T *>(alloca(sizeof(T) * n))

namespace lite {

template<typename T>
inline void Delete (T * ptr) {
    if (ptr) {
        ptr->~T();
        LITE_FREE(ptr);
    }
}

} // namespace lite
