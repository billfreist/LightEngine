///
/// LICENSE
///

#include "pch.h"

namespace lite { namespace physics {

///////////////////////////////////////////////////////////
//
//    RigidBody
//
///////////////////////////////////////////////////////////

RigidBody::RigidBody (const RigidBodyParams & params)
    : m_shape(params.shape)
    , m_flags(params.flags)
{
    LITE_ASSERT(m_shape);
}

RigidBody::~RigidBody () {
    m_shape = nullptr;
}


///////////////////////////////////////////////////////////
//
//    World
//
///////////////////////////////////////////////////////////

World::World (const WorldParams & params)
    : m_params(params)
{

}

void World::Step (float timeSecs) {
    LITE_REF(timeSecs);
    for (RigidBody * ptr : m_rigidBodies) {
        LITE_REF(ptr);
    }
}

RigidBody * World::CreateRigidBody (const RigidBodyParams & params) {
    RigidBody * ptr = LITE_NEW(RigidBody)(params);
    m_rigidBodies.Add(ptr);
    return ptr;
}

void World::DestroyRigidBody (RigidBody * ptr) {
    m_rigidBodies.RemoveValueOrdered(ptr);
    LITE_DEL(ptr);
}

}} // namespace lite::physics
