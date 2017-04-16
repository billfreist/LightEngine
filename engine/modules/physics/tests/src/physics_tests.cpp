///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, physics)

TEST(Physics, Init) {
    WorldParams params;
    World world(params);

    RigidBodyParams rbParams;
    rbParams.shape = ShapeGroundPlanePtr::New();
    RigidBody * groundPlaneBody = world.CreateRigidBody(rbParams);

    ShapeSpherePtr sphere(ShapeSpherePtr::New());
    sphere->localPos = 0.0f;
    sphere->radius   = 0.5f;
    rbParams.shape = sphere;
    rbParams.transform.SetPosition({ 0.0f, 1.0f, 0.0f });
    RigidBody * rb = world.CreateRigidBody(rbParams);
    world.DestroyRigidBody(rb);

    world.DestroyRigidBody(groundPlaneBody);
}

LITE_NAMESPACE_END(lite, physics)

int LiteMain (int argc, char ** argsv) {
    testing::InitGoogleTest(&argc, argsv);
    return RUN_ALL_TESTS();
}
