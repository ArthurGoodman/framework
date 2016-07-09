TEMPLATE = lib
CONFIG += windows c++11 staticlib
CONFIG -= app_bundle qt

HEADERS += \
    fr/application.h \
    fr/canvas.h \
    fr/color.h \
    fr/common.h \
    fr/directory.h \
    fr/file.h \
    fr/image.h \
    fr/keyevent.h \
    fr/mouseevent.h \
    fr/mousewheelevent.h \
    fr/painter.h \
    fr/point.h \
    fr/rectangle.h \
    fr/size.h \
    fr/timerevent.h \
    fr/window.h \
    fr.h \
    fr/vector2.h

SOURCES += \
    fr/application.cpp \
    fr/canvas.cpp \
    fr/color.cpp \
    fr/directory.cpp \
    fr/file.cpp \
    fr/image.cpp \
    fr/keyevent.cpp \
    fr/mouseevent.cpp \
    fr/mousewheelevent.cpp \
    fr/painter.cpp \
    fr/point.cpp \
    fr/rectangle.cpp \
    fr/size.cpp \
    fr/timerevent.cpp \
    fr/window.cpp \
    fr/vector2.cpp
