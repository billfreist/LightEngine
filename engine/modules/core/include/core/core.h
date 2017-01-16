///
/// LICENSE
///

#pragma once

#ifdef LITE_CORE_H_INCLUDED
#   error "Cannot include core.h more than once"
#endif
#define LITE_CORE_H_INCLUDED

#include <atomic>
#include <stdint.h>
#include <mutex>
#include <vector>
#include <thread>
#include <new>
#include <fstream>

#undef NULL
#define NULL nullptr

#include <core/macros.h>

// Enabled
LITE_NAMESPACE_BEGIN(lite)
template<int VAL>
inline bool IsEnabled () {
    return true;
}
template<>
inline bool IsEnabled<0> () {
    return false;
}
LITE_NAMESPACE_END(lite)

#include <core/types.h>
#include <core/allocator.h>
#include <core/common_allocator.h>
#include <core/atomic.h>
#include <core/memory.h>
#include <core/spin_lock.h>
#include <core/thread.h>

