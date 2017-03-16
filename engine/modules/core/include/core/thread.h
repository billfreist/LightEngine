///
/// LICENSE
///

#pragma once

LITE_NAMESPACE_BEGIN(lite)

// Thread
typedef std::thread Thread;

// Lock
class Lock final : std::mutex {
public:

    void Enter () { std::mutex::lock(); }
    bool TryEnter () { std::mutex::try_lock(); }
    void Leave () { std::mutex::unlock(); }
};

// Exported
uint32_t ThreadGetCoreCount ();
uint32_t ThreadGetId ();
void     ThreadSleep (uint32_t timeMs);
void     ThreadYield ();

LITE_NAMESPACE_END(lite)
