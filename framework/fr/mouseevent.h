#pragma once

#include "point.h"
#include "common.h"

namespace fr {

class MouseEvent {
    friend class Window;

public:
    enum MouseEventType {
        MouseDownEvent,
        MouseUpEvent,
        MouseDoubleClickEvent,
        MouseMoveEvent,
        MouseHoverEvent,
        MouseWheelEvent
    };

    enum MouseButton {
        NoButton,
        LeftButton,
        RightButton,
        MiddleButton
    };

private:
    MouseEventType _type;
    MouseButton _button;
    Point _pos;
    uint _modifiers;

public:
    MouseEventType type() const;
    MouseButton button() const;
    Point pos() const;
    uint modifiers() const;

protected:
    MouseEvent(MouseEventType type, MouseButton button, int x, int y, uint modifiers);
};
}
