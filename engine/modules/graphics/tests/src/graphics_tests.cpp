///
/// LICENSE
///

#include "pch.h"

namespace lite::graphics {

TEST(Graphics, Init) {
    graphics::Scene scene({});
    scene.Render();
}

} // namespace lite::graphics

int LiteMain (int argc, char ** argsv) {
    testing::InitGoogleTest(&argc, argsv);
    return RUN_ALL_TESTS();
}
