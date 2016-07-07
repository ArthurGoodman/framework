#include "mainwindow.h"

int main(int argc, const char **argv) {
    Application app(argc, argv);

    MainWindow w;
    w.setMinimumSize(app.desktop()->size() / 4);
    w.resize(1280, 720);
    w.move(Application::desktop()->rect().center() - w.rect().center());
    w.show();

    return app.run();
}
