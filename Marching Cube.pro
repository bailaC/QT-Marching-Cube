#-------------------------------------------------
#
# Project created by QtCreator 2016-07-04T20:48:11
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengl_test_1
TEMPLATE = app

LIBS += -lGL -lglut -lGLU

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    opengl/paulslib.cpp \
    opengl/glvolume.cpp \
    opengl/opengllib.cpp \
    opengl/drawing.cpp \
    opengl/usage.cpp \
    opengl/bitmaplib.cpp \
    opengl/menus.cpp \
    histogram.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    opengl/bitmaplib.h \
    opengl/glvolume.h \
    opengl/opengllib.h \
    opengl/paulslib.h \
    opengl/simplex.h \
    histogram.h

FORMS    += mainwindow.ui

DISTFILES += \
    opengl/dump \
    opengl/cell.gz \
    opengl/cell \
    opengl/testcell
