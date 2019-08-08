///
/// LICENSE
///

#include "pch.h"

#include <bx/allocator.h>
#include <bx/math.h>
#include <common/debugdraw/debugdraw.h>
#include <bgfx/platform.h>

namespace lite::graphics {

///////////////////////////////////////////////////////////
//
//    BgfxAllocator
//
///////////////////////////////////////////////////////////

class BgfxAllocator final : public bx::AllocatorI {
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
//    BgfxCallback
//
///////////////////////////////////////////////////////////

class BgfxCallback final : public bgfx::CallbackI {
    void fatal(
        const char* _filePath
        , uint16_t _line
        , bgfx::Fatal::Enum _code
        , const char* _str
    ) override {
        LITE_REF(_filePath, _line, _code, _str);
        LITE_ASSERT(false);
    }

    void traceVargs(
        const char* _filePath
        , uint16_t _line
        , const char* _format
        , va_list _argList
    ) override {
        LITE_REF(_filePath, _line, _format, _argList);
    }

    void profilerBegin(
        const char* _name
        , uint32_t _abgr
        , const char* _filePath
        , uint16_t _line
    ) override {
        LITE_REF(_name, _abgr, _filePath, _line);
    }

    void profilerBeginLiteral(
        const char* _name
        , uint32_t _abgr
        , const char* _filePath
        , uint16_t _line
    ) override {
        LITE_REF(_name, _abgr, _filePath, _line);
    }

    void profilerEnd() override {

    }

    uint32_t cacheReadSize(uint64_t _id) override {
        LITE_REF(_id);
        return 0;
    }

    bool cacheRead(uint64_t _id, void* _data, uint32_t _size) override {
        LITE_REF(_id, _data, _size);
        return false;
    }

    void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) override {
        LITE_REF(_id, _data, _size);
    }

    void screenShot(
        const char* _filePath
        , uint32_t _width
        , uint32_t _height
        , uint32_t _pitch
        , const void* _data
        , uint32_t _size
        , bool _yflip
    ) override {
        LITE_REF(_filePath, _width, _height, _pitch, _data, _size, _yflip);
    }

    void captureBegin(
        uint32_t _width
        , uint32_t _height
        , uint32_t _pitch
        , bgfx::TextureFormat::Enum _format
        , bool _yflip
    ) override {
        LITE_REF(_width, _height, _pitch, _format, _yflip);
    }

    void captureEnd() override {

    }

    void captureFrame(const void* _data, uint32_t _size) override {
        LITE_REF(_data, _size);
    }
};
static BgfxCallback s_callback;


///////////////////////////////////////////////////////////
//
//    RenderContext
//
///////////////////////////////////////////////////////////

class RenderContext {
public:

    RenderContext (const Scene::Params & params);
    ~RenderContext ();

    View AllocView () { return m_viewPool++; }

private:

    View m_viewPool = 0;
};
static ExplicitConstructor<RenderContext> s_context;

RenderContext::RenderContext (const Scene::Params & params) {
    bgfx::Init init;
    init.type      = params.windowHandle ? bgfx::RendererType::Count : bgfx::RendererType::Noop;
    init.vendorId  = BGFX_PCI_ID_NONE;
    init.deviceId  = 0;
    init.allocator = &s_allocator;
    init.callback  = &s_callback;
    init.debug     = false;
    init.profile   = false;
    init.platformData.nwh = params.windowHandle;
    init.resolution.maxFrameLatency = 1;
    init.resolution.width           = 1280;
    init.resolution.height          = 720;
    init.resolution.reset           = BGFX_RESET_VSYNC;
    const bool initialized = bgfx::init(init);
    LITE_ASSERT(initialized);

    // Initialize debug draw
    ddInit(&s_allocator);

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

    DebugDrawEncoder m_encoder;
    View m_view = 0;
};

void DebugDraw::Begin () {
    m_encoder.begin(m_view);
}

void DebugDraw::End () {
    m_encoder.end();
}

void DebugDraw::MoveTo (const Vec3f & pos) {
    m_encoder.moveTo(reinterpret_cast<const bx::Vec3 &>(pos));
}

void DebugDraw::LineTo (const Vec3f & pos) {
    m_encoder.lineTo(reinterpret_cast<const bx::Vec3 &>(pos));
}

void DebugDraw::Close () {
    m_encoder.close();
}

void DebugDraw::DrawSphere (const Sphere & sphere) {
    LITE_REF(sphere);
    ::Sphere _sphere;
    MemCopy(&_sphere.center, &sphere.center, sizeof(sphere.center));
    _sphere.radius = sphere.radius;
    m_encoder.draw(_sphere);
}


///////////////////////////////////////////////////////////
//
//    Scene
//
///////////////////////////////////////////////////////////

static uint32_t s_sceneCount = 0;

Scene::Scene (const Params & params) : m_params(params) {
    if (!s_sceneCount++) {
        s_context.Init(params);
    }
    m_view = s_context->AllocView();
    m_debugDraw = LITE_NEW(DebugDraw);
    bgfx::resetView(m_view);
}

Scene::~Scene () {
    LITE_DEL(m_debugDraw);
    if (!--s_sceneCount) {
        s_context.Destroy();
    }
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
    m_debugDraw->SetView(m_view);
    return m_debugDraw;
}

void Scene::SetCamera (const Vec3f & eye, const Vec3f & target) {
    bgfx::setViewRect(m_view, 0, 0, 1280, 720);

    float viewMtx[16];
    bx::mtxLookAt(
        viewMtx,
        reinterpret_cast<const bx::Vec3 &>(eye),
        reinterpret_cast<const bx::Vec3 &>(target)
    );

    float projMtx[16];
    bx::mtxProj(projMtx, 45.0f, 1280.0f / 720.0f, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

    bgfx::setViewTransform(m_view, viewMtx, projMtx);
}

} // namespace lite::graphics
