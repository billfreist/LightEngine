///
/// LICENSE
///

#include <pch.h>

#if LITE_OS_WINDOWS

#include <Xinput.h>

#ifndef XINPUT_DLL_A
#   define "xinput.dll"
#endif

#ifdef CreateWindow
#   undef CreateWindow
#endif

namespace lite { namespace platform {

enum UserWindowMsg : int32_t {
    kCreateWindow = WM_USER,
};

class WindowsApplication : public Application {
public:

    WindowsApplication ();
    ~WindowsApplication () override;

    int Run (int argc, char ** argsv);

public:

    bool      Update () override;
    WindowPtr CreateWindow () override;

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
        HWND      hwnd;
        WindowPtr window;

        bool operator== (const HWND & rhs) const          { return hwnd == rhs; }
        bool operator== (const WindowsWindow * rhs) const { return window.Get() == rhs; }
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
        WS_OVERLAPPED, //WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0,    // x
        0,    // y
        1280, // nWidth
        720,  // nHeight
        nullptr, // hWndParent
        nullptr, // hMenu
        // Now process messages
        instance,
        0     // lpParam
    );

    m_thread.Launch(WindowsApplication::ThreadProc, this, argc, argsv);

    MSG msg;
    msg.message = WM_NULL;
    while (!m_exit) {
        // Wait for input idle for ~16ms, which roughly equates to 60fps
        WaitForInputIdle(GetCurrentProcess(), 16);

        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    m_thread.WaitForExit();

    ::DestroyWindow(m_hwnd);

    return m_exitCode;
}

bool WindowsApplication::Update () {
    return Application::Update();
}

WindowPtr WindowsApplication::CreateWindow () {
    const HWND id = (HWND)-intptr_t(m_windows.GetCount());
    WindowsWindow * win = LITE_NEW(WindowsWindow);
    auto * entry = m_windows.Add({ id, WindowPtr(win, tag::RawPtr{}) });
    SendMessageA(m_hwnd, kCreateWindow, WPARAM(id), 0);
    return entry->window;
}

void WindowsApplication::DestroyWindow (WindowsWindow * window) {
    if (!window)
        return;

    auto * mapping = std::find(m_windows.begin(), m_windows.end(), window);
    LITE_ASSERT(mapping != m_windows.end());
    window->Close();
    m_windows.RemoveOrdered(mapping);
}

WindowsWindow * WindowsApplication::FindWindow (HWND hwnd) {
    auto * mapping = std::find(m_windows.begin(), m_windows.end(), hwnd);
    if (mapping == m_windows.end())
        return nullptr;

    return static_cast<WindowsWindow *>(mapping->window.Get());
}

LRESULT CALLBACK WindowsApplication::HwndProc (HWND hwnd, UINT id, WPARAM wparam, LPARAM lparam) {
    LITE_REF(hwnd, id, wparam, lparam);
    switch (id) {
    case kCreateWindow: {
        auto instance = (HINSTANCE)GetModuleHandle(nullptr);
        WNDCLASSEXA wnd;
        MemZero(&wnd, sizeof(wnd));
        wnd.cbSize        = sizeof(wnd);
        wnd.style         = CS_HREDRAW | CS_VREDRAW;
        wnd.lpfnWndProc   = WindowsApplication::HwndProc;
        wnd.hInstance     = instance;
        wnd.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
        wnd.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        wnd.lpszClassName = "lite_child";
        wnd.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
        RegisterClassExA(&wnd);

        HWND childHwnd = CreateWindowA(
            "lite_child",
            "Lite",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_POPUPWINDOW,
            0,    // x
            0,    // y
            1280, // nWidth
            720,  // nHeight
            s_app->m_hwnd, // hWndParent
            nullptr, // hMenu
            instance,
            0     // lpParam
        );
        for (WindowMapping & mapping : s_app->m_windows) {
            if (mapping.hwnd != (HWND)wparam)
                continue;

            mapping.hwnd = childHwnd;
            static_cast<WindowsWindow *>(mapping.window.Get())->SetHandle(childHwnd);
        }
    }
    break;

    case WM_CLOSE:
    case WM_QUIT: {
        s_app->DestroyWindow(s_app->FindWindow(hwnd));
        if (s_app->m_hwnd == hwnd || !s_app->m_windows.GetCount()) {
            Message msg;
            msg.exit = true;
            s_app->PostMsg(std::move(msg));
            s_app->m_exit = true;
            s_app->m_hwnd = (HWND)-1;
        }
        else {
            ::DestroyWindow(hwnd);
        }

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

}} // namespace lite::platform


// Application main entry point
int main (int argc, char ** argv) {
    lite::platform::WindowsApplication app;
    return app.Run(argc, argv);
}

#endif // #if LITE_OS_WINDOWS
