#pragma once

namespace lite {

typedef std::thread Thread;


// Exported
uint32_t ThreadGetCoreCount ();
uint32_t ThreadGetId ();
void     ThreadSleep (uint32_t timeMs);
void     ThreadYield ();

} // common