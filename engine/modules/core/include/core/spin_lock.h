///
/// LICENSE
///

#pragma once

LITE_NAMESPACE_BEGIN(lite)

// SpinLock
class LITE_ALIGN_CACHELINE SpinLock final {
public:

    SpinLock ();

    void Enter ();
    inline bool TryEnter ();
    inline void Leave ();

private:

    volatile int32_t m_lock = 0;
    uint32_t         m_spinCount;
};

LITE_NAMESPACE_END(lite)

#include <core/inline/spin_lock.inl>
