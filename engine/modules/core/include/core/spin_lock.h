///
/// LICENSE
///

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

    Atomic<int32_t> m_lock{ 0 };
    uint32_t        m_spinCount;
};

} // namespace lite

#include <core/inline/spin_lock.inl>
