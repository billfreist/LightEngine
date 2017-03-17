///
/// LICENSE
///

#pragma once

#if LITE_OS_WINDOWS

LITE_NAMESPACE_BEGIN(lite, platform)

class WindowsWindow : public Window {
public:

    WindowsWindow ();
    ~WindowsWindow ();

public: // Window

    void Close () override;
    void GetKeyboardState (KeyboardState * state) override;
    void GetMouseState (MouseState * state) override;

private:

    HWND m_hwnd;
};

LITE_NAMESPACE_END(lite, platform)

#endif // #if LITE_OS_WINDOWS
