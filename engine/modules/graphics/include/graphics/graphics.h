///
/// LICENSE
///

#pragma once

#include <core/debug_drawer.h>

LITE_NAMESPACE_BEGIN(lite, graphics)

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

    const Params m_params;
    uint16_t     m_frameBuffer;
    View         m_view;
};

LITE_NAMESPACE_END(lite, graphics)
