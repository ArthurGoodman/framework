#include "color.h"

int fr::Color::rgba(byte r, byte g, byte b, byte a) {
    return a << 24 | b << 16 | g << 8 | r;
}

int fr::Color::bgra(byte b, byte g, byte r, byte a) {
    return a << 24 | r << 16 | g << 8 | b;
}

int fr::Color::rgb(byte r, byte g, byte b) {
    return rgba(r, g, b, 255);
}

fr::Color fr::Color::fromBgra(int bgra) {
    return Color(blue(bgra), green(bgra), red(bgra), alpha(bgra));
}

byte fr::Color::red(int rgba) {
    return rgba & 0xff;
}

byte fr::Color::green(int rgba) {
    return (rgba >> 8) & 0xff;
}

byte fr::Color::blue(int rgba) {
    return (rgba >> 16) & 0xff;
}

byte fr::Color::alpha(int rgba) {
    return (rgba >> 24) & 0xff;
}

fr::Color::Color()
    : r(0), g(0), b(0), a(255) {
}

fr::Color::Color(byte r, byte g, byte b, byte a)
    : r(r), g(g), b(b), a(a) {
}

fr::Color::Color(int rgba)
    : r(red(rgba)), g(green(rgba)), b(blue(rgba)), a(alpha(rgba)) {
}

byte fr::Color::red() const {
    return r;
}

byte fr::Color::green() const {
    return g;
}

byte fr::Color::blue() const {
    return b;
}

byte fr::Color::alpha() const {
    return a;
}

int fr::Color::rgba() const {
    return rgba(r, g, b, a);
}

int fr::Color::bgra() const {
    return bgra(b, g, r, a);
}

COLORREF fr::Color::toNative() const {
    return RGB(r, g, b);
}
