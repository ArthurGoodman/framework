TEMPLATE = lib
CONFIG += windows c++11 staticlib
CONFIG -= app_bundle qt

SOURCES += \
    fr/application.cpp \
    fr/window.cpp \
    fr/size.cpp \
    fr/rectangle.cpp \
    fr/point.cpp \
    fr/file.cpp \
    fr/directory.cpp \
    fr/canvas.cpp \
    fr/color.cpp \
    fr/image.cpp \
    fr/painter.cpp \
    fr/keyevent.cpp \
    fr/mouseevent.cpp \
    fr/mousewheelevent.cpp \
    fr/timerevent.cpp

HEADERS += \
    fr/application.h \
    fr/window.h \
    fr/size.h \
    fr/rectangle.h \
    fr/point.h \
    fr/file.h \
    fr/directory.h \
    fr/canvas.h \
    fr/color.h \
    fr/common.h \
    fr/image.h \
    fr/painter.h \
    fr.h \
    fr/keyevent.h \
    fr/mouseevent.h \
    fr/mousewheelevent.h \
    fr/timerevent.h
