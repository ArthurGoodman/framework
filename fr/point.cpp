#include "point.h"

fr::Point::Point()
    : _x(0), _y(0) {
}

fr::Point::Point(int x, int y)
    : _x(x), _y(y) {
}

int fr::Point::x() const {
    return _x;
}

int fr::Point::y() const {
    return _y;
}

int &fr::Point::rx() {
    return _x;
}

int &fr::Point::ry() {
    return _y;
}

fr::Point fr::Point::operator+(const fr::Point &p) const {
    return Point(_x + p._x, _y + p._y);
}

fr::Point fr::Point::operator-(const fr::Point &p) const {
    return Point(_x - p._x, _y - p._y);
}

fr::Point fr::Point::operator*(int f) const {
    return Point(_x * f, _y * f);
}

fr::Point fr::Point::operator/(int f) const {
    return Point(_x / f, _y / f);
}

POINT fr::Point::toNative() const {
    return {_x, _y};
}
