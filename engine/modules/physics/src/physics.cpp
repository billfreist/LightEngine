///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, physics)

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

RigidBody * World::CreateRigidBody (const RigidBodyParams & params) {
    return LITE_NEW(RigidBody)(params);
}

void World::DestroyRigidBody (RigidBody * ptr) {
    LITE_DEL(ptr);
}

LITE_NAMESPACE_END(lite, physics)
