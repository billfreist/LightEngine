///
/// LICENSE
///

#include "pch.h"

extern int LiteMain (int argc, char ** argsv);

LITE_NAMESPACE_BEGIN(lite, platform)

static Application * s_application;

Application * Application::Get () {
    LITE_ASSERT(s_application);
    return s_application;
}

uint32_t Application::ThreadProc (Application * thisPtr, int argc, char ** argsv) {
    s_application = thisPtr;
    thisPtr->m_exitCode = (uint32_t)LiteMain(argc, argsv);
    s_application = nullptr;
    return thisPtr->m_exitCode;
}

LITE_NAMESPACE_END(lite, platform)
