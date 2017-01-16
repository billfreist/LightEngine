///
/// LICENSE
///

#pragma once

LITE_NAMESPACE_BEGIN(lite)

typedef std::thread Thread;


// Exported
uint32_t ThreadGetCoreCount ();
uint32_t ThreadGetId ();
void     ThreadSleep (uint32_t timeMs);
void     ThreadYield ();

LITE_NAMESPACE_END(lite)
