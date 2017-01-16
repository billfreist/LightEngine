///
/// LICENSE
///

#pragma once

/// Macros

// Alloc
#define LITE_ALLOC(b)          lite::CommonAllocator::Alloc(b)
#define LITE_FREE(ptr)         lite::CommonAllocator::Free(ptr)

// New/Delete
#define LITE_NEW(T)            new(LITE_ALLOC(sizeof(T))) T
#define LITE_DEL(ptr)          lite::Delete(ptr);

// Stack allocations
#define LITE_STACK_ALLOC(T, n) reinterpret_cast<T *>(alloca(sizeof(T) * n))

LITE_NAMESPACE_BEGIN(lite)

template<typename T>
inline void Delete (T * ptr) {
    if (ptr) {
        ptr->~T();
        LITE_FREE(ptr);
    }
}

LITE_NAMESPACE_END(lite)
