#include "mainwindow.h"

#include <iostream>

MainWindow::MainWindow() {
    desktop = Application::desktop();

    setTimer(16);
}

void MainWindow::closeEvent() {
    Application::instance()->quit();
}

void MainWindow::timerEvent(TimerEvent *) {
    update();
}

void MainWindow::keyPressEvent(KeyEvent *e) {
    switch (e->key()) {
    case VK_ESCAPE:
        close();
        break;

    case VK_F11:
        break;
    }
}

void MainWindow::paintEvent() {
    Painter p(this);
    p.drawImage(0, 0, width(), height(), desktop->capture());
}
