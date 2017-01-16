///
/// LICENSE
///

#pragma once

LITE_NAMESPACE_BEGIN(lite)

int  MemCmp (const void * left, const void * right, size_t size);
void MemCopy (void * ptr, const void * src, size_t bytes);
bool MemIsZero (const void * mem, size_t size);
void MemMove (void * ptr, const void * src, size_t bytes);
void MemSet (void * ptr, size_t bytes, uint8_t v);
void MemZero (void * ptr, size_t bytes);

LITE_NAMESPACE_END(lite)
