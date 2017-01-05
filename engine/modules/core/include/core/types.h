#pragma once

#ifdef _MSC_VER
#    define LITE_NO_VTABLE __declspec(novtable)
#else
#    define LITE_NO_VTABLE
#endif

#undef interface
#define interface struct LITE_NO_VTABLE


namespace lite {

#define LITE_COORD3(type, prefix, arg0, arg1, arg2) \
    struct Coord3##prefix {                           \
        type arg0;                                    \
        type arg1;                                    \
        type arg2;                                    \
    };

LITE_COORD3(float, f, x, y, z);

// Array
template <typename T>
class Array : std::vector<T> {
public:

    T *       Ptr ()        { return std::vector<T>::data(); }
    const T * Ptr () const  { return std::vector<T>::data(); }
    T *       Term ()       { return std::vector<T>::data() + std::vector<T>::size(); }
    const T * Term () const { return std::vector<T>::data() + std::vector<T>::size(); }

    void Push (const T & data) { std::vector<T>::push_back(data); }
    T    Pop ()                { T tmp = std::vector<T>::back(); std::vector<T>::pop_back(); return tmp; }

    uint32_t Count () const { return uint32_t(std::vector<T>::size()); }
    void     Clear ()       { std::vector<T>::clear(); }
    void     Reset ()       { std::vector<T>::clear(); }
    void     SetCount (uint32_t newCount) { std::vector<T>::resize(newCount); }

    uint32_t Capacity () const { return uint32_t(std::vector<T>::capacity()); }
    void     SetCapacity (uint32_t capacity) { std::vector<T>::reserve(capacity); }

    T & operator[] (uint32_t i)             { return std::vector<T>::[i]; }
    const T & operator[] (uint32_t i) const { return std::vector<T>::[i]; }

    typedef T * Iterator;
    Iterator begin () { return Ptr(); }
    Iterator end ()   { return Term(); }

};

// Lock
class Lock final : std::mutex {
public:

    void Enter ()    { std::mutex::lock(); }
    bool TryEnter () { std::mutex::try_lock(); }
    void Leave ()    { std::mutex::unlock(); }

};


} // common
