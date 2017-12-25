///
/// LICENSE
///

#include "pch.h"

#include <bx/allocator.h>
#include <bx/math.h>
#include <common/debugdraw/debugdraw.h>
#include <bgfx/platform.h>

namespace lite { namespace graphics {

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

    RenderContext (const bgfx::PlatformData & data);
    ~RenderContext ();

    View AllocView () { return m_viewPool++; }

private:

    View m_viewPool = UINT8_C(0);
};
static ExplicitConstructor<RenderContext> s_context;

RenderContext::RenderContext (const bgfx::PlatformData & data) {
    bgfx::setPlatformData(data);
    const bool initialized = bgfx::init(
        data.nwh ? bgfx::RendererType::Count : bgfx::RendererType::Noop,
        BGFX_PCI_ID_NONE,
        0, // deviceId
        nullptr,
        &s_allocator
    );
    LITE_ASSERT(initialized);
    bgfx::reset(1280, 720, BGFX_RESET_VSYNC);

    // Initialize debug draw
    ddInit(true, &s_allocator);

    // Initialize debugging
    bgfx::setDebug(BGFX_DEBUG_TEXT);
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
public:

    void SetView (View view) { m_view = view; }

public: // IDebugDrawer

    void Begin () override;
    void End () override;

    void MoveTo (const Vec3f & pos) override;
    void LineTo (const Vec3f & pos) override;
    void Close () override;

    void DrawSphere (const Sphere & sphere) override;

private:

    View m_view = 0;
};

void DebugDraw::Begin () {
    ddBegin(m_view);
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

void DebugDraw::DrawSphere (const Sphere & sphere) {
    LITE_REF(sphere);
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

Scene::Scene (const Params & params) : m_params(params) {
    if (!s_sceneCount++) {
        bgfx::PlatformData platformData;
        MemZero(&platformData, sizeof(platformData));
        platformData.nwh = m_params.windowHandle;
        s_context.Init(platformData);
    }
    m_view = s_context->AllocView();
    m_frameBuffer = bgfx::createFrameBuffer(m_params.windowHandle, 1280, 720).idx;
    bgfx::resetView(m_view);
}

Scene::~Scene () {
    bgfx::destroy(bgfx::FrameBufferHandle{ m_frameBuffer });
    if (!--s_sceneCount)
        s_context.Destroy();
}

void Scene::Render () {
    // Ensure we are rendering to our current window
    bgfx::PlatformData platformData;
    MemZero(&platformData, sizeof(platformData));
    platformData.nwh = m_params.windowHandle;
    bgfx::setPlatformData(platformData);

    // Clear the view
    bgfx::setViewClear(m_view, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030FF);

    // Ensure the view clears
    bgfx::touch(m_view);

    // Now advance the frame
    bgfx::frame();
}

IDebugDrawer * Scene::GetDebugDrawer () {
    static DebugDraw s_debugDraw;
    s_debugDraw.SetView(m_view);
    return &s_debugDraw;
}

void Scene::SetCamera (const Vec3f & eye, const Vec3f & target) {
    bgfx::setViewRect(m_view, 0, 0, 1280, 720);

    float viewMtx[16];
    bx::mtxLookAt(viewMtx, &eye.x, &target.x);

    float projMtx[16];
    bx::mtxProj(projMtx, 45.0f, 1280.0f / 720.0f, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

    bgfx::setViewTransform(m_view, viewMtx, projMtx);
}

}} // namespace lite::graphics
