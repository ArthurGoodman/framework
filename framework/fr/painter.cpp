#include "painter.h"

#include <windows.h>
#include <algorithm>
//#include <gdiplus.h>

fr::Painter::Painter(Canvas *canvas)
    : canvas(canvas), color(Color::rgb(0, 0, 0)) {
    hdc = canvas->begin();
}

fr::Painter::~Painter() {
    canvas->end();
}

void fr::Painter::setColor(int rgba) {
    color = rgba;
}

void fr::Painter::setColor(byte r, byte g, byte b, byte a) {
    color = Color::rgba(r, g, b, a);
}

void fr::Painter::setColor(const Color &color) {
    this->color = color;
}

void fr::Painter::drawLine(int x0, int y0, int x1, int y1) {
    if (hdc) {
        HPEN hPen = CreatePen(PS_SOLID, 1, 0);

        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, color.toNative());

        MoveToEx(hdc, x0, y0, 0);
        LineTo(hdc, x1, y1);

        DeleteObject(hPen);

        //        using namespace Gdiplus;
        //        Graphics g(hdc);
        //        Pen pen(Gdiplus::Color(255, 0, 0));
        //        g.DrawLine(&pen, x0, y0, x1, y1);

        return;
    }

    int rgba = color.rgba();

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = x1 >= x0 ? 1 : -1;
    int sy = y1 >= y0 ? 1 : -1;

    if (dy <= dx) {
        int d = (dy << 1) - dx;

        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;

        canvas->setPixel(x0, y0, rgba);

        for (int x = x0 + sx, y = y0, i = 1; i <= dx; i++, x += sx) {
            if (d > 0) {
                d += d2;
                y += sy;
            } else
                d += d1;

            canvas->setPixel(x, y, rgba);
        }
    } else {
        int d = (dx << 1) - dy;

        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;

        canvas->setPixel(x0, y0, rgba);

        for (int y = y0 + sy, x = x0, i = 1; i <= dy; i++, y += sy) {
            if (d > 0) {
                d += d2;
                x += sx;
            } else
                d += d1;

            canvas->setPixel(x, y, rgba);
        }
    }
}

void fr::Painter::drawLine(const Point &p0, const Point &p1) {
    drawLine(p0.x(), p0.y(), p1.x(), p1.y());
}

void fr::Painter::fillRect(const Rectangle &rect, const Color &color) {
    if (hdc) {
        RECT r = rect.toNative();
        HBRUSH hBrush = CreateSolidBrush(color.toNative());

        SelectObject(hdc, GetStockObject(DC_BRUSH));

        FillRect(hdc, &r, hBrush);

        DeleteObject(hBrush);
    }
}
