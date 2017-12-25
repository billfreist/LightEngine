///
/// LICENSE
///

#pragma once

#include <atomic>

namespace lite {

///////////////////////////////////////////////////////////
//
//    Atomic
//
///////////////////////////////////////////////////////////

#define LITE_ATOMIC_INTEGRAL_ONLY(t) std::enable_if_t<!std::is_same<t, bool>::value, t>

template<typename T>
class Atomic {
    static_assert(std::is_integral<T>::value, "T must be integral to be atomic");
public:

    /// You must initialize to a valid value
    explicit Atomic (T val);

    ///
    T Load () const;
    T LoadRelaxed () const;

    ///
    void Set (T val);
    void SetRelaxed (T val);

    ///
    T Exchange (T val);
    T ExchangeRelaxed (T val);

    ///
    LITE_ATOMIC_INTEGRAL_ONLY(T) Increment ();
    LITE_ATOMIC_INTEGRAL_ONLY(T) IncrementRelease ();
    LITE_ATOMIC_INTEGRAL_ONLY(T) IncrementRelaxed ();

    ///
    LITE_ATOMIC_INTEGRAL_ONLY(T) Decrement ();
    LITE_ATOMIC_INTEGRAL_ONLY(T) DecrementRelease ();
    LITE_ATOMIC_INTEGRAL_ONLY(T) DecrementRelaxed ();

    ///
    LITE_ATOMIC_INTEGRAL_ONLY(T) Add (T val);
    LITE_ATOMIC_INTEGRAL_ONLY(T) AddRelaxed (T val);

    ///
    LITE_ATOMIC_INTEGRAL_ONLY(T) Sub (T val);
    LITE_ATOMIC_INTEGRAL_ONLY(T) SubRelaxed (T val);

    ///
    bool CompareExchangeStrong (T val, T comparand);
    bool CompareExchangeStrongRelaxed (T val, T comparand);

    ///
    bool CompareExchangeWeak (T val, T comparand);
    bool CompareExchangeWeakRelaxed (T val, T comparand);

private:

    std::atomic<T> m_val;
};

} // namespace lite

#include <core/inline/atomic.inl>
