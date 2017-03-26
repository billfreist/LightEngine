///
/// LICENSE
///

#include <core/core.h>

#include <platform/platform.h>

#if LITE_OS_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   include <windows.h>

// Windows impl
#   include "windows/windows_input.h"
#   include "windows/windows_window.h"
#endif
