#pragma once

#include <core/thread.h>

LITE_NAMESPACE_BEGIN(lite)

inline bool SpinLock::TryEnter () {
    const int32_t threadId = ThreadGetId();
    if (AtomicBoolCompareAndSwap(&m_lock, threadId, 0))
        return true;
    // Catch reentrant locks.
    return AtomicBoolCompareAndSwap(&m_lock, threadId, threadId);
}

inline void SpinLock::Leave () {
    const int32_t threadId = ThreadGetId();
    const bool    unlocked = AtomicBoolCompareAndSwap(&m_lock, 0, threadId);
    LITE_ASSERT(unlocked);
}

LITE_NAMESPACE_END(lite)
