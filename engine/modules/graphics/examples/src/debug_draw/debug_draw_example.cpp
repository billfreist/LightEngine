///
/// LICENSE
///

#include "pch.h"

#include <core/geometry.h>

LITE_NAMESPACE_BEGIN(lite, graphics, example)

class DebugDraw : public example_framework::ExampleBase {
public:

    DebugDraw () = default;
    ~DebugDraw () override = default;

    int Update () override;
};
LITE_EXAMPLE_DEFINITION(DebugDraw);

int DebugDraw::Update () {

    graphics::Scene * scene = GetRenderScene();
    IDebugDrawer * drawer = scene->GetDebugDrawer();
    drawer->Begin();
    drawer->DrawSphere({ Vec3f(0.0f), 1.0f });
    drawer->End();

    // Setup camera
    scene->SetCamera(Vec3f(0.0f, 10.0f, 10.0f), Vec3f(0.0f, 5.0f, 5.0f));

    return 0;
}

LITE_NAMESPACE_END(lite, graphics, example)
