///
/// LICENSE
///

#pragma once

#include <core/geometry.h>

LITE_NAMESPACE_BEGIN(lite)

///////////////////////////////////////////////////////////
//
//    IDebugDrawer
//
///////////////////////////////////////////////////////////

interface IDebugDrawer {

    ///
    virtual void Begin (uint8_t view) = 0;
    virtual void End () = 0;

    ///
    virtual void MoveTo (const Vec3f & pos) = 0;
    virtual void LineTo (const Vec3f & pos) = 0;
    virtual void Close () = 0;

    ///
    virtual void DrawSphere (const Vec3f & center, float radius) = 0;
    virtual void DrawSphere (const Sphere & sphere) = 0;
};

LITE_NAMESPACE_END(lite)
