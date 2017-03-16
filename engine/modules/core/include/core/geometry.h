///
/// LICENSE
///

#pragma once

LITE_NAMESPACE_BEGIN(lite)

struct Sphere {
    ///
    Vec3f center;

    ///
    float radius;
};

struct Box {
    ///
    Transform transform{ tag::Uninitialized{} };

    ///
    Vec3f halfDims;
};

LITE_NAMESPACE_END(lite)
