
#pragma once

#ifdef LITE_CORE_H_INCLUDED
#error "ADLFKJSDF0"
#endif
#define LITE_CORE_H_INCLUDED

#ifndef LITE_MACROS_H_INCLUDED
#error "Must include Macros.h first"
#endif

#include <atomic>
#include <stdint.h>
#include <mutex>
#include <vector>
#include <thread>
#include <new>
#include <fstream>

#undef NULL
#define NULL nullptr

#include <core/types.h>
#include <core/allocator.h>
#include <core/common_allocator.h>
#include <core/atomic.h>
#include <core/memory.h>
#include <core/spin_lock.h>
#include <core/thread.h>

