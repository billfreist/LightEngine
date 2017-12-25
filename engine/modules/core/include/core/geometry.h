///
/// LICENSE
///

#pragma once

namespace lite {

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

} // namespace lite
