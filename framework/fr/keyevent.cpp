#include "keyevent.h"

fr::KeyEvent::KeyEventType fr::KeyEvent::type() {
    return _type;
}

int fr::KeyEvent::key() const {
    return _key;
}

fr::KeyEvent::KeyEvent(fr::KeyEvent::KeyEventType type, int key)
    : _type(type), _key(key) {
}
