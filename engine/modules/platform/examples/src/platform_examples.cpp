///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, platform)

void TestCreateWindow () {
    Window * window = Application::Get()->CreateWindow();
    LITE_ASSERT(window);
    window->Close();
}

LITE_NAMESPACE_END(lite, platform)

int LiteMain (int argc, char ** argsv) {
    LITE_REF(argc, argsv);
    lite::platform::TestCreateWindow();
    return 0;
}
