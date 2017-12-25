///
/// LICENSE
///

#pragma once

namespace lite { namespace physics {

///////////////////////////////////////////////////////////
//
//    Shape
//
///////////////////////////////////////////////////////////

enum class ShapeType {
    ///
    kSphere,

    ///
    kGroundPlane,
};

struct Shape : RefCounted {
    ///
    const ShapeType type;

    virtual ~Shape () = default;

protected:

    Shape (ShapeType type) : type(type) { }
};
using ShapePtr = SharedPtr<const Shape>;

///
struct ShapeSphere final : Shape {
    ///
    Vec3f localPos;

    ///
    float radius;

    ShapeSphere () : Shape(ShapeType::kSphere) { }

private:
    ~ShapeSphere () = default;
};
using ShapeSpherePtr = SharedPtr<ShapeSphere>;

///
struct ShapeGroundPlane final : Shape {
    ShapeGroundPlane () : Shape(ShapeType::kGroundPlane) { }
private:
    ~ShapeGroundPlane () = default;
};
using ShapeGroundPlanePtr = SharedPtr<const ShapeGroundPlane>;


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
    ShapePtr shape;

    ///
    Transform transform = { tag::Identity{} };

    ///
    Vec3f scale = { 1.0f };

    ///
    RigidBodyFlags flags;
};

class RigidBody {
    LITE_DECLARE_NOCOPY(RigidBody);
public:

    RigidBody (const RigidBodyParams & params);
    ~RigidBody ();

private:

    ShapePtr       m_shape;
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
    LITE_DECLARE_NOCOPY(World);
public:

    World (const WorldParams & params);

    ///
    void Step (float timeSecs);

    ///
    RigidBody * CreateRigidBody (const RigidBodyParams & params);
    void        DestroyRigidBody (RigidBody * ptr);

private:

    Array<RigidBody *> m_rigidBodies;

    const WorldParams m_params;
};

}} // namespace lite::physics
