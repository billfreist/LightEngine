///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, graphics)

void InitTest () {
    graphics::Scene scene;
    scene.Render();
}

LITE_NAMESPACE_END(lite, graphics)

int main () {
    lite::graphics::InitTest();
    return 0;
}
