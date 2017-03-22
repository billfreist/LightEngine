///
/// LICENSE
///

#pragma once

#if LITE_OS_WINDOWS

LITE_NAMESPACE_BEGIN(lite, platform)

class WindowsWindow : public Window {
public:

    WindowsWindow (HWND hwnd);
    ~WindowsWindow ();

public: // Window

    bool   IsClosed () const override;
    void   Close () override;
    void * GetHandle () const override;
    void   GetKeyboardState (KeyboardState * state) override;
    void   GetMouseState (MouseState * state) override;

private:

    HWND m_hwnd;
};

LITE_NAMESPACE_END(lite, platform)

#endif // #if LITE_OS_WINDOWS
