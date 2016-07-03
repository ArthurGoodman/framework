#include "rectangle.h"

fr::Rectangle::Rectangle()
    : _left(0), _right(0), _top(0), _bottom(0) {
}

fr::Rectangle::Rectangle(int left, int right, int top, int bottom)
    : _left(left), _right(right), _top(top), _bottom(bottom) {
}

int fr::Rectangle::left() const {
    return _left;
}

int fr::Rectangle::right() const {
    return _right;
}

int fr::Rectangle::top() const {
    return _top;
}

int fr::Rectangle::bottom() const {
    return _bottom;
}

fr::Point fr::Rectangle::center() const {
    return Point((_left + _right) / 2, (_top + _bottom) / 2);
}
