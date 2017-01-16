///
/// LICENSE
///

#include "core_pch.h"

LITE_NAMESPACE_BEGIN(lite)

const uint32_t SPIN_COUNT = 75;
const uint32_t SPIN_COUNT_MP = 1000;
const uint32_t PAUSE_EXP = 12;


SpinLock::SpinLock () {
    m_spinCount = ThreadGetCoreCount() > 2 ? SPIN_COUNT_MP : SPIN_COUNT;
}

void SpinLock::Enter () {
    // Trivial lock
    if (TryEnter())
        return;

    // Spin
    for (uint32_t i = 0; i < SPIN_COUNT; ++i) {
        if (TryEnter())
            return;
    }

    // Spin with exponential back-off
    for (uint32_t i = 0, m = 1; i < PAUSE_EXP; ++i, m *= 2) {
        if (TryEnter())
            return;

        for (uint32_t j = 0; j < m; ++j)
            _mm_pause();
    }

    // Thread yield to scheduler
    while (!TryEnter())
        ThreadYield();
}

LITE_NAMESPACE_END(lite)
