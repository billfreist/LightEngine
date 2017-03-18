///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite)

TEST(Allocator, Alloc) {
    // Macro Alloc/Free
    void * ptr = LITE_ALLOC(1);
    LITE_FREE(ptr);
}

TEST(Allocator, LiteNew) {
    // Macro new/del
    uint32_t * ptr = LITE_NEW(uint32_t);
    LITE_DEL(ptr);
}

TEST(Allocator, New_Mixed) {
    // Standard new/delete should use custom allocator
    uint32_t * ptr = new uint32_t;
    LITE_FREE(ptr);
    ptr = LITE_NEW(uint32_t);
    delete ptr;
}

LITE_NAMESPACE_END(lite)
