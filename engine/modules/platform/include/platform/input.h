///
/// LICENSE
///

#pragma once

#include <core/ptr.h>

LITE_NAMESPACE_BEGIN(lite, platform)

enum class Key : uint8_t {
    Up,
    Down,
    Left,
    Right,

    Backspace,
    Enter,
    Tab,
    Space,
    PageUp,
    PageDown,
    Home,
    End,
    Insert,
    Delete,

    LCtrl,
    RCtrl,
    LShift,
    RShift,
    LAlt,
    RAlt,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,

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

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    Count,
};

enum class Modifier : uint32_t {
    LCtrl = UINT32_C(1) << 0,
    RCtrl = UINT32_C(1) << 1,

    LShift = UINT32_C(1) << 2,
    RShift = UINT32_C(1) << 3,

    LAlt = UINT32_C(1) << 4,
    RAlt = UINT32_C(1) << 5,
};
LITE_DEFINE_ENUM_BIT_OPERATORS(Modifier);


struct KeyboardState {
    ///
    bool keys[int32_t(Key::Count)];

    ///
    Flags<Modifier> modifiers;
};


enum class MouseButtons : int32_t {
    Left,
    Right,
    Middle,

    Count,
};

struct MouseState {
    ///
    Vec2f pos = { tag::Uninitialized{} };

    ///
    bool buttons[int32_t(MouseButtons::Count)];
};

LITE_NAMESPACE_END(lite, platform)
