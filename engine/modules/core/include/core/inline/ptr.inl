///
/// LICENSE
///

#pragma once

namespace lite {

///////////////////////////////////////////////////////////
//
//    RefCounted
//
///////////////////////////////////////////////////////////

inline RefCounted::~RefCounted () {
    LITE_ASSERT(m_refCount.Load() == 0);
}

inline void RefCounted::IncRef () const {
    m_refCount.IncrementRelease();
}

inline void RefCounted::DecRef () const {
    if (m_refCount.Decrement() == 1) {
        LITE_DEL(const_cast<RefCounted *>(this));
    }
}


///////////////////////////////////////////////////////////
//
//    SharedPtr
//
///////////////////////////////////////////////////////////

template<class T>
template<typename... Args>
SharedPtr<T> SharedPtr<T>::New (Args&&... args) {
    return SharedPtr<T>(LITE_NEW(T)(args...));
}

template<class T>
template<class TorDerived>
inline SharedPtr<T>::SharedPtr (TorDerived * ptrRaw)
    : m_ptr(ptrRaw)
{
    static_assert(std::is_base_of_v<T, TorDerived>, "Not convertible");
    LITE_ASSERT(m_ptr);
    LITE_ASSERT(m_ptr->m_refCount.Load() == 0);
    m_ptr->IncRef();
}

template<class T>
template<class TorDerived>
inline SharedPtr<T>::SharedPtr (TorDerived * ptrRaw, tag::RawPtr)
    : m_ptr(ptrRaw)
{
    static_assert(std::is_base_of_v<T, TorDerived>, "Not convertible");
    LITE_ASSERT(m_ptr);
    m_ptr->IncRef();
}

template<class T>
template<class TorDerived>
inline SharedPtr<T>::SharedPtr (const SharedPtr<TorDerived> & rhs)
    : m_ptr(rhs.m_ptr)
{
    static_assert(std::is_base_of_v<T, TorDerived>, "Not convertible");
    if (m_ptr)
        m_ptr->IncRef();
}

template<class T>
template<class TorDerived>
inline SharedPtr<T>::SharedPtr (SharedPtr<TorDerived> && rhs)
    : m_ptr(rhs.m_ptr)
{
    static_assert(std::is_base_of_v<T, TorDerived>, "Not convertible");
    rhs.m_ptr = nullptr;
}

template<class T>
inline SharedPtr<T>::~SharedPtr () {
    if (m_ptr) {
        m_ptr->DecRef();
        m_ptr = nullptr;
    }
}

template<class T>
template<class TorDerived>
inline SharedPtr<T> & SharedPtr<T>::operator= (const SharedPtr<TorDerived> & rhs) {
    static_assert(std::is_base_of_v<T, TorDerived>, "Not convertible");
    if (uintptr_t(&rhs) == uintptr_t(this))
        return *this;

    if (m_ptr)
        m_ptr->DecRef();

    m_ptr = rhs.m_ptr;
    if (m_ptr)
        m_ptr->IncRef();

    return *this;
}

template<class T>
template<class TorDerived>
inline void SharedPtr<T>::operator= (SharedPtr<TorDerived> && rhs) {
    static_assert(std::is_base_of_v<T, TorDerived>, "Not convertible");
    if (uintptr_t(&rhs) == uintptr_t(this))
        return;

    if (m_ptr)
        m_ptr->DecRef();

    m_ptr = rhs.m_ptr;
    rhs.m_ptr = nullptr;
}

template<class T>
inline void SharedPtr<T>::operator= (std::nullptr_t) {
    if (m_ptr) {
        m_ptr->DecRef();
        m_ptr = nullptr;
    }
}

template<class T>
inline T & SharedPtr<T>::operator* () {
    LITE_ASSERT(m_ptr);
    return *m_ptr;
}

template<class T>
inline const T & SharedPtr<T>::operator* () const {
    LITE_ASSERT(m_ptr);
    return *m_ptr;
}

template<class T>
inline T * SharedPtr<T>::operator-> () {
    LITE_ASSERT(m_ptr);
    return m_ptr;
}

template<class T>
inline const T * SharedPtr<T>::operator-> () const {
    LITE_ASSERT(m_ptr);
    return m_ptr;
}

template<class T>
inline T * SharedPtr<T>::Get () {
    return m_ptr;
}

template<class T>
inline const T * SharedPtr<T>::Get () const {
    return m_ptr;
}

template<class T>
inline SharedPtr<T>::operator bool () const {
    return !!m_ptr;
}

template<class T>
template<class TorDerived>
inline bool SharedPtr<T>::operator== (const SharedPtr<TorDerived> & rhs) const {
    static_assert(std::is_base_of_v<T, TorDerived>, "Not convertible");
    return m_ptr == rhs.m_ptr;
}

template<class T>
template<class TorDerived>
inline bool SharedPtr<T>::operator!= (const SharedPtr<TorDerived> & rhs) const {
    static_assert(std::is_base_of_v<T, TorDerived>, "Not convertible");
    return m_ptr != rhs.m_ptr;
}

} // namespace lite
