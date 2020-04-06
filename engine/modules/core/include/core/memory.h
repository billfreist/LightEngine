///
/// LICENSE
///

#pragma once

#ifndef LITE_CORE_H_INCLUDED
#   error "Must be included through core.h"
#endif // LITE_CORE_H_INCLUDED

namespace lite {

int  MemCmp (const void * left, const void * right, size_t bytes);
void MemCopy (void * ptr, const void * src, size_t bytes);
bool MemIsZero (const void * mem, size_t bytes);
void MemMove (void * ptr, const void * src, size_t bytes);
void MemSet (void * ptr, size_t bytes, uint8_t value);
void MemZero (void * ptr, size_t bytes);

} // namespace lite

#include <core/inline/memory.inl>
