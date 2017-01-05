
#include "core_pch.h"
#include <malloc.h>


/// Override Global New/Delete
void * operator new (size_t bytes) {
    return lite::CommonAllocator::Alloc(bytes);
}

void operator delete (void * ptr) noexcept {
    lite::CommonAllocator::Free(ptr);
}


namespace lite {

void * CommonAllocator::Alloc (size_t bytes) {
    return ::malloc(bytes);
}

void CommonAllocator::Free (void * ptr) {
    ::free(ptr);
}

} // common
