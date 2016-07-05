#pragma once

#include "color.h"
#include "point.h"
#include "canvas.h"
#include "rectangle.h"
#include "image.h"

namespace fr {

class Painter {
    HDC hdcWindow, hdc;
    HBITMAP hBmp;
    HGDIOBJ hBmpOld;

    Canvas *canvas;
    Color color;

public:
    Painter(Canvas *canvas);
    ~Painter();

    void setColor(int rgba);
    void setColor(byte r, byte g, byte b, byte a = 255);
    void setColor(const Color &color);

    void drawLine(int x1, int y1, int x2, int y2);
    void drawLine(const Point &p1, const Point &p2);

    void drawRect(const Rectangle &rect);

    void fillRect(const Rectangle &rect, const Color &color);
    void fillRect(int x, int y, int width, int height, const Color &color);

    void drawEllipse(int x, int y, int w, int h);

    void drawImage(const Rectangle &rect, const Image &image);
    void drawImage(int x, int y, const Image &image);
    void drawImage(int x, int y, int width, int height, const Image &image);
};
}
