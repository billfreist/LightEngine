///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, graphics)

TEST(Graphics, Init) {
    graphics::Scene scene;
    scene.Render();
}

LITE_NAMESPACE_END(lite, graphics)

int LiteMain (int argc, char ** argsv) {
    testing::InitGoogleTest(&argc, argsv);
    return RUN_ALL_TESTS();
}
