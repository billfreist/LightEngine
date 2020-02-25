///
/// LICENSE
///

#include "pch.h"

namespace lite::platform {

struct ModifierKeyMapping {
    int      osKey;
    Modifier key;
};
static constexpr ModifierKeyMapping kModifierMapping[] = {
    { VK_LCONTROL, Modifier::LCtrl  },
    { VK_RCONTROL, Modifier::RCtrl  },
    { VK_LSHIFT,   Modifier::LShift },
    { VK_RSHIFT,   Modifier::RShift },
    { VK_LMENU,    Modifier::LAlt   },
    { VK_RMENU,    Modifier::RAlt   },
};

static const class KeyMappings {
public:

    KeyMappings ();
    Key operator[] (uint8_t i) const { return m_keys[i]; }

private:

    Key m_keys[uint32_t(UINT8_MAX) + 1];
} kKeyMappings;

KeyMappings::KeyMappings () {
    MemZero(&m_keys, sizeof(m_keys));

    // Operations
    m_keys[VK_RETURN] = Key::Enter;
    m_keys[VK_SPACE] = Key::Space;
    m_keys[VK_BACK] = Key::Backspace;
    m_keys[VK_TAB] = Key::Tab;
    m_keys[VK_PRIOR] = Key::PageUp;
    m_keys[VK_NEXT] = Key::PageDown;
    m_keys[VK_INSERT] = Key::Insert;
    m_keys[VK_DELETE] = Key::Delete;
    m_keys[VK_HOME] = Key::Home;
    m_keys[VK_END] = Key::End;

    // Modifiers
    m_keys[VK_LCONTROL] = Key::LCtrl;
    m_keys[VK_RCONTROL] = Key::RCtrl;
    m_keys[VK_LSHIFT] = Key::LShift;
    m_keys[VK_RSHIFT] = Key::RShift;
    m_keys[VK_LMENU] = Key::LAlt;
    m_keys[VK_RMENU] = Key::RAlt;

    // Arrows
    m_keys[VK_UP] = Key::Up;
    m_keys[VK_DOWN] = Key::Down;
    m_keys[VK_LEFT] = Key::Left;
    m_keys[VK_RIGHT] = Key::Right;

    // F keys
    m_keys[VK_F1] = Key::F1;
    m_keys[VK_F2] = Key::F2;
    m_keys[VK_F3] = Key::F3;
    m_keys[VK_F4] = Key::F4;
    m_keys[VK_F5] = Key::F5;
    m_keys[VK_F6] = Key::F6;
    m_keys[VK_F7] = Key::F7;
    m_keys[VK_F8] = Key::F8;
    m_keys[VK_F9] = Key::F9;
    m_keys[VK_F10] = Key::F10;
    m_keys[VK_F11] = Key::F11;
    m_keys[VK_F12] = Key::F12;

    // Numbers
    m_keys[uint8_t('0')] = Key::k0;
    m_keys[uint8_t('1')] = Key::k1;
    m_keys[uint8_t('2')] = Key::k2;
    m_keys[uint8_t('3')] = Key::k3;
    m_keys[uint8_t('4')] = Key::k4;
    m_keys[uint8_t('5')] = Key::k5;
    m_keys[uint8_t('6')] = Key::k6;
    m_keys[uint8_t('7')] = Key::k7;
    m_keys[uint8_t('8')] = Key::k8;
    m_keys[uint8_t('9')] = Key::k9;

    // Letters
    m_keys[uint8_t('a')] = Key::A;
    m_keys[uint8_t('b')] = Key::B;
    m_keys[uint8_t('c')] = Key::C;
    m_keys[uint8_t('d')] = Key::D;
    m_keys[uint8_t('e')] = Key::E;
    m_keys[uint8_t('f')] = Key::F;
    m_keys[uint8_t('g')] = Key::G;
    m_keys[uint8_t('h')] = Key::H;
    m_keys[uint8_t('i')] = Key::I;
    m_keys[uint8_t('j')] = Key::J;
    m_keys[uint8_t('k')] = Key::K;
    m_keys[uint8_t('l')] = Key::L;
    m_keys[uint8_t('m')] = Key::M;
    m_keys[uint8_t('n')] = Key::N;
    m_keys[uint8_t('o')] = Key::O;
    m_keys[uint8_t('p')] = Key::P;
    m_keys[uint8_t('q')] = Key::Q;
    m_keys[uint8_t('r')] = Key::R;
    m_keys[uint8_t('s')] = Key::S;
    m_keys[uint8_t('t')] = Key::T;
    m_keys[uint8_t('u')] = Key::U;
    m_keys[uint8_t('v')] = Key::V;
    m_keys[uint8_t('w')] = Key::W;
    m_keys[uint8_t('x')] = Key::X;
    m_keys[uint8_t('y')] = Key::Y;
    m_keys[uint8_t('z')] = Key::Z;
}

} // namespace lite::platform
