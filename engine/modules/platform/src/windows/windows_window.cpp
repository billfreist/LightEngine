///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, platform)

constexpr HWND kInvalidHwnd = (HWND)-1;
constexpr HWND kClosedHwnd  = (HWND)-2;


struct ModifierKeyMapping {
    int      osKey;
    Modifier key;
};
static const ModifierKeyMapping kModifierMapping[] = {
    { VK_LCONTROL, Modifier::kLCtrl  },
    { VK_RCONTROL, Modifier::kRCtrl  },
    { VK_LSHIFT,   Modifier::kLShift },
    { VK_RSHIFT,   Modifier::kRShift },
    { VK_LMENU,    Modifier::kLAlt   },
    { VK_RMENU,    Modifier::kRAlt   },
};

static const class KeyMapping {
public:

    KeyMapping ();
    Key operator[] (uint8_t i) const { return m_keys[i]; }

private:

    Key m_keys[uint32_t(UINT8_MAX) + 1];
} kKeyMapping;

KeyMapping::KeyMapping () {
    MemZero(&m_keys, sizeof(m_keys));

    // Operations
    m_keys[VK_RETURN] = Key::kEnter;
    m_keys[VK_SPACE] = Key::kSpace;
    m_keys[VK_BACK] = Key::kBackspace;
    m_keys[VK_TAB] = Key::kTab;
    m_keys[VK_PRIOR] = Key::kPageUp;
    m_keys[VK_NEXT] = Key::kPageDown;
    m_keys[VK_INSERT] = Key::kInsert;
    m_keys[VK_DELETE] = Key::kDelete;
    m_keys[VK_HOME] = Key::kHome;
    m_keys[VK_END] = Key::kEnd;

    // Modifiers
    m_keys[VK_LCONTROL] = Key::kLCtrl;
    m_keys[VK_RCONTROL] = Key::kRCtrl;
    m_keys[VK_LSHIFT] = Key::kLShift;
    m_keys[VK_RSHIFT] = Key::kRShift;
    m_keys[VK_LMENU] = Key::kLAlt;
    m_keys[VK_RMENU] = Key::kRAlt;

    // Arrows
    m_keys[VK_UP] = Key::kUp;
    m_keys[VK_DOWN] = Key::kDown;
    m_keys[VK_LEFT] = Key::kLeft;
    m_keys[VK_RIGHT] = Key::kRight;

    // F keys
    m_keys[VK_F1] = Key::kF1;
    m_keys[VK_F2] = Key::kF2;
    m_keys[VK_F3] = Key::kF3;
    m_keys[VK_F4] = Key::kF4;
    m_keys[VK_F5] = Key::kF5;
    m_keys[VK_F6] = Key::kF6;
    m_keys[VK_F7] = Key::kF7;
    m_keys[VK_F8] = Key::kF8;
    m_keys[VK_F9] = Key::kF9;
    m_keys[VK_F10] = Key::kF10;
    m_keys[VK_F11] = Key::kF11;
    m_keys[VK_F12] = Key::kF12;

    // Numbers
    m_keys[uint8_t('0')] = Key::k0;
    m_keys[uint8_t('1')] = Key::k1;
    m_keys[uint8_t('2')] = Key::k2;
    m_keys[uint8_t('3')] = Key::k3;
    m_keys[uint8_t('4')] = Key::k4;
    m_keys[uint8_t('5')] = Key::k5;
    m_keys[uint8_t('6')] = Key::k6;
    m_keys[uint8_t('7')] = Key::k7;
    m_keys[uint8_t('8')] = Key::k8;
    m_keys[uint8_t('9')] = Key::k9;

    // Letters
    m_keys[uint8_t('a')] = Key::kA;
    m_keys[uint8_t('b')] = Key::kB;
    m_keys[uint8_t('c')] = Key::kC;
    m_keys[uint8_t('d')] = Key::kD;
    m_keys[uint8_t('e')] = Key::kE;
    m_keys[uint8_t('f')] = Key::kF;
    m_keys[uint8_t('g')] = Key::kG;
    m_keys[uint8_t('h')] = Key::kH;
    m_keys[uint8_t('i')] = Key::kI;
    m_keys[uint8_t('j')] = Key::kJ;
    m_keys[uint8_t('k')] = Key::kK;
    m_keys[uint8_t('l')] = Key::kL;
    m_keys[uint8_t('m')] = Key::kM;
    m_keys[uint8_t('n')] = Key::kN;
    m_keys[uint8_t('o')] = Key::kO;
    m_keys[uint8_t('p')] = Key::kP;
    m_keys[uint8_t('q')] = Key::kQ;
    m_keys[uint8_t('r')] = Key::kR;
    m_keys[uint8_t('s')] = Key::kS;
    m_keys[uint8_t('t')] = Key::kT;
    m_keys[uint8_t('u')] = Key::kU;
    m_keys[uint8_t('v')] = Key::kV;
    m_keys[uint8_t('w')] = Key::kW;
    m_keys[uint8_t('x')] = Key::kX;
    m_keys[uint8_t('y')] = Key::kY;
    m_keys[uint8_t('z')] = Key::kZ;
}


WindowsWindow::WindowsWindow (HWND hwnd) : m_hwnd(hwnd) {

}

WindowsWindow::~WindowsWindow () {
    if (m_hwnd != kInvalidHwnd && m_hwnd != kClosedHwnd)
        DestroyWindow(m_hwnd);
}

bool WindowsWindow::IsClosed () const {
    return m_hwnd == kClosedHwnd;
}

void WindowsWindow::Close () {
    if (m_hwnd == kInvalidHwnd || m_hwnd == kClosedHwnd)
        return;

    PostMessageA(m_hwnd, WM_CLOSE, 0, 0);
    m_hwnd = kClosedHwnd;
}

void * WindowsWindow::GetHandle () const {
    return (void *)m_hwnd;
}

void WindowsWindow::GetKeyboardState (KeyboardState * state) {
    LITE_REF(state);
}

void WindowsWindow::GetMouseState (MouseState * state) {
    LITE_REF(state);
}

LITE_NAMESPACE_END(lite, platform)
