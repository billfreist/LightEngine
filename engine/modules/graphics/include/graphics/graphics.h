///
/// LICENSE
///

#pragma once

#include <core/debug_drawer.h>

namespace lite::graphics {

///////////////////////////////////////////////////////////
//
//    View
//
///////////////////////////////////////////////////////////

using View = uint8_t;


///////////////////////////////////////////////////////////
//
//    Scene
//
///////////////////////////////////////////////////////////

class Scene {
public:

    struct Params {
        ///
        void * windowHandle = nullptr;
    };

    Scene (const Params & params);
    ~Scene ();

    ///
    void Render ();

    ///
    IDebugDrawer * GetDebugDrawer ();

    ///
    void SetCamera (const Vec3f & eye, const Vec3f & target);

private:

    const Params      m_params;
    class DebugDraw * m_debugDraw;
    View              m_view;
};

} // namespace lite::graphics
