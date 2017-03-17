///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite)

// Thread
Thread::Thread (uint32_t stackSize, const char * name) {
    LITE_REF(stackSize, name);
}

Thread::~Thread () {
    WaitForExit();
}

bool Thread::WaitForExit () {
    if (!m_thr.joinable())
        return false;

    m_thr.join();
    return true;
}


// Exported
uint32_t ThreadGetCoreCount () {
#if LITE_OS_WINDOWS
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return uint32_t(sysinfo.dwNumberOfProcessors);
#else
#   error "not implemented"
#endif
}

uint32_t ThreadGetId () {
#if LITE_OS_WINDOWS
    return ::GetCurrentThreadId();
#else
#   error "not implemented"
#endif
}

void ThreadSleep (uint32_t timeMs) {
#if LITE_OS_WINDOWS
    ::Sleep(timeMs);
#else
#   error "not implemented"
#endif
}

void ThreadYield () {
#if LITE_OS_WINDOWS
    ::SwitchToThread();
#else
#   error "not implemented"
#endif
}

LITE_NAMESPACE_END(lite)
