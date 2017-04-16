///
/// LICENSE
///

#pragma once

LITE_NAMESPACE_BEGIN(lite)

///////////////////////////////////////////////////////////
//
//    Atomic
//
///////////////////////////////////////////////////////////

template<typename T>
inline Atomic<T>::Atomic (T val) : m_val{val} {
}

template<typename T>
inline T Atomic<T>::Load () const {
    return m_val.load(std::memory_order_seq_cst);
}

template<typename T>
inline T Atomic<T>::LoadRelaxed () const {
    return m_val.load(std::memory_order_relaxed);
}

template<typename T>
inline void Atomic<T>::Set (T val) {
    return m_val.store(std::memory_order_seq_cst);
}

template<typename T>
inline void Atomic<T>::SetRelaxed (T val) {
    return m_val.store(std::memory_order_relaxed);
}

template<typename T>
inline T Atomic<T>::Exchange (T val) {
    return m_val.exchange(val, std::memory_order_seq_cst);
}

template<typename T>
inline T Atomic<T>::ExchangeRelaxed (T val) {
    return m_val.exchange(val, std::memory_order_relaxed);
}

template<typename T>
inline LITE_ATOMIC_INTEGRAL_ONLY(T) Atomic<T>::Increment () {
    return m_val.fetch_add(T(1), std::memory_order_seq_cst);
}

template<typename T>
inline LITE_ATOMIC_INTEGRAL_ONLY(T) Atomic<T>::IncrementRelaxed () {
    return m_val.fetch_add(T(1), std::memory_order_relaxed);
}

template<typename T>
inline LITE_ATOMIC_INTEGRAL_ONLY(T) Atomic<T>::Decrement () {
    return m_val.fetch_sub(T(1), std::memory_order_seq_cst);
}

template<typename T>
inline LITE_ATOMIC_INTEGRAL_ONLY(T) Atomic<T>::DecrementRelaxed () {
    return m_val.fetch_sub(T(1), std::memory_order_relaxed);
}

template<typename T>
inline LITE_ATOMIC_INTEGRAL_ONLY(T) Atomic<T>::Add (T val) {
    return m_val.fetch_add(val, std::memory_order_seq_cst);
}

template<typename T>
inline LITE_ATOMIC_INTEGRAL_ONLY(T) Atomic<T>::AddRelaxed (T val) {
    return m_val.fetch_add(val, std::memory_order_relaxed);
}

template<typename T>
inline LITE_ATOMIC_INTEGRAL_ONLY(T) Atomic<T>::Sub (T val) {
    return m_val.fetch_sub(val, std::memory_order_seq_cst);
}

template<typename T>
inline LITE_ATOMIC_INTEGRAL_ONLY(T) Atomic<T>::SubRelaxed (T val) {
    return m_val.fetch_sub(val, std::memory_order_relaxed);
}

template<typename T>
inline bool Atomic<T>::CompareExchangeStrong (T val, T comparand) {
    return m_val.compare_exchange_strong(comparand, val, std::memory_order_seq_cst);
}

template<typename T>
inline bool Atomic<T>::CompareExchangeStrongRelaxed (T val, T comparand) {
    return m_val.compare_exchange_strong(comparand, val, std::memory_order_relaxed);
}

template<typename T>
inline bool Atomic<T>::CompareExchangeWeak (T val, T comparand) {
    return m_val.compare_exchange_weak(comparand, val, std::memory_order_seq_cst);
}

template<typename T>
inline bool Atomic<T>::CompareExchangeWeakRelaxed (T val, T comparand) {
    return m_val.compare_exchange_weak(comparand, val, std::memory_order_relaxed);
}

LITE_NAMESPACE_END(lite)
