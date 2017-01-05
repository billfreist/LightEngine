
#include "core_pch.h"



namespace lite {

template<typename T, typename... Args>
static void Construct (T * ptr, Args... args) {
    new(ptr) T(std::forward<Args>(args)...);
}

void Test () {
    struct Tester {
      //  Tester (int) {}
      //  explicit Tester (uint32_t) {}
        explicit Tester (float) {}
    };
    Construct(LITE_STACK_ALLOC(int, 1), 5);
    Construct(LITE_STACK_ALLOC(float, 1), 5.0f);
   // Construct(LITE_STACK_ALLOC(Tester, 1), 5);
    Construct(LITE_STACK_ALLOC(Tester, 1), 5.0f);
}

int MemCmp (const void * left, const void * right, size_t size) {
    return std::memcmp(left, right, size);
}

void MemCopy (void * ptr, const void * src, size_t bytes) {
    std::memcpy(ptr, src, bytes);
}

bool MemIsZero (const void * mem, size_t size) {
    auto ptr  = reinterpret_cast<const char *>(mem);
    auto term = ptr + size;
    for (; ptr != term; ++ptr) {
        if (*ptr)
            return false;
    }
    return true;
}

void MemMove (void * ptr, const void * src, size_t bytes) {
    std::memmove(ptr, src, bytes);
}

void MemSet (void * ptr, size_t bytes, uint8_t v) {
    std::memset(ptr, v, bytes);
}

void MemZero (void * ptr, size_t bytes) {
    std::memset(ptr, 0, bytes);
}


} // common
