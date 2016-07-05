#include "application.h"

#include <windows.h>

#include "window.h"
#include "file.h"

fr::Application *fr::Application::application = 0;

fr::Application *fr::Application::instance() {
    return application;
}

fr::Window *fr::Application::desktop() {
    return Window::find(GetDesktopWindow());
}

fr::Application::Application(int /*argc*/, const char ** /*argv*/) {
    application = this;
}

void fr::Application::exit(int code) {
    PostQuitMessage(code);
}

void fr::Application::quit() {
    exit(0);
}

std::string fr::Application::moduleFilePath() {
    char result[MAX_PATH];
    return std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
}

std::string fr::Application::moduleFileName() {
    return File(moduleFilePath()).getSimpleName();
}

int fr::Application::run() {
    MSG msg;
    int bRet;

    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (bRet == -1) {
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
