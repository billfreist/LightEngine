///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, platform)

void TestCreateWindow () {
    WindowPtr window = Application::Get()->CreateWindow();
    LITE_ASSERT(window);
    for (;;) {
        ThreadSleep(16);
        if (window->IsClosed())
            break;
    }
}

LITE_NAMESPACE_END(lite, platform)

int LiteMain (int argc, char ** argsv) {
    LITE_REF(argc, argsv);
    lite::platform::TestCreateWindow();
    return 0;
}
