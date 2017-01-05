#include "core_pch.h"


namespace lite {

// Exported
uint32_t ThreadGetCoreCount () {
#if LITE_OS_WINDOWS
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return uint32_t(sysinfo.dwNumberOfProcessors);
#else
#error "not implemented"
#endif
}

uint32_t ThreadGetId () {
#if LITE_OS_WINDOWS
    return ::GetCurrentThreadId();
#else
#error "not implemented"
#endif
}

void ThreadSleep (uint32_t timeMs) {
#if LITE_OS_WINDOWS
    ::Sleep(timeMs);
#else
#error "not implemented"
#endif
}

void ThreadYield () {
#if LITE_OS_WINDOWS
    ::SwitchToThread();
#else
#error "not implemented"
#endif
}

} // common
