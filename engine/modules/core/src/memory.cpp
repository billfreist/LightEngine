///
/// LICENSE
///

#include "pch.h"

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
    //Construct(LITE_STACK_ALLOC(Tester, 1), 5);
    Construct(LITE_STACK_ALLOC(Tester, 1), 5.0f);
}

bool MemIsZero (const void * mem, size_t bytes) {
    const char * ptr  = reinterpret_cast<const char *>(mem);
    const char * term = ptr + bytes;
    for (; ptr != term; ++ptr) {
        if (*ptr)
            return false;
    }
    return true;
}

} // namespace lite
