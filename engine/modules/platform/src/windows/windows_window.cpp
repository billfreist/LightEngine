///
/// LICENSE
///

#include "pch.h"

LITE_NAMESPACE_BEGIN(lite, platform)

WindowsWindow::WindowsWindow () {

}

WindowsWindow::~WindowsWindow () {
    DestroyWindow(m_hwnd);
}

void WindowsWindow::Close () {
    if (m_hwnd == HWND(-1))
        return;

    PostMessageA(m_hwnd, WM_CLOSE, 0, 0);
    m_hwnd = HWND(-1);
}

void WindowsWindow::GetKeyboardState (KeyboardState * state) {
    LITE_REF(state);
}

void WindowsWindow::GetMouseState (MouseState * state) {
    LITE_REF(state);
}

LITE_NAMESPACE_END(lite, platform)
