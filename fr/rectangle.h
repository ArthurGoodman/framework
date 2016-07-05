#pragma once

#include <windows.h>

#include "point.h"
#include "size.h"

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

    int width() const;
    int height() const;

    Size size() const;

    Point topLeft() const;
    Point topRight() const;
    Point bottomLeft() const;
    Point bottomRight() const;

    Point center() const;

    RECT toNative() const;
};
}
