#pragma once

#include "point.h"

namespace fr {

class Rectangle {
    int _left, _right, _top, _bottom;

public:
    Rectangle();
    Rectangle(int left, int right, int top, int bottom);

    int left() const;
    int right() const;
    int top() const;
    int bottom() const;

    Point center() const;
};
}
