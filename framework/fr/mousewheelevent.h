#pragma once

#include "mouseevent.h"

namespace fr {

class MouseWheelEvent : public MouseEvent {
    friend class Window;

    int _delta;

public:
    int delta() const;

protected:
    MouseWheelEvent(MouseEventType type, MouseButton button, int x, int y, uint modifiers, int delta);
};
}
