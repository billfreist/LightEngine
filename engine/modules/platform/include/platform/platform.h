///
/// LICENSE
///

#pragma once

#include <core/ptr.h>

#include <platform/input.h>

namespace lite::platform {

class Window;
using WindowPtr = SharedPtr<Window>;

struct Message {
    bool exit = false;
};

class Application {
public:

    /// Return the currently running Application object
    static Application * Get ();

public:

    Application ();
    virtual ~Application () = default;

    /// Grab the current snapshot of the keyboard state
    void GetKeyboardState (KeyboardState * state) const;

    /// Grab the current snapshot of the mouse state
    void GetMouseState (MouseState * state) const;

public:

    ///
    virtual bool Update ();

    ///
    virtual WindowPtr CreateWindow () = 0;

protected:

    void PostMsg (Message && msg);

    /// The main thread procedure for the application which ultimately
    /// calls the "LiteMain" function in user code.
    static uint32_t ThreadProc (Application * thisPtr, int argc, char ** argsv);

    KeyboardState m_keyboardState;
    MouseState    m_mouseState;

    Lock           m_messageQueueLock;
    Array<Message> m_messageQueue;

    Thread   m_thread   = { 1 * 1024 * 1024, "Application" };
    uint32_t m_exitCode = 0;
};


class Window : public RefCounted {
public:

    ///
    virtual bool IsClosed () const = 0;

    /// Close the window by posting the relevant message to it. This object will be deleted.
    virtual void Close () = 0;

    ///
    virtual void * GetHandle () const = 0;

protected:

    virtual ~Window () = default;
};

} // namespace lite::platform
