///
/// LICENSE
///

#include "pch.h"

namespace lite::physics {

///////////////////////////////////////////////////////////
//
//    Constants
//
///////////////////////////////////////////////////////////

static constexpr Vec3f kStartPts[] = {
    { 1.0f, 2.0f, 3.0f },
    { 2.0f, 3.0f, 4.0f },
    { 3.0f, 4.0f, 5.0f }
};
static constexpr Vec3f kEndPts[] = {
    { 3.0f, 2.0f, 1.0f },
    { 5.0f, 6.0f, 7.0f },
    { 8.0f, 9.0f, 10.0f }
};


///////////////////////////////////////////////////////////
//
//    Tests
//
///////////////////////////////////////////////////////////

TEST(Physics, Init) {
    WorldParams params;
    World world(params);

    RigidBodyParams rbParams;
    rbParams.type  = RigidBodyType::Static;
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

TEST(Physics, QuerySynchronous) {
    WorldParams params;
    World world(params);

    RigidBodyParams rbParams;
    rbParams.type  = RigidBodyType::Static;
    rbParams.shape = ShapeGroundPlanePtr::New();
    world.CreateRigidBody(rbParams);

    QueryParam param;
    param.bodyTypeMask = 1 << int32_t(RigidBodyType::Static);

    RayCastHit closest;
    if (world.RayCastClosest(param, { 1.0f, 2.0f, 3.0f }, { 3.0f, 2.0f, 1.0f }, closest)) {
        // Success
    }

    Array<RayCastHit> all;
    if (world.RayCastAll(param, { 1.0f, 2.0f, 3.0f }, { 3.0f, 2.0f, 1.0f }, all)) {
        // Success
    }

    Array<RayCastHit> many;
    if (world.RayCastMany(param, kStartPts, kEndPts, many)) {
        // Success
    }

    Array<RayCastHit> toMany;
    if (world.RayCastToMany(param, { 1.0f, 2.0f, 3.0f }, kEndPts, toMany)) {
        // Success
    }
}

TEST(Physics, QueryAsynchronous) {
    WorldParams params;
    World world(params);

    RigidBodyParams rbParams;
    rbParams.type  = RigidBodyType::Static;
    rbParams.shape = ShapeGroundPlanePtr::New();
    world.CreateRigidBody(rbParams);

    QueryParam param;
    param.bodyTypeMask = 1 << int32_t(RigidBodyType::Static);

    AsyncResultHandle closest = world.RayCastClosestAsync(param, { 1.0f, 2.0f, 3.0f }, { 3.0f, 2.0f, 1.0f });
    AsyncResultHandle all     = world.RayCastAllAsync(param, { 1.0f, 2.0f, 3.0f }, { 3.0f, 2.0f, 1.0f });
    AsyncResultHandle many    = world.RayCastManyAsync(param, kStartPts, kEndPts);
    AsyncResultHandle toMany  = world.RayCastToManyAsync(param, { 1.0f, 2.0f, 3.0f }, kEndPts);

    // Advance the simulation and perform queries
    world.Step(1.0f);

    // Fetch the query results
    RayCastHit closestResult;
    if (world.GetAsyncResult(closest, closestResult) == AsyncQueryResult::Success) {
        // Success
    }

    Array<RayCastHit> allResult;
    if (world.GetAsyncResults(all, allResult) == AsyncQueryResult::Success) {
        // Success
    }

    Array<RayCastHit> manyResult;
    if (world.GetAsyncResults(many, manyResult) == AsyncQueryResult::Success) {
        // Success
    }

    Array<RayCastHit> toManyResult;
    if (world.GetAsyncResults(toMany, toManyResult) == AsyncQueryResult::Success) {
        // Success
    }
}

} // namespace lite::physics

int LiteMain (int argc, char ** argsv) {
    testing::InitGoogleTest(&argc, argsv);
    return RUN_ALL_TESTS();
}
