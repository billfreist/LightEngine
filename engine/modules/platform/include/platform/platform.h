///
/// LICENSE
///

#pragma once

#include <core/ptr.h>

LITE_NAMESPACE_BEGIN(lite, platform)

class Window;
using WindowPtr = SharedPtr<Window>;

class Application {
public:

    /// Return the currently running Application object
    static Application * Get ();

public:

    Application () = default;
    virtual ~Application () = default;

    ///
    virtual WindowPtr CreateWindow () = 0;

protected:

    /// The main thread procedure for the application which ultimately
    /// calls the "LiteMain" function in user code.
    static uint32_t ThreadProc (Application * thisPtr, int argc, char ** argsv);

    Thread   m_thread   = { 1 * 1024 * 1024, "Application" };
    uint32_t m_exitCode = 0;
};


class Window {
public:

    ///
    virtual bool IsClosed () const = 0;

    /// Close the window by posting the relevant message to it. This object will be deleted.
    virtual void Close () = 0;

    ///
    virtual void * GetHandle () const = 0;

    /// Grab the current snapshot of the keyboard state
    virtual void GetKeyboardState (struct KeyboardState * state) = 0;

    /// Grab the current snapshot of the mouse state
    virtual void GetMouseState (struct MouseState * state) = 0;

protected:

    virtual ~Window () { }

    friend class SharedPtr<Window>;
    friend class std::_Ref_count<Window>;
    friend class std::shared_ptr<Window>;
};


enum class Key : uint8_t {
    kUp,
    kDown,
    kLeft,
    kRight,

    kBackspace,
    kEnter,
    kTab,
    kSpace,
    kPageUp,
    kPageDown,
    kHome,
    kEnd,
    kInsert,
    kDelete,

    kLCtrl,
    kRCtrl,
    kLShift,
    kRShift,
    kLAlt,
    kRAlt,

    kF1,
    kF2,
    kF3,
    kF4,
    kF5,
    kF6,
    kF7,
    kF8,
    kF9,
    kF10,
    kF11,
    kF12,

    k1,
    k2,
    k3,
    k4,
    k5,
    k6,
    k7,
    k8,
    k9,
    k0,

    kA,
    kB,
    kC,
    kD,
    kE,
    kF,
    kG,
    kH,
    kI,
    kJ,
    kK,
    kL,
    kM,
    kN,
    kO,
    kP,
    kQ,
    kR,
    kS,
    kT,
    kU,
    kV,
    kW,
    kX,
    kY,
    kZ,

    kCount,
};

enum class Modifier : uint32_t {
    kLCtrl = UINT32_C(1) << 0,
    kRCtrl = UINT32_C(1) << 1,

    kLShift = UINT32_C(1) << 2,
    kRShift = UINT32_C(1) << 3,

    kLAlt = UINT32_C(1) << 4,
    kRAlt = UINT32_C(1) << 5,
};
LITE_DEFINE_ENUM_BIT_OPERATORS(Modifier);


struct KeyboardState {
    ///
    bool keys[int32_t(Key::kCount)];

    ///
    Flags<Modifier> modifiers;
};


enum class MouseButtons : int32_t {
    kLeft,
    kRight,
    kMiddle,

    kCount,
};

struct MouseState {
    ///
    Vec2f pos = { tag::Uninitialized{} };

    ///
    bool buttons[int32_t(MouseButtons::kCount)];
};

LITE_NAMESPACE_END(lite, platform)
