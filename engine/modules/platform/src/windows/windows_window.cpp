///
/// LICENSE
///

#include "pch.h"

namespace lite { namespace platform {

static const HWND kInvalidHwnd = (HWND)-1;
static const HWND kClosedHwnd  = (HWND)-2;


WindowsWindow::WindowsWindow () : m_hwnd(kInvalidHwnd) {

}

WindowsWindow::~WindowsWindow () {
    if (m_hwnd != kInvalidHwnd && m_hwnd != kClosedHwnd)
        DestroyWindow(m_hwnd);
}

void WindowsWindow::SetHandle (HWND handle) {
    m_hwnd = handle;
}

bool WindowsWindow::IsClosed () const {
    return m_hwnd == kClosedHwnd;
}

void WindowsWindow::Close () {
    if (m_hwnd == kInvalidHwnd || m_hwnd == kClosedHwnd)
        return;

    HWND hwnd = m_hwnd;
    m_hwnd = kClosedHwnd;
    PostMessageA(hwnd, WM_CLOSE, 0, 0);
}

void * WindowsWindow::GetHandle () const {
    return (void *)m_hwnd;
}

}} // namespace lite::platform
