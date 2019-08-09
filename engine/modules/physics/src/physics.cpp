///
/// LICENSE
///

#include "pch.h"

namespace lite::physics {

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

    // Process async queries, ideally this would be done in a separate thread/task/job
    for (AsyncQueryFunc func : m_asyncQueries) {
        func();
    }
    m_asyncQueries.Reset();
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

bool World::RayCastClosest (
    const QueryParam & param,
    const Vec3f &      start,
    const Vec3f &      end,
    RayCastHit &       outHit
) const {
    LITE_REF(param, start, end, outHit);
    return false;
}

bool World::RayCastAll (
    const QueryParam &  param,
    const Vec3f &       start,
    const Vec3f &       end,
    Array<RayCastHit> & outHits
) const {
    LITE_REF(param, start, end, outHits);
    return false;
}

bool World::RayCastMany (
    const QueryParam &             param,
    const ArrayView<const Vec3f> & start,
    const ArrayView<const Vec3f> & end,
    Array<RayCastHit> &            outHits
) const {
    LITE_REF(param, start, end, outHits);
    LITE_ASSERT(start.GetCount() > 0 && end.GetCount() > 0);
    if (start.GetCount() == 1) {
        if (end.GetCount() == 1) {
            return RayCastAll(param, start[0], end[0], outHits);
        }
        else {
            return RayCastToMany(param, start[0], end, outHits);
        }
    }
    return false;
}

bool World::RayCastToMany (
    const QueryParam &             param,
    const Vec3f &                  start,
    const ArrayView<const Vec3f> & end,
    Array<RayCastHit> &            outHits
) const {
    LITE_REF(param, start, end, outHits);
    LITE_ASSERT(end.GetCount() > 0);
    if (end.GetCount() == 1) {
        return RayCastAll(param, start, end[0], outHits);
    }
    return false;
}

AsyncResultHandle World::RayCastClosestAsync (
    const QueryParam & param,
    const Vec3f &      start,
    const Vec3f &      end
) {
    LITE_REF(param, start, end);
    LITE_SCOPED_LOCK(m_lock);
    AsyncResultHandle handle = AllocHandle_CS();

    // Capture the stack by copy, we will execute this lambda later.
    m_asyncQueries.Add([this, param, start, end, handle]() {
        RayCastHit hit;
        if (RayCastClosest(param, start, end, hit)) {
            LITE_SCOPED_LOCK(m_lock);
            AsyncResult & result = m_asyncResults[handle.m_index];
            LITE_ASSERT(result.handle == handle);
            result.hits.Add(hit);
            result.finished = true;
        }
        else {
            LITE_SCOPED_LOCK(m_lock);
            AsyncResult & result = m_asyncResults[handle.m_index];
            LITE_ASSERT(result.handle == handle);
            result.finished = true;
        }
    });

    return handle;
}

AsyncResultHandle World::RayCastAllAsync (
    const QueryParam & param,
    const Vec3f &      start,
    const Vec3f &      end
) {
    LITE_REF(param, start, end);
    AsyncResultHandle handle = AllocHandle_CS();

    // Capture the stack by copy, we will execute this lambda later.
    m_asyncQueries.Add([this, param, start, end, handle]() {
        RayCastArray hits;
        {
            LITE_SCOPED_LOCK(m_lock);
            AsyncResult & result = m_asyncResults[handle.m_index];
            LITE_ASSERT(result.handle == handle);
            hits = std::move(result.hits); // grab the preexisting results array to reuse the memory
        }
        RayCastAll(param, start, end, hits);
        LITE_SCOPED_LOCK(m_lock);
        AsyncResult & result = m_asyncResults[handle.m_index];
        LITE_ASSERT(result.handle == handle);
        result.hits = std::move(hits); // move the memory back, regardless of the results
        result.finished = true;
    });

    return handle;
}

AsyncResultHandle World::RayCastManyAsync (
    const QueryParam &             param,
    const ArrayView<const Vec3f> & start,
    const ArrayView<const Vec3f> & end
) {
    LITE_REF(param, start, end);
    LITE_ASSERT(start.GetCount() > 0 && end.GetCount() > 0);
    if (start.GetCount() == 1 && end.GetCount() == 1) {
        return RayCastAllAsync(param, start[0], end[0]);
    }

    LITE_SCOPED_LOCK(m_lock);
    AsyncResultHandle handle = AllocHandle_CS();
    AsyncResult &     result = m_asyncResults[handle.m_index];
    result.startPts = start;
    result.endPts   = end;

    // Capture the stack by copy, we will execute this lambda later.
    m_asyncQueries.Add([this, param, handle]() {
        RayCastArray hits;
        Array<Vec3f> start, end;
        {
            LITE_SCOPED_LOCK(m_lock);
            AsyncResult & result = m_asyncResults[handle.m_index];
            LITE_ASSERT(result.handle == handle);

            // grab the preexisting results array to reuse the memory
            hits  = std::move(result.hits);
            start = std::move(result.startPts);
            end   = std::move(result.endPts);
        }
        RayCastMany(param, start, end, hits);
        LITE_SCOPED_LOCK(m_lock);
        AsyncResult & result = m_asyncResults[handle.m_index];
        LITE_ASSERT(result.handle == handle);
        // move the memory back, regardless of the results
        result.hits     = std::move(hits);
        result.startPts = std::move(start);
        result.endPts   = std::move(end);
        result.finished = true;
    });

    return handle;
}

AsyncResultHandle World::RayCastToManyAsync (
    const QueryParam &             param,
    const Vec3f &                  start,
    const ArrayView<const Vec3f> & end
) {
    LITE_REF(param, start, end);
    LITE_ASSERT(end.GetCount() > 0);
    if (end.GetCount() == 1) {
        return RayCastAllAsync(param, start, end[0]);
    }
    else {
        return RayCastManyAsync(param, ArrayView<const Vec3f>(1, &start), end);
    }
}

AsyncQueryResult World::GetAsyncResult (
    AsyncResultHandle handle,
    RayCastHit &      outHit
) {
    LITE_SCOPED_LOCK(m_lock);
    if (handle.m_index >= m_asyncResults.GetCount())
        return AsyncQueryResult::Invalid;

    AsyncResult & result = m_asyncResults[handle.m_index];
    if (result.handle != handle)
        return AsyncQueryResult::Invalid;

    if (result.hits.GetCount()) {
        outHit = std::move(result.hits[0]);
        result.hits.Reset();
        result.handle   = kInvalidAsyncHandle;
        result.finished = false;
        m_freeHandles.Add(handle);
        return AsyncQueryResult::Success;
    }
    else if (result.finished) {
        result.handle   = kInvalidAsyncHandle;
        result.finished = false;
        m_freeHandles.Add(handle);
        return AsyncQueryResult::Miss;
    }
    else {
        return AsyncQueryResult::NotReady;
    }
}

AsyncQueryResult World::GetAsyncResults (
    AsyncResultHandle   handle,
    Array<RayCastHit> & outHits
) {
    LITE_SCOPED_LOCK(m_lock);
    if (handle.m_index >= m_asyncResults.GetCount())
        return AsyncQueryResult::Invalid;

    AsyncResult & result = m_asyncResults[handle.m_index];
    if (result.handle != handle)
        return AsyncQueryResult::Invalid;

    if (result.hits.GetCount()) {
        outHits = result.hits;
        result.hits.Reset();
        result.handle   = kInvalidAsyncHandle;
        result.finished = false;
        m_freeHandles.Add(handle);
        return AsyncQueryResult::Success;
    }
    else if (result.finished) {
        result.handle   = kInvalidAsyncHandle;
        result.finished = false;
        m_freeHandles.Add(handle);
        return AsyncQueryResult::Miss;
    }
    else {
        return AsyncQueryResult::NotReady;
    }
}

AsyncResultHandle World::AllocHandle_CS () {
    AsyncResultHandle handle(tag::Uninitialized{});
    if (m_freeHandles.GetCount()) {
        handle = m_freeHandles.Pop();
    }
    else {
        LITE_ASSERT(m_asyncResults.GetCount() + 1 < UINT16_MAX);
        handle = AsyncResultHandle{ (uint16_t)m_asyncResults.GetCount(), 0 };
        m_asyncResults.Add(handle);
    }

    // Increment the serial number
    ++handle.m_serial;
    m_asyncResults[handle.m_index].handle = handle;

    return handle;
}

void World::ProcessQueryResults_CS (
    AsyncResultHandle             handle,
    const ArrayView<RayCastHit> & hits
) {
    AsyncResult & result = m_asyncResults[handle.m_index];
    LITE_ASSERT(result.handle == handle);
    result.hits = hits;
}

} // namespace lite::physics
