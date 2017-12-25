///
/// LICENSE
///

#include "pch.h"

extern int LiteMain (int argc, char ** argsv);

namespace lite { namespace platform {

static Application * s_application;

Application * Application::Get () {
    LITE_ASSERT(s_application);
    return s_application;
}

Application::Application () {
    MemZero(&m_keyboardState, sizeof(m_keyboardState));
    MemZero(&m_mouseState, sizeof(m_mouseState));
}

void Application::GetKeyboardState (KeyboardState * state) const {
    *state = m_keyboardState;
}

void Application::GetMouseState (MouseState * state) const {
    *state = m_mouseState;
}

bool Application::Update () {
    for (;;) {
        LITE_SCOPED_LOCK(m_messageQueueLock);
        if (!m_messageQueue.GetCount())
            break;

        if (m_messageQueue.Pop().exit)
            return true;
    }
    return false;
}

void Application::PostMsg (Message && msg) {
    LITE_SCOPED_LOCK(m_messageQueueLock);
    m_messageQueue.Add(std::forward<Message>(msg));
}

uint32_t Application::ThreadProc (Application * thisPtr, int argc, char ** argsv) {
    s_application = thisPtr;
    thisPtr->m_exitCode = (uint32_t)LiteMain(argc, argsv);
    s_application = nullptr;
    return thisPtr->m_exitCode;
}

}} // namespace lite::platform
