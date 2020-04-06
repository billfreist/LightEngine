///
/// LICENSE
///

#pragma once

#if LITE_OS_WINDOWS
#   define TRACY_ENABLE 1
#endif // LITE_OS_WINDOWS
#include "Tracy.hpp"

namespace lite {

#define PROFILER_SCOPE()           ZoneScoped
#define PROFILER_NAMED_SCOPE(name) ZoneScopedN(name)

#define PROFILER_TICK()            FrameMark

#define PROFILER_ALLOC(ptr, size)  TracyAlloc(ptr, size)
#define PROFILER_FREE(ptr)         TracyFree(ptr)

#define PROFILER_THREAD_NAME(name) tracy::SetThreadName(name)

//void ProfilerBegin(const char* name);
//void ProfilerEnd();

} // namespace lite

#include <core/inline/perf/profiler.inl>
