#include "canvas.h"

fr::Canvas::~Canvas() {
}

void fr::Canvas::setPixel(int x, int y, const Color &color) {
    setPixel(x, y, color.rgba());
}

fr::Size fr::Canvas::size() {
    return Size(width(), height());
}
