///
/// LICENSE
///

#include "core_pch.h"

LITE_NAMESPACE_BEGIN(lite)

void AtomicSet (volatile int32_t * ptr, int32_t newValue) {
    InterlockedExchange(reinterpret_cast<volatile long *>(ptr), newValue);
}

void AtomicSet64 (volatile int64_t * ptr, int64_t newValue) {
    InterlockedExchange64(ptr, newValue);
}

bool AtomicBoolCompareAndSwap (volatile int32_t * ptr, int32_t newValue, int32_t comparand) {
    return InterlockedCompareExchange(reinterpret_cast<volatile long *>(ptr), newValue, comparand) == comparand;
}

bool AtomicBoolCompareAndSwap64 (volatile int64_t * ptr, int64_t newValue, int64_t comparand) {
    return InterlockedCompareExchange64(ptr, newValue, comparand) == comparand;
}

LITE_NAMESPACE_END(lite)
