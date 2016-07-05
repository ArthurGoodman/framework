#include "mouseevent.h"

fr::MouseEvent::MouseEventType fr::MouseEvent::type() const {
    return _type;
}

fr::MouseEvent::MouseButton fr::MouseEvent::button() const {
    return _button;
}

fr::Point fr::MouseEvent::pos() const {
    return _pos;
}

uint fr::MouseEvent::modifiers() const {
    return _modifiers;
}

fr::MouseEvent::MouseEvent(MouseEventType type, MouseButton button, int x, int y, uint modifiers)
    : _type(type), _button(button), _pos(Point(x, y)), _modifiers(modifiers) {
}
