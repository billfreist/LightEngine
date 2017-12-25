///
/// LICENSE
///

#include "pch.h"

namespace lite { namespace platform {

void TestCreateWindow () {
    WindowPtr window = Application::Get()->CreateWindow();
    LITE_ASSERT(window);
    for (;;) {
        ThreadSleep(16);
        if (window->IsClosed())
            break;
    }
}

}} // namespace lite::platform

int LiteMain (int argc, char ** argsv) {
    LITE_REF(argc, argsv);
    lite::platform::TestCreateWindow();
    return 0;
}
