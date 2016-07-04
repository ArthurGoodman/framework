#include "rectangle.h"

fr::Rectangle::Rectangle()
    : _left(0), _top(0), _right(0), _bottom(0) {
}

fr::Rectangle::Rectangle(int left, int top, int right, int bottom)
    : _left(left), _top(top), _right(right), _bottom(bottom) {
}

int fr::Rectangle::left() const {
    return _left;
}

int fr::Rectangle::top() const {
    return _top;
}

int fr::Rectangle::right() const {
    return _right;
}

int fr::Rectangle::bottom() const {
    return _bottom;
}

fr::Point fr::Rectangle::center() const {
    return Point((_left + _right) / 2, (_top + _bottom) / 2);
}

RECT fr::Rectangle::toNative() const {
    return {_left, _top, _right, _bottom};
}
