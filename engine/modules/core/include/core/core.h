///
/// LICENSE
///

#pragma once

#ifdef LITE_CORE_H_INCLUDED
#   error "Cannot include core.h more than once"
#endif
#define LITE_CORE_H_INCLUDED

#include <stdint.h>
#include <new>
#include <memory>
#include <functional>
#include <fstream>
#include <type_traits>

// Include macros first
#include <core/macros.h>

// Then include everything else
#include <core/tags.h>
#include <core/allocator.h>
#include <core/common_allocator.h>
#include <core/memory.h>
#include <core/ptr.h>

