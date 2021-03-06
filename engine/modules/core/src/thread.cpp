///
/// LICENSE
///

#include "pch.h"

#include <core/thread.h>
#include <core/perf/profiler.h>

namespace lite {

///////////////////////////////////////////////////////////
//
//    Thread
//
///////////////////////////////////////////////////////////

Thread::Thread (uint32_t stackSize, const char * name) {
    LITE_REF(stackSize, name);
    //PROFILER_THREAD_NAME(name);
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


///////////////////////////////////////////////////////////
//
//    Event
//
///////////////////////////////////////////////////////////

Event::Event (bool manualReset) {
#if LITE_OS_WINDOWS
    m_data = ::CreateEventA(
        nullptr,     // attributes
        manualReset,
        false,       // initialState
        nullptr      // name
    );
#else
#   error "not implemented"
#endif
}

Event::~Event () {
#if LITE_OS_WINDOWS
    ::CloseHandle(m_data);
#else
#   error "not implemented"
#endif
}

void Event::Signal () {
#if LITE_OS_WINDOWS
    ::SetEvent(m_data);
#else
#   error "not implemented"
#endif
}

void Event::Wait () {
#if LITE_OS_WINDOWS
    ::WaitForSingleObject(m_data, INFINITE);
#else
#   error "not implemented"
#endif
}

} // namespace lite
