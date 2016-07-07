#pragma once

#include "fr.h"

class MainWindow : public Window {
    Window *desktop;

public:
    MainWindow();

protected:
    void closeEvent();
    void timerEvent(TimerEvent *e);
    void keyPressEvent(KeyEvent *e);
    void paintEvent();
};
