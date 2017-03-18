///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, platform)

constexpr HWND kInvalidHwnd = HWND(-1);
constexpr HWND kClosedHwnd  = HWND(-2);

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

void WindowsWindow::GetKeyboardState (KeyboardState * state) {
    LITE_REF(state);
}

void WindowsWindow::GetMouseState (MouseState * state) {
    LITE_REF(state);
}

LITE_NAMESPACE_END(lite, platform)
