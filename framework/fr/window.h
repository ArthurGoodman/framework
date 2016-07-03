#pragma once

#include <windef.h>
#include <map>

#include "size.h"
#include "rectangle.h"
#include "point.h"
#include "image.h"
#include "mouseevent.h"
#include "mousewheelevent.h"
#include "keyevent.h"

namespace fr {

class Window {
    static std::map<HWND, Window *> windows;

    HWND hWnd;

public:
    static Window *find(HWND hWnd);
    static Window *find(const std::string &title);

    Window();

    void resize(int width, int height);
    void resize(const Size &size);

    void move(int x, int y);
    void move(const Point &p);

    std::string title() const;
    void setTitle(const std::string title);

    Size size() const;
    Rectangle rect() const;

    Point position() const;

    int width() const;
    int height() const;

    void close();

    void show();

    Image capture() const;

protected:
    virtual void closeEvent();
    virtual void mouseDownEvent(MouseEvent *e);
    virtual void mouseUpEvent(MouseEvent *e);
    virtual void mouseDoubleClickEvent(MouseEvent *e);
    virtual void mouseMoveEvent(MouseEvent *e);
    virtual void mouseHoverEvent(MouseEvent *e);
    virtual void mouseWheelEvent(MouseWheelEvent *e);
    virtual void mouseLeaveEvent();
    virtual void keyDownEvent(KeyEvent *e);
    virtual void keyPressEvent(KeyEvent *e);
    virtual void keyUpEvent(KeyEvent *e);
    virtual void paintEvent();

private:
    static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

    Window(HWND hWnd);
};
}
