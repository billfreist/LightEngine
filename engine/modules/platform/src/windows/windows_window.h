///
/// LICENSE
///

#pragma once

#if LITE_OS_WINDOWS

namespace lite::platform {

class WindowsWindow : public Window {
public:

    WindowsWindow (HWND handle);
    ~WindowsWindow ();

    void Destroy ();

public: // Window

    bool   IsClosed () const override;
    void   Close () override;
    void * GetHandle () const override;

private:

    Atomic<HWND> m_hwnd;

    KeyboardState m_keyboardState;
};

} // namespace lite::platform

#endif // #if LITE_OS_WINDOWS
