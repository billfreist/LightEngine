///
/// LICENSE
///

#include "graphics_pch.h"

#include <bx/allocator.h>
#include <common/debugdraw/debugdraw.h>

LITE_NAMESPACE_BEGIN(lite, graphics)

class BgfxAllocator : public bx::AllocatorI {
public:

    void * realloc (void * _ptr, size_t _size, size_t _align, const char * _file, uint32_t _line) override;
};

void * BgfxAllocator::realloc (void * _ptr, size_t _size, size_t _align, const char * _file, uint32_t _line) {
    LITE_REF(_file, _line);
    if (_ptr) {
        if (_size) { // Realloc
            if (_align)
                return LITE_ALIGNED_REALLOC(_ptr, _size, _align);
            else
                return LITE_REALLOC(_ptr, _size);
        }
        else { // Free
            if (_align)
                LITE_ALIGNED_FREE(_ptr, _align);
            else
                LITE_FREE(_ptr);
            return nullptr;
        }
    }
    else { // Alloc
        if (_align)
            return LITE_ALIGNED_ALLOC(_size, _align);
        else
            return LITE_ALLOC(_size);
    }
}
static BgfxAllocator s_allocator;


///////////////////////////////////////////////////////////
//
//    RenderContext
//
///////////////////////////////////////////////////////////

class RenderContext {
public:

    RenderContext ();
    ~RenderContext ();

    View AllocView () { return m_viewPool++; }

private:

    View m_viewPool = UINT8_C(0);
};
static ExplicitConstructor<RenderContext> s_context;

RenderContext::RenderContext () {
    const bool initialized = bgfx::init(
        bgfx::RendererType::Noop,
        BGFX_PCI_ID_NONE,
        0, // deviceId
        nullptr,
        &s_allocator
    );
    LITE_ASSERT(initialized);
    bgfx::reset(1280, 720, BGFX_RESET_VSYNC);

    // Initialize debug draw
    ddInit(true, &s_allocator);
}

RenderContext::~RenderContext () {
    // Shutdown debug drawing first
    ddShutdown();

    // Then the bgfx system
    bgfx::shutdown();
}


///////////////////////////////////////////////////////////
//
//    DebugDraw
//
///////////////////////////////////////////////////////////

class DebugDraw : public IDebugDrawer {
public: // IDebugDrawer

    void Begin (uint8_t view) override;
    void End () override;

    void MoveTo (const Vec3f & pos) override;
    void LineTo (const Vec3f & pos) override;
    void Close () override;

    void DrawSphere (const Vec3f & center, float radius) override;
    void DrawSphere (const Sphere & sphere) override;
};
static DebugDraw s_debugDraw;

void DebugDraw::Begin (uint8_t view) {
    ddBegin(view);
}

void DebugDraw::End () {
    ddEnd();
}

void DebugDraw::MoveTo (const Vec3f & pos) {
    ddMoveTo(&pos);
}

void DebugDraw::LineTo (const Vec3f & pos) {
    ddLineTo(&pos);
}

void DebugDraw::Close () {
    ddClose();
}

void DebugDraw::DrawSphere (const Vec3f & center, float radius) {
    ::Sphere _sphere;
    MemCopy(&_sphere.m_center, &center, sizeof(center));
    _sphere.m_radius = radius;
    ddDraw(_sphere);
}

void DebugDraw::DrawSphere (const Sphere & sphere) {
    ::Sphere _sphere;
    MemCopy(&_sphere.m_center, &sphere.center, sizeof(sphere.center));
    _sphere.m_radius = sphere.radius;
    ddDraw(_sphere);
}


///////////////////////////////////////////////////////////
//
//    Scene
//
///////////////////////////////////////////////////////////

static uint32_t s_sceneCount = 0;

Scene::Scene () {
    if (!s_sceneCount++)
        s_context.Init();
    m_view = s_context->AllocView();
    bgfx::resetView(m_view);
}

Scene::~Scene () {
    if (!--s_sceneCount)
        s_context.Destroy();
}

void Scene::Render () {
    bgfx::setViewClear(m_view, BGFX_CLEAR_NONE);

    bgfx::frame();
}


///////////////////////////////////////////////////////////
//
//    Exported
//
///////////////////////////////////////////////////////////

IDebugDrawer * GetDebugDrawer () {
    return &s_debugDraw;
}
LITE_NAMESPACE_END(lite, graphics)
