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
    virtual void Begin () = 0;
    virtual void End () = 0;

    ///
    virtual void MoveTo (const Vec3f & pos) = 0;
    virtual void LineTo (const Vec3f & pos) = 0;
    virtual void Close () = 0;

    ///
    virtual void DrawSphere (const lite::Sphere & sphere) = 0;
};

LITE_NAMESPACE_END(lite)
