#pragma once

#include <windef.h>

namespace fr {

class KeyEvent {
    friend class Window;

public:
    enum KeyEventType {
        KeyDown,
        KeyPress,
        KeyUp
    };

private:
    KeyEventType _type;
    int _key;

public:
    KeyEventType type();
    int key() const;

protected:
    KeyEvent(KeyEventType type, int key);
};
}
