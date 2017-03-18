///
/// LICENSE
///

#pragma once

#include <memory>

LITE_NAMESPACE_BEGIN(lite, tag)

enum class RawPtr { };

LITE_NAMESPACE_END(tag)

template<class T>
class WeakTarget : public std::shared_ptr<T> {
public:

    WeakTarget (T * rawPtr, tag::RawPtr) : std::shared_ptr<T>(rawPtr) {}
};


template<class T>
class SharedPtr : std::shared_ptr<T> {
public:

    SharedPtr (T * ptrRaw, tag::RawPtr) : std::shared_ptr<T>(ptrRaw) { }

    T & operator* ()              { return *std::shared_ptr<T>::get();  }
    const T & operator* () const  { return *std::shared_ptr<T>::get();  }
    T * operator-> ()             { return std::shared_ptr<T>::get();   }
    const T * operator-> () const { return std::shared_ptr<T>::get();   }
    T * Get ()                    { return std::shared_ptr<T>::get();   }
    const T * Get () const        { return std::shared_ptr<T>::get();   }
    operator bool () const        { return !!std::shared_ptr<T>::get(); }
};


template<class T>
class WeakPtr : std::weak_ptr<T> {
public:

    WeakPtr (T * ptrRaw, tag::RawPtr) : std::weak_ptr<T>(ptrRaw) { }
};

LITE_NAMESPACE_END(lite)
