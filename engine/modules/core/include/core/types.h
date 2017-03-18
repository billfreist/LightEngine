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

    Type2 () = default;
    Type2 (tag::Uninitialized) { }
    Type2 (T x, T y) : x(x), y(y) { }

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

    Type3 () = default;
    Type3 (tag::Uninitialized) { }
    Type3 (T x, T y, T z) : x(x), y(y), z(z) { }

    T x, y, z;
};
using Vec3i = Type3<int32_t>;
using Vec3u = Type3<uint32_t>;
using Vec3f = Type3<float>;
using Vec3d = Type3<double>;


///
/// Vector4 types
///
template<typename T>
struct Type4 {
    static_assert(
        std::is_integral<T>::value || std::is_floating_point<T>::value,
        "Type must be integral or floating point"
    );

    T x, y, z, w;
};
using Vec4i = Type4<int32_t>;
using Vec4u = Type4<uint32_t>;
using Vec4f = Type4<float>;
using Vec4d = Type4<double>;


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


// Quaternion
class Quaternion {
public:

    Vec4f m_vec;

    Quaternion (tag::Identity)
        : m_vec{ 0.0f, 0.0f, 0.0f, 1.0f }
    {
    }

    Quaternion (tag::Uninitialized) {
    }

    Quaternion (const Vec4f & raw) : m_vec(raw) {
    }

    Quaternion (float x, float y, float z, float w)
        : m_vec{ x, y, z, w }
    {
    }

    Quaternion (const Vec3f & axis, float angle) {
        LITE_REF(axis, angle);
    }
};


// Transform
class Transform {
public:

    Transform (tag::Identity)
        : m_rotation{ tag::Identity{} }
        , m_position{ 0.0f, 0.0f, 0.0f }
    {
    }

    Transform (tag::Uninitialized)
        : m_rotation{ tag::Uninitialized{} }
        , m_position{ tag::Uninitialized{} }
    {
    }

    Transform (const Quaternion & rotation, const Vec3f & position)
        : m_rotation(rotation)
        , m_position(position)
    {
    }

private:

    Quaternion m_rotation;
    Vec3f      m_position;
};

// Array
template <typename T>
class Array : std::vector<T> {
public:

    T *       Ptr ()        { return std::vector<T>::data(); }
    const T * Ptr () const  { return std::vector<T>::data(); }
    T *       Term ()       { return std::vector<T>::data() + std::vector<T>::size(); }
    const T * Term () const { return std::vector<T>::data() + std::vector<T>::size(); }

    void Push (const T & data) { std::vector<T>::push_back(data); }
    T    Pop ()                { T tmp(std::move(std::vector<T>::back())); std::vector<T>::pop_back(); return tmp; }

    T * Add (T && v)                    { std::vector<T>::push_back(std::forward<T>(v)); return &std::vector<T>::back(); }
    void RemoveOrdered (const T * ptr)  { std::vector<T>::erase(std::vector<T>::begin() + (ptr - Ptr())); }
    void RemoveOrdered (uint32_t index) { std::vector<T>::erase(std::vector<T>::begin() + index); }

    void     Clear ()       { std::vector<T>::clear(); }
    void     Reset ()       { std::vector<T>::clear(); }

    uint32_t GetCount () const            { return uint32_t(std::vector<T>::size()); }
    void     SetCount (uint32_t newCount) { std::vector<T>::resize(newCount); }

    uint32_t GetCapacity () const            { return uint32_t(std::vector<T>::capacity()); }
    void     SetCapacity (uint32_t capacity) { std::vector<T>::reserve(capacity); }

    T & operator[] (uint32_t i)             { return std::vector<T>::at(i); }
    const T & operator[] (uint32_t i) const { return std::vector<T>::at(i); }

    /// Mutable iterating
    using Iterator      = T *;
    Iterator begin () { return Ptr(); }
    Iterator end ()   { return Term(); }

    /// Const iterating
    using ConstIterator = const T *;
    ConstIterator begin () const { return Ptr(); }
    ConstIterator end () const   { return Term(); }
};


// ExplicitConstructor
template<class T>
class ExplicitConstructor {
public:

    ~ExplicitConstructor ();

    void Init ();
    void Destroy ();

    T * Get ()        { return reinterpret_cast<T *>(&m_mem); }
    T * operator-> () { return Get(); }
    T & operator* ()  { return *Get(); }

private:

    using Memory = std::aligned_storage<sizeof(T), alignof(T)>;

    Memory m_mem;
    bool   m_isInit = false;
};

template<class T>
ExplicitConstructor<T>::~ExplicitConstructor () {
    LITE_ASSERT(!m_isInit);
}

template<class T>
void ExplicitConstructor<T>::Init () {
    LITE_ASSERT(!m_isInit);
    m_isInit = true;
    new(&m_mem) T;
}

template<class T>
void ExplicitConstructor<T>::Destroy () {
    LITE_ASSERT(m_isInit);
    m_isInit = false;
    Get()->~T();
}


#define LITE_DEFINE_ENUM_BIT_OPERATORS(e)                                                                                  \
    static_assert(std::is_enum<e>::value, LITE_STRINGIFY(e) " must be an enum to add bit operators!");                     \
    static_assert(std::is_unsigned<typename std::underlying_type<e>::type>::value, LITE_STRINGIFY(e) " must be unsigned"); \
    inline e operator~ (e val) { return e(~std::underlying_type_t<e>(val)); }                                              \
    inline e operator& (e lhs, e rhs) { return e(std::underlying_type_t<e>(lhs) & std::underlying_type_t<e>(rhs)); }       \
    inline e operator| (e lhs, e rhs) { return e(std::underlying_type_t<e>(lhs) | std::underlying_type_t<e>(rhs)); }       \
    inline e operator^ (e lhs, e rhs) { return e(std::underlying_type_t<e>(lhs) ^ std::underlying_type_t<e>(rhs)); }


// Flags
template<class T>
class Flags {
public:

    static_assert(std::is_unsigned<T>::value || std::is_enum<T>::value, "T must be unsigned");

    Flags () : m_val{} {
    }

    Flags (T raw) : m_val(raw) {
    }

    Flags (const Flags & rhs) : m_val(rhs.m_val) {
    }

    ///
    void ClearBits (T bits) {
        m_val = m_val & ~bits;
    }

    ///
    void SetBits (T bits) {
        m_val = m_val | bits;
    }

    /// Return true if any of 'bits' are set
    bool TestBits (T bits) {
        return !!(m_val & bits);
    }

    /// Return true if all of 'bits' are set
    bool TestAll (T bits) {
        return (m_val & bits) == bits;
    }

private:

    T m_val;
};

using Flags8  = Flags<uint8_t>;
using Flags16 = Flags<uint16_t>;
using Flags32 = Flags<uint32_t>;
using Flags64 = Flags<uint64_t>;

LITE_NAMESPACE_END(lite)
