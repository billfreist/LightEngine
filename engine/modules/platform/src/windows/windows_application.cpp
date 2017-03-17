///
/// LICENSE
///

#include "pch.h"

#if LITE_OS_WINDOWS

#include <Xinput.h>

#ifndef XINPUT_DLL_A
#   define "xinput.dll"
#endif

#ifdef CreateWindow
#   undef CreateWindow
#endif

LITE_NAMESPACE_BEGIN(lite, platform)

enum UserWindowMsg : int32_t {
    kCreateWindow = WM_USER,

};

class WindowsApplication : public Application {
public:

    WindowsApplication ();
    ~WindowsApplication () override;

    int Run (int argc, char ** argsv);

public:

    Window * CreateWindow () override;

private:

    void DestroyWindow (WindowsWindow * window);
    WindowsWindow * FindWindow (HWND hwnd);

    /// Windows message processor
    static LRESULT CALLBACK HwndProc (HWND hwnd, UINT id, WPARAM wparam, LPARAM lparam);

    /// Application thread procedure
    static uint32_t ThreadProc (WindowsApplication * thisPtr, int argc, char ** argsv);

    // Main application window
    HWND m_hwnd;
    bool m_exit = false;

    struct WindowMapping {
        HWND            hwnd;
        WindowsWindow * window;

        bool operator== (const HWND & rhs) const          { return hwnd == rhs; }
        bool operator== (const WindowsWindow * rhs) const { return window == rhs; }
    };
    Array<WindowMapping> m_windows;
};
static WindowsApplication * s_app;

WindowsApplication::WindowsApplication () {
    LITE_ASSERT(!s_app);
    s_app = this;
}

WindowsApplication::~WindowsApplication () {
    LITE_ASSERT(s_app == this);
    s_app = nullptr;
}

int WindowsApplication::Run (int argc, char ** argsv) {

    auto instance = (HINSTANCE)GetModuleHandle(nullptr);
    WNDCLASSEXA wnd;
    MemZero(&wnd, sizeof(wnd));
    wnd.cbSize        = sizeof(wnd);
    wnd.style         = CS_HREDRAW | CS_VREDRAW;
    wnd.lpfnWndProc   = WindowsApplication::HwndProc;
    wnd.hInstance     = instance;
    wnd.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
    wnd.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wnd.lpszClassName = "lite";
    wnd.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
    RegisterClassExA(&wnd);

    m_hwnd = CreateWindowA(
        "lite",
        "Lite",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0,    // x
        0,    // y
        1280, // nWidth
        720,  // nHeight
        nullptr, // hWndParent
        nullptr, // hMenu
        instance,
        0     // lpParam
    );

    m_thread.Launch(WindowsApplication::ThreadProc, this, argc, argsv);

    MSG msg;
    msg.message = WM_NULL;
    while (!m_exit) {
        // Wait for input idle for ~16ms, which roughly equates to 60fps
        WaitForInputIdle(GetCurrentProcess(), 16);

        // Now process messages
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    m_thread.WaitForExit();

    ::DestroyWindow(m_hwnd);

    return m_exitCode;
}

Window * WindowsApplication::CreateWindow () {
    return LITE_NEW(WindowsWindow);
}

void WindowsApplication::DestroyWindow (WindowsWindow * window) {
    if (!window)
        return;

    auto * mapping = std::find(m_windows.begin(), m_windows.end(), window);
    LITE_ASSERT(mapping != m_windows.end());
    m_windows.RemoveOrdered(mapping);
    LITE_DEL(window);
}

WindowsWindow * WindowsApplication::FindWindow (HWND hwnd) {
    const auto * mapping = std::find(m_windows.begin(), m_windows.end(), hwnd);
    if (mapping == m_windows.end())
        return nullptr;

    return mapping->window;
}

LRESULT CALLBACK WindowsApplication::HwndProc (HWND hwnd, UINT id, WPARAM wparam, LPARAM lparam) {
    LITE_REF(hwnd, id, wparam, lparam);
    switch (id) {
    case WM_CLOSE:
    case WM_QUIT: {
        s_app->DestroyWindow(s_app->FindWindow(hwnd));
        if (s_app->m_hwnd == hwnd)
            s_app->m_exit = true;
        return 0;
    }

    default:
        break;
    }
    return DefWindowProc(hwnd, id, wparam, lparam);
}

uint32_t WindowsApplication::ThreadProc (WindowsApplication * thisPtr, int argc, char ** argsv) {
    const uint32_t exitCode = Application::ThreadProc(thisPtr, argc, argsv);
    PostMessageA(thisPtr->m_hwnd, WM_QUIT, 0, 0);
    return exitCode;
}

LITE_NAMESPACE_END(lite, platform)


// Application main entry point
int main (int argc, char ** argv) {
    lite::platform::WindowsApplication app;
    return app.Run(argc, argv);
}

#endif // #if LITE_OS_WINDOWS
