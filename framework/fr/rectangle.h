#pragma once

#include <windows.h>

#include "point.h"

namespace fr {

class Rectangle {
    int _left, _top, _right, _bottom;

public:
    Rectangle();
    Rectangle(int left, int top, int right, int bottom);

    int left() const;
    int top() const;
    int right() const;
    int bottom() const;

    Point center() const;

    RECT toNative() const;
};
}
