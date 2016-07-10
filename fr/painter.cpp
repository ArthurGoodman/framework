#include "painter.h"

#include <windows.h>
#include <algorithm>

fr::Painter::Painter(Canvas *canvas)
    : hdc(0), canvas(canvas), color(Color::rgb(0, 0, 0)), antialiasing(false) {
    if ((hdcWindow = canvas->begin())) {
        hdc = CreateCompatibleDC(hdcWindow);
        hBmp = CreateCompatibleBitmap(hdcWindow, canvas->width(), canvas->height());
        hBmpOld = SelectObject(hdc, hBmp);

        RECT rc = {0, 0, canvas->width(), canvas->height()};
        FillRect(hdc, &rc, (HBRUSH)COLOR_WINDOW);

        graphics = new Gdiplus::Graphics(hdc);

        graphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
        graphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
        graphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeNone);
        graphics->SetSmoothingMode(Gdiplus::SmoothingModeNone);
        graphics->SetInterpolationMode(Gdiplus::InterpolationModeDefault);
    }
}

fr::Painter::~Painter() {
    if (hdc) {
        BitBlt(hdcWindow, 0, 0, canvas->width(), canvas->height(), hdc, 0, 0, SRCCOPY);

        SelectObject(hdc, hBmpOld);
        DeleteObject(hBmp);
        DeleteDC(hdc);

        delete graphics;
    }

    canvas->end();
}

void fr::Painter::setColor(int rgba) {
    color = Color(rgba);
}

void fr::Painter::setColor(byte r, byte g, byte b, byte a) {
    color = Color(r, g, b, a);
}

void fr::Painter::setColor(const Color &color) {
    this->color = color;
}

void fr::Painter::setAntialiasing(bool antialiasing) {
    this->antialiasing = antialiasing;
}

void fr::Painter::drawLine(int x0, int y0, int x1, int y1) {
    if (hdc) {
        if (antialiasing)
            graphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

        Gdiplus::Pen pen(Gdiplus::Color(color.alpha(), color.red(), color.green(), color.blue()));
        graphics->DrawLine(&pen, x0, y0, x1, y1);

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

void fr::Painter::drawRect(const Rectangle &rect) {
    drawLine(rect.topLeft(), rect.topRight());
    drawLine(rect.topRight(), rect.bottomRight());
    drawLine(rect.bottomRight(), rect.bottomLeft());
    drawLine(rect.bottomLeft(), rect.topLeft());
}

void fr::Painter::fillRect(const Rectangle &rect, const Color &color) {
    if (hdc) {
        if (antialiasing)
            graphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

        Gdiplus::SolidBrush brush(Gdiplus::Color(color.alpha(), color.red(), color.green(), color.blue()));
        graphics->FillRectangle(&brush, Gdiplus::RectF(rect.left(), rect.top(), rect.width(), rect.height()));

        return;
    }

    int rgba = color.rgba();

    for (int i = rect.left(); i <= rect.right(); i++)
        for (int j = rect.top(); j <= rect.bottom(); j++)
            canvas->setPixel(i, j, rgba);
}

void fr::Painter::fillRect(int x, int y, int width, int height, const fr::Color &color) {
    fillRect(Rectangle(x, y, x + width, y + height), color);
}

void fr::Painter::drawEllipse(int x, int y, int w, int h) {
    if (hdc) {
        if (antialiasing)
            graphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

        Gdiplus::Pen pen(Gdiplus::Color(color.alpha(), color.red(), color.green(), color.blue()));
        graphics->DrawEllipse(&pen, x, y, w, h);

        return;
    }
}

void fr::Painter::drawEllipse(const Point &center, int rx, int ry) {
    drawEllipse(center.x() - rx, center.y() - ry, 2 * rx, 2 * ry);
}

void fr::Painter::fillEllipse(int x, int y, int w, int h) {
    if (hdc) {
        if (antialiasing)
            graphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

        Gdiplus::SolidBrush brush(Gdiplus::Color(color.alpha(), color.red(), color.green(), color.blue()));
        graphics->FillEllipse(&brush, x, y, w, h);

        return;
    }
}

void fr::Painter::fillEllipse(const fr::Point &center, int rx, int ry) {
    fillEllipse(center.x() - rx, center.y() - ry, 2 * rx, 2 * ry);
}

void fr::Painter::drawImage(const Rectangle &rect, const Image &image) {
    if (hdc) {
        HBITMAP hBitmap = CreateBitmap(image.width(), image.height(), 1, 32, image.bits());
        HDC hdcMem = CreateCompatibleDC(hdc);

        HGDIOBJ oldBitmap = SelectObject(hdcMem, hBitmap);

        SetStretchBltMode(hdc, HALFTONE);
        StretchBlt(hdc, rect.left(), rect.top(), rect.width(), rect.height(), hdcMem, 0, 0, image.width(), image.height(), SRCCOPY);

        SelectObject(hdcMem, oldBitmap);

        DeleteDC(hdcMem);
        DeleteObject(hBitmap);

        return;
    }

    for (int i = 0; i < image.width(); i++)
        for (int j = 0; j < image.height(); j++)
            canvas->setPixel(rect.left() + i, rect.top() + j, image.getPixel(i, j));
}

void fr::Painter::drawImage(int x, int y, const Image &image) {
    drawImage(Rectangle(x, y, x + image.width(), y + image.height()), image);
}

void fr::Painter::drawImage(int x, int y, int width, int height, const Image &image) {
    drawImage(Rectangle(x, y, x + width, y + height), image);
}
