///
/// LICENSE
///

#pragma once

#include <functional>
#include <mutex>
#include <thread>

namespace lite {

///////////////////////////////////////////////////////////
//
//    Thread
//
///////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////
//
//    Lock
//
///////////////////////////////////////////////////////////

class Lock final : std::mutex {
public:

    void Enter ()    { std::mutex::lock(); }
    bool TryEnter () { return std::mutex::try_lock(); }
    void Leave ()    { std::mutex::unlock(); }

public:

    class Scope {
    public:
        Scope (Lock & lock) : m_lock(&lock) { m_lock->Enter(); }
        Scope (Lock * lock) : m_lock(lock)  { m_lock->Enter(); }
        ~Scope ()                           { m_lock->Leave(); }
    private:
        Lock * m_lock;
    };
};
#define LITE_SCOPED_LOCK(lock) Lock::Scope LITE_CONCAT(_scopedLock, __LINE__)(lock)


///////////////////////////////////////////////////////////
//
//    Event
//
///////////////////////////////////////////////////////////

class Event final {
public:

    Event (bool manualReset = true);
    ~Event ();

    void Signal ();
    void Wait ();

private:

    void * m_data;
};


///////////////////////////////////////////////////////////
//
//    Exported
//
///////////////////////////////////////////////////////////

uint32_t ThreadGetCoreCount ();
uint32_t ThreadGetId ();
void     ThreadSleep (uint32_t timeMs);
void     ThreadYield ();

} // namespace lite
