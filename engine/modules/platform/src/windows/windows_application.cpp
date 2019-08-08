///
/// LICENSE
///

#include <pch.h>

#if LITE_OS_WINDOWS

#include <Xinput.h>

#ifndef XINPUT_DLL_A
#   define XINPUT_DLL_A "xinput.dll"
#endif

#ifdef CreateWindow
#   undef CreateWindow
#endif

namespace lite { namespace platform {

///////////////////////////////////////////////////////////
//
//    Constants
//
///////////////////////////////////////////////////////////

constexpr char MsgClassName[]   = "lite_msg_pump";
constexpr char ChildClassName[] = "lite_child_window";

enum UserWindowMsg : int32_t {
    kCreateWindow = WM_USER,
};


///////////////////////////////////////////////////////////
//
//    WindowsApplication
//
///////////////////////////////////////////////////////////

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
    void RegisterChildClass ();

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

        WindowMapping (WindowMapping && rhs) = default;
        WindowMapping & operator= (WindowMapping && rhs) = default;

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
    wnd.lpfnWndProc   = WindowsApplication::HwndProc;
    wnd.hInstance     = instance;
    wnd.lpszClassName = MsgClassName;
    if (::RegisterClassExA(&wnd) == 0) {
        LITE_ASSERT(false);
    }

    m_hwnd = CreateWindowExA(
        0, // dwExStyle
        MsgClassName,
        "Lite",
        WS_OVERLAPPED,
        CW_USEDEFAULT, // x
        CW_USEDEFAULT, // y
        CW_USEDEFAULT, // nWidth
        CW_USEDEFAULT, // nHeight
        HWND_MESSAGE,  // hWndParent
        nullptr,       // hMenu
        instance, 
        0              // lpParam
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
    ::UnregisterClassA(MsgClassName, instance);

    return m_exitCode;
}

bool WindowsApplication::Update () {
    return Application::Update();
}

WindowPtr WindowsApplication::CreateWindow () {
    const HWND id = (HWND)-intptr_t(m_windows.GetCount());
    if (!m_windows.GetCount()) {
        RegisterChildClass();
    }
    SendMessageA(m_hwnd, kCreateWindow, WPARAM(id), 0);
    WindowPtr ptr = (m_windows.Term() - 1)->window;
    return ptr;
}

void WindowsApplication::DestroyWindow (WindowsWindow * window) {
    if (!window)
        return;

    auto * mapping = std::find(m_windows.begin(), m_windows.end(), window);
    LITE_ASSERT(mapping != m_windows.end());
    window->Destroy();
    m_windows.RemoveOrdered(mapping);
    if (!m_windows.GetCount()) {
        ::UnregisterClassA(ChildClassName, (HINSTANCE)GetModuleHandle(nullptr));
    }
}

WindowsWindow * WindowsApplication::FindWindow (HWND hwnd) {
    auto * mapping = std::find(m_windows.begin(), m_windows.end(), hwnd);
    if (mapping == m_windows.end())
        return nullptr;

    return static_cast<WindowsWindow *>(mapping->window.Get());
}

void WindowsApplication::RegisterChildClass () {
    auto instance = (HINSTANCE)GetModuleHandle(nullptr);
    WNDCLASSEXA wnd;
    MemZero(&wnd, sizeof(wnd));
    wnd.cbSize        = sizeof(wnd);
    wnd.style         = CS_HREDRAW | CS_VREDRAW;
    wnd.lpfnWndProc   = WindowsApplication::HwndProc;
    wnd.hInstance     = instance;
    wnd.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
    wnd.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wnd.lpszClassName = ChildClassName;
    wnd.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
    RegisterClassExA(&wnd);
}

LRESULT CALLBACK WindowsApplication::HwndProc (HWND hwnd, UINT id, WPARAM wparam, LPARAM lparam) {
    switch (id) {
    case kCreateWindow: {
        auto instance = (HINSTANCE)GetModuleHandle(nullptr);

        HWND childHwnd = CreateWindowExA(
            0,             // dwExStyle
            ChildClassName,
            "Lite",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, // x
            CW_USEDEFAULT, // y
            1280,          // nWidth
            720,           // nHeight
            (HWND)0,       // hWndParent
            nullptr,       // hMenu
            instance,
            0              // lpParam
        );
        if (!childHwnd) {
            LITE_ASSERT(false);
        }

        WindowsWindow * win = LITE_NEW(WindowsWindow)(childHwnd);
        s_app->m_windows.Add({ childHwnd, WindowPtr(win) });
    }
    break;

    case WM_CLOSE: {
        s_app->DestroyWindow(s_app->FindWindow(hwnd));
    }
    break;

    case WM_QUIT: {
        if (s_app->m_hwnd == hwnd) {
            Message msg;
            msg.exit = true;
            s_app->PostMsg(std::move(msg));
            s_app->m_exit = true;
            s_app->m_hwnd = (HWND)0;
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
