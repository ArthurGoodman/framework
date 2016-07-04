#include "window.h"

#include <windowsx.h>

#include "application.h"
#include "image.h"

std::map<HWND, fr::Window *> fr::Window::windows;

fr::Window *fr::Window::find(HWND hwnd) {
    std::map<HWND, Window *>::iterator i = windows.find((hwnd));

    Window *window;

    if (i == windows.end())
        windows[hwnd] = window = new Window(hwnd);
    else
        window = i->second;

    return window;
}

fr::Window *fr::Window::find(const std::string &title) {
    return find(FindWindowA(title.data(), 0));
}

fr::Window::Window() {
    defaults();
    initialize();
}

void fr::Window::resize(int width, int height) {
    RECT winRect, clientRect;

    GetWindowRect(hWnd, &winRect);
    GetClientRect(hWnd, &clientRect);

    int dx = (clientRect.right - clientRect.left) - width;
    int dy = (clientRect.bottom - clientRect.top) - height;

    SetWindowPos(hWnd, 0, 0, 0, winRect.right - winRect.left - dx, winRect.bottom - winRect.top - dy, SWP_NOZORDER | SWP_NOMOVE);
}

void fr::Window::resize(const Size &size) {
    resize(size.width(), size.height());
}

void fr::Window::move(int x, int y) {
    RECT winRect, clientRect;

    GetWindowRect(hWnd, &winRect);
    GetClientRect(hWnd, &clientRect);

    SetWindowPos(hWnd, 0, x, y, winRect.right - winRect.left, winRect.bottom - winRect.top, SWP_NOZORDER);
}

void fr::Window::move(const Point &p) {
    move(p.x(), p.y());
}

std::string fr::Window::title() const {
    int length = GetWindowTextLengthA(hWnd) + 1;
    char *buffer = new char[length];
    GetWindowTextA(hWnd, buffer, length);
    std::string title(buffer);
    delete[] buffer;
    return title;
}

void fr::Window::setTitle(const std::string title) {
    SetWindowTextA(hWnd, title.data());
}

int fr::Window::minimumWidth() const {
    return minSize.width();
}

void fr::Window::setMinimumWidth(int width) {
    minSize.setWidth(width);
}

int fr::Window::maximumWidth() const {
    return maxSize.width();
}

void fr::Window::setMaximumWidth(int width) {
    maxSize.setWidth(width);
}

int fr::Window::minimumHeight() const {
    return minSize.height();
}

void fr::Window::setMinimumHeight(int height) {
    minSize.setHeight(height);
}

int fr::Window::maximumHeight() const {
    return maxSize.height();
}

void fr::Window::setMaximumHeight(int height) {
    maxSize.setHeight(height);
}

fr::Size fr::Window::minimumSize() const {
    return minSize;
}

void fr::Window::setMinimumSize(const Size &size) {
    minSize = size;
}

void fr::Window::setMinimumSize(int width, int height) {
    minSize.setWidth(width);
    minSize.setHeight(height);
}

fr::Size fr::Window::maximumSize() const {
    return maxSize;
}

void fr::Window::setMaximumSize(const Size &size) {
    maxSize = size;
}

void fr::Window::setMaximumSize(int width, int height) {
    maxSize.setWidth(width);
    maxSize.setHeight(height);
}

fr::Size fr::Window::size() const {
    return Size(width(), height());
}

fr::Rectangle fr::Window::rect() const {
    RECT rect;
    GetClientRect(hWnd, &rect);
    return Rectangle(rect.left, rect.top, rect.right, rect.bottom);
}

fr::Point fr::Window::position() const {
    RECT rect;
    GetClientRect(hWnd, &rect);
    return Point(rect.left, rect.top);
}

void fr::Window::close() {
    DestroyWindow(hWnd);
}

bool fr::Window::isMinimized() const {
    WINDOWPLACEMENT wndpl;
    GetWindowPlacement(hWnd, &wndpl);
    return wndpl.showCmd == SW_SHOWMINIMIZED;
}

bool fr::Window::isMaximized() const {
    WINDOWPLACEMENT wndpl;
    GetWindowPlacement(hWnd, &wndpl);
    return wndpl.showCmd == SW_SHOWMAXIMIZED;
}

bool fr::Window::isVisible() const {
    return IsWindowVisible(hWnd);
}

void fr::Window::show() {
    ShowWindow(hWnd, SW_SHOW);
}

void fr::Window::showNormal() {
    ShowWindow(hWnd, SW_NORMAL);
}

void fr::Window::showMinimized() {
    ShowWindow(hWnd, SW_MINIMIZE);
}

void fr::Window::showMaximized() {
    ShowWindow(hWnd, SW_MAXIMIZE);
}

void fr::Window::hide() {
    ShowWindow(hWnd, SW_NORMAL);
    ShowWindow(hWnd, SW_HIDE);
}

fr::Image fr::Window::capture() const {
    HDC hdc = GetDC(hWnd);
    HDC hdcMemory = CreateCompatibleDC(hdc);
    HBITMAP hbmp = CreateCompatibleBitmap(hdc, width(), height());

    SelectObject(hdcMemory, hbmp);

    BitBlt(hdcMemory, 0, 0, width(), height(), hdc, 0, 0, SRCCOPY);

    BITMAPINFO info;
    info.bmiHeader.biSize = sizeof(info.bmiHeader);

    if (!GetDIBits(hdc, hbmp, 0, 0, NULL, &info, DIB_RGB_COLORS))
        return Image();

    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biHeight = -info.bmiHeader.biHeight;

    Image image(info.bmiHeader.biWidth, -info.bmiHeader.biHeight);

    if (!GetDIBits(hdc, hbmp, 0, info.bmiHeader.biHeight, image.bits(), &info, DIB_RGB_COLORS))
        return Image();

    DeleteDC(hdcMemory);
    DeleteObject(hbmp);
    ReleaseDC(0, hdc);

    return image;
}

HDC fr::Window::begin() {
    return hdc = BeginPaint(hWnd, &ps);
}

void fr::Window::end() {
    EndPaint(hWnd, &ps);
}

int fr::Window::getPixel(int x, int y) const {
    return GetPixel(hdc, x, y) | 0xff000000;
}

void fr::Window::setPixel(int x, int y, int rgba) {
    SetPixel(hdc, x, y, Color(rgba).toNative());
}

int fr::Window::width() const {
    RECT rect;
    GetClientRect(hWnd, &rect);
    return rect.right - rect.left;
}

int fr::Window::height() const {
    RECT rect;
    GetClientRect(hWnd, &rect);
    return rect.bottom - rect.top;
}

void fr::Window::closeEvent() {
}

void fr::Window::mouseDownEvent(MouseEvent *) {
}

void fr::Window::mouseUpEvent(MouseEvent *) {
}

void fr::Window::mouseDoubleClickEvent(MouseEvent *) {
}

void fr::Window::mouseMoveEvent(MouseEvent *) {
}

void fr::Window::mouseHoverEvent(MouseEvent *) {
}

void fr::Window::mouseWheelEvent(MouseWheelEvent *) {
}

void fr::Window::mouseLeaveEvent() {
}

void fr::Window::keyDownEvent(KeyEvent *) {
}

void fr::Window::keyPressEvent(KeyEvent *) {
}

void fr::Window::keyUpEvent(KeyEvent *) {
}

void fr::Window::paintEvent() {
}

LRESULT CALLBACK fr::Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Window *window = Window::find(hWnd);

    switch (msg) {
    case WM_DESTROY:
        window->closeEvent();
        break;

    case WM_LBUTTONDOWN: {
        MouseEvent e(MouseEvent::MouseDownEvent, MouseEvent::LeftButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseDownEvent(&e);
        break;
    }

    case WM_LBUTTONUP: {
        MouseEvent e(MouseEvent::MouseUpEvent, MouseEvent::LeftButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseUpEvent(&e);
        break;
    }

    case WM_LBUTTONDBLCLK: {
        MouseEvent e(MouseEvent::MouseDoubleClickEvent, MouseEvent::LeftButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseDoubleClickEvent(&e);
        break;
    }

    case WM_RBUTTONDOWN: {
        MouseEvent e(MouseEvent::MouseDownEvent, MouseEvent::RightButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseDownEvent(&e);
        break;
    }

    case WM_RBUTTONUP: {
        MouseEvent e(MouseEvent::MouseUpEvent, MouseEvent::RightButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseUpEvent(&e);
        break;
    }

    case WM_RBUTTONDBLCLK: {
        MouseEvent e(MouseEvent::MouseDoubleClickEvent, MouseEvent::RightButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseDoubleClickEvent(&e);
        break;
    }

    case WM_MBUTTONDOWN: {
        MouseEvent e(MouseEvent::MouseDownEvent, MouseEvent::MiddleButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseDownEvent(&e);
        break;
    }

    case WM_MBUTTONUP: {
        MouseEvent e(MouseEvent::MouseUpEvent, MouseEvent::MiddleButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseUpEvent(&e);
        break;
    }

    case WM_MBUTTONDBLCLK: {
        MouseEvent e(MouseEvent::MouseDoubleClickEvent, MouseEvent::MiddleButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseDoubleClickEvent(&e);
        break;
    }

    case WM_MOUSEMOVE: {
        MouseEvent e(MouseEvent::MouseMoveEvent, MouseEvent::NoButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseMoveEvent(&e);

        TRACKMOUSEEVENT tme;

        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.dwHoverTime = 100;
        tme.hwndTrack = hWnd;

        TrackMouseEvent(&tme);

        break;
    }

    case WM_MOUSEHOVER: {
        MouseEvent e(MouseEvent::MouseHoverEvent, MouseEvent::NoButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        window->mouseHoverEvent(&e);
        break;
    }

    case WM_MOUSEWHEEL: {
        MouseWheelEvent e(MouseEvent::MouseWheelEvent, MouseEvent::NoButton, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), GET_KEYSTATE_WPARAM(wParam), GET_WHEEL_DELTA_WPARAM(wParam));
        window->mouseWheelEvent(&e);
        break;
    }

    case WM_MOUSELEAVE:
        window->mouseLeaveEvent();
        break;

    case WM_KEYDOWN: {
        KeyEvent e(KeyEvent::KeyDown, wParam);
        window->keyDownEvent(&e);

        if ((lParam & (1 << 30)) == 0) {
            KeyEvent e(KeyEvent::KeyPress, wParam);
            window->keyPressEvent(&e);
        }

        break;
    }

    case WM_KEYUP: {
        KeyEvent e(KeyEvent::KeyUp, wParam);
        window->keyUpEvent(&e);
        break;
    }

    case WM_PAINT:
        window->paintEvent();
        break;

    case WM_GETMINMAXINFO: {
        RECT winRect, clientRect;

        GetWindowRect(hWnd, &winRect);
        GetClientRect(hWnd, &clientRect);

        int dx = (winRect.right - winRect.left) - (clientRect.right - clientRect.left);
        int dy = (winRect.bottom - winRect.top) - (clientRect.bottom - clientRect.top);

        MINMAXINFO *mmi = (MINMAXINFO *)lParam;

        mmi->ptMinTrackSize.x = window->minSize.width() + dx;
        mmi->ptMinTrackSize.y = window->minSize.height() + dy;
        mmi->ptMaxTrackSize.x = window->maxSize.width() + dx;
        mmi->ptMaxTrackSize.y = window->maxSize.height() + dy;

        break;
    }

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

fr::Window::Window(HWND hWnd)
    : hWnd(hWnd) {
}

void fr::Window::initialize() {
    HINSTANCE hInst = GetModuleHandle(0);

    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;
    wc.lpszMenuName = NULL;

    std::string title = Application::instance()->moduleFileName();
    std::wstring wtitle(title.length(), L'\0');

    mbstowcs(&wtitle[0], title.data(), title.length());

    wc.lpszClassName = wtitle.data();

    RegisterClass(&wc);

    //    if (!RegisterClass(&wc))
    //        return 0;

    hWnd = CreateWindow(wtitle.data(), wtitle.data(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, NULL, NULL, hInst, NULL);

    //    if (!hwnd)
    //        return 0;

    windows[hWnd] = this;
}

void fr::Window::defaults() {
    maxSize = Size(0xffffff, 0xffffff);
}
