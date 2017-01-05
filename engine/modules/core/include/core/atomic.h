#pragma once

namespace lite {

void AtomicSet (volatile int32_t * ptr, int32_t newValue);
void AtomicSet64 (volatile int64_t * ptr, int64_t newValue);
bool AtomicBoolCompareAndSwap (volatile int32_t * ptr, int32_t newValue, int32_t comparand);
bool AtomicBoolCompareAndSwap64 (volatile int64_t * ptr, int64_t newValue, int64_t comparand);

} // common

#include <core/inline/atomic.inl>
