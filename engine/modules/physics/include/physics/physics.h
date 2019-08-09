///
/// LICENSE
///

#pragma once

namespace lite::physics {

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

enum class RigidBodyType : int32_t {
    Dynamic,
    Kinematic,
    Static,
};

struct RigidBodyParams {
    ///
    ShapePtr shape;

    ///
    Transform transform = { tag::Identity{} };

    ///
    Vec3f scale = { 1.0f };

    ///
    RigidBodyType type = RigidBodyType::Dynamic;

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
//    Queries
//
///////////////////////////////////////////////////////////

class AsyncResultHandle {
public:

    bool operator== (const AsyncResultHandle & rhs) const { return m_index == rhs.m_index && m_serial == rhs.m_serial; }
    bool operator!= (const AsyncResultHandle & rhs) const { return m_index != rhs.m_index || m_serial != rhs.m_serial; }

private:

    constexpr AsyncResultHandle (uint16_t index, uint16_t serial)
        : m_index(index)
        , m_serial(serial)
    {
    }

    AsyncResultHandle (tag::Uninitialized)
    {
    }

    /// 16 bit for the handle index value.
    uint16_t m_index;

    /// 16 bits for a unique serial number to disambiguate recycled indices.
    uint16_t m_serial;

    /// Gives exclusive access to the World without abstraction.
    friend class World;
};

enum class AsyncQueryResult {
    /// The query successfully hit and returned hit data.
    Success,

    /// The query failed to hit anything.
    Miss,

    /// The query isn't ready to fetch the results yet, try again later.
    NotReady,

    /// The handle is invalid.
    Invalid,
};

struct QueryParam {
    /// 1 << RigidBodyType
    uint32_t bodyTypeMask = UINT32_MAX;

    ///

};

struct RayCastHit {
    /// World space position of the hit
    Vec3f position{ tag::Uninitialized{} };

    /// World space surface normal of the hit
    Vec3f normal{ tag::Uninitialized{} };

    /// The body that was hit
    RigidBody * body;

    /// Fraction of the hit relative to the ray start/end positions
    float fraction;
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

    /// Advance the simulation and perform batched queries.
    void Step (float timeSecs);

public: // Object creation

    ///
    RigidBody * CreateRigidBody (const RigidBodyParams & params);
    void        DestroyRigidBody (RigidBody * ptr);

public: // Synchronous Queries

    /// RayCast and return the single closest hit.
    bool RayCastClosest (const QueryParam & param, const Vec3f & start, const Vec3f & end, RayCastHit & outHit) const;

    /// RayCast and return all hits.
    bool RayCastAll (const QueryParam & param, const Vec3f & start, const Vec3f & end, Array<RayCastHit> & outHits) const;

    /// RayCast many rays, returning all hits.
    /// Useful for rays in close proximity to each other.
    bool RayCastMany (const QueryParam & param, const ArrayView<const Vec3f> & start, const ArrayView<const Vec3f> & end, Array<RayCastHit> & outHits) const;

    /// RayCast many rays which all start from the same point.
    /// Example use case is audio occlusion culling from audio
    /// sources to the player.
    bool RayCastToMany (const QueryParam & param, const Vec3f & start, const ArrayView<const Vec3f> & end, Array<RayCastHit> & outHits) const;

public: // Asynchronous Queries

    /// RayCast and return the single closest hit.
    /// [Asynchronous] Get results with GetAsyncResult()
    AsyncResultHandle RayCastClosestAsync (const QueryParam & param, const Vec3f & start, const Vec3f & end);

    /// RayCast and return all hits.
    /// [Asynchronous] Get results with GetAsyncResults()
    AsyncResultHandle RayCastAllAsync (const QueryParam & param, const Vec3f & start, const Vec3f & end);

    /// RayCast many rays, returning all hits.
    /// Useful for rays in close proximity to each other.
    /// [Asynchronous] Get results with GetAsyncResults()
    AsyncResultHandle RayCastManyAsync (const QueryParam & param, const ArrayView<const Vec3f> & start, const ArrayView<const Vec3f> & end);

    /// RayCast many rays which all start from the same point.
    /// Example use case is audio occlusion culling from audio
    /// sources to the player.
    /// [Asynchronous] Get results with GetAsyncResults()
    AsyncResultHandle RayCastToManyAsync (const QueryParam & param, const Vec3f & start, const ArrayView<const Vec3f> & end);

    /// Get the result of the closest hit query or the first result of the all hits query.
    /// Clears the results buffer of this request internally.
    AsyncQueryResult GetAsyncResult (AsyncResultHandle handle, RayCastHit & outHit);

    /// Get the results of the all hits query.
    /// Clears the results buffer of this request internally.
    AsyncQueryResult GetAsyncResults (AsyncResultHandle handle, Array<RayCastHit> & outHits);

private:

    AsyncResultHandle AllocHandle_CS ();
    void ProcessQueryResults_CS (AsyncResultHandle handle, const ArrayView<RayCastHit> & hits);

    static constexpr AsyncResultHandle kInvalidAsyncHandle = { UINT16_MAX, UINT16_MAX };

    Array<RigidBody *> m_rigidBodies;

    using AsyncQueryFunc = std::function<void()>;
    using RayCastArray   = Array<RayCastHit>;
    struct AsyncResult {
        LITE_DECLARE_NOCOPY(AsyncResult);

        AsyncResult (AsyncResultHandle handle) : handle(handle) { }

        // Outputs

        RayCastArray      hits;
        AsyncResultHandle handle;
        bool              finished = false;

        // Inputs
        Array<Vec3f> startPts;
        Array<Vec3f> endPts;

        AsyncResult (AsyncResult && rhs) = default;
        AsyncResult & operator= (AsyncResult && rhs) = default;
    };

    Lock                     m_lock;
    Array<AsyncResult>       m_asyncResults;
    Array<AsyncQueryFunc>    m_asyncQueries;
    Array<AsyncResultHandle> m_freeHandles;

    const WorldParams m_params;
};

} // namespace lite::physics
