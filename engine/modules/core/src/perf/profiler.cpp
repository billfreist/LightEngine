///
/// LICENSE
///

#include "pch.h"

#include <core/perf/profiler.h>

namespace lite {

void ProfilerBegin (const char * name) {
    LITE_REF(name);
}

void ProfilerEnd () {

}

} // namespace lite

// Tracy client integration
#pragma warning(push, 3)
#pragma warning(disable: 4005) // macro redefinition
#   include <TracyClient.cpp>
#pragma warning(pop)
