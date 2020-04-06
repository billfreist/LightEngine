#pragma once

#include <core/thread.h>

namespace lite {

inline bool SpinLock::TryEnter () {
    const int32_t threadId = ThreadGetId();
    if (m_lock.CompareExchangeWeak(threadId, 0))
        return true;

    // Catch reentrant locks.
    if constexpr (LITE_BUILD_DEBUG)
        return m_lock.CompareExchangeStrong(threadId, threadId);
    else
        return false;
}

inline void SpinLock::Leave () {
    const int32_t threadId = ThreadGetId();
    const bool    unlocked = m_lock.CompareExchangeStrongRelaxed(0, threadId);
    LITE_ASSERT(unlocked);
}

} // namespace lite
