///
/// LICENSE
///

#pragma once

#include <memory>
#include <type_traits>

///////////////////////////////////////////////////////////
//
//    Tags
//
///////////////////////////////////////////////////////////

namespace lite::tag {

enum class RawPtr { };

} // namespace tag


namespace lite {

///////////////////////////////////////////////////////////
//
//    RefCounted
//
///////////////////////////////////////////////////////////

class RefCounted {
    LITE_DECLARE_NOCOPY(RefCounted);
protected:

    ///
    RefCounted () = default;
    virtual ~RefCounted ();

    ///
    void IncRef () const;

    ///
    void DecRef () const;

private:

    mutable Atomic<int32_t> m_refCount{ 0 };

    template<class T>    friend class SharedPtr;
    template<typename T> friend void  lite::Delete (T *);
};


///////////////////////////////////////////////////////////
//
//    SharedPtr
//
///////////////////////////////////////////////////////////

template<class T>
class SharedPtr {
    static_assert(std::is_base_of<RefCounted, T>::value, "T must derive from RefCounted");
public:

    template<typename... Args>
    static SharedPtr New (Args&&... args);

public:

    /// Raw pointer construction from raw pointer of T or DerivedFromT
    /// This *must* be the first reference count of the object
    template<class TorDerived>
    explicit SharedPtr (TorDerived * ptrRaw);

    /// Raw pointer construction from raw pointer of T or DerivedFromT
    template<class TorDerived>
    SharedPtr (TorDerived * ptrRaw, tag::RawPtr);

    /// Copy construction from SharedPtr<T>
    SharedPtr (const SharedPtr<T> & rhs);

    /// Move construction from SharedPtr<T>
    SharedPtr (SharedPtr<T> && rhs) noexcept;

    ///
    SharedPtr () = default;
    ~SharedPtr ();

    /// Copy assignment of another SharePtr<T>
    SharedPtr & operator= (const SharedPtr<T> & rhs);

    /// Copy assignment of another SharePtr<Derived>
    template<class Derived>
    void operator= (const SharedPtr<Derived> & rhs);

    /// Move assignment of another SharePtr<T>
    SharedPtr & operator= (SharedPtr<T> && rhs) noexcept;

    /// Move assignment of another SharePtr<Derived>
    template<class Derived>
    void operator= (SharedPtr<Derived> && rhs);

    /// Explicitly handle nullptr
    void operator= (std::nullptr_t);

    ///
    T & operator* ();
    const T & operator* () const;

    ///
    T * operator-> ();
    const T * operator-> () const;

    ///
    T * Get ();
    const T * Get () const;

    ///
    operator bool () const;

    /// Equality operator of SharedPtr<T> or SharedPtr<DerivedFromT> or any
    /// combination of both
    template<class TorDerived>
    bool operator== (const SharedPtr<TorDerived> & rhs) const;

    /// Inequality operator of SharedPtr<T> or SharedPtr<DerivedFromT> or any
    /// combination of both
    template<class TorDerived>
    bool operator!= (const SharedPtr<TorDerived> & rhs) const;

private:

    T * m_ptr = nullptr;

    template<class T> friend class SharedPtr;
};


///////////////////////////////////////////////////////////
//
//    WeakTarget
//
///////////////////////////////////////////////////////////

template<class T>
class WeakTarget : public std::shared_ptr<T> {
public:

    WeakTarget (T * rawPtr, tag::RawPtr) : std::shared_ptr<T>(rawPtr) {}
};


///////////////////////////////////////////////////////////
//
//    WeakPtr
//
///////////////////////////////////////////////////////////

template<class T>
class WeakPtr : std::weak_ptr<T> {
public:

    WeakPtr (T * ptrRaw, tag::RawPtr) : std::weak_ptr<T>(ptrRaw) { }
};

} // namespace lite

#include <core/inline/ptr.inl>
