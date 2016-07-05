#pragma once

#include <windows.h>
#include <map>

#include "canvas.h"
#include "size.h"
#include "rectangle.h"
#include "point.h"
#include "image.h"
#include "timerevent.h"
#include "mouseevent.h"
#include "mousewheelevent.h"
#include "keyevent.h"

namespace fr {

class Window : public Canvas {
    static std::map<HWND, Window *> windows;

    PAINTSTRUCT ps;
    HDC hdc;

    HWND hWnd;

    Size minSize, maxSize;

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

    int minimumWidth() const;
    void setMinimumWidth(int width);

    int maximumWidth() const;
    void setMaximumWidth(int width);

    int minimumHeight() const;
    void setMinimumHeight(int height);

    int maximumHeight() const;
    void setMaximumHeight(int height);

    Size minimumSize() const;
    void setMinimumSize(const Size &size);
    void setMinimumSize(int width, int height);

    Size maximumSize() const;
    void setMaximumSize(const Size &size);
    void setMaximumSize(int width, int height);

    Size size() const;
    Rectangle rect() const;

    Point position() const;

    void close();

    bool isMinimized() const;
    bool isMaximized() const;
    bool isVisible() const;

    void show();

    void showNormal();
    void showMinimized();
    void showMaximized();
    void hide();

    void setTimer(int id, int interval);
    void setTimer(int interval);
    void killTimer(int id);

    void update();

    Image capture() const;

    HDC begin();
    void end();

    int getPixel(int x, int y) const;
    void setPixel(int x, int y, int rgba);

    int width() const;
    int height() const;

protected:
    virtual void closeEvent();
    virtual void timerEvent(TimerEvent *e);
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

    void initialize();
    void defaults();
};
}
