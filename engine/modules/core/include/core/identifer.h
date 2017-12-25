///
/// LICENSE
///

#pragma once

namespace lite {

#define LITE_UNIQUE_IDENTIFIER(name, integral)               \
    class name {                                             \
    public:                                                  \
                                                             \
        using RawType = integral;                            \
                                                             \
        name () = default;                                   \
                                                             \
        /* Conversion */                                     \
        explicit name (RawType raw) : m_val(raw) { }         \
        explicit operator RawType () const { return m_val; } \
                                                             \
        /* Operators */                                      \
        bool operator< (const name & rhs) const  { return m_val < rhs.m_val; }  \
        bool operator> (const name & rhs) const  { return m_val > rhs.m_val; }  \
        bool operator== (const name & rhs) const { return m_val == rhs.m_val; } \
        bool operator!= (const name & rhs) const { return m_val != rhs.m_val; } \
                                                             \
    private:                                                 \
                                                             \
        RawType m_val = 0;                                   \
        static_assert(std::is_integral<RawType>::value, ""); \
    };

} // namespace lite
