///
/// LICENSE
///

#pragma once

#include <vector>

#ifdef _MSC_VER
#    define LITE_NO_VTABLE __declspec(novtable)
#else
#    define LITE_NO_VTABLE
#endif

#undef interface
#define interface struct LITE_NO_VTABLE


namespace lite {

///////////////////////////////////////////////////////////
//
//    Type2
//
///////////////////////////////////////////////////////////

template<typename T>
struct Type2 {
    static_assert(
        std::is_integral<T>::value || std::is_floating_point<T>::value,
        "Type must be integral or floating point"
    );

    Type2 (tag::Uninitialized)                   { }
    constexpr Type2 (tag::Zero) : x(0), y(0)     { }
    constexpr Type2 (T all) : x(all), y(all)     { }
    constexpr Type2 (T x, T y, T z) : x(x), y(y) { }
    constexpr Type2 (const Type2<T>& type2) : x(type2.x), y(type2.y) { }

    T x, y;
};
using Vec2i = Type2<int32_t>;
using Vec2u = Type2<uint32_t>;
using Vec2f = Type2<float>;
using Vec2d = Type2<double>;


///////////////////////////////////////////////////////////
//
//    Type3
//
///////////////////////////////////////////////////////////

template<typename T>
struct Type3 {
    static_assert(
        std::is_integral<T>::value || std::is_floating_point<T>::value,
        "Type must be integral or floating point"
    );

    Type3 (tag::Uninitialized) { }
    constexpr Type3 (tag::Zero) : x(0), y(0), z(0)     { }
    constexpr Type3 (T all) : x(all), y(all), z(all)   { }
    constexpr Type3 (T x, T y, T z) : x(x), y(y), z(z) { }
    constexpr Type3 (const Type2<T> & type2, T z) : x(type2.x), y(type2.y), z(z)  { }
    constexpr Type3 (const Type3<T> & type3) : x(type3.x), y(type3.y), z(type3.z) { }

    Type3 & operator= (const Type3 & rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }

    bool operator== (const Type3 & rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
    bool operator!= (const Type3 & rhs) const { return !(*this == rhs); }

    Type3 operator+ (const Type3 & rhs) const { return Type3(x + rhs.x, y + rhs.y, z + rhs.z); }
    Type3 operator- (const Type3 & rhs) const { return Type3(x - rhs.x, y - rhs.y, z - rhs.z); }
    Type3 operator* (const Type3 & rhs) const { return Type3(x * rhs.x, y * rhs.y, z * rhs.z); }
    Type3 operator/ (const Type3 & rhs) const { return Type3(x / rhs.x, y / rhs.y, z / rhs.z); }

    void operator+= (const Type3 & rhs) { *this = *this + rhs; }
    void operator-= (const Type3 & rhs) { *this = *this - rhs; }
    void operator*= (const Type3 & rhs) { *this = *this * rhs; }
    void operator/= (const Type3 & rhs) { *this = *this / rhs; }

    T x, y, z;
};
using Vec3i = Type3<int32_t>;
using Vec3u = Type3<uint32_t>;
using Vec3f = Type3<float>;
using Vec3d = Type3<double>;


///////////////////////////////////////////////////////////
//
//    Type4
//
///////////////////////////////////////////////////////////

template<typename T>
struct Type4 {
    static_assert(
        std::is_integral<T>::value || std::is_floating_point<T>::value,
        "Type must be integral or floating point"
    );

    Type4 (tag::Uninitialized) { }
    constexpr Type4 (tag::Zero) : x(0), y(0), z(0), w(0)          { }
    constexpr Type4 (T all) : x(all), y(all), z(all), w(all)      { }
    constexpr Type4 (T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
    constexpr Type4 (const Type3<T> & type3, T w) : x(type3.x), y(type3.y), z(type3.z), w(w)  { }
    constexpr Type4 (const Type4 & type4) : x(type4.x), y(type4.y), z(type4.z), w(type4.w) { }

    Type4 & operator= (const Type4 & rhs) { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; return *this; }

    bool operator== (const Type4 & rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
    bool operator!= (const Type4 & rhs) const { return !(*this == rhs); }

    Type4 operator+ (const Type4 & rhs) const { return Type4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
    Type4 operator- (const Type4 & rhs) const { return Type4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
    Type4 operator* (const Type4 & rhs) const { return Type4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w); }
    Type4 operator/ (const Type4 & rhs) const { return Type4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w); }

    void operator+= (const Type4 & rhs) { *this = *this + rhs; }
    void operator-= (const Type4 & rhs) { *this = *this - rhs; }
    void operator*= (const Type4 & rhs) { *this = *this * rhs; }
    void operator/= (const Type4 & rhs) { *this = *this / rhs; }

    T x, y, z, w;
};
using Vec4i = Type4<int32_t>;
using Vec4u = Type4<uint32_t>;
using Vec4f = Type4<float>;
using Vec4d = Type4<double>;


///////////////////////////////////////////////////////////
//
//    Type6
//
///////////////////////////////////////////////////////////

template<typename T>
struct Type6 {
    static_assert(
        std::is_integral<T>::value || std::is_floating_point<T>::value,
        "Type must be integral or floating point"
    );

    Type6 (tag::Uninitialized tag)  : min(tag), max(tag) { }
    constexpr Type6 (tag::Zero tag) : min(tag), max(tag) { }
    constexpr Type6 (const Type3<T> & min, const Type3<T> & max) : min(min) , max(max) { }

    Type6& operator= (const Type6& rhs) { min = rhs.min; max = rhs.max; return *this; }

    Type3<T> min;
    Type3<T> max;
};
using Box6i = Type6<int32_t>;
using Box6u = Type6<uint32_t>;
using Box6f = Type6<float>;
using Box6d = Type6<double>;


///////////////////////////////////////////////////////////
//
//    Color4
//
///////////////////////////////////////////////////////////

template<typename T>
struct Color4 {
    static_assert(
        std::is_integral<T>::value || std::is_floating_point<T>::value,
        "Type must be integral or floating point"
    );

    Color4 (tag::Uninitialized) { }
    constexpr Color4 (tag::Zero) : r(0), g(0), b(0), a(0)          { }
    constexpr Color4 (T r, T g, T b, T a) : r(r), g(g), b(b), a(a) { }
    constexpr Color4 (const Color4& rhs) : r(rhs.r), g(rhs.g), b(rhs.b), a(rhs.a) { }

    Color4& operator= (const Color4& rhs) { r = rhs.r; g = rhs.g; b = rhs.b; a = rhs.a; return *this; }

    T r, g, b, a;
};
using Color4b = Color4<uint8_t>;
using Color4f = Color4<float>;


///////////////////////////////////////////////////////////
//
//    Quaternion
//
///////////////////////////////////////////////////////////

class Quaternion {
public:

    Quaternion (tag::Identity)
        : m_vec{ 0.0f, 0.0f, 0.0f, 1.0f }
    {
    }

    Quaternion (tag::Uninitialized tag)
        : m_vec(tag)
    {
    }

    explicit Quaternion (const Vec4f & raw)
        : m_vec(raw)
    {
    }

    Quaternion (float x, float y, float z, float w)
        : m_vec{ x, y, z, w }
    {
    }

    Quaternion (const Vec3f & axis, float angle)
        : m_vec(0.0f, 0.0f, 0.0f, 1.0f)
    {
        LITE_REF(axis, angle);
    }

    explicit operator Vec4f () const {
        return m_vec;
    }

    const Vec4f & GetVec () const {
        return m_vec;
    }

    ///
    bool IsNormalized () const {
        const float lenSq =
            (m_vec.x * m_vec.x) +
            (m_vec.y * m_vec.y) +
            (m_vec.z * m_vec.z) +
            (m_vec.w * m_vec.w);
        return std::sqrtf(lenSq) < 1.e-5f;
    }
    Quaternion & Normalize () {
        const float lenSq =
            (m_vec.x * m_vec.x) +
            (m_vec.y * m_vec.y) +
            (m_vec.z * m_vec.z) +
            (m_vec.w * m_vec.w);
        if (std::isnormal(lenSq)) {
            const float len = std::sqrtf(lenSq);
            m_vec /= len;
        }
        else {
            m_vec = { 0.0f, 0.0f, 0.0f, 1.0f };
        }
    }

private:

    Vec4f m_vec;
};


///////////////////////////////////////////////////////////
//
//    Transform
//        Rotation, Translation and Uniform Scale
//
///////////////////////////////////////////////////////////

class Transform {
public:

    Transform (tag::Identity)
        : m_rotation{ tag::Identity{} }
        , m_position{ 0.0f, 0.0f, 0.0f, 1.0f }
    {
    }

    Transform (tag::Uninitialized)
        : m_rotation{ tag::Uninitialized{} }
        , m_position{ tag::Uninitialized{} }
    {
    }

    /// Initialize with rotation, position and 1.0f scale
    Transform (const Quaternion & rotation, const Vec3f & position)
        : m_rotation(rotation)
        , m_position(position, 1.0f)
    {
    }

    /// Initialize with rotation, position and scale
    Transform (const Quaternion & rotation, const Vec4f & positionWithScale)
        : m_rotation(rotation)
        , m_position(positionWithScale)
    {
    }


    ///
    Vec3f GetPosition () const { return Vec3f(m_position.x, m_position.y, m_position.z); }
    void SetPosition (const Vec3f & translation) {
        m_position = Vec4f(translation, m_position.w);
    }

    ///
    Vec4f GetPositionWithScale () const { return m_position; }
    void SetPositionWithScale (const Vec4f & translationWithScale) {
        m_position = translationWithScale;
    }

    ///
    Quaternion GetRotation () const { return m_rotation; }
    void       SetRotation (const Quaternion & rotation) {
        LITE_ASSERT(rotation.IsNormalized());
        m_rotation = rotation;
    }

private:

    Quaternion m_rotation;
    Vec4f      m_position;
};


///////////////////////////////////////////////////////////
//
//    ArrayView
//
///////////////////////////////////////////////////////////

template <typename T>
class ArrayView {
public:

    template<size_t ArraySize>
    ArrayView (const T (& ptr)[ArraySize]) : m_data(ptr), m_count(ArraySize) { }
    ArrayView (uint32_t count, T * ptr) : m_data(ptr), m_count(count) { }

    T *       Ptr ()       { return m_data; }
    const T * Ptr () const { return m_data; }

    T *       Term ()       { return m_data + m_count; }
    const T * Term () const { return m_data + m_count; }

    uint32_t GetCount () const { return m_count; }

    T &       operator[] (uint32_t i)       { LITE_ASSERT(i < m_count); return m_data[i]; }
    const T & operator[] (uint32_t i) const { LITE_ASSERT(i < m_count); return m_data[i]; }

    /// Const array view conversion
    operator ArrayView<const T>() const { return ArrayView<const T>(GetCount(), Ptr()); }

    /// Mutable iterating
    using Iterator = T *;
    Iterator begin () { return Ptr(); }
    Iterator end ()   { return Term(); }

    /// Const iterating
    using ConstIterator = const T *;
    ConstIterator begin () const { return Ptr(); }
    ConstIterator end () const   { return Term(); }

private:

    T *      m_data;
    uint32_t m_count;
};


///////////////////////////////////////////////////////////
//
//    Array
//
///////////////////////////////////////////////////////////

template <typename T>
class Array : std::vector<T> {
public:

    Array () = default;
    Array (const Array<T> & arr) = default;
    Array (Array<T> && arr) = default;
    Array (const ArrayView<T> & view)       : std::vector<T>(view.begin(), view.end()) {}
    Array (const ArrayView<const T> & view) : std::vector<T>(view.begin(), view.end()) {}

    T *       Ptr ()        { return std::vector<T>::data(); }
    const T * Ptr () const  { return std::vector<T>::data(); }
    T *       Term ()       { return std::vector<T>::data() + std::vector<T>::size(); }
    const T * Term () const { return std::vector<T>::data() + std::vector<T>::size(); }

    void Push (const T & data) { std::vector<T>::push_back(data); }
    T    Pop ()                { T tmp(std::move(std::vector<T>::back())); std::vector<T>::pop_back(); return tmp; }

    T * Add (const T & v)               { std::vector<T>::push_back(v); return &std::vector<T>::back(); }
    T * Add (T && v)                    { std::vector<T>::push_back(std::forward<T>(v)); return &std::vector<T>::back(); }
    void RemoveOrdered (const T * ptr)  { std::vector<T>::erase(std::vector<T>::begin() + (ptr - Ptr())); }
    void RemoveOrdered (uint32_t index) { std::vector<T>::erase(std::vector<T>::begin() + index); }

    void RemoveValueOrdered (const T & val) { std::vector<T>::erase(std::find(std::vector<T>::begin(), std::vector<T>::end(), val)); }

    void     Clear ()       { std::vector<T>::clear(); }
    void     Reset ()       { std::vector<T>::clear(); }

    uint32_t GetCount () const            { return uint32_t(std::vector<T>::size()); }
    void     SetCount (uint32_t newCount) { std::vector<T>::resize(newCount); }

    uint32_t GetCapacity () const            { return uint32_t(std::vector<T>::capacity()); }
    void     SetCapacity (uint32_t capacity) { std::vector<T>::reserve(capacity); }

    T & operator[] (uint32_t i)             { return std::vector<T>::at(i); }
    const T & operator[] (uint32_t i) const { return std::vector<T>::at(i); }

    operator ArrayView<T>()             { return ArrayView<T>(GetCount(), Ptr()); }
    operator ArrayView<const T>() const { return ArrayView<const T>(GetCount(), Ptr()); }

    Array & operator= (const ArrayView<T> & view)       { std::vector<T>::assign(view.begin(), view.end()); return *this; }
    Array & operator= (const ArrayView<const T> & view) { std::vector<T>::assign(view.begin(), view.end()); return *this; }

    Array & operator= (const Array<T> & view) = default;
    Array & operator= (Array<T> && view) = default;

    /// Mutable iterating
    using Iterator = T *;
    Iterator begin () { return Ptr(); }
    Iterator end ()   { return Term(); }

    /// Const iterating
    using ConstIterator = const T *;
    ConstIterator begin () const { return Ptr(); }
    ConstIterator end () const   { return Term(); }
};


///////////////////////////////////////////////////////////
//
//    ExplicitConstructor
//
///////////////////////////////////////////////////////////

template<class T>
class ExplicitConstructor {
public:

    ~ExplicitConstructor ();

    template<typename... Args>
    void Init (Args&&... args);
    void Destroy ();

    T * Get ()        { return reinterpret_cast<T *>(&m_mem); }
    T * operator-> () { return Get(); }
    T & operator* ()  { return *Get(); }

private:

    using Memory = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

    Memory m_mem;
    bool   m_isInit = false;
};

template<class T>
ExplicitConstructor<T>::~ExplicitConstructor () {
    LITE_ASSERT(!m_isInit);
}

template<class T>
template<typename... Args>
void ExplicitConstructor<T>::Init (Args&&... args) {
    LITE_ASSERT(!m_isInit);
    m_isInit = true;
    new(&m_mem) T(std::forward<Args>(args)...);
}

template<class T>
void ExplicitConstructor<T>::Destroy () {
    LITE_ASSERT(m_isInit);
    m_isInit = false;
    Get()->~T();
}


///////////////////////////////////////////////////////////
//
//    Flags
//
///////////////////////////////////////////////////////////

#define LITE_DEFINE_ENUM_BIT_OPERATORS(e)                                                                                  \
    static_assert(std::is_enum<e>::value, LITE_STRINGIFY(e) " must be an enum to add bit operators!");                     \
    static_assert(std::is_unsigned<typename std::underlying_type<e>::type>::value, LITE_STRINGIFY(e) " must be unsigned"); \
    inline e operator~ (e val) { return e(~std::underlying_type_t<e>(val)); }                                              \
    inline e operator& (e lhs, e rhs) { return e(std::underlying_type_t<e>(lhs) & std::underlying_type_t<e>(rhs)); }       \
    inline e operator| (e lhs, e rhs) { return e(std::underlying_type_t<e>(lhs) | std::underlying_type_t<e>(rhs)); }       \
    inline e operator^ (e lhs, e rhs) { return e(std::underlying_type_t<e>(lhs) ^ std::underlying_type_t<e>(rhs)); }

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

} // namespace lite
