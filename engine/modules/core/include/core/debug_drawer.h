///
/// LICENSE
///

#pragma once

#include <core/geometry.h>

namespace lite {

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
    virtual void DrawSphere (const Sphere & sphere) = 0;
};

} // namespace lite
