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

// Enabled
namespace lite {
template<int VAL>
inline bool IsEnabled () {
    return true;
}
template<>
inline bool IsEnabled<0> () {
    return false;
}
} // lite

// Include macros first
#include <core/macros.h>

// The include everything else
#include <core/allocator.h>
#include <core/common_allocator.h>
#include <core/memory.h>
#include <core/types.h>
#include <core/atomic.h>
#include <core/spin_lock.h>
#include <core/thread.h>
