///
/// LICENSE
///

#pragma once

#ifdef _MSC_VER
#    define LITE_NO_VTABLE __declspec(novtable)
#else
#    define LITE_NO_VTABLE
#endif

#undef interface
#define interface struct LITE_NO_VTABLE


LITE_NAMESPACE_BEGIN(lite)

///
/// Vector2 types
///
template<typename T>
struct Type2 {
    static_assert(
        std::is_integral<T>::value || std::is_floating_point<T>::value,
        "Type must be integral or floating point"
    );

    T x, y;
};
using Vec2i = Type2<int32_t>;
using Vec2u = Type2<uint32_t>;
using Vec2f = Type2<float>;
using Vec2d = Type2<double>;


///
/// Vector3 types
///
template<typename T>
struct Type3 {
    static_assert(
        std::is_integral<T>::value || std::is_floating_point<T>::value,
        "Type must be integral or floating point"
    );

    T x, y, z;
};
using Vec3i = Type3<int32_t>;
using Vec3u = Type3<uint32_t>;
using Vec3f = Type3<float>;
using Vec3d = Type3<double>;


///
/// Vector6 types
///
template<typename T>
struct Type6 {
    static_assert(
        std::is_integral<T>::value || std::is_floating_point<T>::value,
        "Type must be integral or floating point"
    );

    Type3<T> min;
    Type3<T> max;
};
using Box6i = Type6<int32_t>;
using Box6u = Type6<uint32_t>;
using Box6f = Type6<float>;
using Box6d = Type6<double>;


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

    void     Clear ()       { std::vector<T>::clear(); }
    void     Reset ()       { std::vector<T>::clear(); }

    uint32_t GetCount () const { return uint32_t(std::vector<T>::size()); }
    void     SetCount (uint32_t newCount) { std::vector<T>::resize(newCount); }

    uint32_t GetCapacity () const { return uint32_t(std::vector<T>::capacity()); }
    void     SetCapacity (uint32_t capacity) { std::vector<T>::reserve(capacity); }

    T & operator[] (uint32_t i)             { return std::vector<T>::[i]; }
    const T & operator[] (uint32_t i) const { return std::vector<T>::[i]; }

    /// Mutable iterating
    using Iterator      = T *;
    Iterator begin () { return Ptr(); }
    Iterator end ()   { return Term(); }

    /// Const iterating
    using ConstIterator = const T *;
    ConstIterator begin () const { return Ptr(); }
    ConstIterator end () const   { return Term(); }
};

// Lock
class Lock final : std::mutex {
public:

    void Enter ()    { std::mutex::lock(); }
    bool TryEnter () { std::mutex::try_lock(); }
    void Leave ()    { std::mutex::unlock(); }
};

LITE_NAMESPACE_END(lite)
