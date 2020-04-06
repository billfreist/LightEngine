///
/// LICENSE
///

#pragma once

namespace lite {

inline int MemCmp (const void * left, const void * right, size_t bytes) {
    return std::memcmp(left, right, bytes);
}

inline void MemCopy (void * ptr, const void * src, size_t bytes) {
    std::memcpy(ptr, src, bytes);
}

inline void MemMove (void * ptr, const void * src, size_t bytes) {
    std::memmove(ptr, src, bytes);
}

inline void MemSet (void * ptr, size_t bytes, uint8_t value) {
    std::memset(ptr, value, bytes);
}

inline void MemZero (void * ptr, size_t bytes) {
    std::memset(ptr, 0, bytes);
}

} // namespace lite
