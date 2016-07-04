#include "size.h"

fr::Size::Size()
    : _width(0), _height(0) {
}

fr::Size::Size(int width, int height)
    : _width(width), _height(height) {
}

int fr::Size::width() const {
    return _width;
}

void fr::Size::setWidth(int width) {
    _width = width;
}

int fr::Size::height() const {
    return _height;
}

void fr::Size::setHeight(int height) {
    _height = height;
}

fr::Size fr::Size::operator+(const fr::Size &size) const {
    return Size(_width + size._width, _height + size._height);
}

fr::Size fr::Size::operator-(const fr::Size &size) const {
    return Size(_width - size._width, _height - size._height);
}

fr::Size fr::Size::operator*(int f) const {
    return Size(_width * f, _height * f);
}

fr::Size fr::Size::operator/(int f) const {
    return Size(_width / f, _height / f);
}

SIZE fr::Size::toNative() const {
    return {_width, _height};
}
