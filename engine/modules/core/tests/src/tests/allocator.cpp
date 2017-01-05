
#include "core_tests_pch.h"

namespace lite {

void TestAlloc () {
    // Macro Alloc/Free
    void * ptr = LITE_ALLOC(1);
    LITE_FREE(ptr);

    // Macro new/del
    ptr = LITE_NEW(uint32_t);
    LITE_DEL(ptr);

    // Standard new/delete should use custom allocator
    ptr = new uint32_t;
    LITE_FREE(ptr);
    ptr = LITE_NEW(uint32_t);
    delete ptr;
}

} // common
