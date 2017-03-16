///
/// LICENSE
///

#pragma once

LITE_NAMESPACE_BEGIN(lite, physics)

///////////////////////////////////////////////////////////
//
//    Shape
//
///////////////////////////////////////////////////////////

enum class ShapeType {
    ///
    kSphere,
};

struct Shape {
    ///
    const ShapeType type;

protected:

    Shape (ShapeType type) : type(type) { }
};

struct SphereShape : Shape {
    ///
    Vec3f localPos;

    ///
    float radius;

    SphereShape () : Shape(ShapeType::kSphere) { }
};


///////////////////////////////////////////////////////////
//
//    RigidBody
//
///////////////////////////////////////////////////////////

enum class RigidBodyFlag : uint32_t {
};
LITE_DEFINE_ENUM_BIT_OPERATORS(RigidBodyFlag);
using RigidBodyFlags = Flags<RigidBodyFlag>;

struct RigidBodyParams {
    ///
    Shape * shape = nullptr;

    ///
    Transform transform = { Identity::kTag };

    ///
    Vec3f scale = { 0.0f, 0.0f, 0.0f };

    ///
    RigidBodyFlags flags;
};

class RigidBody {
public:

    RigidBody (const RigidBodyParams & params);

private:

    RigidBodyFlags m_flags;
};


///////////////////////////////////////////////////////////
//
//    World
//
///////////////////////////////////////////////////////////

struct WorldParams {
    ///
    Vec3f gravity = { 0.0f, -9.81f, 0.0f };

    ///
};

class World {
public:

    World (const WorldParams & params);

private:

    const WorldParams m_params;
};

LITE_NAMESPACE_END(lite, physics)
