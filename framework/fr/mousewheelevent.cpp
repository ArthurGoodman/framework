#include "mousewheelevent.h"

int fr::MouseWheelEvent::delta() const {
    return _delta;
}

fr::MouseWheelEvent::MouseWheelEvent(fr::MouseEvent::MouseEventType type, fr::MouseEvent::MouseButton button, int x, int y, uint modifiers, int delta)
    : MouseEvent(type, button, x, y, modifiers), _delta(delta) {
}
