///
/// LICENSE
///

#pragma once

#include <functional>

LITE_NAMESPACE_BEGIN(lite)

// Thread
class Thread : std::thread {
public:

    Thread (uint32_t stackSize, const char * name);
    ~Thread ();

    bool WaitForExit ();

    template<class Func, typename... Args>
    void Launch (Func && func, Args&&... args) {
        m_thr = std::thread { std::forward<Func>(func), std::forward<Args>(args)... };
    }

private:

    std::thread m_thr;
};

// Lock
class Lock final : std::mutex {
public:

    void Enter ()    { std::mutex::lock(); }
    bool TryEnter () { std::mutex::try_lock(); }
    void Leave ()    { std::mutex::unlock(); }
};

// Exported
uint32_t ThreadGetCoreCount ();
uint32_t ThreadGetId ();
void     ThreadSleep (uint32_t timeMs);
void     ThreadYield ();

LITE_NAMESPACE_END(lite)
