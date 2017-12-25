///
/// LICENSE
///

#pragma once

#if LITE_OS_WINDOWS

namespace lite { namespace platform {

class WindowsWindow : public Window {
public:

    WindowsWindow ();
    ~WindowsWindow ();

    void SetHandle (HWND handle);

public: // Window

    bool   IsClosed () const override;
    void   Close () override;
    void * GetHandle () const override;

private:

    HWND m_hwnd;

    KeyboardState m_keyboardState;
};

}} // namespace lite::platform

#endif // #if LITE_OS_WINDOWS
