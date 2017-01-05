#pragma once

namespace lite {

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

} // common

#include <core/inline/spin_lock.inl>
