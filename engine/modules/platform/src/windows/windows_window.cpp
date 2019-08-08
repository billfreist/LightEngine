///
/// LICENSE
///

#include "pch.h"

namespace lite::platform {

///////////////////////////////////////////////////////////
//
//    Constants
//
///////////////////////////////////////////////////////////

static const HWND kClosedHwnd  = (HWND)0;


///////////////////////////////////////////////////////////
//
//    WindowsWindow
//
///////////////////////////////////////////////////////////

WindowsWindow::WindowsWindow (HWND handle)
    : m_hwnd(handle)
{
}

WindowsWindow::~WindowsWindow () {
    HWND hwnd = m_hwnd.Load();
    if (hwnd != kClosedHwnd)
        ::DestroyWindow(hwnd);
}

void WindowsWindow::Destroy () {
    HWND hwnd = m_hwnd.Load();
    if (hwnd == kClosedHwnd)
        return;

    m_hwnd.Set(kClosedHwnd);
    ::DestroyWindow(hwnd);
}

bool WindowsWindow::IsClosed () const {
    return m_hwnd.LoadRelaxed() == kClosedHwnd;
}

void WindowsWindow::Close () {
    HWND hwnd = m_hwnd.Load();
    if (hwnd == kClosedHwnd)
        return;

    m_hwnd.Set(kClosedHwnd);
    SendMessageA(hwnd, WM_CLOSE, 0, 0);
}

void * WindowsWindow::GetHandle () const {
    return (void *)m_hwnd.LoadRelaxed();
}

} // namespace lite::platform
